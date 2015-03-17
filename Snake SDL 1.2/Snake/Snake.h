//======================================================================
//  Name:     Snake.h
//  Author:   Will Blades
//  Function: Class storing the actual snake in the game with its
//			  relevant member functions. Food items and relative functions
//			  are also stored in the same class as they make use of the
//            the same struct (axis)
//======================================================================
#include <vector>
#include <iostream>
#include "SDL.h"

#ifndef SNAKE_H
#define SNAKE_H

// Defines snake body & food texture size
#define TileIncrement 15

// Screen dimensions defined relative to texture size
#define MAX_WIDTH  TileIncrement * 20
#define MAX_HEIGHT TileIncrement  * 20

typedef struct axis
{
	int xposition;
	int yposition;
}axis;

class Snake
{
public:
	Snake();
	~Snake();
	void Move();
	void IncrementSnakeSize();
	void ChangeDirection(int heading);
	bool DetectCollision();
	bool FoodDetected();
	void NewFood();
	std::vector<axis> get_body(); 
	axis get_food();
	SDL_Surface* headTexture;
	SDL_Surface* bodyTexture;
	SDL_Surface* foodTexture;
	SDL_Surface* load_image(std::string filename);
private:
	std::vector<axis> body;
	axis food; 
	int head_xposition;
	int head_yposition; 
	int direction;

};

#endif