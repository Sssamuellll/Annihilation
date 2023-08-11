#include "Game.h"
#include "GameObject.h"
#include "Player.h"
#include "Bullet.h"
#include "Text.h"
#include <vector>
#include <iostream>
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <string>
#include <stdlib.h>
#include <time.h>
#include <cstring>

Game::Game()//Defining the Game class' constructor.
{
	//Assiging window and render pointers to nullptr.
	m_window = nullptr;
	m_renderer = nullptr;
	//Assiging the screen dimensions variables.
	m_screenW = 580;
	m_screenH = 1000;
	//Assigning the player member variable to the Player class' constructor passing through integer parameters.
	m_player = Player(0,950);
	//Assigning the gameState member variable to the enum value MENU.
	m_gameState = MENU;
	//Initialising srand passing time(NULL) as a seed parameter.
	srand(time(NULL));
	//Calling the Init() method.
	Init();
}
Game::~Game()//Defining the Game class' destructor.
{
	//Calls SDL functions that destroy the render and window.
	SDL_DestroyRenderer(m_renderer);
	SDL_DestroyWindow(m_window);
}

//Defining class getters and setters.
int Game::GetScreenW()//Defines the GetScreenW() class method.
{
	return m_screenW;//returns its respective member variable.
}

int Game::GetScreenH() 
{
	return m_screenH;
}

void Game::SetGameState(int _gameState)//Defines the SetGameState() class method.
{
	m_gameState = _gameState;//Assigns an integer parameter to the m_gameState member variable.
}

int Game::GetGameState() 
{
	return m_gameState;
}

SDL_Window* Game::GetWindow() 
{
	return m_window;
}

SDL_Renderer* Game::GetRenderer() 
{
	return m_renderer;
}

