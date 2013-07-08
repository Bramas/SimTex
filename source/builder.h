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

#ifndef BUILDER_H
#define BUILDER_H
#include <QObject>
#include <QString>
#include <QProcess>
#include <QStringList>

class File;

class Builder : public QObject
{
        Q_OBJECT
public:
    Builder(File * file);
    const QStringList & simpleOutput() const { return _simpleOutPut; }
public slots:
    void pdflatex();
    void onFinished(int exitCode,QProcess::ExitStatus exitStatus);
    void onStandartOutputReady();

signals:
    void statusChanged(QString);
    void outputReady(QString);
    void pdfChanged();
    void error();
    void success();
    void started();

private:
    bool checkOutput();
    File * file;
    QString _basename;
    QProcess * process;
    QString _lastOutput;
    QStringList _simpleOutPut;
};

#endif // BUILDER_H
