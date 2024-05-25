/* ---   Снимок   --- */
#include "0. Testing.h"

/*   Подготовка данных для хранения   */
// Ориентация
enum EOrientation : int8_t
{
	Top,	// Верх
	Bottom,	// Низ
	Left,	// Лево
	Right	// Право
};
// Данные для хранения
struct Data
{
	// Координаты
	int coord_X = 0;
	int coord_Y = 0;
	// Ориентация
	EOrientation orientation = EOrientation::Bottom;
};

/*   "Создатель" ("Originator")   */
// Объект, чьи данные требуется хранить
class SokoBan
{
private:
	Data data;
public:
	// Ввод информации
	bool SetStep(char inControl, int inStep)
	{
		inControl = inControl | 0x20;

		switch (inControl)
		{
		case 'w':
			data.orientation = EOrientation::Top;
			data.coord_Y += inStep;
			break;
		case 's':
			data.orientation = EOrientation::Bottom;
			data.coord_Y -= inStep;
			break;
		case 'a':
			data.orientation = EOrientation::Left;
			data.coord_X -= inStep;
			break;
		case 'd':
			data.orientation = EOrientation::Right;
			data.coord_X += inStep;
			break;
		default:
			return false;
			break;
		}

		return true;
	}

	// Получение данных
	Data GetData()
	{
		return data;
	}
	// Запись данных
	void SetData(Data inData)
	{
		data = inData;
	}

	// Вывод информации
	friend std::ostream& operator<<(std::ostream& out, const SokoBan& sb)
	{
		char charOrientation = '0';

		switch (sb.data.orientation)
		{
		case Top:
			charOrientation = '^';
			break;
		case Bottom:
			charOrientation = 'v';
			break;
		case Left:
			charOrientation = '<';
			break;
		case Right:
			charOrientation = '>';
			break;
		}

		out
			<< "Координаты: " << sb.data.coord_X
			<< ", " << sb.data.coord_Y
			<< ". Ориентация: " << charOrientation;

		return out;
	}
};

/*   "Опекун" ("Caretaker")   */
class Caretaker
{
private:
	std::vector<Data*> savedData;
	SokoBan& sokoban;

public:
	// Конструктор
	Caretaker(SokoBan& inSokoBan) : sokoban(inSokoBan)
	{
		SaveData();
	}

	// Сохранение данных по порядку
	void SaveData()
	{
		savedData.push_back(new Data(sokoban.GetData()));
	}
	// Возврат данных в обратном порядке
	void Undo()
	{

		if (savedData.size() > 1)
		{
			savedData.pop_back();
			savedData.shrink_to_fit();
			sokoban.SetData(*savedData.back());
		}
	}
};

// Сброс std::cin
void stdReset()
{
	std::cin.clear();				// возвращаем cin в 'обычный' режим работы
	std::cin.ignore(32767, '\n');	// и удаляем значения предыдущего ввода из входного буфера
}

int main5()
{
	/*   Инициализация переменных   */
	// Грузчик
	SokoBan Loader;
	// Хранитель данных
	Caretaker Quardian(Loader);
	// Переменные вводимых данных
	char control = '0';
	int steps = 0;

	std::cout << "=== Управление:\n"
		<< "Вверх:  \"W\"  + количество шагов\n"
		<< "Вниз:   \"S\"  + количество шагов\n"
		<< "Влево:  \"A\"  + количество шагов\n"
		<< "Вправо: \"D\"  + количество шагов\n"
		<< "Отмена: \"U\"\n"
		<< "Выход:	\"0\"\n"
		<< '\n'
		<< "=== Движение с начальной позиции:\n"
		<< Loader
		<< "\n\n"
		<< "=== Ввидите команду:\n"
		<< std::endl;

	// Начало цикла
	do
	{
		// Ввод символа направления
		std::cin >> control;

		/*   Проверка:   */
		// Выход:
		if (control == '0')
			break;

		// Возврат:
		else if (control == 'U' || control == 'u')
		{
			// Возврат на предыдущее состояние
			Quardian.Undo();
		}

		else
		{
			// Ввод количества шагов
			std::cin >> steps;

			// Если предыдущее извлечение было неудачным,
			if (std::cin.fail())
				// То сбрасываем std::cin
				stdReset();			

			// Записать и сохранить новые данные
			Loader.SetStep(control, steps);
			Quardian.SaveData();
		}

		// Вывод текущих данных
		std::cout << Loader << std::endl;
	}
	while (control != ('0'));

	return 0;
}

/*   Вывод:
* Паттерн "Снимок" позволяет делать сохранение внутреннего
* состояния объектов, а также восстанавливать их.
*/