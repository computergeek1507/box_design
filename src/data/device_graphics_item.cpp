
#include "device_graphics_item.h"

void DeviceGraphicsItem::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget*)
{
	if (!m_pixmap.isNull())
	{
		painter->drawPixmap(boundingRect(), m_pixmap, m_pixmap.rect());
	}
}