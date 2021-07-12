#ifndef WIDGET_STAGE_H
#define WIDGET_STAGE_H

#include <QApplication>
#include <QFrame>
#include <QWidget>
#include <QGridLayout>
#include <memory>
class WidgetStage : public QFrame {
	Q_OBJECT
public:
	explicit WidgetStage(QWidget* parent = nullptr);

	inline void ResetLayout() { layout.reset(new QGridLayout());}
private:
	std::unique_ptr<QGridLayout> layout;
};
#endif // WIDGET_STAGE_H
