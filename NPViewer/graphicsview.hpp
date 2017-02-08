#ifndef GRAPHICSVIEW_HPP
#define GRAPHICSVIEW_HPP

#include <QGraphicsView>
#include <qevent.h>
#include "polyhedron.h"

class GraphicsView : public QGraphicsView
{
	Q_OBJECT
public:
	GraphicsView(QWidget *parent = 0);
	//void Paint(Polygon a, bool screen = 0);

protected:
	void wheelEvent(QWheelEvent *event);
	void scaleView(qreal scaleFactor);
};

#endif