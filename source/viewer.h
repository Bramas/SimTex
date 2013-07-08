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

#ifndef VIEWER_H
#define VIEWER_H
#include <QObject>
#include <QProcess>

class File;


class Viewer : public QObject
{
    Q_OBJECT
public:
    Viewer(File * file);
    void setLine(int line) { this->currentLine = line; }

public slots:
    void view(QString s="");
    void onFinished(int, QProcess::ExitStatus exitStatus);

signals:
    void finished(void);

private:

    QProcess * process;
    File * file;
    int currentLine;
};

#endif // VIEWER_H
