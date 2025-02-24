#include "BoxGraphicsScene.h"


#include <QGraphicsSceneDragDropEvent>
#include <QMimeData>
#include <QStandardItem>
#include <QTreeWidgetItem>

BoxGraphicsScene::BoxGraphicsScene(  QObject* parent ):
m_dragItem( nullptr ),
QGraphicsScene( parent )
{

}

BoxGraphicsScene::~BoxGraphicsScene()
{

}

void BoxGraphicsScene::mousePressEvent( QGraphicsSceneMouseEvent* mouseEvent )
{
	QGraphicsScene::mousePressEvent( mouseEvent );
}

void BoxGraphicsScene::dragEnterEvent( QGraphicsSceneDragDropEvent* event )
{
	//event->ignore();

	if( m_dragItem )
	{
		m_dragItem->setPos( event->scenePos() );
		this->addItem( m_dragItem );
		update();
	}
}

void BoxGraphicsScene::dragLeaveEvent( QGraphicsSceneDragDropEvent* event )
{
	
}

void BoxGraphicsScene::dragMoveEvent( QGraphicsSceneDragDropEvent* event )
{
	
}

void BoxGraphicsScene::dropEvent( QGraphicsSceneDragDropEvent* event )
{

}