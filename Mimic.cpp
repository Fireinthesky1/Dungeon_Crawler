#include "Mimic.h"

Mimic::Mimic()
{
	m_armorClass = 10;
	m_baseDifficulty = 1;
	m_maxHealth = 4;
	m_currentHealth = m_maxHealth;
	m_range = false;
	m_doDamageMin = 1;
	m_doDamageMax = 4;
	//This is so they show up as a dollar sign
	m_name = "$      ";
	m_type = "Mimic  ";
	m_xpValue = 50;
	m_monsterType = 11;
}