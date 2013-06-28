#ifndef WIDGETCONSOLE_H
#define WIDGETCONSOLE_H

#include <QWidget>

class Builder;

class WidgetConsole : public QWidget
{
    Q_OBJECT
public:
    explicit WidgetConsole();

    void setBuilder(Builder * builder);
    
signals:
    
public slots:
    void expand(void);

protected:
    void paintEvent(QPaintEvent *);
    void mouseMoveEvent(QMouseEvent *);

private:
    bool _collapsed;
    int _height;
    Builder * _builder;
    
};

#endif // WIDGETCONSOLE_H
