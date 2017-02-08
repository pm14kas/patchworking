#include "newpolygondialog.hpp"


newPolygonDialog::newPolygonDialog(QWidget *parent)
	:QDialog(parent)
{
	this->setFixedSize(250, 100);
	buttonAccept = new QPushButton(QString::fromLocal8Bit("OK"), this);
	buttonAccept->setGeometry(70, 70, 55, 25);
	buttonDeny = new QPushButton(QString::fromLocal8Bit("Отмена"), this);
	buttonDeny->setGeometry(140, 70, 55, 25);
	connect(buttonAccept, SIGNAL(pressed()), this, SLOT(accept()));
	connect(buttonDeny, SIGNAL(pressed()), this, SLOT(close()));
	lineEdit = new QLineEdit(this);
	lineEdit->setGeometry(20, 30, 210, 20);
	lineEdit->setFocus();
	label = new QLabel(QString::fromLocal8Bit("Введите степень полигона: "), this);
	label->setGeometry(50, 10, 200, 20);
}
newPolygonDialog::~newPolygonDialog()
{
	delete buttonAccept;
	delete buttonDeny;
	delete lineEdit;
}







void newPolygonDialog::accept()
{
	if (lineEdit->text() != "")
	{
		value = lineEdit->text().toInt();
		emit send_data(value);
	}
	emit close();
}