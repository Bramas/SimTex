#include "dialogconfig.h"
#include "configmanager.h"
#include "ui_dialogconfig.h"

#include <QFile>
#include <QTextStream>
#include <QDebug>

DialogConfig::DialogConfig(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogConfig)
{
    ui->setupUi(this);
    connect(this->ui->pushButton,SIGNAL(clicked()),this,SLOT(saveAndClose()));
    connect(this->ui->pushButton_2,SIGNAL(clicked()),this,SLOT(close()));
}

DialogConfig::~DialogConfig()
{
    delete ui;
}


void DialogConfig::saveAndClose()
{
    QSettings settings;
    settings.beginGroup("theme");
    if(this->ui->radioButtonLightTheme->isChecked())
    {
        settings.setValue("theme",QString("light"));
    }
    else
    {
        settings.setValue("theme",QString("dark"));
    }

    settings.setValue("pointSize",this->ui->spinBoxPointSize->value());
    ConfigManager::Instance.setPointSize(this->ui->spinBoxPointSize->value());
    this->accept();
}

void DialogConfig::save()
{
    //QFile file()
}
void DialogConfig::show()
{
    QSettings settings;
    settings.beginGroup("theme");
    if(!settings.value("theme",QString("dark")).toString().compare("dark"))
    {
        this->ui->radioButtonDarkTheme->setChecked(true);
        this->ui->radioButtonLightTheme->setChecked(false);
    }
    else
    {
        this->ui->radioButtonDarkTheme->setChecked(false);
        this->ui->radioButtonLightTheme->setChecked(true);
    }
    this->ui->spinBoxPointSize->setValue(ConfigManager::Instance.getTextCharFormats("normal").font().pointSize());
    QDialog::show();
}
