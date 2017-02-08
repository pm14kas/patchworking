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
		/*void setTextGeneric(){ helpText->setText(QString::fromLocal8Bit("Эта программа позволяет просматривать и изменять файлы графического построения комбинаторных моделей вещественных проективных алгебраических кривых методом комбинаторного патчворкинга Виро.\nNPViewer расшифровывается как \"Newton Polygon Viewer\", или как \"Просмотрщик многоугольников Ньютона\"")); }
		void setTextNew() {helpText->setText(QString::fromLocal8Bit("Чтобы создать новый полигон, нажмите Правка/Создать. Появится окно, в котором необходимо ввести степень требуемого полигона. При введении отрицательного или пустого значения полигон не создастся. Также скорость создания полигона зависит от введенной величины. Созданный полигон будет иметь заполнение, состоящее из отрицательных степеней.")); }
		void setTextFill(){ helpText->setText(QString::fromLocal8Bit("NPViewer позволяет заполнить полигон одним из четырех предустановленных алгоритмов. Чтобы заполнить полигон, нажмите Правка/Заполнение и выберите необходимый тип.\nXOR заполняет полигон по алгоритму \"+, если x==i==0XOR2, -, если иначе\".\nRANDOM заполняет полигон по псевдослучайному алгоритму.\nALLPLUS заполняет полигон исключительно положительными степенями.\nALLMINUS заполняет полигон исключительно отрицательными степенями.")); }
		void setTextTriangulation(){ helpText->setText(QString::fromLocal8Bit("NPViewer позволяет выполнить триангуляцию (разбиение на треугольники) для полигона. Чтобы выполнить триангуляцию, нажмите Правка/Триангуляция/Простая и выберите необходимый тип.\nПростая триангуляция разбивает полигон на равнобедренные прямые треугольники.\n")); }
		void setTextSaveLoad(){ helpText->setText(QString::fromLocal8Bit("NPViewer позволяет сохранять в файл и загружать из файла полигоны и триангуляцию для них.\nДля загрузки вершин полигона выберите Файл/Загрузить вершины и в появившемся диалоговом окне выберите необходимый файл с расширением .VERTEX\nДля загрузки триангуляции полигона выберите Файл/Загрузить триангуляцию и в появившемся диалоговом окне выберите необходимый файл с расширением .TRIANGLES. Стоит заметить, что проверка на совпадение количества вершин и количества треугольников не выполняется из-за разнообразия алгоритмов триангуляции\nДля сохранения вершин полигона выберите Файл/Сохранить вершины и в появившемся диалоговом окне выберите необходимый файл с расширением .VERTEX\nДля сохранения триангуляции выберите Файл/Сохранить триангуляцию и в появившемся диалоговом окне выберите необходимый файл с расширением .TRIANGLES\n")); }
		void setTextScreenshot(){ helpText->setText(QString::fromLocal8Bit("NPViewer позволяет делать скриншоты полигонов. Для этого нажмите Файл/Скриншот и в появившемся диалоговом окне выберите место для сохранения файла. Скриншот сохраняется в формате .png.")); }
		*/
	void setTextGeneric();
	void setTextNew();
	void setTextFill();
	void setTextTriangulation();
	void setTextSaveLoad();
	void setTextScreenshot();
};

#endif // NEWPOLYFORM_H
