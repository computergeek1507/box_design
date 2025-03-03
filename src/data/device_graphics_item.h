#include "device.h"

#include <QGraphicsRectItem>
#include <QPixmap>
#include <QImage>
#include <QPainter>

struct DeviceGraphicsItem : public QGraphicsRectItem
{
	DeviceGraphicsItem(Device* device, QGraphicsItem* parent = nullptr)
		: QGraphicsRectItem(parent), m_device(device)
	{
		setRect(0, 0, m_device->width, m_device->height);
		//setBrush(Qt::black);
		setFlag(QGraphicsItem::ItemIsMovable);
		setFlag(QGraphicsItem::ItemIsSelectable);

		if (!device->image.empty())
		{
			QImage image(device->image.c_str());
			if (!image.isNull())
			{
				m_pixmap.convertFromImage(image, Qt::OrderedAlphaDither);
			}
		}
	}

protected:
	void mousePressEvent(QGraphicsSceneMouseEvent* event) override
	{
		//if (event->button() == Qt::RightButton)
		//{
		//	delete this;
		//}
	}

	virtual void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget*);
private:
	Device* m_device;
	QPixmap m_pixmap;
};