SDL_Texture* Game::PlayerLoadImage()//Defines the PlayerLoadImage() class method.
{
	SDL_DestroyTexture(m_teximage);//Destroys previous SDL_Texture from memory.
	m_teximage = SDL_CreateTextureFromSurface(GetRenderer(), m_player.GetImage());//Creating a texture from the surface that is returned by GetImage() called by the player object. This is assigned to a SDL_Texture member pointer.
	if (m_teximage == NULL)//if this member pointer is still equal to NULL then...
	{
		std::cout << "SDL could not load texture! SDL Error: " << SDL_GetError() << std::endl;//An error message will output.
	}
	SDL_FreeSurface(m_player.GetImage());//By calling the SDL_FreeSurface function and passing in the surface frees it from memory.
	return  m_teximage;//returns the texture member pointer.
}
SDL_Texture* Game::BulletLoadImage()
{
	SDL_DestroyTexture(m_teximage);//Destroys the SDL_Texture.
	m_teximage = SDL_CreateTextureFromSurface(GetRenderer(), m_bullets[0]->GetImage());
	if (m_teximage == NULL)
	{
		std::cout << "SDL could not load texture! SDL Error: " << SDL_GetError() << std::endl;
	}
	SDL_FreeSurface(m_player.GetImage());
	return  m_teximage;
}
SDL_Texture* Game::EnemyLoadImage()
{
	SDL_DestroyTexture(m_teximage);//Destroys the SDL_Texture.
	m_teximage = SDL_CreateTextureFromSurface(GetRenderer(), m_enemies[0]->GetImage());
	if (m_teximage == NULL)
	{
		std::cout << "SDL could not load texture! SDL Error: " << SDL_GetError() << std::endl;
	}
	SDL_FreeSurface(m_player.GetImage());
	return  m_teximage;
}
SDL_Texture* Game::LivesLoadText(SDL_Color _colour)//Defines the LivesLoadText() class method. An SDL_Color value is passed by value.
{
	SDL_DestroyTexture(m_teximage);//Destroys previous SDL_Texture from memory.
	char message[10] = { "Lives: " };//A cstring is initialised with the message variable.
	char message1[4] = { GetLives()+48 };//Another cstring is initialised to another variable calling the GetLives() function in its initialisiation. The incrementation of 48 is necessary to display the correct integer when dealing with ascii.
	strcat_s(message, message1);//Concatenating message1 onto the message variable.
	SDL_Surface* text = TTF_RenderText_Solid(GetText().GetFont(), message, _colour);//Initialising the TTF_RenderText_Solid() function, passing in the font called by the text object, the text I want to display and the colour of it, assigned to a SDL_Surface variable.
	m_teximage = SDL_CreateTextureFromSurface(GetRenderer(), text);//Creates a texture from the text surface making the text renderable in the render method.
	SDL_FreeSurface(text);//freeing the text surface from memory.
	return m_teximage;//returning the final texture value member pointer of the text.
}
SDL_Texture* Game::ScoreLoadText(SDL_Color _colour)//Defined similar to the above method.
{
	//However, score's values is determined differently as the ascii table only takes single integers into account.
	SDL_DestroyTexture(m_teximage);//Destroys the SDL_Texture.
	int score = GetScore();//the GetScore() method is called and the returned value is assigned to an integer variable.
	char message[12] = { "Score: " };//A cstring initialised with the message variable.
	if (GetScore() > 99)//If the value returned from calling GetScore() is greater than 99...
	{
		char message1[4] = { (GetScore() / 100) + 48 };//A new cstring is initialised with the GetScore() method manipulated by dividing by 100 to calculate the score's hundredth unit and incrementing by 48 to get the correct ascii value.
		strcat_s(message, message1);//This calculation is then concatenated on to the message.
		int hundred = (score / 100) * 100;//works out how many hundreds are in the score and multiplies it by 100.
		score = score - hundred;//The score variable is then subtracted by the variable hundred ready for calculating the tenth unit of the score.
	}
	if (GetScore() > 9)//If the value returned by calling GetScore() is greater than 10...
	{
		//A cstring is initialised with the score integer variable, that depending on if the returned value is also greater than 99 has already been manipulated.
		char message2[4] = { (score / 10) + 48 };//Further calculations are performed to obtain the score's tenth unit.
		strcat_s(message, message2);//This is then concatenated on to the message cstring.
	}
		char message3[4] = { (GetScore() % 10) + 48 };//Lastly, the score's unit is calculated by performing modulus by 10 and incrementing it by 48 to get the correct ascii value.
		strcat_s(message, message3);//This is then concatenated on to the message cstring.
	SDL_Surface* text = TTF_RenderText_Solid(GetText().GetFont(), message, _colour);
	m_teximage = SDL_CreateTextureFromSurface(GetRenderer(), text);
	SDL_FreeSurface(text);
	return m_teximage;
}
SDL_Texture* Game::WaveLoadText(SDL_Color _colour)//Defined very similarly to the above method but...
{
	SDL_DestroyTexture(m_teximage);//Destroys previous SDL_Texture from memory.
	//it only calculates the tenth unit and the unit.
	char message[10] = { "WAVE " };
	if (GetWave() > 9)
	{
		char message1[4] = { (GetWave() - 9) + 48 };//Calculating the tenth unit is done differently, this time 9 is subtracted and then is incremented by 48 to get the ascii value.
		strcat_s(message, message1);
	}
	char message2[4] = { (GetWave() % 10)+48 };
	strcat_s(message, message2);

	SDL_Surface* text = TTF_RenderText_Solid(GetText().GetFont(), message, _colour);
	m_teximage = SDL_CreateTextureFromSurface(GetRenderer(), text);
	SDL_FreeSurface(text);
	return m_teximage;
}

