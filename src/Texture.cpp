#include "Texture.h"
#include <SDL_image.h>
#include <iostream>

Texture::Texture()
{
	//Initialize
	mTexture = NULL;
	mWidth = 0;
	mHeight = 0;
	mPixels = NULL;
	mPitch = 0;
	scaleX = 1;
	scaleY = 1;
}

Texture::~Texture()
{
	free();
}

bool Texture::loadFromFile(std::string path, SDL_Renderer* renderer, Color colorkey)
{
	//Get rid of preexisting texture
	free();

	//The final texture
	SDL_Texture* newTexture = NULL;

	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
	if( loadedSurface == NULL )
	{
		printf( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
	}
	else
	{
		//Convert surface to display format
		SDL_Surface* formattedSurface = SDL_ConvertSurfaceFormat( loadedSurface, SDL_PIXELFORMAT_RGBA8888, NULL );
		if( formattedSurface == NULL )
		{
			printf( "Unable to convert loaded surface to display format! %s\n", SDL_GetError() );
		}
		else
		{
			//Create blank streamable texture
			newTexture = SDL_CreateTexture( renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING, formattedSurface->w, formattedSurface->h );
			if( newTexture == NULL )
			{
				printf( "Unable to create blank texture! SDL Error: %s\n", SDL_GetError() );
			}
			else
			{
				//Enable blending on texture
				SDL_SetTextureBlendMode( newTexture, SDL_BLENDMODE_BLEND );

				//Lock texture for manipulation
				SDL_LockTexture( newTexture, &formattedSurface->clip_rect, &mPixels, &mPitch );

				//Copy loaded/formatted surface pixels
				memcpy( mPixels, formattedSurface->pixels, formattedSurface->pitch * formattedSurface->h );

				//Get image dimensions
				mWidth = formattedSurface->w;
				mHeight = formattedSurface->h;

				//Get pixel data in editable format
				Uint32* pixels = (Uint32*)mPixels;
				int pixelCount = ( mPitch / 4 ) * mHeight;

				//Map colors				
				Uint32 colorKey = SDL_MapRGB( formattedSurface->format, colorkey.r, colorkey.g, colorkey.b);
				Uint32 transparent = SDL_MapRGBA( formattedSurface->format, 0xFF, 0xFF, 0xFF, 0x00 );

				//Color key pixels
				for( int i = 0; i < pixelCount; ++i )
				{
					if( pixels[ i ] == colorKey )
					{
						pixels[ i ] = transparent;
					}
				}

				//Unlock texture to update
				SDL_UnlockTexture( newTexture );
				mPixels = NULL;
			}

			//Get rid of old formatted surface
			SDL_FreeSurface( formattedSurface );
		}	

		//Get rid of old loaded surface
		SDL_FreeSurface( loadedSurface );
	}

	//Return success
	mTexture = newTexture;
	return mTexture != NULL;
}

void Texture::free()
{
	//Free texture if it exists
	if( mTexture != NULL )
	{
		SDL_DestroyTexture( mTexture );
		mTexture = NULL;
		mWidth = 0;
		mHeight = 0;
		mPixels = NULL;
		mPitch = 0;
	}
}

void Texture::setColor(Uint8 r, Uint8 g, Uint8 b)
{
	SDL_SetTextureColorMod( mTexture, r, g, b );
}

void Texture::setColor(Color color)
{
	setColor(color.r, color.g, color.b);
}

void Texture::setBlendMode(SDL_BlendMode blending)
{
	SDL_SetTextureBlendMode( mTexture, blending );
}

void Texture::setAlpha(Uint8 a)
{
	SDL_SetTextureAlphaMod( mTexture, a );
}

void Texture::render(int x, int y, SDL_Renderer* renderer, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip)
{
	//Set rendering space and render to screen
	SDL_Rect renderQuad = { x, y, mWidth * scaleX, mHeight * scaleY };

	//Set clip rendering dimensions
	if( clip != NULL )
	{
		renderQuad.w = scaleX * clip->w;
		renderQuad.h = scaleY * clip->h;
	}

	//Render to screen
	SDL_RenderCopyEx( renderer, mTexture, clip, &renderQuad, angle, center, flip );
}

bool Texture::lockTexture()
{
	bool success = true;

	//Texture is already locked
	if( mPixels != NULL )
	{
		printf( "Texture is already locked!\n" );
		success = false;
	}
	//Lock texture
	else
	{
		if( SDL_LockTexture( mTexture, NULL, &mPixels, &mPitch ) != 0 )
		{
			printf( "Unable to lock texture! %s\n", SDL_GetError() );
			success = false;
		}
	}

	return success;
}

bool Texture::unlockTexture()
{
	bool success = true;

	//Texture is not locked
	if( mPixels == NULL )
	{
		printf( "Texture is not locked!\n" );
		success = false;
	}
	//Unlock texture
	else
	{
		SDL_UnlockTexture( mTexture );
		mPixels = NULL;
		mPitch = 0;
	}

	return success;
}

void* Texture::getPixels()
{
	return mPixels;
}

int Texture::getPitch()
{
	return mPitch;
}

Uint32 Texture::getPixel32(unsigned int x, unsigned int y)
{
	//Convert the pixels to 32 bit
	Uint32 *pixels = (Uint32*)mPixels;

	//Get the pixel requested
	return pixels[ ( y * ( mPitch / 4 ) ) + x ];
}