#include "widgetconsole.h"
#include <QPainter>
#include <QBrush>
#include <QColor>
#include <QDebug>
#include <QSizePolicy>
#include <QTextBlock>
#include "builder.h"

WidgetConsole::WidgetConsole() :
    QPlainTextEdit(0),
    //_mainWidget(new QPlainTextEdit()),
    _builder(0)
{
    _height = 100;
    _collapsed = true;
    //this->setWidget(_mainWidget);
    this->setMaximumHeight(0);
    this->setMinimumHeight(0);
    this->setSizePolicy(QSizePolicy(QSizePolicy::Ignored, QSizePolicy::Minimum));
    this->setMouseTracking(true);
    this->setReadOnly(true);

}
/*
void WidgetConsole::paintEvent(QPaintEvent *)
{
    QPainter painter(this);

    painter.setBrush(QBrush(QColor(200,0,0)));
    painter.drawRect(0,0,100,100);
}*/

void WidgetConsole::setBuilder(Builder *builder)
{
    this->_builder = builder;
    if(!this->_builder)
    {
        return;
    }

    connect(_builder, SIGNAL(error()),this, SLOT(onError()));
    connect(_builder, SIGNAL(success()),this, SLOT(onSuccess()));
    connect(_builder, SIGNAL(started()), this, SLOT(clear()));
    connect(_builder, SIGNAL(outputReady(QString)), this, SLOT(appendPlainText(QString)));
}

void WidgetConsole::mouseMoveEvent(QMouseEvent * event)
{
    QPlainTextEdit::mouseMoveEvent(event);
    if(event->modifiers() == Qt::CTRL)
    {
        this->setCursor(Qt::PointingHandCursor);
    }
    else
    {
        this->setCursor(Qt::ArrowCursor);
    }
}
void WidgetConsole::mousePressEvent(QMouseEvent *event)
{
    QPlainTextEdit::mousePressEvent(event);
    if(event->modifiers() == Qt::CTRL)
    {
        //this->setCursor(Qt::PointingHandCursor);
        qDebug()<<this->textCursor().blockNumber();
        QString text = this->textCursor().block().text();
        if(text.length() && !text.left(2).compare("l."))
        {
            int firstSpace = text.indexOf(" ");
            int lineNumber = text.mid(2,firstSpace-2).toInt();
            emit requestLine(lineNumber);
        }
    }
}

void WidgetConsole::expand()
{
    if(_collapsed || this->maximumHeight()==0)
    {
        _collapsed = false;
        this->setMaximumHeight(_height);
        this->setMinimumHeight(_height);
    }
}

void WidgetConsole::collapsed()
{
    if(!_collapsed)
    {
        _collapsed = true;

        this->setMaximumHeight(0);
        this->setMinimumHeight(0);
    }
}
void WidgetConsole::onError()
{
    this->setPlainText(this->_builder->simpleOutput().join("\n"));
    this->expand();
}
void WidgetConsole::onSuccess()
{
    this->setPlainText(this->_builder->simpleOutput().join("\n"));
    this->collapsed();
}