SDL_Texture* Game::MenuLoadText(SDL_Color _colour, char &_text, int &_h)//This is also similarly defined...
{
	//However, two extra parameters are passed by reference into the method.
	SDL_DestroyTexture(m_teximage);//Destroys previous SDL_Texture from memory.
	char message[50] = {};
	if (_text == 'p' && _h==0)//Tests for if the values are equal to 'p' and 0.
	{
		strcpy_s(message, "PLAY");//If so, then a cstring is copied to the previously initialised cstring.
	}
	if (_text == 'h' && _h == 0)
	{
		strcpy_s(message, "HOW TO PLAY");
	}
	if (_text == 'q' && _h == 0)
	{
		strcpy_s(message, "QUIT");
	}
	//These only test for if the _h value is equal to the corrosponding value.
	if (_h == 1) { strcpy_s(message, "HOW TO PLAY:"); }//If so, then a cstring is copied to the message cstring variable.
	if (_h == 2) { strcpy_s(message, "USE KEYS 'A' AND 'D' TO MOVE"); }
	if (_h == 3) { strcpy_s(message, "USE 'SPACE' TO SHOOT ENEMIES"); }
	if (_h == 4) { strcpy_s(message, "PRESS 'ESCAPE' TO RETURN TO THE MENU"); }
	SDL_Surface* text = TTF_RenderText_Solid(GetText().GetFont(), message, _colour);
	m_teximage = SDL_CreateTextureFromSurface(GetRenderer(), text);
	SDL_FreeSurface(text);
	return m_teximage;
}

int Game::GetLives()
{
	return m_lives;
}

void Game::SetLives(int _lives)
{
	m_lives = _lives;
}

int Game::GetNumOfEnemies()
{
	return m_numOfEnemies;
}

void Game::SetNumOfEnemies(int _enemies)
{
	m_numOfEnemies = _enemies;
}

int Game::GetEnemiesPerWave()
{
	return m_enemiesPerWave;
}

void Game::SetEnemiesPerWave(int _enemies)
{
	m_enemiesPerWave = _enemies;
}

int Game::GetWave()
{
	return m_wave;
}

void Game::SetWave(int _wave)
{
	m_wave = _wave;
}

int Game::GetTotalEnemies()
{
	return m_totalEnemies;
}

void Game::SetTotalEnemies(int _enemies)
{
	m_totalEnemies = _enemies;
}

Text Game::GetText()
{
	return m_text;
}

int Game::GetScore()
{
	return m_score;
}

void Game::SetScore(int _score)
{
	m_score = _score;
}

Audio Game::GetSound()
{
	return m_audio;
}

int Game::GetMouseCollide()
{
	return m_mouseCollide;
}
void Game::SetMouseCollide(int _mouse)
{
	m_mouseCollide = _mouse;
}


//Defining class methods.
void Game::Run()//Defining the method.
{
	GameLoop();//Calls the GameLoop() method.
}

int Game::Init()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)//tests for if when initialising SDL using SDL_Init that it doen't return a value less than 0.
	{
		std::cout << "Unable to initialise SDL: %s", SDL_GetError();//If it does than an error message will output.
		return 1;//And 1 is returned.
	}
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)//tests for if when initialising the SDL Mixer using Mix_Init that it doen't return a value less than 0 passing in the frequency, its default format, channels and the chuncksize.
	{
		std::cout << "Unable to open SDL Audio: %s", Mix_GetError();//If it does than a SDL Mixer error message will output.
		return -1;
	}
	else
	{
		m_audio.SetVolume(30);//Otherwise the volume will be set to 30 percent by calling the SetVolume() method called by the m_audio object that was previously initialised in the Game Class' header file.
		InitAudio();//Calls the InitAudio() method.
	}
	if (TTF_Init() < 0)//The same is tested for when initialising SDL_TTF.
	{
		std::cout << "Unable to initialise SDL TTF: %s", TTF_GetError();//A TTF error will output if an integer greater than 0 was returned.
		return 1;
	}
	else
	{
		InitText();//Otherwise, InitText() is called.
	}
	//m_window is assigned with the SDL_CreateWindow() function passing the title of the window, the poisiton it will be created on the screen, the screen dimensions and a SDL_WINDOW_SHOWN flag.
	m_window = SDL_CreateWindow("OOGP A2 - Samuel Leach", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, GetScreenW(), GetScreenH(), SDL_WINDOW_SHOWN);
	if (m_window == 0)//if m_window is still equal to 0 then...
	{
		std::cout << "Unable to create window SDL: %s", SDL_GetError();//A SDL error message will output.
		return -1;//And -1 is returned.
	}

	m_renderer = SDL_CreateRenderer(GetWindow(), -1, SDL_RENDERER_ACCELERATED);//m_renderer is assigned with the SDL_CreateRenderer() function passing the window, an index of -1 and the render mode as parameters.
	if (m_renderer == 0)//The same is tested for with the creation of the renderer.
	{
		std::cout << "Unable to create renderer SDL: %s", SDL_GetError();
		return -1;
	}

	return 0;
}

