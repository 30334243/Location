#pragma once
class CustomScene : public QGraphicsScene
{
	Q_OBJECT
public:
	explicit CustomScene(QObject* parent = 0);
	~CustomScene();

signals:
	// ������ ��� �������� ��������� ��������� ������� ����
	//void signalTargetCoordinate(QPointF point);

public slots:

private:
	// �������, � ������� ������������ ������������ ��������� ����
	//void mouseMoveEvent(QGraphicsSceneMouseEvent* event);
};