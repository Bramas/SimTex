#include "builder.h"
#include "file.h"
#include <QDebug>

Builder::Builder(File * file) :
    file(file),
    process(new QProcess())
{
    connect(this->process,SIGNAL(finished(int,QProcess::ExitStatus)), this, SLOT(onFinished(int,QProcess::ExitStatus)));
    connect(this->process,SIGNAL(readyReadStandardOutput()), this, SLOT(onStandartOutputReady()));
}

void Builder::pdflatex()
{
    this->file->save();
    emit started();
    _lastOutput = QString("");
    _simpleOutPut.clear();
    _basename = this->file->fileInfo().baseName();
    qDebug()<<"pdflatex -aux-directory=\""+this->file->getAuxPath()+"\" -synctex=1 -shell-escape -interaction=nonstopmode -enable-write18 \""+this->file->getFilename()+"\"";
    process->start("pdflatex -output-directory=\""+this->file->getPath()+"\" -aux-directory="+this->file->getAuxPath()+" -synctex=1 -shell-escape -interaction=nonstopmode -enable-write18 \""+this->file->getFilename()+"\"");
}

void Builder::onFinished(int exitCode, QProcess::ExitStatus exitStatus)
{
    //qDebug()<<_lastOutput;
    this->file->refreshLineNumber();
    if(!checkOutput())
    {
        emit error();
        emit statusChanged(QString::fromUtf8("Terminé avec des erreurs"));
        return;
    }
    emit statusChanged(QString::fromUtf8("Terminé avec succés"));
    emit success();
    emit pdfChanged();
}
void Builder::onStandartOutputReady()
{
    QString output = this->process->readAllStandardOutput();
    _lastOutput.append(output);
    emit outputReady(output);
}

bool Builder::checkOutput()
{
    int index;
    if(index = _lastOutput.indexOf("Output written on ") != -1)
    {
        _simpleOutPut << "Output written on \""+this->_basename+".pdf\"";
        return true;
    }

    QStringList lines = _lastOutput.split('\n');
    bool errorState = false;
    bool firsLineError = true;

    foreach(const QString &line, lines)
    {
        if(!errorState && line.length() && line.at(0) == QChar('!'))
        {
            _simpleOutPut<<"\n"+line;
            errorState = true;
            firsLineError = true;
        }
        else
        if(errorState)
        {
            if(firsLineError)
            {
                _simpleOutPut.last().append(line);
            }
            if(!line.length())
            {
                firsLineError = false;
            }
            else
            if(line.at(0) == QChar('l'))
            {
                _simpleOutPut.last().append("\n"+line);
                errorState = false;
            }
        }
    }

    return false;
}
