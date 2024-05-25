/* ---   Проверка патернов через консоль   --- */
#include "0. Testing.h"

//Выбор по умолчанию
int DefaultSelection = 5;

bool MainSelection(int sel)
{
	switch (sel)
	{
	case 1:
		main1();
		break;
	case 2:
		main2();
		break;
	case 3:
		main3();
		break;
	case 4:
		main4();
		break;
	case 5:
		main5();
		break;
	default:
		std::cout << "Некорректный ввод. Выбор по умолчанию: "
			<< DefaultSelection
			<< '\n'
			<< std::endl;;
		return true;
		break;
	}

	return false;
}

int main()
{
	setlocale(LC_ALL, "Russian");

	std::cout << "Поведенческие патерны:\n"
		<< "1. Команда\n"
		<< "2. Состояние\n"
		<< "3. Посетитель\n"
		<< "4. Наблюдатель\n"
		<< "5. NONE\n"
		<< '\n';

	std::cout << "Выбирите тестируемый патерн: ";
	int Selection;
	std::cin >> Selection;
	std::cout << std::endl;

	DefaultSelection = ((DefaultSelection - 1) % 5) + 1;

	if (MainSelection(Selection))
		MainSelection(DefaultSelection);

	return 0;
}