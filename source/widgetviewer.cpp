#include "widgetviewer.h"
#include "ui_widgetviewer.h"
#include <QPainter>
#include "widgetpdfdocument.h"

WidgetViewer::WidgetViewer(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WidgetViewer),
    _widgetPdfDocument(new WidgetPdfDocument(this))
{
    ui->setupUi(this);
    this->ui->verticalLayout->addWidget(_widgetPdfDocument);
}

WidgetViewer::~WidgetViewer()
{
    delete ui;
}

