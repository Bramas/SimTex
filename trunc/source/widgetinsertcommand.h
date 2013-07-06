#ifndef WIDGETINSERTCOMMAND_H
#define WIDGETINSERTCOMMAND_H

#include <QWidget>

class WidgetTextEdit;
namespace Ui {
class WidgetInsertCommand;
}

class WidgetInsertCommand : public QWidget
{
    Q_OBJECT
    
public:
    explicit WidgetInsertCommand(WidgetTextEdit *parent = 0);
    ~WidgetInsertCommand();
    
private:
    Ui::WidgetInsertCommand *ui;
};

#endif // WIDGETINSERTCOMMAND_H
