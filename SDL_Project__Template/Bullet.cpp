#include "Bullet.h"
#include <iostream>
#include <SDL.h>

Bullet::Bullet():m_image(NULL), m_rect() { Bullet::SetSpeed(5); }//Defines default constructor.
Bullet::Bullet(int _x, int _y) :m_image(NULL), m_rect() { Bullet::SetSpeed(5); SetX(_x); SetY(_y); }//Defines class constructor that intialises class members.
Bullet::~Bullet() {}//Defines class destructor.

//Defines class getters and setters.
SDL_Surface* Bullet::GetImage()
{
	m_image = SDL_LoadBMP("bullet.BMP");//Assigning the file bitmap image to class member m_image.
	if (m_image == NULL)//tests if this member variable is still NULL...
	{
		std::cout << "SDL Could not load image! SDL Error: " << SDL_GetError() << std::endl;//Outputs a SDL error message.
	}
	return m_image;//returns the class member value of m_image.
}

SDL_Rect Bullet::GetRect()
{
	return m_rect;
}

void Bullet::SetRect(SDL_Rect& _rect)//passes SDL rect by reference.
{
	m_rect = _rect;//Assigns the rect parameter to the class member variable m_rect.
}

//Defines class methods.
void Bullet::Move(int _y)//passes integer by value.
{
	_y = _y - GetSpeed();//Increments its the parameter by GetSpeed() getter's return value.
	SetY(_y);//uses a setter to assign the incremented parameter to its y class member variable.
}