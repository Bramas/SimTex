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

#ifndef WIDGETLINENUMBER_H
#define WIDGETLINENUMBER_H

#include <QWidget>
class WidgetTextEdit;

class WidgetLineNumber : public QWidget
{
    Q_OBJECT
public:
    explicit WidgetLineNumber(QWidget *parent);
    void setWidgetTextEdit(WidgetTextEdit * widgetTextEdit);
signals:
    
public slots:
    void updateFirstVisibleBlock(int, int);
    void setBlockRange(int,int);
    void updateWidth(int lineCount);

private:
    void paintEvent(QPaintEvent * event);
    
    WidgetTextEdit * widgetTextEdit;
    int scrollOffset;
    int firstVisibleBlock;
    int firstVisibleBlockTop;
    int _startBlock;
    int _endBlock;
};

#endif // WIDGETLINENUMBER_H
