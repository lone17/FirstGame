#pragma once

#include <SDL.h>
#include <SDL_mixer.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

class Button{
	private:
		SDL_Texture *idle;	// idle-state texture
		SDL_Texture *hover;	// active-state texture (when button is being hovered)
		SDL_Rect idle_src;	// idle-state rect
		SDL_Rect hover_src;	// active-state rect
		SDL_Rect area;	//	area of the texture which is being shown
	public:
		/* 	constructors	*/
		Button(){};
		// idle_address: idle-state image's location
		// hover_address: active-state image's location
		Button(const string& idle_address, const string& hover_address);
		
		/* 	destructor	*/
		~Button();
		
		/*	align the texture in a given area	*/
		// src: texture's rect
		// des: destination's rect
		SDL_Rect align(SDL_Rect src, SDL_Rect des) const;
		
		/*	show idle-state texture	*/
		// des: destination rect where texture will be shown
		void showIdle(SDL_Rect des);
		
		/*	show active-sate texture	*/
		// des: destination rect where texture will be shown
		void showHover(SDL_Rect des);
		
		/*	check if object is in active state	*/
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
	des.x += (des.w - src.w)/2;
	des.y += (des.h - src.h)/2;
	des.w = src.w;
	des.h = src.h;
	
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
