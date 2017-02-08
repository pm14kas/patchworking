#include "npviewer.hpp"

NPViewer::NPViewer(QWidget *parent)
	: QMainWindow(parent)
{
	this->setMinimumSize(QSize(640, 480));
	this->setWindowIcon(QIcon(":/NPViewer/Resources/icon_main.png"));
	graphicsView = new GraphicsView(this);
	render = new QGraphicsScene(graphicsView);
	menuFile = menuBar()->addMenu(QString::fromLocal8Bit("&Файл"));
	actionNewPolygon = menuFile->addAction(QString::fromLocal8Bit("Новый полигон"));
	menuFile->addSeparator();
	actionLoadVertex = menuFile->addAction(QString::fromLocal8Bit("Загрузить сетку вершин"));
	actionLoadTriangulation = menuFile->addAction(QString::fromLocal8Bit("Загрузить триангуляцию"));
	menuFile->addSeparator();
	actionSaveVertex = menuFile->addAction(QString::fromLocal8Bit("Сохранить сетку вершин"));
	actionSaveTriangulation = menuFile->addAction(QString::fromLocal8Bit("Сохранить триангуляцию"));
	menuFile->addSeparator();
	actionScreenshot = menuFile->addAction(QString::fromLocal8Bit("Скриншот"));
	menuFile->addSeparator();
	actionExit = menuFile->addAction(QString::fromLocal8Bit("Выход"));

	menuEdit = menuBar()->addMenu(QString::fromLocal8Bit("&Правка"));
	actionInvert = menuEdit->addAction(QString::fromLocal8Bit("Инверсия вершин"));
	menuEdit->addSeparator();
	menuFill = menuEdit->addMenu(QString::fromLocal8Bit("Заполнить..."));
	actionFillXOR = menuFill->addAction(QString::fromLocal8Bit("Паттерн XOR"));
	actionFillRandom = menuFill->addAction(QString::fromLocal8Bit("Случайный паттерн"));
	actionFillALLPLUS = menuFill->addAction(QString::fromLocal8Bit("Паттерн \"+\""));
	actionFillALLMINUS = menuFill->addAction(QString::fromLocal8Bit("Паттерн \"-\""));
	menuTriangulation = menuEdit->addMenu(QString::fromLocal8Bit("Триангуляция"));
	actionSimpleTriangulation = menuTriangulation->addAction(QString::fromLocal8Bit("Простая триангуляция"));

	menuHelp = menuBar()->addMenu(QString::fromLocal8Bit("&Справка"));
	actionAbout = menuHelp->addAction(QString::fromLocal8Bit("О программе"));
	menuHelp->addSeparator();
	actionHelp = menuHelp->addAction(QString::fromLocal8Bit("Справка"));

	toolBar = addToolBar(QString::fromLocal8Bit("Панель управления"));
	buttonNew = toolBar->addAction(QIcon(":/NPViewer/Resources/icon_new.png"), QString::fromLocal8Bit("Новый файл"));
	toolBar->addSeparator();
	buttonLoadVertex = toolBar->addAction(QIcon(":/NPViewer/Resources/icon_load_vertex.png"),QString::fromLocal8Bit("Загрузить сетку вершин"));
	buttonLoadTriangulation = toolBar->addAction(QIcon(":/NPViewer/Resources/icon_load_triangulation.png"),QString::fromLocal8Bit("Загрузить триангуляцию"));
	buttonReload = toolBar->addAction(QIcon(":/NPViewer/Resources/icon_reload.png"), QString::fromLocal8Bit("Обновить"));
	toolBar->addSeparator();
	buttonRandom = toolBar->addAction(QIcon(":/NPViewer/Resources/icon_random.png"),QString::fromLocal8Bit("Сгенерировать вершины"));


	polyDegree = new QLabel(this);


	connect(actionLoadVertex, SIGNAL(triggered()), this, SLOT(loadVertexFromFile()));
	connect(actionLoadTriangulation, SIGNAL(triggered()), this, SLOT(loadTriangulationFromFile()));
	connect(actionSaveVertex, SIGNAL(triggered()), this, SLOT(saveVertexToFile()));
	connect(actionSaveTriangulation, SIGNAL(triggered()), this, SLOT(saveTriangulationToFile()));
	connect(actionScreenshot, SIGNAL(triggered()), this, SLOT(screenshot()));
	connect(actionExit, SIGNAL(triggered()), this, SLOT(close()));

	connect(actionFillXOR, SIGNAL(triggered()), this, SLOT(fillXOR()));
	connect(actionFillRandom, SIGNAL(triggered()), this, SLOT(fillRAND()));
	connect(actionFillALLPLUS, SIGNAL(triggered()), this, SLOT(fillPLUS()));
	connect(actionFillALLMINUS, SIGNAL(triggered()), this, SLOT(fillMINUS()));

	connect(actionInvert, SIGNAL(triggered()), this, SLOT(invert()));

	connect(actionSimpleTriangulation, SIGNAL(triggered()), this, SLOT(triangulateSimple()));

	connect(actionNewPolygon, SIGNAL(triggered()), this, SLOT(polyForm()));

	connect(actionAbout, SIGNAL(triggered()), this, SLOT(showAbout()));
	connect(actionHelp, SIGNAL(triggered()), this, SLOT(showHelp()));

	connect(buttonNew, SIGNAL(triggered()), this, SLOT(polyForm()));
	connect(buttonLoadVertex, SIGNAL(triggered()), this, SLOT(loadVertexFromFile()));
	connect(buttonLoadTriangulation, SIGNAL(triggered()), this, SLOT(loadTriangulationFromFile()));
	connect(buttonReload, SIGNAL(triggered()), this, SLOT(reload()));
	connect(buttonRandom, SIGNAL(triggered()), this, SLOT(fillRAND()));

}

