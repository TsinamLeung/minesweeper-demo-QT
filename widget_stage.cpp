#include "widget_stage.h"
#include <QPushButton>
#include <QDebug>
#include "qevent.h"
#include <QAction>

WidgetStage::WidgetStage(QWidget* parent /*= nullptr*/)
	: QFrame(parent)
{
	SetLayout();
	SetMapSize(row, col, num_mine);

	timer.reset(new QTimer(this));
	connect(timer.get(), &QTimer::timeout, this, &WidgetStage::TimeUP);
	//this->setFixedWidth(100);
	//this->setFixedHeight(100);

	//auto a = new ButtonGame(this);
	//auto b = new ButtonGame(this);
	//layout->addWidget(a,0,0,1,1);
	//layout->addWidget(b,1,0,1,1);
}

void ButtonGame::showGameButton()
{
	this->setAutoFillBackground(true);
	this->setStyleSheet(QString::fromUtf8("background:rgb(199,211,209)"));
	this->setFrameShape(QFrame::Panel);
	this->setFrameShadow(QFrame::Raised);
	this->setLineWidth(4);
	this->setFixedHeight(40);
	this->setFixedWidth(40);
}

void ButtonGame::Turn(QString content)
{
	this->setAutoFillBackground(false);
	this->setFrameShadow(Plain);
	this->setLineWidth(1);
	this->setStyleSheet(QString::fromUtf8("background:rgb(238,234,242)"));
	is_turn = true;
	button_content = content;
}
void ButtonGame::paintEvent(QPaintEvent * event)
{

	QFrame::paintEvent(event);
	QPainter painter(this);
	painter.setPen(Qt::black);
	painter.setFont(QFont("Seoge UI", 10));
	if (is_turn)
	{
		painter.drawText(rect(), Qt::AlignCenter, button_content);
	}
	if (is_flag)
	{
		painter.drawText(rect(), Qt::AlignCenter, "F");
	}
	else
	{
		QFrame::paintEvent(event);
	}

}

// initialize the game, start the game
void WidgetStage::SetMapSize(int row, int col, int num_mine)
{
	ResetLayout();

	emit changeState("Reset");

	if (timer.get())
	{
		timer->stop();
	}
	time_count = 0;
	emit increaseTime(0);
	emit displayFlagCount(0);

	first_click = true;
	current_state = GAMING;
	game_board.release();

	this->setFixedHeight(42 * row);
	this->setFixedWidth(42 * col);
	emit resizeWindow(45 * col, 180 + 45 * row);

	this->row = row;
	this->col = col;
	this->num_mine = num_mine;

	for (int x = 0; x < row; ++x)
	{
		for (int y = 0; y < col; ++y)
		{
			layout->addWidget(new ButtonGame(this), x, y, 1, 1);
		}
	}
	first_click = true;
}

void WidgetStage::SetMapSize()
{
	SetMapSize(row, col, num_mine);
}

void WidgetStage::SetDifficult()
{
	QString action_name = dynamic_cast<QAction*>(sender())->text();
	if (action_name == "Easy")
	{
		SetMapSize(9, 9, 10);
	}
	else if (action_name == "Middle")
	{
		SetMapSize(16, 16, 40);
	}
	else if (action_name == "Hard")
	{
		SetMapSize(16, 30, 99);
	}
}

void WidgetStage::TimeUP()
{
	emit increaseTime(++time_count);
}

void WidgetStage::mouseMoveEvent(QMouseEvent * event)
{
	if ((hold_left || hold_right) && current_state == GAMING)
	{
		const auto& element = childAt(event->pos());
		if (element)
		{
			const auto& clicked_index = layout->indexOf(element);
			ButtonGame* btn = dynamic_cast<ButtonGame*>(element);
			if (clicked_index >= 0)
			{
				if (!(hold_left && hold_right))
				{
					if (!btn->IsClicking() && btn->CanClick())
						btn->ShowClicked();
					auto nearby_buttons = getAroundInLayout(clicked_index);

					foreach(ButtonGame* a, nearby_buttons)
					{
						if (a == element)
							continue;
						if (a->IsClicking())
							a->HideClicked();
					}
				}
				else
				{
					foreach(ButtonGame* a, getAroundInLayout(clicked_index))
					{
						if (a->CanClick())
						{
							a->ShowClicked();
						}
					}

					foreach(auto p, FindIndexInCircle(clicked_index / col, clicked_index% col, row, col, 2, 1))
					{
						int pos_x = p.first;
						int pos_y = p.second;
						dynamic_cast<ButtonGame*>(layout->itemAt(pos_x * row + pos_y)->widget())->HideClicked();
					}
				}
			}
		}
	}
	//qDebug() << "Move: " << event->button();
	// update view here
}

