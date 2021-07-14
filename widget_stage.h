#ifndef WIDGET_STAGE_H
#define WIDGET_STAGE_H

#include <QApplication>
#include <QFrame>
#include <QWidget>
#include <QGridLayout>
#include <QPainter>
#include <memory>
#include "model_game.h"

class ButtonGame : public QFrame
{
	Q_OBJECT
public:
	explicit ButtonGame(QWidget* parent = nullptr) : QFrame(parent)
	{
		painter.reset(new QPainter(this));
		showGameButton();
	};
	void ShowClicked() { setFrameShadow(Sunken); }
	void HideClicked() { setFrameShadow(Raised); }
	inline bool isClicking() { return this->frameShadow() == Sunken; }

private:
	void showGameButton();
	std::unique_ptr<QPainter> painter;
};

class WidgetStage : public QFrame
{
	Q_OBJECT
public:
	explicit WidgetStage(QWidget* parent = nullptr);

	inline void SetLayout()
	{
		layout.reset(new QGridLayout(this));
		layout->setHorizontalSpacing(5);
		layout->setVerticalSpacing(5);
		layout->setAlignment(Qt::AlignLeft | Qt::AlignTop);
		this->setLayout(layout.get());
	}

	void ResetLayout()
	{
		if (layout.get())
		{
			QLayoutItem *item;
			while ((item = layout->takeAt(0)))
			{
				if (item->widget())
				{
					delete item->widget();
				}
				delete item;
			}
		}
	}
signals:
	void resizeWindow(int w, int h);
	public slots:
	void SetMapSize(int row, int col, int num_mine);
	void SetDifficult();
private:
	std::unique_ptr<QGridLayout> layout;
	std::unique_ptr<Board> game_board;

	virtual void mouseMoveEvent(QMouseEvent *event);
	virtual void mousePressEvent(QMouseEvent *event);
	virtual void mouseReleaseEvent(QMouseEvent *event);
	QSet<ButtonGame*> getAroundInLayout(ButtonGame* center, int radius = 1);
	QSet<ButtonGame*> getAroundInLayout(int center_index, int radius = 1);
	void update();

	bool hold_left = false;
	bool hold_right = false;
	bool first_click = true;

	int row = 9;
	int col = 9;
	int num_mine = 10;
};

#endif // WIDGET_STAGE_H