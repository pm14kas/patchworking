#include "graphicsview.hpp"

GraphicsView::GraphicsView(QWidget *parent)
	: QGraphicsView(parent)
{
	setFixedSize(parent->size());
	setMouseTracking(true);
	setCacheMode(CacheBackground);
	setRenderHint(QPainter::Antialiasing);

	setViewportUpdateMode(BoundingRectViewportUpdate);
	setDragMode(QGraphicsView::DragMode::ScrollHandDrag);
	setTransformationAnchor(AnchorUnderMouse);
	translate(size().width() / 2, size().height() / 2);
}

void GraphicsView::wheelEvent(QWheelEvent *event)
{
	scaleView(pow((double)2, event->delta() / 240.0));
}


void GraphicsView::scaleView(qreal scaleFactor)
{
	qreal factor = transform().scale(scaleFactor, scaleFactor).mapRect(QRectF(0, 0, 1, 1)).width();
	if (factor < 0.07 || factor > 100)
		return;

	scale(scaleFactor, scaleFactor);
}