NPViewer::~NPViewer()
{
	/*delete graphicsView;
	delete menuFile;
	delete actionLoadVertex;
	delete actionLoadTriangulation;
	delete actionSaveVertex;
	delete actionSaveTriangulation;
	delete actionScreenshot;
	delete actionExit;
	delete menuEdit;
	delete actionNewPolygon;
	delete menuFill;
	delete actionFillXOR;
	delete actionFillRandom;
	delete actionFillALLPLUS;
	delete actionFillALLMINUS;
	delete menuTriangulation;
	delete actionSimpleTriangulation;
	delete menuHelp;
	delete actionAbout;
	delete actionHelp;

	delete polyDegree;*/
}


void NPViewer::resizeEvent(QResizeEvent *)
{
	
	polyDegree->setGeometry(0, this->size().height() - 20, 100, 20);
	graphicsView->setGeometry(0, 20 + toolBar->size().height(), this->size().width(), (this->size().height()));
	graphicsView->setFixedSize(this->size() - QSize(0, 70));
}


void NPViewer::DrawPolygon(bool screen)
{
	const int radius = 14;
	const int distance = 30;
	QString polygondegree;
	polygondegree.setNum(poly.GetDegree());
	polyDegree->setText(QString::fromLocal8Bit("Степень: ") +  polygondegree);
	render->clear();
	//render = new QGraphicsScene(graphicsView);

	QPen graypen(Qt::darkGray);
	QPen emptypen(Qt::transparent);
	QPen blackpen(Qt::black, 2, Qt::SolidLine, Qt::PenCapStyle::RoundCap, Qt::RoundJoin);
	QBrush brush(Qt::white);
	QBrush graybrush(QColor(204,204,204));
	QFont arial("Arial");
	int size = (poly.GetDegree() * 2) - 1;




	/*for (int i = -poly.GetDegree(); i < poly.GetDegree(); i++)
	{
		for (int j = -poly.GetDegree() + abs(i); j < poly.GetDegree() - abs(i); j++)
		{
			std::vector<Polygon::Triangle> mesh = poly.GetMeshForVertex(poly(abs(i), abs(j)));
			for (int k = 0; k < mesh.size(); k++)// each (Polygon::Triangle k in mesh)
			{
				bool pass = false;
				for (int p = 0; p < k; p++)
					if (mesh[k] == mesh[p]){ pass = true; break; }
				if (pass) continue;

				if ((mesh[k].v1 > poly.Sum(poly.GetDegree())) || (mesh[k].v2>poly.Sum(poly.GetDegree())) || (mesh[k].v3>poly.Sum(poly.GetDegree())))
					continue;

				int x1 = poly.ConvertIndex(mesh[k].v1).x;
				int x2 = poly.ConvertIndex(mesh[k].v2).x;
				int x3 = poly.ConvertIndex(mesh[k].v3).x;
				int y1 = poly.ConvertIndex(mesh[k].v1).y;
				int y2 = poly.ConvertIndex(mesh[k].v2).y;
				int y3 = poly.ConvertIndex(mesh[k].v3).y;
				int is, js;

				if ((i == 0) && (j == 0))///начало костыля
				{
					is = -1;
					js = -1;
				}
				else
				{
					is = (i < 0 ? -1 : 1);
					js = (j < 0 ? -1 : 1);
				}                          ///конец костыля

				x1 *= is;
				x2 *= is;
				x3 *= is;
				y1 *= js;
				y2 *= js;
				y3 *= js;



				Polygon::Vector v1(y1, x1);
				Polygon::Vector v2(y2, x2);
				Polygon::Vector v3(y3, x3);

				x1 = x1 * distance + radius / 2;
				y1 = -y1 * distance + radius / 2;
				x2 = x2 * distance + radius / 2;
				y2 = -y2 * distance + radius / 2;
				x3 = x3 * distance + radius / 2;
				y3 = -y3 * distance + radius / 2;

				render->addLine(x1, y1, x2, y2, graypen);
				render->addLine(x2, y2, x3, y3, graypen);
				render->addLine(x3, y3, x1, y1, graypen);


				QPolygon triangle;

				if ((poly.Get(v1.x, v1.y).value == poly.Get(v2.x, v2.y).value) && (poly.Get(v1.x, v1.y).value != poly.Get(v3.x, v3.y).value))
				{
					if (poly.Get(v3.x, v3.y).value == '-')
					{
						triangle << QPoint(x3, y3) << QPoint(x3 + (x2 - x3) / 2, y3 + (y2 - y3) / 2) << QPoint(x3 + (x1 - x3) / 2, y3 + (y1 - y3) / 2);
					}
					else if ((poly.Get(v1.x, v1.y).value == '-') && (poly.Get(v2.x, v2.y).value == '-'))
					{
							triangle << QPoint(x1, y1) << QPoint(x2, y2) << QPoint(x2 + (x3 - x2) / 2, y2 + (y3 - y2) / 2) << QPoint(x1 + (x3 - x1) / 2, y1 + (y3 - y1) / 2);
					}
					render->addLine(x2 + (x3 - x2) / 2, y2 + (y3 - y2) / 2, x1 + (x3 - x1) / 2, y1 + (y3 - y1) / 2, blackpen);
				}
				if ((poly.Get(v2.x, v2.y).value == poly.Get(v3.x, v3.y).value) && (poly.Get(v2.x, v2.y).value != poly.Get(v1.x, v1.y).value))
				{
					if (poly.Get(v1.x, v1.y).value == '-')
					{
						triangle << QPoint(x1, y1) << QPoint(x1 + (x2 - x1) / 2, y1 + (y2 - y1) / 2) << QPoint(x1 + (x3 - x1) / 2, y1 + (y3 - y1) / 2);
					}
					else if ((poly.Get(v2.x, v2.y).value == '-') && (poly.Get(v3.x, v3.y).value == '-'))
					{
							triangle << QPoint(x3, y3) << QPoint(x2, y2) << QPoint(x2 + (x1 - x2) / 2, y2 + (y1 - y2) / 2) << QPoint(x3 + (x1 - x3) / 2, y3 + (y1 - y3) / 2);
					}
					render->addLine(x2 + (x1 - x2) / 2, y2 + (y1 - y2) / 2, x3 + (x1 - x3) / 2, y3 + (y1 - y3) / 2, blackpen);
				}
				if ((poly.Get(v1.x, v1.y).value == poly.Get(v3.x, v3.y).value) && (poly.Get(v1.x, v1.y).value != poly.Get(v2.x, v2.y).value))
				{
					if (poly.Get(v2.x, v2.y).value == '-')
					{
						triangle << QPoint(x2, y2) << QPoint(x3 + (x2 - x3) / 2, y3 + (y2 - y3) / 2) << QPoint(x1 + (x2 - x1) / 2, y1 + (y2 - y1) / 2);
					}
					else if ((poly.Get(v1.x, v1.y).value == '-') && (poly.Get(v3.x, v3.y).value == '-'))
					{
							triangle << QPoint(x1, y1) << QPoint(x3, y3) << QPoint(x3 + (x2 - x3) / 2, y3 + (y2 - y3) / 2) << QPoint(x1 + (x2 - x1) / 2, y1 + (y2 - y1) / 2);
					}
					render->addLine(x1 + (x2 - x1) / 2, y1 + (y2 - y1) / 2, x3 + (x2 - x3) / 2, y3 + (y2 - y3) / 2, blackpen);
				}
				if ((poly.Get(v1.x, v1.y).value == poly.Get(v3.x, v3.y).value) && (poly.Get(v1.x, v1.y).value == poly.Get(v2.x, v2.y).value))
				{
					if (poly.Get(v1.x, v1.y).value == '-')
					{
						triangle << QPoint(x2, y2) << QPoint(x3, y3) << QPoint(x1, y1);
					}
				}
				render->addPolygon(triangle, emptypen, graybrush);

				if ((poly.Get(v1.x, v1.y).value == poly.Get(v2.x, v2.y).value) && (poly.Get(v1.x, v1.y).value != poly.Get(v3.x, v3.y).value))
				{
					render->addLine(x2 + (x3 - x2) / 2, y2 + (y3 - y2) / 2, x1 + (x3 - x1) / 2, y1 + (y3 - y1) / 2, blackpen);
				}
				if ((poly.Get(v2.x, v2.y).value == poly.Get(v3.x, v3.y).value) && (poly.Get(v2.x, v2.y).value != poly.Get(v1.x, v1.y).value))
				{
					render->addLine(x2 + (x1 - x2) / 2, y2 + (y1 - y2) / 2, x3 + (x1 - x3) / 2, y3 + (y1 - y3) / 2, blackpen);
				}
				if ((poly.Get(v1.x, v1.y).value == poly.Get(v3.x, v3.y).value) && (poly.Get(v1.x, v1.y).value != poly.Get(v2.x, v2.y).value))
				{
					render->addLine(x1 + (x2 - x1) / 2, y1 + (y2 - y1) / 2, x3 + (x2 - x3) / 2, y3 + (y2 - y3) / 2, blackpen);
				}

			}
		}
	}*/







for (int i = -poly.GetDegree(); i < poly.GetDegree(); i++)
{
	for (int j = -poly.GetDegree() + abs(i); j < poly.GetDegree() - abs(i); j++)
	{
		std::vector<Polygon::Triangle> mesh = poly.GetMeshForVertex(poly(abs(i), abs(j)));
		for (int k = 0; k < mesh.size(); k++)// each (Polygon::Triangle k in mesh)
		{
			bool pass = false;
			for (int p = 0; p < k; p++)
				if (mesh[k] == mesh[p]){ pass = true; break; }
			if (pass) continue;

			if ((mesh[k].v1 > poly.Sum(poly.GetDegree())) || (mesh[k].v2>poly.Sum(poly.GetDegree())) || (mesh[k].v3>poly.Sum(poly.GetDegree())))
				continue;

			int x1 = poly.ConvertIndex(mesh[k].v1).x;
			int x2 = poly.ConvertIndex(mesh[k].v2).x;
			int x3 = poly.ConvertIndex(mesh[k].v3).x;
			int y1 = poly.ConvertIndex(mesh[k].v1).y;
			int y2 = poly.ConvertIndex(mesh[k].v2).y;
			int y3 = poly.ConvertIndex(mesh[k].v3).y;
			int is, js;

			if ((i == 0) && (j == 0))///начало костыля
			{
				is = -1;
				js = -1;
			}
			else
			{
				is = (i < 0 ? -1 : 1);
				js = (j < 0 ? -1 : 1);
			}                          ///конец костыля

			x1 *= is;
			x2 *= is;
			x3 *= is;
			y1 *= js;
			y2 *= js;
			y3 *= js;



			Polygon::Vector v1(y1, x1);
			Polygon::Vector v2(y2, x2);
			Polygon::Vector v3(y3, x3);

			x1 = x1 * distance + radius / 2;
			y1 = -y1 * distance + radius / 2;
			x2 = x2 * distance + radius / 2;
			y2 = -y2 * distance + radius / 2;
			x3 = x3 * distance + radius / 2;
			y3 = -y3 * distance + radius / 2;



			QPolygon triangle;

			if ((poly.Get(v1.x, v1.y).value == poly.Get(v2.x, v2.y).value) && (poly.Get(v1.x, v1.y).value != poly.Get(v3.x, v3.y).value))
			{
				if (poly.Get(v3.x, v3.y).value == '-')
				{
					triangle << QPoint(x3, y3) << QPoint(x3 + (x2 - x3) / 2, y3 + (y2 - y3) / 2) << QPoint(x3 + (x1 - x3) / 2, y3 + (y1 - y3) / 2);
				}
				else if ((poly.Get(v1.x, v1.y).value == '-') && (poly.Get(v2.x, v2.y).value == '-'))
				{
					/**/	triangle << QPoint(x1, y1) << QPoint(x2, y2) << QPoint(x2 + (x3 - x2) / 2, y2 + (y3 - y2) / 2) << QPoint(x1 + (x3 - x1) / 2, y1 + (y3 - y1) / 2);
				}
			}
			if ((poly.Get(v2.x, v2.y).value == poly.Get(v3.x, v3.y).value) && (poly.Get(v2.x, v2.y).value != poly.Get(v1.x, v1.y).value))
			{
				if (poly.Get(v1.x, v1.y).value == '-')
				{
					triangle << QPoint(x1, y1) << QPoint(x1 + (x2 - x1) / 2, y1 + (y2 - y1) / 2) << QPoint(x1 + (x3 - x1) / 2, y1 + (y3 - y1) / 2);
				}
				else if ((poly.Get(v2.x, v2.y).value == '-') && (poly.Get(v3.x, v3.y).value == '-'))
				{
					/**/	triangle << QPoint(x3, y3) << QPoint(x2, y2) << QPoint(x2 + (x1 - x2) / 2, y2 + (y1 - y2) / 2) << QPoint(x3 + (x1 - x3) / 2, y3 + (y1 - y3) / 2);
				}
			}
			if ((poly.Get(v1.x, v1.y).value == poly.Get(v3.x, v3.y).value) && (poly.Get(v1.x, v1.y).value != poly.Get(v2.x, v2.y).value))
			{
				if (poly.Get(v2.x, v2.y).value == '-')
				{
					triangle << QPoint(x2, y2) << QPoint(x3 + (x2 - x3) / 2, y3 + (y2 - y3) / 2) << QPoint(x1 + (x2 - x1) / 2, y1 + (y2 - y1) / 2);
				}
				else if ((poly.Get(v1.x, v1.y).value == '-') && (poly.Get(v3.x, v3.y).value == '-'))
				{
					/**/	triangle << QPoint(x1, y1) << QPoint(x3, y3) << QPoint(x3 + (x2 - x3) / 2, y3 + (y2 - y3) / 2) << QPoint(x1 + (x2 - x1) / 2, y1 + (y2 - y1) / 2);
				}
			}
			if ((poly.Get(v1.x, v1.y).value == poly.Get(v3.x, v3.y).value) && (poly.Get(v1.x, v1.y).value == poly.Get(v2.x, v2.y).value))
			{
				if (poly.Get(v1.x, v1.y).value == '-')
				{
					triangle << QPoint(x2, y2) << QPoint(x3, y3) << QPoint(x1, y1);
				}
			}
			render->addPolygon(triangle, emptypen, graybrush);


		}
	}
}




	for (int i = -poly.GetDegree(); i < poly.GetDegree(); i++)
	{
		for (int j = -poly.GetDegree() + abs(i); j < poly.GetDegree() - abs(i); j++)
		{
			std::vector<Polygon::Triangle> mesh = poly.GetMeshForVertex(poly(abs(i), abs(j)));
			for (int k = 0; k < mesh.size();k++)// each (Polygon::Triangle k in mesh)
			{
				bool pass = false;
				for (int p = 0; p < k; p++)
					if (mesh[k] == mesh[p]){ pass = true; break; }
				if (pass) continue;

				if ((mesh[k].v1 > poly.Sum(poly.GetDegree())) || (mesh[k].v2>poly.Sum(poly.GetDegree())) || (mesh[k].v3>poly.Sum(poly.GetDegree()))) 
					continue;

				int x1 = poly.ConvertIndex(mesh[k].v1).x;
				int x2 = poly.ConvertIndex(mesh[k].v2).x;
				int x3 = poly.ConvertIndex(mesh[k].v3).x;
				int y1 = poly.ConvertIndex(mesh[k].v1).y;
				int y2 = poly.ConvertIndex(mesh[k].v2).y;
				int y3 = poly.ConvertIndex(mesh[k].v3).y;
				int is, js;

				if ((i == 0) && (j == 0))///начало костыля
				{
					is = -1;
					js = -1;
				}
				else
				{
					is = (i < 0 ? -1 : 1);
					js = (j < 0 ? -1 : 1);
				}                          ///конец костыля

				x1 *= is;
				x2 *= is;
				x3 *= is;
				y1 *= js;
				y2 *= js;
				y3 *= js;



				Polygon::Vector v1(y1, x1);
				Polygon::Vector v2(y2, x2);
				Polygon::Vector v3(y3, x3);

				x1 = x1 * distance + radius / 2;
				y1 = -y1 * distance + radius / 2;
				x2 = x2 * distance + radius / 2;
				y2 = -y2 * distance + radius / 2;
				x3 = x3 * distance + radius / 2;
				y3 = -y3 * distance + radius / 2;

				render->addLine(x1, y1, x2, y2, graypen);
				render->addLine(x2, y2, x3, y3, graypen);
				render->addLine(x3, y3, x1, y1, graypen);


				//QPolygon triangle;

				if ((poly.Get(v1.x, v1.y).value == poly.Get(v2.x, v2.y).value) && (poly.Get(v1.x, v1.y).value != poly.Get(v3.x, v3.y).value))
				{
					render->addLine(x2 + (x3 - x2) / 2, y2 + (y3 - y2) / 2, x1 + (x3 - x1) / 2, y1 + (y3 - y1) / 2, blackpen);
				}
				 if ((poly.Get(v2.x, v2.y).value == poly.Get(v3.x, v3.y).value) && (poly.Get(v2.x, v2.y).value != poly.Get(v1.x, v1.y).value))
				{
					render->addLine(x2 + (x1 - x2) / 2, y2 + (y1 - y2) / 2, x3 + (x1 - x3) / 2, y3 + (y1 - y3) / 2, blackpen);
				}
				 if ((poly.Get(v1.x, v1.y).value == poly.Get(v3.x, v3.y).value) && (poly.Get(v1.x, v1.y).value != poly.Get(v2.x, v2.y).value))
				{
					render->addLine(x1 + (x2 - x1) / 2, y1 + (y2 - y1) / 2, x3 + (x2 - x3) / 2, y3 + (y2 - y3) / 2, blackpen);
				}

			}
		}
	}












	for (int i = -poly.GetDegree(); i < poly.GetDegree(); i++)
	{
		for (int j = -poly.GetDegree() + abs(i) + 1; j < poly.GetDegree() - abs(i); j++)
		{

			int x = i * distance;
			int y = -j * distance;

			render->addEllipse(x, y, radius, radius, blackpen, brush);
			if ((poly.Get(j, i).value == '+') || (poly.Get(j, i).value == '-'))
			{
				render->addLine(x + 3, y + radius / 2, x + radius - 3, y + radius / 2, blackpen);
			}
			if (poly.Get(j, i).value == '+')
			{
				render->addLine(x + radius / 2, y + 3, x + radius / 2, y + radius - 3, blackpen);
			}

		}
	}

	if (screen)
	{

		QImage img(render->sceneRect().size().width()*2, render->sceneRect().size().height()*2, QImage::Format::Format_ARGB32_Premultiplied);
		img.fill(0);
		QPainter painter(&img);
		painter.setRenderHint(QPainter::Antialiasing, true);
		render->render(&painter);
		QString filename;
		filename = QFileDialog::getSaveFileName(0, QString::fromLocal8Bit("Сохранить скриншот"), "screenshot.png", QString::fromLocal8Bit("Изображения (*.png)"));
		if (filename != "")
			img.save(filename);
	}

	graphicsView->setScene(render);
	
}



