#include "viewer.h"
#include "file.h"
#include <QDebug>
#include "poppler/poppler-qt4.h"

Viewer::Viewer(File * file) :
    file(file),
    process(new QProcess)
{
    connect(this->process, SIGNAL(finished(int,QProcess::ExitStatus)), this, SLOT(onFinished(int,QProcess::ExitStatus)));
}

void Viewer::view(QString)
{
    process->start("sumatrapdf "+this->file->getFilename().replace(QRegExp("(.*)\.tex$"),"\\1.pdf")+" -reuse-instance -forward-search "+this->file->getFilename()+" "+QString::number(this->currentLine));
    qDebug()<<"sumatrapdf -reuse-instance -forward-search "+this->file->getFilename()+" "+QString::number(this->currentLine);
}

void Viewer::onFinished(int exitCode, QProcess::ExitStatus exitStatus)
{
    emit finished();
}
