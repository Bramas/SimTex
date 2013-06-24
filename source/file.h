#ifndef FILE_H
#define FILE_H

#include <QString>
#include <QDir>
#include <QDebug>
#include <QRegExp>

class Viewer;
class Builder;

class File
{
public:
    explicit File(QString filename = "");

    QString getData() { return this->data; }
    void setData(QString data) { this->data = data; }

    void open(QString filename = "");
    void save(QString filename = "");

    QString getFilename() { return this->filename; }
    QString getPath() { QString s(this->filename); return s.replace(QRegExp("^(([^\\\\\\/]*[\\\\\\/])*)[^\\\\\\/]*$"),"\\1"); }
    QString getAuxPath() {
        QDir dir;
        if(!dir.exists(this->getPath()+".simtex"))
        {
            dir.mkpath( this->getPath()+".simtex");
        }
        return this->getPath()+".simtex";//+dir.separator();
    }

    Builder * getBuilder() { return this->builder; }
    Viewer * getViewer() { return this->viewer; }

private:
    QString filename;
    QString data;
    Builder * builder;
    Viewer * viewer;
    
};

#endif // FILE_H
