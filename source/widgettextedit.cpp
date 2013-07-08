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

#include "widgettextedit.h"
#include "widgetinsertcommand.h"
#include "configmanager.h"
#include "file.h"
#include "viewer.h"
#include <QScrollBar>
#include <QDebug>
#include <QPainter>
#include "filestructure.h"
#include "blockdata.h"
#include <QListIterator>
#include <QMutableListIterator>
#include <QList>
#include <QFontMetrics>
#include <QFileDialog>
#include <QSettings>
#include <QMimeData>
#include <QPalette>
#include "syntaxhighlighter.h"
#include "completionengine.h"
#include <math.h>
#include <QtCore>

#define max(a,b) ((a) < (b) ? (b) : (a))
#define min(a,b) ((a) > (b) ? (b) : (a))
#define abs(a) ((a) > 0 ? (a) : (-(a)))

WidgetTextEdit::WidgetTextEdit(QWidget * parent) :
    QPlainTextEdit(parent),
    fileStructure(new FileStructure(this)),
    updatingIndentation(false),
    currentFile(new File(this)),
    textHeight(0),
    firstVisibleBlock(0),
    blocksInfo(new BlockInfo[1]),
    _lineCount(0),
    _syntaxHighlighter(0),
    _completionEngine(new CompletionEngine(this)),
    _indentationInited(false),
    _widgetInsertCommand(new WidgetInsertCommand(this))

{
    blocksInfo[0].height = -1;

    connect(this,SIGNAL(textChanged()),this->currentFile,SLOT(setModified()));
    connect(this,SIGNAL(textChanged()),this,SLOT(updateIndentation()));
    connect(this,SIGNAL(cursorPositionChanged()), this, SLOT(onCursorPositionChange()));
    //connect(this->verticalScrollBar(),SIGNAL(valueChanged(int)),this,SLOT(update()));
    connect(this->verticalScrollBar(),SIGNAL(valueChanged(int)),this->viewport(),SLOT(update()));

    //this->setCurrentFont(QFont("Consolas", 17));
    //this->setCurrentFont(QFont("Consolas", 17));



    this->setText("");

}

void WidgetTextEdit::scrollTo(int p)
{
    this->verticalScrollBar()->setSliderPosition(p);
}

