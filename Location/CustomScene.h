#pragma once
class CustomScene : public QGraphicsScene
{
	Q_OBJECT
public:
	explicit CustomScene(QObject* parent = 0);
	~CustomScene();

signals:
	// Сигнал для передачи координат положения курсора мыши
	//void signalTargetCoordinate(QPointF point);

public slots:

private:
	// Функция, в которой производится отслеживание положения мыши
	//void mouseMoveEvent(QGraphicsSceneMouseEvent* event);
};