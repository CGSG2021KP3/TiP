#include <iostream>
#include<string>

class Tracker
{
private:
	std::string name;
	static int aliveCount;

public:
	Tracker(std::string objName) : name(objName)
	{
		aliveCount++;
		std::cout << "[" << name << "]: конструктор с параметром. Живых объектов: " << aliveCount << "\n";
	}

	Tracker() : name("Аноним")
	{
		aliveCount++;
		std::cout << "[" << name << "]: конструктор по умолчанию. Живых объектов: " << aliveCount << "\n";
	}

	Tracker(const Tracker& other)
	{
		aliveCount++;
		name = "Копия_" + other.name;
		std::cout << "[" << name << "]: конструктор копирования. Живых объектов: " << aliveCount << "\n";
	}

	~Tracker()
	{
		aliveCount--;
		std::cout << "[" << name << "]: деструктор. Живых объектов: " << aliveCount << "\n";
	}

	void doAction() const
	{
		std::cout << "[" << name << "]: выполняет действие" << "\n";
	}
};

// инициализация статического поля
int Tracker::aliveCount = 0;

// функция для 3 теста
void processTracker(Tracker t)
{
	t.doAction();
}

// функция для 4 теста
Tracker createTracker()
{
	Tracker temp("TempInFunction");
	return temp;
}

int main()
{
	std::cout << "--- Test1 ---\n";
	{
		Tracker t1("StaticObj");
		t1.doAction();
	} // локальный блок, t1 выходит из области видимости здесь

	std::cout << "--- test2 ---\n";
	Tracker* t2 = new Tracker("DynamicObj");
	t2->doAction();
	delete t2;

	std::cout << "--- test3 ---\n";
	Tracker t3("Original");
	processTracker(t3);

	std::cout << "--- test4 ---\n";
	{
		Tracker t4 = createTracker();
		t4.doAction();
	}

	return 0;
}