void Game::InitText()
{
	m_text.Init();//Init method is called from an object of the Text class.
}

void Game::InitAudio()
{
	//Pushing sounds and music onto their respective member vectors through an Audio class object calling methods LoadMusic() and LoadSound() passing in file char strings as parameters.
	m_music.push_back(GetSound().LoadMusic("background.wav"));
	m_sounds.push_back(GetSound().LoadSound("shoot.wav"));
	m_sounds.push_back(GetSound().LoadSound("lost a life.wav"));
	m_sounds.push_back(GetSound().LoadSound("hit alien.wav"));
	GetSound().PlayMusic(0, m_music);//Plays the background music by calling the PlayMusic() method and passing in a vector index and its corrosponding vector.
}

void Game::InitGame()
{
	//Assigning values to member variables.
	m_lives = 3;
	m_numOfEnemies = 5;
	m_enemiesPerWave = 25;
	m_totalEnemies = 0;
	m_wave = 1;
	m_player.SetX(0);
	SetScore(0);
	//Iterating through both the bullet and enemy vectors backwards as well as deleting them from memory.
	if (m_enemies.size() > 0)
	{
		for (int i = m_enemies.size() - 1; i >= 0; i--)
		{
			delete m_enemies[i];
			m_enemies.erase(m_enemies.begin() + i);
		}
	}
	if (m_bullets.size() > 0)
	{
		for (int i = m_bullets.size() - 1; i >= 0; i--)
		{
			delete m_bullets[i];
			m_bullets.erase(m_bullets.begin() + i);
		}
	}
}

