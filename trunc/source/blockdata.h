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
