#pragma once

#include "Vinglish_Materials.h"

bool player_exit(SDL_Event event);
bool player_back(SDL_Event event);
bool checkCollision(int x, int y, int w, int h);
void last_collision(int& last);
void collision(int& last);
void click(const int& i);
void pick(const int& i, string& player_answer, pos answer_board[]);
void unpick(const int& i, string& player_answer, pos answer_board[]);
void playMixer(const string address, int loops);

// get player's back/exit request
#ifndef Vinglish_back_or_exit
#define Vinglish_back_or_exit {\
	if (lv_num > 0 && player_back(event)){\
		lv_num--;\
		break;\
	}\
	if (player_exit(event)) exit(0);\
}
#endif /* End Vinglish_back_or_exit */

// process all player's actions within main game
#ifndef Vinglish_player_action
#define Vinglish_player_action {\
	static int last;\
	last_collision(last);\
	collision(last);\
	for (int i = 1; i <= board_size; i++){\
		if (checkCollision(board[i].x, board[i].y, letterW, letterH)){\
			if (event.type == SDL_MOUSEBUTTONDOWN) {\
				click(i);\
				break;\
			}\
			if (event.type == SDL_MOUSEBUTTONUP){\
				if (board[i].y < _4thB) unpick(i, player_answer, answer_board);\
				else pick(i, player_answer, answer_board);\
				break;\
			}\
		}\
	}\
}
#endif /* End Vinglish_player_action */

/* check if player want to get exit */
// event: current mouse event
bool player_exit(SDL_Event event){
	// declare the cursor's position as a SDL_Point
	SDL_Point cursor;
	cursor.x = event.motion.x;
	cursor.y = event.motion.y;

	// check if mouse is in the exit button's area
	if (SDL_PointInRect(&cursor, &exit_text_rect)){
		// animation when you hover over the exit button
		drawRect(570*ratio, 0, 100*ratio, 90*ratio, BROWN_RED);
		drawTexture(exit_text_texture, exit_text_rect);
		if (event.type == SDL_MOUSEBUTTONUP) return true;
	}
	else {
		// if not then draw the default texture
		drawRect(570*ratio, 0, 100*ratio, 90*ratio, BROWN_RED);
		drawTexture(exit_icon_texture, exit_icon_rect);
	}
	return false;
}

/* check if player want to get back */
// event: current mouse event
bool player_back(SDL_Event event){
	// declare the cursor's position as a SDL_Point
	SDL_Point cursor;
	cursor.x = event.motion.x;
	cursor.y = event.motion.y;

	// check if mouse is in the back button's area
	if (SDL_PointInRect(&cursor, &back_text_rect)){
		// animation when you hover over the back button
		drawRect(0, 0, 100*ratio, 90*ratio, BROWN_RED);
		drawTexture(back_text_texture, back_text_rect);
		if (event.type == SDL_MOUSEBUTTONUP) return true;
	}
	else {
		// if not then draw the default texture
		drawRect(0, 0, 100*ratio, 90*ratio, BROWN_RED);
		drawTexture(back_icon_texture, back_icon_rect);
	}
	return false;
}

/* check if the mouse cursor is inside the area defined by (x,y,w,h) */
// there is a function similar to this in SDL_rect.h
// but I didn't know it by that time so I make one myself
// switching to the other function would require quite a lot time
// so I'm just gonna leave it here for now
// this doesn't make the code less understandable anyway
bool checkCollision(int x, int y, int w, int h){
	if (event.motion.x >= x &&
		event.motion.x <= x + w &&
		event.motion.y >= y &&
		event.motion.y <= y + h)
			return true;
	else return false;
}

/* use to check if cursor is still hover on the same button or not */
// last: the last button cursor hover on
void last_collision(int& last){
	// if last != default (which is 0)
	// and mouse is not hovering that button anymore
	if (last != 0 && !checkCollision(board[last].x, board[last].y, letterW, letterH))
	{
		// reset "last" button to normal state
		drawButtonTexture(button_texture, board[last].x, board[last].y);
		drawLetter(board[last].symbol, "font/Simple-regular.ttf",
			45, PURE_WHITE, board[last].x, board[last].y-2);

		// reset last to default
		last = 0;
	}
}

