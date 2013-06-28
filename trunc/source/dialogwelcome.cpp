#include "dialogwelcome.h"
#include "ui_dialogwelcome.h"

DialogWelcome::DialogWelcome(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogWelcome)
{
    ui->setupUi(this);
}

DialogWelcome::~DialogWelcome()
{
    delete ui;
}
QPushButton * DialogWelcome::getActionNew()
{
    return this->ui->pushButtonNew;
}
QPushButton * DialogWelcome::getActionOpen()
{
    return this->ui->pushButtonOpen;
}
QPushButton * DialogWelcome::getActionOpenLast()
{
    return this->ui->pushButtonOpenLast;
}
