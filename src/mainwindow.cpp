#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>
#include <QStack>
#include <QImage>
#include <QPainter>
#include <QMessageBox>
#include <QColorDialog>

#include <QTimer>

#include "lsystem.h"
#include "lsystemexamples.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    lsystem(new LSystem(ui))
{
    ui->setupUi(this);

    QFont font("Monospace");
    font.setStyleHint(QFont::TypeWriter);
    ui->rulesPlainTextEdit->setFont(font);
    ui->startLineEdit->setFont(font);
    ui->resultPlainTextEdit->setFont(font);

    LSystemExamples::instance()->fillSettingsComboBox(ui->examplesComboBox);
    LSystemExamples::instance()->loadSettingsFromExample(0, ui);

    if (qApp->arguments().size() > 1)
    {
        if (qApp->arguments()[1] == "--run-tests")
        {
            QTimer::singleShot(1, this, SLOT(runTests()));
        }
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    if (ui->autoProduceCheckBox->isChecked())
        lsystem->produce();

    lsystem->paint(ui->canvas);
}

void MainWindow::on_pushButton_2_clicked()
{
    lsystem->produce();
}

void MainWindow::on_exampleLoadButton_clicked()
{
    LSystemExamples::instance()->loadSettingsFromExample(ui->examplesComboBox->currentIndex(), ui);
}

void MainWindow::on_actionE_xit_triggered()
{
    qApp->exit();
}

void MainWindow::on_lineColorPickerButton_clicked()
{
    QColor newColor = QColorDialog::getColor(Qt::blue, this);
    ui->lineColorLineEdit->setText(newColor.name());
}

void MainWindow::runTests()
{
    QStringList errors;
    // Testing the produce part only

    // Pythagoras tree test
    ui->startLineEdit->setText("0");
    ui->rulesPlainTextEdit->setPlainText("1 -> 11\n0 -> 1[+0]-0");

    auto expectedResults = QStringList()
            << "0"
            << "1[+0]-0"
            << "11[+1[+0]-0]-1[+0]-0"
            << "1111[+11[+1[+0]-0]-1[+0]-0]-11[+1[+0]-0]-1[+0]-0";

    for (int i = 0; i < expectedResults.size(); ++i)
    {
        ui->iterationsSpinBox->setValue(i);
        lsystem->produce();

        if (ui->resultPlainTextEdit->toPlainText() != expectedResults[i])
            errors.push_back(QString("Iteration(%1)").arg(i));
    }
    if (errors.empty())
    {
        qApp->exit(0);
        return;
    }

    qCritical() << "Not all tests have passed:";
    for (auto& error : errors)
    {
        qCritical() << " - " << error;
    }
    qApp->exit(errors.size());
}
