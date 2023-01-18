/*Game Logic Layer
	-All updates to the game state will be done here*/

//STATUS
/*
*	-Need to implement AI
*/
#pragma once
#include <vector>
#include <iostream>
#include <assert.h>

#include "Menu.h"
#include "Utility.h"
#include "Board.h"

#include "Player.h"
#include "Fighter.h"
#include "Wizard.h"
#include "Priest.h"

#include "Monster.h"
#include "Skeleton.h"
#include "Zombie.h"
#include "Spider.h"
#include "Goblin.h"
#include "Orc.h"
#include "Bugbear.h"
#include "Cultist.h"
#include "Mummy.h"
#include "Rat.h"
#include "Bat.h"
#include "Mimic.h"
#include "PurpleWorm.h"

#include <windows.h>


class Game
{
public:
	//member variables
	int m_turn; 
	bool m_gameOver, m_vecnaIsDead, m_notFirstPlaythrough = false;

	Board m_board;
	Menu m_menu;
	std::vector<Monster> m_monsters;
	Player *player;



	//Console Handles
	HANDLE ScreenBuffer = GetStdHandle(STD_OUTPUT_HANDLE);

	

	//constructor
	Game()
	{
		//Start the game loop
		playGame();
	}



	//When using the hand of vecna a monster was reduced to 0 hp and didn't go away till the next action
	void checkForSlainMonsters()
	{
		for (int i = 0; i < m_monsters.size(); i++)
		{
			if (m_monsters[i].m_currentHealth <= 0)
			{
				//give xp, remove the body, kill the monster, refresh the board
				(*player).m_xp += m_monsters[i].m_xpValue;
				m_board.markRoom(m_monsters[i].m_yCoord, m_monsters[i].m_xCoord,' ',m_board.m_currentRoom);
				m_monsters.erase(m_monsters.begin()+i);
			}
		}
		//TEST CODE
		m_board.refreshBoard();
		//refresh monsters
		for (Monster m : m_monsters)
		{
			m_board.markRoom(m.m_yCoord, m.m_xCoord, m.getSymbol(), m_board.m_currentRoom);
		}
		//refresh player
		m_board.markRoom((*player).m_yCoord, (*player).m_xCoord, (*player).getName().at(0), m_board.m_currentRoom);
	}



	void checkForTraps()
	{
		m_board.m_trapsChecked = true;
		m_board.refreshBoard();
		//TEST CODE
		//refresh monsters
		for (Monster m : m_monsters)
		{
			m_board.markRoom(m.m_yCoord, m.m_xCoord, m.getSymbol(), m_board.m_currentRoom);
		}
		m_board.markRoom((*player).m_yCoord, (*player).m_xCoord, (*player).getName().at(0), m_board.m_currentRoom);
	}



	void checkGameOver()
	{
		if (!(*player).isAlive())
		{
			clearScreen(ScreenBuffer);
			std::cout << "The dungeons of Chaos have defeated you and Vecna Lives" << "\n" << std::endl;
			if (playAgain())
			{
				playGame();
			}
			else
			{
				m_gameOver = true;
				clearScreen(ScreenBuffer);
				std::cout << "Thanks for playing!" << std::endl;
			}
		}
		else if (vecnaIsDead())
		{
			clearScreen(ScreenBuffer);
			std::cout << (*player).getName() << " " << "has destroyed Vecna. Peace is restored to the multiverse!" << "\n" << std::endl;
			if (playAgain())
			{
				playGame();
			}
			else
			{
				m_gameOver = true;
				clearScreen(ScreenBuffer);
				std::cout << "Thanks for playing!" << std::endl;
			}
		}
	}



	void combat(Entity& attacker)
	{
		//determine if the attacker is a monster or a player
		//monster
		if (m_turn % 2 == 0)
		{
			//doing this because all monsters have +5 to hit and will scale to dungeon level
			int adjustedArmorClass = (*player).m_armorClass - m_board.getCurrentDungeonLevel();
			assert(adjustedArmorClass >= 1);
			std::vector<int> attackSolution = attacker.attack(m_board, adjustedArmorClass, attacker.m_range);
			if (attacker.m_range)
			{
				(*player).hit(attackSolution[generateRandomNumber(1, 3)]);
			}
			else
			{
				if ((*player).getLocation()[0] == attackSolution[0] && (*player).getLocation()[1] == attackSolution[1])
					(*player).hit(attackSolution[2]);
			}
			
		}
		//player
		else
		{
			if ((*player).m_range)
			{
				for (Monster &m : m_monsters)
				{
					int damage = (*player).attack(m_board, m.m_armorClass, (*player).m_range)[generateRandomNumber(0,2)];
					m.hit(damage);
				}
			}
			else
			{
				for (Monster &m : m_monsters)
				{
					std::vector<int> attackSolution = (*player).attack(m_board, m.m_armorClass, (*player).m_range);
					if (m.getLocation()[0] == attackSolution[0] && m.getLocation()[1] == attackSolution[1])
					{
						m.hit(attackSolution[2]);
						return;
					}
				}
			}
		}
	}



	void computerChangeDirection(Monster& monster, int direction)
	{
		monster.changeDirection(direction);
	}