void WidgetStage::mousePressEvent(QMouseEvent* event)
{
	//qDebug() << "Press: " << event->button();
	const auto& element = childAt(event->pos());

	switch (event->button())
	{
	case Qt::LeftButton:
		hold_left = true;
		break;
	case Qt::RightButton:
		hold_right = true;
		break;
	}

	if (element && current_state == GAMING)
	{
		auto btn = dynamic_cast<ButtonGame*>(element);
		if (!btn)
		{
			return;
		}
		if (btn->CanClick())
		{
			btn->ShowClicked();
		}
		if (hold_left && hold_right)
		{
			foreach(ButtonGame* a, getAroundInLayout(dynamic_cast<ButtonGame*>(element)))
			{
				if (a->CanClick())
				{
					a->ShowClicked();
				}
			}
		}
	}

}

void WidgetStage::mouseReleaseEvent(QMouseEvent * event)
{
	//qDebug() << "Release: " << event->button();
	const auto& element = childAt(event->pos());
	if (element)
	{
		if (current_state == GAMING)
		{

			auto btn = dynamic_cast<ButtonGame*>(element);
			if (!btn)
			{
				return;
			}
			foreach(ButtonGame* c, getAroundInLayout(btn))
			{
				c->HideClicked();
			}
			int index = layout->indexOf(element);
			int pos_x = index / col;
			int pos_y = index % col;

			if (hold_left && hold_right)
			{
				if (game_board.get())
				{
					int count_flag = game_board->CountAroundFlag(pos_x, pos_y);
					type_piece state = game_board->GetState(pos_x, pos_y);
					if (count_flag >= (int)state)
					{
						foreach(auto dug_pos, FindIndexInCircle(pos_x, pos_y, row, col, 1, 0))
						{
							game_board->Dug(dug_pos.first, dug_pos.second);
						}
					}
				}
			}
			else if (hold_left)
			{

				if (first_click)
				{
					timer->start(1000);
					game_board.reset(new Board(row, col, num_mine, pos_x, pos_y));
					first_click = false;
				}
				else
				{
					game_board->Dug(pos_x, pos_y);
				}

			}
			else if (hold_right)
			{
				if (game_board.get())
				{
					btn->SetFlag(game_board->ToggleFlag(pos_x, pos_y));
					btn->setFrameShadow(Raised);
				}
			}
		}
		update();
	}

	hold_left = hold_right = false;
}

QSet<ButtonGame*> WidgetStage::getAroundInLayout(ButtonGame* center, int radius /* = 1*/)
{
	int center_index = layout->indexOf(center);
	return getAroundInLayout(center_index, radius);
}

QSet<ButtonGame*> WidgetStage::getAroundInLayout(int center_index, int radius /* = 1*/)
{
	auto ret = QSet<ButtonGame*>();
	if (center_index >= 0)
	{
		int pos_x = center_index / col;
		int pos_y = center_index  % col;

		// full spec
		for (int i = pos_x - radius; i <= pos_x + radius; ++i)
		{
			if (i < 0 || i >= row)
			{
				continue;
			}
			for (int j = pos_y - radius; j <= pos_y + radius; ++j)
			{
				if (j < 0 || j >= col)
				{
					continue;
				}

				ButtonGame* res = dynamic_cast<ButtonGame*>(layout->itemAt(i * col + j)->widget());
				if (res)
				{
					ret.insert(res);
				}
			}
		}
	}
	return ret;
}

void WidgetStage::update()
{
	//qDebug() << "Current State : " << current_state;
	if (!game_board.get())
		return;
	
	this->current_state = game_board->state;
	if (current_state == WIN)
	{
		emit changeState("You Won!!");
		timer->stop();
	}
	else if (current_state == DEAD)
	{
		emit changeState("You lose!!");
		timer->stop();
	}
	emit displayFlagCount(game_board->FlagCount());

	for (int i = 0; i < layout->count(); ++i)
	{
		ButtonGame* btn = dynamic_cast<ButtonGame*>(layout->itemAt(i)->widget());
		if (!btn)
		{
			continue;
		}
		if (!game_board.get())
		{
			return;
		}
		int pos_x = i / col;
		int pos_y = i % col;
		if (game_board->IsDiscover(pos_x, pos_y))
		{
			auto& state = game_board->GetState(pos_x, pos_y);
			if (state == EMPTY)
			{
				btn->Turn();
			}
			else if (state == MINE)
			{
				btn->Turn("*");
			}
			else
			{
				btn->Turn(QString::number((int)state));
			}
		}

	}
}

QList<QPair<int, int>> FindIndexInCircle(int x, int y, int border_x, int border_y, int outter_radius, int inner_radius)
{
	auto ret = QList<QPair<int, int>>();

	for (int i = x - outter_radius; i <= x + outter_radius; ++i)
	{
		if (i < 0 || i >= border_x)
			continue;
		for (int j = y - outter_radius; j <= y + outter_radius; ++j)
		{
			if (j < 0 || j >= border_y || ((x - inner_radius <= i && i <= x + inner_radius) && (y - inner_radius <= j && j <= y + inner_radius)))
				continue;
			ret.append(QPair<int, int>(i, j));
		}
	}
	return ret;
}
