#include "Console.h"
#include <iostream>
using namespace std;

Console::Console(const char* title, int width, int height) 
	: title(title), screenWidth(width), screenHeight(height)
{
	background = black;
	forground = white;
	window = nullptr;
	renderer = nullptr;
}

Console::~Console()
{
	if (renderer)
	{
		SDL_DestroyRenderer(renderer);
		renderer = nullptr;
	}

	if (window)
	{
		SDL_DestroyWindow(window);
		window = nullptr;
	}

	SDL_Quit();
}

bool Console::Init(std::string bitmapPath)
{	
	// Init SDL
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		cout << SDL_GetError() << endl;
		return false;
	}

	// Create window and renderer
	window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, screenWidth, screenHeight, SDL_WINDOW_SHOWN);
	if (window == nullptr)
	{
		cout << SDL_GetError() << endl;
		return false;
	}

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (renderer == nullptr)
	{
		cout << SDL_GetError() << endl;
		return false;
	}

	if (!fontTexture.loadFromFile(bitmapPath, renderer))
	{
		cout << "Error loading bitmap font" << endl;
		return false;
	}

	font.buildFont(&fontTexture);

	return true;
}

void Console::Clear()
{
	SDL_RenderClear(renderer);
}

void Console::Present()
{
	SDL_RenderPresent(renderer);
}

void Console::DrawString(int x, int y, std::string text, float scale)
{
	if (scale != 1)
	{
		float tmp = fontTexture.getScaleX();
		fontTexture.setScale(scale);
		font.renderText(x, y, renderer, text);
		fontTexture.setScale(tmp);
	}

	else
		font.renderText(x, y, renderer, text);
}

void Console::SetBackground(Uint8 r, Uint8 g, Uint8 b)
{
	SDL_SetRenderDrawColor(renderer, r, g, b, 255);
}

void Console::SetForground(Uint8 r, Uint8 g, Uint8 b)
{
	fontTexture.setColor(r, g, b);
}

void Console::SetForground(Color color)
{
	SetForground(color.r, color.g, color.b);
}

void Console::DrawLine(int x1, int y1, int x2, int y2)
{
	SetBackground(255, 255, 255);
	SDL_RenderDrawLine(renderer, x1, y1, x2, y2);
	SetBackground(0, 0, 0);
}

void Console::DrawChar(int x, int y, unsigned char c)
{
	int xx = x % 50 * 16;
	int yy = y % 37 * 16;
	
	font.renderChar(xx, yy, renderer, c);
}