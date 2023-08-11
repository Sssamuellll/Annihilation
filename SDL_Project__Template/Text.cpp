#include "Text.h"
#include <iostream>
#include <string.h>
#include <SDL_ttf.h>
#include <SDL.h>

Text::Text() :m_font(NULL), m_message(NULL){}//Defines class constructor.
Text::Text(TTF_Font* _font, SDL_Surface* _message): m_font(_font), m_message(_message) {}//Defines class constructor that intialises class members.
Text::~Text() {}//Defines class destructor.

//Defines class getters and setters.
TTF_Font* Text::GetFont()
{
	return m_font;//returns class member m_font.
}

//Defines class methods.
void Text::Init()
{
	m_font = TTF_OpenFont("pixelmix.ttf", 12);//Assigns a font type and a font size to class member m_font by using function TTF_OpenFont() and passing them as paramters.
	if (m_font == nullptr)//if this member is still NULL then...
	{
		std::cout << TTF_GetError() << std::endl;//A TFF error will be output.
	}
}