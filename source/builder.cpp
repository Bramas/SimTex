#include "builder.h"
#include "file.h"
#include <QDebug>

Builder::Builder(File * file) :
    file(file),
    process(new QProcess())
{
    connect(this->process,SIGNAL(finished(int,QProcess::ExitStatus)), this, SLOT(onFinished(int,QProcess::ExitStatus)));
}

void Builder::pdflatex()
{
    qDebug()<<"pdflatex -aux-directory="+this->file->getAuxPath()+" -synctex=1 -shell-escape -interaction=nonstopmode -enable-write18 "+this->file->getFilename();
    process->start("pdflatex -output-directory="+this->file->getPath()+" -aux-directory="+this->file->getAuxPath()+" -synctex=1 -shell-escape -interaction=nonstopmode -enable-write18 "+this->file->getFilename());
}

void Builder::onFinished(int exitCode, QProcess::ExitStatus exitStatus)
{
    emit statusChanged("Terminé");
}
