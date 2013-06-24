#ifndef FILE_H
#define FILE_H

#include <QString>
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

    Builder * getBuilder() { return builder; }

private:
    QString filename;
    QString data;
    Builder * builder;
    
};

#endif // FILE_H
