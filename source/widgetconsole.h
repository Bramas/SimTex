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

#ifndef WIDGETCONSOLE_H
#define WIDGETCONSOLE_H

#include <QScrollArea>
#include <QPlainTextEdit>

class Builder;

class WidgetConsole : public QPlainTextEdit
{
    Q_OBJECT
public:
    explicit WidgetConsole();

    void setBuilder(Builder * builder);
    
signals:
    void requestLine(int);
public slots:
    void expand(void);
    void collapsed(void);
    void onError(void);
    void onSuccess(void);

protected:
    //void paintEvent(QPaintEvent *);
    void mouseMoveEvent(QMouseEvent * event);
    void mousePressEvent(QMouseEvent * event);

private:
    bool _collapsed;
    int _height;
    Builder * _builder;
    //QPlainTextEdit * _mainWidget;
    
};

#endif // WIDGETCONSOLE_H
