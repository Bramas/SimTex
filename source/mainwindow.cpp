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

#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "widgetlinenumber.h"
#include "widgetpdfviewer.h"
#include "widgettextedit.h"
#include "widgetscroller.h"
#include "syntaxhighlighter.h"
#include "file.h"
#include "builder.h"
#include "dialogwelcome.h"
#include "dialogconfig.h"
#include "viewer.h"
#include "widgetpdfdocument.h"
#include "dialogclose.h"
#include "widgetfindreplace.h"
#include "minisplitter.h"
#include "widgetsimpleoutput.h"

#include <QAction>
#include <QList>
#include <QScrollBar>
#include <QFileDialog>
#include <QVBoxLayout>
#include <QSettings>
#include <QPushButton>
#include <QDebug>
#include <QMimeData>
#include <QString>
#include <QPalette>
#include "configmanager.h"
#include "widgetconsole.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    dialogConfig(new DialogConfig(this)),
    dialogWelcome(new DialogWelcome(this)),
    _leftLayout(new QVBoxLayout()),
    _mainSplitter(new MiniSplitter(Qt::Horizontal)),
    _leftSplitter(new MiniSplitter(Qt::Vertical)),
    _widgetConsole(new WidgetConsole()),
    widgetLineNumber(new WidgetLineNumber(this)),
    _widgetPdfViewer(new WidgetPdfViewer(this)),
    widgetScroller(new WidgetScroller),
    _widgetSimpleOutput(new WidgetSimpleOutput(this)),
    widgetTextEdit(new WidgetTextEdit(this)),
    _mousePressed(false),
    _resizeConsole(false)
{
    ui->setupUi(this);
    ConfigManager::Instance.setMainWindow(this);
    //setWindowFlags(Qt::FramelessWindowHint);
    widgetLineNumber->setWidgetTextEdit(widgetTextEdit);
    widgetScroller->setWidgetTextEdit(widgetTextEdit);
    _widgetSimpleOutput->setWidgetTextEdit(widgetTextEdit);
    _widgetPdfViewer->widgetPdfDocument()->setWidgetTextEdit(widgetTextEdit);
    _syntaxHighlighter = new SyntaxHighlighter(widgetTextEdit);
    widgetTextEdit->setSyntaxHighlighter(_syntaxHighlighter);
    _widgetFindReplace = new WidgetFindReplace(widgetTextEdit);

    // Load settings

    QSettings settings;
    settings.beginGroup("mainwindow");
    if(settings.contains("geometry")) this->setGeometry(settings.value("geometry").toRect());


    //define background
    this->initTheme();

    // Connect things that can update the widgetTextEdit

    connect(widgetTextEdit,SIGNAL(textChanged()),widgetLineNumber,SLOT(update()));
    connect(widgetTextEdit,SIGNAL(setBlockRange(int,int)),widgetLineNumber,SLOT(setBlockRange(int,int)));
    //connect(widgetTextEdit->verticalScrollBar(),SIGNAL(valueChanged(int)),widgetLineNumber,SLOT(update()));

    //connect(widgetTextEdit,SIGNAL(textChanged()),widgetScroller,SLOT(updateText()));
    //connect(widgetTextEdit->verticalScrollBar(),SIGNAL(valueChanged(int)),widgetScroller,SLOT(update()));

    connect(widgetTextEdit->verticalScrollBar(),SIGNAL(valueChanged(int)), _widgetPdfViewer->widgetPdfDocument(),SLOT(jumpToPdfFromSourceView(int)));

    connect(widgetScroller,SIGNAL(changed(int)),widgetTextEdit,SLOT(scrollTo(int)));

    // Connect menubar Actions

    connect(this->ui->actionDeleteLastOpenFiles,SIGNAL(triggered()),this,SLOT(clearLastOpened()));
    connect(this->ui->actionNouveau,SIGNAL(triggered()),this,SLOT(newFile()));
    connect(this->ui->actionOpen,SIGNAL(triggered()),this,SLOT(open()));
    connect(this->ui->actionSave,SIGNAL(triggered()),this,SLOT(save()));
    connect(this->ui->actionSaveAs,SIGNAL(triggered()),this,SLOT(saveAs()));
    connect(this->ui->actionExit, SIGNAL(triggered()), this, SLOT(close()));
    //connect(this->ui->actionOpenRecent, SIGNAL(triggered()), this, SLOT(openLast()));
    connect(this->ui->actionUndo, SIGNAL(triggered()), this->widgetTextEdit, SLOT(undo()));
    connect(this->ui->actionRedo, SIGNAL(triggered()), this->widgetTextEdit, SLOT(redo()));
    connect(this->ui->actionCopy, SIGNAL(triggered()), this->widgetTextEdit, SLOT(copy()));
    connect(this->ui->actionCut, SIGNAL(triggered()), this->widgetTextEdit, SLOT(cut()));
    connect(this->ui->actionPaste, SIGNAL(triggered()), this->widgetTextEdit, SLOT(paste()));
    connect(this->ui->actionOpenConfigFolder, SIGNAL(triggered()), &ConfigManager::Instance, SLOT(openThemeFolder()));
    connect(this->ui->actionFindReplace, SIGNAL(triggered()), this, SLOT(openFindReplaceWidget()));
    connect(_widgetFindReplace->pushButtonClose(), SIGNAL(clicked()), this, SLOT(closeFindReplaceWidget()));
    this->closeFindReplaceWidget();
    connect(this->ui->actionPdfLatex,SIGNAL(triggered()),this,SLOT(pdflatex()));
    connect(this->ui->actionBibtex,SIGNAL(triggered()),this,SLOT(bibtex()));
    connect(this->widgetTextEdit->getCurrentFile()->getBuilder(), SIGNAL(pdfChanged()),this->_widgetPdfViewer->widgetPdfDocument(),SLOT(updatePdf()));
    connect(this->ui->actionView, SIGNAL(triggered()),this->_widgetPdfViewer->widgetPdfDocument(),SLOT(jumpToPdfFromSource()));
    connect(this->widgetTextEdit->getCurrentFile()->getBuilder(), SIGNAL(statusChanged(QString)), this->ui->statusBar, SLOT(showMessage(QString)));
    //connect(this->widgetTextEdit->getCurrentFile()->getViewer(), SIGNAL(finished()), this, SLOT(focus()));

    QAction * lastAction = this->ui->menuTh_me->actions().last();
    foreach(const QString& theme, ConfigManager::Instance.themesList())
    {
        QAction * action = new QAction(theme.left(theme.size()-10), this->ui->menuTh_me);
        action->setCheckable(true);
        if(!theme.left(theme.size()-10).compare(ConfigManager::Instance.theme()))
        {
            action->setChecked(true);
        }
        this->ui->menuTh_me->insertAction(lastAction,action);
        connect(action, SIGNAL(triggered()), this, SLOT(changeTheme()));
    }
    this->ui->menuTh_me->insertSeparator(lastAction);

    settings.endGroup();
    lastAction = this->ui->menuOuvrir_R_cent->actions().last();
    QStringList lastFiles = settings.value("lastFiles").toStringList();
    foreach(const QString& file, lastFiles)
    {
        QAction * action = new QAction(file, this->ui->menuOuvrir_R_cent);
        this->ui->menuOuvrir_R_cent->insertAction(lastAction,action);
        connect(action, SIGNAL(triggered()), this, SLOT(openLast()));
    }
    this->ui->menuOuvrir_R_cent->insertSeparator(lastAction);

    connect(_widgetConsole, SIGNAL(requestLine(int)), widgetTextEdit, SLOT(goToLine(int)));



    ui->gridLayout->addWidget(widgetLineNumber,0,0);
    ui->gridLayout->addWidget(_mainSplitter,0,1);

    _mainSplitter->addWidget(_leftSplitter);
    _mainSplitter->addWidget(_widgetPdfViewer);


    _leftSplitter->addWidget(this->widgetTextEdit);
    _leftSplitter->addWidget(this->_widgetFindReplace);
    _leftSplitter->addWidget(this->_widgetSimpleOutput);
    _leftSplitter->addWidget(this->_widgetConsole);

    _leftSplitter->setCollapsible(3,true);

    //Display only the editor :
    {
        QList<int> sizes;
        sizes<<800<<0<<0<<0;
        _leftSplitter->setSizes(sizes);
    }

    ui->gridLayout->setColumnMinimumWidth(0,40);


    connect(this->ui->actionSettings,SIGNAL(triggered()),this->dialogConfig,SLOT(show()));
    connect(this->dialogConfig,SIGNAL(accepted()),_syntaxHighlighter,SLOT(rehighlight()));


    this->newFile();

}

