#include "blockdata.h"
#include <QDebug>

QVector<ParenthesisInfo *> BlockData::parentheses() {
    return _parentheses;
}
QVector<LatexBlockInfo *> BlockData::latexblocks() {
    return _latexblocks;
}

void BlockData::insertPar( ParenthesisInfo *info ) {
    int i = 0;
    while (
        i < _parentheses.size() &&
        info->position > _parentheses.at(i)->position )
        ++i;
    _parentheses.insert( i, info );
}

void BlockData::insertLat( LatexBlockInfo *info ) {
    int i = 0;
    while (
        i < _latexblocks.size() &&
        info->position > _latexblocks.at(i)->position )
        ++i;
    _latexblocks.insert( i, info );
}

bool BlockData::isAClosingDollar(int position)
{
    bool even = false;
    foreach(int dollar, this->_dollars)
    {
        if(dollar > position)
        {
            return even;
        }
        even = !even;
    }
    return even;
}
