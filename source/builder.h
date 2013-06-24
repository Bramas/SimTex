#ifndef BUILDER_H
#define BUILDER_H
#include <QObject>
#include <QString>

class File;

class Builder : public QObject
{
        Q_OBJECT
public:
    Builder(File * file);
public slots:
    void pdflatex();

private:
    File * file;
};

#endif // BUILDER_H
