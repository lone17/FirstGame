#pragma once

#include <iostream>
#include <vector>
#include <windows.h>
#include <time.h>
#include <fstream>
#include "wtypes.h"

#include <SDL.h>
#include <SDL_mixer.h>
#include <SDL_image.h>
#include <SDL_ttf.h>


using namespace std;

#define fps 60 // frame rate
#define delay 1000/fps // time per frame

#define row 2 // number of rows of a board
#define col 8 // number of columns of a board
#define board_size (row*col) // total cells of a board

/* 
	macro some colours 
*/
#define CREAM_WHITE {255, 242, 204, 0}
#define PURE_WHITE {255, 255, 255, 0}
#define MINT {129, 231, 170, 0}
#define SALMON_RED {242, 74, 46, 0}
#define BROWN_RED {152, 30, 10, 0}
#define DARK_GREY {64,64,64,0}

float setRatio();
void clean();

/* 	
	declare ratio and sizes and set default
	the screen is vertically divided into 4 sections 
*/
float ratio = setRatio(); // shrink-ratio
int screenW = 670*ratio, screenH = 1000*ratio; // screen's sizes
int _1stH = 100*ratio, _2ndH = 270*ratio, _3rdH = 340*ratio, _4thH = 290*ratio; // sections' height

// sections' vertical base (start point)
int _1stB, _2ndB, _3rdB, _4thB; 
int letterW = 54*ratio, letterH = 78*ratio;

/* 
	a struct to store level's data 
*/
struct level{
    int num;	// level number
    string hint;	// level's hint
    string answer;	// level's answer
};

/* 
	struct for button object
	pos is short for position
*/
struct pos{
    string symbol;	// a letter shown with the button
    int x, y; // current position 
	int prevX, prevY; // previous position

	// take the button back to previous position
	void resetXY(){
		x = prevX;
		y = prevY;
	}
	
	/*	swap button's current position with another's
		also save current position as previous position */
	void changeXY(pos other){
    	prevX = x;
    	prevY = y;
		this->x = other.x;
		this->y = other.y;
	}
};

/* things we will working with throughout the game */
SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;
TTF_Font *font = NULL;
SDL_Event event;
Mix_Music* music = NULL;

/*
	I declare a lot of texture so that I don't have to remake texture everytime 
	this might take up memory space but will shorten processing time 
	check out image folder to see what these texture are 
	all of them are made entirely by me 
*/
	
// textures for letter button
SDL_Texture* button_texture = NULL;
SDL_Texture* blank_texture = NULL;
SDL_Texture* pick_texture = NULL;
SDL_Texture* click_texture = NULL;

// textures for exit button
SDL_Texture* exit_text_texture = NULL;
SDL_Texture* exit_icon_texture = NULL;
SDL_Texture* exit_click_texture = NULL;

// textures for back button
SDL_Texture* back_text_texture = NULL;
SDL_Texture* back_icon_texture = NULL;
SDL_Texture* back_click_texture = NULL;

/*
	some SDL_Rect to store exit and back button textures' value
	I declare it here because all alignment will be adjusted manually
	since making a function for that would be unnescessary
*/
SDL_Rect back_icon_rect, back_text_rect, exit_icon_rect, exit_text_rect;

vector<level> lv; // where we store all level's data
int lv_num = 0; // current playing level
pos board[board_size + 1]; // initialize a board that has <board_size> cells
// +1 so that index range from 1 to <board_size> for easier understanding

/* 
	get screen's height in pixel and set the ratio accordingly 
*/
float setRatio(){
	// get user's screen resolution
	RECT desktop;
	const HWND hDesktop = GetDesktopWindow();
	GetWindowRect(hDesktop, &desktop);
	
	// if user's screen is less than 100 pixel height, set shrink ratio = 0.7
	if (desktop.bottom < 1080) return 0.7;
	// else shrink ratio = default, which is 1
	else return 1;
}

// Clean up, free system resources
void clean(){
	// de-allocate all textures
	SDL_DestroyTexture(button_texture);
	SDL_DestroyTexture(blank_texture);
	SDL_DestroyTexture(pick_texture);
	SDL_DestroyTexture(click_texture);
	SDL_DestroyTexture(exit_text_texture);
	SDL_DestroyTexture(exit_icon_texture);
	SDL_DestroyTexture(exit_click_texture);
	SDL_DestroyTexture(back_text_texture);
	SDL_DestroyTexture(back_icon_texture);
	SDL_DestroyTexture(back_click_texture);
    button_texture = NULL;
    blank_texture = NULL;
    pick_texture = NULL;
    click_texture = NULL;
    exit_text_texture = NULL;
    exit_icon_texture = NULL;
    exit_click_texture = NULL;
    back_text_texture = NULL;
    back_icon_texture = NULL;
    back_click_texture = NULL;

	// destroy window
	SDL_DestroyWindow(window);
	window = NULL;
	
	// free the music
	Mix_FreeMusic(music);
	music = NULL;

	// quit the truetype font api
	TTF_Quit();

	// quit the image api
	IMG_Quit();
	
	// quit the mixer api
	Mix_Quit();

	// quit SDL subsystems
	SDL_Quit();
}



