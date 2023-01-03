/*Game View Layer
	-All updates to visual state will be done here*/

/*STATUS
	-We have a healthy looking board class
TODAY GOALS----------------------------------------------------------------------------------------------

	-Structure of room locations array
	{
		y1,x1,y2,x2..., Exits
		y1,x1,y2,x2..., Traps
		y1,x1,y2,x2..., Treasure
		y1,x1}			Stairs
	}
*/
#pragma once
#include <string>
#include <iostream>
#include <vector>
#include <assert.h>


//Table V dungeon master guide 1e
enum class Area
{
	VERTICALPASSAGE		= 1,
	SQUARE30X30			= 2,
	SQUARE50X50			= 3,
	SQUARE70X70			= 4,
	SQUARE90X90			= 5,
	RECTANGULAR30X50	= 6,
	RECTANGULAR50X70	= 7,
	RECTANGULAR70X90	= 8,
	HORIZONTALPASSAGE	= 9,
	BOSSROOM			= 10,
	STARTINGROOM		= 11
};



class Board
{
public:
	bool m_isCorridor;
	bool m_isBossRoom;
	bool m_trapsChecked;
	bool m_firstTreasureTaken, m_secondTreasureTaken;
	std::vector<std::vector<char>> m_currentRoom;

private:
	std::vector<int> m_roomLocations;
	std::vector<bool> bossRoomGenerated{ false, false, false, false };
	int m_chanceToGenerateBossRoom;
	int m_currentDungeonLevel;
	


public:
	//constructors
	Board() : m_currentDungeonLevel(1), bossRoomGenerated({ false, false, false, false }), m_chanceToGenerateBossRoom(0), m_trapsChecked(false), m_firstTreasureTaken(false), m_secondTreasureTaken(false)
	{
		//Create the starting room
		std::vector<std::vector<char>> startingRoom = initializeStartingRoom();

		//set starting room to current room
		m_currentRoom = startingRoom;

		//Mark the rooom
		refreshBoard();
	}



	void displayCurrentRoom()
	{
		//Building Blocks of Dungeon
		const std::string horizontal_bar = "||";
		const std::string top_line_begin = "||===";
		const std::string top_line_middle = "||===";
		const std::string top_line_end = "||===||";
		const std::string middle_line = "||===";
		const std::string middle_line_end = "||===||";
		const std::string bottom_line_begin = "||===";
		const std::string bottom_line_middle = "||===";
		const std::string bottom_line_end = "||===||";



//vertical Passages----------------------------------------------------
		if (m_currentRoom[0].size() == 1)
		{
			for (int i = 0; i < m_currentRoom.size(); i++)
			{

				std::cout << top_line_end << std::endl;
				std::cout << horizontal_bar << " " << m_currentRoom[i][0] <<  " " << horizontal_bar << std::endl;
			}
			std::cout << bottom_line_end << std::endl;
			return;
		}


//top line-------------------------------------------------------------
		std::cout << top_line_begin;
		for (int i = 0; i < m_currentRoom[0].size() - 2; i++)
		{
			std::cout << (top_line_middle);
		}
		std::cout << top_line_end << std::endl;



//horizontal bars-----------------------------------------------------
		for (int i = 0; i < m_currentRoom.size(); i++)
		{
			for (int j = 0; j < m_currentRoom[0].size(); j++)
			{
				std::cout << (horizontal_bar + " " + m_currentRoom[i][j] + " ");
			}
			std::cout << horizontal_bar;
			std::cout << '\n';



//bottom line----------------------------------------------------------
			if (i == m_currentRoom.size() - 1)
			{
				std::cout << bottom_line_begin;
				for (int b = 0; b < m_currentRoom[0].size() - 2; b++)
				{
					std::cout << bottom_line_middle;
				}
				std::cout << bottom_line_end << std::endl;



//middle lines---------------------------------------------------------
			}
			else
			{
				std::cout << middle_line;
				for (int c = 0; c < m_currentRoom[0].size() - 2; c++)
				{
					std::cout << middle_line;
				}
				std::cout << middle_line_end << std::endl;
			}
		}
	}



