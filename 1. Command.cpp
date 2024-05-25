/* ---   Команда   --- */
#include "0. Testing.h"

/*   "Получатель" ("Receiver") */
// Хранилище всех возможных действий
class Actions
{
public:
	void Run() { std::cout << " Бежит"; }
	void Stand() { std::cout << " Стоит"; }
	void Down() { std::cout << " Опускается"; }
	void Lie() { std::cout << " Лежит"; }
	void Howl() { std::cout << " \"Му, му, му\""; }
	void Attack() { std::cout << " Атакует"; }
};

// Абстрактный класс "Команды"
class Command abstract
{
protected:
	Actions* actions;
public:
	Command(Actions* inActions) : actions(inActions) {}
	virtual void Execute() const = 0;
};

/*   Конкретные Команды   */
// Команда: Ко мне
class CComeHere : public Command
{
public:
	CComeHere(Actions* inActions) : Command(inActions) {}

	void Execute() const override
	{
		std::cout << "Команда \"Ко мне\": ";
		actions->Run();
		std::cout << ",";
		actions->Stand();
	}
};
// Команда: Лежать
class CDown : public Command
{
public:
	CDown(Actions* inActions) : Command(inActions) {}

	void Execute() const override
	{
		std::cout << "Команда \"Лежать\": ";
		actions->Down();
		std::cout << ",";
		actions->Lie();
	}
};
// Команда: Голос
class CBark : public Command
{
public:
	CBark(Actions* inActions) : Command(inActions) {}

	void Execute() const override
	{
		std::cout << "Команда \"Голос\": ";
		actions->Howl();
	}
};
// Команда: Взять
class CFetch : public Command
{
public:
	CFetch(Actions* inActions) : Command(inActions) {}

	void Execute() const override
	{
		std::cout << "Команда \"Взять\": ";
		actions->Run();
		std::cout << ",";
		actions->Attack();
	}
};

/*   "Отправитель" ("Invoker")   */
class Owner
{
private:
	std::vector<Command*> vCommand;
	bool checkChoice(int choice)
	{
		if (choice < vCommand.size())
			return true;
		else
		{
			std::cout << "Некорректный номер команды: " << choice << std::endl;
			return false;
		}
	}

public:
	// Записать команду
	void setCommand(Command* inCommand)
	{
		vCommand.push_back(inCommand);
	}

	// Удаление команды
	void removeCommand(int choice)
	{
		// Если команда существует
		if (checkChoice(choice))
		{
			// то выполнить удаление
			vCommand.erase(vCommand.begin()+choice);
			// с удалением лишней емкости
			vCommand.shrink_to_fit();
		}
	}

	// Выполнение команды по порядковому номеру
	void userInput(int choice)
	{
		// Если команда существует
		if (checkChoice(choice))
		{
			// то выполнить команду
			vCommand[choice]->Execute();
		}
	}

	// Получение количества команд
	size_t getSize()
	{
		return vCommand.size();
	}
};

int main1()
{
	Actions* Gavryusha = new Actions();

	// Список "изученных" команд
	Command* C1 = new CComeHere(Gavryusha);
	Command* C2 = new CDown(Gavryusha);
	Command* C3 = new CBark(Gavryusha);
	Command* C4 = new CFetch(Gavryusha);

	Owner Sharik;
	
	Sharik.setCommand(C1);
	Sharik.setCommand(C4);
	Sharik.setCommand(C2);
	Sharik.setCommand(C3);
	std::cout << "Количество изученых команд: " << Sharik.getSize() << std::endl;

	Sharik.setCommand(C4);
	std::cout << "Количество изученых команд: " << Sharik.getSize() << std::endl;

	Sharik.removeCommand(1);
	std::cout << "Количество изученых команд: " << Sharik.getSize() << std::endl;

	std::cout << "\nВыполнение всех изученных команд по порядку: ";
	for (size_t i = 0; i < Sharik.getSize(); i++)
	{
		std::cout << '\n';
		Sharik.userInput(i);
	}
	std::cout << std::endl;

	return 0;
}

/*   Вывод:
* Патерн "Команда" позволяет откладывать выполнение "Команд",
* выстраивать их в очередь, а также хранить историю и делать отмену.
*/