	void computerDetermineMove(Monster& monster)
	{
		//The anatomy of a dungeon room will be 2 ranged and 2 melee.
		//Each melee monster will have a different attack behavior
		//monsterType chart
		/*
		1:  skeleton	(range == true)
		2:  zombie		(range == false) (behavior 1)
		3:  spider		(range == false) (behavior 1)
		4:  Goblin		(range == false) (behavior 1)
		5:  Orc			(range == false) (behavior 1)
		6:  Bugbear		(range == true)
		7:  Cultist		(range == true)
		8:  Mummy		(range == false) (behavior 2)
		9:  Rat			(range == false) (behavior 2)
		10: Bat			(range == false) (behavior 2)
		11: Mimic		(range == false) (behavior 2)
		12: Purpleworm	(range == true)
		*/
		
		//if monster has 0 or less HP return
		if (monster.m_currentHealth <= 0) { return; }

		//ranged types won't move, just shoot every round
		if (monster.m_range)
		{
			combat(monster);
			return;
		}

		int type = monster.m_monsterType;

		int playerY = player->m_yCoord;
		int playerX = player->m_xCoord;
		int y = monster.m_yCoord;
		int x = monster.m_xCoord;
		int direction = monster.m_direction;

		if (type > 1 && type < 6)
		{
			//determine north south standing (get into melee range)
			if (playerY < y - 1 && direction == 1)		//player: north. monster: facing north. move.
			{
				move(monster);
			}
			else if (playerY < y - 1 && direction != 1) //player: north. monster: facing !north. turn.
			{
				computerChangeDirection(monster, 1);
				computerDetermineMove(monster);
			}
			else if (playerY > y + 1 && direction == 3) //player: south. monster: facing south. move.
			{
				move(monster);
			}
			else if (playerY > y + 1 && direction != 3) //player: south. monster: !facing south. turn.
			{
				computerChangeDirection(monster, 3);
				computerDetermineMove(monster);
			}
			//determine east west standing (get into melee range)
			else if (playerX < x - 1 && direction == 4) //player: west. monster: facing west. move.
			{
				move(monster);
			}
			else if (playerX < x - 1 && direction != 4) //player: west. monster: !facing west. turn.
			{
				computerChangeDirection(monster, 4);
				computerDetermineMove(monster);
			}
			else if (playerX > x + 1 && direction == 2) //player: east. monster: facing east. move.
			{
				move(monster);
			}
			else if (playerX > x + 1 && direction != 2) //player: east. monster: !facing east. turn.
			{
				computerChangeDirection(monster, 2);
				computerDetermineMove(monster);
			}
			//In range; turn or attack
			//test-------------------------------------------------------------------------------------------
			else if (playerY == y - 1 && playerX == x && direction == 1) //player to north x == x fire
			{
				combat(monster);
			}
			else if (playerY == y + 1 && playerX == x && direction == 3) //player to south x == x fire
			{
				combat(monster);
			}
			else if (playerX == x - 1 && playerY == y && direction == 4) //player to west y == y
			{
				combat(monster);
			}
			else if (playerX == x + 1 && playerY == y && direction == 2) //player to east y == y
			{
				combat(monster);
			}
			else if (playerY == y - 1 && playerX != x) //player to north but off x by 1
			{
				if (playerX > x)
				{
					computerChangeDirection(monster, 2);
					move(monster);
					computerChangeDirection(monster, 1);
				}
				else if (playerX < x)
				{
					computerChangeDirection(monster, 4);
					move(monster);
					computerChangeDirection(monster, 1);
				}
			}
			else if (playerY == y + 1 && playerX != x) //player to south but off x by 1
			{
				if (playerX > x)
				{
					computerChangeDirection(monster,2);
					move(monster);
					computerChangeDirection(monster, 3);
				}
				else if(playerX < x)
				{
					computerChangeDirection(monster, 4);
					move(monster);
					computerChangeDirection(monster, 3);
				}
			}
			else if (playerX == x - 1 && playerY != y) //player to west but off y by 1
			{
				if (playerY > y)
				{
					computerChangeDirection(monster, 3);
					move(monster);
					computerChangeDirection(monster, 4);
				}
				else if (playerY < y)
				{
					computerChangeDirection(monster, 1);
					move(monster);
					computerChangeDirection(monster, 4);
				}
			}
			else if (playerX == x + 1 && playerY != y) //player to east but off y by 1
			{
				if (playerY > y)
				{
					computerChangeDirection(monster, 3);
					move(monster);
					computerChangeDirection(monster, 2);
				}
				else if (playerY < y)
				{
					computerChangeDirection(monster, 1);
					move(monster);
					computerChangeDirection(monster, 2);
				}
			}
			//test---------------------------------------------------------------------------------------
			else
			{
				combat(monster);
			}
		}
		else
		{
			//determine east west standing (get into melee range)
			if (playerX < x - 1 && direction == 4)		//player: west. monster: facing west. move.
			{
				move(monster);
			}
			else if (playerX < x - 1 && direction != 4) //player: west. monster: !facing west. turn.
			{
				computerChangeDirection(monster, 4);
				computerDetermineMove(monster);
			}
			else if (playerX > x + 1 && direction == 2) //player: east. monster: facing east. move.
			{
				move(monster);
			}
			else if (playerX > x + 1 && direction != 2) //player: east. monster: !facing east. turn.
			{
				computerChangeDirection(monster, 2);
				computerDetermineMove(monster);
			}
			//determine north south standing (get into melee range)
			else if (playerY < y - 1 && direction == 1)	//player: north. monster: facing north. move.
			{
				move(monster);
			}
			else if (playerY < y - 1 && direction != 1) //player: north. monster: facing !north. turn.
			{
				computerChangeDirection(monster, 1);
				computerDetermineMove(monster);
			}
			else if (playerY > y + 1 && direction == 3) //player: south. monster: facing south. move.
			{
				move(monster);
			}
			else if (playerY > y + 1 && direction != 3) //player: south. monster: !facing south. turn.
			{
				computerChangeDirection(monster, 3);
				computerDetermineMove(monster);
			}
			//In range; turn or attack
			else if (playerY < y && direction != 1)		//player: north. monster: !facing north. turn.
			{
				computerChangeDirection(monster, 1);
				computerDetermineMove(monster);
			}
			else if (playerY > y && direction != 3)		//player: south. monster: !facing south. turn.
			{
				computerChangeDirection(monster, 3);
				computerDetermineMove(monster);
			}
			else if (playerX < x && direction != 4)		//player: west. monster: !facing west. turn.
			{	
				computerChangeDirection(monster, 4);
				computerDetermineMove(monster);
			}
			else if (playerX > x && direction != 2)		//player: east. monster: !facing east. turn.
			{
				computerChangeDirection(monster, 2);
				computerDetermineMove(monster);
			}
			//In range; turn or attack
			//test-------------------------------------------------------------------------------------------
			else if (playerX == x - 1 && playerY == y && direction == 4) //player to west y == y
			{
				combat(monster);
			}
			else if (playerX == x + 1 && playerY == y && direction == 2) //player to east y == y
			{
				combat(monster);
			}
			else if (playerY == y - 1 && playerX == x && direction == 1) //player to north x == x fire
			{
				combat(monster);
			}
			else if (playerY == y + 1 && playerX == x && direction == 3) //player to south x == x fire
			{
				combat(monster);
			}
			else if (playerX == x - 1 && playerY != y) //player to west but off y by 1
			{
				if (playerY > y)
				{
					computerChangeDirection(monster, 3);
					move(monster);
					computerChangeDirection(monster, 4);
				}
				else if (playerY < y)
				{
					computerChangeDirection(monster, 1);
					move(monster);
					computerChangeDirection(monster, 4);
				}
			}
			else if (playerX == x + 1 && playerY != y) //player to east but off y by 1
			{
				if (playerY > y)
				{
					computerChangeDirection(monster, 3);
					move(monster);
					computerChangeDirection(monster, 2);
				}
				else if (playerY < y)
				{
					computerChangeDirection(monster, 1);
					move(monster);
					computerChangeDirection(monster, 2);
				}
			}
			else if (playerY == y - 1 && playerX != x) //player to north but off x by 1
			{
				if (playerX > x)
				{
					computerChangeDirection(monster, 2);
					move(monster);
					computerChangeDirection(monster, 1);
				}
				else if (playerX < x)
				{
					computerChangeDirection(monster, 4);
					move(monster);
					computerChangeDirection(monster, 1);
				}
			}
			else if (playerY == y + 1 && playerX != x) //player to south but off x by 1
			{
				if (playerX > x)
				{
					computerChangeDirection(monster, 2);
					move(monster);
					computerChangeDirection(monster, 3);
				}
				else if (playerX < x)
				{
					computerChangeDirection(monster, 4);
					move(monster);
					computerChangeDirection(monster, 3);
				}
			}
			//test---------------------------------------------------------------------------------------
			else
			{
				combat(monster);
			}
		}

	}



