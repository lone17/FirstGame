#pragma once

#include <SDL.h>
#include <SDL_mixer.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

class imgTexture{
	private:
		SDL_Texture* texture; // image's texture
		SDL_Rect src; // image's rect
		SDL_Rect area; // area of the texture on the screen
	
	public:
		/*	constructors	*/
		imgTexture(){};
		// address: image's location
		imgTexture(const string& address);
		
		/*	destructor	*/
		~imgTexture();
		
		/*	load image	*/
		// address: image's location
		void load(const string& address);
		
		/*	align the texture in a given area	*/
		// des: destination's rect
		SDL_Rect align(SDL_Rect des) const;
		
		/*	show image's texture	*/
		// des: destination rect where texture will be shown
		void show(SDL_Rect des);
};

imgTexture::imgTexture(const string& address){
	// load image into surface
	SDL_Surface* surface = IMG_Load(address.c_str());
	// check if image was successfully loaded
	if(surface == NULL){
		cout << "ERROR: " << SDL_GetError();
	}

	// create texture from loaded image
	texture = SDL_CreateTextureFromSurface(renderer, surface);
	
	// get texture width and height
	SDL_QueryTexture(texture, NULL, NULL, &src.w, &src.h);
	src.x = src.y = 0;
	
	// de-allocate surface
	SDL_FreeSurface(surface);
	surface = NULL;
}

SDL_Rect imgTexture::align(SDL_Rect des) const{
	des.x += (des.w - src.w)/2;
	des.y += (des.h - src.h)/2;
	des.w = src.w;
	des.h = src.h;
	
	return des;
}

void imgTexture::show(SDL_Rect des){
	area = imgTexture::align(des);
	// Copy texture to the renderer
	SDL_RenderCopy(renderer, texture, &src, &area);
}

imgTexture::~imgTexture(){
	// de-allocate texture
	SDL_DestroyTexture(texture);
	texture = NULL;
}

void imgTexture::load(const string& address){
	// load image into surface
	SDL_Surface* surface = IMG_Load(address.c_str());
	// check if image was successfully loaded
	if(surface == NULL){
		cout << "ERROR: " << SDL_GetError();
	}

	// create texture from loaded image
	texture = SDL_CreateTextureFromSurface(renderer, surface);
	
	// get texture width and height
	SDL_QueryTexture(texture, NULL, NULL, &src.w, &src.h);
	src.x = src.y = 0;
	
	// de-allocate surface
	SDL_FreeSurface(surface);
	surface = NULL;
}