void NPViewer::loadVertexFromFile()
{
	QString path = QFileDialog::getOpenFileName(0, QString::fromLocal8Bit("Загрузить вершины"), "polygon.VERTEX", QString::fromLocal8Bit("Файлы вершин (*.VERTEX)"));
	if (path != "")
	{
		poly.fromFile(path.toStdString());
		pathVertex = path;
	}
	DrawPolygon();
}

void NPViewer::loadTriangulationFromFile()
{
	QString path = QFileDialog::getOpenFileName(0, QString::fromLocal8Bit("Загрузить триангуляцию"), "polygon.TRIANGLES", QString::fromLocal8Bit("Файлы треугольников (*.TRIANGLES)"));
	if (path != "")
	{
		poly.fromFileTriangulation(path.toStdString());
		pathTriangulation = path;
	}
	DrawPolygon();
}

void NPViewer::saveVertexToFile()
{
	QString path = QFileDialog::getSaveFileName(0, QString::fromLocal8Bit("Сохранить вершины"), "polygon.VERTEX", QString::fromLocal8Bit("Файлы вершин (*.VERTEX)"));
	if (path != "")
		poly.toFile(path.toStdString());
}

void NPViewer::saveTriangulationToFile()
{
	QString path = QFileDialog::getSaveFileName(0, QString::fromLocal8Bit("Сохранить триангуляцию"), "polygon.TRIANGLES", QString::fromLocal8Bit("Файлы треугольников (*.TRIANGLES)"));
	if (path != "")
		poly.toFileTriangulation(path.toStdString());
}

