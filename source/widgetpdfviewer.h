#ifndef WIDGETPDFVIEWER_H
#define WIDGETPDFVIEWER_H

#include <QWidget>

namespace Ui {
class WidgetPdfViewer;
}

class WidgetPdfDocument;

class WidgetPdfViewer : public QWidget
{
    Q_OBJECT
    
public:
    explicit WidgetPdfViewer(QWidget *parent = 0);
    ~WidgetPdfViewer();

    WidgetPdfDocument * widgetPdfDocument() { return this->_widgetPdfDocument; }
    
private:
    Ui::WidgetPdfViewer *ui;

    WidgetPdfDocument *_widgetPdfDocument;
};

#endif // WIDGETPDFVIEWER_H
