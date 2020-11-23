#include "KeyboardCommandWindow.hpp"
#include "ui_KeyboardCommandWindow.h"

KeyboardCommandWindow::KeyboardCommandWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::KeyboardCommandWindow)
{
    ui->setupUi(this);
    this->setFixedSize(520,280);

    QPixmap wPix(":command_icons/computer_key_W_T.png");
    QPixmap aPix(":command_icons/computer_key_A_T.png");
    QPixmap sPix(":command_icons/computer_key_S_T.png");
    QPixmap dPix(":command_icons/computer_key_D_T.png");
    QPixmap iPix(":command_icons/computer_key_I_T.png");
    QPixmap jPix(":command_icons/computer_key_J_T.png");
    QPixmap kPix(":command_icons/computer_key_K_T.png");
    QPixmap lPix(":command_icons/computer_key_L_T.png");

    ui->label_w->setPixmap(wPix);
    ui->label_a->setPixmap(aPix);
    ui->label_s->setPixmap(sPix);
    ui->label_d->setPixmap(dPix);
    ui->label_i->setPixmap(iPix);
    ui->label_j->setPixmap(jPix);
    ui->label_k->setPixmap(kPix);
    ui->label_l->setPixmap(lPix);
}

KeyboardCommandWindow::~KeyboardCommandWindow()
{
    delete ui;
}
