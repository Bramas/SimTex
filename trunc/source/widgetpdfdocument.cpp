#include "widgetpdfdocument.h"
#include "widgettextedit.h"
#include <QMouseEvent>
#include <QDebug>
#include <QPainter>
#include <QBrush>
#include <QColor>
#include "file.h"
#define SYNCTEX_GZ_EXT ".synctex.gz"
#define SYNCTEX_EXT ".synctex"
#define max(a,b) ((a)>(b)?(a):(b))
#define min(a,b) ((a)<(b)?(a):(b))

QImage * WidgetPdfDocument::EmptyImage = new QImage();
int WidgetPdfDocument::PageMargin = 20;

WidgetPdfDocument::WidgetPdfDocument(QWidget *parent) :
    QWidget(parent),
    _widgetTextEdit(0),
    _document(0),
    _file(0),
    _mousePressed(false),
    _loadedPages(0),
    _pages(0),
    _zoom(1)

{
    this->setMouseTracking(true);
    this->setCursor(Qt::OpenHandCursor);
    connect(&this->_timer, SIGNAL(timeout()),this, SLOT(update()));
}

void WidgetPdfDocument::paintEvent(QPaintEvent *)
{
    if(!this->_document)
    {
        return;
    }
    QPainter painter(this);
    painter.translate(this->_painterTranslate);
    painter.setBrush(QBrush(QColor(0,0,0,50)));
    painter.setPen(QPen(QColor(0,0,0,0)));
    QImage * image;
    int cumulatedTop=0;
    for(int i = 0; i < this->_document->numPages(); ++i)
    {
        if(cumulatedTop + _document->page(i)->pageSize().height()*_zoom < -this->_painterTranslate.y())
        {
            //qDebug()<<cumulatedTop<<","<<_document->page(i)->pageSize().height();
            cumulatedTop += _document->page(i)->pageSize().height()*_zoom+WidgetPdfDocument::PageMargin;
            continue;
        }
        image = this->page(i);
        painter.drawImage(0,cumulatedTop,*image);
        if(i == _syncPage+1)
        {
            if(_lastUpdate.elapsed()<1200)
            {
                painter.drawRect(0, cumulatedTop, this->width()*_zoom+1, this->height());
            }
        }
        if(i == _syncPage)
        {
            if(_lastUpdate.elapsed()<1200)
            {
                painter.setBrush(QBrush(QColor(0,0,0,min(50,(750-_lastUpdate.elapsed())*(2250-_lastUpdate.elapsed())*50/(750*750) + 50))));
                //qDebug()<<"t "<<_lastUpdate.elapsed();
                painter.drawRect(0, cumulatedTop - this->height(), this->width()*_zoom+1, this->height() + _syncRect.y() * _zoom);
                painter.drawRect(0, _syncRect.y()*_zoom + cumulatedTop + _syncRect.height()*_zoom, this->width()*_zoom+1, this->height());
                //painter.drawRect(_syncRect.x()*_zoom, _syncRect.y()*_zoom + cumulatedTop, _syncRect.width()*_zoom, _syncRect.height()*_zoom);
            }
            else
            {
                this->_timer.stop();
            }
            //painter.drawLine(_syncRect.x()*_zoom-50,_syncRect.y()*_zoom + cumulatedTop,_syncRect.x()*_zoom-20,_syncRect.y()*_zoom + cumulatedTop);
            //painter.drawLine(_syncRect.x()*_zoom-50,_syncRect.y()*_zoom + cumulatedTop,_syncRect.x()*_zoom-50,_syncRect.y()*_zoom + 20 + cumulatedTop);
        }
        cumulatedTop += _document->page(i)->pageSize().height()*_zoom+WidgetPdfDocument::PageMargin;
        if(cumulatedTop > this->height() - this->_painterTranslate.y())
        {
            break;
        }
    }


}