	Monster computerInitializeCharacter(int left, int right, int override)
	{
		int type;
		//randomly determine monster type
		if (override)
			type = override;
		else

			type = generateRandomNumber(left, right);
		Monster m;
		switch (type)
		{
		case 1:
			m = Skeleton();
			break;
		case 2:
			m = Zombie();
			break;
		case 3:
			m = Spider();
			break;
		case 4:
			m = Goblin();
			break;
		case 5:
			m = Orc();
			break;
		case 6:
			m = Bugbear();
			break;
		case 7:
			m = Cultist();
			break;
		case 8:
			m = Mummy();
			break;
		case 9:
			m = Rat();
			break;
		case 10:
			m = Bat();
			break;
		case 11:
			m = Mimic();
			break;
		case 12:
			m = PurpleWorm();
			break;
		default:
			clearScreen(ScreenBuffer);
			std::cout << "Failed to initialize Monster" << std::endl;
			abort();
			break;
		}

		//set health appropriately to max
		m.m_currentHealth = m.m_maxHealth;

		//set damage appropriatley by dungeon level
		m.m_doDamageMax *= m_board.getCurrentDungeonLevel();

		//Set xp value appropriately by dungeon level
		m.m_xpValue *= m_board.getCurrentDungeonLevel();

		return m;
	}



	void computerInitializeCharacters()
	{
		//empty the monster vector and the positions vector
		m_monsters.clear();

		//choose a random number of monsters for the room
		int numMonsters = (m_board.m_isBossRoom) ?  5 : generateRandomNumber(1, 4);


		//Fill the monster array
		for (int i = 0; i < numMonsters; i++)
		{
			switch (i)
			{
			case 0:
				//range
				m_monsters.push_back(computerInitializeCharacter(1,1,1));
				break;
			case 1:
				//behavior group 1
				m_monsters.push_back(computerInitializeCharacter(2,5,0));
				break;
			case 2:
				//range
				m_monsters.push_back(computerInitializeCharacter(6,7,0));
				break;
			case 3:
				//behavior group 2
				m_monsters.push_back(computerInitializeCharacter(8,11,0));
				break;
			default:
				//worm
				m_monsters.push_back(computerInitializeCharacter(12, 12, 12));
				break;
			}
		}

		//Place the monsters in the room
		initializeComputerPositions();
	}



	void computerTakeTurn(Monster& monster)
	{
		computerDetermineMove(monster);
	}



