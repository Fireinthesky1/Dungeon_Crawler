#include "Menu.h"


//constructor
Menu::Menu()
	: m_currentMenu(1)
{
	
}



void Menu::displayCurrentMenu(std::vector<std::string> inventory, std::string classType)
{
	switch (m_currentMenu)
	{
	case 1:
		openMainMenu(classType);
		break;
	case 2:
		openDirectionMenu();
		break;
	case 3:
		openInteractMenu();
		break;
	case 4:
		openInventoryMenu(inventory);
		break;
	case 5:
		openChestMenu();
		break;
	case 6:
		openInvestigateMenu();
		break;
	case 8:
		openSymbolsMenu();
		break;
	}
}



void Menu::openMainMenu(std::string classType)
{
	m_currentMenu = 1;
	std::string line1 = "|1:MOVE                       |";
	std::string line2 = "|2:CHANGE_DIRECTION           |";
	std::string line3 = "|3:ATTACK                     |";
	std::string line4 = "|4:INTERACT                   |";
	std::string line5 = "|5:CHECK_FOR_TRAPS            |";
	std::string line6 = "|6:OPEN_INVENTORY             |";
	std::string line7 = "";
	if (classType == "PRIEST ")
		line7 = "|7:HEAL                       |";
	std::string line8 = "|8:OPEN_SYMBOL_MENU           |";

	std::cout << line1 << std::endl;
	std::cout << line2 << std::endl;
	std::cout << line3 << std::endl;
	std::cout << line4 << std::endl;
	std::cout << line5 << std::endl;
	std::cout << line6 << std::endl;
	if (classType == "PRIEST ")
		std::cout << line7 << std::endl;
	else
		std::cout << line7;
	std::cout << line8 << std::endl;
	std::cout << '\n';
}



void Menu::openClassSelectionMenu()
{
	std::string line1 = "|Pick your Class:         |";
	std::string line2 = "|1:FIGHTER                |";
	std::string line3 = "|2:WIZARD                 |";
	std::string line4 = "|3:PRIEST                 |";

	std::cout << line1 << std::endl;
	std::cout << line2 << std::endl;
	std::cout << line3 << std::endl;
	std::cout << line4 << std::endl;
}



void Menu::openNameSelectionMenu()
{
	std::string line1 = "|Please enter your name          |";

	std::cout << line1 << std::endl;
}



void Menu::openDirectionMenu()
{
	m_currentMenu = 2;
	std::string line1 = "|1:NORTH                      |";
	std::string line2 = "|2:EAST                       |";
	std::string line3 = "|3:SOUTH                      |";
	std::string line4 = "|4:WEST                       |";
	std::string line5 = "|5:EXIT_SUBMENU               |";

	std::cout << line1 << std::endl;
	std::cout << line2 << std::endl;
	std::cout << line3 << std::endl;
	std::cout << line4 << std::endl;
	std::cout << line5 << std::endl;
}



void Menu::openInteractMenu()
{
	m_currentMenu = 3;
	std::string line1 = "|1:OPEN_DOOR                  |";
	std::string line2 = "|2:OPEN_CHEST                 |";
	std::string line3 = "|3:TALK                       |";
	std::string line4 = "|4:INVESTIGATE                |";
	std::string line5 = "|5:EXIT_SUBMENU               |";

	std::cout << line1 << std::endl;
	std::cout << line2 << std::endl;
	std::cout << line3 << std::endl;
	std::cout << line4 << std::endl;
	std::cout << line5 << std::endl;
}



void Menu::openInventoryMenu(std::vector<std::string> &inventory)
{
	m_currentMenu = 4;
	std::string line1 = "|1:" + inventory[0] + "|";
	std::string line2 = "|2:" + inventory[1] + "|";
	std::string line3 = "|3:" + inventory[2] + "|";
	std::string line4 = "|4:" + inventory[3] + "|";
	std::string line5 = "|5:" + inventory[4] + "|";
	std::string line6 = "|6:EXIT_SUBMENU               |";

	std::cout << line1 << std::endl;
	std::cout << line2 << std::endl;
	std::cout << line3 << std::endl;
	std::cout << line4 << std::endl;
	std::cout << line5 << std::endl;
	std::cout << line6 << std::endl;
}



