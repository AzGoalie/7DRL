#pragma once

#include <SDL.h>
#include <string>

#include "BitmapFont.h"
#include "Color.h"

class Console
{
private:
	SDL_Window* window;
	SDL_Renderer* renderer;
	int screenWidth, screenHeight;
	const char* title;

	Color forground;
	Color background;

	Texture fontTexture;
	BitmapFont font;

public:
	Console(const char* title, int width, int height);
	~Console();

	bool Init(std::string bitmapPath);
	void Clear();
	void Present();

	void DrawChar(int x, int y, unsigned char c);
	void DrawString(int x, int y, std::string text, float scale = 1);
	void DrawLine(int x1, int y1, int x2, int y2);

	Texture* LoadTexture(std::string path);

	void SetForground(Uint8 r, Uint8 g, Uint8 b);
	void SetForground(Color color);
	void SetBackground(Uint8 r, Uint8 g, Uint8 b);
	void SetBackground(Color color);

	int GetWidth() { return screenWidth; }
	int GetHeight() { return screenHeight; }

	void SetFontScale(float scale) { fontTexture.setScale(scale); }
	float GetFontScale() { return fontTexture.getScaleX(); }
	BitmapFont GetFont() { return font; }
};