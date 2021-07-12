#ifndef MODEL_GAME_H
#define MODEL_GAME_H

#include <QVector>
#include <QSet>
#include <QPair>
#include <QList>
#include <QTime>
#include <QDebug>
#include <QQueue>

unsigned long randomUpper(long);

using pos = QPair<int, int>;
enum type_piece {
    EMPTY = 0,
    ONE,
    TWO,
    THREE,
    FOUR,
    FIVE,
    SIX,
    SEVEN,
    EIGHT,
    MINE,
};

enum state_game {
	GAMING,
	DEAD,
	WIN
};
// structure that indicate the piece on board
class Piece{
public:
    type_piece Type;
    bool Discover;
	bool Flag;

	Piece(type_piece t = EMPTY,bool d = false,bool f = false) : Type(t),Discover(d),Flag(f) {}
};

class Board {
public:
    Board(int row,int col,int num_mine,int clicked_x,int clicked_y);
	void Dug(int x,int y);
	void PlaceFlag(int x, int y);
	void PlugFlag(int x, int y);
	state_game state = GAMING;
protected:
    QList<pos> generateMine(int row,int col,int num_mine,int clicked_x,int clicked_y);
	void countMine(int x, int y);
	void bfsExplore(int x, int y);
	int discoverd_blocks = 0;
private:
	int row;
	int col;
	int num_mine;
	Board() {};
    QVector<QVector<Piece>> _board;
};

#endif // MODEL_GAME_H