void Menu::openInventoryMenuSubMenu()
{
	m_currentMenu = 5;
	std::string line1 = "|WHAT WOULD YOU LIKE TO DO?   |";
	std::string line2 = "|1:USE		              |";
	std::string line3 = "|2:DROP                       |";
	std::string line4 = "|3:EXIT_SUBMENU               |";

	std::cout << line1 << std::endl;
	std::cout << line2 << std::endl;
	std::cout << line3 << std::endl;
	std::cout << line4 << std::endl;
}



std::string Menu::openChestMenu()
{
	m_currentMenu = 6;
	std::string item = m_chestContents[rand() % m_chestContents.size()];
	std::string line1 = "|" + item + "  |";
	std::string line2 = "|1:TAKE                       |";
	std::string line3 = "|2:EXIT_SUBMENU               |";

	std::cout << line1 << std::endl;
	std::cout << line2 << std::endl;
	std::cout << line3 << std::endl;

	return item;
}



void Menu::openInvestigateMenu()
{
	m_currentMenu = 6;
	std::string line1 = "|1:" + m_investigateContents[rand() % m_investigateContents.size()] + "|";
	std::cout << line1 << std::endl;
}



int Menu::mainMenuSolution(std::vector<std::string> &inventory, bool isOnValidChest, std::string classType)
{
	int input = getUserInputInt(1, 8);

	switch (input)
	{
	case 1:
		//Move
		return 1;
		break;
	case 2:
		openDirectionMenu();
		return directionMenuSolution(classType);
		break;
	case 3:
		//Attack
		return 6;
		break;
	case 4:
		openInteractMenu();
		return interactMenuSolution(inventory, isOnValidChest, classType);
		break;
	case 5:
		//check for traps
		return 11;
		break;
	case 6:
		//open inventory
		openInventoryMenu(inventory);
		return inventoryMenuSolution(classType);
		break;
	case 7:
		//heal
		if (classType == "PRIEST ")
		{
			return 22;
		}
		else
		{
			return 24;
		}
		break;
	case 8:
		//open Symbols menu
		openSymbolsMenu();
		return symbolsMenuSolution(classType);
		break;
	default:
		//Jump back to main
		openMainMenu(classType);
		return 24;
		break;
	}
}



void Menu::openSymbolsMenu()
{
	m_currentMenu = 8;
	std::string line1 = "|*:DOOR                       |";
	std::string line2 = "|$:CHEST or MIMIC             |";
	std::string line3 = "|/:STAIRCASE                  |";
	std::string line4 = "|T:TRAP                       |";
	std::string line5 = "|B:BAT or BUGBEAR             |";
	std::string line6 = "|C:CULTIST                    |";
	std::string line7 = "|G:GOBLIN                     |";
	std::string line8 = "|M:MUMMY                      |";
	std::string line9 = "|O:ORC                        |";
	std::string line10 = "|P:PURPLEWORM                 |";
	std::string line11 = "|R:RAT                        |";
	std::string line12 = "|S:SKELETON or SPIDER         |";
	std::string line13 = "|Z:ZOMBIE                     |";
	std::string line14 = "|PRESS ANY NUMBER TO EXIT MENU|";

	std::cout << line1 << std::endl;
	std::cout << line2 << std::endl;
	std::cout << line3 << std::endl;
	std::cout << line4 << std::endl;
	std::cout << line5 << std::endl;
	std::cout << line6 << std::endl;
	std::cout << line7 << std::endl;
	std::cout << line8 << std::endl;
	std::cout << line9 << std::endl;
	std::cout << line10 << std::endl;
	std::cout << line11 << std::endl;
	std::cout << line12 << std::endl;
	std::cout << line13 << std::endl;
	std::cout << line14 << std::endl;
}



int Menu::symbolsMenuSolution(std::string classType)
{
	clearInputBuffer();
	int input = getUserInputInt(0, 9);
	switch (input)
	{
	default:
		openMainMenu(classType);
		return 24;
		break;
	}
}



int Menu::directionMenuSolution(std::string classType)
{
	clearInputBuffer();
	int input = getUserInputInt(1, 5);

	switch (input)
	{
	case 1:
		//North
		return 2;
		break;
	case 2:
		//East
		return 3;
		break;
	case 3:
		//South
		return 4;
		break;
	case 4:
		//West
		return 5;
		break;
	case 5:
		openMainMenu(classType);
		//Jump back to main
		return 24;
		break;
	default:
		//Jump back to main
		openMainMenu(classType);
		return 24;
		break;
	}

}



