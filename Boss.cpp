#include "Boss.h"

Boss::Boss(int currentDungeonLevel)
{
	switch (currentDungeonLevel)
	{
	case 1:
		m_name = "Vampire";
		m_type = "Vampire";
		m_armorClass = 2;
		m_maxHealth = 50;
		break;
	case 2:
		m_name = "Lich   ";
		m_type = "Lich   ";
		m_armorClass = 6;
		m_maxHealth = 100;
		break;
	case 3:
		m_name = "Death  ";
		m_type = "Death  ";
		m_armorClass = 10;
		m_maxHealth = 200;
		break;
	case 4:
		m_name = "Vecna  ";
		m_type = "Vecna  ";
		m_armorClass = 15;
		m_maxHealth = 300;
		break;
	}

	m_currentHealth = m_maxHealth;
	m_range = true;
	m_doDamageMin = 2 * currentDungeonLevel;
	m_doDamageMax = 6 * currentDungeonLevel;
	m_xpValue = 1000 * currentDungeonLevel;
	m_monsterType = 13;
}