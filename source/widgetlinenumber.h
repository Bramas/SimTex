#ifndef WIDGETLINENUMBER_H
#define WIDGETLINENUMBER_H

#include <QWidget>
class WidgetTextEdit;

class WidgetLineNumber : public QWidget
{
    Q_OBJECT
public:
    explicit WidgetLineNumber(QWidget *parent);
    void setWidgetTextEdit(WidgetTextEdit * widgetTextEdit);
signals:
    
public slots:
    void updateFirstVisibleBlock(int, int);

private:
    void paintEvent(QPaintEvent * event);
    
    WidgetTextEdit * widgetTextEdit;
    int scrollOffset;
    int firstVisibleBlock;
    int firstVisibleBlockTop;
};

#endif // WIDGETLINENUMBER_H
