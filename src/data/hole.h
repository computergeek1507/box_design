#pragma once

#include <QGraphicsRectItem>

#include <nlohmann/json.hpp>

struct Hole
{
	Hole(int x, int y, int diameter)
		: x(x)
		, y(y)
		, diameter(diameter)
	{
	}

	Hole(nlohmann::json const& json)
	{
		x = json["x"];
		y = json["y"];
		diameter = json["diameter"];
	}
	int x;
	int y;
	int diameter;
};

struct HoleQGraphics : public QGraphicsRectItem
{
	HoleQGraphics(Hole* hole, QGraphicsItem* parent = nullptr)
		: QGraphicsRectItem(parent), m_hole(hole)
	{
		setRect(0, 0, 10, 10);
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