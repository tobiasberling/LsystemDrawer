#include "lsystem.h"
#include "ui_mainwindow.h"

#include <QPainter>
#include <QStack>
#include <QMessageBox>
#include <QDebug>

void LSystem::paint(QLabel *canvas)
{
    auto product = settingsUi->resultPlainTextEdit->toPlainText();
    product = product.trimmed().replace(' ', "").replace('\n', "");


    // Set up off screen image for drawing
    QImage image(10000, 10000, QImage::Format_RGB16);
    image.fill(Qt::white);
    QPainter painter(&image);
    painter.translate(image.width() / 2, image.height() / 2);
    painter.scale(1, -1);


    // Setup helper variables
    QPointF position, tmp;
    QPointF direction(0, 1); // upwards
    int length = settingsUi->lineLengthSpinBox->value();
    QStack<QPointF> stackPosition;
    QStack<QPointF> stackDirection;

    QMatrix rotateMatrixLeft = QMatrix().rotate(settingsUi->angleSpinBox->value());
    QMatrix rotateMatrixRight = QMatrix().rotate(-1 * settingsUi->angleSpinBox->value());
    QColor lineColor = Qt::blue;
    QColor settingsColor(settingsUi->lineColorLineEdit->text());
    if (settingsColor.isValid())
        lineColor = settingsColor;
    painter.setPen(QPen(lineColor, settingsUi->lineWidthSpinBox->value(), Qt::SolidLine, Qt::SquareCap, Qt::BevelJoin));

    if (!settingsUi->startUpwardsCheckBox->isChecked())
        direction = QPointF(1, 0);

    qreal minX = -1;
    qreal minY = -1;
    qreal maxX = 1;
    qreal maxY = 1;

    for (auto symbol : product)
    {
        switch (symbol.unicode())
        {
        case '0':
        case '1':
        case 'F':
        case 'A':
        case 'B':
            tmp = position;
            position += direction * length;
            painter.drawLine(tmp, position);
            minX = qMin(qMin(tmp.x(), position.x()), minX);
            maxX = qMax(qMax(tmp.x(), position.x()), maxX);
            minY = qMin(qMin(tmp.y(), position.y()), minY);
            maxY = qMax(qMax(tmp.y(), position.y()), maxY);
            break;
        case '[':
            stackPosition.push(position);
            stackDirection.push(direction);
            break;
        case ']':
            position = stackPosition.pop();
            direction = stackDirection.pop();
            break;
        case '+':
            direction = rotateMatrixRight.map(direction);
            break;
        case '-':
        case 8722: // unicode '-' used on wikipedia
            direction = rotateMatrixLeft.map(direction);
            break;
        case 'X':
        case 'Y':
            // ignore
            break;
        default:
            qDebug() << "Unknown symbol `" << symbol.unicode() << "`";
        }
    }
    painter.end();


    // Crop image to painted area + margin
    qreal halfWidth = 0.5 * image.width();
    qreal halfHeight = 0.5 * image.height();

    if (minX < -halfWidth || maxX > halfWidth || minY < -halfHeight || maxY > halfHeight)
        QMessageBox::warning(nullptr, "Drawing out of image", "The interal image size is not large enough to represent the current instructions with the given drawing settings.");

    image = image.copy(qMax<qreal>(0, halfWidth + minX - 10),
                       qMax<qreal>(0, halfHeight - maxY - 10),
                       qMin<qreal>(image.width(), maxX - minX + 20),
                       qMin<qreal>(image.height(), maxY - minY + 20));


    // Scale image to label size and set pixmap
    image = image.scaled(settingsUi->canvas->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
    QPixmap pixmap = QPixmap::fromImage(image);
    canvas->setPixmap(pixmap);
}


/*
 * L-system parameters are read from ui
 *
 * Multiple rules are split by new line.
 *   Format: predecessor -> successor
 */
void LSystem::produce()
{
    const int iterations = settingsUi->iterationsSpinBox->value();
    QString production = settingsUi->startLineEdit->text();

    QMap<QString, QString> rules;
    for (QString rule : settingsUi->rulesPlainTextEdit->toPlainText().trimmed().split('\n', QString::SkipEmptyParts))
    {
        QStringList tmp = rule.split("->");
        if (tmp.size() != 2)
        {
            QMessageBox::critical(nullptr, "Invalid rule", "Invalid production rule: `" + rule + "`. Cannot continue. Please fix your rules!");
            return;
        }
        rules[tmp[0].trimmed()] = tmp[1].trimmed();
    }


    for (int i = 0; i < iterations; ++i)
    {
        QStringList next;
        for (QString c : production)
        {
            next.push_back(rules.contains(c) ? rules[c] : c);
        }
        production = next.join("");
    }
    settingsUi->resultPlainTextEdit->setPlainText(production);
}
