#include "blockdata.h"

QVector<ParenthesisInfo *> BlockData::parentheses() {
    return m_parentheses;
}
QVector<LatexBlockInfo *> BlockData::latexblocks() {
    return m_latexblocks;
}

void BlockData::insertPar( ParenthesisInfo *info ) {
    int i = 0;
    while (
        i < m_parentheses.size() &&
        info->position > m_parentheses.at(i)->position )
        ++i;
    m_parentheses.insert( i, info );
}

void BlockData::insertLat( LatexBlockInfo *info ) {
    int i = 0;
    while (
        i < m_latexblocks.size() &&
        info->position > m_latexblocks.at(i)->position )
        ++i;
    m_latexblocks.insert( i, info );
}
