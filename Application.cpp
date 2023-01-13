#pragma once
#include <iostream>

#include "Game.h"

//TO DO BY PRIORITY
/*
*	-Implement Collision detection for entities
* 
*	-Organize all class methods
* 
*/

//IDEAS
/*
*	-Need a way for monster actions to be displayed to user (line 331)
*	-Try to introduce rarity to the items you find in chests (hand and eye and black heart and vorpal being
*	 extremely rare)
*	-Need to remove artifacts from list of chest items after they've been found
*/

//BUGS
/*
*	-Enemies can now attack and it is brutal (fix damage)
* 
*	-Need to thoroughly test the generate random number again (utility)
* 
*	-Used hand of vecna. Reduced monster to zero hp. Monster didn't come off battlefield till next action was taken (1/2/23)
* 
*	-When a chest is on a trap and you grab the chest the trap is now hidden
*/



int main()
{
	srand(time(0));
	Game g;	
}