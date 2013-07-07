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
    widgetTextEdit(new WidgetTextEdit(this)),
    widgetLineNumber(new WidgetLineNumber(this)),
    widgetScroller(new WidgetScroller),
    dialogWelcome(new DialogWelcome(this)),
    dialogConfig(new DialogConfig(this)),
    _widgetPdfViewer(new WidgetPdfViewer(this)),
    _mousePressed(false),
    _leftLayout(new QVBoxLayout()),
    _widgetConsole(new WidgetConsole()),
    _resizeConsole(false)
{
    ui->setupUi(this);
    ConfigManager::Instance.setMainWindow(this);
    //setWindowFlags(Qt::FramelessWindowHint);
    widgetLineNumber->setWidgetTextEdit(widgetTextEdit);
    widgetScroller->setWidgetTextEdit(widgetTextEdit);
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

    connect(widgetTextEdit,SIGNAL(updateFirstVisibleBlock(int,int)), _widgetPdfViewer->widgetPdfDocument(),SLOT(jumpToPdfFromSourceView(int,int)));

    connect(widgetScroller,SIGNAL(changed(int)),widgetTextEdit,SLOT(scrollTo(int)));

    // Connect menubar Actions

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
    connect(this->ui->actionPdfLatex,SIGNAL(triggered()),this->widgetTextEdit->getCurrentFile()->getBuilder(),SLOT(pdflatex()));
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
    ui->gridLayout->addLayout(this->_leftLayout,0,1);
    ui->gridLayout->addWidget(_widgetPdfViewer,0,2);

    this->_leftLayout->setSpacing(4);
    this->_leftLayout->addWidget(this->widgetTextEdit);
    this->_leftLayout->addWidget(this->_widgetFindReplace);
    this->_leftLayout->addWidget(this->_widgetConsole);

    ui->gridLayout->setColumnMinimumWidth(0,40);
    ui->gridLayout->setColumnMinimumWidth(2,settings.value("pdfViewerWidth",600).toInt());
    //ui->gridLayout->setColumnMinimumWidth(2,100);


    /*connect(this->dialogWelcome->getActionNew(),SIGNAL(clicked()), this->widgetTextEdit->getCurrentFile(), SLOT(create()));
    connect(this->dialogWelcome->getActionNew(),SIGNAL(clicked()), this->dialogWelcome, SLOT(close()));
    connect(this->dialogWelcome->getActionOpen(),SIGNAL(clicked()), this->dialogWelcome, SLOT(close()));
    connect(this->dialogWelcome->getActionOpenLast(),SIGNAL(clicked()), this->dialogWelcome, SLOT(close()));
    connect(this->dialogWelcome->getActionOpen(),SIGNAL(clicked()), this, SLOT(open()));*/
    //this->dialogWelcome->show();


    connect(this->ui->actionSettings,SIGNAL(triggered()),this->dialogConfig,SLOT(show()));
    connect(this->dialogConfig,SIGNAL(accepted()),_syntaxHighlighter,SLOT(rehighlight()));



    this->setMouseTracking(true);

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
void MainWindow::closeEvent(QCloseEvent * event)
{
    if(widgetTextEdit->toPlainText().isEmpty() || !widgetTextEdit->getCurrentFile()->isModified())
    {
        event->accept();
        return;
    }
    qDebug()<<"Closing";
    DialogClose dialogClose(this);
    dialogClose.setMessage(tr(QString::fromUtf8("Le fichier %1 n'a pas été enregistré.").toLatin1()).arg(this->widgetTextEdit->getCurrentFile()->getFilename()));
    dialogClose.exec();
    if(dialogClose.confirmed())
    {
        event->accept();
        return;
    }
    event->ignore();

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
    //get the filname
    if(filename.isEmpty())
    {
        filename = QFileDialog::getOpenFileName(this,tr("Ouvrir un fichier"));

        if(filename.isEmpty())
        {
            return;
        }
    }
    QString basename(filename);
    //window title
    this->setWindowTitle(basename.replace(QRegExp("^.*[\\\\\\/]([^\\\\\\/]*)$"),"\\1")+" - SimTex");
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


void MainWindow::mouseMoveEvent(QMouseEvent * event)
{


    //qDebug()<<event->pos().x()<<"    editor : "<<widgetTextEdit->width()+47<<","<<widgetTextEdit->width()+54<<"  y: "<<event->pos().y();
    if(_mousePressed || event->pos().x() > widgetTextEdit->width()+47
       && event->pos().x() < widgetTextEdit->width()+54
       && event->pos().y() > 30)
    {
        this->setCursor(Qt::SizeHorCursor);


        if(_mousePressed && event->pos().x() > 500)
        {
            this->ui->gridLayout->setColumnMinimumWidth(2,this->width()-event->pos().x());
            //qDebug()<<this->width()-event->pos().x();
        }
        return;
    }

    int leftLayoutY = this->height() - this->_widgetConsole->height() - this->ui->statusBar->height();
    if(this->_resizeConsole || (event->pos().x() > 50
            && event->pos().x() < widgetTextEdit->width()
            && event->pos().y() > leftLayoutY - 5
            && event->pos().y() < leftLayoutY + 5
                 ))
    {
        this->setCursor(Qt::SizeVerCursor);
        if(this->_resizeConsole)
        {
            int consoleHeight = this->height() - event->pos().y() - this->ui->statusBar->height();
            this->_widgetConsole->setMaximumHeight(qMax(0, qMin(consoleHeight, this->height()/2)));
            this->_widgetConsole->setMinimumHeight(qMax(0, qMin(consoleHeight, this->height()/2)));
        }
        return;
    }
    this->setCursor(Qt::ArrowCursor);

}
void MainWindow::mousePressEvent(QMouseEvent * event)
{
    if(event->pos().x() > widgetTextEdit->width()+47
       && event->pos().x() < widgetTextEdit->width()+54
       && event->pos().y() > 30)
    {
        this->_mousePressed = true;
    }
    int leftLayoutY = this->height() - this->_widgetConsole->height() - this->ui->statusBar->height();
    if(event->pos().x() > 50
       && event->pos().x() < widgetTextEdit->width()
       && event->pos().y() > leftLayoutY - 5
       && event->pos().y() < leftLayoutY + 5
            )
    {
        this->_resizeConsole = true;
    }
}
void MainWindow::mouseReleaseEvent(QMouseEvent * event)
{

    QSettings settings;
    settings.beginGroup("mainwindow");
    settings.setValue("pdfViewerWidth", this->ui->gridLayout->columnMinimumWidth(2));
    settings.endGroup();

    this->_mousePressed = false;
    this->_resizeConsole = false;
    this->setCursor(Qt::ArrowCursor);
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
    //this->widgetTextEdit->setPalette(QPalette(Qt::white,Qt::white,Qt::white,Qt::white,Qt::white,Qt::white,ConfigManager::Instance.getTextCharFormats("normal").background().color()));
    this->widgetTextEdit->setStyleSheet(QString("QTextEdit { border: 1px solid ")+
                                        ConfigManager::Instance.colorToString(ConfigManager::Instance.getTextCharFormats("textedit-border").foreground().color())+"; "+
                                        QString("background-color: ")+ConfigManager::Instance.colorToString(ConfigManager::Instance.getTextCharFormats("normal").background().color())+
                                "; }");
    this->widgetTextEdit->setCurrentCharFormat(ConfigManager::Instance.getTextCharFormats("normal"));
    this->widgetTextEdit->textCursor().setBlockCharFormat(ConfigManager::Instance.getTextCharFormats("normal"));

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
}

void MainWindow::closeFindReplaceWidget()
{
    this->_widgetFindReplace->setMaximumHeight(0);
    this->_widgetFindReplace->setMinimumHeight(0);
}
