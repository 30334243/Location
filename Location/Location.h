#pragma once
#include <Header.h>
#include "ui_Location.h"
#include "Widget.h"

class Location : public QMainWindow
{
	Q_OBJECT
public:
	Location(QWidget *parent = Q_NULLPTR);
private:
	Ui::LocationClass ui;

	std::unique_ptr<Widget> mWidget;
	std::atomic<int> mIdxRfids{ 0 };
	QRgb mColorRfid{ 1683335680 };
	QRgb mColorWall{ 4283782527 };
public slots:
	void sAddWall();
	void sAddRfid();
	void sColorRfid();
	void sColorWall();
	void sCreateRoom();
};