void Game::GameLoop()
{
	InitGame();
	//Initialising variables to handle the frame rate.
	int fps = 60;
	int desiredDelta = 1000 / fps;
	//Initalising SDL_Event variable.
	SDL_Event event;
	//While the Game State returns anything but QUIT.
	while (GetGameState() != QUIT)
	{
		if (GetLives() <= 0 && GetGameState() == PLAY)
		{
			InitGame();//Calls a Game class method.
			SetGameState(MENU);//if so, the game state is set to MENU.
		}
		int startLoop = SDL_GetTicks();//Initialises a variable that call of SDL_GetTicks which returns the milliseconds since the SDL library initialisation.
		if (SDL_PollEvent(&event))//Test for and current of pending SDL events.
		{
			if (event.type == SDL_QUIT)//If the event SDL_QUIT, refering to the window exit button, is pressed...
			{
				SetGameState(QUIT);//Game State is set to QUIT by calling the SetGameState() method.
			}
			if (event.type == SDL_MOUSEBUTTONDOWN)//Tests for any mouse button related events have been pressed down...
			{
				if (GetGameState() == MENU)//If the game state is equal to MENU, only allowing this input while in this game state...
				{
					if (event.button.button == SDL_BUTTON_LEFT)//If the left mouse button has been pressed...
					{
						if (GetMouseCollide() == PLAY)//tests for if the called method returns PLAY.
						{
							SetGameState(PLAY);//sets the game state to PLAY.
						}
						if (GetMouseCollide() == HOWTOPLAY)//again tests for if a specific game state returns once the method is called..
						{
							SetGameState(HOWTOPLAY);
						}
						if (GetMouseCollide() == QUIT)
						{
							SetGameState(QUIT);
						}
					}
				}
			}
			if (event.type == SDL_KEYDOWN)//Tests for if any key related events have been pressed down.
			{
				if (event.key.keysym.sym == SDLK_ESCAPE)//tests for if the escape key has been pressed...
				{
					SetGameState(MENU);//if so, the game state is set to MENU.
					InitGame();//Calls a Game class method.
				}
				if (GetGameState() == PLAY)
				{
					m_player.Move(event, m_player.GetX());//calls the Move() method from the Player class object assigned to m_player passing parameters SDL_event object and a method retreiving the object's x position.
					if (event.key.keysym.sym == SDLK_SPACE)//test for if space has been pressed.
					{
						Bullet* bullet = new Bullet(m_player.GetX(), m_player.GetY());//initialising a Bullet object pointer to a new Bullet constructor with parameters of the Player object's x and y positions.
						m_bullets.push_back(bullet);//This object is then pushed to the back of the Bullet vector dereference.
						GetSound().PlaySound(0, m_sounds);//Plays the sound in position 0 of m_sounds vector.
					}
				}
			}
		}
		if (GetGameState() == PLAY)
		{
			Update();//calls the Update() method.
		}
		Render();//calls the Render(0 method.
		int delta = SDL_GetTicks() - startLoop;//initalises and integer again to handle the frame rate that assigns SDL_GetTicks() which is subracted by the variable startloop;
		if (delta < desiredDelta)//if this is less than desired Delta after perform all the above functions.
		{
			SDL_Delay(desiredDelta - delta);//A SDL_Delay is callculated based on the above calculations and by subtracting delta by the desired Delta. maintaining 60 frames per second.
		}
	}
	//Outside of the loop once the game state has been set to QUIT.
	SDL_DestroyTexture(m_teximage);//Destroys the SDL_Texture.
	SDL_DestroyRenderer(GetRenderer());//Destroys the SDL renderer.
	SDL_DestroyWindow(GetWindow());//Destroys the SDL window.
	//Deallocating the music and sounds/chunks from memory.
	Mix_FreeMusic(m_music[0]);
	Mix_FreeChunk(m_sounds[0]);
	Mix_FreeChunk(m_sounds[1]);
	Mix_FreeChunk(m_sounds[2]);
	Mix_Quit;//Quits SDL mixer.
	TTF_Quit();//Quits SDL ttf.
	SDL_Quit();//Quits SDL.
}

void Game::Update()
{
	//Calls the necessary methods to control the game obejcts and features.
	CheckWave();
	MoveBullet();
	AddEnemies();
	MoveEnemy();
	Collision();
}

//Moves the Bullet Game Object when called...
void Game::MoveBullet()
{
	if (m_bullets.size() > 0)//checks the size of the bullet vector is greater than 0.
	{
		for (int i = 0; i < m_bullets.size(); i++)//iterates through the bullet vector.
		{
			m_bullets[i]->Move(m_bullets[i]->GetY());//calls each objects Move() method.
		}
	}
}

//Spawns Enemy Game Objects when called...
void Game::AddEnemies()
{
	if (rand() % 20 == 1)//The rand() function generates a value between 0 and 20, if the value is equal to 1...
	{
		//tests for if the size of the enemy vector is less than the number of enemies that are allowed on the screen at a time.
		//and it tests for if the total enemy objects that have been created in the game are less than the allowed amount per wave.
		if (m_enemies.size() < GetNumOfEnemies() && GetTotalEnemies() < GetEnemiesPerWave())
		{
			int x = rand() % (GetScreenW() - 50);//if so, a random intager between 0 and 50 less than the width of the screen. 50 is subtract as this is the width of the enemy which prevents it from spawning off screen.
			Enemy* enemy = new Enemy(x, 0);//An Enemy object is initialised assigned to a new Enemy constructor passing the random int and 0 as its starting position.
			m_enemies.push_back(enemy);//This object is then pushed to the back of an Enemy vector.
			SetTotalEnemies(GetTotalEnemies() + 1);//The total enemies that have ever been created is incremented by 1.
		}
	}
}

