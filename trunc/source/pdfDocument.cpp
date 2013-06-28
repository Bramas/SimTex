#include "pdfdocument.h"
#include <QDebug>


PdfDocument::PdfDocument()
{
    //qDebug()<<Poppler::Document::

/*
    this->_document = Poppler::Document::load("G:/Projects/test.pdf");

    if (!_document || _document->isLocked()) {
      delete _document;
        _document = 0;
      return;
    }
    this->_document->setRenderHint(Poppler::Document::TextAntialiasing);
    this->_document->setRenderHint(Poppler::Document::Antialiasing);
*/

}

QImage PdfDocument::image(int page)
{
   // if(!_document)
    {
        return QImage();
    }
/*
    Poppler::Page* pdfPage = _document->page(page);
    if (pdfPage == 0) {
        return QImage();
    }
    return pdfPage->renderToImage(72,72);
    // */
}
