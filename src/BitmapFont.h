#pragma once

#include "Texture.h"
#include <string>

class BitmapFont
{
private:
	Texture* mBitmap;
	SDL_Rect mChars[256];
	int mNewLine, mSpace;

public:
	BitmapFont();
	bool buildFont(Texture *bitmap);
	bool buildFont(std::string path);
	void renderText(int x, int y, SDL_Renderer* renderer, std::string text);
	void renderChar(int x, int y, SDL_Renderer* renderer, unsigned char c);
	
	int GetStringWidth(std::string text);
	int GetStringHeight(std::string text);
};