//Moves the Enenmies when called...
void Game::MoveEnemy()
{
	if (m_enemies.size() > 0)//Checks that the Enemy vector size is greater than 0. 
	{
		for (int i = 0; i < m_enemies.size(); i++)//iterates through the Enemy vector.
		{
			m_enemies[i]->Move(m_enemies[i]->GetY());//calls each objects Move method.
		}
	}
}

//Handles all the collision of objects...
void Game::Collision()
{
	//Initialising boolean variables.
	bool enemyCollide = false;
	bool bulletCollide = false;
	if (m_enemies.size() > 0)//Checks that the Enemy vector size is greater than 0.
	{
		for (int i = m_enemies.size() - 1; i >= 0; i--)//Iterates through the vector backwards. This is because when you erase an element from a vector, the vector to the right of it takes up its index and changes the size of the vector and once the loop index i is incremented a whole element is skipped over.
		{
			const SDL_Rect enemy = m_enemies[i]->GetRect();//Initialises the enemy object's rect by calling GetRect().
			if (m_bullets.size() > 0)//Checks that the Bullet vector size is greater than 0.
			{
				//Looping through all the Bullet objects to test for if any of then iteract with this current Enemy object
				for (int j = m_bullets.size() - 1; j >= 0; j--)//Also iterates through the bullect vector backwards for the same reasons as above.
				{
					const SDL_Rect bullet = m_bullets[j]->GetRect();//Initialises the Bullet object's rect by calling GetRect().
					//Calculating Collisions between the enemy and the bullests...
					//left corner or right corner is within the x of the enemy rect and if the bullets y is within the enemy's y.
					//Tests for: the Bullet objects' top left corner is along the Enemy object's x,
					//the Bullets objects' top Right corner is within the Enemy objects' x,
					//and if the Bullet objects' y is within the Enemy object's y.
					//Testing for a cross section of x and y values.
					//This then determines whether the boolean variables equal to true or false.
					if (((bullet.x >= enemy.x && bullet.x <= enemy.x + 50) || ((bullet.x + 50 >= enemy.x && bullet.x + 50 <= enemy.x + 50))) && (bullet.y >= enemy.y && bullet.y <= enemy.y + 50)) { bulletCollide = true; enemyCollide = true; SetScore(GetScore() + 1); GetSound().PlaySound(2, m_sounds); }//plays a sound if there is collision and increments the score by 1 calling class methods.
					else { bulletCollide = false; enemyCollide = false; }
					if (bulletCollide == true) { delete m_bullets[j]; m_bullets.erase(m_bullets.begin() + j); bulletCollide = false; }//If there has been a collision the bullet object that collided will be erased.
					if (enemyCollide == true) { delete m_enemies[i]; m_enemies.erase(m_enemies.begin() + i); enemyCollide = false; }//If there has been a collision the enemy object that collided will be erased.
				}
			}
			if (enemy.y + 50 > GetScreenH()) { enemyCollide = true; SetLives(GetLives() - 1); GetSound().PlaySound(1, m_sounds); delete m_enemies[i]; m_enemies.erase(m_enemies.begin() + i); }//Decrements the lives by 1 and plays a sound calling class methods.

		}
	}
	if (m_bullets.size() > 0)//Again tests for if the Bullets vector's size is greater than 0;
	{
		for (int i = m_bullets.size() - 1; i >= 0; i--)//Again iterates through the Bullet vector backwards.
		{
			const SDL_Rect bullet = m_bullets[i]->GetRect();//initialises the Bullet object's rect through calling class methods.
			if (bullet.y < 0) { bulletCollide = true; }//test for if the Bullet object's y position is less than 0 which is the top of the screen.
			else { bulletCollide = false; }
			if (bulletCollide == true) { delete m_bullets[i]; m_bullets.erase(m_bullets.begin() + i); }//if true then the Bullet object is removed from the vector.
		}
	}
}

