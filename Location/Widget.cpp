#pragma  once
#include <Header.h>
#include "widget.h"
#include "ui_widget.h"

#include <Random.hpp>

Widget::Widget(QWidget* parent, const int& w, const int& h) :
	QWidget(parent),
	ui(new Ui::Widget)
{
	ui->setupUi(this);
	this->resize(w, h);
	this->setFixedSize(w, h);

	mScene = std::make_unique<QGraphicsScene>();
	mTriangle = std::make_unique<Rect>();

	ui->graphicsView->setScene(mScene.get());
	ui->graphicsView->setRenderHint(QPainter::Antialiasing);
	ui->graphicsView->setCacheMode(QGraphicsView::CacheBackground);
	ui->graphicsView->setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);
	ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

	mScene->setSceneRect(0, 0, w - 30, h - 30);

	mScene->addRect(0, 0, WIDTH_WALL, h - 30, QPen(Qt::NoPen), QBrush(QColor{ COLOR_WALL }));
	mScene->addRect(0, 0, w - 30, WIDTH_WALL, QPen(Qt::NoPen), QBrush(QColor{ COLOR_WALL }));
	mScene->addRect(0, w - 40, w - 30, WIDTH_WALL, QPen(Qt::NoPen), QBrush(QColor{ COLOR_WALL }));
	mScene->addRect(w - 40, 0, WIDTH_WALL, h - 30, QPen(Qt::NoPen), QBrush(QColor{ COLOR_WALL }));

	mScene->addItem(mTriangle.get());
	mTriangle->setPos(w / 2, h / 2);
	ui->graphicsView->setMouseTracking(true);

	for (const auto& elm : ranges::views::iota(0, 10)
		 | ranges::views::transform(
			 [this](const auto& idx)
			 {
				 QMediaPlayer* m_player = new QMediaPlayer(this);
				 QMediaPlaylist* m_playlist = new QMediaPlaylist(m_player);
				 m_player->setPlaylist(m_playlist);
				 m_playlist->addMedia(mSounds[idx]);
				 return std::pair(m_player, m_playlist);
			 }
		 )
		 )
	{
		mPSound.push_back(elm);
	}
			 connect(mTriangle.get(), &Rect::playSound, this, &Widget::sPlayRfids);
}

Widget::~Widget()
{
	delete ui;
}

void Widget::setSize(const int& w, const int& h)
{
	this->resize(w, h);
	this->setFixedSize(w, h);

	mIdxRfids = 0;
	mScene->clear();
	mScene.release();
	mTriangle.release();
	mRfids.clear();
	emit clearAllRfids();

	mScene = std::make_unique<QGraphicsScene>();
	mTriangle = std::make_unique<Rect>();

	ui->graphicsView->setScene(mScene.get());
	ui->graphicsView->setRenderHint(QPainter::Antialiasing);
	ui->graphicsView->setCacheMode(QGraphicsView::CacheBackground);
	ui->graphicsView->setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);
	ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

	mScene->setSceneRect(0, 0, w - 30, h - 30);

	mScene->addRect(0, 0, WIDTH_WALL, h - 30, QPen(Qt::NoPen), QBrush(QColor{ COLOR_WALL }));
	mScene->addRect(0, 0, w - 30, WIDTH_WALL, QPen(Qt::NoPen), QBrush(QColor{ COLOR_WALL }));
	mScene->addRect(0, h - 40, w - 30, WIDTH_WALL, QPen(Qt::NoPen), QBrush(QColor{ COLOR_WALL }));
	mScene->addRect(w - 40, 0, WIDTH_WALL, h - 30, QPen(Qt::NoPen), QBrush(QColor{ COLOR_WALL }));

	mScene->addItem(mTriangle.get());
	mTriangle->setPos(w / 2, h / 2);
	ui->graphicsView->setMouseTracking(true);

	for (const auto& elm : ranges::views::iota(0, 10)
		 | ranges::views::transform(
			 [this](const auto& idx)
			 {
				 QMediaPlayer* m_player = new QMediaPlayer(this);
				 QMediaPlaylist* m_playlist = new QMediaPlaylist(m_player);
				 m_player->setPlaylist(m_playlist);
				 m_playlist->addMedia(mSounds[idx]);
				 return std::pair(m_player, m_playlist);
			 }
		 )
		 )
	{
		mPSound.push_back(elm);
	}

			 connect(mTriangle.get(), &Rect::playSound, this, &Widget::sPlayRfids);
}

void Widget::sPlayRfids(const std::vector<Rfid*>& rfids)
{
	mPSound[0].first->setVolume(100);
	for (const auto& rfid : rfids)
	{
		int idx{ mRfids.at(rfid) };
		mPSound[idx].first->play();
	}
}

void Widget::addWall(const int& w, const int& h,const QRgb& color)
{
	int rx{ random::generate<std::uniform_int_distribution, int>(0, this->width() - 100) };
	int ry{ random::generate<std::uniform_int_distribution, int>(0, this->height() - 100) };

	Wall* item = new Wall();
	item->setSize(w, h);
	item->setPos(rx, ry);
	item->setColor(color);
	mScene->addItem(item);

	mWalls.append(item);

	connect(item, &Wall::toDelete, this, &Widget::removeWall);
}

void Widget::removeWall(Wall* item)
{
	mScene->removeItem(item);
	mWalls.removeOne(item);
}

void Widget::addRfid(const int& radius, const QRgb& color)
{
	int rx{ random::generate<std::uniform_int_distribution, int>(0, this->width() - 100) };
	int ry{ random::generate<std::uniform_int_distribution, int>(0, this->height() - 100) };

	Rfid* item = new Rfid;
	item->setRadius(radius);
	item->setColor(color);
	item->setPos(rx, ry);
	mScene->addItem(item);

	for (auto& rfid : mRfids)
	{
		rfid.second == mIdxRfids ? ++mIdxRfids : 0;
	}

	mRfids.insert(std::make_pair(item, mIdxRfids++));

	connect(item, &Rfid::toDelete, this, &Widget::removeRfid);
}

void Widget::removeRfid(Rfid* item)
{
	mScene->removeItem(item);
	mRfids.erase(item);
	--mIdxRfids;
	--mIdxRfids;
	
	emit removedRfid();
}