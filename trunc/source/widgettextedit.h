#ifndef WIDGETTEXTEDIT_H
#define WIDGETTEXTEDIT_H

#include <QTextEdit>
#include <QTextBlock>
#include <QTextLayout>
#include <QMutex>
#include "file.h"

class FileStructure;
class SyntaxHighlighter;
class CompletionEngine;

struct BlockInfo
{
    int top;
    int height;
    int position;
    int leftMargin;
    BlockInfo() : leftMargin(0), top(0), height(0), position(0) {}
};


class WidgetTextEdit : public QTextEdit
{
    Q_OBJECT
public:
    explicit WidgetTextEdit(QWidget *parent);
    int blockHeight(const QTextBlock &textBlock) { return textBlock.layout()->boundingRect().height(); }
    int blockWidth(const QTextBlock &textBlock) { return textBlock.layout()->boundingRect().width(); }
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
    void setBlockRange(int,int);
public slots:
    void scrollTo(int);
    void updateIndentation(void);
    void onCursorPositionChange(void);
    void matchCommand();
    void matchAll();
    void setFocus() { QTextEdit::setFocus(); }
    void setFocus(QKeyEvent * event) { QTextEdit::setFocus(); this->keyPressEvent(event); }
    void goToLine(int line);
protected:
    void insertFromMimeData(const QMimeData * source);

private:
    void initIndentation(void);
    void paintEvent(QPaintEvent *event);
    void keyPressEvent(QKeyEvent *e);
    void resizeEvent(QResizeEvent * event);
    void wheelEvent(QWheelEvent * event);
    void highlightCurrentLine(void);

    void setBlockLeftMargin(const QTextBlock & textBlock, int leftMargin);

    void matchPar();
    bool matchLeftPar(QTextBlock currentBlock, int index, int numLeftPar );
    bool matchRightPar(QTextBlock currentBlock, int index, int numRightPar);
    void createParSelection(int pos );
    void matchLat();
    bool matchLeftLat(QTextBlock currentBlock, int index, int numLeftLat, int bpos);
    bool matchRightLat(QTextBlock currentBlock, int index, int numLeftLat, int bpos);
    void createLatSelection(int start, int end);

    SyntaxHighlighter * _syntaxHighlighter;
    CompletionEngine * _completionEngine;
    bool updatingIndentation;
    QMutex _indentationMutex;
    QMutex _formatMutex;
    bool _indentationInited;
    FileStructure * fileStructure;
    BlockInfo * blocksInfo;
    File * currentFile;
    int textHeight;
    int firstVisibleBlock;
    int _lineCount;


};

#endif // WIDGETTEXTEDIT_H