MainWindow::~MainWindow()
{
    // Save settings
    {
        QSettings settings;
        settings.beginGroup("mainwindow");
        settings.setValue("geometry", this->geometry());
        settings.endGroup();
    }
    delete ui;
}

void MainWindow::focus()
{
    this->activateWindow();
}
bool MainWindow::closeCurrentFile()
{
    if(widgetTextEdit->toPlainText().isEmpty() || !widgetTextEdit->getCurrentFile()->isModified())
    {
        return true;
    }
    DialogClose dialogClose(this);
    dialogClose.setMessage(tr(QString::fromUtf8("Le fichier %1 n'a pas été enregistré.").toLatin1()).arg(this->widgetTextEdit->getCurrentFile()->getFilename()));
    dialogClose.exec();
    if(dialogClose.confirmed())
    {
        return true;
    }
    return false;
}

void MainWindow::closeEvent(QCloseEvent * event)
{

    if(this->closeCurrentFile())
    {
        event->accept();
        return;
    }
    event->ignore();

}

void MainWindow::newFile()
{
    if(!this->closeCurrentFile())
    {
        return;
    }
    this->widgetTextEdit->getCurrentFile()->create();
    this->widgetTextEdit->setText("");


    this->_widgetPdfViewer->widgetPdfDocument()->setFile(this->widgetTextEdit->getCurrentFile());
    this->_widgetConsole->setBuilder(this->widgetTextEdit->getCurrentFile()->getBuilder());
    this->_widgetSimpleOutput->setBuilder(this->widgetTextEdit->getCurrentFile()->getBuilder());
}

