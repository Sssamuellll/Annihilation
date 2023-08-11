#include "Audio.h"
#include <iostream>
#include <string.h>
#include <SDL_MIXER.h>
#include <SDL.h>
#include <vector>

Audio::Audio() :m_volume(0){}//Defining default constructor.
Audio::Audio(int _vol):m_volume(_vol){}//Defining constructor that initalises class member.
Audio::~Audio(){}//Defines class destructor.
//Defines class getters and setters.
void Audio::SetVolume(int _vol)//passing integer by value.
{
	m_volume = (MIX_MAX_VOLUME * _vol) / 100;//calculates the volume percentage by multiplying the mixers max volume by the integer parameter and divided by 100 to get the percentage.
}
int Audio::GetVolume()
{
	return m_volume;
}
Mix_Music* Audio::LoadMusic(const char* _file)//passes const char pointer as parameter.
{
	Mix_Music* m = NULL;//Initialises a Mix_Music pointer as NULL.
	m = Mix_LoadMUS(_file);//This is then assigned as the load music file using Mix_LoadMUS() to load music file pass as parameter to this function.
	if (m == NULL)//if m is still NULL
	{
		std::cout << Mix_GetError() << std::endl;//A Mix error will be output.
	}
	return m;//returns Mix_Music pointer.
}
Mix_Chunk* Audio::LoadSound(const char* _file)//The similar happens with the sounds, however Mix_Chunks is used to assigns the sound file to rather than Mix_Music as they are just small sound files.
{
	Mix_Chunk* s = NULL;
	s = Mix_LoadWAV(_file);
	if (s == NULL)
	{
		std::cout << Mix_GetError() << std::endl;
	}
	return s;//This chunk pointer is then returned.
}
//Defines class methods.
int Audio::PlayMusic(int _m, std::vector<Mix_Music*> _music)//passes a integer and a Mix_Music vector by value.
{
	if (Mix_PlayingMusic() == 0)//calls the Mix_PlayMusic() function to test for any current music being played. Which the value 0 represent no music being played.
	{
		Mix_Volume(1, m_volume);//If so, the mixer volume is set to channel 1 and passes in the member volume variable.
		Mix_PlayMusic(_music[_m], -1);//Mix_PlayMusic() function plays the music by idenifying the position it is in the music vector and the -1 being passed represent how many times it loops.
	}
	return 0;
}
int Audio::PlaySound(int _s, std::vector<Mix_Chunk*> _sounds)//This is defined similar to the PlayMusic() method.
{
	Mix_Volume(-1, m_volume);
	Mix_PlayChannel(-1, _sounds[_s], 0);//This uses the Mix_PlayChannel() function to play the sound passing values that represent the channel its to be played on, the chunk or the position the sound is in the vector and how many times it loops.
	return 0;
}