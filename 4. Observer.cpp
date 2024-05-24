/* ---   Наблюдатель   --- */
#include "0. Testing.h"
#include <list>

// Дополнительно: Список типа событий
enum class EEventType
{
	Weak,	// Слабое
	Strong,	// Сильное
	Police	// Особое
};

/*   Интерфейс "Наблюдателя" ("Observer")   */
// Интерфейс Существа
class ICreature abstract
{
public:
	// Реакция на событие
	virtual void Action(EEventType inType) = 0;
};

/*   Конкретные "Наблюдатели"   */
// Существо: Кот
class C_Cat : public ICreature
{
public:
	void Action(EEventType inType) override
	{
		std::cout << "Кот: ";
		if (inType == EEventType::Strong)
			std::cout << "Встревожился" << std::endl;
		else if (inType == EEventType::Police)
			std::cout << "Впопыхах сворачивает лавочку по продаже кошачьей мяты" << std::endl;
	}
};
// Существо: Собака
class C_Dog : public ICreature
{
public:
	void Action(EEventType inType) override
	{
		std::cout << "Собака: Лает на источник звука" << std::endl;
	}
};
// Существо: Птица
class C_Bird : public ICreature
{
public:
	void Action(EEventType inType) override
	{
		if (inType == EEventType::Strong)
			std::cout << "Птица: Взлетает" << std::endl;
	}
};

/*   Интерфейс "Субъекта" ("Subject")   */
// Интерфейс События
class IEvent
{
private:
	// Список "Подписчиков"
	std::list<ICreature*> observers;

	/*   Дополнительно:   */
	// Наименование события
	std::string Name;
	// Тип события:
	EEventType Type;

public:
	// Конструктор
	IEvent(std::string inName)
		: IEvent(inName, EEventType::Weak)
	{}

	IEvent(std::string inName, EEventType inType)
		: Name(inName), Type(inType)
	{}

	// "Подписка" на событие
	void Attach(ICreature& inObserver) {
		observers.push_back(&inObserver);
	}
	// "Отписка" от события
	void Detach(ICreature& inObserver) {
		observers.remove(&inObserver);
	}
	// Проявление события и запуск реакций на него
	void Notify() {
		std::cout << "=== " << Name << ": " << std::endl;
		for (ICreature* observer : observers) {
			observer->Action(Type);
		}
		std::cout << std::endl;
	}
};

int main4()
{
	// Инициализация событий
	IEvent Whistling("Свист");
	IEvent Bang("Сильный хлопок", EEventType::Strong);
	IEvent PoliceSiren("Полицейская сирена", EEventType::Police);

	// Инициализация Существ
	C_Dog Dog;
	C_Bird Bird;
	C_Cat Cat;

	/*   "Подписка" на События   */
	// Свист:
	Whistling.Attach(Dog);
	Whistling.Attach(Cat); // PS: Далее будет продемонстрирована "отписка"
	// Сильный хлопок:
	Bang.Attach(Dog);
	Bang.Attach(Bird);
	Bang.Attach(Cat);
	// Полицейская сирена:
	PoliceSiren.Attach(Dog);
	PoliceSiren.Attach(Cat);

	/*   "Отписка" от Событий   */
	Whistling.Detach(Cat);

	/*   Проявление Событий   */
	// Свист:
	Whistling.Notify();
	// Сильный хлопок:
	Bang.Notify();
	// Полицейская сирена:
	PoliceSiren.Notify();

	return 0;
}

/*   Вывод:
* Паттерн "Наблюдатель" позволяет одним объектам ("Наблюдателям")
* реагировать на события других объектов ("Субъектов")
*/