#pragma once

#include "Vinglish_Materials.h"

class imgTexture{
	private:
		SDL_Texture* texture;
		SDL_Rect src, area;
	
	public:
		imgTexture(){};
		imgTexture(const string& address);
		~imgTexture();
		SDL_Rect align(SDL_Rect des) const;
		void show(SDL_Rect des);
		SDL_Rect getArea();
		bool being_hovered();
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
	des.x += (des.w - src.w*ratio)/2;
	des.y += (des.h - src.h*ratio)/2;
	des.w = src.w*ratio;
	des.h = src.h*ratio;
	
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
SDL_Rect imgTexture::getArea(){
	return area;
}
bool imgTexture::being_hovered(){
	if (event.motion.x >= area.x &&
		event.motion.x <= area.x + area.w &&
		event.motion.y >= area.y &&
		event.motion.y <= area.y + area.h)
			return true;
	else return false;
}


