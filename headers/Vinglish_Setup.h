#pragma once

#include "Vinglish_Materials.h"
#include "Vinglish_Draw.h"

int getX(int index, int len);
int getY(int index, int len, int loc, int baseH);
void initBasic();
void initButtonTexture();
void initNevigationTexture();
void drawUI();
void setBoard();
void setAnsBoard(const int& len, pos answer_board[]);

#ifndef Vinglish_init_materials
#define Vinglish_init_materials {\
	initBasic();\
	initButtonTexture();\
	initNevigationTexture();}
#endif /* End Vinglish_init_materials */

#ifndef Vinglish_game_setup
#define Vinglish_game_setup {\
	drawUI();\
	setBoard();\
	setAnsBoard(len, answer_board);\
}
#endif /* End Vinglish_game_setup */

/*	get x co-ordiante for the button's texture
	just a bunch of calculation that's hard to explain in text so you may skip
	just know that basically this is used to align buttons horizontally	*/
// index: letter's serial number in the string
// len: string's length
int getX(int index, int len){
	int row_len; // row's length
	// if string's length > number of cols
	// then 1st-row's length = number of cols
	// and 2nd-row's length = string's length - number of cols
	// else the string could be displayed in 1 row
	// so row's length = string's length
	if (len > col)
		if (index > col) row_len = len - col;
		else row_len = col;
	else row_len = len;

	int row_index; // index's serial number
	// if index > col then index it's in the 2nd row
	// so index's serial number = index - number of cols
	// else index is in the 1st row and index's serial number = index itself
	if (index > col) row_index = index - col;
	else row_index = index;

	int gap = 20; // gap's width between 2 consecutive textures

	int rowW = row_len*letterW + (row_len-1)*gap; // calculate row's width

	int align = (screenW - rowW)/2; // calculate fundamental align

	return align + (row_index-1)*(letterW + gap); // return x co-ordinate of the texture
}

/*	get y co-ordinate of the button's texture
	again, a bunch of calculation
	basically this is used to align buttons vertically */
// index: letter's serial number in the string
// len: string's length
// loc: location of the section where we want the texture to be shown
// baseH: height of that section
int getY(int index, int len, int loc, int baseH){
	int row_amt; // amount of rows
	// if string's length < number of columns then it could be display in 1 row
	// else 2 rows will be displayed
	// since there is no string that could be displayed in more than 2 rows
	if (len <= col) row_amt = 1;
	else row_amt = 2;

	int row_num; // the serial number of the row
	// if index <= number of cols then it's in the 1st row
	// else it must be in the 2nd row
	if(index <= col) row_num = 1;
	else row_num = 2;

	int dis = 40; // distance between 2 columns

	int sheetH = row_amt*letterH + (row_amt-1)*dis; // calculate sheet's height

	// devide the screen into 3 parts and we are working in the 2nd part
	int align = loc + (baseH - sheetH)/2;

	return align + (row_num-1)*(letterH + dis); // return y co-ordinate of the texture
}

/* initialize basic elements */
void initBasic(){
	// initialize subsystems
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0){
		cout << "ERROR: " << SDL_GetError();
		exit(1);
	}

	// initialize the image api
	if (IMG_Init(IMG_INIT_PNG) < 0){
		cout << "ERROR: " << SDL_GetError();
		exit(1);
	}

	// initialize the truetype font api
	if (TTF_Init() < 0){
		cout << "ERROR: " << SDL_GetError();
		exit(1);
	}

	// initialize window
	window = SDL_CreateWindow("Vinglish", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
				screenW, screenH, SDL_WINDOW_BORDERLESS);
	// check if window was initialized sucessfully
	if(window == NULL){
		cout << "ERROR: " << SDL_GetError();
		exit(1);
	}

	// initialize renderer
	renderer = SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED);
	// check if renderer was initialized sucessfully
	if(renderer == NULL){
		cout << "ERROR: " << SDL_GetError();
		exit(1);
	}
}

/*	initialize buttons' textures
	it may looks like a long function
	but actually just same set of steps doing over and over again */
