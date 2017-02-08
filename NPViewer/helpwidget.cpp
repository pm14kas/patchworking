#include "helpwidget.hpp"

HelpWidget::HelpWidget(QWidget *parent)
	:QDialog(parent)
{
	setFixedSize(400, 300);
	buttonGeneric = new QPushButton(QString::fromLocal8Bit("����� �������"), this);
	buttonNew = new QPushButton(QString::fromLocal8Bit("�������� ��������"), this);
	buttonFill = new QPushButton(QString::fromLocal8Bit("���������� ��������"), this);
	buttonTriangulation = new QPushButton(QString::fromLocal8Bit("������������"), this);
	buttonSaveLoad = new QPushButton(QString::fromLocal8Bit("���������� � ��������"), this);
	buttonScreenshot = new QPushButton(QString::fromLocal8Bit("���������"), this);
	buttonExit = new QPushButton(QString::fromLocal8Bit("�����"), this);

	helpText = new QTextBrowser(this);
	helpText->setGeometry(160, 0, 240, 300);

	buttonGeneric->setGeometry(0,0,150,25);
	buttonNew->setGeometry(0,40,150,25);
	buttonFill->setGeometry(0,80,150,25);
	buttonTriangulation->setGeometry(0,120,150,25);
	buttonSaveLoad->setGeometry(0,160,150,25);
	buttonScreenshot->setGeometry(0,200,150,25);
	buttonExit->setGeometry(0,260,150,25);

	connect(buttonGeneric, SIGNAL(pressed()), this, SLOT(setTextGeneric()));
	connect(buttonNew, SIGNAL(pressed()), this, SLOT(setTextNew()));
	connect(buttonFill, SIGNAL(pressed()), this, SLOT(setTextFill()));
	connect(buttonTriangulation, SIGNAL(pressed()), this, SLOT(setTextTriangulation()));
	connect(buttonSaveLoad, SIGNAL(pressed()), this, SLOT(setTextSaveLoad()));
	connect(buttonScreenshot, SIGNAL(pressed()), this, SLOT(setTextScreenshot()));
	connect(buttonExit, SIGNAL(pressed()), this, SLOT(close()));
}

HelpWidget::~HelpWidget()
{
	delete helpText;
	delete buttonGeneric;
	delete buttonNew;
	delete buttonFill;
	delete buttonTriangulation;
	delete buttonSaveLoad;
	delete buttonScreenshot;
	delete buttonExit;
}


void HelpWidget::setTextGeneric(){ helpText->setText(QString::fromLocal8Bit("��� ��������� ��������� ������������� � �������� ����� ������������ ���������� ������������� ������� ������������ ����������� �������������� ������ ������� �������������� ������������ ����.\nNPViewer ���������������� ��� \"Newton Polygon Viewer\", ��� ��� \"����������� ��������������� �������\"\n� ����� ������ ��������� ����������� ����������� �����������.")); }
void HelpWidget::setTextNew() { helpText->setText(QString::fromLocal8Bit("����� ������� ����� �������, ������� ����/�������. �������� ����, � ������� ���������� ������ ������� ���������� ��������. ��� �������� �������������� ��� ������� �������� ������� �� ���������. ����� �������� �������� �������� ������� �� ��������� ��������. ��������� ������� ����� ����� ����������, ��������� �� ������������� ��������.")); }
void HelpWidget::setTextFill(){ helpText->setText(QString::fromLocal8Bit("NPViewer ��������� ��������� ������� ����� �� ������� ����������������� ����������. ����� ��������� �������, ������� ������/���������� � �������� ����������� ���.\nXOR ��������� ������� �� ��������� \"+, ���� x==i==0XOR2, -, ���� �����\".\nRANDOM ��������� ������� �� ���������������� ���������.\nALLPLUS ��������� ������� ������������� �������������� ���������.\nALLMINUS ��������� ������� ������������� �������������� ���������.\n��� �������� �������� ������� ������/�������� ������")); }
void HelpWidget::setTextTriangulation(){ helpText->setText(QString::fromLocal8Bit("NPViewer ��������� ��������� ������������ (��������� �� ������������) ��� ��������. ����� ��������� ������������, ������� ������/������������ � �������� ����������� ���.\n������� ������������ ��������� ������� �� �������������� ������ ������������.\n")); }
void HelpWidget::setTextSaveLoad(){ helpText->setText(QString::fromLocal8Bit("NPViewer ��������� ��������� � ���� � ��������� �� ����� �������� � ������������ ��� ���.\n��� �������� ������ �������� �������� ����/��������� ������� � � ����������� ���������� ���� �������� ����������� ���� � ����������� .VERTEX\n��� �������� ������������ �������� �������� ����/��������� ������������ � � ����������� ���������� ���� �������� ����������� ���� � ����������� .TRIANGLES. ����� ��������, ��� �������� �� ���������� ���������� ������ � ���������� ������������� �� ����������� ��-�� ������������ ���������� ������������\n��� ���������� ������ �������� �������� ����/��������� ������� � � ����������� ���������� ���� �������� ����������� ���� � ����������� .VERTEX\n��� ���������� ������������ �������� ����/��������� ������������ � � ����������� ���������� ���� �������� ����������� ���� � ����������� .TRIANGLES\n")); }
void HelpWidget::setTextScreenshot(){ helpText->setText(QString::fromLocal8Bit("NPViewer ��������� ������ ��������� ���������. ��� ����� ������� ����/�������� � � ����������� ���������� ���� �������� ����� ��� ���������� �����. �������� ����������� � ������� .png.")); }

