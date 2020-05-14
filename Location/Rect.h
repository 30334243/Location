#pragma once
#include "Rfid.h"
#include "Wall.h"
class Rect : public QObject, public QGraphicsItem
{
	Q_OBJECT
public:
	explicit Rect(QObject* parent = 0);
	~Rect();

signals:
	void playSound(const std::vector<Rfid*>&);
private slots:
	void slotGameTimer(); // Слот, который отвечает за обработку перемещения треугольника

protected:
	void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget);

private:
	qreal mAngle; 
	QPointF mTarget;
	std::unique_ptr<QTimer> mTimer;

	QRectF boundingRect() const;
	QPainterPath shape()const;

	const int SIZE_RECT{ 20 };

};