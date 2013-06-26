#include "widgettextedit.h"
#include "configmanager.h"
#include "file.h"
#include "viewer.h"
#include <QScrollBar>
#include <QDebug>
#include <QPainter>
#include "filestructure.h"
#include <QListIterator>
#include <QMutableListIterator>
#include <QList>
#include <QFontMetrics>
#include <QFileDialog>
#include <QSettings>
#include <QMimeData>
#include <QPalette>

#define max(a,b) ((a) < (b) ? (b) : (a))
#define min(a,b) ((a) > (b) ? (b) : (a))
#define abs(a) ((a) > 0 ? (a) : (-(a)))

WidgetTextEdit::WidgetTextEdit(QWidget * parent) :
    QTextEdit(parent),
    fileStructure(new FileStructure(this)),
    updatingIndentation(false),
    currentFile(new File(this)),
    textHeight(0),
    firstVisibleBlock(0),
    blocksInfo(new BlockInfo[1]),
    _lineCount(0)

{
    blocksInfo[0].height = -1;
    connect(this,SIGNAL(textChanged()),this->currentFile,SLOT(setModified()));
    connect(this,SIGNAL(textChanged()),this,SLOT(updateIndentation()));
    connect(this,SIGNAL(cursorPositionChanged()), this, SLOT(onCursorPositionChange()));
    //connect(this->verticalScrollBar(),SIGNAL(valueChanged(int)),this,SLOT(update()));
    connect(this->verticalScrollBar(),SIGNAL(valueChanged(int)),this->viewport(),SLOT(update()));

    this->setCurrentFont(QFont("Consolas", 12));

    this->setPalette(QPalette(Qt::white,Qt::white,Qt::white,Qt::white,Qt::white,Qt::white,ConfigManager::Instance.getTextCharFormats()->value("normal").background().color()));
    //this->setStyleSheet("QTextEdit { background-color: rgb(0, 255, 0) }");
}

void WidgetTextEdit::scrollTo(int p)
{
    this->verticalScrollBar()->setSliderPosition(p);
}

void WidgetTextEdit::setText(const QString &text)
{
    QTextEdit::setText(text);

    this->initIndentation();
    this->updateIndentation();
    this->update();
    this->viewport()->update();
}
void WidgetTextEdit::paintEvent(QPaintEvent *event)
{

    //qDebug()<<this->document()->blockCount();

    //this->setLineWrapColumnOrWidth(this->width()*0.8);

    QTextEdit::paintEvent(event);
    QPainter painter(viewport());
    painter.translate(15,0);
    painter.rotate(-90);

    painter.setBrush(ConfigManager::Instance.getTextCharFormats()->value("leftStructure").background());
    painter.setPen(QPen(ConfigManager::Instance.getTextCharFormats()->value("leftStructure").foreground().color()));

    QFont font(ConfigManager::Instance.getTextCharFormats()->value("leftStructure").font());
    QFontMetrics fm(font);
    painter.setFont(font);

    QListIterator<FileStructureInfo*> iterator(*this->fileStructure->info());
    FileStructureInfo * value;
    int top = 0;
    int height = 0;
    //qDebug()<<"--------------------";

    while(iterator.hasNext())
    {
        value = iterator.next();
        if(value->top + value->height < this->verticalScrollBar()->value() ||
           this->verticalScrollBar()->value() + this->height() < value->top   )
        {
            continue;
        }
        top = max(value->top - this->verticalScrollBar()->value(),0);
        height = fm.width(value->name);
        //qDebug()<<value->top<<","<<value->endBlock<<"    "<<(value->height + value->top - this->verticalScrollBar()->value())<<" , "<<(height + 30);
        if(value->height + value->top - this->verticalScrollBar()->value() <  height + 30)
        {
            top = value->top + value->height -30 -height - this->verticalScrollBar()->value();
            //qDebug()<<"pas assez "<<(value->height + value->top - this->verticalScrollBar()->value())<<" > "<<(height + 30);
        }

        painter.setPen(QPen(ConfigManager::Instance.getTextCharFormats()->value("leftStructure").background().color()));
        painter.drawRect(- value->top - value->height + -10 + this->verticalScrollBar()->value(),25*(value->level-2)+5,value->height,25);

        painter.setPen(QPen(ConfigManager::Instance.getTextCharFormats()->value("leftStructure").foreground().color()));
        painter.drawText(-top-height-20,25*(value->level-1),value->name);
    }



    if(this->blocksInfo[0].height != -1)
    {
        int lastFirstVisibleBlock = this->firstVisibleBlock;
        this->firstVisibleBlock = -1;
        for(int i=1; i< this->document()->blockCount(); ++i)
        {
            //qDebug()<<"block "<<i<<" top : "<<blocksInfo[i].top<<" height : "<<blocksInfo[i].height<<"  scroll : "<<this->verticalScrollBar()->value();
            if(this->firstVisibleBlock == -1 && blocksInfo[i].top+blocksInfo[i].height > this->verticalScrollBar()->value())
            {
                this->firstVisibleBlock = i;
            }

        }
        if(lastFirstVisibleBlock != this->firstVisibleBlock)
        {
            emit updateFirstVisibleBlock(this->firstVisibleBlock,blocksInfo[this->firstVisibleBlock].top);
        }
        else
        {
            emit updatedWithSameFirstVisibleBlock();
        }
    }

}

bool WidgetTextEdit::isCursorVisible()
{
    bool down = this->blockBottom(this->textCursor().block()) > this->verticalScrollBar()->value();
    bool up = this->blockTop(this->textCursor().block()) < this->verticalScrollBar()->value()+this->height();
    return up && down;
}

