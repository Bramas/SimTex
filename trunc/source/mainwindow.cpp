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
    SyntaxHighlighter * syntaxHighlighter = new SyntaxHighlighter(widgetTextEdit);
    widgetTextEdit->setSyntaxHighlighter(syntaxHighlighter);

    // Load settings

    QSettings settings;
    settings.beginGroup("mainwindow");
    if(settings.contains("geometry")) this->setGeometry(settings.value("geometry").toRect());


    //define background

    {
        QPalette Pal(palette());
        // set black background
        Pal.setColor(QPalette::Background, ConfigManager::Instance.getTextCharFormats()->value("linenumber").background().color());
        this->setAutoFillBackground(true);
        this->setPalette(Pal);
    }

    {
        QPalette Pal(this->ui->statusBar->palette());
        // set black background
        Pal.setColor(QPalette::Background, ConfigManager::Instance.getTextCharFormats()->value("normal").background().color());
        Pal.setColor(QPalette::Window, ConfigManager::Instance.getTextCharFormats()->value("normal").background().color());
        Pal.setColor(QPalette::WindowText, ConfigManager::Instance.getTextCharFormats()->value("normal").foreground().color());
        this->setAutoFillBackground(true);
        this->ui->statusBar->setPalette(Pal);
        this->ui->statusBar->setStyleSheet("QStatusBar {background: "+ConfigManager::Instance.colorToString(ConfigManager::Instance.getTextCharFormats()->value("normal").background().color())+
                                           "}");
    }
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


    connect(this->ui->actionPdfLatex,SIGNAL(triggered()),this->widgetTextEdit->getCurrentFile()->getBuilder(),SLOT(pdflatex()));
    connect(this->widgetTextEdit->getCurrentFile()->getBuilder(), SIGNAL(pdfChanged()),this->_widgetPdfViewer->widgetPdfDocument(),SLOT(updatePdf()));
    connect(this->ui->actionView, SIGNAL(triggered()),this->_widgetPdfViewer->widgetPdfDocument(),SLOT(updatePdf()));
    connect(this->widgetTextEdit->getCurrentFile()->getBuilder(), SIGNAL(statusChanged(QString)), this->ui->statusBar, SLOT(showMessage(QString)));
    //connect(this->widgetTextEdit->getCurrentFile()->getViewer(), SIGNAL(finished()), this, SLOT(focus()));

    connect(_widgetConsole, SIGNAL(requestLine(int)), widgetTextEdit, SLOT(goToLine(int)));

    ui->gridLayout->addWidget(widgetLineNumber,0,0);
    ui->gridLayout->addLayout(this->_leftLayout,0,1);
    //ui->gridLayout->addWidget(widgetScroller,0,2);
    ui->gridLayout->addWidget(_widgetPdfViewer,0,2);

    this->_leftLayout->setSpacing(4);
    this->_leftLayout->addWidget(this->widgetTextEdit);
    this->_leftLayout->addWidget(this->_widgetConsole);

    ui->gridLayout->setColumnMinimumWidth(0,40);
    ui->gridLayout->setColumnMinimumWidth(2,settings.value("pdfViewerWidth",600).toInt());
    //ui->gridLayout->setColumnMinimumWidth(2,100);


    connect(this->dialogWelcome->getActionNew(),SIGNAL(clicked()), this->widgetTextEdit->getCurrentFile(), SLOT(create()));
    connect(this->dialogWelcome->getActionNew(),SIGNAL(clicked()), this->dialogWelcome, SLOT(close()));
    connect(this->dialogWelcome->getActionOpen(),SIGNAL(clicked()), this->dialogWelcome, SLOT(close()));
    connect(this->dialogWelcome->getActionOpenLast(),SIGNAL(clicked()), this->dialogWelcome, SLOT(close()));
    connect(this->dialogWelcome->getActionOpen(),SIGNAL(clicked()), this, SLOT(open()));
    connect(this->dialogWelcome->getActionOpenLast(),SIGNAL(clicked()), this, SLOT(openLast()));

    this->dialogWelcome->show();
    connect(this->ui->actionSettings,SIGNAL(triggered()),this->dialogConfig,SLOT(show()));
    connect(this->dialogConfig,SIGNAL(accepted()),syntaxHighlighter,SLOT(rehighlight()));



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
    if(!widgetTextEdit->getCurrentFile()->isModified())
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
    //load last file if it exists
    {
        QSettings settings;
        if(settings.contains("files/filename"))
        {
            this->open(settings.value("files/filename").toString());
        }
    }
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
        settings.setValue("files/filename", filename);
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


        if(_mousePressed)
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