	void markRoom(int y, int x, char symbol, std::vector<std::vector<char>> &room)
	{
		assert(y >= 0 && y < room.size());
		assert(x >= 0 && x < room[0].size());
		room[y][x] = symbol;
	}



	std::vector<std::vector<char>> initializeNewRoom(int exitDirection)
	{
		destroyRoom();
		//Find out if this is a boss room
		int num = rand() % 101;
		if (num <= m_chanceToGenerateBossRoom)
		{
			m_chanceToGenerateBossRoom = 0;
			m_currentRoom = generateNewRoom(10, exitDirection);
			refreshBoard();
		}
		else
		{
			m_chanceToGenerateBossRoom += 10;
			m_currentRoom = generateRoomByExitLocation(exitDirection);
			refreshBoard();
		}

		return m_currentRoom;
	}



//Setters and Getters--------------------------------------------------
	void setChanceToGenerateBossRoom(int value)
	{
		if (value < 0)
			m_chanceToGenerateBossRoom = 0;
		else if (value > 100)
			m_chanceToGenerateBossRoom = 100;
		else
			m_chanceToGenerateBossRoom = value;
	}



	int getCurrentRoomRows()
	{
		return (int) m_currentRoom.size();
	}



	int getCurrentRoomColumns()
	{
		return (int) m_currentRoom[0].size();
	}



	int getCurrentDungeonLevel()
	{
		return m_currentDungeonLevel;
	}



	void setCurrentDungeoneLevel(int currentDungeonLevel)
	{
		//Make sure we can only go to the fourth dungeon level
		if (currentDungeonLevel > 4)
			m_currentDungeonLevel = 4;
		else
			m_currentDungeonLevel = currentDungeonLevel;
	}



	bool getIsCorridor()
	{
		if (m_currentRoom.size() == 1 || m_currentRoom[0].size() == 1)
			return true;
		else
			return false;
	}



	std::vector<int> getExitLocations()
	{
		return { m_roomLocations[0], m_roomLocations[1], m_roomLocations[2], m_roomLocations[3] };
	}



	std::vector<int> getTrapLocations()
	{
		return { m_roomLocations[4], m_roomLocations[5], m_roomLocations[6], m_roomLocations[7] };
	}



	std::vector<int> getTreasureLocations()
	{
		return { m_roomLocations[8], m_roomLocations[9], m_roomLocations[10], m_roomLocations[11] };
	}



	std::vector<int> getStairLocations()
	{
		return { 10, 10 };
	}



	void refreshBoard()
	{
		if (m_isCorridor)
		{
			if (!m_firstTreasureTaken)
				markRoom(m_roomLocations[8], m_roomLocations[9], '$', m_currentRoom);

			markRoom(m_roomLocations[0], m_roomLocations[1], '*', m_currentRoom);
			markRoom(m_roomLocations[2], m_roomLocations[3], '*', m_currentRoom);
		}
		else if (m_isBossRoom)
		{
			if (!m_firstTreasureTaken)
				markRoom(m_roomLocations[8], m_roomLocations[9], '$', m_currentRoom);

			if (!m_secondTreasureTaken)
				markRoom(m_roomLocations[10], m_roomLocations[11], '$', m_currentRoom);

			if (m_trapsChecked)
			{
				markRoom(m_roomLocations[4], m_roomLocations[5], 'T', m_currentRoom);
				markRoom(m_roomLocations[6], m_roomLocations[7], 'T', m_currentRoom);
			}

			markRoom(m_roomLocations[0], m_roomLocations[1], '*', m_currentRoom);
			markRoom(m_roomLocations[2], m_roomLocations[3], '*', m_currentRoom);
			markRoom(m_roomLocations[12], m_roomLocations[13], '/', m_currentRoom);
		}
		else
		{
			if (!m_firstTreasureTaken)
				markRoom(m_roomLocations[8], m_roomLocations[9], '$', m_currentRoom);

			if (!m_secondTreasureTaken)
				markRoom(m_roomLocations[10], m_roomLocations[11], '$', m_currentRoom);

			if (m_trapsChecked)
				markRoom(m_roomLocations[4], m_roomLocations[5], 'T', m_currentRoom);

			markRoom(m_roomLocations[0], m_roomLocations[1], '*', m_currentRoom);
			markRoom(m_roomLocations[2], m_roomLocations[3], '*', m_currentRoom);
		}
	}


private:
	void destroyRoom()
	{
		m_roomLocations.clear();
		m_trapsChecked = false;
		m_firstTreasureTaken = false;
		m_secondTreasureTaken = false;
	}



