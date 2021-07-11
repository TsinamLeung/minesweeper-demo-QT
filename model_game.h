#ifndef MODEL_GAME_H
#define MODEL_GAME_H

#include <QVector>
#include <QSet>
#include <QPair>

enum type_piece {
    empty = 0,
    one,
    two,
    three,
    four,
    five,
    six,
    seven,
    eight,
    mine,
};

// structure that indidate the piece on board
class Piece{
public:
    type_piece Type = empty;
    bool Discover = false;
    bool Flag = false;
};

class Board {
public:
    void CreateBoard(int row,int col,int num_mine,int clicked_row,int clicked_col);
protected:
    QSet<QPair<int,int>> generateMine(int row,int col,int num_mine,int clicked_row,int clicked_col);
private:
    QVector<QVector<Piece>> _board;
};

#endif // MODEL_GAME_H