//Testing for Mouse Collision when called...
void Game::MouseCollision(SDL_Rect & _play, SDL_Rect & _howTo, SDL_Rect & _quit)
{
	int mouseX, mouseY;//Assiging integer variables.
	SDL_GetMouseState(&mouseX, &mouseY);// Calls the SDL_GetMouseState() passing the integer variables by reference to retrieve the mouse position coordinates.
	//The following if statements handle the collision for the 3 SDL_Rects passed by reference.
	//The collision is very simialr to the previous game object collision however it only checks for if one set of coordinates are within the rect's x and y rather than two.
	if ((mouseX >= _play.x && mouseX <= _play.x+150) && (mouseY >= _play.y && mouseY <= _play.y+50))
	{
		SetMouseCollide(PLAY);//Sets the Game State to PLAY.
	}
	else if ((mouseX >= _howTo.x && mouseX <= _howTo.x+200) && (mouseY >= _howTo.y && mouseY <= _howTo.y+50))
	{
		SetMouseCollide(HOWTOPLAY);
	}
	else if ((mouseX >= _quit.x && mouseX <= _quit.x + 150) && (mouseY >= _quit.y && mouseY <= _quit.y + 50))
	{
		SetMouseCollide(QUIT);
	}
	else
	{
		SetMouseCollide(MENU);
	}
}

//Checks if the wave has been completed when called...
void Game::CheckWave()
{
	if (GetTotalEnemies() == GetEnemiesPerWave() && GetWave() < 10)//Tests for if the total enemies spawned ever is equal to the amount of enemeies per wave and if the wave count is less than 10.
	{
		//increasing the waves difficultly and resetting memeber variables.
		SetWave(GetWave() + 1);//increments wave by 1.
		SetEnemiesPerWave(GetEnemiesPerWave() + 2);//increments enemies per wave by 5.
		SetNumOfEnemies(GetNumOfEnemies() + 1);//increments number of enemies by 2.
		SetTotalEnemies(0);//sets the total eneimes spawned to 0.
	}
}