	void dropInventorySlot(int slot)
	{
		assert(slot >= 0 && slot < (*player).m_inventory.size());
		(*player).m_inventory[slot] = "                           ";
	}



	//This function determines the type of room we are in, whether or not we are on an exit
	//which direction that exit is then calls initializeNewRoom(exitDirection) 
	//and updates the character's location
	void exitRoom()
	{
		//Get the current Character Location
		std::vector<int> playerLocation = (*player).getLocation();
		int playerY = playerLocation[0];
		int playerX = playerLocation[1];
		int entranceY = m_board.getExitLocations()[0];
		int entranceX = m_board.getExitLocations()[1];
		int exitY = m_board.getExitLocations()[2];
		int exitX = m_board.getExitLocations()[3];
		bool isHorizontalCorridor = m_board.getCurrentRoomRows() == 1;
		bool isVerticalCorridor = m_board.getCurrentRoomColumns() == 1;

		//Check if stairCase
		if (m_board.m_isBossRoom && playerLocation[0] == 10 && playerLocation[1] == 10)
		{
			//Generate a new Starting Room
			m_board.initializeNewRoom(rand() % 4 + 1);
			
			//Update current Floor
			m_board.setCurrentDungeoneLevel( m_board.getCurrentDungeonLevel() + 1);

			//Update Player Location
			(*player).m_yCoord = m_board.getCurrentRoomRows() / 2;
			(*player).m_xCoord = m_board.getCurrentRoomColumns() / 2;

			//initialize monsters in the new room
			computerInitializeCharacters();
		}
		

		//Verticle Passage North Exit
		if (((playerY == entranceY && playerX == entranceX) || (playerY == exitY && playerX == exitX))
			&& playerY == 0 && playerX == 0 && isVerticalCorridor)
		{
			//If we're on an exit location. There is only one Column, my y is 0, and my x is 0 then exit location == North
			m_board.initializeNewRoom(1);
			//Update player location
			(*player).m_yCoord = m_board.getExitLocations()[0];
			(*player).m_xCoord = m_board.getExitLocations()[1];
			
			//initialize monsters in the new room
			computerInitializeCharacters();
		}

		//Horizontal Passage East Exit
		else if (((playerY == entranceY && playerX == entranceX) || (playerY == exitY && playerX == exitX))
			&& playerY == 0 && playerX != 0 && isHorizontalCorridor)
		{
			//If we're on an exit location. There is only one row, my y is 0 and my x is not 0 then exit location == East
			m_board.initializeNewRoom(2);
			//Update player location
			(*player).m_yCoord = m_board.getExitLocations()[0];
			(*player).m_xCoord = m_board.getExitLocations()[1];
			
			//initialize monsters in the new room
			computerInitializeCharacters();
		}

		//Verticle passage South Exit
		else if (((playerY == entranceY && playerX == entranceX) || (playerY == exitY && playerX == exitX))
			&& playerY != 0 && playerX == 0 && isVerticalCorridor)
		{
			//If we're on an exit location. There is only one Column, my y is not 0, and my x is 0 then exit location == South
			m_board.initializeNewRoom(3);
			//Update player location
			(*player).m_yCoord = m_board.getExitLocations()[0];
			(*player).m_xCoord = m_board.getExitLocations()[1];

			//initialize monsters in the new room
			computerInitializeCharacters();
		}

		//Horizontal passage West exit
		else if (((playerY == entranceY && playerX == entranceX) || (playerY == exitY && playerX == exitX))
			&& playerY == 0 && playerX == 0 && isHorizontalCorridor)
		{
			//If we're on an exit location. There is only one row, my y is 0 and my x is 0 then exit location == West
			m_board.initializeNewRoom(4);
			//Update player location
			(*player).m_yCoord = m_board.getExitLocations()[0];
			(*player).m_xCoord = m_board.getExitLocations()[1];

			//initialize monsters in the new room
			computerInitializeCharacters();
		}

		//Standard Room North Exit
		else if (((playerY == entranceY && playerX == entranceX) || (playerY == exitY && playerX == exitX))
			&& playerY == 0)
		{
			//If we're on an exit location and y is 0 then exit location == North
			m_board.initializeNewRoom(1);
			//Update player location
			(*player).m_yCoord = m_board.getExitLocations()[0];
			(*player).m_xCoord = m_board.getExitLocations()[1];

			//initialize monsters in the new room
			computerInitializeCharacters();
		}

		//Standard Room East Exit
		else if (((playerY == entranceY && playerX == entranceX) || (playerY == exitY && playerX == exitX))
			&& playerX == m_board.getCurrentRoomColumns() - 1)
		{
			//If we're on an exit location and x is max then exit location == East
			m_board.initializeNewRoom(2);
			//Update player location
			(*player).m_yCoord = m_board.getExitLocations()[0];
			(*player).m_xCoord = m_board.getExitLocations()[1];

			//initialize monsters in the new room
			computerInitializeCharacters();
		}

		//Standard Room South Exit
		else if (((playerY == entranceY && playerX == entranceX) || (playerY == exitY && playerX == exitX))
			&& playerY == m_board.getCurrentRoomRows() - 1)
		{
			//If we're on an exit location and y is max then exit location == South
			m_board.initializeNewRoom(3);
			//Update player location
			(*player).m_yCoord = m_board.getExitLocations()[0];
			(*player).m_xCoord = m_board.getExitLocations()[1];

			//initialize monsters in the new room
			computerInitializeCharacters();
		}

		//Standard Room West Exit
		else if (((playerY == entranceY && playerX == entranceX) || (playerY == exitY && playerX == exitX))
			&& playerX == 0)
		{
			//If we're on an exit location and x is 0 then exit location == West
			m_board.initializeNewRoom(4);
			//Update player location
			(*player).m_yCoord = m_board.getExitLocations()[0];
			(*player).m_xCoord = m_board.getExitLocations()[1];

			//initialize monsters in the new room
			computerInitializeCharacters();
		}
	}



