#include<iostream>
#include<string>
#include<windows.h>
#include<conio.h>
#include<stdlib.h>
#include<algorithm>

bool SetConsoleFont(const wchar_t* fontName, SHORT fontSize) {
	CONSOLE_FONT_INFOEX fontInfo;
	fontInfo.cbSize = sizeof(CONSOLE_FONT_INFOEX);

	// Get the current console font info
	HANDLE hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	if (!GetCurrentConsoleFontEx(hConsoleOutput, FALSE, &fontInfo)) {
		return false; // Error getting current font
	}

	// Set the font name and size
	wcscpy_s(fontInfo.FaceName, fontName);
	fontInfo.dwFontSize.Y = fontSize;

	// Set the new font
	if (!SetCurrentConsoleFontEx(hConsoleOutput, FALSE, &fontInfo)) {
		return false; // Error setting font
	}

	return true;
}



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
	void descreaseHealth(int h)
	{
		health -= h;
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
	int getItemCount() { return itemCount; }
	bool seachItem(std::string search)
	{
		// Convert the search term to lowercase
		std::transform(search.begin(), search.end(), search.begin(), ::tolower);

		for (int i = 0; i < 5; ++i)
		{
			if (inventory[i].empty()) continue;  // Skip empty inventory slots

			// Convert the item to lowercase before comparing
			std::string lowerItem = inventory[i];
			std::transform(lowerItem.begin(), lowerItem.end(), lowerItem.begin(), ::tolower);

			if (lowerItem.find(search, 0) != std::string::npos)
			{
				return true;
			}
		}
		return false;
	}


};
class Ghost :public Character
{
public:
	Ghost(std::string n, int h):Character(n,h){}
	void haunt()const
	{
		std::cout << "The Ghost " << name << " lets out a chilling wail!" << std::endl;
	}
};
//functions, Explore different locations
void exploreLibrary(Player& player)
{
	std::cout << "You enter the dusty library. Ancient books line the shelves.....\n";
	std::cout << "Do you read a myserious book? (yes/no):";
	std::string choice;
	std::cin >> choice;
	if (choice == "yes") 
	{
		std::cout << "The book reveals a spell! You gain a magic amulect.\n";
		player.addItem("Magic Amulet");
	}
	else 
	{
		std::cout << "You hear a whisper.....A ghost appears!\n";
		Ghost ghost(" Phantom Librarian", 50);
		ghost.haunt();
		player.descreaseHealth(50);
		player.displayStats();
	}
}
void exploreBasement(Player& player)
{
	std::cout << "You descend into the dark Basement. It's damp and cold...\n";
	std::cout << "Do you light a candle? (yes/no):";
	std::string choice;
	std::cin >> choice;
	if (choice == "yes")
	{
		std::cout << "You find and Old key on the ground.\n";
		player.addItem("Old key");
	}
	else {
		std::cout << "You trip in the dark and lose health!\n";
		player.descreaseHealth(50);
		player.displayStats();
	}
}
void exploreAttic(Player& player)
{
	std::cout << "You Enter the attic and find and strange mirror....\n";
	player.addItem("Haunted Mirror");
}
void exploreBedroom(Player& player)
{

	std::cout << "You Open the bedside drawer with the old key and find holy water to protect yourself";
	std::cout << "from the ghost\n";
	player.addItem("Holy Water");

	if (player.seachItem("Magic Amulet"))
	{
		std::cout << "The Ghost tries to posses you but can't, the Amulet protects you.\n";
		std::cout << "looks like you need something that reflects to trap the ghost....\n";
	}

	if (player.seachItem("Haunted Mirror"))
	{
		std::cout << "Your trap the ghost in the mirror, you make a cross on the mirror using the holy water\n";
	}
	player.addItem("Ghost");
}
//Game loop
void gameLoop(Player& player)
{
	std::cout << "Choose where to explore:\n";
	std::cout << "1.Explore the Library\n";
	std::cout << "2.Enter the Basement\n";
	std::cout << "3.Climb to the Attic\n";
	std::cout << "4.Open Bedroom Door\n";
	
	int choice;
	std::cin >> choice;
	switch (choice)
	{
	case 1: exploreLibrary(player); break;
	case 2: exploreBasement(player); break;
	case 3: exploreAttic(player); break;
	case 4:
		if (player.seachItem("Old Key"))
		{
			exploreBedroom(player);
		}
		else
		{
			std::cout << "The door to the bedroom is locked\n";
		}
		break;
	default:
		std::cout << "Invalid Choice. The Ghost are closing in!\n";
		break;
	}
}
void escapeManor()
{

}
void endingEscape(Player& player)
{
	std::cout << "You suuccessfully escape the haunted manor with the ghost trapped in the mirror!\n";
	player.showInventory();
	std::cout << "You live to tell the tale of the haunted Manor. Congratulations!\n";
}
void endingDefeat() 
{
	std::cout << "You succumb to the ghostly horrors of the manor...\n";
	std::cout << "Your adventure ends here.\n";
}
void endingStay() 
{
	std::cout << "You decide to stay in the haunted manor, never to be seen again...\n";
	std::cout << "Perhaps you'll become one of its many restless spirits.\n";
}
//main function
int main()
{
	system("color 04");

	if (!SetConsoleFont(L"", 40)) {
		// Handle error if needed
	}

	std::cout << "Welcome to 'Escape From The Haunted Manor'!\n";
	std::string playerName;
	std::cout << "Enter your name, brave adventure: ";
	std::cin >> playerName;
	Player player(playerName, 100);
	player.displayStats();
	while (true)
	{
		gameLoop(player);
		std::cout << "Do you want to explore more?(yes/no):";
		std::string choice;
		std::cin >> choice;
		if (choice == "no")
		{
			std::cout << "You decide to rest.Will you survive another day?\n";
			break;
		}
		if (player.seachItem("Ghost"))
		{
			escapeManor();
			exit(0);
		}
		system("cls");
	}
	std::cout << "Thanks for playing!\n";
	return 0;
}





