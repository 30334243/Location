#pragma once
#include <Header.h>
#include "Location.h"

Location::Location(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	mWidget = std::make_unique<Widget>();
	ui.LayWidget->addWidget(mWidget.get());
	mWidget->setFocusPolicy(Qt::NoFocus);

	connect(ui.BtnWall, &QPushButton::clicked, this, &Location::sAddWall);
	connect(ui.BtnRfid, &QPushButton::clicked, this, &Location::sAddRfid);

	connect(mWidget.get(), &Widget::removedRfid, 
			[this]
			{
				--mIdxRfids;
			});
	connect(ui.BtnColorRfid, &QPushButton::clicked, this, &Location::sColorRfid);
	connect(ui.BtnColorWall, &QPushButton::clicked, this, &Location::sColorWall);
	connect(ui.BtnRoom, &QPushButton::clicked, this, &Location::sCreateRoom);
	connect(mWidget.get(), &Widget::clearAllRfids,
			[this]
			{
				mIdxRfids = 0;
			});
}

void Location::sCreateRoom()
{
	mWidget->setSize(ui.SpinWRoom->value(), ui.SpinHRoom->value());
}

void Location::sColorRfid()
{
	mColorRfid = QColorDialog::getRgba();
	ui.BtnColorRfid->setStyleSheet(
		"QPushButton"
		"{"
		"background-color: " + QColor::fromRgba(mColorRfid).name() + ""
		"}"
	);
}
void Location::sColorWall()
{
	mColorWall = QColorDialog::getRgba();
	ui.BtnColorWall->setStyleSheet(
		"QPushButton"
		"{"
		"background-color: " + QColor::fromRgba(mColorWall).name() + ""
		"}"
	);
}

void Location::sAddWall()
{
	int w{ ui.SpinWWall->value() };
	int h{ ui.SpinHWall->value() };


	mWidget->addWall(w, h, mColorWall);
}

void Location::sAddRfid()
{
	if (mIdxRfids >= 10)
	{
		QMessageBox::warning(this, "Внимание", "Максимальное количествао меток 10");
		return;
	}
	mIdxRfids++;
	int rfid{ ui.SpinRadiusRfid->value() };

	mWidget->addRfid(rfid, mColorRfid);
}
