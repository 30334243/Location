#include <Header.h>
#include "Rect.h"

static const double Pi = 3.14159265358979323846264338327950288419717;
static double TwoPi = 2.0 * Pi;
static qreal normalizeAngle(qreal angle)
{
	while (angle < 0)
		angle += TwoPi;
	while (angle > TwoPi)
		angle -= TwoPi;
	return angle;
}

Rect::Rect(QObject* parent) :
	QObject(parent),
	QGraphicsItem(),
	mTarget{ QPointF{ 0, 0 } },
	mAngle{ 0 }
{
	mTimer = std::make_unique<QTimer>();
	connect(mTimer.get(), &QTimer::timeout, this, &Rect::slotGameTimer);
	mTimer->start(10);
	setRotation(mAngle);
}

Rect::~Rect()
{

}

QRectF Rect::boundingRect() const
{
	return QRectF(0, 0, SIZE_RECT, SIZE_RECT);
}

QPainterPath Rect::shape() const
{
	QPainterPath path;
	path.addEllipse(boundingRect());
	return path;
}

void Rect::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
	painter->setBrush(Qt::red);
	painter->drawRect(0, 0, SIZE_RECT, SIZE_RECT);
	Q_UNUSED(option);
	Q_UNUSED(widget);
}

void Rect::slotGameTimer()
{

	if (GetAsyncKeyState(VK_LEFT))
	{
		this->setX(this->x() - 1);
		QList<QGraphicsItem*> items = scene()->collidingItems(this);
		bool state{ false };
		std::vector<Rfid*> rfids;
		for (const auto& item : items)
		{
			if (dynamic_cast<Wall*>(item))
			{
				state = true;
			}
			else if (auto rfid{ dynamic_cast<Rfid*>(item) };
					 rfid != nullptr)
			{
				rfids.push_back(rfid);
			}
			else
			{
				state = true;
			}
		}
		state ? this->setX(this->x() + 1) : emit playSound(rfids);
	}
	if (GetAsyncKeyState(VK_RIGHT))
	{
		this->setX(this->x() + 1);
		QList<QGraphicsItem*> items = scene()->collidingItems(this);
		bool state{ false };
		std::vector<Rfid*> rfids;
		for (const auto& item : items)
		{
			if (dynamic_cast<Wall*>(item))
			{
				state = true;
			}
			else if (auto rfid{ dynamic_cast<Rfid*>(item) };
					 rfid != nullptr)
			{
				rfids.push_back(rfid);
			}
			else
			{
				state = true;
			}
		}
		state ? this->setX(this->x() - 1) : emit playSound(rfids);
	}
	if (GetAsyncKeyState(VK_UP))
	{
		this->setY(this->y() - 1);
		QList<QGraphicsItem*> items = scene()->collidingItems(this);
		bool state{ false };
		std::vector<Rfid*> rfids;
		for (const auto& item : items)
		{
			if (dynamic_cast<Wall*>(item))
			{
				state = true;
			}
			else if (auto rfid{ dynamic_cast<Rfid*>(item) };
					 rfid != nullptr)
			{
				rfids.push_back(rfid);
			}
			else
			{
				state = true;
			}
		}
		state ? this->setY(this->y() + 1) : emit playSound(rfids);
	}
	if (GetAsyncKeyState(VK_DOWN))
	{
		this->setY(this->y() + 1);
		QList<QGraphicsItem*> items = scene()->collidingItems(this);
		if (!items.isEmpty())
		{
			bool state{ false };
			std::vector<Rfid*> rfids;
			for (const auto& item : items)
			{
				if (dynamic_cast<Wall*>(item))
				{
					state = true;
				}
				else if (auto rfid{ dynamic_cast<Rfid*>(item) };
						 rfid != nullptr)
				{
					rfids.push_back(rfid);
				}
				else
				{
					state = true;
				}
			}
			state ? this->setY(this->y() - 1) : emit playSound(rfids);
		}
	}
}