void WidgetPdfDocument::initDocument()
{
    if(!_file)
    {
        return;
    }
    if(_document)
    {
        delete _document;
    }

    _document = Poppler::Document::load(_file->getPdfFilename());//PdfDocument::load(_file->getFilename());//new PdfDocument(_file->getFilename());

    if(!_document || _document->isLocked())
    {
        delete _document;
        _document = 0;
        return;
    }

    _document->setRenderHint(Poppler::Document::Antialiasing);
    _document->setRenderHint(Poppler::Document::TextAntialiasing);

    if(_pages)
    {
        this->refreshPages();
        delete _pages;
    }
    _pages = new QImage*[_document->numPages()];

    if(_loadedPages)
    {
        delete _loadedPages;
    }
    _loadedPages = new bool[_document->numPages()];
    for(int idx = 0; idx < _document->numPages(); ++idx)
    {
        _loadedPages[idx] = false;
    }

    QString syncFile = QFileInfo(this->_file->getFilename()).canonicalFilePath();
    scanner = synctex_scanner_new_with_output_file(syncFile.toUtf8().data(), NULL, 1);


    jumpToPdfFromSource(_file->getFilename(),_widgetTextEdit->textCursor().blockNumber());
}
QImage * WidgetPdfDocument::page(int page)
{
    if(!_pages || page < 0 || page >= _document->numPages())
    {
        return WidgetPdfDocument::EmptyImage;
    }
    if(_loadedPages[page])
    {
        return _pages[page];
    }
    _loadedPages[page] = true;
    return  _pages[page] = new QImage(this->_document->page(page)->renderToImage(this->_zoom*72.0,this->_zoom*72.0));

}
void WidgetPdfDocument::goToPage(int page, int top, int height)
{
    if(!_file) return;

    page = min(page,this->_document->numPages()-1);

    int cumulatedTop = 0;
    int i = 0;
    for(i = 0; i < page; ++i)
    {
        cumulatedTop += _document->page(i)->pageSize().height()*_zoom+WidgetPdfDocument::PageMargin;
    }
    //qDebug()<<(this->height());
    //qDebug()<<(-this->_painterTranslate.y() + this->height())<<"  <  "<<(cumulatedTop + height * _zoom)<<" | "<<(-this->_painterTranslate.y())<<" > "<<cumulatedTop + top ;
    if(-this->_painterTranslate.y() + this->height() < cumulatedTop + top*_zoom + height * _zoom || -this->_painterTranslate.y() > cumulatedTop + top*_zoom )
    {
        this->_painterTranslate.setY(-cumulatedTop-top*_zoom-height*_zoom/2+this->height()/2);
    }
    update();
}

void WidgetPdfDocument::refreshPages()
{
    for(int idx = 0; idx < this->_document->numPages(); ++idx)
    {
        if(_loadedPages[idx])
        {
            delete _pages[idx];
            _loadedPages[idx] = false;
        }
    }

}

void WidgetPdfDocument::mousePressEvent(QMouseEvent * event)
{
    this->_pressAt = event->pos();
    this->_painterTranslateWhenMousePressed = this->_painterTranslate;
    this->_mousePressed = true;
    this->setCursor(Qt::ClosedHandCursor);
}
void WidgetPdfDocument::mouseReleaseEvent(QMouseEvent * event)
{
    this->_mousePressed = false;
    this->setCursor(Qt::OpenHandCursor);
    update();
}
void WidgetPdfDocument::wheelEvent(QWheelEvent * event)
{
    if(event->modifiers() & (Qt::ControlModifier | Qt::AltModifier | Qt::ShiftModifier))
    {
        qreal factor =  event->delta() > 0 ? 1.1 : 0.90;
        this->zoom(factor, event->pos());
    }
    else
    {
       this->_painterTranslate.setY(this->_painterTranslate.y()+event->delta());
        update();
    }
}
void WidgetPdfDocument::zoom(qreal factor, QPoint target)
{
    this->_zoom *= factor;
    this->_painterTranslate *= factor;
    this->_painterTranslate += target - target*factor;
    this->boundPainterTranslation();
    this->refreshPages();
    update();
}
void WidgetPdfDocument::zoomIn()
{
    this->zoom(1.1);
}

