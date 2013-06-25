#ifndef WIDGETVIEWER_H
#define WIDGETVIEWER_H

#include <QWidget>

namespace Ui {
class WidgetViewer;
}
class File;
class Document;

class WidgetViewer : public QWidget
{
    Q_OBJECT
    
public:
    explicit WidgetViewer(QWidget *parent = 0);
    ~WidgetViewer();

    void setFile(File * file) { this->_file = file; this->initDocument(); }
    
protected:
    void paintEvent(QPaintEvent * event);

private:
    void initDocument();

    Ui::WidgetViewer *ui;

    File* _file;
    Document* _document;

};

#endif // WIDGETVIEWER_H
