#include "Priest.h"



Priest::Priest()
{
	m_class = "PRIEST ";
	m_healSpellsRemaining = 3;
}



void Priest::displayStats()
{
	std::string line1 = "|1:NAME:" + getName() + "CLASS:" + getClass() + "|" + '\n';
	std::string line2 = "|2:LEVEL:" + getLevel() + "XP:" + getXP() + "GOLD:" + getGold() + "|" + '\n';
	std::string line3 = "|3:HP:" + getHealth() + "AC:" + getArmorClass() + "DIRECTION:" + getFacing() + "|" + '\n';
	std::string line4 = "|4:WEAPON:" + m_weapon + "ARMOR:" + m_armor + "|" + '\n';
	std::string line5 = "|5:HEALING SPELLS: " + getHealSpellsRemaining() + "         |" + '\n';
	std::string menuToDisplay = line1 + line2 + line3 + line4 + line5;
	std::cout << menuToDisplay;
}



std::string Priest::getHealSpellsRemaining()
{
	std::string healSpellsRemaining = std::to_string(m_healSpellsRemaining);
	if (healSpellsRemaining.length() < 2)
	{
		healSpellsRemaining.insert(0, "0");
	}
	return healSpellsRemaining;
}



void Priest::heal()
{
	if (m_healSpellsRemaining <= 0)
	{
		m_healSpellsRemaining = 0;
		return;
	}

	int healingValue = -1 *(generateRandomNumber(1, 8) * m_level);
	this->hit(healingValue);
	m_healSpellsRemaining--;
}



void Priest::levelUp()
{
	if (m_xp >= 9999 && m_level == 9)
	{
		//level 10
		m_level++;
		m_healSpellsRemaining = 10;
		m_maxHealth += 8;
		m_currentHealth = m_maxHealth;
	}
	else if (m_xp > 9000 && m_level == 8)
	{
		//level 9
		m_level++;
		m_healSpellsRemaining = 9;
		m_maxHealth += 8;
		m_currentHealth = m_maxHealth;
	}
	else if (m_xp > 7500 && m_level == 7)
	{
		//level 8
		m_level++;
		m_healSpellsRemaining = 8;
		m_maxHealth += 8;
		m_currentHealth = m_maxHealth;
	}
	else if (m_xp > 5000 && m_level == 6)
	{
		//level 7
		m_level++;
		m_healSpellsRemaining = 7;
		m_maxHealth += 8;
		m_currentHealth = m_maxHealth;
	}
	else if (m_xp > 2500 && m_level == 5)
	{
		//level 6
		m_level++;
		m_healSpellsRemaining = 6;
		m_maxHealth += 8;
		m_currentHealth = m_maxHealth;
	}
	else if (m_xp > 2000 && m_level == 4)
	{
		//level 5
		m_level++;
		m_healSpellsRemaining = 5;
		m_maxHealth += 8;
		m_currentHealth = m_maxHealth;
	}
	else if (m_xp > 1500 && m_level == 3)
	{
		//level 4
		m_level++;
		m_healSpellsRemaining = 4;
		m_maxHealth += 8;
		m_currentHealth = m_maxHealth;
	}
	else if (m_xp > 1000 && m_level == 2)
	{
		//level 3
		m_level++;
		m_healSpellsRemaining = 3;
		m_maxHealth += 8;
		m_currentHealth = m_maxHealth;
	}
	else if (m_xp > 500 && m_level == 1)
	{
		//level 2
		m_level++;
		m_healSpellsRemaining = 2;
		m_maxHealth += 8;
		m_currentHealth = m_maxHealth;
	}
}