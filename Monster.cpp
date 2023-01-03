#include "Monster.h"



Monster::Monster()
	: m_type("MONSTER"), m_xpValue(100), m_monsterType(0)
{
	m_name = "MONSTER";
}



Monster::Monster(std::string type, int maxHealth, int yCoord, int xCoord, int doDamageMax, int doDamageMin, int direction, bool range, int armorClass)
{
	m_type = type;
	m_maxHealth = maxHealth;
	m_yCoord = yCoord;
	m_xCoord = xCoord;
	m_doDamageMax = doDamageMax;
	m_doDamageMin = doDamageMin;
	m_direction = direction;
	m_range = range;
	m_armorClass = armorClass;
}



std::vector<int> Monster::attack(Board board, int armorClass, bool range)
{
	std::vector<int> attackSolution{ 0,0,0 };
	if (range)
	{
		//When it's ranged attack the player will either recieve
		//full damage, half damage, or min damage
		if (successfulAction(5,armorClass))
		{
			attackSolution[0] = m_doDamageMax;
			attackSolution[1] = m_doDamageMax / 2;
			attackSolution[2] = m_doDamageMin;
			
		}
		return attackSolution;
	}

	attackSolution[0] = newIncrement(board)[0]; //yCoord of attack square
	attackSolution[1] = newIncrement(board)[1];	//xCoord of attack square

	if (successfulAction(5,armorClass))
	{
		//random amount of damage
		attackSolution[2] = rand() % (m_doDamageMax = m_doDamageMin + 1);
	}
	else
	{
		//Missed attack
		attackSolution[2] = 0;
	}

	return attackSolution;
}



std::string Monster::getFacing()
{
	switch (m_direction)
	{
	case 1:
		return "North";
		break;
	case 2:
		return "East ";
		break;
	case 3:
		return "South";
		break;
	case 4:
		return "West ";
		break;
	default:
		return "Error";
	}
}



std::string Monster::getHealth()
{
	std::string health = std::to_string(m_currentHealth);
	if (m_currentHealth < 10)
	{
		health += " ";
		return health.insert(0, "0");
	}
	else if (m_currentHealth < 100)
	{
		return health + " ";
	}
	else
	{
		return health;
	}
}



std::string Monster::getType()
{
	return m_type;
}



std::string Monster::getArmorClass()
{
	std::string armorClass = std::to_string(m_armorClass);
	if (m_armorClass < 10)
	{
		armorClass += " ";
		return armorClass.insert(0, "0");
	}
	else
	{
		return armorClass + " ";
	}
}



void Monster::displayStats()
{
	std::string line1 = "|1:TYPE:" + getType() + "               |" + '\n';
	std::string line2 = "|2:HP:" + getHealth() + "AC:" + getArmorClass() + "DIRECTION:" + getFacing() + "|" + '\n';
	std::string menuToDisplay = line1 + line2;
	std::cout << menuToDisplay << std::endl;
}
