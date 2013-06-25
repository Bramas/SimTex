#include "document.h"

Document::Document(QString filename):
    _document(Poppler::Document::load(filename))
{

    if (!_document || _document->isLocked()) {
      delete _document;
        _document = 0;
      return;
    }
}
QImage Document::image(int page)
{
    return QImage();
   /* if(!_document)
    {
        return QImage();
    }

    Poppler::Page* pdfPage = _document->page(0);
    if (pdfPage == 0) {
        return QImage();
    }
    return pdfPage->renderToImage(500, 500, 0, 0, 500, 500);*/
}
