#ifndef NEWPOLYGONDIALOG_HPP
#define NEWPOLYGONDIALOG_HPP

#include <QtWidgets/QDialog>
#include <qpushbutton.h>
#include <qlineedit.h>
#include <qlabel.h>

class newPolygonDialog : public QDialog
{
	Q_OBJECT
public:
	newPolygonDialog(QWidget *parent = 0);
	~newPolygonDialog();


signals :
	void send_data(int value);

private:
	int value;
	QPushButton* buttonAccept;
	QPushButton* buttonDeny;
	QLineEdit* lineEdit;
	QLabel* label;

private slots:
	void accept();

};

#endif // NEWPOLYFORM_H
