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

#include "filestructure.h"
#include "widgettextedit.h"
#include <QList>
#include <QTextBlock>

FileStructure::FileStructure(WidgetTextEdit *parent) :
    blockIndentations(new BlockIndentation[0]),
    structureInfo(new QList<FileStructureInfo*>()),
    widgetTextEdit(parent)
{

}

void FileStructure::updateStructure()
{
    // clean memory
    foreach(FileStructureInfo * in,*this->structureInfo)
    {
        delete in;
    }
    this->structureInfo->clear();
    delete this->blockIndentations;
    this->blockIndentations = new BlockIndentation[this->widgetTextEdit->document()->blockCount()];

    int textBlockIndex = 0;
    FileStructureInfo * stru;
    int lastLevel[3];
    lastLevel[0] = lastLevel[1] = lastLevel[2] = -1;
    int level = 0;
    int lastBlock=0;
    QTextBlock textBlock = this->widgetTextEdit->document()->begin();
    bool first = true;
    do{

        if(textBlock.text().indexOf(QRegExp("\\\\(sub){0,2}section\\{[^\\}]*\\}"), 0) != -1 ||
                textBlock.text().indexOf(QRegExp("\\\\begin\\{thebibliography\\}"), 0) != -1)
        {
            for(int i = lastBlock; i < textBlockIndex; ++i)
            {
                this->blockIndentations[i].level = level;
                this->blockIndentations[i].next = textBlockIndex;
            }
            level = textBlock.text().indexOf(QRegExp("\\\\subsubsection\\{[^\\}]*\\}"), 0) != -1 ? 3 : textBlock.text().indexOf(QRegExp("\\\\subsection\\{[^\\}]*\\}"), 0) != -1 ? 2 : 1;
            for(int i = level; i <= 3; ++i)
            {
                if(lastLevel[i - 1] != -1)
                {
                    this->structureInfo->at(lastLevel[i - 1])->endBlock = textBlockIndex - 1;
                    lastLevel[i - 1] = -1;
                }
            }
            lastBlock = textBlockIndex;
            lastLevel[level - 1] = this->structureInfo->count();
            first = false;
            QString s = textBlock.text();
            stru = new FileStructureInfo;
            stru->startBlock = textBlockIndex;
            stru->endBlock = this->widgetTextEdit->document()->blockCount() - 1;
            stru->name = textBlock.text().indexOf(QRegExp("\\\\(sub){0,2}section\\{[^\\}]*\\}"), 0) != -1 ? s.replace(QRegExp(".*\\\\(sub){0,2}section\\{([^\\}]*)\\}.*"), "\\2") : "Bibliography";
            stru->level = level;
            this->structureInfo->append(stru);
        }
        textBlock = textBlock.next();
        ++textBlockIndex;
    }while(textBlockIndex < this->widgetTextEdit->document()->blockCount());

    for(int i = lastBlock; i < this->widgetTextEdit->document()->blockCount(); ++i)
    {
        this->blockIndentations[i].level = level;
        this->blockIndentations[i].next = this->widgetTextEdit->document()->blockCount();
    }

    return;

    first = true;
    textBlockIndex = 0;
    textBlock = this->widgetTextEdit->document()->begin();
    do{
        if(textBlock.text().indexOf(QRegExp("\\\\subsection\\{[^\\}]*\\}"), 0) != -1)
        {
            if(!first)
            {
                this->structureInfo->last()->endBlock = textBlockIndex-1;
            }
            level = 2;
            first = false;
            QString s = textBlock.text();
            stru = new FileStructureInfo;
            stru->startBlock = textBlockIndex;
            stru->endBlock = this->widgetTextEdit->document()->blockCount() - 1;
            stru->name = s.replace(QRegExp(".*\\\\subsection\\{([^\\}]*)\\}.*"), "\\1");
            stru->level = level;
            this->structureInfo->append(stru);
        }
        textBlock = textBlock.next();
        ++textBlockIndex;
    }while(textBlockIndex < this->widgetTextEdit->document()->blockCount());
    first = true;
    textBlockIndex = 0;
    textBlock = this->widgetTextEdit->document()->begin();
    do{
        if(textBlock.text().indexOf(QRegExp("\\\\subsubsection\\{[^\\}]*\\}"), 0) != -1)
        {
            if(!first)
            {
                this->structureInfo->last()->endBlock = textBlockIndex-1;
            }
            level = 3;
            first = false;
            QString s = textBlock.text();
            stru = new FileStructureInfo;
            stru->startBlock = textBlockIndex;
            stru->endBlock = this->widgetTextEdit->document()->blockCount() - 1;
            stru->name = s.replace(QRegExp(".*\\\\subsubsection\\{([^\\}]*)\\}.*"), "\\1");
            stru->level = level;
            this->structureInfo->append(stru);
        }
        textBlock = textBlock.next();
        ++textBlockIndex;
    }while(textBlockIndex < this->widgetTextEdit->document()->blockCount());
}
