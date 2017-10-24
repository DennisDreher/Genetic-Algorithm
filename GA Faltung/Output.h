#pragma once

#include <SDL.h>
#include <stdio.h>
#include <Windows.h>
#include <iostream>
#undef main

#include "Defines.h"

class Output
{
public:
	const int rectWidth = 10;
	const int lineLength = 10;
	const int lineThickness = 2;

	Output();
	virtual ~Output();

	bool Initialize(int iSeqLength);
	void CalculateStart();
	void Draw();

private:
	//fesnter
	SDL_Window* window;
	//flaeche
	SDL_Surface* screenSurface;

	int iSeqLength;

	int startX;
	int startY;
};

#define SCREEN_WIDTH	1500
#define SCREEN_HEIGTH	800

#define WHITE		0xFF, 0xFF, 0xFF
#define BLACK		0x00, 0x00, 0x00
#define RED			0xFF, 0x00, 0x00

#define GAP		10
#define KA		5

#define DELAY	SDL_Delay(15)