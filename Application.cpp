#pragma once
#include <iostream>

#include "Game.h"

//TO DO BY PRIORITY
/*
*	
*	-Get current build stable then work on a.i.
* 
*	-Need a way for monster actions to be displayed to user
* 
*	-Get turns happening
*	-Implement AI
*		-just added monsterType which will help navigate behaviors in the ai function
*	-Implement Collision detection for entities
* 
*	-Implement dialogue
*	-Need to implement attacks
*	-Need to implement NPC's
*	-Need to implement dialogue system
* 
*	-Organize all class methods
* 
*	-Work on the investigate menu
*/

//IDEAS
/*
*	-maybe have some way to get bonuses to hit from leveling up and or better weapons
*	-Try to introduce rarity to the items you fin in chests (hand and eye and black heart and vorpal being
*	 extremely rare)
*	
*/

//BUGS
/*
*	-Monsters get down to zero hitpoints and don't go away
*	
*	-infinite chest loop on fighter room 1.
* 
*	-Upon second play monsters didn't initially show up in room
* 
*	-Vector subScript out of range when using wizard attack after play again and switching TO wizard
*	-When a chest is on a trap and you grab the chest the trap is now hidden
*/



int main()
{
	srand(time(0));
	Game g;	
}