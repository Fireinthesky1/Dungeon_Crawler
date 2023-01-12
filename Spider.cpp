//Spider speed will be twice the regular speed, have 6 hp but good damage and 50 xp
#include "Spider.h"

Spider::Spider()
{
	m_armorClass = 6;
	m_maxHealth = 6;
	m_currentHealth = m_maxHealth;
	m_range = false;
	m_doDamageMin = 3;
	m_doDamageMax = 6;
	m_name = "Spider ";
	m_type = "Spider ";
	m_xpValue = 60;
	m_monsterType = 3;
}
