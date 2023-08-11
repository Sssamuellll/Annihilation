#pragma once
#ifndef _ENEMY_H_
#define _ENEMY_H_
#include "GameObject.h"
#include <iostream>
#include <SDL.h>

//Intialises the Enemy Class inheriting from the GameObject Class.
class Enemy : public GameObject
{
//Using the private access specifier to initalise class members:
private:
	SDL_Surface* m_image = NULL;
	SDL_Rect m_rect;
//Using the public access specifier to initalise getters, setters and class methods:
public:
	Enemy();//Initialises the default constructor.
	Enemy(int _x, int _y);//Initalises the constructor intialising class member variables.
	~Enemy();//Intialsing class destructor.
	//Initialises class getters and setters.
	SDL_Surface* GetImage();
	SDL_Rect GetRect();
	void SetRect(SDL_Rect &_rect);
	//Initialises class methods.
	void Move(int _y);
};

#endif // !_PLAYER_H_