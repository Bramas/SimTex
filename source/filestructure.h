#ifndef FILESTRUCTURE_H
#define FILESTRUCTURE_H

#include <QObject>

class QList<class T>;
class WidgetTextEdit;

struct FileStructureInfo
{
    QString name;
    int startBlock;
    int endBlock;
    int level;
    int top=0;
    int height=0;
};

struct BlockIndentation
{
    int next;
    int level;
};


class FileStructure : public QObject
{
    Q_OBJECT
public:
    explicit FileStructure(WidgetTextEdit *parent = 0);
    QList<FileStructureInfo*> * info() { return this->structureInfo; }
    BlockIndentation *  indentations() { return this->blockIndentations; }

signals:
    
public slots:
    void updateStructure(void);
    
private:
    QList<FileStructureInfo*> * structureInfo;
    BlockIndentation * blockIndentations;

    WidgetTextEdit * widgetTextEdit;
};

#endif // FILESTRUCTURE_H
