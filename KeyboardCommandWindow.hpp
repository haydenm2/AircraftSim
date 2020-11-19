#ifndef KEYBOARD_COMMAND_WINDOW_HPP
#define KEYBOARD_COMMAND_WINDOW_HPP

#include <QDialog>

namespace Ui {
class KeyboardCommandWindow;
}

class KeyboardCommandWindow : public QDialog
{
    Q_OBJECT

public:
    explicit KeyboardCommandWindow(QWidget *parent = nullptr);
    ~KeyboardCommandWindow();

private:
    Ui::KeyboardCommandWindow *ui;
};

#endif
