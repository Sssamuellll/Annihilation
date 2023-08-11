#pragma once
#ifndef _GAME_H_
#define _GAME_H_
#include <SDL.h>
#include <string>
#include "GameObject.h"
#include "Player.h"
#include "Bullet.h"
#include "Enemy.h"
#include "Text.h"
#include "Audio.h"
#include <vector>
#include <iostream>

//Initalising a Game State enum with 4 values.
enum GameState { MENU, HOWTOPLAY, PLAY, QUIT };

//Initalises the Game class.
class Game
{
//Using the private access specifier to initalise class members:
private:
	SDL_Window* m_window{nullptr};
	SDL_Renderer* m_renderer{nullptr};
	int m_screenW;
	int m_screenH;
	int m_gameState;
	Player m_player;
	SDL_Texture* m_teximage = NULL;
	std::vector<Bullet*> m_bullets;
	std::vector<Enemy*> m_enemies;
	int m_lives;
	int m_numOfEnemies;
	int m_enemiesPerWave;
	int m_totalEnemies;
	int m_wave;
	int m_score;
	int m_mouseCollide;
	Text m_text;
	Audio m_audio;
	std::vector<Mix_Chunk*> m_sounds;
	std::vector<Mix_Music*> m_music;
//Using the public access specifier to initalise getters, setters and class methods:
public:
	Game(); //Initalising default constructor.
	~Game(); //Initalising destructor.
	//Initalising all getters and setters.
	int GetScreenW();
	int GetScreenH();
	void SetGameState(int _gameState);
	int GetGameState();
	SDL_Window* GetWindow();
	SDL_Renderer* GetRenderer();
	SDL_Texture* PlayerLoadImage();
	SDL_Texture* BulletLoadImage();
	SDL_Texture* EnemyLoadImage();
	int GetLives();
	void SetLives(int _lives);
	int GetNumOfEnemies();
	void SetNumOfEnemies(int _enemies);
	int GetEnemiesPerWave();
	void SetEnemiesPerWave(int _enemies);
	int GetWave();
	void SetWave(int _wave);
	int GetTotalEnemies();
	void SetTotalEnemies(int _enemies);
	int GetScore();
	void SetScore(int _score);
	Text GetText();
	Audio GetSound();
	int GetMouseCollide();
	void SetMouseCollide(int _mouse);
	//Initalising class methods
	SDL_Texture* LivesLoadText(SDL_Color _colour);
	SDL_Texture* WaveLoadText(SDL_Color _colour);
	SDL_Texture* ScoreLoadText(SDL_Color _colour);
	SDL_Texture* MenuLoadText(SDL_Color _colour, char& _text, int& _h);
	void InitText();
	void Run();
	int Init();
	void GameLoop();
	void Update();
	void MoveBullet();
	void Render();
	void AddEnemies();
	void MoveEnemy();
	void Collision();
	void MouseCollision(SDL_Rect &_play, SDL_Rect &_howTo, SDL_Rect &_quit);
	void CheckWave();
	void InitAudio();
	void InitGame();
};

#endif // !_GAME_H_