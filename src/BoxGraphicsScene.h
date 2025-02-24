#pragma once

#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QString>
#include <QPointF>

class BoxGraphicsScene : public QGraphicsScene
{
public:
	BoxGraphicsScene(  QObject* parent = 0 );

	virtual ~BoxGraphicsScene();

protected:

	virtual void mousePressEvent( QGraphicsSceneMouseEvent* mouseEvent );

	//Drag and drop events
	virtual void dragEnterEvent( QGraphicsSceneDragDropEvent* event );
	virtual void dragLeaveEvent( QGraphicsSceneDragDropEvent* event );
	virtual void dragMoveEvent( QGraphicsSceneDragDropEvent* event );
	virtual void dropEvent( QGraphicsSceneDragDropEvent* event );
	
	QGraphicsItem* m_dragItem;
};