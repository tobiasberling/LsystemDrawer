#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>
#include <QStack>
#include <QImage>
#include <QPainter>
#include <QMessageBox>
#include <QColorDialog>

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
