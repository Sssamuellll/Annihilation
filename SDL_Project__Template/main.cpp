#include <SDL.h>
#include "Game.h"
#include <iostream>

//The main function using SDL's required parameters.
int main(int argc, char* argv[])
{
	Game game; //Instantiating an object of the Game class called game.
	game.Run(); //Calling the run function from the game object.

	return 0;// returns 0.
}