#pragma once
#include <iostream>

#include "Game.h"

//TO DO BY PRIORITY
/*
*	-Get current build stable then work on a.i. 
* 
*	-Get turns happening
*	-Implement AI
*		-just added monsterType which will help navigate behaviors in the ai function
*	-Implement Collision detection for entities
* 
*	-Implement dialogue
*	-Need to implement NPC's
*	-Need to implement dialogue system
* 
*	-Organize all class methods
* 
*	-Work on the investigate menu
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
*	-Monsters get down to zero hitpoints and don't go away (this is due to the playerDetermineMove function not exiting because
*	 the player can still take more actions. Ex: Fighter with multiple attacks. The board won't refresh until after playerDetermineMove
*	 exits)
* 
* 
*	-When a chest is on a trap and you grab the chest the trap is now hidden
*/



int main()
{
	srand(time(0));
	Game g;	
}