//======================================================================
//  Name:     Game_Shell.cpp
//  Author:   Will Blades
//  Function: Implements Game_Shell class
//======================================================================

#include "GameShell.h"

// Name: Shell()
// Function: Default Constructor 
Shell::Shell()
{
	level = 1;
	score = 0;
	start_ticks = 0;
	paused_ticks = 0;
}

// Name: Shell()
// Function: Default Destructor 
Shell::~Shell()
{
	level = 0;
	score = 0;
	start_ticks = 0;
	paused_ticks = 0;
	started = false;
	paused = false;
}

// Name: StartTime()
// Function: Get the current ticks using SDL_GetTicks()
void Shell::StartTime()
{
	started = true;
	paused = false;
	start_ticks = SDL_GetTicks();
}

// Name: get_Ticks()
// Function: Getter function. Returns the number of ticks elapsed ater the game
//           started or after the game paused. 
int Shell::get_Ticks()
{
	if (started) 
	{ 
		//If the timer is paused
		if( paused) 
			return paused_ticks; 
		else  
			return SDL_GetTicks() - start_ticks; 
	} 
	return 0;
}

// Name: Pause()
// Function: Sets the pause flag to true and starts calculated ticks 
//           passed since game started.
void Shell::Pause()
{
	paused = true;
	//Calculate the paused ticks 
	paused_ticks = SDL_GetTicks() - start_ticks;
}

// Name: UnPause()
// Function: UnPauses the game and sets the pause flag to false 
void Shell::UnPause()
{
	paused = false;
	//Calculate the paused ticks 
	start_ticks = SDL_GetTicks() - paused_ticks;
	//Reset paused ticks counter
	paused_ticks = 0;
}

// Name: TimeDelay()
// Function: Delays the display rendering relative to the current level. 
//           Higher levels indicate lower delay, which causes the snake
//           to "move" faster
void Shell::TimeDelay()
{
	SDL_Delay(1000 / (50*((level*1.0)/2)));
}

// Name: UpdateScore()
// Function: Evoked when snake "eats" a food item. Increments score by 10s. 
void Shell::UpdateScore()
{
	score += 10;
}

void Shell::IncrementLevel()
{
	level++;
}

bool Shell::is_Paused()
{
	return paused;
}