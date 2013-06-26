#ifndef PDF_DOCUMENT_H
#define PDF_DOCUMENT_H

#include <QImage>
#include <poppler-qt4.h>

class PdfDocument
{
public:
    QImage image(int page);

private:
    PdfDocument();//QString filename);
    //Poppler::Document* _document;
};

#endif // PDF_DOCUMENT_H
