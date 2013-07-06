#include "widgetinsertcommand.h"
#include "ui_widgetinsertcommand.h"
#include "widgettextedit.h"

WidgetInsertCommand::WidgetInsertCommand(WidgetTextEdit *parent) :
    QWidget(parent),
    ui(new Ui::WidgetInsertCommand)
{
    ui->setupUi(this);
    this->setVisible(false);
    this->ui->tableWidget->item(0,0)->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
}

WidgetInsertCommand::~WidgetInsertCommand()
{
    delete ui;
}
