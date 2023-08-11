#pragma once
#ifndef _AUDIO_H_
#define _AUDIO_H_
#include <iostream>
#include <SDL_mixer.h>
#include <SDL.h>
#include <vector>

//Initialise Audio Class.
class Audio
{
//Using the private access specifier to initalise class members:
private:
	int m_volume;
//Using the public access specifier to initalise getters, setters and class methods:
public:
	Audio();//Initialises class default constructor.
	Audio(int _vol);//Initialises class constructor that intialises class member variables.
	~Audio();
	//Initialising class getters and setters.
	void SetVolume(int _vol);
	int GetVolume();
	int GetShoot();
	int GetLostLife();
	int GethitAlien();
	Mix_Music* LoadMusic(const char* _file);
	Mix_Chunk* LoadSound(const char* _file);
	//Initialising class methods.
	int PlayMusic(int _m, std::vector<Mix_Music*> _music);
	int PlaySound(int _s, std::vector<Mix_Chunk*> _sounds);
};

#endif // !_PLAYER_H_