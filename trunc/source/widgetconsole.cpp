#include "widgetconsole.h"
#include <QPainter>
#include <QBrush>
#include <QColor>
#include <QSizePolicy>
#include "builder.h"

WidgetConsole::WidgetConsole() :
    QWidget(0),
    _builder(0)
{
    _height = 100;
    _collapsed = true;
    this->setMinimumHeight(0);
    this->setSizePolicy(QSizePolicy(QSizePolicy::Ignored, QSizePolicy::Minimum));
    this->setMouseTracking(true);


}

void WidgetConsole::paintEvent(QPaintEvent *)
{
    QPainter painter(this);

    painter.setBrush(QBrush(QColor(200,0,0)));
    painter.drawRect(0,0,100,100);
}

void WidgetConsole::setBuilder(Builder *builder)
{
    this->_builder = builder;
    if(!this->_builder)
    {
        return;
    }

    //connect(_builder, SIGNAL(error()),this, SLOT(expand()));
}

void WidgetConsole::mouseMoveEvent(QMouseEvent *)
{
    this->setCursor(Qt::ArrowCursor);
}

void WidgetConsole::expand()
{
    if(_collapsed)
    {
        _collapsed = false;
        this->setMinimumHeight(_height);
    }
}
