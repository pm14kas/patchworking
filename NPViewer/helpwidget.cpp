#include "helpwidget.hpp"

HelpWidget::HelpWidget(QWidget *parent)
	:QDialog(parent)
{
	setFixedSize(400, 300);
	buttonGeneric = new QPushButton(QString::fromLocal8Bit("Общая справка"), this);
	buttonNew = new QPushButton(QString::fromLocal8Bit("Создание полигона"), this);
	buttonFill = new QPushButton(QString::fromLocal8Bit("Заполнение полигона"), this);
	buttonTriangulation = new QPushButton(QString::fromLocal8Bit("Триангуляция"), this);
	buttonSaveLoad = new QPushButton(QString::fromLocal8Bit("Сохранение и загрузка"), this);
	buttonScreenshot = new QPushButton(QString::fromLocal8Bit("Скриншоты"), this);
	buttonExit = new QPushButton(QString::fromLocal8Bit("Выход"), this);

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


void HelpWidget::setTextGeneric(){ helpText->setText(QString::fromLocal8Bit("Эта программа позволяет просматривать и изменять файлы графического построения комбинаторных моделей вещественных проективных алгебраических кривых методом комбинаторного патчворкинга Виро.\nNPViewer расшифровывается как \"Newton Polygon Viewer\", или как \"Просмотрщик многоугольников Ньютона\"\nВ новой версии добавлена возможность приближения изображения.")); }
void HelpWidget::setTextNew() { helpText->setText(QString::fromLocal8Bit("Чтобы создать новый полигон, нажмите Файл/Создать. Появится окно, в котором необходимо ввести степень требуемого полигона. При введении отрицательного или пустого значения полигон не создастся. Также скорость создания полигона зависит от введенной величины. Созданный полигон будет иметь заполнение, состоящее из отрицательных степеней.")); }
void HelpWidget::setTextFill(){ helpText->setText(QString::fromLocal8Bit("NPViewer позволяет заполнить полигон одним из четырех предустановленных алгоритмов. Чтобы заполнить полигон, нажмите Правка/Заполнение и выберите необходимый тип.\nXOR заполняет полигон по алгоритму \"+, если x==i==0XOR2, -, если иначе\".\nRANDOM заполняет полигон по псевдослучайному алгоритму.\nALLPLUS заполняет полигон исключительно положительными степенями.\nALLMINUS заполняет полигон исключительно отрицательными степенями.\nДля инверсии полигона нажмите Правка/Инверсия вершин")); }
void HelpWidget::setTextTriangulation(){ helpText->setText(QString::fromLocal8Bit("NPViewer позволяет выполнить триангуляцию (разбиение на треугольники) для полигона. Чтобы выполнить триангуляцию, нажмите Правка/Триангуляция и выберите необходимый тип.\nПростая триангуляция разбивает полигон на равнобедренные прямые треугольники.\n")); }
void HelpWidget::setTextSaveLoad(){ helpText->setText(QString::fromLocal8Bit("NPViewer позволяет сохранять в файл и загружать из файла полигоны и триангуляцию для них.\nДля загрузки вершин полигона выберите Файл/Загрузить вершины и в появившемся диалоговом окне выберите необходимый файл с расширением .VERTEX\nДля загрузки триангуляции полигона выберите Файл/Загрузить триангуляцию и в появившемся диалоговом окне выберите необходимый файл с расширением .TRIANGLES. Стоит заметить, что проверка на совпадение количества вершин и количества треугольников не выполняется из-за разнообразия алгоритмов триангуляции\nДля сохранения вершин полигона выберите Файл/Сохранить вершины и в появившемся диалоговом окне выберите необходимый файл с расширением .VERTEX\nДля сохранения триангуляции выберите Файл/Сохранить триангуляцию и в появившемся диалоговом окне выберите необходимый файл с расширением .TRIANGLES\n")); }
void HelpWidget::setTextScreenshot(){ helpText->setText(QString::fromLocal8Bit("NPViewer позволяет делать скриншоты полигонов. Для этого нажмите Файл/Скриншот и в появившемся диалоговом окне выберите место для сохранения файла. Скриншот сохраняется в формате .png.")); }

