#include "lsystemexamples.h"
#include "ui_mainwindow.h"
#include <QComboBox>

LSystemExamples* LSystemExamples::mInstance = nullptr;


LSystemExamples::LSystemExamples()
{
    // Instanciating all examples
    LSystemExample* e = nullptr;


    // Pythagoras tree
    examples.emplace_back();
    e = &examples.back();
    e->name = "Pythagoras tree";
    e->iterations = 6;
    e->start = "0";
    e->rules = "1 -> 11\n0 -> 1[+0]-0";
    e->angle = 45;
    e->line_length = 10;
    e->line_width = 3;
    e->line_color = "blue";
    e->start_upwards = true;


    // Koch curve
    examples.emplace_back();
    e = &examples.back();
    e->name = "Koch curve";
    e->iterations = 5;
    e->start = "F";
    e->rules = "F -> F-F+F+F-F";
    e->angle = 90;
    e->line_length = 5;
    e->line_width = 1;
    e->line_color = "blue";
    e->start_upwards = false;


    // Sierpinski triangle
    examples.emplace_back();
    e = &examples.back();
    e->name = "Sierpinski triangle";
    e->iterations = 8;
    e->start = "A";
    e->rules = "A -> B+A+B\nB -> A-B-A";
    e->angle = 60;
    e->line_length = 6;
    e->line_width = 2;
    e->line_color = "blue";
    e->start_upwards = false;


    // Dragon curve
    examples.emplace_back();
    e = &examples.back();
    e->name = "Dragon curve";
    e->iterations = 13;
    e->start = "FX";
    e->rules = "X -> X+YF+\nY -> -FX-Y";
    e->angle = 90;
    e->line_length = 6;
    e->line_width = 1;
    e->line_color = "blue";
    e->start_upwards = true;


    // Fractal plant
    examples.emplace_back();
    e = &examples.back();
    e->name = "Fractal plant";
    e->iterations = 7;
    e->start = "+X";
    e->rules = "X -> F-[[X]+X]+F[+FX]-X\nF -> FF";
    e->angle = 25;
    e->line_length = 6;
    e->line_width = 2;
    e->line_color = "green";
    e->start_upwards = true;
}

void LSystemExamples::fillSettingsComboBox(QComboBox *comboBox)
{
    // Clear items
    while(comboBox->count())
        comboBox->removeItem(0);

    // No iterator use because the position is needed
    for (int i = 0; i < examples.size(); ++i)
    {
        comboBox->addItem(examples[i].name, i);
    }
}

void LSystemExamples::loadSettingsFromExample(int i, Ui::MainWindow* ui)
{
    LSystemExample& e = examples[i];
    ui->iterationsSpinBox->setValue(e.iterations);
    ui->startLineEdit->setText(e.start);
    ui->rulesPlainTextEdit->setPlainText(e.rules);
    ui->angleSpinBox->setValue(e.angle);
    ui->lineLengthSpinBox->setValue(e.line_length);
    ui->lineWidthSpinBox->setValue(e.line_width);
    ui->lineColorLineEdit->setText(e.line_color);
    ui->startUpwardsCheckBox->setChecked(e.start_upwards);
}
