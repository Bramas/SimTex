#include "dialogclose.h"
#include "ui_dialogclose.h"
#include <QDebug>

DialogClose::DialogClose(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogClose),
    _confirmed(false)
{
    ui->setupUi(this);

    connect(this->ui->confirmAndClose, SIGNAL(clicked()), this, SLOT(confirmAndClose()));
    connect(this->ui->cancel, SIGNAL(clicked()), this, SLOT(close()));
}

DialogClose::~DialogClose()
{
    delete ui;
}


void DialogClose::confirmAndClose()
{
    _confirmed = true;
    this->close();
}
void DialogClose::setMessage(QString message)
{
    this->ui->label->setText(message);
}
