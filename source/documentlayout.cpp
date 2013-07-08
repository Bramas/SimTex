#include "documentlayout.h"
#include <QDebug>
#include <QRectF>
DocumentLayout::DocumentLayout(QTextDocument *parent) :
    QPlainTextDocumentLayout (parent)
{
}

QRectF DocumentLayout::blockBoundingRect(const QTextBlock &block) const
{
    return QPlainTextDocumentLayout::blockBoundingRect(block);
    QRectF rect(0,0,0,0);
    return rect;
}
QRectF DocumentLayout::frameBoundingRect(QTextFrame *frame) const
{

    QRectF rect(0,0,0,0);
    return rect;
}

int DocumentLayout::hitTest(const QPointF &point, Qt::HitTestAccuracy accuracy) const
{

    return -1;
}

void DocumentLayout::documentChanged(int position, int charsRemoved, int charsAdded)
{
    QPlainTextDocumentLayout::documentChanged(position, charsRemoved, charsAdded);
}

int DocumentLayout::pageCount() const
{
    return QPlainTextDocumentLayout::pageCount();
}

void DocumentLayout::draw(QPainter *painter, const PaintContext &context)
{
    // QPlainTextDocumentLayout::draw(painter, context);
}
QSizeF DocumentLayout::documentSize() const
{
    return QPlainTextDocumentLayout::documentSize();
}
