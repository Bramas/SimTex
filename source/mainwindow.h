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

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class QMimeData;
class WidgetTextEdit;
class WidgetLineNumber;
class WidgetScroller;
class WidgetPdfViewer;
class WidgetConsole;
class DialogWelcome;
class DialogConfig;
class QVBoxLayout;
class SyntaxHighlighter;
class WidgetFindReplace;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    bool closeCurrentFile();
    ~MainWindow();

public slots:

    void newFile(void);
    void save(void);
    void saveAs(void);
    void open(QString filename = "");
    void openLast(void);
    void clearLastOpened(void);
    void focus(void);
    void changeTheme(void);
    void openFindReplaceWidget(void);
    void closeFindReplaceWidget(void);
protected:
    void mousePressEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent *);
    void closeEvent(QCloseEvent *);
    
private:
    Ui::MainWindow *ui;
    void initTheme();

    WidgetLineNumber * widgetLineNumber;
    WidgetTextEdit * widgetTextEdit;
    WidgetScroller * widgetScroller;
    WidgetPdfViewer * _widgetPdfViewer;
    WidgetConsole * _widgetConsole;
    WidgetFindReplace * _widgetFindReplace;
    DialogWelcome * dialogWelcome;
    DialogConfig * dialogConfig;
    QVBoxLayout * _leftLayout;
    SyntaxHighlighter * _syntaxHighlighter;
    int _editorWidth;
    bool _mousePressed;
    bool _resizeConsole;
};

#endif // MAINWINDOW_H
