/***************************************************************************
 *   copyright       : (C) 2013 by Quentin BRAMAS                          *
 *   http://www.simtex.fr                                                  *
 *                                                                         *
 *   This file is part of SimTex.                                          *
 *                                                                         *
 *   SimTex is free software: you can redistribute it and/or modify        *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation, either version 3 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   SimTex is distributed in the hope that it will be useful,             *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with SimTex.  If not, see <http://www.gnu.org/licenses/>.       *                         *
 *                                                                         *
 ***************************************************************************/

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
    if(this->file->getFilename().isEmpty())
    {
        return;
    }
    emit started();
    _lastOutput = QString("");
    _simpleOutPut.clear();
    _basename = this->file->fileInfo().baseName();

    QString command = "pdflatex -output-directory=\""+this->file->getPath()+"\" -aux-directory="+this->file->getAuxPath()+" -synctex=1 -shell-escape -interaction=nonstopmode -enable-write18 \""+this->file->getFilename()+"\"";

    if(this->process->state() != QProcess::NotRunning)
    {
        this->process->kill();
    }
    qDebug()<<command;
    process->start(command);
}

void Builder::bibtex()
{
    if(this->file->getFilename().isEmpty())
    {
        return;
    }
    emit started();
    _lastOutput = QString("");
    _simpleOutPut.clear();
    _basename = this->file->fileInfo().baseName();
    qDebug()<<"bibtex --include-directory=\""+this->file->getPath()+"\" \""+this->file->getAuxPath()+"/"+_basename+"\"";
    process->start("bibtex --include-directory=\""+this->file->getPath()+"\" \""+this->file->getAuxPath()+"/"+_basename+"\"");
}
void Builder::onFinished(int /*exitCode*/, QProcess::ExitStatus /*exitStatus*/)
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
    if(_lastOutput.indexOf("Output written on ") != -1)
    {
        _simpleOutPut << "Output written on \""+this->_basename+".pdf\"";
        return true;
    }
    if(_lastOutput.indexOf("Database file ") != -1)
    {
        _simpleOutPut << "Success";
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
