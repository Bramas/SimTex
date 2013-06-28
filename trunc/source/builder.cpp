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
    qDebug()<<"pdflatex -aux-directory=\""+this->file->getAuxPath()+"\" -synctex=1 -shell-escape -interaction=nonstopmode -enable-write18 \""+this->file->getFilename()+"\"";
    process->start("pdflatex -output-directory=\""+this->file->getPath()+"\" -aux-directory="+this->file->getAuxPath()+" -synctex=1 -shell-escape -interaction=nonstopmode -enable-write18 \""+this->file->getFilename()+"\"");
}

void Builder::onFinished(int exitCode, QProcess::ExitStatus exitStatus)
{
    qDebug()<<"exit : "<<exitCode<<" existStatus : "<<exitStatus;
    //qDebug()<<"output : "<<this->process->readAllStandardOutput();
    emit statusChanged("Terminé");
    this->file->refreshLineNumber();
    emit error();
    emit pdfChanged();
}
void Builder::onStandartOutputReady()
{

}
