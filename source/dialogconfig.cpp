#include "dialogconfig.h"
#include "ui_dialogconfig.h"

#include <QFile>
#include <QTextStream>

DialogConfig::DialogConfig(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogConfig)
{
    ui->setupUi(this);
    connect(this->ui->pushButton,SIGNAL(clicked()),this,SLOT(close()));
}

DialogConfig::~DialogConfig()
{
    delete ui;
}


void DialogConfig::save()
{
    //QFile file()
}
