#pragma once
#include <vector>
#include <string>
#include <iostream>
#include "Utility.h"
#include "Player.h"
#include "Board.h"
#include <assert.h>


class Menu
{
public:
	//data members
	std::vector<std::string> m_chestContents =
	{
		//ARTIFACTS
		"HAND_OF_VECNA              ",
		"EYE_OF_VECNA               ",
		"BLACK_HEART                ",
		//Potions
		"POTION_OF_HEALTH           ",
		"POTION_OF_EXPERIENCE       ",
		"POTION_OF_STRENGTH         ",
		//Swords
		"WOODEN_SWORD               ",
		"STEEL_SWORD                ",
		"VORPAL_SWORD               ",
		//Armor
		"LEATHER_ARMOR              ",
		"SCALE_ARMOR                ",
		"PLATE_ARMOR                ",
		//Gold
		"5_GOLD                     ",
		"10_GOLD                    ",
		"50_GOLD                    ",
		"100_GOLD                   ",
		"500_GOLD                   ",
		"1000_GOLD                  ",
		//scrolls
		"MAGIC_MISSILE              ",
		"LIGHTNING_BOLT             ",
		"FIRE_BALL                  "

	};
	std::vector<std::string> m_investigateContents =
	{
		//WORK ON THESE INVESTIGATIONS
		//SMELL
		"The air smells most foul.  ",
		"A sweet smell is in the air",
		"There is a smell of sulfur.",
		//SIGHT
		"The area is dimly lit.     ",
		"A deep and ominous orange light, poors out from the doorway.",
		"Tapestries of many eyed men fill the room. Blood stains to\n"
		"cobblestone and human remains hang from.",
		"There is soot in the air.  ",
		//SOUND
		"Screams come from the exit.",
		"Whispers from the darkness.",
		"A voice whispers 'lies....'",
		"My ears are ringing.       ",
		"Sound of scraping stone.   ",
		//FEEL
		"It is much colder here.    ",
		"It is very hot in this room",
		"I feel a tap on the shoulder",
	};
	int m_currentMenu;
	HANDLE ScreenBuffer = GetStdHandle(STD_OUTPUT_HANDLE);



	//constructor
	Menu();



	//member functions
	void displayCurrentMenu(std::vector<std::string> inventory, std::string classType);



public:
	//Primary menus
	void openMainMenu(std::string classType);
	void openClassSelectionMenu();
	void openNameSelectionMenu();
	void openDirectionMenu();
	void openInteractMenu();
	void openInventoryMenu(std::vector<std::string> &inventory);
	void openInventoryMenuSubMenu();



	//Secondary Menus
	std::string openChestMenu();
	void openInvestigateMenu();



	//Menu Navigation
	int mainMenuSolution(std::vector<std::string> &inventory, bool isOnValidChest, std::string classType);
	int directionMenuSolution(std::string classType);
	int interactMenuSolution(std::vector<std::string>& inventory, bool isOnValidChest, std::string classType);
	int inventoryMenuSolution(std::string classType);
	int chestMenuSolution(std::vector<std::string> &inventory, std::string classType);
	int inventorySubMenuSolution();
	int navigateMenus(std::vector<std::string> &inventory, bool isOnValidChest, std::string classType);



	//helper functions
	bool inventoryFull(std::vector<std::string> inventory);
	int indexOfNextAvailableInventorySlot(std::vector<std::string> inventory);
};