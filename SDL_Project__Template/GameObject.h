#pragma once
#ifndef _GAMEOBJECT_H_
#define _GAMEOBJECT_H_
#include <iostream>
#include <SDL.h>

//Initialises the GameObject class.
class GameObject
{
//Using the private access specifier to initalise class members:
private:
	//Initialising integers.
	int m_x;
	int m_y;
	int m_speed;
//Using the public access specifier to initalise getters, setters and class methods:
public:
	GameObject();//Initialising default constructor.
	GameObject(int _x, int _y, int _speed);//Initialising class members constructor.
	~GameObject();//Initialising destructor.
	//Intialising Getters and Setters.
	int GetX();
	void SetX(int _x);
	int GetY();
	void SetY(int _y);
	int GetSpeed();
	void SetSpeed(int _speed);
};

#endif // !_GAME_H_