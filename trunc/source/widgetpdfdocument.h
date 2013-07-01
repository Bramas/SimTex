#ifndef WIDGETPDFDOCUMENT_H
#define WIDGETPDFDOCUMENT_H

#include <QWidget>
#include <QPoint>
#include <QElapsedTimer>
#include <QTimer>
#include <QList>
#include <QRectF>

#include "synctex_parser.h"
#include <QPoint>
#if linux
    #include <poppler/qt4/poppler-qt4.h>
#else
    #include <poppler-qt4.h>
#endif

class File;
class QImage;
class WidgetTextEdit;

struct Link
{
    QRectF rectangle;
    Poppler::LinkDestination * destination;

    ~Link()
    {
        //delete destination;
    }
};


class WidgetPdfDocument : public QWidget
{
    Q_OBJECT
public:
    explicit WidgetPdfDocument(QWidget *parent = 0);
    void setFile(File * file) { this->_file = file; this->initDocument(); }
    void setWidgetTextEdit(WidgetTextEdit * widgetTextEdit) { this->_widgetTextEdit = widgetTextEdit; }
    void goToPage(int page, int top=0, int height=0);
signals:
    
public slots:
    void jumpToPdfFromSourceView(int firstVisibleBlock, int);
    void jumpToPdfFromSource(QString sourceFile, int source_line);
    void zoomIn();
    void zoomOut();
    void zoom(qreal factor, QPoint target = QPoint(0,0));
    void updatePdf(void);

protected:
    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent *);
    void wheelEvent(QWheelEvent *);
private:
    void initDocument();
    void initLinks();
    void boundPainterTranslation();
    QImage * page(int page);
    void refreshPages();
    void checkLinksOver(const QPointF &pos);
    bool checkLinksPress(const QPointF &pos);

    QElapsedTimer _lastUpdate;
    QTimer _timer;

    WidgetTextEdit * _widgetTextEdit;
    File* _file;
    Poppler::Document* _document;
    QPoint _pressAt;
    QPoint _painterTranslateWhenMousePressed;
    QPoint _painterTranslate;
    bool _mousePressed;
    qreal _zoom;

    QImage ** _pages;
    bool * _loadedPages;
    QPainterPath path;

    QRectF _syncRect;
    int _syncPage;

    synctex_scanner_t scanner;

    QList<Link> _links;

    static QImage * EmptyImage;
    static int PageMargin;
};

#endif // WIDGETPDFDOCUMENT_H