void MainWindow::openLast()
{
    QString filename = dynamic_cast<QAction*>(sender())->text();
    /*load last file if it exists
    {
        QSettings settings;
        if(settings.contains("files/filename"))
        {
            this->open(settings.value("files/filename").toString());
        }
    }*/
    this->open(filename);
}
void MainWindow::open(QString filename)
{
    if(!this->closeCurrentFile())
    {
        return;
    }
    QSettings settings;
    //get the filname
    if(filename.isEmpty())
    {
        filename = QFileDialog::getOpenFileName(this,tr("Ouvrir un fichier"),settings.value("lastFolder").toString(),tr("Latex (*.tex *.latex);;BibTex(*.bib)"));

        if(filename.isEmpty())
        {
            return;
        }
    }
    QFileInfo info(filename);
    settings.setValue("lastFolder",info.path());
    QString basename = info.baseName();
    //window title
    this->setWindowTitle(basename+" - SimTex");
    //udpate the settings
    {
        QSettings settings;
        QStringList lastFiles = settings.value("lastFiles",QStringList()).toStringList();
        lastFiles.prepend(filename);
        lastFiles.removeDuplicates();
        while(lastFiles.count()>10) { lastFiles.pop_back(); }
        settings.setValue("lastFiles", lastFiles);
    }
    //open
    this->widgetTextEdit->getCurrentFile()->open(filename);
    this->_widgetPdfViewer->widgetPdfDocument()->setFile(this->widgetTextEdit->getCurrentFile());
    this->_widgetConsole->setBuilder(this->widgetTextEdit->getCurrentFile()->getBuilder());

    //udpate the widget
    //this->widgetTextEdit->setText(this->widgetTextEdit->getCurrentFile()->getData());

    this->ui->statusBar->showMessage(basename+" - "+this->widgetTextEdit->getCurrentFile()->codec());

}
void MainWindow::clearLastOpened()
{
    QSettings settings;
    settings.setValue("lastFiles", QStringList());
    this->ui->menuOuvrir_R_cent->clear();
    this->ui->menuOuvrir_R_cent->insertAction(0,this->ui->actionDeleteLastOpenFiles);
}

void MainWindow::pdflatex()
{
    this->save();
    this->widgetTextEdit->getCurrentFile()->getBuilder()->pdflatex();
}
void MainWindow::bibtex()
{
    this->save();
    this->widgetTextEdit->getCurrentFile()->getBuilder()->bibtex();
}


