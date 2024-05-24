/* ---   Посетитель   --- */
#include "0. Testing.h"

/* Предварительное объявление классов для метода
* "Двойной диспетчеризации" ("Double dispatch")
*/
class S_Clothing;
class S_Brulik;
class S_Food;

/*   Интерфейс "Посетителя"   */
// "Посетитель"
class IVisitor
{
public:
	virtual void Visit(S_Clothing& inComp) = 0;
	virtual void Visit(S_Brulik& inComp) = 0;
	virtual void Visit(S_Food& inComp) = 0;
};

/*   Интерфейс "Компонента"   */
// "Магазин"
class IShop abstract
{
public:
	virtual void Accept(IVisitor& inVisitor) = 0;
};

/*   Дочерние "Компоненты"   */
// "Магазин": Одежда
class S_Clothing : public IShop
{
public:
	void Accept(IVisitor& inVisitor) override
	{
		std::cout << "М.1: ";
		inVisitor.Visit(*this);
	}
};
// "Магазин": 2
class S_Brulik : public IShop
{
public:
	void Accept(IVisitor& inVisitor) override
	{
		std::cout << "М.2: ";
		inVisitor.Visit(*this);
	}
};
// "Магазин": 3
class S_Food : public IShop
{
public:
	void Accept(IVisitor& inVisitor) override
	{
		std::cout << "М.3: ";
		inVisitor.Visit(*this);
	}
};

/*   Дочерние "Посетители"   */
// "Посетитель": Обычный
class V_Ordinary : public IVisitor
{
public:
	void Visit(S_Clothing& inComp) override
	{
		std::cout << "Магазин одежды предлагает простую одежду" << std::endl;
	}
	void Visit(S_Brulik& inComp) override
	{
		std::cout << "В магазине \"Брюликов\" еле хватает на кольцо" << std::endl;
	}
	void Visit(S_Food& inComp) override
	{
		std::cout << "Поел в Магазине Фаст-фуда" << std::endl;
	}
};
// "Посетитель": Знатный
class V_Noble : public IVisitor
{
public:
	void Visit(S_Clothing& inComp) override
	{
		std::cout << "Магазин одежды предлагает Фирменную одежду дорогого бренда" << std::endl;
	}
	void Visit(S_Brulik& inComp) override
	{
		std::cout << "Магазин \"Брюликов\" предлагает Алмазы да Сапфиры" << std::endl;
	}
	void Visit(S_Food& inComp) override
	{
		std::cout << "Поел в Ресторане" << std::endl;
	}
};
// "Посетитель": Очень богатый (унаследован от Знатного)
class V_VeryRich : public V_Noble
{
public:
	void Visit(S_Clothing& inComp) override
	{
		std::cout << "Скупается часть магазина одежды" << std::endl;
	}
	void Visit(S_Brulik& inComp) override
	{
		std::cout << "Магазин \"Брюликов\" предлагает Колье" << std::endl;
	}
	void Visit(S_Food& inComp) override
	{
		std::cout << "Прибыл в свой Ресторан" << std::endl;
	}
};

/*   Вспомогательный код "клиента"   */
// Посещение каждого из магазинов (Шоппинг)
void Shopping(std::vector<IShop*> components, IVisitor& visitor)
{
	for (IShop* iComp : components)
	{
		iComp->Accept(visitor);
	}
	std::cout << std::endl;
}

int main3()
{
	// Инициализация "Магазинов"
	S_Clothing C1;
	S_Brulik C2;
	S_Food C3;

	// Инициализация вектора "Торговая площадь" из "Магазинов"
	std::vector<IShop*> ShoppingArea;
	ShoppingArea.push_back(&C1);
	ShoppingArea.push_back(&C2);
	ShoppingArea.push_back(&C3);

	// Инициализация "Посетителей"
	V_Ordinary V1;
	V_Noble V2;
	V_VeryRich V3;

	std::cout << "=== Шоппинг обычного посетителя:" << '\n';
	Shopping(ShoppingArea, V1);

	std::cout << "=== Шоппинг посетителя из знатного рода:" << '\n';
	Shopping(ShoppingArea, V2);

	std::cout << "=== Шоппинг очень богатого:" << '\n';
	Shopping(ShoppingArea, V3);

	return 0;
}

/*   Вывод:
* Паттерн "Посетитель" позволяет добавлять для "Компонентов" новые операции,
* не изменяя классы "Компонентов", над которыми эти операции могут выполняться.
* 
* PS: "Двойная диспетчеризация" позволяет обойти проблему вызова
* метода « родительского » класса "Компонентов"
* при обращении к его « дочернему » классу
*/