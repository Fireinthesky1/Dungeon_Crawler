#include "Player.h"



//constructors
Player::Player()
	: m_weapon("WOODEN "), m_armor("NONE   "), m_class("PLAYER "), m_level(1), m_xp(0), m_gold(0),
	m_inventory({ "                           ", "                           ", "                           ", "                           ", "                           " })
{
	m_name = "Player ";
}


Player::Player(std::string name, std::string weapon, std::string armor, int maxHealth, int yCoord, int xCoord, int baseDifficulty, int doDamageMax, int doDamageMin, int direction, bool range, int level, int xp, int gold, int armorClass)
	: m_weapon("WOODEN "), m_armor("NONE "), m_class("PLAYER "),
	m_level(1), m_xp(0), m_gold(0), m_inventory({ "                           ", "                           ", "                           ", "                           ", "                           " })
{

}



std::vector<int> Player::attack(Board board, int armorClass, bool range)
{
	std::vector<int> attackSolution{ 0,0,0 };
	if (range)
	{
		//When it's a ranged attack the attack solution will
		//Consist of 3 tiers of damage to be taken by ALL enemies
		//It is randomly determined who takes max damage, half damage
		//and min damage
		if (successfulAction(this->m_level, armorClass))
		{
			attackSolution[0] = m_doDamageMax;
			attackSolution[1] = m_doDamageMax / 2;
			attackSolution[2] = m_doDamageMin;
		}
		return attackSolution;
	}
	attackSolution[0] = newIncrement(board)[0];
	attackSolution[1] = newIncrement(board)[1];
	if (successfulAction(this->m_level, armorClass))
	{
		//Random amount of damage
		attackSolution [2] = rand() % (m_doDamageMax - m_doDamageMin + 1);
	}
	else
	{
		//Missed attack
		attackSolution[2] = 0;
	}

	return attackSolution;
}



std::string Player::getFacing()
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



std::string Player::getName()
{
	//The MAINMENU only allows for a name of exactly 7 characters
	std::string truncatedName = m_name.substr(0,9);
	while (truncatedName.length() < 9)
	{
		truncatedName += " ";
	}
	return truncatedName;
}



std::string Player::getHealth()
{
	std::string health = std::to_string(m_currentHealth);
	if (m_currentHealth < 10)
	{
		health += " ";
		return health.insert(0, "0");
	}
	else
	{
		return health + " ";
	}
}



std::string Player::getLevel()
{
	switch (m_level)
	{
	case 1:
		return "01 ";
		break;
	case 2:
		return "02 ";
		break;	   
	case 3:		   
		return "03 ";
		break;	   
	case 4:		   
		return "04 ";
		break;	   
	case 5:		   
		return "05 ";
		break;	   
	case 6:		   
		return "06 ";
		break;	   
	case 7:		   
		return "07 ";
		break;	   
	case 8:		   
		return "08 ";
		break;	   
	case 9:		   
		return "09 ";
		break;	   
	case 10:	   
		return "10 ";
		break;
	default:
		return "ER ";
	}
}



std::string Player::getXP()
{
	m_xp = setVars(0, 9999, m_xp);
	std::string xp = std::to_string(m_xp);
	while (xp.length() < 4)
	{
		xp += " ";
	}
	return xp;
}



std::string Player::getGold()
{
	m_gold = setVars(0, 999999, m_gold);
	std::string gold = std::to_string(m_gold);
	while (gold.length() < 6)
	{
		gold += " ";
	}
	return gold;
}



std::string Player::getArmorClass()
{
	return std::to_string(m_armorClass) + " ";
}



std::string Player::getClass()
{
	return m_class;
}



bool Player::hasInventorySpace()
{
	for (int i = 0; i < m_inventory.size(); i++)
	{
		if (m_inventory[i].at(0) == ' ')
			return true;
	}

	return false;
}



void Player::displayStats()
{
	std::string line1 = "|1:NAME:" + getName() + "CLASS:" + getClass() + "|" + '\n';
	std::string line2 = "|2:LEVEL:" + getLevel() + "XP:" + getXP() + "GOLD:" + getGold() +"|" + '\n';
	std::string line3 = "|3:HP:" + getHealth() + "AC:" + getArmorClass() + "DIRECTION:" + getFacing() + "|" + '\n';
	std::string line4 = "|4:WEAPON:" + m_weapon + "ARMOR:" + m_armor + "|";
	std::string menuToDisplay = line1 + line2 + line3 + line4;
	std::cout << menuToDisplay << std::endl;
}



void Player::levelUp()
{
	if (m_xp > 10000 && m_level == 9)
	{
		//level 10
		m_level++;
		m_maxHealth += 10;
		m_currentHealth = m_maxHealth;
	}
	else if (m_xp > 9000 && m_level == 8)
	{
		//level 9
		m_level++;
		m_maxHealth += 10;
		m_currentHealth = m_maxHealth;
	}
	else if (m_xp > 7500 && m_level == 7)
	{
		//level 8
		m_level++;
		m_maxHealth += 10;
		m_currentHealth = m_maxHealth;
	}
	else if (m_xp > 5000 && m_level == 6)
	{
		//level 7
		m_level++;
		m_maxHealth += 10;
		m_currentHealth = m_maxHealth;
	}
	else if (m_xp > 2500 && m_level == 5)
	{
		//level 6
		m_level++;
		m_maxHealth += 10;
		m_currentHealth = m_maxHealth;
	}
	else if (m_xp > 2000 && m_level == 4)
	{
		//level 5
		m_level++;
		m_maxHealth += 10;
		m_currentHealth = m_maxHealth;
	}
	else if (m_xp > 1500 && m_level == 3)
	{
		//level 4
		m_level++;
		m_maxHealth += 10;
		m_currentHealth = m_maxHealth;
	}
	else if (m_xp > 1000 && m_level == 2)
	{
		//level 3
		m_level++;
		m_maxHealth += 10;
		m_currentHealth = m_maxHealth;
	}
	else if (m_xp > 50 && m_level == 1)
	{
		//level 2
		m_level++;
		m_maxHealth += 10;
		m_currentHealth = m_maxHealth;
	}
}