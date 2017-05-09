#pragma once

#include "Vinglish_Materials.h"

void drawLetter(const string& letter, const string& font_address,
				 int size, SDL_Color colour, int x, int y);
void drawText(int baseH, const string& text, const string& font_address,
				 int size, SDL_Color colour, int x, int y);
void drawButtonTexture(SDL_Texture* t, int x, int y);
void drawTexture(SDL_Texture* t, SDL_Rect des);
void drawImage(const string& address, int x, int y);
void alignImage(const string& address, SDL_Rect area);
void drawRect(int x, int y, int w, int h, SDL_Color colour);
void lv_completed();
void more_lv_coming_soon();

/*	shown formated letter at (x,y) */
// letter: the letter that you want to show
// font_address: address of the font you want to use
// size: size of the letter
// colour: colour of the text
// x, y: where the text will be shown
void drawLetter(const string& letter, const string& font_address,
				 int size, SDL_Color colour, int x, int y){
	SDL_Rect src, des; // source and destination rectangle
	size *= ratio;
	// get font and size
	font = TTF_OpenFont(font_address.c_str(), size);
	if (font == NULL){
		cout << "ERROR: " << SDL_GetError();
		exit(1);
	}

	// load text to surface
	SDL_Surface* surface = TTF_RenderText_Blended(font, letter.c_str(), colour);

	// draw text into the renderer to create a texture
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);

	// get texture's dimensions
	TTF_SizeText(font, letter.c_str(), &src.w, &src.h);

	// set value for source and destination rectangle
	src.x = src.y = 0;
	des.x = x + (letterW - src.w)/2;
	des.y = y + (letterH - src.h)/2;
	des.w = src.w;
	des.h = src.h;

	// Copy texture to the renderer
	SDL_RenderCopy(renderer, texture, &src, &des);

	// de-allocate surface
	SDL_FreeSurface(surface);
	surface = NULL;

	// de-allocate texture
	SDL_DestroyTexture(texture);
	texture = NULL;

	// free font
	TTF_CloseFont(font);
	font = NULL;
}

/*	shown formated text at (x,y) */
// baseH: height of the section where the text will be shown
// text: what you want to show
// font_address: address of the font you want to use
// size: size of the text
// colour: colour of the text
// x, y: where the text will be shown
void drawText(int baseH, const string& text, const string& font_address,
				 int size, SDL_Color colour, int x, int y){
	SDL_Rect src, des; // source and destination rectangle
	size = size*ratio;
	// get font and size
	font = TTF_OpenFont(font_address.c_str(), size);
	if (font == NULL){
		cout << "ERROR: " << SDL_GetError();
		exit(1);
	}

	// load text to surface
	SDL_Surface* surface = TTF_RenderText_Blended(font, text.c_str(), colour);

	// draw text into the renderer
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);

	// get texture's dimensions
	TTF_SizeText(font, text.c_str(), &src.w, &src.h);

	// set value for source and destination rectangle
	src.x = src.y = 0;
	des.x = x + (screenW - src.w)/2;
	des.y = y + (baseH - src.h)/2;
	des.w = src.w;
	des.h = src.h;

	// Copy texture to the renderer
	SDL_RenderCopy(renderer, texture, &src, &des);

	// de-allocate surface
	SDL_FreeSurface(surface);
	surface = NULL;

	// de-allocate texture 
	SDL_DestroyTexture(texture);
	texture = NULL;

	// free font
	TTF_CloseFont(font);
	font = NULL;
}

/*	draw the a chosen button texture into the renderer
	this use dedicatedly for drawing buttons' stuffs
	like the normal button, button when we hover on, button on click	*/
// t: a pointer to the texture that you want to draw
// x, y: co-ordinates in the screen at which the texture will be drawn
void drawButtonTexture(SDL_Texture* t, int x, int y){
	// declare source and destination rectangle
	SDL_Rect src, des;

	// set value for source and destination rectangle
	src.x = src.y = 0;
	des.x = x;
	des.y = y;
	src.w = 54;
	src.h = 78;
	des.w = letterW; 
	des.h = letterH;

	// copy texture to renderer
	SDL_RenderCopy(renderer, t, &src, &des);
}

