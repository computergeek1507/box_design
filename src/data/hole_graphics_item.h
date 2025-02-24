#pragma once

#include <QGraphicsRectItem>

#include "hole.h"


struct HoleGraphicsItem : public QGraphicsEllipseItem
{
	HoleGraphicsItem(Hole* hole, QGraphicsItem* parent = nullptr)
		: QGraphicsEllipseItem(parent), m_hole(hole)
	{
		setRect(0, 0, m_hole->diameter, m_hole->diameter);
		//setBrush(Qt::black);
		setFlag(QGraphicsItem::ItemIsMovable);
		setFlag(QGraphicsItem::ItemIsSelectable);
	}

protected:
	void mousePressEvent(QGraphicsSceneMouseEvent* event) override
	{
		//if (event->button() == Qt::RightButton)
		//{
		//	delete this;
		//}
	}
private:
	Hole* m_hole;
};