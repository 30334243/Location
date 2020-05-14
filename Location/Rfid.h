#pragma once

class Rfid : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    explicit Rfid(QObject *parent = 0);
    ~Rfid();

    void setRadius(const int& r);
    void setColor(const QRgb& c);

signals:
	void toDelete(Rfid*);

private:
    int mRadius{ 50 };
    QRgb mColor;
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

public slots:
};
