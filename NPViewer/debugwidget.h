#ifndef DEBUGWINDOW_HPP
#define DEBUGWINDOW_HPP

#include <QtWidgets/QWidget>
#include <QTextBrowser>
#include <qfile.h>
#include "debug.h"

class DebugWindow : public QWidget
{
	Q_OBJECT
public:
	DebugWindow(QWidget *parent = 0)
		:QWidget(parent)
	{
		setFixedSize(300, 100);
		label = new QTextBrowser(this);
		label->setGeometry(0,10, 300, 80);

		lastIndex = 0;
		connect(this, SIGNAL(SetFile()), this, SIGNAL(ReadFile()));
		connect(this, SIGNAL(SetOut()), this, SIGNAL(OutFile()));

		ReadFile();
	}
	~DebugWindow(){}

private:
	QTextBrowser* label;
	int lastIndex;
	QList<QString> storage;
	
private slots:
	void ReadFile()
	{
		QFile file("debug.txt");
		if (file.open( QIODevice::Text))
		{
			while (!file.atEnd())
			{
				QString str = file.readLine();

				QStringList lst = str.split(" : ");
				if (lastIndex < lst.at(0).toInt())
				{
					lastIndex = lst.at(0).toInt();
					storage.push_back(str);
					if (storage.size() >= 300) storage.pop_front();
				}
			}

		}
		emit SetOut();
	}

	void OutFile()
	{
		QString giant;
		for each (QString i in storage)
		{
			giant += i;
			giant += "\n";
		}
		label->setText(giant);
		emit ReadFile();
	}



signals:
	void SetFile();
	void SetOut();

};

#endif // NEWPOLYFORM_H
