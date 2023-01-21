#include "Mummy.h"



Mummy::Mummy()
{
	m_armorClass = 12;
	m_maxHealth = 50;
	m_currentHealth = m_maxHealth;
	m_range = false;
	m_doDamageMin = 2;
	m_doDamageMax = 24;
	m_name = "Mummy  ";
	m_type = "Mummy  ";
	m_xpValue = 1000;
	m_monsterType = 8;
}