void initButtonTexture(){
	// declare a surface
	SDL_Surface* surface = NULL; 

	/* normal button texture */
	// load image into surface
	surface = IMG_Load("Image/Letters/button.png");
	// check if image was successfully loaded
	if(surface == NULL){
		cout << "ERROR: " << SDL_GetError();
		exit(1);
	}
	// create texture from loaded image
	button_texture = SDL_CreateTextureFromSurface(renderer, surface);

	/* blank button texture */
	// load image into surface
	surface = IMG_Load("Image/Letters/blank.png");
	// check if image was successfully loaded
	if(surface == NULL){
		cout << "ERROR: " << SDL_GetError();
		exit(1);
	}
	// create texture from loaded image
	blank_texture = SDL_CreateTextureFromSurface(renderer, surface);

	/* button texture when hover on */
	// load image into surface
	surface = IMG_Load("Image/Letters/pick.png");
	// check if image was successfully loaded
	if(surface == NULL){
		cout << "ERROR: " << SDL_GetError();
		exit(1);
	}
	// create texture from loaded image
	pick_texture = SDL_CreateTextureFromSurface(renderer, surface);

	/* button texture on click */
	// load image into surface
	surface = IMG_Load("Image/Letters/click.png");
	// check if image was successfully loaded
	if(surface == NULL){
		cout << "ERROR: " << SDL_GetError();
		exit(1);
	}
	// create texture from loaded image
	click_texture = SDL_CreateTextureFromSurface(renderer, surface);

	// de-allocate surface
	SDL_FreeSurface(surface);
	surface = NULL;
}

/* initialize nevigation buttons's textures
	it may looks like a long function but actually 
	it just doing the same set of steps over and over again */
void initNevigationTexture(){
	// declare a suface
	SDL_Surface* surface = NULL;
	
	/* initialize rectangle for back and exit button */
    // all numbers are adjusted manually
    // cuz I am too lazy to write a funcyion for this
    // also due to the heterogeneity of textures' sizes
    // it's not ideal to write a function
	back_icon_rect.x = 20; back_icon_rect.y = 22;
	back_icon_rect.w = 58; back_icon_rect.h = 64;

	back_text_rect.x = 37; back_text_rect.y = 36;
	back_text_rect.w = 30; back_text_rect.h = 30;

	exit_icon_rect.x = 587; exit_icon_rect.y = 22;
	exit_icon_rect.w = 58; exit_icon_rect.h = 64;

	exit_text_rect.x = 604; exit_text_rect.y = 34;
	exit_text_rect.w = 31; exit_text_rect.h = 31;

	/* load icon, text and click texture for exit button */
	// load image into surface
	surface = IMG_Load("Image/exit_text.png");
	// check if image was successfully loaded
	if(surface == NULL){
		cout << "ERROR: " << SDL_GetError();
		exit(1);
	}
	// create texture from loaded image
	exit_text_texture = SDL_CreateTextureFromSurface(renderer, surface);

	// load image into surface
	surface = IMG_Load("Image/exit_icon.png");
	// check if image was successfully loaded
	if(surface == NULL){
		cout << "ERROR: " << SDL_GetError();
		exit(1);
	}
	// create texture from loaded image
	exit_icon_texture = SDL_CreateTextureFromSurface(renderer, surface);

	/* load icon, text and click texture for back button */
	// load image into surface
	surface = IMG_Load("Image/exit_click.png");
	// check if image was successfully loaded
	if(surface == NULL){
		cout << "ERROR: " << SDL_GetError();
		exit(1);
	}
	// create texture from loaded image
	exit_click_texture = SDL_CreateTextureFromSurface(renderer, surface);

	// load image into surface
	surface = IMG_Load("Image/back_text.png");
	// check if image was successfully loaded
	if(surface == NULL){
		cout << "ERROR: " << SDL_GetError();
		exit(1);
	}
	// create texture from loaded image
	back_text_texture = SDL_CreateTextureFromSurface(renderer, surface);

	// load image into surface
	surface = IMG_Load("Image/back_icon.png");
	// check if image was successfully loaded
	if(surface == NULL){
		cout << "ERROR: " << SDL_GetError();
		exit(1);
	}
	// create texture from loaded image
	back_icon_texture = SDL_CreateTextureFromSurface(renderer, surface);

	// de-allocate surface
	SDL_FreeSurface(surface);
	surface = NULL;
}

/*	draw UI layout
	UI is devine into 4 sections
	1st: the nevigation bar
	2nd: the box where the hint is shown
	3rd: the box where the guessing sheet is shown
	4rd: the box where the keyboard is shown */
