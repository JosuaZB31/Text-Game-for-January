#include<iostream>
#include<string>

class Character 
{
protected:
	std::string name;
	int health;
public:
	Character(std::string n,int h): name(n), health(h){}
	virtual void displayStats()const 
	{
		std::cout << "Name: " << name << "\nHealth: " << health << std::endl;
	}
	virtual~Character(){}
};
class Player :public Character 
{
private:
	std::string inventory[5]; //fixed inventory size
	int itemCount = 0;
public:
	Player(std::string n, int h):Character(n,h){}
	void addItem(const std::string& item) 
	{
		if (itemCount < 5)
		{
			inventory[itemCount++] = item;
			std::cout << "You picked up: " << item << std::endl;
		}
	}
	void showInventory()const
	{
		std::cout << "Inventory: ";
		for (int i = 0; i < itemCount; ++i)
		{
			std::cout << inventory[i] << " ";
		}
		std::cout << std::endl;
	}
};
class Ghost :public Character
{
public:
	Ghost(std::string n, int h):Character(n,h){}
	void haunt()const
	{
		std::cout << "The Ghost " << name << "lets out a chilling wail!" << std::endl;
	}
};
//functions, Explore different locations
void exploreLibrary(Player& player)
{
	std::cout << "You enter the dusty library. Ancient books line the shelves.....\n";
	std::cout << "Do you read a myserious book? (yes/no):";

}