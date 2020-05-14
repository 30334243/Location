#pragma once

class Wall : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    explicit Wall(QObject *parent = 0);
    ~Wall();

    void setSize(const int& w, const int& h);
    void setColor(const QRgb& color);

signals:
	void toDelete(Wall*);

private:
    int mW;
	int mH;
    QRgb mColor;
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

public slots:
};