/*	draw a chosen texture at the area defined by <des>	*/
void drawTexture(SDL_Texture* t, SDL_Rect des){
	// declare source and destination rectangle
	SDL_Rect src;

	// set value for source and destination rectangle
	src.x = src.y = 0;
	src.w = des.w;
	src.h = des.h;
	des.w *= ratio;
	des.h *= ratio;

	// copy texture to renderer
	SDL_RenderCopy(renderer, t, &src, &des);
}


/*	draw an image from <address> at (x,y)	*/
void drawImage(const string& address, int x, int y){
	// declare source and destination rectangle
	SDL_Rect src, des;

	// load image into surface
	SDL_Surface* surface = IMG_Load(address.c_str());
	// check if image was successfully loaded
	if(surface == NULL){
		cout << "ERROR: " << SDL_GetError();
		exit(1);
	}

	// create texture from loaded image
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);

	// get texture width and height
	SDL_QueryTexture(texture, NULL, NULL, &src.w, &src.h);

	// set value for source and destination rectangle
	src.x = src.y = 0;
	des.x = x*ratio;
	des.y = y*ratio;
	des.w = src.w*ratio;
	des.h = src.h*ratio;

	// Copy texture to the renderer
	SDL_RenderCopy(renderer, texture, &src, &des);

	// de-allocate surface
	SDL_FreeSurface(surface);
	surface = NULL;

	// de-allocate texture
	SDL_DestroyTexture(texture);
	texture = NULL;
}

/*	align and draw an image from <address> at the area defined by <area>	*/
void alignImage(const string& address, SDL_Rect area){
	// declare source and destination rectangle
	SDL_Rect src, des;

	// load image into surface
	SDL_Surface* surface = IMG_Load(address.c_str());
	// check if image was successfully loaded
	if(surface == NULL){
		cout << "ERROR: " << SDL_GetError();
		exit(1);
	}

	// create texture from loaded image
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);

	// get texture width and height
	SDL_QueryTexture(texture, NULL, NULL, &src.w, &src.h);

	// set value for source and destination rectangle
	src.x = src.y = 0;
	des.x = area.x + (area.w-src.w*ratio)/2;
	des.y = area.y + (area.h-src.h*ratio)/2;
	des.w = src.w*ratio;
	des.h = src.h*ratio;

	// Copy texture to the renderer
	SDL_RenderCopy(renderer, texture, &src, &des);

	// de-allocate surface
	SDL_FreeSurface(surface);
	surface = NULL;

	// de-allocate texture
	SDL_DestroyTexture(texture);
	texture = NULL;
}

/*	draw a rectangle at (x,y) location with a defined colour
	with w pixels wide, h pixels high */
void drawRect(int x, int y, int w, int h, SDL_Color colour){
	SDL_Rect rect = {x, y, w, h};
	// why this function doesn't just let me pass a SDL_Colour as a param
	// this is so unnescessary
	SDL_SetRenderDrawColor(renderer, colour.r, colour.g, colour.b, colour.a);
	SDL_RenderFillRect(renderer, &rect);
}

// show when a lv is completed
void lv_completed(){
	drawRect(0 , _3rdB, screenW, _3rdH, CREAM_WHITE);
	drawText(_3rdH, "LEVEL COMPLETED", "font/lato/lato-regular.ttf", 60, SALMON_RED, 0, _3rdB);
	SDL_RenderPresent(renderer);
	SDL_Delay(2000);
}

// show if all levels are completed
void more_lv_coming_soon(){
	drawRect(0, 0, screenW, screenH, MINT);
	drawRect(85*ratio, 250*ratio, 500*ratio, 500*ratio, PURE_WHITE);
	drawRect(90*ratio, 255*ratio, 490*ratio, 490*ratio, MINT);
	drawText(130*ratio,"MORE LEVELS","font/lato/lato-regular.ttf",60,PURE_WHITE,0,300*ratio);
	drawText(140*ratio,"COMING","font/lato/lato-regular.ttf",60,PURE_WHITE,0,430*ratio);
	drawText(130*ratio,"SOON","font/lato/lato-regular.ttf",60,PURE_WHITE,0,570*ratio);
	SDL_RenderPresent(renderer);
	SDL_Delay(2500);
}
