//Purple worms are rare miniBosses able to teleport around a room worth 5000 xp and can do up to 60 damage in one shot
#include "PurpleWorm.h"

//Need to work out how to teleport these guys around the room
PurpleWorm::PurpleWorm()
{
	m_armorClass = 20;
	m_baseDifficulty = 10;
	m_maxHealth = 500;
	m_currentHealth = m_maxHealth;
	m_range = true;
	m_doDamageMin = 15;
	m_doDamageMax = 50;
	m_name = "Worm   ";
	m_type = "Worm   ";
	m_xpValue = 5000;
	m_monsterType = 12;
}