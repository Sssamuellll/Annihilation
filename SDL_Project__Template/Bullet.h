#pragma once
#ifndef _BULLET_H_
#define _BULLET_H_
#include "GameObject.h"
#include <iostream>
#include <SDL.h>

//Initialises the Bullet class that inherits from the GameObject class.
class Bullet : public GameObject
{
//Using the private access specifier to initalise class members:
private:
	SDL_Surface* m_image = NULL;
	SDL_Rect m_rect;
//Using the public access specifier to initalise getters, setters and class methods:
public:
	Bullet();//Initialises default constructor.
	Bullet(int _x, int _y);//Intitialises class constructor that initialises class members.
	~Bullet();//Initialises destructor.
	//Initialises class getters and setters.
	SDL_Surface* GetImage();
	SDL_Rect GetRect();
	void SetRect(SDL_Rect& _rect);
	//Intialises class methods
	void Move(int _y);

};

#endif