void drawUI(){
	// clear renderer
	// not really nescessary but just to be sure
	SDL_RenderClear(renderer);

	/* draw nevigation bar */
	drawRect(0, 0, screenW, 100, BROWN_RED);
    // if it's not lv 1, show back button
	if (lv_num > 0) drawTexture(back_icon_texture, back_text_rect);
    // show exit button
	drawTexture(exit_icon_texture, exit_text_rect);
    // show current lv
	drawText(100, "L E V E L " + to_string(lv_num+1), "font/lato/lato-light.ttf", 43, PURE_WHITE, 0, 0);
    // draw a white line to separate nevigation bar and the other parts
    drawRect(0 , 99, 670, 1, PURE_WHITE);

	/* draw hint section */
	drawRect(0, 100, screenW, 270, SALMON_RED);
    // show hint
	drawText(270, lv[lv_num].hint, "font/Lato/lato-regular.ttf",  60, PURE_WHITE, 0 , 100);

	/* draw answer section */
	drawRect(0 , 370, screenW, 340, CREAM_WHITE);

	/* draw keyboard section */
	drawRect(0, 710, screenW, 290, MINT);
}


/* set (x ,y) values for board[] and then display it */
void setBoard(){
	// set default symbol for all board's member as null
	for (int i = 1; i <= board_size; i++) board[i].symbol = "\0";

	// prepare for random
    srand(time(0));

    // for each letter in answer
    for (int i = 1; i <= lv[lv_num].answer.size(); i++){
    	// random a member of the board[]
    	// +1 because board start from 1
        int temp = 1 + rand()%board_size;
        // if that member haven't been used, which means symbol is still as default
        if(board[temp].symbol == "\0"){
        	// set its symbol as the letter number [i-1] of the answer
        	// -1 because i start from 1 but answer start from 0
            board[temp].symbol = (lv[lv_num].answer[i-1]);
            // set (x, y) values
            board[temp].x = getX(temp, board_size);
            board[temp].y = getY(temp, board_size, 710, 290);
            // draw it to the screen
			drawButtonTexture(button_texture, board[temp].x, board[temp].y);
			drawLetter(board[temp].symbol, "font/Simple-regular.ttf",
				45, PURE_WHITE, board[temp].x, board[temp].y-2);
        }
        // if that member is already used, decrease i by one so that we can
        // continue working with letter number [i-1] of the answer
        else i--;
    }

    // after every letter of answer had been set randomly into the board[]
    // we need to random the left over
    // scan each member in board[]
    for (int i = 1; i <= board_size; i++){
    	// if a member haven't been used
        if(board[i].symbol == "\0"){
        	// random a uppercase letter
        	int temp;
        	do temp = 65 + rand()%26;
        	// making sure it won't get F, J, W, Z because the answer is in vietnamese
        	while (temp == 70 || temp == 74 || temp == 87 || temp == 90);
        	// set symbol and (x, y) values for that member
            board[i].symbol = (char)temp;
            board[i].x = getX(i, board_size);
            board[i].y = getY(i, board_size, 710, 290);
            // then draw it
			drawButtonTexture(button_texture, board[i].x, board[i].y);
			drawLetter(board[i].symbol, "font/Simple-regular.ttf",
				45, PURE_WHITE, board[i].x, board[i].y-2);
		}
    }
}

/* draw a series of blank button in the answer section */
// len: the answer's length
// answer_board[]: this function will set (x, y) value for answer_board[]
// we can't just use sizeof instead of using len
// because I didn't use answer_board[0] so that I can count from 1
// for better understanding
void setAnsBoard(const int& len, pos answer_board[]){
	// as you can see i go from 1, not 0 so the 1st index of answer_board[] is 1
	for(int i = 1; i <= len; i++){
		// play a beep sound just to make the game cooler
		Beep(700,50);
		// set (x, y) value for each member of answer_board
		answer_board[i].x = getX(i, len);
		answer_board[i].y = getY(i, len, 370, 340);

		// draw a blank texture
		drawButtonTexture(blank_texture, answer_board[i].x, answer_board[i].y);
		// show it to the screen
		SDL_RenderPresent(renderer);
		// delay so that it won't happen too fast
		SDL_Delay(200);
	}
}

