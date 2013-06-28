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
    void setBlockRange(int,int);

private:
    void paintEvent(QPaintEvent * event);
    
    WidgetTextEdit * widgetTextEdit;
    int scrollOffset;
    int firstVisibleBlock;
    int firstVisibleBlockTop;
    int _startBlock;
    int _endBlock;
};

#endif // WIDGETLINENUMBER_H
