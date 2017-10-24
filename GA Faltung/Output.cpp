#include "Output.h"

Output::Output()
	:window(nullptr), screenSurface(nullptr), startX(10), startY(10)
{
}

Output::~Output()
{
	//Destroy window 
	SDL_DestroyWindow(window);
	//Quit SDL subsystems 
	SDL_Quit();
}

bool Output::Initialize(int iSeqLength)
{
	this->iSeqLength = iSeqLength;

	//Initialize SDL 
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		COUT << "SDL could not initialize! SDL_Error: " << SDL_GetError();
		return false;
	}
	else
	{
		//Create window 
		//title, xpos, ypos, width, height, parameter
		window = SDL_CreateWindow("Genetic Algorithm", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGTH, SDL_WINDOW_SHOWN);
		if (window == NULL)
		{
			COUT << "Window could not be created! SDL_Error: " << SDL_GetError();
			return false;
		}
	}
	//Get window surface
	screenSurface = SDL_GetWindowSurface(window);

	//fill surface with color: grey
	SDL_Rect rect = { 0 ,0, SCREEN_WIDTH, SCREEN_HEIGTH };
	SDL_FillRect(screenSurface, &rect, SDL_MapRGB(screenSurface->format, 0xAA, 0xAA, 0xAA));
	return true;
}

void Output::CalculateStart()
{
	int candidate = veryBestCandidate[0];
	int generation = veryBestCandidate[1] - 1;

	int lessX = 0;
	int lessY = 0;

	for (int element = 1; element < iSeqLength; element++)
	{
		if (population[generation][candidate][element][X_Value] < lessX)
		{
			lessX = population[generation][candidate][element][X_Value];
		}
		if (population[generation][candidate][element][Y_Value] < lessY)
		{
			lessY = population[generation][candidate][element][Y_Value];
		}
	}
	
	if (lessX < 0)
	{
		lessX = (lessX * -1) / COORD_OFFSET;
		startX = lessX * rectWidth + lessX * lineLength + startX;
	}
	if (lessY < 0)
	{
		lessY = lessY * -1 / COORD_OFFSET;
		startY = lessY * rectWidth + lessY * lineLength + startY;
	}

}

void Output::Draw()
{
	int x = startX;
	int y = startY;

	// x, y, width, height
	SDL_Rect rect = { x, y, rectWidth, rectWidth };

	SDL_Rect lineVertical = { x, y, lineThickness, lineLength };
	SDL_Rect lineHorizontal = { x, y, lineLength, lineThickness };

	int candidate = veryBestCandidate[0];
	int generation = veryBestCandidate[1] - 1;

	//draw first element
	//-----check element type, colour
	if (population[generation][candidate][0][ElementType] == HYDROPHIL)
	{
		SDL_FillRect(screenSurface, &rect, SDL_MapRGB(screenSurface->format, WHITE));
		SDL_UpdateWindowSurface(window);
		DELAY;

	}
	else
	{
		SDL_FillRect(screenSurface, &rect, SDL_MapRGB(screenSurface->format, BLACK));
		SDL_UpdateWindowSurface(window);
		DELAY;

	}
	//CardinalDirections dir = North;
	for (int element = 1; element < iSeqLength; element++)
	{
		switch (population[generation][candidate][element][CardinalDirection])
		{
		case North:
			//y = y - 6 - lineLength;
			y = y - rectWidth - lineLength;
			break;
		case East:
			x = x + rectWidth + lineLength;
			break;
		case South:
			y = y + rectWidth + lineLength;
			break;
		case West:
			x = x - rectWidth - lineLength;
			break;
		default:
			break;
		}

		// update rectangle position
		rect.x = x;
		rect.y = y;

		switch (population[generation][candidate][element][ElementType])
		{
		case HYDROPHIL:
			SDL_FillRect(screenSurface, &rect, SDL_MapRGB(screenSurface->format, 0xFF, 0xFF, 0xFF));
			break;
		case HYDROPHOB:
			SDL_FillRect(screenSurface, &rect, SDL_MapRGB(screenSurface->format, 0x00, 0x00, 0x00));
			break;
		default:
			break;
		}
		SDL_UpdateWindowSurface(window);
		//Wait two seconds 
		DELAY;
	}

	x = startX + 5;
	y = startY + 5;

	for (int element = 1; element < iSeqLength; element++)
	{
		switch (population[generation][candidate][element][CardinalDirection])
		{
		case North:
			y = y - KA - lineLength;
			// update rectangle position
			lineVertical.x = x;
			lineVertical.y = y;

			SDL_FillRect(screenSurface, &lineVertical, SDL_MapRGB(screenSurface->format, BLACK));
			y = y - KA;

			break;
		case East:
			x = x + KA;
			// update rectangle position
			lineHorizontal.x = x;
			lineHorizontal.y = y;

			SDL_FillRect(screenSurface, &lineHorizontal, SDL_MapRGB(screenSurface->format, BLACK));
			x = x + KA + lineLength;

			break;
		case South:
			y = y + KA;
			// update rectangle position
			lineVertical.x = x;
			lineVertical.y = y;

			SDL_FillRect(screenSurface, &lineVertical, SDL_MapRGB(screenSurface->format, BLACK));
			y = y + KA + lineLength;

			break;
		case West:
			x = x - KA - lineLength;
			// update rectangle position
			lineHorizontal.x = x;
			lineHorizontal.y = y;

			SDL_FillRect(screenSurface, &lineHorizontal, SDL_MapRGB(screenSurface->format, BLACK));
			x = x - KA;

			break;
		default:
			break;
		}
		SDL_UpdateWindowSurface(window);
		DELAY;

	}
}