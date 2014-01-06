#pragma once

#include <SDL.h>
#include <string>

#include "Color.h"

class Texture
{
private:
	//The actual hardware texture
	SDL_Texture* mTexture;
	void* mPixels;
	int mPitch;

	//Image dimensions
	int mWidth;
	int mHeight;

	float scaleX;
	float scaleY;

public:
	Texture();
	~Texture();

	bool loadFromFile(std::string path, SDL_Renderer* renderer, Color colorkey = magenta);
	void free();
	void setColor(Uint8 r, Uint8 g, Uint8 b);
	void setColor(Color color);
	void setBlendMode(SDL_BlendMode blending);
	void setAlpha(Uint8 a);

	void render(int x, int y, SDL_Renderer* renderer, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);

	int getWidth() { return mWidth; }
	int getHeight() { return mHeight; }

	bool lockTexture();
	bool unlockTexture();
	void* getPixels();
	int getPitch();
	Uint32 getPixel32(unsigned int x, unsigned int y);
	SDL_Texture* getTexture() { return mTexture; }

	void setScale(float scale) { scaleX = scaleY = scale; }
	void setScaleX(float scale) { scaleX = scale; }
	void setScaleY(float scale) { scaleY = scale; }
	float getScaleX() { return scaleX; }
	float getScaleY() { return scaleY; }
};