#include "builder.h"
#include "file.h"
#include <QProcess>

Builder::Builder(File * file) :
    file(file)
{

}

void Builder::pdflatex()
{
    QProcess * process = new QProcess();
    process->start("pdflatex -synctex=1 -shell-escape -interaction=nonstopmode -enable-write18 "+this->file->getFilename());
}
