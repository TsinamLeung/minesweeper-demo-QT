#include "widget_stage.h"
#include <QPushButton>
WidgetStage::WidgetStage(QWidget* parent /*= nullptr*/)
	: QFrame(parent)
{
	setStyleSheet("#stage { background-color: white; border: none; }");
	ResetLayout();
}

