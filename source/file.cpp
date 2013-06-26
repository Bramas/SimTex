#include "file.h"
#include "builder.h"
#include "viewer.h"
#include "widgettextedit.h"
#include <QFile>
#include <QFileDialog>
#include <QTextStream>

File::File(WidgetTextEdit* widgetTextEdit,QString filename) :
    filename(filename),
    builder(new Builder(this)),
    viewer(new Viewer(this)),
    _widgetTextEdit(widgetTextEdit)
{
}
void File::save(QString filename)
{
    //Check the filename
    if(!filename.isEmpty())
    {
        this->filename = filename;
    }
    if(this->filename.isEmpty())
    {
        return;
    }

    if(_modified)
    {
        this->data = this->_widgetTextEdit->toPlainText();
    }

    // Save
    QFile file(this->filename);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        return;

    QTextStream out(&file);
    out.setCodec("UTF-8");
    //out.setGenerateByteOrderMark(true);
    out << this->data;

    _modified = false;
}

void File::open(QString filename)
{
    // Get the filename

    if(filename.isEmpty())
    {
        if(this->filename.isEmpty())
        {

            //this->filename = QFileDialog::getOpenFileName(this->_parent,tr("Ouvrir un fichier"));
            if(this->filename.isEmpty())
            {
                return;
            }
        }
    }
    else
    {
        this->filename = filename;
    }
    // Open the file

    QFile file(this->filename);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    this->data = QString("");

    QTextStream in(&file);
    while (!in.atEnd()) {
        data.append(in.readLine()+"\n");
    }
    _modified = false;

}

void File::refreshLineNumber()
{
    int lineNumber = this->_widgetTextEdit->document()->blockCount();
    _lineNumberSinceLastBuild.clear();
    for(int idx = 0; idx < lineNumber; ++idx)
    {
        _lineNumberSinceLastBuild.insert(idx,idx);
    }
}
void File::insertLine(int lineNumber, int lineCount)
{
    for(int idx = lineNumber; idx < _lineNumberSinceLastBuild.size(); ++idx)
    {
        _lineNumberSinceLastBuild.insert(idx,_lineNumberSinceLastBuild.value(idx) - lineCount);
    }

    for(int idx = 0; idx < lineCount; ++idx)
    {
        _lineNumberSinceLastBuild.insert(_lineNumberSinceLastBuild.size(),_lineNumberSinceLastBuild.value(_lineNumberSinceLastBuild.size()-1)+1);
    }
    for(int idx = 0; idx > lineCount; --idx)
    {
        _lineNumberSinceLastBuild.remove(_lineNumberSinceLastBuild.size()-1);
    }
}
