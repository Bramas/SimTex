#include "widgetpdfviewer.h"
#include "ui_widgetpdfviewer.h"
#include "widgetpdfdocument.h"
#include <QImage>
#include <QIcon>
#include <QDebug>

WidgetPdfViewer::WidgetPdfViewer(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WidgetPdfViewer),
    _widgetPdfDocument(new WidgetPdfDocument(this))
{
    ui->setupUi(this);

    this->ui->pushButtonZoomIn->setVisible(false);
    this->ui->pushButtonZoomOut->setVisible(false);
    this->ui->verticalLayout->removeWidget(this->ui->pushButtonZoomIn);
    this->ui->verticalLayout->removeWidget(this->ui->pushButtonZoomOut);
    this->ui->verticalLayout->addWidget(_widgetPdfDocument);
/*
     QPixmap zoomOut(":/icons/data/icons/zoom-out.png");
     QIcon buttonIconZoomOut(zoomOut);
     this->ui->pushButtonZoomOut->setIcon(buttonIconZoomOut);
     this->ui->pushButtonZoomOut->setIconSize(zoomOut.rect().size());

     QPixmap zoomIn(":/icons/data/icons/zoom-in.png");
     QIcon buttonIconZoomIn(zoomIn);
     this->ui->pushButtonZoomIn->setIcon(buttonIconZoomIn);
     this->ui->pushButtonZoomIn->setIconSize(zoomIn.rect().size());

     connect(this->ui->pushButtonZoomIn, SIGNAL(clicked()), this->_widgetPdfDocument, SLOT(zoomIn()));
     connect(this->ui->pushButtonZoomOut, SIGNAL(clicked()), this->_widgetPdfDocument, SLOT(zoomOut()));*/
}

WidgetPdfViewer::~WidgetPdfViewer()
{
    delete ui;
}
