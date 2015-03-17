//======================================================================
//  Name:     Game_Shell.h
//  Author:   Will Blades
//  Function: Class storing the "Accessories" of the game. Timers, Scores,
//            and Levels are declared & implemented together. 
//======================================================================

#include "SDL.h"

#ifndef GAMESHELL_H
#define GAMESHELL_H

class Shell
{
public:
	Shell();
	~Shell();
	void UpdateScore();
	void IncrementLevel();
	void StartTime();
	void StopTime(); 
	void Pause();
	void UnPause();
	int get_Ticks();
	void TimeDelay();
	bool is_Paused();
private:
	int level;
	int score; 
	int start_ticks;
	int paused_ticks;
	bool started;
	bool paused;

};

#endif