#include "model_game.h"
#include <time.h>

int last_time = 0;
void updateRandomSeed(uint seed)
{
	last_time = seed;
	qsrand(seed);
}
unsigned long randomUpper(long high)
{
	int current_time = QTime::currentTime().msec();
	if (current_time != last_time)
	{
		updateRandomSeed(current_time);
	}
	return (qrand() % (high + 1));
}


Board::Board(int row, int col, int num_mine, int clicked_x, int clicked_y)
	: row(row), col(col), num_mine(num_mine)
{
	if (num_mine > (row * col - 9))
	{
		num_mine = row * col - 9;
		this->num_mine = num_mine;
	}
	auto mines = generateMine(row, col, num_mine, clicked_x, clicked_y);
	_board.resize(row);
	for (int r = 0; r < row; ++r)
	{
		auto& container_piece = _board[r];
		for (int c = 0; c < col; ++c)
		{
			container_piece.push_back(Piece());
		}
	}

	foreach(auto& m, mines)
	{
		int r = m.first;
		int c = m.second;
		_board[r][c].Type = MINE;
		countMine(r, c);
	}

	bfsExplore(clicked_x, clicked_y);
}

void Board::Dug(int x, int y)
{
	auto& piece = _board[x][y];
	if (!piece.Discover && !piece.Flag)
	{
		if (piece.Type == MINE)
		{
			this->state = DEAD;
			return;
		}
		bfsExplore(x, y);
		if (discoverd_blocks == (row * col - num_mine))
		{
			state = WIN;
			return;
		}
	}
}

bool Board::ToggleFlag(int x, int y)
{
	if (_board[x][y].Discover)
		return false;
	_board[x][y].Flag ^= true;
	_board[x][y].Flag ? ++flag_count : --flag_count;
	return _board[x][y].Flag;
}

int Board::CountAroundFlag(int pos_x, int pos_y)
{
	int cnt = 0;
	foreach(auto p, getNearbyPosition(pos_x, pos_y))
	{
		cnt += _board[p.first][p.second].Flag ? 1 : 0;
	}
	return cnt;
}

bool Board::IsDiscover(int pos_x, int pos_y)
{
	return _board[pos_x][pos_y].Discover;
}

type_piece& Board::GetState(int pos_x, int pos_y)
{
	return _board[pos_x][pos_y].Type;
}

QList<pos> Board::generateMine(int row, int col, int num_mine, int clicked_x, int clicked_y)
{
	auto ret = QList<pos>();
	num_mine = num_mine > (row * col - 9) ? row * col - 9 : num_mine;

	QVector<pos> pos_pool;
	for (int x = 0; x < row; ++x)
	{
		for (int y = 0; y < col; ++y)
		{
			// around the clicked point
			bool cannot_place = (x >= clicked_x - 1 && x <= clicked_x + 1) && (y >= clicked_y - 1 && y <= clicked_y + 1);
			if (cannot_place)
			{
				continue;
			}
			pos_pool.push_back(pos(x, y));
		}
	}
	while (num_mine)
	{
		int index = randomUpper(pos_pool.size() - 1);
		ret.append(pos_pool[index]);
		pos_pool.removeAt(index);
		--num_mine;
	}
	// using remove at might cause performance issue
	return ret;
}

void Board::countMine(int x, int y)
{
	for (int i = x - 1; i <= x + 1; ++i)
	{
		if (i < 0 || i >= _board.size())
		{
			continue;
		}
		for (int j = y - 1; j <= y + 1; ++j)
		{
			if (j < 0 || j >= _board[i].size())
			{
				continue;
			}
			auto& type = _board[i][j].Type;
			if ((int)type < (int)MINE)
			{
				type = (type_piece)(_board[i][j].Type + 1);
			}
		}
	}
}

void Board::bfsExplore(int x, int y)
{
	const int& row_size = _board.size();
	const int& col_size = _board.isEmpty() ? 0 : _board.first().size();
	if (row_size > 0 && col_size > 0)
	{
		QQueue<pos> q;
		q.enqueue(pos(x, y));
		while (!q.isEmpty())
		{
			const auto& cur_pos = q.dequeue();
			auto& cur_x = cur_pos.first;
			auto& cur_y = cur_pos.second;

			if (cur_x < 0 || cur_x >= row_size || cur_y < 0 || cur_y >= col_size)
			{
				continue;
			}
			// do not discover when pointing to a mine
			if (_board[cur_x][cur_y].Type == MINE || _board[cur_x][cur_y].Discover)
			{
				continue;
			}
			_board[cur_x][cur_y].Discover = true;
			discoverd_blocks++;
			// just Single layer BFS
			if (_board[cur_x][cur_y].Type == EMPTY)
			{
				foreach(pos p,getNearbyPosition(cur_x, cur_y))
				{
					q.push_back(p);
				}
			}

		}
	}
}

QList<pos> Board::getNearbyPosition(int x, int y,int radius)
{
	auto ret = QList<pos>();

	if (row > 0 && col > 0)
	{
		for (int i = x - radius; i <= x + radius; ++i)
		{
			if (i < 0 || i >= row)
				continue;
			for (int j = y - radius; j <= y + radius; ++j)
			{
				if (j < 0 || j >= col || (i == x && j == y))
					continue;
				ret.push_back(pos(i, j));
			}
		}
	}
	return ret;
}
