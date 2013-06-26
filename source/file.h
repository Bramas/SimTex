#ifndef FILE_H
#define FILE_H

#include <QObject>
#include <QString>
#include <QDir>
#include <QDebug>
#include <QRegExp>
#include <QMap>

class Viewer;
class Builder;
class WidgetTextEdit;
class File : public QObject
{
    Q_OBJECT
public:
    explicit File(WidgetTextEdit * widgetTextEdit, QString filename = "");

    QString getData() { return this->data; }
    void setData(QString data) { this->data = data; }

    void open(QString filename = "");
    void save(QString filename = "");

    void refreshLineNumber();
    void insertLine(int lineNumber, int lineCount = 1);
    int getBuildedLine(int line) { qDebug()<<"getLine : "<<line<<" : "<<this->_lineNumberSinceLastBuild.value(line,-1); return this->_lineNumberSinceLastBuild.value(line,line); }

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
    QString getPdfFilename(){
        QString s(this->filename); return s.replace(QRegExp("\.tex$"),".pdf");
    }

    Builder * getBuilder() { return this->builder; }
    Viewer * getViewer() { return this->viewer; }

public slots:
    void setModified() { this->_modified = true; }

private:
    QString filename;
    QString data;
    Builder * builder;
    Viewer * viewer;
    WidgetTextEdit * _widgetTextEdit;
    bool _modified;

    QMap<int,int> _lineNumberSinceLastBuild;
};

#endif // FILE_H
