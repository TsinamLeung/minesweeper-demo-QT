#include "model_game.h"
#include <QTime>
#include <QDebug>
#include <QQueue>

unsigned long randomUpper(long high) {
	qsrand(QTime::currentTime().msec());
	return (qrand() % (high + 1));
}


void Board::CreateBoard(int row, int col, int num_mine, int clicked_x, int clicked_y)
{
	QSet<QPair<int, int>> mines = generateMine(row, col, num_mine, clicked_x, clicked_y);
	_board.resize(row);
	for (int r = 0; r < row; ++r) {
		auto& container_piece = _board[r];
		for (int c = 0; c < col; ++c) {
			container_piece.push_back(Piece());
		}
	}

	foreach(auto& m, mines) {
		int r = m.first;
		int c = m.second;
		_board[r][c].Type = mine;
		setMineCount(r, c);
	}

	bfsExplore(clicked_x, clicked_y);
}

QSet<QPair<int, int>> Board::generateMine(int row, int col, int num_mine, int clicked_x, int clicked_y)
{
	auto ret = QSet<QPair<int, int>>();
	num_mine = num_mine > (row * col - 1) ? row * col - 1 : num_mine;
	while (num_mine) {
		int x = randomUpper(row - 1);
		int y = randomUpper(col - 1);
		bool can_place = !(x == clicked_x && y == clicked_y);
		if (!ret.contains(qMakePair(x, y)) && can_place)
		{
			ret.insert(qMakePair(x, y));
			--num_mine;
		}
	}
	// another way to avoid too random wasting is to make the set to map,[row => col]
	// if counts of row equals to col,which means,current col is full of mine,then skip it
	// make sure only the unplaced piece would be in next random
	return ret;
}

void Board::setMineCount(int x, int y)
{
	for (int i = x - 1; i <= x + 1; ++i) {
		if (i < 0 || i >= _board.size()) {
			continue;
		}
		for (int j = y - 1; j <= y + 1; ++j) {
			if (j < 0 || j >= _board[i].size()) {
				continue;
			}
			auto& type = _board[i][j].Type;
			if ((int)type < (int)mine) {
				type = (type_piece)(_board[i][j].Type + 1);
			}
		}
	}
}

void Board::bfsExplore(int x, int y)
{
	const int& row_size = _board.size();
	const int& col_size = _board.isEmpty() ? 0 : _board.first().size();
	if (row_size > 0 && col_size > 0) {
		using pos = QPair<int, int>;
		QQueue<pos> q;
		q.enqueue(pos(x, y));
		while (!q.isEmpty()) {
			auto& cur_pos = q.dequeue();
			auto& cur_x = cur_pos.first;
			auto& cur_y = cur_pos.second;

			if (cur_x < 0 || cur_x >= row_size || cur_y < 0 || cur_y >= col_size) {
				continue;
			}
			// do not discover when pointing to a mine
			if (_board[cur_x][cur_y].Type == mine || _board[cur_x][cur_y].Discover) {
				continue;
			}
			_board[cur_x][cur_y].Discover = true;

			//up
			q.push_back(pos(cur_x - 1, cur_y));
			//down
			q.push_back(pos(cur_x + 1, cur_y));
			//left
			q.push_back(pos(cur_x, cur_y - 1));
			//right
			q.push_back(pos(cur_x, cur_y + 1));
		}
	}
}
