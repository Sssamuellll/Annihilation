#pragma once
#ifndef _TEXT_H_
#define _TEXT_H_
#include <iostream>
#include <SDL_ttf.h>
#include <SDL.h>

//Initialises Text Class.
class Text
{
//Using the private access specifier to initalise class members:
private:
	TTF_Font* m_font;
	SDL_Surface* m_message;
//Using the public access specifier to initalise getters, setters and class methods:
public:
	Text();
	Text(TTF_Font* _font, SDL_Surface* _message);
	~Text();
	//Initalises class getters and setters.
	TTF_Font* GetFont();
	//Intialises class methods.
	void Init();

};

#endif // !_PLAYER_H_