	std::vector<std::vector<char>> initializeStartingRoom()
	{
		return generateNewRoom(11, rand() % 4 + 1);
	}



	void populateRoom(std::vector<std::vector<char>> &room, int &height, int &width, int entranceLocation, bool isBossRoom)
	{
		int exitLocation, entranceY, entranceX, exitY, exitX, trapY1, trapX1, trapY2, trapX2, treasureY1, treasureX1, treasureY2, treasureX2, stairY, stairX;
		bool corridor = false;
		//Corridors
		if (height <= 1 && entranceLocation == 2)
		{
			corridor = true;
			exitLocation = 4;
			entranceY = 0;
			entranceX = width - 1;
			exitY = 0;
			exitX = 0;
		}
		else if (height <= 1 && entranceLocation == 4)
		{
			corridor = true;
			exitLocation = 2;
			entranceY = 0;
			entranceX = 0;
			exitY = 0;
			exitX = width - 1;
		}
		else if (width <= 1 && entranceLocation == 1)
		{
			corridor = true;
			exitLocation = 3;
			entranceY = 0;
			entranceX = 0;
			exitY = height - 1;
			exitX = 0;
		}
		else if (width <= 1 && entranceLocation == 3)
		{
			corridor = true;
			exitLocation = 1;
			entranceY = height - 1;
			entranceX = 0;
			exitY = 0;
			exitX = 0;
		}

		if (!corridor)
		{
			//Find the exit location
			if (entranceLocation == 1)
			{
				exitLocation = rand() % 4 + 2;
				if (exitLocation > 4)
					exitLocation = 4;
			}
			else if (entranceLocation == 2)
			{
				exitLocation = rand() % 4 + 1;
				if (exitLocation == 2)
					exitLocation = 3;
			}
			else if (entranceLocation == 3)
			{
				exitLocation = rand() % 4 + 1;
				if (exitLocation == 3)
					exitLocation = 1;
			}
			else
			{
				exitLocation = rand() % 4 + 1;
				if (exitLocation == 4)
					exitLocation = 2;
			}

			//determine Coordinates of Entrance
			switch (entranceLocation)
			{
			case 1:
				entranceY = 0;
				entranceX = width / 2;
				break;
			case 2:
				entranceY = height / 2;
				entranceX = width - 1;
				break;
			case 3:
				entranceY = height - 1;
				entranceX = width / 2;
				break;
			case 4:
				entranceY = height / 2;
				entranceX = 0;
				break;
			}

			//Determine Coordinates of Exit
			switch (exitLocation)
			{
			case 1:
				exitY = 0;
				exitX = width / 2;
				break;
			case 2:
				exitY = height / 2;
				exitX = width - 1;
				break;
			case 3:
				exitY = height - 1;
				exitX = width / 2;
				break;
			case 4:
				exitY = height / 2;
				exitX = 0;
				break;
			}
		}

		//Randomly Determine Location of trap
		
		trapY1 = rand() % height;
		trapX1 = rand() % width;

		trapY2 = rand() % height;
		trapX2 = rand() % width;

		//Randomly Determine Location of Treasure
		treasureY1 = rand() % height;
		treasureX1 = rand() % width;
		
		treasureY2 = rand() % height;
		treasureX2 = rand() % width;

		//If is bossRoom
		stairY = height - 1;
		stairX = width - 1;

		//Put All Room Locations into m_roomLocations      0			1		2		3	   4	   5	   6      7         8			9			10			11
		m_roomLocations.insert(m_roomLocations.end(), { entranceY, entranceX, exitY, exitX, trapY1, trapX1, trapY2, trapX2, treasureY1, treasureX1, treasureY2, treasureX2});
		if (isBossRoom)									//	   12      13
			m_roomLocations.insert(m_roomLocations.end(), { stairY, stairX });
	}



