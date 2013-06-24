#include "file.h"
#include "builder.h"
#include <QFile>
#include <QFileDialog>
#include <QTextStream>

File::File(QString filename) :
    filename(filename),
    builder(new Builder(this))
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

    // Save
    QFile file(this->filename);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        return;

    QTextStream out(&file);
    out.setCodec("UTF-8");
    //out.setGenerateByteOrderMark(true);
    out << this->data;
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
}