void WidgetTextEdit::onCursorPositionChange()
{

    this->currentFile->getViewer()->setLine(this->textCursor().blockNumber()+1);
    //this->currentFile->getViewer()->view();
}

void WidgetTextEdit::resizeEvent(QResizeEvent *event)
{
    QTextEdit::resizeEvent(event);
    //this->updateGeometry();
    //this->update();
    //this->viewport()->update();
}

void WidgetTextEdit::keyPressEvent(QKeyEvent *e)
{

    QTextEdit::keyPressEvent(e);
    /*//qDebug()<<"ok"<<e->key()<<"  "<<Qt::Key_Enter;
    if(e->key() == Qt::Key_Enter || e->key() == Qt::Key_Enter - 1)
    {

    }*/
}
void WidgetTextEdit::initIndentation(void)
{
    if(this->updatingIndentation)
    {
        return;
    }
    this->updatingIndentation = true;
    this->fileStructure->updateStructure();
    if(!this->fileStructure->info()->count())
    {

        this->updatingIndentation = false;
        return;
    }
    delete this->blocksInfo;
    this->blocksInfo = new BlockInfo[this->document()->blockCount()];




    QTextCursor cursor(this->textCursor());
    QTextBlock textBlock = this->document()->begin();


    //QListIterator<FileStructureInfo*> iterator(*this->fileStructure->info());
    FileStructureInfo * value;


    blocksInfo[0].top = 0;
    blocksInfo[0].height = this->blockHeight(textBlock);
    blocksInfo[0].position = 0;
    this->firstVisibleBlock = -1;
    for(int i=1; i< this->document()->blockCount(); ++i)
    {
        blocksInfo[i].top = blocksInfo[i-1].top + this->blockHeight(textBlock);
        blocksInfo[i].position = blocksInfo[i-1].position + textBlock.text().length()+1;

        textBlock=textBlock.next();

        blocksInfo[i].height =this->blockHeight(textBlock);
    }
    //update the entire text height
    this->textHeight = blocksInfo[this->document()->blockCount()-1].top + blocksInfo[this->document()->blockCount()-1].height;

    QTextBlockFormat myClassFormat;
    QListIterator<FileStructureInfo*> iterator(*this->fileStructure->info());
    //FileStructureInfo * value;
    while(iterator.hasNext())
    {
        value = iterator.next();
        value->top = blocksInfo[value->startBlock].top;
        value->height = blocksInfo[value->endBlock].top - blocksInfo[value->startBlock].top + blocksInfo[value->endBlock].height;
        for(int i = value->startBlock; i <= value->endBlock; ++i)
        {
            if(this->document()->findBlockByNumber(i).blockFormat().leftMargin() != 25*value->level)
            {
                myClassFormat.setLeftMargin(25*value->level);
                cursor.setPosition(blocksInfo[i].position);
                cursor.setBlockFormat(myClassFormat);
            }
        }
    }
    this->updatingIndentation = false;
}

void WidgetTextEdit::updateIndentation(void)
{
    if(this->updatingIndentation)
    {
        return;
    }
    this->updatingIndentation = true;
    this->fileStructure->updateStructure();
    if(!this->fileStructure->info()->count())
    {
        this->updatingIndentation = false;
        return;
    }
    delete blocksInfo;
    blocksInfo = new BlockInfo[this->document()->blockCount()];

    qDebug()<<"line count "<<this->document()->blockCount()<<" "<<_lineCount;
    if(this->document()->blockCount() != _lineCount)
    {
        this->currentFile->insertLine(this->textCursor().blockNumber(), this->document()->blockCount() - _lineCount);
    }
    _lineCount = this->document()->blockCount();


    QTextCursor cursor(this->textCursor());
    QTextBlock textBlock = this->document()->begin();


    FileStructureInfo * value;

    blocksInfo[0].top = 0;
    blocksInfo[0].height = this->blockHeight(textBlock);
    blocksInfo[0].position = 0;

    this->firstVisibleBlock = -1;
    //qDebug()<<"block Count "<<this->document()->blockCount();
    for(int i=1; i < this->document()->blockCount(); ++i)
    {
        blocksInfo[i].top = blocksInfo[i-1].top + blocksInfo[i-1].height;
        blocksInfo[i].position = blocksInfo[i-1].position + textBlock.text().length()+1;

        textBlock=textBlock.next();

        blocksInfo[i].height =this->blockHeight(textBlock);
    }
    this->textHeight = blocksInfo[this->document()->blockCount()-1].top + blocksInfo[this->document()->blockCount()-1].height;

    QTextBlockFormat myClassFormat;
    QListIterator<FileStructureInfo*> iterator(*this->fileStructure->info());

    while(iterator.hasNext())
    {
        value = iterator.next();
        value->top = blocksInfo[value->startBlock].top;
        value->height = blocksInfo[value->endBlock].top - blocksInfo[value->startBlock].top + blocksInfo[value->endBlock].height;

    }
    BlockIndentation * indentation = this->fileStructure->indentations();

    if(this->textCursor().block().blockFormat().leftMargin() != 25*indentation[this->textCursor().blockNumber()].level)
        for(int i = this->textCursor().blockNumber(); i < indentation[this->textCursor().blockNumber()].next; ++i)
        {
            myClassFormat.setLeftMargin(25*indentation[i].level);
            cursor.setPosition(blocksInfo[i].position);
            cursor.setBlockFormat(myClassFormat);
        }
    this->updatingIndentation = false;

}

void WidgetTextEdit::insertFromMimeData(const QMimeData *source)
{
   /* if(source->hasUrls())
    {
        this->currentFile->open(source->urls().first().toLocalFile());//this->currentFile->open()
        this->setText(this->currentFile->getData());
        return;
    }
    this->append(source->text());*/
}

