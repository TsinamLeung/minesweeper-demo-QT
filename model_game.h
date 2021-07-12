#ifndef MODEL_GAME_H
#define MODEL_GAME_H

#include <QVector>
#include <QSet>
#include <QPair>

unsigned long randomUpper(long);

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

// structure that indicate the piece on board
class Piece{
public:
    type_piece Type;
    bool Discover;
	bool Flag;
	Piece(type_piece t = empty,bool d = false,bool f = false) : Type(t),Discover(d),Flag(f) {}
};

class Board {
public:
    void CreateBoard(int row,int col,int num_mine,int clicked_x,int clicked_y);
protected:
    QSet<QPair<int,int>> generateMine(int row,int col,int num_mine,int clicked_x,int clicked_y);
	void setMineCount(int x, int y);
	void bfsExplore(int x, int y);
private:
    QVector<QVector<Piece>> _board;
};

#endif // MODEL_GAME_H
