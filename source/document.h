#ifndef DOCUMENT_H
#define DOCUMENT_H

#include <QImage>
#include <poppler-qt4.h>

class Document
{
public:
    Document(QString filename);
    QImage image(int page);

private:
    Poppler::Document* _document;
};

#endif // DOCUMENT_H
