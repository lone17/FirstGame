#pragma once

#include "imgTexture.h"

class Button{
	private:		
		SDL_Texture *idle, *hover;
		SDL_Rect idle_src, hover_src, area;
	public:
		Button(const string& idle_address, const string& hover_address);
		~Button();
		SDL_Rect align(SDL_Rect src, SDL_Rect des) const;
		void showIdle(SDL_Rect des);
		void showHover(SDL_Rect des);
		bool being_hovered();
};

Button::Button(const string& idle_address, const string& hover_address){
	// load image into surface
	SDL_Surface* surface1 = IMG_Load(idle_address.c_str());
	SDL_Surface* surface2 = IMG_Load(hover_address.c_str());
	// check if image was successfully loaded
	if(surface1 == NULL || surface2 == NULL){
		cout << "ERROR: " << SDL_GetError();
	}

	// create textures from loaded images
	idle = SDL_CreateTextureFromSurface(renderer, surface1);
	hover = SDL_CreateTextureFromSurface(renderer, surface2);
	
	// get textures width and height
	SDL_QueryTexture(idle, NULL, NULL, &idle_src.w, &idle_src.h);
	idle_src.x = idle_src.y = 0;
	SDL_QueryTexture(hover, NULL, NULL, &hover_src.w, &hover_src.h);
	hover_src.x = hover_src.y = 0;
	
	// de-allocate surface
	SDL_FreeSurface(surface1);
	surface1 = NULL;
	SDL_FreeSurface(surface2);
	surface2 = NULL;
}
Button::~Button(){
	// free all texture
	SDL_DestroyTexture(idle);
	idle = NULL;
	SDL_DestroyTexture(hover);
	hover = NULL;
}
SDL_Rect Button::align(SDL_Rect src, SDL_Rect des) const{
	des.x += (des.w - src.w*ratio)/2;
	des.y += (des.h - src.h*ratio)/2;
	des.w = src.w*ratio;
	des.h = src.h*ratio;
	
	return des;
}
void Button::showIdle(SDL_Rect des){
	area = Button::align(idle_src, des);
	// Copy texture to the renderer
	SDL_RenderCopy(renderer, idle, &idle_src, &area);
}
void Button::showHover(SDL_Rect des){
	area = Button::align(hover_src, des);
	// Copy texture to the renderer
	SDL_RenderCopy(renderer, hover, &hover_src, &area);
}
bool Button::being_hovered(){
	if (event.motion.x >= area.x &&
		event.motion.x <= area.x + area.w &&
		event.motion.y >= area.y &&
		event.motion.y <= area.y + area.h)
			return true;
	else return false;
}