	//This function returns the index of the inventory item type you pass into it 
	//(1 for swords, 2 for armor, 3 for gold, 4 for scroll)
	int indexOfInventoryItemType(int itemType)
	{
		//sword
		if (itemType == 1)
		{
			for (int i = 0; i < (*player).m_inventory.size(); i++)
			{
				if ((*player).m_inventory[i].find("SWORD", 0) != std::string::npos)
				{
					return i;
				}
				else if((*player).m_inventory[i].find("BLACK", 0) != std::string::npos)
				{
					return i;
				}
			}
		}
		//armor
		else if (itemType == 2)
		{
			for (int i = 0; i < (*player).m_inventory.size(); i++)
			{
				if ((*player).m_inventory[i].find("ARMOR", 0) != std::string::npos)
					return i;
			}
		}
		//gold
		else if (itemType == 3)
		{
			for (int i = 0; i < (*player).m_inventory.size(); i++)
			{
				if ((*player).m_inventory[i].find("GOLD", 0) != std::string::npos)
					return i;
			}
		}
		//scroll
		else if (itemType == 4)
		{
			for (int i = 0; i < (*player).m_inventory.size(); i++)
			{
				if ((*player).m_inventory[i].find("MAGIC", 0) != std::string::npos)
					return i;
				else if ((*player).m_inventory[i].find("LIGHTNING", 0) != std::string::npos)
					return i;
				else if ((*player).m_inventory[i].find("FIRE", 0) != std::string::npos)
					return i;
			}
		}

		return -1;
	}



	void initializeComputerPositions()
	{
		
		int playerY = (*player).m_yCoord;
		int playerX = (*player).m_xCoord;
		std::vector<int> playerPosition{ playerY, playerX };

		std::vector<std::vector<int>> occupiedPositions{ playerPosition };


		for (Monster &m : m_monsters)
		{																										
			std::vector<int> monsterPosition = randomRoomLocation();											
																												
			for (std::vector<int> position : occupiedPositions)													
			{																									
				if (monsterPosition[0] == position[0] && monsterPosition[1] == position[1])						
				{																								
					while (monsterPosition[0] == position[0] && monsterPosition[1] == position[1])				
						monsterPosition = randomRoomLocation();													
				}																								
																												
			}																									
				//put the monster position into occupied positions												
				occupiedPositions.push_back(monsterPosition);													
																												
				//put the monster on the board																	
				m_board.markRoom(monsterPosition[0], monsterPosition[1], m.getSymbol(), m_board.m_currentRoom);	
																												
				//update the monster's locations fields															
				m.m_yCoord = monsterPosition[0];																
				m.m_xCoord = monsterPosition[1];																
		}
	}



	void initializeGame()
	{
		//Clear the screen
		clearScreen(ScreenBuffer);
		//Reset game over
		m_gameOver = false;
		//Bring vecna back
		m_vecnaIsDead = false;
		//Set dungeon Level to 1
		m_board.setCurrentDungeoneLevel(1);
		//reset chance to generateBossRoom
		m_board.setChanceToGenerateBossRoom(0);
		//Set turn to 1
		m_turn = 1;
		//Initialize new Room
		if (m_notFirstPlaythrough)
			m_board.initializeNewRoom(rand() % 4 + 1);
		//clear the monster vector
		m_monsters.clear();
		//Initialize the characters
		playerInitializeCharacter();
	}



	bool isOnValidChest()
	{
		int playerY = (*player).getLocation()[0];
		int playerX = (*player).getLocation()[1];
		int firstTreasureY = m_board.getTreasureLocations()[0];
		int firstTreasureX = m_board.getTreasureLocations()[1];
		int secondTreasureY = m_board.getTreasureLocations()[2];
		int secondTreasureX = m_board.getTreasureLocations()[3];

		//need to account for two chests on top of eachother
		if (playerY == firstTreasureY && playerX == firstTreasureX && !m_board.m_firstTreasureTaken)
			return true;
		else if (!m_board.m_isCorridor && playerY == secondTreasureY && playerX == secondTreasureX && !m_board.m_secondTreasureTaken)
			return true;
		else
			return false;
	}


	
	void move(Entity& e)
	{
		//Remove old mark
		m_board.markRoom(e.getLocation()[0], e.getLocation()[1], ' ', m_board.m_currentRoom);
		
		//Refresh the Board
		m_board.refreshBoard();

		//Move
		e.move(m_board);
		int ycoord = e.getLocation()[0];
		int xcoord = e.getLocation()[1];

		//refresh monsters
		for (Monster& m : m_monsters)																		  
		{																									  
			m_board.markRoom(m.m_yCoord, m.m_xCoord, m.getSymbol(), m_board.m_currentRoom);					  
		}																									  

		//Determine if you stepped on a trap
		resolveTraps(e);
		
		//Mark the room with your new location
		m_board.markRoom(ycoord, xcoord, e.getName().at(0) , m_board.m_currentRoom);
	}



