#pragma once
#ifndef _PLAYER_H_
#define _PLAYER_H_
#include "GameObject.h"
#include <iostream>
#include <SDL.h>

//Initalises Player Class inheriting from the GameObject Class.
class Player : public GameObject
{
//Using the private access specifier to initalise class members:
private:
	SDL_Surface* m_image = NULL;//Initialising a SDL_Surface pointer class member variable as NULL.
//Using the public access specifier to initalise getters, setters and class methods:
public:
	Player();//Initialising default constructor.
	Player(int _x, int _y);//Initialising constructor intialising class members.
	~Player();//Intialising deconstructor.
	//Initialising class members' getters and setters.
	SDL_Surface* GetImage();
	//Intialising class methods.
	void Move(SDL_Event& event, int _x);
};

#endif // !_PLAYER_H_