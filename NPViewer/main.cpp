#include "npviewer.hpp"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	NPViewer w;
	w.show();
	return a.exec();
}
