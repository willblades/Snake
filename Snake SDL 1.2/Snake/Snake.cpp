//======================================================================
//  Name:     Snake.cpp
//  Author:   Will Blades
//  Function: Implements Snake class
//======================================================================

#include "Snake.h"

// Name: Snake()
// Function: Default Constructor 
Snake::Snake()
{
	// Since the Head of the Snake (leading tile) and the body are seperate
	// Bothare initialized seperately, with the body positioned relative to
	// the position of the head 

	head_xposition = (int)MAX_WIDTH / 2;
	head_yposition = (int)MAX_HEIGHT / 2;

	body.push_back({head_xposition, head_yposition});
	for (int i = 1; i < 4; i++)
		body.push_back({ head_xposition - (i*TileIncrement), head_yposition });

	int tempx = rand()%((MAX_WIDTH - 5) + 5);
	int tempy = rand()%((MAX_HEIGHT - 5) + 5);
	food = { tempx, tempy };

	// Direction of the snake is left by default
	direction = 4;

	// load textures
	headTexture = load_image("snake_head.bmp");
	bodyTexture = load_image("snake_body.bmp");
	foodTexture = load_image("food.bmp");
}

// Name: load_image
// Function: Helper function for the constructor. Calls SDL_LoadBMP
SDL_Surface* Snake::load_image(std::string filename)
{
	//Temporary storage for the image that's loaded
	SDL_Surface* loadedImage = NULL;

	//Load the image
	loadedImage = SDL_LoadBMP(filename.c_str());
	return loadedImage;
}

// Name: get_body()
// Function: "Getter" function. Returns the vector holding the snake 
// body location 
std::vector<axis> Snake::get_body()
{
	return body;
}

// Name: IncrementSnakeSize()
// Function: Adds a new tile to the snake and positions it relative to 
// the current direction of the head tile 
void Snake::IncrementSnakeSize()
{
	if (direction == 1)
		body.push_back({ body.at(body.size() - 1).xposition, 
		body.at(body.size() - 1).yposition - TileIncrement });
	else if (direction == 2)
		body.push_back({ body.at(body.size() - 1).xposition, 
		body.at(body.size() - 1).yposition + TileIncrement });
	else if (direction == 3)
		body.push_back({ body.at(body.size() - 1).xposition - TileIncrement, 
		body.at(body.size() - 1).yposition });
	else 
		body.push_back({ body.at(body.size() - 1).xposition + TileIncrement, 
		body.at(body.size() - 1).yposition });
}

// Name: DetectCollision()
// Function: Returns true if the head bumps into any of the four walls. False otherwise
bool Snake::DetectCollision()
{
	if (body.at(0).xposition > MAX_WIDTH - TileIncrement || 
		body.at(0).xposition < TileIncrement)
		return true;
	else if (body.at(0).yposition > MAX_HEIGHT - TileIncrement ||
		body.at(0).yposition < TileIncrement)
		return true;
	else
	{
		for (int i = 1; i < (int)body.size(); i++)
		{
			if ((body.at(0).xposition == body.at(i).xposition) && 
				(body.at(0).yposition == body.at(i).yposition))
				return true;
		}
	}	
	return false;
}

// Name: Move()
// Function: Translates the value of direction into a heading and moves the snake's 
//		     parts one step towards that heading. The Comments below translates the
//			 meaning of each of direction's integer values into an actual distance
void Snake::Move()
{
	// 1 = UP 
	// 2 = DOWN
	// 3 = RIGHT
	// 4 = LEFT
	
	if (direction == 1)
	{
		body.at(0).yposition--;
		for (int i = body.size() - 1; i > 0; i--)
		{
			if (body.at(i).xposition < body.at(0).xposition)
				body.at(i).xposition++;
			else if (body.at(i).xposition > body.at(0).xposition)
				body.at(i).xposition--;
			else
				body.at(i).yposition--;
		}
	}
	else if (direction == 2)
	{
		body.at(0).yposition++;
		for (int i = body.size() - 1; i > 0; i--)
		{
			if (body.at(i).xposition < body.at(0).xposition)
				body.at(i).xposition++;
			else if (body.at(i).xposition > body.at(0).xposition)
				body.at(i).xposition--;
			else
				body.at(i).yposition++;
		}
	}
	else if (direction == 3)
	{
		body.at(0).xposition--;
		for (int i = body.size() - 1; i > 0; i--)
		{
			if (body.at(i).yposition < body.at(0).yposition)
				body.at(i).yposition++;
			else if (body.at(i).yposition > body.at(0).yposition)
				body.at(i).yposition--;
			else
				body.at(i).xposition--;
		}
	}
	else if (direction == 4)
	{
		body.at(0).xposition++;
		for (int i = body.size() - 1; i > 0; i--)
		{
			if (body.at(i).yposition < body.at(0).yposition)
				body.at(i).yposition++;
			else if (body.at(i).yposition > body.at(0).yposition)
				body.at(i).yposition--;
			else
				body.at(i).xposition++;
		}
	}
	else
	{
		// Exception handling when/if direction is anything but numbers 1-4. 
		// Investigate alternatives as this outputs to stdout.txt
		std::cout << "Exception Error: Invalid Direction ID "
			      << direction << std::endl;
		std::cin.ignore(80, '\n');
		exit(-1);
	}
}

// Name: ChangeDirection(int heading)
// Parameter(s): heading: an int that corresponds to direction. Must be between 1-4. 
// Function: Assigns direction to heading. Function is called when user's directional
//			 buttons are pressed. 
void Snake::ChangeDirection(int heading)
{
	switch (heading)
	{
		case 1: direction = 1; break;
		case 2: direction = 2; break;
		case 3: direction = 3; break;
		case 4: direction = 4; break;
		default:
			{
				// Exception handling when/if heading is anything but numbers 1-4. 
				// Investigate alternatives as this outputs to stdout.txt
				std::cout << "Exception Error: Invalid Direction ID "
					<< heading << std::endl;
				std::cin.ignore(80, '\n');
				exit(-1);
			}
	}
}

// Name: get_food()
// Function: "Getter" function. Returns a struct of type axis that holds the
//			 position of the current food item. 
axis Snake::get_food()
{
	return food;
}

// Name: DetectCollision()
// Function: Returns true if the head collides (or "eats") food item. False otherwise
bool Snake::FoodDetected()
{
	axis head = body.at(0);
	int threshold = TileIncrement + 5;

	if ((abs(head.xposition - food.xposition) < threshold) &&
		(abs(head.yposition - food.yposition) < threshold))
		return true;
	else
		return false;
}

// Name: DetectCollision()
// Function: Assign a random position for a new food item using numbers between 
//           5 and (X/Y Dimension - 5)
void Snake::NewFood()
{
	int tempx = rand()%((MAX_WIDTH - 5) + 5);
	int tempy = rand()%((MAX_HEIGHT - 5) + 5);
	food = { tempx, tempy };
}

// Name: ~Snake()
// Function: Default Destructor. Clears used pointers & variables
Snake::~Snake()
{
	body.clear();
	headTexture = NULL;
	bodyTexture = NULL;
	foodTexture = NULL; 
}