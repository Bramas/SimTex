#include "widgettextedit.h"
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
    _lineCount(0),
    _syntaxHighlighter(0),
    _completionEngine(new CompletionEngine(this))

{
    blocksInfo[0].height = -1;
    connect(this,SIGNAL(textChanged()),this->currentFile,SLOT(setModified()));
    connect(this,SIGNAL(textChanged()),this,SLOT(updateIndentation()));
    connect(this,SIGNAL(cursorPositionChanged()), this, SLOT(onCursorPositionChange()));
    //connect(this->verticalScrollBar(),SIGNAL(valueChanged(int)),this,SLOT(update()));
    connect(this->verticalScrollBar(),SIGNAL(valueChanged(int)),this->viewport(),SLOT(update()));
    connect(this,SIGNAL(cursorPositionChanged()),this, SLOT(matchAll()));

    //this->setCurrentFont(QFont("Consolas", 17));
    //this->setCurrentFont(QFont("Consolas", 17));

    this->setPalette(QPalette(Qt::white,Qt::white,Qt::white,Qt::white,Qt::white,Qt::white,ConfigManager::Instance.getTextCharFormats()->value("normal").background().color()));
    this->setStyleSheet(QString("QTextEdit { border: 1px solid ")+
                        ConfigManager::Instance.colorToString(ConfigManager::Instance.getTextCharFormats()->value("textedit-border").foreground().color())+
                                "}");

    this->setCurrentCharFormat(ConfigManager::Instance.getTextCharFormats()->value("normal"));
    this->setText("");
    this->textCursor().setBlockCharFormat(ConfigManager::Instance.getTextCharFormats()->value("normal"));

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
        painter.drawRect(- value->top - value->height -4  + this->verticalScrollBar()->value(),25*(value->level-2)+5,value->height-2,25);

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
    if(e->key() == Qt::Key_Space && (e->modifiers() & Qt::CTRL))
    {
        this->matchCommand();
        return;
    }
    if(this->_completionEngine->isVisible() && e->key() == Qt::Key_Down)
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
    QTextEdit::keyPressEvent(e);
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
        /*this->setCurrentCharFormat(ConfigManager::Instance.getTextCharFormats()->value("normal"));
        QTextBlock tb = this->document()->begin();
        for(int i = 0; i < this->document()->blockCount(); ++i)
        {
            tb.layout()->setFont(ConfigManager::Instance.getTextCharFormats()->value("normal").font());
            tb.clearLayout();
            tb.next();
        }*/
        int pos = this->textCursor().position();
        this->selectAll();
        this->textCursor().setBlockCharFormat(ConfigManager::Instance.getTextCharFormats()->value("normal"));
        this->textCursor().setPosition(pos,QTextCursor::KeepAnchor);

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
            r.format = ConfigManager::Instance.getTextCharFormats()->value("normal");
            formats.append(r);
            tb.layout()->setAdditionalFormats(formats);
            tb.clearLayout();
            tb.next();
        }*/
    }
    else
    {
        QTextEdit::wheelEvent(event);
    }
    update();
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
    this->currentFile->refreshLineNumber();
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
    QTextEdit::insertFromMimeData(source2);
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
    QList<QTextEdit::ExtraSelection> selections;
    setExtraSelections(selections);
    this->matchPar();
    this->matchLat();
}

void WidgetTextEdit::matchCommand()
{
    QRegExp command("\\\\[a-zA-Z]+$");
    int pos = this->textCursor().positionInBlock();
    QString possibleCommand = this->textCursor().block().text().left(pos);


    if(possibleCommand.indexOf(command) != -1) // the possibleCommand is a command
    {
        QFontMetrics fm(ConfigManager::Instance.getTextCharFormats()->value("normal").font());
        /*double widthD = double(fm.width(possibleCommand)) / double(this->blockWidth(this->textCursor().block()));
        qDebug()<<"command "<<fm.width(possibleCommand)<<" => "<<widthD<<", "<<fm.height();
        int widthI = floor(widthD);
        widthD -= widthI;
        widthD *= this->blockWidth(this->textCursor().block());
        ++widthI;
        widthI *= fm.height() + 2;
        widthI += 4;*/

        //QRect rect = fm.boundingRect (0,0,this->blockWidth(this->textCursor().block()),9999999, Qt::TextWordWrap | Qt::AlignLeft, possibleCommand);

        //qDebug()<<"command "<<rect.width()<<" , "<<rect.height();
        QTextLine line = this->textCursor().block().layout()->lineForTextPosition(this->textCursor().positionInBlock());
        qreal left = line.cursorToX(this->textCursor().positionInBlock());
        qreal top = line.position().y() + line.height() + 5;
        int length = command.matchedLength();
        this->_completionEngine->proposeCommand(left,top + this->blockTop(this->textCursor().block())-this->verticalScrollBar()->value(),possibleCommand.right(length));
        if(this->_completionEngine->isVisible())// && e->key() == Qt::Key_Down)
        {
            this->_completionEngine->setFocus();
        }
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

