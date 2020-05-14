#pragma once
#include "Rect.h"
#include "Wall.h"
#include "Rfid.h"
namespace Ui
{
	class Widget;
}

class Widget : public QWidget
{
	Q_OBJECT
public:
	explicit Widget(QWidget* parent = 0, const int& w = 600, const int& h = 600);
	~Widget();

	void setSize(const int& w, const int& h);
	void addWall(const int& w, const int& h, const QRgb& color);
	void removeWall(Wall* item);
	void addRfid(const int& r, const QRgb& color);
	void removeRfid(Rfid* item);
private:
	Ui::Widget* ui;
	std::unique_ptr<QGraphicsScene> mScene;
	std::unique_ptr<Rect> mTriangle;

	const std::vector<QUrl> mSounds{
		QUrl{ "qrc:/Location/sound/1.wav" },
		QUrl{ "qrc:/Location/sound/2.wav" },
		QUrl{ "qrc:/Location/sound/3.wav" },
		QUrl{ "qrc:/Location/sound/4.wav" },
		QUrl{ "qrc:/Location/sound/5.wav" },
		QUrl{ "qrc:/Location/sound/6.wav" },
		QUrl{ "qrc:/Location/sound/7.wav" },
		QUrl{ "qrc:/Location/sound/8.wav" },
		QUrl{ "qrc:/Location/sound/9.wav" },
		QUrl{ "qrc:/Location/sound/10.wav" }
	};

	std::vector<std::pair<QMediaPlayer*, QMediaPlaylist*>> mPSound;

	const int WIDTH_WALL{ 10 };
	const QString COLOR_WALL{ "#aa5500" };

	QList<QGraphicsItem*> mWalls;

	std::atomic<int> mIdxRfids{ 0 };
	std::unordered_map<Rfid*, int> mRfids;
public slots:
	void sPlayRfids(const std::vector<Rfid*>&);
signals:
	void removedRfid();
	void clearAllRfids();
};