//When called renders all the visuals to the screen.
void Game::Render()
{
	//Initialising SDL_Colors
	SDL_Color white = { 255, 255, 255 };
	SDL_Color black = { 0, 0, 0 };
	SDL_SetRenderDrawColor(GetRenderer(), 0, 0, 0, 0);//Sets the render draw colour to black.
	SDL_RenderClear(GetRenderer());//clears the renderer of any visuals.
	if (GetGameState() == MENU || GetGameState() == HOWTOPLAY)//tests if the game state is equal to either MENU or HOWTOPLAY.
	{
		int num = 0;//intialising integer variable.
		char text[3] = { 'p', 'h', 'q' };//initialising an array of chars.
		if (GetGameState() == MENU)//test for if the game state is equal to MENU.
		{
			SDL_Rect playTextRect{ 200,400,150,50 };//creates a SDL_Rect with x,y position and size parameters.
			SDL_RenderFillRect(GetRenderer(), &playTextRect);//Fills the rect with the colour thats currently set as the render's draw colour passing the renderer and referenceing the previously initalised SDL_Rect.
			SDL_Rect howTextRect{ 130,455,285,50 };
			SDL_RenderFillRect(GetRenderer(), &howTextRect);
			SDL_Rect quitTextRect{ 200,510,150,50 };
			SDL_RenderFillRect(GetRenderer(), &quitTextRect);
			MouseCollision(playTextRect, howTextRect, quitTextRect);//calls a class method that handles mouse collision passing all the initalised rects as reference.
			//Render copy displays the text onto the rect that has been passed by reference as a parameter.
			//Uses SDL_RenderCopy() to draw whatever is in its parameters to the screen.
			SDL_RenderCopy(GetRenderer(), MenuLoadText(white, text[0], num), NULL, &playTextRect);//Here its drawing text by passing the text method, color, a char array index, an integer and a reference to the rect its going to draw the text on.
			SDL_RenderCopy(GetRenderer(), MenuLoadText(white, text[1], num), NULL, &howTextRect);
			SDL_RenderCopy(GetRenderer(), MenuLoadText(white, text[2], num), NULL, &quitTextRect);
		}
		if (GetGameState() == HOWTOPLAY)
		{
			SDL_Rect h1TextRect{ 40,400,200,25 };
			SDL_RenderFillRect(GetRenderer(), &h1TextRect);
			SDL_Rect h2TextRect{ 40,455,500,25 };
			SDL_RenderFillRect(GetRenderer(), &h1TextRect);
			SDL_Rect h3TextRect{ 40,510,500,25 };
			SDL_RenderFillRect(GetRenderer(), &h1TextRect);
			SDL_Rect h4TextRect{ 40,565,500,25 };
			SDL_RenderFillRect(GetRenderer(), &h1TextRect);
			num = 1;
			SDL_RenderCopy(GetRenderer(), MenuLoadText(white, text[1], num), NULL, &h1TextRect);
			num = 2;
			SDL_RenderCopy(GetRenderer(), MenuLoadText(white, text[1], num), NULL, &h2TextRect);
			num = 3;
			SDL_RenderCopy(GetRenderer(), MenuLoadText(white, text[1], num), NULL, &h3TextRect);
			num = 4;
			SDL_RenderCopy(GetRenderer(), MenuLoadText(white, text[1], num), NULL, &h4TextRect);
		}
	}

	if (GetGameState() == PLAY)
	{
		SDL_Rect livesTextRect{ 0,0,150,50 };
		SDL_RenderFillRect(GetRenderer(), &livesTextRect);
		SDL_Rect scoreTextRect{ 0,55,150,50 };
		SDL_RenderFillRect(GetRenderer(), &scoreTextRect);
		SDL_Rect waveTextRect{ 100,450,350,75 };
		SDL_RenderFillRect(GetRenderer(), &waveTextRect);
		SDL_RenderCopy(GetRenderer(), WaveLoadText(white), NULL, &waveTextRect);
		SDL_Rect playerRect{ m_player.GetX(),950,50,50 };
		//SDL_RenderFillRect(GetRenderer(), &playerRect);
		SDL_RenderCopy(GetRenderer(), PlayerLoadImage(), NULL, &playerRect);
		if (m_bullets.size() > 0)//Again tests for if the Bullet vector size is greater than 0.
		{
			for (int i = 0; i < m_bullets.size(); i++)//iterates through the Bullet vector.
			{
				SDL_Rect bulletRect{ m_bullets[i]->GetX(),m_bullets[i]->GetY(),50,50 };//A SDL_Rect is initalised to represent the bullet object and is given its x and y position as parameters.
				SDL_RenderCopy(GetRenderer(), BulletLoadImage(), NULL, &bulletRect);
				m_bullets[i]->SetRect(bulletRect);//Calls a method to assign rect to a variable inside the class itself.
			}
		}
		//The same is repeated exactly for the enemies.
		if (m_enemies.size() > 0)
		{
			for (int j = 0; j < m_enemies.size(); j++)
			{
				SDL_Rect enemyRect{ m_enemies[j]->GetX(),m_enemies[j]->GetY(),50,50 };
				SDL_RenderCopy(GetRenderer(), EnemyLoadImage(), NULL, &enemyRect);
				m_enemies[j]->SetRect(enemyRect);
			}
		}
		//Uses SDL_RenderCopy to render the text of the amount of lives and the score that the player has to the screen.
		SDL_RenderCopy(GetRenderer(), LivesLoadText(white), NULL, &livesTextRect);
		SDL_RenderCopy(GetRenderer(), ScoreLoadText(white), NULL, &scoreTextRect);
	}
	//Finally, SDL_RenderPresent() passes the renderer as a parameter which renders everything that needs to be rendered to the screen.
	SDL_RenderPresent(GetRenderer());
}