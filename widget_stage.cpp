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


void WidgetStage::SetMapSize(int row, int col, int num_mine)
{
	ResetLayout();
	first_click = true;
	this->setFixedHeight(50 * row);
	this->setFixedWidth(50 * col);
    emit resizeWindow(50 * row,145 + 50 * col);

    this->row = row;
    this->col = col;
    this->num_mine = num_mine;

	for (int x = 0; x < row; ++x) {
		for (int y = 0; y < col; ++y) {
			layout->addWidget(new ButtonGame(this), x, y, 1, 1);
		}
	}
	first_click = true;
}

void WidgetStage::SetDifficult()
{
	QString action_name = dynamic_cast<QAction*>(sender())->text();
	if (action_name == "Easy") {
		SetMapSize(9, 9, 10);
	}
	else if (action_name == "Middle") {
		SetMapSize(16, 16, 40);
	}
	else if (action_name == "Hard") {
		SetMapSize(16, 30, 99);
	}
}

void WidgetStage::mouseMoveEvent(QMouseEvent * event)
{
	if (hold_left | hold_right) {
		const auto& element = childAt(event->pos());
		if (element) {
			const auto& clicked_index = layout->indexOf(element);
			if (clicked_index >= 0) {
				ButtonGame* btn = dynamic_cast<ButtonGame*>(element);
				if(!btn->isClicking())
					btn->ShowClicked();
				auto nearby_buttons = getAroundInLayout(clicked_index);

                foreach (ButtonGame* a , nearby_buttons)
				{
					if(a == element) 
						continue;
					if(a->isClicking())
						a->HideClicked();
				}

			}
		}
	}
	//qDebug() << "Move: " << event->button();
	// update view here
}

void WidgetStage::mousePressEvent(QMouseEvent * event)
{
	qDebug() << "Press: " << event->button();
	const auto& element = childAt(event->pos());
	if (element) {
		auto btn = dynamic_cast<ButtonGame*>(element);
		if (!btn->isClicking()) {
			btn->HideClicked();
		}
	}
	switch (event->button()) {
	case Qt::LeftButton:
		hold_left = true;
		break;
	case Qt::RightButton:
		hold_right = true;
		break;
	}
}

void WidgetStage::mouseReleaseEvent(QMouseEvent * event)
{
	qDebug() << "Release: " << event->button();
	const auto& element = childAt(event->pos());
	if (element) {
		auto btn = dynamic_cast<ButtonGame*>(element);
		if (btn->isClicking()) {
			btn->HideClicked();
		}
	}
	if (hold_left && hold_right) {

	}
	else if (hold_left) {

	}
	else if (hold_right) {

	}

	hold_left = hold_right = false;
}

QSet<ButtonGame*> WidgetStage::getAroundInLayout(ButtonGame* center,int radius /* = 1*/)
{
	int center_index = layout->indexOf(center);
	return getAroundInLayout(center_index);
}

QSet<ButtonGame*> WidgetStage::getAroundInLayout(int center_index,int radius /* = 1*/)
{
	auto ret = QSet<ButtonGame*>();
	if (center_index >= 0) {
		int x = center_index / col;
		int y = center_index  % col;

		// full spec
		for (int i = x - radius; i <= x + radius; ++i) {
			if (i < 0 || i >= row) {
				continue;
			}
			for (int j = y - radius; j <= y + radius; ++j) {
				if (j < 0 || j >= col) {
					continue;
				}

				ButtonGame* res = dynamic_cast<ButtonGame*>(layout->itemAt(i * col + j)->widget());
				if (res) {
					ret.insert(res);
				}
			}
		}
	}
	return ret;
}
