//======================================================================
//  Name:     Game_Engine.cpp
//  Author:   Will Blades
//  Function: Implements Game_Engine class
//======================================================================

#include "Game_Engine.h"

// Name: Engine()
// Function: Default Constructor 
Engine::Engine()
{
	snake = new Snake;
	game_shell = new Shell; 
	//initialize screen 
	screen = NULL;
	//Start SDL
	SDL_Init(SDL_INIT_EVERYTHING | SDL_INIT_NOPARACHUTE); // NO_PARACHUTE flag for MS VC++
	//Set up screen
	screen = SDL_SetVideoMode(MAX_WIDTH, MAX_HEIGHT, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
	SDL_WM_SetCaption("Snake v0.1", "Snake v0.1");
	//TTF_Init();
}

// Name: Snake()
// Function: Default Destructor 
Engine::~Engine()
{
	delete snake;
	delete game_shell;
	//Quit SDL
	SDL_Quit();
	//TTF_Quit();
}

// Name: apply_surface
// Function: Helper function for the constructor. Blits the texture on a rectangle to
//           the screen using SDL_BlitSurface
void apply_surface(int x, int y, SDL_Surface* source, SDL_Surface* destination)
{
	SDL_Rect offset;

	// give the offsets to the rectangle
	offset.x = x;
	offset.y = y;
	SDL_BlitSurface(source, NULL, destination, &offset);
}

// Name: Render(bool flipScreen)
// Parameter(s): Flipscreen (boolean)
// Function: Renders the HUD and textures to screen 
void Engine::Render(bool flipScreen)
{
	// Fill background color first 
	Uint32 backgroundcolor = 0xA9F5E1;
	SDL_FillRect(screen, nullptr, backgroundcolor);
	std::vector<axis>temp = snake->get_body();
	axis tempfood = snake->get_food();

	// Blit Snake on screen
	apply_surface(temp.at(0).xposition, temp.at(0).yposition, snake->headTexture, screen);
	for (int i = 1; i < (int)temp.size(); i++)
		apply_surface(temp.at(i).xposition, temp.at(i).yposition, snake->bodyTexture, screen);

	// Blit food
	apply_surface(tempfood.xposition, tempfood.yposition, snake->foodTexture, screen);
	// Apply HUD
	DrawScreen();

	if (flipScreen) 
		SDL_Flip(screen);
}

// Name: InitiateGame()
// Function: Pre-game processing. To be expanded later
void Engine::InitiateGame()
{
	SDL_EventState(SDL_KEYDOWN, SDL_IGNORE);
	SDL_EventState(SDL_KEYDOWN, SDL_ENABLE);
}

// Name: InitiateGame()
// Function: Render HUD on screen
void Engine::DrawScreen()
{
	SDL_Rect wall;
	Uint32 wallcolor = 0x1C1C1C; 
	int wall_width = 5;

	// The upper horizontal part
	wall.x = 0;
	wall.y = 0;
	wall.w = MAX_WIDTH - wall_width;
	wall.h = wall_width;
	SDL_FillRect(screen, &wall, wallcolor);

	// The bottom horizontal part
	wall.y = MAX_WIDTH - wall_width;
	SDL_FillRect(screen, &wall, wallcolor);

	// The right vertical part
	wall.x = MAX_WIDTH - wall_width;
	wall.y = 0;
	wall.w = wall_width;
	wall.h = MAX_HEIGHT;
	SDL_FillRect(screen, &wall, wallcolor);

	// Draw the left vertical part
	wall.x = 0;
	wall.y = 0;
	wall.w = wall_width;
	wall.h = MAX_HEIGHT - wall_width;
	SDL_FillRect(screen, &wall, wallcolor);
}

// Name: Update()
// Function: Keeps calling Move function unless the game is paused. 
//           Update is evoked in each instance of the main game loop
void Engine::Update()
{
	if (!game_shell->is_Paused())
		snake->Move();
}

// Name: Update()
// Parameter(s): Key ,Must be of standard SDLKey format
// Function: Translates Directional keys into integers for the 
//           snake's class direction variable storage 
int DetermineDirection(SDLKey key)
{
	switch (key)
	{
	case SDLK_UP:
		return 1;
		break;
	case SDLK_DOWN:
		return 2;
		break;
	case SDLK_LEFT:
		return 3;
		break;
	case SDLK_RIGHT:
		return 4;
		break;
	/*default:
		std::cout << "Not a valid movement key \n";
		exit(-1);*/
	}
}

// Name: Start()
// Function: Main good loop. Keep looping until gamerunning is false. 
//           Gamerunning is false when collision is detected or when
//           the user presses ESC or clicks on the window's X button. 
void Engine::Start()
{
	InitiateGame();
	Render();
    gamerunning = true; 
	SDL_Event event;
	while (gamerunning)
	{
		game_shell->StartTime();
		if (snake->DetectCollision())
			gamerunning = false;

		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
				gamerunning = false;
			else if (event.type == SDL_KEYDOWN)
			{
				if (event.key.keysym.sym == SDLK_ESCAPE)
					gamerunning = false;
				else
					snake->ChangeDirection(DetermineDirection(event.key.keysym.sym));
			}
			if (snake->DetectCollision())
				gamerunning = false;
			// Add to the snake body and initiate new food item if snake eats current
			// food
			if (snake->FoodDetected())
			{
				snake->IncrementSnakeSize();
				snake->NewFood();
				game_shell->UpdateScore();
			}
		}
		Update();
		Render();
		game_shell->TimeDelay();
	}
}

