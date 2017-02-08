#ifndef NPVIEWER_H
#define NPVIEWER_H

#include <QtWidgets/QMainWindow>
#include <qgraphicsview.h>
#include <qmenubar.h>
#include <qtoolbar.h>
#include <qtoolbutton.h>
#include <qpainter.h>
#include <qfiledialog.h>
#include <qmessagebox.h>
#include <qgraphicsscene.h>

#include "newpolygondialog.hpp"
#include "helpwidget.hpp"
#include "polyhedron.h"
#include "graphicsview.hpp"


class NPViewer : public QMainWindow
{
	Q_OBJECT

public:
	NPViewer(QWidget *parent = 0);
	~NPViewer();
	void DrawPolygon(bool screen = false);

private:
	Polygon poly;
	QString pathTriangulation;
	QString pathVertex;
	bool screen;
	bool refresh;
	newPolygonDialog* polygonDialog;
	HelpWidget* helpWidget;


	GraphicsView* graphicsView;
	QToolBar* toolBar;
		QAction* buttonNew;
		QAction* buttonLoadVertex;
		QAction* buttonLoadTriangulation;
		QAction* buttonReload;
		QAction* buttonRandom;
	QMenu* menuFile;
		QAction* actionNew;
		QAction* actionLoadVertex;
		QAction* actionLoadTriangulation;
		QAction* actionSaveVertex;
		QAction* actionSaveTriangulation;
		QAction* actionScreenshot;
		QAction* actionExit;
	QMenu* menuEdit;
		QAction* actionNewPolygon;
		QAction* actionInvert;
		QMenu* menuFill;
			QAction* actionFillXOR;
			QAction* actionFillRandom;
			QAction* actionFillALLPLUS;
			QAction* actionFillALLMINUS;
		
		QMenu* menuTriangulation;
			QAction* actionSimpleTriangulation;
	QMenu* menuHelp;
		QAction* actionAbout;
		QAction* actionHelp;

	QLabel* polyDegree;
	QGraphicsScene *render;
protected:
	void resizeEvent(QResizeEvent *);




public slots:
	void loadVertexFromFile();
	void loadTriangulationFromFile();
	void saveVertexToFile();
	void saveTriangulationToFile();

	void reload();

	void newPoly(int value);
	void polyForm();

	void fillXOR();
	void fillRAND();
	void fillPLUS();
	void fillMINUS();

	void invert();

	void triangulateSimple();
	void screenshot();

	void showAbout();
	void showHelp();
signals:
	void fillPoly(char value);
};

#endif // NPVIEWER_H
