#include "Enemy.h"
#include <iostream>
#include <SDL.h>

Enemy::Enemy():m_image(NULL), m_rect() { Enemy::SetSpeed(1); }//Defining Class constructor.
Enemy::Enemy(int _x, int _y):m_image(NULL), m_rect() { Enemy::SetSpeed(1); Enemy::SetY(_y); Enemy::SetX(_x); }//Defining class constructor that initalises class member variables.
Enemy::~Enemy() {}//Defining class destructor.

//Defining class getters and setters
SDL_Surface* Enemy::GetImage()
{
	m_image = SDL_LoadBMP("alien.BMP");//Assigning the file bitmap image to class member m_image.
	if (m_image == NULL)//tests if this member variable is still NULL...
	{
		std::cout << "SDL Could not load image! SDL Error: " << SDL_GetError() << std::endl;//Outputs a SDL error message.
	}
	return m_image;//returns the class member value of m_image.
}
SDL_Rect Enemy::GetRect()
{
	return m_rect;
}

void Enemy::SetRect(SDL_Rect& _rect)//passes SDL rect by reference.
{
	m_rect = _rect;//Assigns the rect parameter to the class member variable m_rect.
}

//Defining class methods
void Enemy::Move(int _y)//passes integer by value.
{
	_y = _y + GetSpeed();//Increments its the parameter by GetSpeed() getter's return value.
	SetY(_y);//uses a setter to assign the incremented parameter to its y class member variable.
}