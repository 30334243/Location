#pragma once
#include <Header.h>

#include "Wall.h"

Wall::Wall(QObject* parent) :
	QObject(parent), QGraphicsItem()
{

}

Wall::~Wall()
{

}

void Wall::setColor(const QRgb& color)
{
	mColor = color;
}

void Wall::setSize(const int& w, const int& h)
{
	mW = w;
	mH = h;
}

QRectF Wall::boundingRect() const
{
	return QRectF(-mW / 2, -mH / 2, mW, mH);
}

void Wall::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
	painter->setPen(QColor{ 1, 1, 1, 0 });
	painter->setBrush(QBrush{ QColor::fromRgba(mColor) });
	painter->drawRect(-mW / 2, -mH / 2, mW, mH);
	Q_UNUSED(option);
	Q_UNUSED(widget);
}

void Wall::mouseMoveEvent(QGraphicsSceneMouseEvent* event)
{
	/* Устанавливаем позицию графического элемента
	 * в графической сцене, транслировав координаты
	 * курсора внутри графического элемента
	 * в координатную систему графической сцены
	 * */
	this->setPos(mapToScene(event->pos()));
}

void Wall::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
	/* При нажатии мышью на графический элемент
	 * заменяем курсор на руку, которая держит этот элемента
	 * */

	if (event->button() == Qt::RightButton)
	{
		emit toDelete(this);
	}

	this->setCursor(QCursor(Qt::ClosedHandCursor));
	Q_UNUSED(event);
}

void Wall::mouseReleaseEvent(QGraphicsSceneMouseEvent* event)
{
	/* При отпускании мышью элемента
	 * заменяем на обычный курсор стрелку
	 * */
	this->setCursor(QCursor(Qt::ArrowCursor));
	Q_UNUSED(event);
}
