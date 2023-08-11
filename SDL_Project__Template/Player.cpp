#include "Player.h"
#include "Bullet.h"
#include <iostream>
#include <SDL.h>

Player::Player() { Player::SetSpeed(10); }//Defining default constructor.
Player::Player(int _x, int _y) { Player::SetSpeed(10); Player::SetY(_y); }//Defining constructor initalising class members.
Player::~Player(){}//Defining deconstructor.

//Defining class getters and setters.
SDL_Surface* Player::GetImage()
{
	m_image = SDL_LoadBMP("ship.BMP");//Assigning the file bitmap image to class member m_image.
	if (m_image == NULL)//if member is still equal to NULL.
	{
		std::cout << "SDL Could not load image! SDL Error: " << SDL_GetError() << std::endl;//if this is NULL then an SDL error message will output.
	}
	return m_image;//returns the value of member m_image.
}

//Defining class methods.
void Player::Move(SDL_Event& _event, int _x)//passes by reference a SDL event and passes by value an integer value.
{
	if (_event.key.keysym.sym == SDLK_d)//tests if the event was the 'D' key.
	{
		_x = _x + GetSpeed();//if so, increments its x value by its speed.
		SetX(_x);//This new value is the set to the player's x class member.
	}
	if (_event.key.keysym.sym == SDLK_a)//tests if the event was the 'A' key.
	{
		_x = _x - GetSpeed();//if so, decrements its x value by its speed.
		SetX(_x);//This new value is again set to player's x class member.
	}
}