#ifndef LSYSTEMEXAMPLES_H
#define LSYSTEMEXAMPLES_H

class QComboBox;
namespace Ui {
class MainWindow;
}

#include <vector>

struct LSystemExample {
    char* name;

    // lsystem
    int iterations;
    char* start;
    char* rules;

    // drawing
    int angle;
    int line_length;
    int line_width;
    char* line_color;
    bool start_upwards; // if false: start to the right
};


class LSystemExamples
{
public:
    static LSystemExamples* instance()
    {
        if (!mInstance)
            mInstance = new LSystemExamples();
        return mInstance;
    }
private:
    static LSystemExamples* mInstance;
    LSystemExamples();

public:
    void fillSettingsComboBox(QComboBox* comboBox);
    void loadSettingsFromExample(int i, Ui::MainWindow *ui);

private:
    std::vector<LSystemExample> examples;
};

#endif // LSYSTEMEXAMPLES_H