int Menu::interactMenuSolution(std::vector<std::string> &inventory, bool isOnValidChest, std::string classType)
{
	clearInputBuffer();
	int input = getUserInputInt(1, 5);

	switch (input)
	{
	case 1:
		//Enter new room
		return 7;
		break;
	case 2:
		//See if player is on chest
		if (!isOnValidChest)
			return 24;
		return chestMenuSolution(inventory, classType);
		break;
	case 3:
		//Resolve Dialogue
		return 9;
		break;
	case 4:
		//Resolve investigate
		return 10;
		break;
	case 5:
		//Jump back to main
		openMainMenu(classType);
		return 24;
		break;
	default:
		//Jump back to main
		openMainMenu(classType);
		return 24;
		break;
	}
}



int Menu::inventoryMenuSolution(std::string classType)
{
	clearInputBuffer();
	int input = getUserInputInt(1, 6);
	int decision;

	switch (input)
	{
	case 1:
		openInventoryMenuSubMenu();
		decision = inventorySubMenuSolution();
		if (decision == 1)
			//use inventory item 1
			return 12;
		else if (decision == 2)
			//drop inventory item 1
			return 13;
		else if (decision == 3)
			//jump back to main
			openMainMenu(classType);
			return 24;
		break;
	case 2:
		openInventoryMenuSubMenu();
		decision = inventorySubMenuSolution();
		if (decision == 1)
			//use inventory item 2
			return 14;
		else if (decision == 2)
			//drop inventory item 2
			return 15;
		else if (decision == 3)
			//jump back to main
			openMainMenu(classType);
		return 24;
		break;
	case 3:
		openInventoryMenuSubMenu();
		decision = inventorySubMenuSolution();
		if (decision == 1)
			//use inventory item 3
			return 16;
		else if (decision == 2)
			//drop inventory item 3
			return 17;
		else if (decision == 3)
			//jump back to main
			openMainMenu(classType);
		return 24;
		break;
	case 4:
		openInventoryMenuSubMenu();
		decision = inventorySubMenuSolution();
		if (decision == 1)
			//use inventory item 4
			return 18;
		else if (decision == 2)
			//drop inventory item 4
			return 19;
		else if (decision == 3)
			//jump back to main
			openMainMenu(classType);
		return 24;
		break;
	case 5:
		openInventoryMenuSubMenu();
		decision = inventorySubMenuSolution();
		if (decision == 1)
			//use inventory item 5
			return 20;
		else if (decision == 2)
			//drop inventory item 5
			return 21;
		else if (decision == 3)
			//jump back to main
			openMainMenu(classType);
		return 24;
		break;
	case 6:
		//Jump back to main
		openMainMenu(classType);
		return 24;
		break;
	default:
		//Jump back to main
		openMainMenu(classType);
		return 24;
		break;
	}
}



int Menu::chestMenuSolution(std::vector<std::string> &inventory, std::string classType)
{
	std::string item = openChestMenu();
	clearInputBuffer();
	int input = getUserInputInt(1,2);
	switch (input)
	{
	case 1:
		//Attempt to add item to inventory
		if (!inventoryFull(inventory))
		{
			//This assumes a valid output from indexOfNextAvailableInventorySlot
			int index = indexOfNextAvailableInventorySlot(inventory);
			assert(index != -1);
			inventory[index] = item;
			//resolve chest interaction
			return 8;
		}
		//inventory was full jump back to main
		return 24;
		break;
	case 2:
		//Jump back to main
		openMainMenu(classType);
		return 24;
		break;
	default:
		abort();
		break;
	}
}



int Menu::inventorySubMenuSolution()
{
	clearInputBuffer();
	int input = getUserInputInt(1, 3);
	return input;
}



int Menu::navigateMenus(std::vector<std::string> &inventory, bool isOnValidChest, std::string classType)
{
	return mainMenuSolution(inventory, isOnValidChest, classType);
}



bool Menu::inventoryFull(std::vector<std::string> inventory)
{
	for (int i = 0; i < inventory.size(); i++)
	{
		if (inventory[i].at(0) == ' ')
			return false;
	}

	return true;
}



int Menu::indexOfNextAvailableInventorySlot(std::vector<std::string> inventory)
{
	for (int i = 0; i < inventory.size(); i++)
	{
		if (inventory[i].at(0) == ' ')
			return i;
	}
	//This indicates failure (There is no available inventory slot)
	return -1;
}