#ifndef HELPFORM_H
#define HELPFORM_H

#include <QtWidgets/QDialog>
#include <QTextBrowser>
#include <qpushbutton.h>

class HelpWidget : public QDialog
{
	Q_OBJECT
public:
	HelpWidget(QWidget *parent = 0);
	~HelpWidget();

private:
	QTextBrowser* helpText;
	QPushButton* buttonGeneric;
	QPushButton* buttonNew;
	QPushButton* buttonFill;
	QPushButton* buttonTriangulation;
	QPushButton* buttonSaveLoad;
	QPushButton* buttonScreenshot;
	QPushButton* buttonExit;
private slots :
		/*void setTextGeneric(){ helpText->setText(QString::fromLocal8Bit("��� ��������� ��������� ������������� � �������� ����� ������������ ���������� ������������� ������� ������������ ����������� �������������� ������ ������� �������������� ������������ ����.\nNPViewer ���������������� ��� \"Newton Polygon Viewer\", ��� ��� \"����������� ��������������� �������\"")); }
		void setTextNew() {helpText->setText(QString::fromLocal8Bit("����� ������� ����� �������, ������� ������/�������. �������� ����, � ������� ���������� ������ ������� ���������� ��������. ��� �������� �������������� ��� ������� �������� ������� �� ���������. ����� �������� �������� �������� ������� �� ��������� ��������. ��������� ������� ����� ����� ����������, ��������� �� ������������� ��������.")); }
		void setTextFill(){ helpText->setText(QString::fromLocal8Bit("NPViewer ��������� ��������� ������� ����� �� ������� ����������������� ����������. ����� ��������� �������, ������� ������/���������� � �������� ����������� ���.\nXOR ��������� ������� �� ��������� \"+, ���� x==i==0XOR2, -, ���� �����\".\nRANDOM ��������� ������� �� ���������������� ���������.\nALLPLUS ��������� ������� ������������� �������������� ���������.\nALLMINUS ��������� ������� ������������� �������������� ���������.")); }
		void setTextTriangulation(){ helpText->setText(QString::fromLocal8Bit("NPViewer ��������� ��������� ������������ (��������� �� ������������) ��� ��������. ����� ��������� ������������, ������� ������/������������/������� � �������� ����������� ���.\n������� ������������ ��������� ������� �� �������������� ������ ������������.\n")); }
		void setTextSaveLoad(){ helpText->setText(QString::fromLocal8Bit("NPViewer ��������� ��������� � ���� � ��������� �� ����� �������� � ������������ ��� ���.\n��� �������� ������ �������� �������� ����/��������� ������� � � ����������� ���������� ���� �������� ����������� ���� � ����������� .VERTEX\n��� �������� ������������ �������� �������� ����/��������� ������������ � � ����������� ���������� ���� �������� ����������� ���� � ����������� .TRIANGLES. ����� ��������, ��� �������� �� ���������� ���������� ������ � ���������� ������������� �� ����������� ��-�� ������������ ���������� ������������\n��� ���������� ������ �������� �������� ����/��������� ������� � � ����������� ���������� ���� �������� ����������� ���� � ����������� .VERTEX\n��� ���������� ������������ �������� ����/��������� ������������ � � ����������� ���������� ���� �������� ����������� ���� � ����������� .TRIANGLES\n")); }
		void setTextScreenshot(){ helpText->setText(QString::fromLocal8Bit("NPViewer ��������� ������ ��������� ���������. ��� ����� ������� ����/�������� � � ����������� ���������� ���� �������� ����� ��� ���������� �����. �������� ����������� � ������� .png.")); }
		*/
	void setTextGeneric();
	void setTextNew();
	void setTextFill();
	void setTextTriangulation();
	void setTextSaveLoad();
	void setTextScreenshot();
};

#endif // NEWPOLYFORM_H
