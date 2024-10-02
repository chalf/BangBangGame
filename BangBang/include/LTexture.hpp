#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>

class LTexture
{
    private:
        //The actual hardware texture
        SDL_Texture* mTexture;

        //Image dimensions
        int mWidth;
        int mHeight;
        
	public:
        LTexture();
        ~LTexture();

        bool loadFromFile(SDL_Renderer* gRenderer, std::string path );
        void free();
        int getWidth();
        int getHeight();
};