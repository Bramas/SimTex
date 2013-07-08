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

#ifndef WIDGETTEXTEDIT_H
#define WIDGETTEXTEDIT_H

#include <QPlainTextEdit>
#include <QTextBlock>
#include <QTextLayout>
#include <QMutex>
#include <QRectF>
#include "file.h"

class FileStructure;
class SyntaxHighlighter;
class CompletionEngine;
class WidgetInsertCommand;

struct BlockInfo
{
    int top;
    int height;
    int position;
    int leftMargin;
    BlockInfo() : leftMargin(0), top(0), height(0), position(0) {}
};


class WidgetTextEdit : public QPlainTextEdit
{
    Q_OBJECT
public:
    explicit WidgetTextEdit(QWidget *parent);
    int blockHeight(int blockNumber) { return blockHeight(this->document()->findBlockByNumber(blockNumber));  }
    int blockHeight(const QTextBlock &textBlock) { return blockBoundingGeometry(textBlock).height(); }
    int blockWidth(const QTextBlock &textBlock) { return textBlock.layout()->boundingRect().width(); }
    int blockTop(int blockNumber) { return blockTop(this->document()->findBlockByNumber(blockNumber)); }
    int blockTop(const QTextBlock &textBlock) { return blockBoundingGeometry(textBlock).top(); }
    int blockAbsoluteTop(int blockNumber) { return blockAbsoluteTop(this->document()->findBlockByNumber(blockNumber)); }
    int blockAbsoluteTop(const QTextBlock &textBlock) { return blockBoundingGeometry(textBlock).translated(contentOffset()).top(); }
    int blockBottom(const QTextBlock &textBlock) { return this->blocksInfo[textBlock.blockNumber()].top + this->blocksInfo[textBlock.blockNumber()].height; }
    QRectF blockGeometry(QTextBlock &textBlock) { return textBlock.layout()->boundingRect(); }


    int getTextHeight() { return this->textHeight; }
    File * getCurrentFile() { return this->currentFile; }
    void setText(const QString &text);
    int getFirstVisibleBlock() { return this->_firstVisibleBlock; }
    BlockInfo * getBlocksInfo() { return this->blocksInfo; }

    int scrollHeight();

    bool isCursorVisible();
    void setSyntaxHighlighter(SyntaxHighlighter * syntaxHighlighter) { this->_syntaxHighlighter = syntaxHighlighter; }
    void displayWidgetInsertCommand();
signals:
    void updateFirstVisibleBlock(int,int);
    void updatedWithSameFirstVisibleBlock();
    void setBlockRange(int,int);
    void lineCountChanged(int);
public slots:
    void scrollTo(int);
    void updateIndentation(void);
    void onCursorPositionChange(void);
    void matchCommand();
    void matchAll();
    void setFocus() { QPlainTextEdit::setFocus(); }
    void setFocus(QKeyEvent * event) { QPlainTextEdit::setFocus(); this->keyPressEvent(event); }
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
    int _firstVisibleBlock;
    int _lineCount;
    int _lastInitiedBlock;
    WidgetInsertCommand * _widgetInsertCommand;


};

#endif // WIDGETTEXTEDIT_H