	std::vector<std::vector<char>> generateRoomByExitLocation(int exitLocation)
	{
		if (exitLocation == 1)
		{
			int roomType = rand() % 8 + 1;
			if (roomType > 8)
				roomType = 8;
			return generateNewRoom(roomType, 3);
		}
		else if (exitLocation == 2)
		{
			int roomType = rand() % 8 + 2;
			if (roomType > 9)
				roomType = 9;
			return generateNewRoom(roomType, 4);
		}
		else if (exitLocation == 3)
		{
			int roomType = rand() % 8 + 1;
			if (roomType > 8)
				roomType = 8;
			return generateNewRoom(roomType, 1);
		}
		else if (exitLocation == 4)
		{
			int roomType = rand() % 8 + 2;
			if (roomType > 9)
				roomType = 9;
			return generateNewRoom(roomType, 2);
		}
		else
		{
			std::cout << "Error in method generateRoomByExitLocation" << std::endl;
			abort();
		}
	}



	std::vector<std::vector<char>> generateNewRoom(int roomType, int entranceLocation)
	{
		//Set booleans
		if (roomType == 1 || roomType == 9)
		{
			m_isCorridor = true;
			m_isBossRoom = false;
		}
		else if (roomType == 10)
		{
			m_isBossRoom = true;
			m_isCorridor = false;
		}
		else
		{
			m_isCorridor = false;
			m_isBossRoom = false;
		}

		int width, height;
		switch (roomType)
		{
		case 1:
			height = 9;
			width = 1;
			return createRoomVector(height, width, entranceLocation);
			break;
		case 2:
			height = 3;
			width = 3;
			return createRoomVector(height, width, entranceLocation);
			break;					
		case 3:		
			height = 5;
			width = 5;
			return createRoomVector(height, width, entranceLocation);
			break;					
		case 4:				
			height = 7;
			width = 7;
			return createRoomVector(height, width, entranceLocation);
			break;					
		case 5:					
			height = 9;
			width = 9;
			return createRoomVector(height, width, entranceLocation);
			break;					
		case 6:					
			height = 3;
			width = 5;
			return createRoomVector(height, width, entranceLocation);
			break;					
		case 7:					
			height = 5;
			width = 7;
			return createRoomVector(height, width, entranceLocation);
			break;					
		case 8:					
			height = 7;
			width = 9;
			return createRoomVector(height, width, entranceLocation);
			break;					
		case 9:		
			height = 1;
			width = 9;
			return createRoomVector(height, width, entranceLocation);
			break;
		case 10:
			height = 11;
			width = 11;
			if (entranceLocation == 1)
				entranceLocation = 3;
			else if (entranceLocation == 2)
				entranceLocation = 4;
			else if (entranceLocation == 3)
				entranceLocation = 1;
			else
				entranceLocation = 2;
			return createRoomVector(height, width, entranceLocation);
			break;					
		case 11:				
			height = 5;
			width = 5;
			return createRoomVector(height, width, entranceLocation);
			break;
		default:
			std::cout << "Error in method 'generateNewRoom'." << std::endl;
			abort();
			break;
		}
	}



	std::vector<std::vector<char>> createRoomVector(int &height,int &width, int entranceLocation)
	{
		//Create the vector and populate the room
		std::vector<std::vector<char>> room (height, std::vector<char>(width, ' '));
		populateRoom(room, height, width, entranceLocation, m_isBossRoom);
		return room;
	}
};
