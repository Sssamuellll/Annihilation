#include "GameObject.h"
#include <iostream>
#include <SDL.h>

GameObject::GameObject():m_x(0), m_y(0), m_speed(0){}//Defining Class default constructor.

GameObject::GameObject(int _x, int _y, int _speed): m_x(_x), m_y(_y), m_speed(_speed){}//Defining Class constructor Initialising Class members.

GameObject::~GameObject(){}//Defining class destructor.

//Initialising class members' getters and setters
int GameObject::GetX()
{
	return m_x;//returning class member value.
}
void GameObject::SetX(int _x)//setters passing integer parameter.
{
	m_x = _x;//assiging parameter to class member variable.
}
int GameObject::GetY()
{
	return m_y;
}
void GameObject::SetY(int _y)
{
	m_y = _y;
}
int GameObject::GetSpeed()
{
	return m_speed;
}
void GameObject::SetSpeed(int _speed)
{
	m_speed = _speed;
}