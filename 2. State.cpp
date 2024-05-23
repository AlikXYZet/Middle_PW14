/* ---   Состояние   --- */
#include "0. Testing.h"

/*   "Состояние"   */
// Интерфейс Состояния
class IState abstract
{
public:
	virtual void Action() = 0;
};

/*   Конкретные "Состояния"   */
// "Состояние": Мирный
class SPeaceful : public IState
{
public:
	void Action() override
	{
		std::cout << "Мирный: Приветствует" << std::endl;
	}
};
// "Состояние": Нервный
class SNervous : public IState
{
public:
	void Action() override
	{
		std::cout << "Нервный: Предупреждает" << std::endl;
	}
};
// "Состояние": Злой
class SEvil : public IState
{
public:
	void Action() override
	{
		std::cout << "Злой: Нападает" << std::endl;
	}
};
// "Состояние": Контужен
class SShellShocked : public IState
{
public:
	void Action() override
	{
		std::cout << "Контужен: Временно обездвижен" << std::endl;
	}
};
// "Состояние": Измотан
class SExhausted : public IState
{
public:
	void Action() override
	{
		std::cout << "Измотан: Сдаётся" << std::endl;
	}
};

/*   "Контекст"   */
// "Скрытый Босс"
class HiddenBoss
{
private:
	// Указатель на актуальное "Состояние"
	IState* state;
	// Health Points (Очки жизни)
	int MaxHP;
	float HP = MaxHP = 100;

public:
	// Конструктор
	HiddenBoss() : HiddenBoss(new SPeaceful) {}
	HiddenBoss(IState* inState) : state(inState) {}

	// "Состояние", зависимое от уровня HP
	void TakingDamage(int inDamage)
	{
		HP -= inDamage;

		if (HP >= 0.9 * MaxHP)
		{
			state = new SNervous();
		}
		else if (HP > 0.5 * MaxHP)
		{
			state = new SEvil();
		}
		else if (HP > 0.4 * MaxHP)
		{
			state = new SShellShocked();
		}
		else if (HP > 0.1 * MaxHP)
		{
			state = new SEvil();
		}
		else if (HP > 0 * MaxHP)
		{
			state = new SShellShocked();
		}
		else if (HP <= 0)
		{
			HP = 0;
			state = new SExhausted();
		}

		Request();
	}

	void Request()
	{
		state->Action();
	}

	bool CheckHP()
	{
		if (HP > 0)
		{
			return true;
		}
		return false;
	}
};

int main2()
{
	// Инициализация Босса ("Контекста")
	HiddenBoss HiddenBoss;

	// Контроль нанесения урона
	float Damage = 10.1;
	int MaxHP = 100;

	std::cout << "=== Встреча с Скрытым Боссом" << '\n';
	// Первая встреча
	HiddenBoss.Request();

	std::cout << "\n=== Нанесение урона Боссу" << '\n';

	// Цикл нанесения урона
	while (HiddenBoss.CheckHP())
	{
		HiddenBoss.TakingDamage(Damage);
	}

	return 0;
}

/*   Вывод:
* Паттерн "Состояние" позволяет изменять "Поведение"
* класса "Контекст" изменяя его "Состояние".
* Изменять "Состояние" можно как внутри, так и извне класса "Контекст".
*/