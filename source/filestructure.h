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

#ifndef FILESTRUCTURE_H
#define FILESTRUCTURE_H

#include <QObject>

class QList<class T>;
class WidgetTextEdit;

struct FileStructureInfo
{
    QString name;
    int startBlock;
    int endBlock;
    int level;
    int top;
    int height;

    FileStructureInfo() : top(0), height(0) {}
};

struct BlockIndentation
{
    int next;
    int level;
};


class FileStructure : public QObject
{
    Q_OBJECT
public:
    explicit FileStructure(WidgetTextEdit *parent = 0);
    QList<FileStructureInfo*> * info() { return this->structureInfo; }
    BlockIndentation *  indentations() { return this->blockIndentations; }

signals:
    
public slots:
    void updateStructure(void);
    
private:
    BlockIndentation * blockIndentations;
    QList<FileStructureInfo*> * structureInfo;
    WidgetTextEdit * widgetTextEdit;
};

#endif // FILESTRUCTURE_H