	bool playAgain()
	{
		std::cout << "Would you like to play again?" << std::endl;
		std::cout << "1 for yes. 2 for no." << std::endl;
		int input = getUserInputInt(1, 2);

		if (input == 1)
			m_notFirstPlaythrough = true;
		else
			m_notFirstPlaythrough = false;

		return m_notFirstPlaythrough;
	}



	void playerChangeDirection()
	{
		int direction = getUserInputInt(1, 4);
		(*player).changeDirection(direction);
	}



	void playerInitializeCharacter()
	{
		clearScreen(ScreenBuffer);
		m_menu.openClassSelectionMenu();
		int input = getUserInputInt(1,3);

		clearScreen(ScreenBuffer);
		m_menu.openNameSelectionMenu();
		std::string name = getUserInputString();

		switch (input)
		{
		case 1:
			player = new Fighter();
			(*player).m_name = name;
			break;
		case 2:
			player = new Wizard();
			(*player).m_name = name;
			break;
		case 3:
			player = new Priest();
			(*player).m_name = name;
			break;
		default:
			std::cout << "ERROR PLAYER INITIALIZATION FAILED" << std::endl;
			abort();
			break;
		}

		(*player).m_yCoord = m_board.getCurrentRoomRows() / 2;
		(*player).m_xCoord = m_board.getCurrentRoomColumns() / 2;
		m_board.markRoom((*player).m_yCoord, (*player).m_xCoord, (*player).getSymbol(), m_board.m_currentRoom);
	}



	void playerTakeTurn()
	{
		playerDetermineMove();

		//if fighter reset number of attacks after move has been taken
		if ((*player).m_class == "FIGHTER")
		{
			Fighter* f = dynamic_cast<Fighter*>(player);
			f->m_currentNumAttacks = f->m_numAttacks;
		}
	}



	//This calls Menu::navigateMenus and decides behavior based on the return value of that function
	//WHEN TURNS START HAPPENING NEED TO DELETE UNNECESSARY PLAYERDETERMINEMOVE RECURSIVE CALLS
	//POTENTIALLY REPLACE THESE CALLS WITH AN INCREMENT OF TURN
	void playerDetermineMove()
	{
		m_menu.m_currentMenu = 1;
		refresh();
		int decision = m_menu.navigateMenus((*player).m_inventory, isOnValidChest(), (*player).m_class);
		switch (decision)
		{
		case 1:
			move((*player));
			break;
		case 2:
			(*player).changeDirection(1);
			playerDetermineMove();
			break;
		case 3:
			(*player).changeDirection(2);
			playerDetermineMove();
			break;
		case 4:
			(*player).changeDirection(3);
			playerDetermineMove();
			break;
		case 5:
			(*player).changeDirection(4);
			playerDetermineMove();
			break;
		case 6:
			//TEST THIS
			if ((*player).m_class == "FIGHTER")
			{
				Fighter* f = dynamic_cast<Fighter*>(player);
				if (f->m_currentNumAttacks > 0)
				{
					combat((*player));
					f->m_currentNumAttacks--;
					if (f->m_currentNumAttacks == 0)
						break;
					else
						playerDetermineMove();
				}
			}
			else
			{
				combat((*player));
			}
			break;
		case 7:
			exitRoom();
			//Mark the room with your new location
			m_board.markRoom((*player).m_yCoord, (*player).m_xCoord, (*player).getName().at(0), m_board.m_currentRoom);
			playerDetermineMove();
			break;
		case 8:
			resolveChestInteraction();
			removeChestFromBoard();
			break;
		case 9:
			//The player did not take the item from the chest
			removeChestFromBoard();
			playerDetermineMove();
			break;
		case 10:
			resolveInvestigate();
			break;
		case 11:
			checkForTraps();
			break;
		case 12:
			useInventorySlot(0);
			playerDetermineMove();
			break;
		case 13:
			dropInventorySlot(0);
			playerDetermineMove();
			break;
		case 14:
			useInventorySlot(1);
			playerDetermineMove();
			break;
		case 15:
			dropInventorySlot(1);
			playerDetermineMove();
			break;
		case 16:
			useInventorySlot(2);
			playerDetermineMove();
			break;
		case 17:
			dropInventorySlot(2);
			playerDetermineMove();
			break;
		case 18:
			useInventorySlot(3);
			playerDetermineMove();
			break;
		case 19:
			dropInventorySlot(3);
			playerDetermineMove();
			break;
		case 20:
			useInventorySlot(4);
			playerDetermineMove();
			break;
		case 21:
			dropInventorySlot(4);
			playerDetermineMove();
			break;
		case 22:
			if ((*player).m_class == "PRIEST ")
			{
				//This has to be safe because the classType is priest
				Priest* p = dynamic_cast<Priest*>(player);
				(*p).heal();
			}
			break;
		case 24:
			playerDetermineMove();
			break;
		default:
			clearScreen(ScreenBuffer);
			std::cout << "ERROR IN MENU NAVIGATION" << std::endl;
			abort();
		}
	}



	void playGame()
	{
		initializeGame();
		while (!m_gameOver)
			takeTurns();
	}
	


	std::vector<int> randomRoomLocation()
	{
		int Y = generateRandomNumber(0, m_board.getCurrentRoomRows());
		int X = generateRandomNumber(0, m_board.getCurrentRoomColumns());
		return { Y,X };
	}



	//dispay monster moves and monster stats
	void refresh()
	{
		//clear the screen
		clearScreen(ScreenBuffer);
		//display the board
		m_board.displayCurrentRoom();
		//display player stats
		(*player).displayStats();
		//display currentMenu
		m_menu.displayCurrentMenu((*player).m_inventory, (*player).m_class);
		
		//Display all monster stats
		for (Monster m : m_monsters)
		{
			m.displayStats();
		}
	}



