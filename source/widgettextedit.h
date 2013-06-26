#ifndef WIDGETTEXTEDIT_H
#define WIDGETTEXTEDIT_H

#include <QTextEdit>
#include <QTextBlock>
#include <QTextLayout>
#include "file.h"

class FileStructure;
class SyntaxHighlighter;

struct BlockInfo
{
    int top;
    int height;
    int position;
};


class WidgetTextEdit : public QTextEdit
{
    Q_OBJECT
public:
    explicit WidgetTextEdit(QWidget *parent);
    int blockHeight(QTextBlock &textBlock) { return textBlock.layout()->boundingRect().height(); }
    int blockTop(const QTextBlock &textBlock) { return this->blocksInfo[textBlock.blockNumber()].top; }
    int blockBottom(const QTextBlock &textBlock) { return this->blocksInfo[textBlock.blockNumber()].top + this->blocksInfo[textBlock.blockNumber()].height; }
    QRectF blockGeometry(QTextBlock &textBlock) { return textBlock.layout()->boundingRect(); }

    int getTextHeight() { return this->textHeight; }
    File * getCurrentFile() { return this->currentFile; }
    void setText(const QString &text);
    int getFirstVisibleBlock() { return this->firstVisibleBlock; }
    BlockInfo * getBlocksInfo() { return this->blocksInfo; }

    bool isCursorVisible();
    void setSyntaxHighlighter(SyntaxHighlighter * syntaxHighlighter) { this->_syntaxHighlighter = syntaxHighlighter; }
    
signals:
    void updateFirstVisibleBlock(int,int);
    void updatedWithSameFirstVisibleBlock();
public slots:
    void scrollTo(int);
    void updateIndentation(void);
    void onCursorPositionChange(void);
protected:
    void insertFromMimeData(const QMimeData * source);

private:
    void initIndentation(void);
    void paintEvent(QPaintEvent *event);
    void keyPressEvent(QKeyEvent *e);
    void resizeEvent(QResizeEvent * event);
    void wheelEvent(QWheelEvent * event);

    SyntaxHighlighter * _syntaxHighlighter;
    bool updatingIndentation;
    FileStructure * fileStructure;
    BlockInfo * blocksInfo;
    File * currentFile;
    int textHeight;
    int firstVisibleBlock;
    int _lineCount;

};

#endif // WIDGETTEXTEDIT_H