void MainWindow::save()
{
    if(this->widgetTextEdit->getCurrentFile()->getFilename().isEmpty())
    {
        return this->saveAs();
    }
    this->widgetTextEdit->getCurrentFile()->setData(this->widgetTextEdit->toPlainText());
    this->widgetTextEdit->getCurrentFile()->save();
    this->ui->statusBar->showMessage(tr(QString::fromUtf8("Sauvegardé").toLatin1()),2000);
}

void MainWindow::saveAs()
{
    //this->widgetTextEdit->getCurrentFile()->setData("sdfsdfg");
    //return;
    QString filename = QFileDialog::getSaveFileName(this,tr("Enregistrer un fichier"));
    this->widgetTextEdit->getCurrentFile()->setData(this->widgetTextEdit->toPlainText());
    if(filename.isEmpty())
    {
        return;
    }
    this->widgetTextEdit->getCurrentFile()->save(filename);
    this->setWindowTitle(filename.replace(QRegExp("^.*[\\\\\\/]([^\\\\\\/]*)$"),"\\1")+" - SimTex");
}



void MainWindow::changeTheme()
{
    QString text = dynamic_cast<QAction*>(this->sender())->text();
    foreach(QAction * action, this->ui->menuTh_me->actions())
    {
        if(action->text().compare(text))
            action->setChecked(false);
        else
            action->setChecked(true);

    }
    ConfigManager::Instance.load(text);
    this->_syntaxHighlighter->rehighlight();
    this->initTheme();
    this->widgetTextEdit->onCursorPositionChange();
}

void MainWindow::initTheme()
{
    {
        QPalette Pal(palette());
        Pal.setColor(QPalette::Background, ConfigManager::Instance.getTextCharFormats("linenumber").background().color());
        this->setAutoFillBackground(true);
        this->setPalette(Pal);
    }
    {
        QPalette Pal(this->ui->statusBar->palette());
        // set black background
        Pal.setColor(QPalette::Background, ConfigManager::Instance.getTextCharFormats("normal").background().color());
        Pal.setColor(QPalette::Window, ConfigManager::Instance.getTextCharFormats("normal").background().color());
        Pal.setColor(QPalette::WindowText, ConfigManager::Instance.getTextCharFormats("normal").foreground().color());
        this->setAutoFillBackground(true);
        this->ui->statusBar->setPalette(Pal);
        this->ui->statusBar->setStyleSheet("QStatusBar {background: "+ConfigManager::Instance.colorToString(ConfigManager::Instance.getTextCharFormats("normal").background().color())+
                                           "}");
    }
    this->widgetTextEdit->setStyleSheet(QString("QTextEdit { border: 1px solid ")+
                                        ConfigManager::Instance.colorToString(ConfigManager::Instance.getTextCharFormats("textedit-border").foreground().color())+"; "+QString("color: ")+
                                        ConfigManager::Instance.colorToString(ConfigManager::Instance.getTextCharFormats("normal").foreground().color())+"; "+
                                        QString("background-color: ")+ConfigManager::Instance.colorToString(ConfigManager::Instance.getTextCharFormats("normal").background().color())+
                                "; }");
    this->widgetTextEdit->setCurrentCharFormat(ConfigManager::Instance.getTextCharFormats("normal"));
    QTextCursor cur = this->widgetTextEdit->textCursor();
    cur.setCharFormat(ConfigManager::Instance.getTextCharFormats("normal"));
    this->widgetTextEdit->setTextCursor(cur);


    {
        QPalette Pal(palette());
        // set black background
        QTextCharFormat format = ConfigManager::Instance.getTextCharFormats("linenumber");
        QBrush brush = format.background();
        Pal.setColor(QPalette::Background, brush.color());
        this->widgetLineNumber->setAutoFillBackground(true);
        this->widgetLineNumber->setPalette(Pal);
    }
}

void MainWindow::openFindReplaceWidget()
{
    this->_widgetFindReplace->setMaximumHeight(110);
    this->_widgetFindReplace->setMinimumHeight(110);
    this->_widgetFindReplace->open();
}

void MainWindow::closeFindReplaceWidget()
{
    this->_widgetFindReplace->setMaximumHeight(0);
    this->_widgetFindReplace->setMinimumHeight(0);
}
