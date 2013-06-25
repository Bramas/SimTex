#include "widgetviewer.h"
#include "ui_widgetviewer.h"
#include "document.h"
#include "file.h"
#include <QPainter>

WidgetViewer::WidgetViewer(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WidgetViewer),
    _document(0),
    _file(0)
{
    ui->setupUi(this);
}

WidgetViewer::~WidgetViewer()
{
    delete ui;
}

void WidgetViewer::initDocument()
{
    if(!_file)
    {
        return;
    }
    if(_document)
    {
        delete _document;
    }
    _document = new Document(_file->getFilename());

}

void WidgetViewer::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);

    painter.drawImage(0,0,this->_document->image(0));
}