void WidgetPdfDocument::zoomOut()
{
    this->zoom(0.9);
}

void WidgetPdfDocument::mouseMoveEvent(QMouseEvent * event)
{
    if(this->_mousePressed)
    {
        this->_painterTranslate = this->_painterTranslateWhenMousePressed + (event->pos() - this->_pressAt);
        this->boundPainterTranslation();
        update();
    }
}
void WidgetPdfDocument::boundPainterTranslation()
{
    if(!this->_document || !this->_document->numPages())
    {
        return;
    }
    this->_painterTranslate.setX(max(this->_painterTranslate.x(), this->width()-this->_document->page(0)->pageSize().width()*_zoom - 10));
    this->_painterTranslate.setX(min(this->_painterTranslate.x(), 10));
    if(this->_document->page(0)->pageSize().width()*_zoom - 20 < this->width())
    {
        this->_painterTranslate.setX(-this->_document->page(0)->pageSize().width()*_zoom/2+this->width()/2);
    }
}

void WidgetPdfDocument::updatePdf()
{
    this->initDocument();

    update();
}

void WidgetPdfDocument::jumpToPdfFromSourceView(int firstVisibleBlock, int i)
{
    if(!this->_widgetTextEdit->isCursorVisible())
    {
        this->jumpToPdfFromSource(this->_file->getFilename(),firstVisibleBlock);
    }
}

void WidgetPdfDocument::jumpToPdfFromSource(QString sourceFile, int source_line)
{
    if (!_file) return;

    if (scanner == NULL)
    {
      return;
    }

    source_line = this->_file->getBuildedLine(source_line);

    const QFileInfo sourceFileInfo(sourceFile);
    QDir curDir(QFileInfo(this->_file->getPdfFilename()).canonicalPath());
    synctex_node_t node = synctex_scanner_input(scanner);
    QString name;
    bool found = false;
    while (node != NULL)
    {
        name = QString::fromUtf8(synctex_scanner_get_name(scanner, synctex_node_tag(node)));
        const QFileInfo fi(curDir, name);
        if (fi == sourceFileInfo)
        {
            found = true;
            break;
        }
        node = synctex_node_sibling(node);
    }
    if (!found)
    {
        return;
    }

    if (synctex_display_query(scanner, name.toUtf8().data(), source_line, 0) > 0)
    {
        int page = -1;
        path= QPainterPath();
        while ((node = synctex_next_result(scanner)) != NULL)
        {
            if (page == -1) page = synctex_node_page(node);
            if (synctex_node_page(node) != page) continue;
            QRectF nodeRect(synctex_node_box_visible_h(node),
                            synctex_node_box_visible_v(node) - synctex_node_box_visible_height(node),
                            synctex_node_box_visible_width(node),
                            synctex_node_box_visible_height(node) + synctex_node_box_visible_depth(node));
            path.addRect(nodeRect);
        }
        if (page > 0)
        {

            //disconnect(pdfview, SIGNAL(currentPageChanged(int)), this, SLOT(checkPage(int)));

            _syncPage = page - 1;
            _syncRect = path.boundingRect();
            goToPage(_syncPage, _syncRect.y(), _syncRect.height());
            _lastUpdate.start();
            _timer.start(1);
            /*
            currentPage=page;
            lastPage=currentPage;
            pdfview->showRect(currentPage-1,r);
            path.setFillRule(Qt::WindingFill);
            QTimer::singleShot(500,this, SLOT(slotHighlight()) );
            updateCurrentPage();
            connect(pdfview, SIGNAL(currentPageChanged(int)), this, SLOT(checkPage(int)));*/
        }
    }
}