	void removeChestFromBoard()
	{
		int playerY = (*player).m_yCoord;
		int playerX = (*player).m_xCoord;
		int treasure1Y = m_board.getTreasureLocations()[0];
		int treasure1X = m_board.getTreasureLocations()[1];

		//If you're not on the first treasure you must be on the second treasure
		if (m_board.m_firstTreasureTaken == false && playerX == treasure1X && playerY == treasure1Y)
			m_board.m_firstTreasureTaken = true;
		else
			m_board.m_secondTreasureTaken = true;
	}



	//This function will parse the users inventory
		//It will add any gold to player gold and remove gold from inventory
		//It will add best armor to player armor and remove lower armor from inventory
		//It will add best sword to player sword and remove lower sword from inventory IF THEY ARE A FIGHTER
		//It will add best scroll to player scroll and remove lower scroll from inventory IF THEY ARE A WIZARD
		//PRIESTS should be able to pick up scrolls and use them out of the inventory
	void resolveChestInteraction()
	{
		//parse for sword (inventory item type 1)
		int swordIndex = indexOfInventoryItemType(1);
		//swords are only for fighters and priests
		if (((*player).m_class.at(0) == 'F' || (*player).m_class.at(0) == 'P') && swordIndex != -1)
		{
			
			//The player inventory versions are "BLCKHRT", "WOODEN", "STEEL", "VORPAL"
			//The chest item versions are "BLACK_HEART", "WOODEN_SWORD", "STEEL_SWORD", "VORPAL_SWORD"
			char chestSword = (*player).m_inventory[swordIndex].at(0);
			char currentSword = (*player).m_weapon.at(0);

			if ((chestSword == 'S' || chestSword == 'V' || chestSword == 'B') && currentSword == 'W')
			{
				//Update the current Sword
				updateWeapon(chestSword);
			}
			else if ((chestSword == 'V' || chestSword == 'B') && (currentSword == 'S' || currentSword == 'W'))
			{
				//Update the current Sword
				updateWeapon(chestSword);
			}
			else if ((chestSword == 'B') && (currentSword == 'V' || currentSword == 'S' || currentSword == 'W'))
			{
				//Update the current Sword
				updateWeapon(chestSword);
			}
			
			//drop the item
			dropInventorySlot(swordIndex);
		}
		else if ((*player).m_class.at(0) == 'W' && swordIndex != -1)
		{
			//drop the item because wizards can use swords
			dropInventorySlot(swordIndex);
		}



		//parse for armor (inventory item type 2)
		int armorIndex = indexOfInventoryItemType(2);
		if (((*player).m_class.at(0) == 'F' || (*player).m_class.at(0) == 'P') && armorIndex != -1)
		{
			//decide if this is the best armor we have
			char chestArmor = (*player).m_inventory[armorIndex].at(0);
			char currentArmor = (*player).m_armor.at(0);
			if ((chestArmor == 'L' || chestArmor == 'S' || chestArmor == 'P') && currentArmor == 'N')
			{
				//Update the armor and armorclass
				updateArmor(chestArmor);
			}
			else if ((chestArmor == 'S' || chestArmor == 'P') && (currentArmor == 'N' || currentArmor == 'L'))
			{
				//Update the armor and armorclass
				updateArmor(chestArmor);
			}
			else if ((chestArmor == 'P') && (currentArmor == 'N' || currentArmor == 'L' || currentArmor == 'S'))
			{
				//Update the armor and armorclass
				updateArmor(chestArmor);
			}
			//Drop the item
			dropInventorySlot(armorIndex);
		}
		else if ((*player).m_class.at(0) == 'W' && armorIndex != -1)
		{
			//drop the item because wizards can wear armor
			dropInventorySlot(armorIndex);
		}
		

		
		//parse for gold (inventory item type 3)
		int goldIndex = indexOfInventoryItemType(3);
		if (goldIndex != -1)
		{
			//Add the gold
			int lengthOfSubstring = 0;
			for (lengthOfSubstring; lengthOfSubstring < (*player).m_inventory[goldIndex].length(); lengthOfSubstring++)
			{
				if ((*player).m_inventory[goldIndex].at(lengthOfSubstring) == '_')
					break;
			}
			std::string subString = (*player).m_inventory[goldIndex].substr(0, lengthOfSubstring);
			int goldToAdd = std::stoi(subString);
			(*player).m_gold += goldToAdd;
			(*player).m_xp += goldToAdd;


			//drop the inventory slot
			dropInventorySlot(goldIndex);
		}



		//parse for scoll (inventory item type 4)
		int scrollIndex = indexOfInventoryItemType(4);
		if (((*player).m_class.at(0) == 'W') && scrollIndex != -1)
		{
			//The player inventory versions are "MISSILE ", "LIGHTNIN", "FIREBALL"
			//The chest item versions are "MAGIC_MISSILE", "LIGHTNING_BOLT", "FIREBALL"
			char chestScroll = (*player).m_inventory[scrollIndex].at(0);
			char currentScroll = (*player).m_weapon.at(0);

			if ((chestScroll == 'L' || chestScroll == 'F') && currentScroll == 'M')
			{
				//Update the current Sword
				updateWeapon(chestScroll);
			}
			else if ((chestScroll == 'F') && (currentScroll == 'L' || currentScroll == 'M'))
			{
				//Update the current Sword
				updateWeapon(chestScroll);
			}
			dropInventorySlot(scrollIndex);
		}
		else if ((*player).m_class.at(0) == 'F' && scrollIndex != -1)
		{
			//drop the scroll because fighters can't use scrolls
			dropInventorySlot(scrollIndex);
		}
	}



