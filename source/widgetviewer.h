#ifndef WIDGETVIEWER_H
#define WIDGETVIEWER_H

#include <QWidget>

namespace Ui {
class WidgetViewer;
}
class File;
class WidgetPdfDocument;

class WidgetViewer : public QWidget
{
    Q_OBJECT
    
public:
    explicit WidgetViewer(QWidget *parent = 0);
    ~WidgetViewer();

    WidgetPdfDocument * widgetPdfDocument() { return this->_widgetPdfDocument; }

    
protected:

private:

    WidgetPdfDocument * _widgetPdfDocument;
    Ui::WidgetViewer *ui;

};

#endif // WIDGETVIEWER_H