void WidgetTextEdit::setText(const QString &text)
{
    this->_indentationInited = false;
    QPlainTextEdit::setPlainText(text);
/* TODO : Run initIndentation in a thread */
    //QtConcurrent::run(this,&WidgetTextEdit::initIndentation);
    this->initIndentation();
    this->updateIndentation();
    this->update();
    this->viewport()->update();
}
void WidgetTextEdit::paintEvent(QPaintEvent *event)
{

    //qDebug()<<this->document()->blockCount();

    //this->setLineWrapColumnOrWidth(this->width()*0.8);

    QPlainTextEdit::paintEvent(event);
    QPainter painter(viewport());



    painter.setBrush(ConfigManager::Instance.getTextCharFormats("leftStructure").background());
    painter.setPen(QPen(ConfigManager::Instance.getTextCharFormats("leftStructure").foreground().color()));

    QFont font(ConfigManager::Instance.getTextCharFormats("leftStructure").font().family(),ConfigManager::Instance.getTextCharFormats("leftStructure").font().pointSize());
    font.setBold(ConfigManager::Instance.getTextCharFormats("leftStructure").font().bold());
    QFontMetrics fm(font);
    painter.setFont(font);



    QListIterator<FileStructureInfo*> iterator(*this->fileStructure->info());
    FileStructureInfo * value;
    int top = 0;
    int height = 0;


    int scrollHeight =  this->scrollHeight();

    qDebug()<<"--------------------";
    qDebug()<<scrollHeight<<"   "<<(this->document()->blockCount()>1 ? blocksInfo[1].top: false);

    painter.translate(15,0);
    painter.rotate(-90);
    while(iterator.hasNext())
    {

        value = iterator.next();
        if(value->top + value->height < scrollHeight ||
           scrollHeight + this->height() < value->top   )
        {
            continue;
        }
        top = max(value->top - scrollHeight,0);
        height = fm.width(value->name);
        //qDebug()<<value->top<<","<<value->endBlock<<"    "<<(value->height + value->top - this->verticalScrollBar()->value())<<" , "<<(height + 30);
        if(value->height + value->top - scrollHeight <  height + 30)
        {
            top = value->top + value->height -30 -height - scrollHeight;
            //qDebug()<<"pas assez "<<(value->height + value->top - this->verticalScrollBar()->value())<<" > "<<(height + 30);
        }

        painter.setPen(QPen(ConfigManager::Instance.getTextCharFormats("leftStructure").background().color()));
        painter.drawRect(- value->top - value->height -4  + scrollHeight,25*(value->level-2)+5,value->height-2,25);

        painter.setPen(QPen(ConfigManager::Instance.getTextCharFormats("leftStructure").foreground().color()));
        painter.drawText(-top-height-20,25*(value->level-1),value->name);
    }



    if(this->blocksInfo[0].height != -1)
    {
        int lastFirstVisibleBlock = this->firstVisibleBlock;
        this->firstVisibleBlock = -1;
        for(int i=1; i< this->document()->blockCount(); ++i)
        {
            //qDebug()<<"block "<<i<<" top : "<<blocksInfo[i].top<<" height : "<<blocksInfo[i].height<<"  scroll : "<<this->verticalScrollBar()->value();
            if(this->firstVisibleBlock == -1 && blocksInfo[i].top+blocksInfo[i].height > scrollHeight)
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

int WidgetTextEdit::scrollHeight()
{
    int lineHeight = this->document()->begin().layout()->lineAt(0).height();
    return this->verticalScrollBar()->value() * lineHeight;
}

bool WidgetTextEdit::isCursorVisible()
{
    bool down = this->blockBottom(this->textCursor().block()) > this->verticalScrollBar()->value();
    bool up = this->blockTop(this->textCursor().block()) < this->verticalScrollBar()->value()+this->height();
    return up && down;
}

void WidgetTextEdit::onCursorPositionChange()
{
    QList<QTextEdit::ExtraSelection> selections;
    setExtraSelections(selections);
    this->highlightCurrentLine();
    matchAll();
    this->currentFile->getViewer()->setLine(this->textCursor().blockNumber()+1);
}

void WidgetTextEdit::resizeEvent(QResizeEvent *event)
{
    this->updateIndentation();
    QPlainTextEdit::resizeEvent(event);
    update();
    //this->updateGeometry();
    //this->update();
    //this->viewport()->update();
}

void WidgetTextEdit::keyPressEvent(QKeyEvent *e)
{
    if(e->key() == Qt::Key_Space && (e->modifiers() & Qt::CTRL))
    {
        //this->matchCommand();
        this->displayWidgetInsertCommand();
        return;
    }
    if(this->_completionEngine->isVisible() && e->key() == Qt::Key_Down)
    {
        this->_completionEngine->setFocus();
        return;
    }
    if(this->_completionEngine->isVisible() && e->key() == Qt::Key_Up)
    {
        this->_completionEngine->setFocus();
        return;
    }

    if(this->focusWidget() != this)
    {
        this->insertPlainText(this->_completionEngine->acceptedWord());
        this->setFocus();
        return;
    }
    if(e->key() == Qt::Key_Dollar)
    {
        /* TODO : use beginEditBlock */
        QTextCursor cur = this->textCursor();
        int start = cur.selectionStart();
        int end = cur.selectionEnd();
        BlockData * bd = dynamic_cast<BlockData *>(this->textCursor().block().userData());
        if(start == end && bd->isAClosingDollar(start - this->textCursor().block().position()))
        {
            cur.insertText(QString::fromUtf8("$"));
            this->setTextCursor(cur);
            return;
        }
        cur.beginEditBlock();
        cur.setPosition(start);
        cur.insertText(QString::fromUtf8("$"));
        cur.setPosition(end+1);
        cur.endEditBlock();
        cur.beginEditBlock();
        cur.insertText(QString::fromUtf8("$"));

        if(end == start)
        {
            cur.movePosition(QTextCursor::Left);
        }
        cur.endEditBlock();
        this->setTextCursor(cur);
        return;
    }
    if(e->key() == Qt::Key_BraceLeft)
    {

        QTextCursor cur = this->textCursor();
        int start = cur.selectionStart();
        int end = cur.selectionEnd();
        cur.setPosition(start);
        cur.insertText(QString::fromUtf8("{"));
        cur.setPosition(end+1);
        cur.insertText(QString::fromUtf8("}"));
        if(end == start)
        {
            cur.movePosition(QTextCursor::Left);
        }
        this->setTextCursor(cur);
        return;
    }
    QPlainTextEdit::keyPressEvent(e);
    /*//qDebug()<<"ok"<<e->key()<<"  "<<Qt::Key_Enter;
    if(e->key() == Qt::Key_Enter || e->key() == Qt::Key_Enter - 1)
    {

    }*/
}
void WidgetTextEdit::wheelEvent(QWheelEvent * event)
{

    if(event->modifiers() & (Qt::ControlModifier))
    {
        int delta =  event->delta() > 0 ? 1 : -1 ;


        //this->textCursor().movePosition()
        ConfigManager::Instance.changePointSizeBy(delta);
        /*this->setCurrentCharFormat(ConfigManager::Instance.getTextCharFormats("normal"));
        QTextBlock tb = this->document()->begin();
        for(int i = 0; i < this->document()->blockCount(); ++i)
        {
            tb.layout()->setFont(ConfigManager::Instance.getTextCharFormats("normal").font());
            tb.clearLayout();
            tb.next();
        }*/
        int pos = this->textCursor().position();
        this->selectAll();
        this->textCursor().setBlockCharFormat(ConfigManager::Instance.getTextCharFormats("normal"));

        QTextCursor cur(this->textCursor());
        cur.setPosition(pos);
        this->setTextCursor(cur);

        if(this->_syntaxHighlighter)
        {
            this->_syntaxHighlighter->rehighlight();
        }
        /*QTextBlock tb = this->document()->begin();
        for(int i = 0; i < this->document()->blockCount(); ++i)
        {
            QList<QTextLayout::FormatRange> formats;
            QTextLayout::FormatRange r;
            r.start = -1;
            r.length=2;
            r.format = ConfigManager::Instance.getTextCharFormats("normal");
            formats.append(r);
            tb.layout()->setAdditionalFormats(formats);
            tb.clearLayout();
            tb.next();
        }*/
    }
    else
    {
        QPlainTextEdit::wheelEvent(event);
    }
    update();
}
void WidgetTextEdit::setBlockLeftMargin(const QTextBlock &textBlock, int leftMargin)
{
    //_formatMutex.lock();
    //if(!textBlock.isValid()) return;
/*    int blockNumber = textBlock.blockNumber();
    QTextBlockFormat format;
    QTextCursor cursor(this->textCursor());
    format.setLeftMargin(leftMargin);
    cursor.setPosition(textBlock.position());
    cursor.setBlockFormat(format);
*/
    textBlock.layout()->setPosition(QPointF(leftMargin,0));

    //_formatMutex.unlock();
    //if(blockNumber < this->document()->blockCount() - 1)
   // QtConcurrent::run(this, &WidgetTextEdit::setBlockLeftMargin, this->document()->findBlockByNumber(blockNumber+1), leftMargin);
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
    QTextCursor cursor(this->textCursor());
    while(iterator.hasNext())
    {
        value = iterator.next();
        value->top = blocksInfo[value->startBlock].top;
        value->height = blocksInfo[value->endBlock].top - blocksInfo[value->startBlock].top + blocksInfo[value->endBlock].height;

        for(int i = value->startBlock; i <= value->endBlock; ++i)
        {
            blocksInfo[i].leftMargin = 25*value->level;
            /*if(this->document()->findBlockByNumber(i).blockFormat().leftMargin() != 25*value->level)
            {
                myClassFormat.setLeftMargin(25*value->level);
                cursor.setPosition(blocksInfo[i].position);
                //cursor.setBlockFormat(myClassFormat);
            }*/
        }
    }

    //QtConcurrent::run(this, &WidgetTextEdit::setBlockLeftMargin, this->document()->begin(), marginApplied);
    //textBlock = this->document()->begin();
    for(int idx = 0; idx < this->document()->blockCount(); ++idx)
    {
        //this->setBlockLeftMargin(textBlock, marginApplied[idx]);
        textBlock = this->document()->findBlockByNumber(idx);
        this->setBlockLeftMargin(textBlock, blocksInfo[idx].leftMargin);
    }

    this->currentFile->refreshLineNumber();
    this->_indentationMutex.lock();
    this->_indentationInited = true;
    this->_indentationMutex.unlock();
    this->updatingIndentation = false;
}

void WidgetTextEdit::updateIndentation(void)
{
    if(this->updatingIndentation)
    {
        return;
    }
    this->updatingIndentation = true;
    delete blocksInfo;
    blocksInfo = new BlockInfo[this->document()->blockCount()];

    if(this->document()->blockCount() != _lineCount)
    {
        this->currentFile->insertLine(this->textCursor().blockNumber(), this->document()->blockCount() - _lineCount);
        emit lineCountChanged(this->document()->blockCount());
    }
    _lineCount = this->document()->blockCount();


    QTextBlock textBlock = this->document()->begin();



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

        blocksInfo[i].height = this->blockHeight(textBlock);
    }
    this->textHeight = blocksInfo[this->document()->blockCount()-1].top + blocksInfo[this->document()->blockCount()-1].height;

    this->matchCommand();

    this->_indentationMutex.lock();
    if(!this->_indentationInited)
    {
        this->_indentationMutex.unlock();
        this->updatingIndentation = false;
        return;
    }
    this->_indentationMutex.unlock();

    this->fileStructure->updateStructure();
    if(!this->fileStructure->info()->count())
    {
        this->updatingIndentation = false;
        return;
    }

    QTextBlockFormat myClassFormat;
    QListIterator<FileStructureInfo*> iterator(*this->fileStructure->info());


    FileStructureInfo * value;
    while(iterator.hasNext())
    {
        value = iterator.next();
        value->top = blocksInfo[value->startBlock].top;
        value->height = blocksInfo[value->endBlock].top - blocksInfo[value->startBlock].top + blocksInfo[value->endBlock].height;

    }

    BlockIndentation * indentation = this->fileStructure->indentations();
    QTextCursor cursor(this->textCursor());
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
    QMimeData * source2 =new QMimeData();
    source2->setData(QString("text/plain"),QByteArray(source->text().toLatin1()));
    QPlainTextEdit::insertFromMimeData(source2);
   /* if(source->hasUrls())
    {
        this->currentFile->open(source->urls().first().toLocalFile());//this->currentFile->open()
        this->setText(this->currentFile->getData());
        return;
    }
    this->append(source->text());*/
}
void WidgetTextEdit::matchAll()
{
    this->_completionEngine->setVisible(false);
    this->matchPar();
    this->matchLat();
}

void WidgetTextEdit::displayWidgetInsertCommand()
{
    QTextLine line = this->textCursor().block().layout()->lineForTextPosition(this->textCursor().positionInBlock());
    qreal left = line.cursorToX(this->textCursor().positionInBlock());
    qreal top = line.position().y() + line.height() + 5;
    QRect geo = _widgetInsertCommand->geometry();
    geo.moveTo(QPoint(0, top + this->blockTop(this->textCursor().block())-this->verticalScrollBar()->value()));
    if(geo.bottom() > this->height())
    {
        geo.translate(QPoint(0,-geo.height()-line.height()));
    }
    _widgetInsertCommand->setGeometry(geo);
    _widgetInsertCommand->setVisible(true);
    this->_widgetInsertCommand->show();

}

void WidgetTextEdit::matchCommand()
{
    QRegExp command("\\\\[a-zA-Z\\{\\-_]+$");
    QRegExp beginCommand("\\\\begin\\{([^\\}]+)\\}$");
    int pos = this->textCursor().positionInBlock();
    QString possibleCommand = this->textCursor().block().text().left(pos);


    if(possibleCommand.indexOf(command) != -1) // the possibleCommand is a command
    {
        //QFontMetrics fm(ConfigManager::Instance.getTextCharFormats("normal").font());
        int length = command.matchedLength();
        possibleCommand = possibleCommand.right(length);

        QTextLine line = this->textCursor().block().layout()->lineForTextPosition(this->textCursor().positionInBlock());
        qreal left = line.cursorToX(this->textCursor().positionInBlock());
        qreal top = line.position().y() + line.height() + 5;
        this->_completionEngine->proposeCommand(left,top + this->blockTop(this->textCursor().block())-this->verticalScrollBar()->value(),possibleCommand);
        if(this->_completionEngine->isVisible())// && e->key() == Qt::Key_Down)
        {
            this->_completionEngine->setFocus();
        }
    }
    else if(possibleCommand.indexOf(beginCommand) != -1)
    {
        QString environment = beginCommand.capturedTexts().last();
        QString endCommand(QString("\\end{")+environment+"}");
        QTextCursor cur = this->textCursor();
        int start = cur.selectionStart();
        cur.clearSelection();
        QTextBlock nextBlock = this->textCursor().block().next().next();
        if(nextBlock.isValid() && nextBlock.text().contains(endCommand))
        {
            return;
        }
        cur.insertText("\n    ");
        cur.beginEditBlock();
        cur.insertText(QString("\n")+endCommand);
        cur.setPosition(start+5);
        cur.endEditBlock();
        this->setTextCursor(cur);
    }

}

void WidgetTextEdit::matchPar()
{

    QTextBlock textBlock = textCursor().block();
    BlockData *data = static_cast<BlockData *>( textBlock.userData() );
    if ( data ) {
        QVector<ParenthesisInfo *> infos = data->parentheses();
        int pos = textCursor().block().position();

        for (int i=0; i < infos.size(); ++i) {
            ParenthesisInfo *info = infos.at(i);
            int curPos = textCursor().position() - textBlock.position();
            // Clicked on a left parenthesis?
            if ( info->position == curPos-1 && info->character == '{' ) {
                if ( matchLeftPar( textBlock, i+1, 0 ) )
                    createParSelection( pos + info->position );
            }

            // Clicked on a right parenthesis?
            if ( info->position == curPos-1 && info->character == '}' ) {
                if ( matchRightPar( textBlock, i-1, 0 ) )
                    createParSelection( pos + info->position );
            }
        }
    }
}
bool WidgetTextEdit::matchLeftPar(	QTextBlock currentBlock, int index, int numLeftPar )
{
    BlockData *data = static_cast<BlockData *>( currentBlock.userData() );
    QVector<ParenthesisInfo *> infos = data->parentheses();
    int docPos = currentBlock.position();

    // Match in same line?
    for ( ; index<infos.size(); ++index ) {
        ParenthesisInfo *info = infos.at(index);

        if ( info->character == '{' ) {
            ++numLeftPar;
            continue;
        }

        if ( info->character == '}' && numLeftPar == 0 ) {
            createParSelection( docPos + info->position );
            return true;
        } else
            --numLeftPar;
    }

    // No match yet? Then try next block
    currentBlock = currentBlock.next();
    if ( currentBlock.isValid() )
        return matchLeftPar( currentBlock, 0, numLeftPar );

    // No match at all
    return false;
}

bool WidgetTextEdit::matchRightPar(QTextBlock currentBlock, int index, int numRightPar)
{
    BlockData *data = static_cast<BlockData *>( currentBlock.userData() );
    QVector<ParenthesisInfo *> infos = data->parentheses();
    int docPos = currentBlock.position();

    // Match in same line?
    for (int j=index; j>=0; --j ) {
        ParenthesisInfo *info = infos.at(j);

        if ( info->character == '}' ) {
            ++numRightPar;
            continue;
        }

        if ( info->character == '{' && numRightPar == 0 ) {
            createParSelection( docPos + info->position );
            return true;
        } else
            --numRightPar;
    }

    // No match yet? Then try previous block
    currentBlock = currentBlock.previous();
    if ( currentBlock.isValid() ) {

        // Recalculate correct index first
        BlockData *data = static_cast<BlockData *>( currentBlock.userData() );
        QVector<ParenthesisInfo *> infos = data->parentheses();

        return matchRightPar( currentBlock, infos.size()-1, numRightPar );
    }

    // No match at all
    return false;
}

void WidgetTextEdit::createParSelection( int pos )
{
    QList<QTextEdit::ExtraSelection> selections = extraSelections();
    QTextEdit::ExtraSelection selection;
    QTextCharFormat format = selection.format;
    format.setBackground( QColor("#FFFF99") );
    format.setForeground( QColor("#FF0000") );
    selection.format = format;

    QTextCursor cursor = textCursor();
    cursor.setPosition( pos );
    cursor.movePosition( QTextCursor::NextCharacter, QTextCursor::KeepAnchor );
    selection.cursor = cursor;
    selections.append( selection );
    setExtraSelections( selections );
}
void WidgetTextEdit::matchLat()
{
    QTextBlock textBlock = textCursor().block();
    //if (foldableLines.keys().contains(textBlock.blockNumber())) createLatSelection(textBlock.blockNumber(),foldableLines[textBlock.blockNumber()]);
    //else
    {
        BlockData *data = static_cast<BlockData *>( textBlock.userData() );
        if( data )
        {
            QVector<LatexBlockInfo *> infos = data->latexblocks();
            int pos = textCursor().block().position();
            if (infos.size()==0)
            {
                emit setBlockRange(-1,-1);
                //endBlock=-1;
            }
            for ( int i=0; i<infos.size(); ++i )
            {
                LatexBlockInfo *info = infos.at(i);
                int curPos = textCursor().position() - textBlock.position();
                if ( info->position <= curPos && info->character == 'b' ) matchLeftLat( textBlock, i+1, 0, textBlock.blockNumber());
                if ( info->position <= curPos && info->character == 'e' ) matchRightLat( textBlock, i-1, 0,textBlock.blockNumber());
            }
        }
    }

}

bool WidgetTextEdit::matchLeftLat(	QTextBlock currentBlock, int index, int numLeftLat, int bpos )
{
    BlockData *data = static_cast<BlockData *>( currentBlock.userData() );
    QVector<LatexBlockInfo *> infos = data->latexblocks();
    int docPos = currentBlock.position();

    // Match in same line?
    for ( ; index<infos.size(); ++index ) {
        LatexBlockInfo *info = infos.at(index);

        if ( info->character == 'b' ) {
            ++numLeftLat;
            continue;
        }

        if ( info->character == 'e' && numLeftLat == 0 ) {
            createLatSelection( bpos,currentBlock.blockNumber() );
            return true;
        } else
            --numLeftLat;
    }

    // No match yet? Then try next block
    currentBlock = currentBlock.next();
    if ( currentBlock.isValid() )
        return matchLeftLat( currentBlock, 0, numLeftLat, bpos );

    // No match at all
    return false;
}

bool WidgetTextEdit::matchRightLat(QTextBlock currentBlock, int index, int numRightLat, int epos)
{

    BlockData *data = static_cast<BlockData *>( currentBlock.userData() );
    QVector<LatexBlockInfo *> infos = data->latexblocks();
    int docPos = currentBlock.position();

    // Match in same line?
    for (int j=index; j>=0; --j ) {
        LatexBlockInfo *info = infos.at(j);

        if ( info->character == 'e' ) {
            ++numRightLat;
            continue;
        }

        if ( info->character == 'b' && numRightLat == 0 ) {
            createLatSelection( epos, currentBlock.blockNumber() );
            return true;
        } else
            --numRightLat;
    }

    // No match yet? Then try previous block
    currentBlock = currentBlock.previous();
    if ( currentBlock.isValid() ) {

        // Recalculate correct index first
        BlockData *data = static_cast<BlockData *>( currentBlock.userData() );
        QVector<LatexBlockInfo *> infos = data->latexblocks();

        return matchRightLat( currentBlock, infos.size()-1, numRightLat, epos );
    }

    // No match at all
    return false;
}

void WidgetTextEdit::createLatSelection( int start, int end )
{
    int s=qMin(start,end);
    int e=qMax(start,end);
    emit setBlockRange(s,e);
    //endBlock=e;
}

void WidgetTextEdit::goToLine(int line)
{
    QTextCursor cursor(this->textCursor());
    cursor.setPosition(this->document()->findBlockByNumber(line).position());
    this->setTextCursor(cursor);
}

void WidgetTextEdit::highlightCurrentLine(void)
{
    QList<QTextEdit::ExtraSelection> extraSelections = this->extraSelections();


    QTextCursor cursor = textCursor();
    int blockNumber = cursor.blockNumber();
    cursor.movePosition(QTextCursor::StartOfBlock);
    while(cursor.blockNumber() == blockNumber)
    {
        QTextEdit::ExtraSelection selection;
        selection.format.setBackground(ConfigManager::Instance.getTextCharFormats("selected-line").background());
        selection.format.setProperty(QTextFormat::FullWidthSelection, true);
        selection.cursor = QTextCursor(cursor);
        selection.cursor.clearSelection();
        extraSelections.append(selection);
        if(!cursor.movePosition(QTextCursor::Down))
        {
            break;
        }
    }

    setExtraSelections(extraSelections);
}
