//======================================================================
//  Name:     Game_Engine.h
//  Author:   Will Blades
//  Function: Class storing the SDL video mechanics of the game. The game
//            main loop is implemented here, thus all the used classes are 
//			  evoked and combined together
//======================================================================

#include "Snake.h"
#include "GameShell.h"
#include "SDL_ttf.h"

#ifndef GAME_ENGINE_H
#define GAME_ENGINE_H

class Engine
{
public:
	Engine();
	~Engine();
	void InitiateGame();
	void DrawScreen();
	void Update();
	void Render(bool flipScreen = true);
	void GameOver();
	void PauseGame();
	void Start();
	
private:
	SDL_Surface* screen;
	Snake* snake;
	Shell* game_shell;
	bool gamerunning;
};

#endif