	void resolveInvestigate()
	{
		clearScreen(ScreenBuffer);
		std::cout << m_menu.m_investigateContents[generateRandomNumber(0, m_menu.m_investigateContents.size() - 1)];
		Sleep(2500);
	}



	void resolveTraps(Entity& e)
	{
		int ycoord = e.getLocation()[0];
		int xcoord = e.getLocation()[1];
		int damage1 = generateRandomNumber(5, 20) * m_board.getCurrentDungeonLevel();
		int damage2 = generateRandomNumber(5, 20) * m_board.getCurrentDungeonLevel();
		//bossroom
		if (m_board.m_isBossRoom)
		{
			if (ycoord == m_board.getTrapLocations()[0] && xcoord == m_board.getTrapLocations()[1])
			{
				e.hit(damage1);
			}
			else if (ycoord == m_board.getTrapLocations()[2] && xcoord == m_board.getTrapLocations()[3])
			{
				e.hit(damage2);
			}
		}
		//regular room
		else if (!m_board.m_isCorridor && !m_board.m_isBossRoom)
		{
			if (ycoord == m_board.getTrapLocations()[0] && xcoord == m_board.getTrapLocations()[1])
			{
				e.hit(damage1);
			}
		}
		//no traps in corridors
	}



	void takeTurns()
	{
		if (m_turn % 2 == 0)
		{
			for (Monster& monster : m_monsters)
			{
				computerTakeTurn(monster);
				checkForSlainMonsters();
				checkGameOver();
			}
			m_turn++;
		}
		else
		{
			playerTakeTurn();
			checkGameOver();
			(*player).levelUp();
			m_turn++;
		}
	}



	void updateWeapon(char weapon)
	{
		
		//Update the damage
		if ((*player).m_class.at(0) == 'F' || (*player).m_class.at(0) == 'P')
		{
			if (weapon == 'B')
			{
				(*player).m_weapon = "BLCKHRT";
				//10 D10
				(*player).m_doDamageMax = 100;
				(*player).m_doDamageMin = 7;
			}
			else if (weapon == 'S')
			{
				(*player).m_weapon = "STEEL  ";
				//4 D6
				(*player).m_doDamageMax = 24;
				(*player).m_doDamageMin = 4;
			}
			else if (weapon == 'V')
			{
				(*player).m_weapon = "VORPAL ";
				//5 D10
				(*player).m_doDamageMax = 50;
				(*player).m_doDamageMin = 5;
			}
		}
		else if((*player).m_class.at(0) == 'W')
		{
			if (weapon == 'L')
			{
				(*player).m_weapon = "L-BOLT ";
				//6D6
				(*player).m_doDamageMax = 36;
				(*player).m_doDamageMin = 6;
			}
			else if(weapon == 'F')
			{
				(*player).m_weapon = "FIREBAL";
				//10D6
				(*player).m_doDamageMax = 60;
				(*player).m_doDamageMin = 10;
			}
		}
	}



	void updateArmor(char armor)
	{
		if (armor == 'L')
		{
			(*player).m_armor = "LEATHER";
			(*player).m_armorClass = 13;
		}
		else if (armor == 'S')
		{
			(*player).m_armor = "SCALE  ";
			(*player).m_armorClass = 16;
		}
		else if (armor == 'P')
		{
			(*player).m_armor = "PLATE  ";
			(*player).m_armorClass = 20;
		}
	}



	void useInventorySlot(int slot)
	{
		assert(slot >= 0 && slot < (*player).m_inventory.size());

		std::string item = (*player).m_inventory[slot];
		if (item.at(0) == ' ')
		{
			return;
		}
		else if (!item.compare("HAND_OF_VECNA              "))
		{
			//This clears the room of monsters and give the player 500 xp
			for (Monster& m : m_monsters)
			{
				m.m_currentHealth = 0;
			}

			checkForSlainMonsters();
		}
		else if (!item.compare("EYE_OF_VECNA               "))
		{
			//Need to figure out something that this can do
		}
		else if (!item.compare("POTION_OF_HEALTH           "))
		{
			(*player).hit(generateRandomNumber(-40, -5));
		}
		else if (!item.compare("POTION_OF_EXPERIENCE       "))
		{
			(*player).m_xp += 1000;
		}
		else if (!item.compare("POTION_OF_STRENGTH         "))
		{
			(*player).m_doDamageMin += 10;
			(*player).m_doDamageMax += 10;
		}
		else if (!item.compare("MAGIC_MISSILE              "))
		{
			std::vector<int> damage = { 4,8,18 };
			
			for (Monster& m : m_monsters)
			{
				m.hit(damage[generateRandomNumber(0,2)]);
			}
		}
		else if (!item.compare("LIGHTNING_BOLT             "))
		{
			std::vector<int> damage = { 6,24,48 };
			
			for (Monster& m : m_monsters)
			{
				m.hit(damage[generateRandomNumber(0, 2)]);
			}
		}
		else if (!item.compare("FIRE_BALL                  "))
		{
			std::vector<int> damage = { 10,40,80 };
			
			for (Monster& m : m_monsters)
			{
				m.hit(damage[generateRandomNumber(0, 2)]);
			}
		}

		dropInventorySlot(slot);
	}



	bool vecnaIsDead()
	{
		return m_vecnaIsDead;
	}



};