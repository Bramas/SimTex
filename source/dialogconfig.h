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

#ifndef DIALOGCONFIG_H
#define DIALOGCONFIG_H

#include <QDialog>
#include <QSettings>
#include <QList>

namespace Ui {
class DialogConfig;
}
class QListWidgetItem;
class MainWindow;

class DialogConfig : public QDialog
{
    Q_OBJECT
    
public:
    explicit DialogConfig(MainWindow * parent = 0);
    void addEditableActions(const QList<QAction *> & actions);
    ~DialogConfig();
public slots:
    void save(void);
    void saveAndClose(void);
    void show();
    void changePage(int currentRow);
    
private:
    QList<QAction*> _actionsList;
    Ui::DialogConfig *ui;
    QSettings settings;
    MainWindow * _parent;
};

#endif // DIALOGCONFIG_H
