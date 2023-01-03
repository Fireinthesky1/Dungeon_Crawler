#include "Mimic.h"

Mimic::Mimic()
{
	m_armorClass = 6;
	m_maxHealth = 4;
	m_currentHealth = m_maxHealth;
	m_range = false;
	m_doDamageMin = 1;
	m_doDamageMax = 4;
	//This is so they show up as a dollar sign
	m_name = "$      ";
	m_type = "Mimic  ";
	m_xpValue = 40;
	m_monsterType = 11;
}