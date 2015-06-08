#ifndef LSYSTEM_H
#define LSYSTEM_H

class QComboBox;
class QLabel;

namespace Ui {
class MainWindow;
}


class LSystem
{
public:
    LSystem(Ui::MainWindow* settingsUi)
        : settingsUi(settingsUi) {}

    void paint(QLabel* canvas);
    void produce();

private:
    Ui::MainWindow* settingsUi;
};

#endif // LSYSTEM_H
