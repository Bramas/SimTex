#ifndef DOCUMENTLAYOUT_H
#define DOCUMENTLAYOUT_H

#include <QPlainTextDocumentLayout>

class DocumentLayout : public QPlainTextDocumentLayout
{
    Q_OBJECT
public:
    explicit DocumentLayout(QTextDocument *parent = 0);
    QRectF	blockBoundingRect ( const QTextBlock & block ) const;
    QRectF	frameBoundingRect ( QTextFrame * frame ) const;
    int hitTest ( const QPointF & point, Qt::HitTestAccuracy accuracy ) const;
    void draw ( QPainter * painter, const PaintContext & context );
    int pageCount () const;
    QSizeF	documentSize () const  ;
signals:
    
public slots:

protected:
    void documentChanged ( int position, int charsRemoved, int charsAdded );
    
};

#endif // DOCUMENTLAYOUT_H