/* what happen when you hover to a letter's button */
// last: the last button cursor hover on
void collision(int& last){
	// scan through all board's members
	for (int i = 1; i <= board_size; i++){
		// if mouse cursor is hovering on it
		if (checkCollision(board[i].x, board[i].y, letterW, letterH))
		{
//			if (last != i) Beep(700,40);
			// if it isn't at the button board section,
			// it must be at the answer section
			if (board[i].y < _4thB)
				// draw the backgound match answer section's colour
				drawRect(board[i].x, board[i].y, letterW, letterH, CREAM_WHITE);
			else // if it is at the button board section
				// draw the background match that section's colour
				drawRect(board[i].x, board[i].y, letterW, letterH, MINT);

			// draw pick button texture
			drawButtonTexture(pick_texture, board[i].x, board[i].y);
			drawLetter(board[i].symbol, "font/Simple-regular.ttf",
				45, PURE_WHITE, board[i].x, board[i].y+2);

			// save the last button cursor hovered on
			last = i;
			return;
		}
	}
}


/* animation when you click on button in the keyboard section */
// i: index of the board's member you click on
void click(const int& i){
	// draw the click texture
	drawButtonTexture(click_texture, board[i].x, board[i].y);
	drawLetter(board[i].symbol, "font/Simple-regular.ttf",
		45, PURE_WHITE, board[i].x, board[i].y+2);
	// show it in the screen
	SDL_RenderPresent(renderer);
	// delay a bit so it doesn't happen too fast
	SDL_Delay(50);
}

/* what happen when you click on button in the keyboard section */
// i: index of the board's member we are working with
// player_answer: player's current answer
// answer_board[]: this function will move button in baord[] to the answer_board[]
void pick(const int& i, string& player_answer, pos answer_board[]){
	drawRect(board[i].x, board[i].y, letterW, letterH, MINT);
	for (int j = 0; j < player_answer.size(); j++){
		if (player_answer[j] == '\0') {
			player_answer[j] = board[i].symbol[0];
			board[i].changeXY(answer_board[j+1]);
			drawButtonTexture(button_texture, board[i].x, board[i].y);
			drawLetter(board[i].symbol, "font/Simple-regular.ttf",
				45, PURE_WHITE, board[i].x, board[i].y-2);
		break;
		}
	}
	return;
}

/* what happen when you click on button in the answer section */
// i: index of the board's member we are working with
// player_answer: player's current answer
// answer_board[]: this function will move button in answer_baord[] back to board[]
void unpick(const int& i, string& player_answer, pos answer_board[]){
	// reset button in the answer's section to normal form
	// which is a blank button
	drawButtonTexture(blank_texture, board[i].x, board[i].y);
	// reset (x, y) value of the board's member we are working with
	board[i].resetXY();
	// scan through all members in answer_board[]
	for (int j = 0; j < player_answer.size(); j++){
		// if cursor is at a button's area
		// +1 because player_answer's index starts from 0
		// but answer_board start from 1
		if (checkCollision(answer_board[j+1].x, answer_board[j+1].y, letterW, letterH)){
			// reset character to default, which is '\0'
			player_answer[j] = '\0';
			// redraw the button at the board section
			drawButtonTexture(button_texture, board[i].x, board[i].y);
			drawLetter(board[i].symbol, "font/Simple-regular.ttf",
				45, PURE_WHITE, board[i].x, board[i].y-2);
		break;
		}
	}
}

// play music or sound
void playMixer(const string address, int loops){
	//Load Music
	music = Mix_LoadMUS(address.c_str());
	if (music == NULL)
	{
		cout << Mix_GetError();
	}
	Mix_PlayMusic(music, loops);
}


