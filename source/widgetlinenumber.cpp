#include "widgetlinenumber.h"
#include "widgettextedit.h"
#include <QPainter>
#include <QString>
#include <QTextBlock>
#include <QTextLayout>
#include <QScrollBar>
#include <QDebug>

WidgetLineNumber::WidgetLineNumber(QWidget *parent) :
    QWidget(parent),
    widgetTextEdit(0),
    firstVisibleBlock(0),
    firstVisibleBlockTop(0)
{
    this->scrollOffset = 0;

}

void WidgetLineNumber::setWidgetTextEdit(WidgetTextEdit *widgetTextEdit)
{
    this->widgetTextEdit = widgetTextEdit;
    connect(this->widgetTextEdit,SIGNAL(updateFirstVisibleBlock(int,int)), this, SLOT(updateFirstVisibleBlock(int,int)));
}

void WidgetLineNumber::updateFirstVisibleBlock(int block, int top)
{
    this->firstVisibleBlock = block;
    this->firstVisibleBlockTop = top;
    this->update();
    //qDebug()<<"first : "<<block<<"  "<< this->firstVisibleBlockTop;
}

void WidgetLineNumber::paintEvent(QPaintEvent *event)
{
    if(!widgetTextEdit) return;

    //update info about the scroll position
    this->scrollOffset = -this->widgetTextEdit->verticalScrollBar()->value();


    QPainter painter(this);

    QFont font("Consolas", 12);
    painter.setFont(font);
    QFontMetrics fm(font);
    painter.setFont(font);

    QTextBlock textBlock = widgetTextEdit->document()->findBlockByNumber(this->firstVisibleBlock);

    //qDebug()<<"line";
    int l;

   /* BlockInfo * blocksInfo = this->widgetTextEdit->getBlocksInfo();
    for(int i=0; i < this->widgetTextEdit->document()->blockCount(); ++i)
    {
        if(blocksInfo[i].top > this->widgetTextEdit->verticalScrollBar()->value())
        {
            qDebug()<<i;
        }
    }*/
    int cumulatedPosition = this->firstVisibleBlockTop;
    if(this->firstVisibleBlock == 1)
    {
        painter.drawText(0,this->scrollOffset+fm.height(),QString::number(1));
    }
    for(l = this->firstVisibleBlock+1; l <= widgetTextEdit->document()->blockCount(); ++l)
    {
        //qDebug()<<l;//<<"  "<<this->widgetTextEdit->blockGeometry(textBlock).bottom();
        //if(this->widgetTextEdit->blockBottom(textBlock) < this->widgetTextEdit->verticalScrollBar()->value())//  !textBlock.isVisible())
        //{
        //    textBlock = textBlock.next();
        //    continue;
        //}
        if(!textBlock.isValid())
        {
            break;
        }
        painter.drawText(0,this->scrollOffset+cumulatedPosition+fm.height(),QString::number(l));
        cumulatedPosition += widgetTextEdit->blockHeight(textBlock);
        textBlock = textBlock.next();
    }
}

