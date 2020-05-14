#pragma once
#include <Header.h>

#include "Rfid.h"

Rfid::Rfid(QObject* parent) :
	QObject(parent), QGraphicsItem()
{

}

Rfid::~Rfid()
{

}

void Rfid::setRadius(const int& r)
{
	mRadius = r;
}

void Rfid::setColor(const QRgb& c)
{
	mColor = c;
}

QRectF Rfid::boundingRect() const
{
	return QRectF(-(mRadius / 2), -(mRadius / 2), mRadius, mRadius);
}

void Rfid::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
	painter->setPen(QColor{ 1, 1, 1, 0 });
	painter->setBrush(QBrush{ QColor::fromRgba(mColor) });
	painter->drawEllipse(-(mRadius / 2), -(mRadius / 2), mRadius, mRadius);
	Q_UNUSED(option);
	Q_UNUSED(widget);
}

void Rfid::mouseMoveEvent(QGraphicsSceneMouseEvent* event)
{
	this->setPos(mapToScene(event->pos()));
}

void Rfid::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
	if (event->button() == Qt::RightButton)
	{
		emit toDelete(this);
	}

	this->setCursor(QCursor(Qt::ClosedHandCursor));
	Q_UNUSED(event);
}

void Rfid::mouseReleaseEvent(QGraphicsSceneMouseEvent* event)
{
	this->setCursor(QCursor(Qt::ArrowCursor));
	Q_UNUSED(event);
}
