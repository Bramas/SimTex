#ifndef BLOCKDATA_H
#define BLOCKDATA_H

#include <QTextBlock>
#include <QTextBlockUserData>

struct ParenthesisInfo {
    QChar character;
    int position;
};

struct LatexBlockInfo {
    QChar character;
    int position;
};

class BlockData : public QTextBlockUserData
{

public:
    BlockData() {};
    static BlockData *data(const QTextBlock &block) { return static_cast<BlockData *>(block.userData()); }
    QList<int> code;
    QList<bool> misspelled;
    QVector<ParenthesisInfo *> parentheses();
    QVector<LatexBlockInfo *> latexblocks();
    void insertPar( ParenthesisInfo *info );
    void insertLat( LatexBlockInfo *info );
    void insertDollar(int pos ) { this->_dollars.append(pos); }
    bool isAClosingDollar(int position);
private:
    QVector<ParenthesisInfo *> _parentheses;
    QVector<LatexBlockInfo *> _latexblocks;
    QVector<int> _dollars;
};


#endif // BLOCKDATA_H
