#include "file.h"
#include "builder.h"
#include "viewer.h"
#include "widgettextedit.h"
#include <QFile>
#include <QFileDialog>
#include <QTextStream>
#include <QTextCodec>

File::File(WidgetTextEdit* widgetTextEdit,QString filename) :
    filename(filename),
    builder(new Builder(this)),
    viewer(new Viewer(this)),
    _widgetTextEdit(widgetTextEdit),
    _codec(QTextCodec::codecForLocale()->name()),
    _modified(false)
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
    out.setCodec(_codec.toLatin1());
    //out.setGenerateByteOrderMark(true);
    out << this->data;

    _modified = false;
}

const QString& File::open(QString filename, QString codec)
{
    // Get the filename

    if(filename.isEmpty())
    {
        if(this->filename.isEmpty())
        {

            //this->filename = QFileDialog::getOpenFileName(this->_parent,tr("Ouvrir un fichier"));
            if(this->filename.isEmpty())
            {
                return "";
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
        return "";

    this->data = QString("");

    QTextStream in(&file);
    if(codec.isEmpty())
    {
        in.setCodec("UTF-8");
    }
    else
    {
        in.setCodec(codec.toLatin1());
    }

    while (!in.atEnd()) {
        data.append(in.readLine()+"\n");
    }
    if(codec.isEmpty() && data.contains(QString::fromUtf8("�")))
    {
        this->open(this->filename,"ISO 8859-1");
        return "";
    }
    this->_codec = in.codec()->name();
    this->_widgetTextEdit->setText(this->data);
    this->refreshLineNumber();
    _modified = false;
    return this->data;

}

void File::refreshLineNumber()
{
    int lineNumber = this->_widgetTextEdit->document()->blockCount();
    //qDebug()<<"refreshLineNumber "<<lineNumber;
    _lineNumberSinceLastBuild.clear();
    for(int idx = 0; idx < lineNumber; ++idx)
    {
        _lineNumberSinceLastBuild.insert(idx,idx);
    }
}
void File::insertLine(int lineNumber, int lineCount)
{
    //qDebug()<<"insertLine "<<lineNumber<<" : "<<lineCount;
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