void NPViewer::fillXOR()
{
	poly.FillXor();
	DrawPolygon();
}

void NPViewer::fillRAND()
{
	poly.FillRandom();
	DrawPolygon();
}

void NPViewer::fillPLUS()
{
	poly.FillWith(true);
	DrawPolygon();
}

void NPViewer::fillMINUS()
{
	poly.FillWith(false);
	DrawPolygon();
}

void NPViewer::invert()
{
	poly.Invert();
	DrawPolygon();
}


void NPViewer::polyForm()
{
	polygonDialog = new newPolygonDialog(this);
	polygonDialog->setAttribute(Qt::WA_DeleteOnClose, true);
	connect(polygonDialog, SIGNAL(send_data(int)), this, SLOT(newPoly(int)));
	polygonDialog->exec();
}

void NPViewer::newPoly(int value)
{
	poly = Polygon(value);
	DrawPolygon();
}

void NPViewer::triangulateSimple()
{
	poly.SimpleTriangulate();
	DrawPolygon();
}

void NPViewer::reload()
{
	if (pathTriangulation != "")
		poly.fromFileTriangulation(pathTriangulation.toStdString());
	if (pathVertex != "")
		poly.fromFile(pathVertex.toStdString());
	DrawPolygon();
}

void NPViewer::screenshot()
{
	DrawPolygon(true);
}

void NPViewer::showAbout()
{
	QMessageBox::about(this, QString::fromLocal8Bit("О программе"), QString::fromLocal8Bit("Комбинаторный патчворкинг алгебраических кривых \n ©Александр Козлов\nЛГТУ, ПМ-14-2, 2016 год"));
}

void NPViewer::showHelp()
{
	helpWidget = new HelpWidget(this);
	helpWidget->setAttribute(Qt::WA_DeleteOnClose, true);
	helpWidget->exec();
}