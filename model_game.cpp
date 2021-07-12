#include "model_game.h"
#include <QRandomGenerator>

void Board::CreateBoard(int row, int col, int num_mine,int clicked_row,int clicked_col)
{
    QSet<QPair<int,int>> mines = generateMine(row,col,num_mine,clicked_row,clicked_col);

}

QSet<QPair<int, int>> Board::generateMine(int row, int col, int num_mine, int clicked_row, int clicked_col)
{
    auto ret = QSet<QPair<int,int>>();

    while(num_mine && num_mine < (row * col - 1)) {
        int x = QRandomGenerator::global()->bounded(row);
        int y = QRandomGenerator::global()->bounded(col);
        if(!ret.contains(qMakePair(x,y)) && (x != clicked_row && y != clicked_col))
        {
            ret.insert(qMakePair(x,y));
            --num_mine;
        }
    }
    // another way to avoid too random wasting is to make the set to map,[row => col]
    // if counts of row equals to col,which means,current col is full of mine,then skip it
    // make sure only the unplaced piece would be in next random
    return ret;
}
