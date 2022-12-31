#include "Entity.h"


Entity::Entity()
	: m_name("PLAYER"), m_yCoord(0), m_xCoord(0), m_direction(1), m_doDamageMin(1), m_doDamageMax(5), m_maxHealth(10), m_currentHealth(10), m_armorClass(10), m_symbol('E'), m_range(false)
{
}



char Entity::getSymbol()
{
	return m_name.at(0);
}



int Entity::setVars(int min, int max, int var)
{
	if (var < min)
		var = min;
	else if (var > max)
		var = max;

	return var;
}



std::vector<int> Entity::getLocation()
{
	std::vector<int> location{ m_yCoord, m_xCoord };
	return location;
}



std::vector<int> Entity::newIncrement(Board board)
{
	std::vector<int> incrementArray;
	switch (m_direction)
	{
	case 1:
		incrementArray = incrementNorth(board);
		break;
	case 2:
		incrementArray = incrementEast(board);
		break;
	case 3:
		incrementArray = incrementSouth(board);
		break;
	case 4:
		incrementArray = incrementWest(board);
		break;
	}

	return incrementArray;
}



std::vector<int> Entity::incrementNorth(Board board)
{
	//subtract from y to go north
	int y = setVars(0, board.getCurrentRoomRows() - 1, m_yCoord - 1);
	std::vector<int> newIncrement{ y, m_xCoord };
	return newIncrement;
}



std::vector<int> Entity::incrementEast(Board board)
{
	//Add to x to go east
	int x = setVars(0, board.getCurrentRoomColumns() - 1, m_xCoord + 1);
	std::vector<int> newIncrement{ m_yCoord, x };
	return newIncrement;
}



std::vector<int> Entity::incrementSouth(Board board)
{
	//Add to y to go south
	int y = setVars(0, board.getCurrentRoomRows() - 1, m_yCoord + 1);
	std::vector<int> newIncrement{ y, m_xCoord };
	return newIncrement;
}



std::vector<int> Entity::incrementWest(Board board)
{
	//Subtract from x to go west
	int x = setVars(0, board.getCurrentRoomColumns() - 1, m_xCoord - 1);
	std::vector<int> newIncrement{ m_yCoord, x };
	return newIncrement;
}



bool Entity::isAlive()
{
	return m_currentHealth > 0;
}



void Entity::changeDirection(int direction)
{
	m_direction = setVars(1, 4, direction);
}



void Entity::hit(int damage)
{
	m_currentHealth = setVars(0, m_maxHealth, m_currentHealth - damage);
}



std::string Entity::getName()
{
	return m_name;
}



void Entity::move(Board board)
{
	std::vector<int> newPosition = newIncrement(board);
	m_yCoord = newPosition[0];
	m_xCoord = newPosition[1];
}



std::vector<int> Entity::attack(Board board, int armorClass, bool range)
{
	std::vector<int> attackSolution{ 0,0,0 };
	if (range)
	{
		//When it's a ranged attack the attack solution will
		//Consist of 3 tiers of damage to be taken by ALL enemies
		//It is randomly determined who takes max damage, half damage
		//and min damage
		if (successfulAction(armorClass))
		{
			attackSolution[0] = m_doDamageMax;
			attackSolution[1] = m_doDamageMax / 2;
			attackSolution[2] = m_doDamageMin;
		}
		return attackSolution;
	}
	attackSolution[0] = newIncrement(board)[0];
	attackSolution[1] = newIncrement(board)[1];
	if (successfulAction(armorClass))
	{
		//Random amount of damage
		attackSolution[2] = rand() % (m_doDamageMax - m_doDamageMin + 1);
	}
	else
	{
		attackSolution[2] = 0;
	}

	return attackSolution;
}