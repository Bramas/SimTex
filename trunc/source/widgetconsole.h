#ifndef WIDGETCONSOLE_H
#define WIDGETCONSOLE_H

#include <QScrollArea>
#include <QPlainTextEdit>

class Builder;

class WidgetConsole : public QPlainTextEdit
{
    Q_OBJECT
public:
    explicit WidgetConsole();

    void setBuilder(Builder * builder);
    
signals:
    void requestLine(int);
public slots:
    void expand(void);
    void collapsed(void);
    void onError(void);
    void onSuccess(void);

protected:
    //void paintEvent(QPaintEvent *);
    void mouseMoveEvent(QMouseEvent * event);
    void mousePressEvent(QMouseEvent * event);

private:
    bool _collapsed;
    int _height;
    Builder * _builder;
    //QPlainTextEdit * _mainWidget;
    
};

#endif // WIDGETCONSOLE_H
