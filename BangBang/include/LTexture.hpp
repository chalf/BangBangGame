#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class LTexture
{
	public:
        LTexture();
        ~LTexture();

        bool loadFromFile( std::string path );
        void free();
        void render( int x, int y );
        int getWidth();
        int getHeight();

    private:
        //The actual hardware texture
        SDL_Texture* mTexture;

        //Image dimensions
        int mWidth;
        int mHeight;
};