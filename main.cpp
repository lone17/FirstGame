#include "headers/Vinglish_Data.h"
#include "headers/Vinglish_Draw.h"
#include "headers/Vinglish_Setup.h"
#include "headers/Vinglish_Control.h"
#include "headers/imgTexture.h"
#include "headers/Button.h"

#include "headers/imgTexture.h"

int main(int argc, char *argv[]){
	// load data
	getData(lv, lv_num);
	
	// initialize stuffs
	Vinglish_init_materials // see macro in Vinglish_Setup.h
	
	// play background music
	playMixer("music/Happy, Epic, Cinematic & Corporate Background music.mp3", -1);
	
	/* game's introduction */
	// load textures based on screen resolution
	imgTexture gamelogo(ratio == 1 ? "image/game_logo.png" : "image/game_logo-small.png");
	imgTexture lonelogo(ratio == 1 ? "image/lone_logo.png" : "image/lone_logo-small.png");
	imgTexture sologan(ratio == 1 ? "image/sologan.png" : "image/sologan-small.png");
	Button play(ratio == 1 ? "image/play_default.png" : "image/play_default-small.png", 
				ratio == 1 ? "image/play_hover.png" : "image/play_hover-small.png");
	Button quit(ratio == 1 ? "image/quit_default.png" : "image/quit_default-small.png", 
				ratio == 1 ? "image/quit_hover.png" : "image/quit_hover-small.png");
	
	// draw a white box with grey border
	drawRect(0, 0, screenW, screenH, DARK_GREY);
	drawRect(2, 2, screenW-4, screenH-4, PURE_WHITE);
	
	// show my logo
	lonelogo.show({0,0,screenW,screenH});
	sologan.show({0,screenH*0.9,screenW,screenH*0.1});
	SDL_RenderPresent(renderer);
	SDL_Delay(2000);
	
	// show game logo
	drawRect(2, 2, screenW-4, screenH-4, PURE_WHITE);
	gamelogo.show({0,_3rdB,screenW,_3rdH});
	SDL_RenderPresent(renderer);
	SDL_Delay(1000);
	
	//	animation showing main menu
	for (int x = screenW; x >= 0; x-=screenW/67){
		// make sure nothing go beyond window's border
		if(x < 10) x = 0;
		
		/*	this is the 1st section	*/
		drawRect(x, _1stB, screenW, _1stH, BROWN_RED);
		/*	draw title
			if current lv = 0 means game has never been played
			else show current lv	*/
		if (lv_num == 0) {
			drawText(_1stH, "N E W G A M E", "font/lato/lato-light.ttf", 43, PURE_WHITE, x, _1stB);
		}
		else 
			drawText(_1stH, "L E V E L " + to_string(lv_num), "font/lato/lato-light.ttf", 43, PURE_WHITE, x, _1stB);
		
		/*	this isthe 2nd section	*/
		drawRect(-x, _2ndB, screenW, _2ndH, SALMON_RED);
		// draw play button in idle state
		play.showIdle({-x, _2ndB, screenW, _2ndH});
		
		/*	this is the 3r section	*/
		drawRect(x, _3rdB, screenW, _3rdH, CREAM_WHITE);
		// draw game logo
		gamelogo.show({0, _3rdB, screenW, _3rdH});
		
		/*	this is the 4th section	*/
		drawRect(-x, _4thB, screenW, _4thH, MINT);
		// draw quit button in idle state
		quit.showIdle({-x, _4thB, screenW, _4thH});
		
		// update renderer
		SDL_RenderPresent(renderer);
		SDL_Delay(10);
	}
	
	bool over = false;	// over = true when player request to quit or all lv are played
	
	/*	this is the main menu screen */
	while(!over){
		//	wait for event
		if (SDL_WaitEvent(&event) == 0) continue;
		
		//	new game shortcut - for testing only
		if (event.type == SDL_KEYDOWN)
			if (event.key.keysym.sym == SDLK_RETURN){
				lv_num = 0;
				drawRect(0, _1stB, screenW, _1stH, BROWN_RED);
				drawText(_1stH, "N E W G A M E", "font/lato/lato-light.ttf", 43, PURE_WHITE, 0, _1stB);
			}
		
		// animation when mouse cursor hovers on play button
		if (play.being_hovered()){
			drawRect(0, _2ndB, screenW, _2ndH, SALMON_RED);
			play.showHover({0, _2ndB, screenW, _2ndH});
		}
		else play.showIdle({0, _2ndB, screenW, _2ndH});
		
		// animation when mouse cursor hovers on quit button
		if (quit.being_hovered()){
			drawRect(0, _4thB, screenW, _4thH, MINT);
			quit.showHover({0, _4thB, screenW, _4thH});
		}
		else quit.showIdle({0, _4thB, screenW, _4thH});
		
		//	if click event happens
		if (event.type == SDL_MOUSEBUTTONUP){
			// if clicked on play button
			if (play.being_hovered()) break;
			// if clicked on quit button
			if (quit.being_hovered()) over = true;
		}
		
		// show new frame
		SDL_RenderPresent(renderer);
	}
	
    // main game loop
	while (lv_num < lv.size() && !over)
	{
        /* initialize nesscesaries for current lv */
        // so that I don't to call lv[lv_num].answer everytime
        string ans = lv[lv_num].answer;
        // now I don't have to call ans.size() everytime
		int len = ans.size();
        // answer_board[] index starts from 1 so we need len+1 members
		pos answer_board[len+1];
        // default character is '\0'
		string player_answer(len,'\0');
		
		// set up playgound
		Vinglish_game_setup // see macro in Vinglish_Setup.h
		SDL_RenderPresent(renderer); // show playground

        // if player didn't get the right answer yet and wish to keep playing
		while(player_answer != ans){
            // ignore all mouse event during initialization
			SDL_FlushEvents(SDL_MOUSEMOTION, SDL_MOUSEBUTTONUP);

            /*	get the start time of current loop
				this is used to control frame rate	*/
			Uint32 start = SDL_GetTicks();

            // wait for mouse event
			if (SDL_WaitEvent(&event) == 0) continue;
            
            // process player's back/exit request
            Vinglish_back_or_exit

            // process player's actions
            Vinglish_player_action

            // calulate how much time this loop took
			Uint32 time = SDL_GetTicks() - start;
            // control frame rate by controling the amount of time between 2 loops
			if(time < delay) SDL_Delay(delay-time);
            // show new frame
			SDL_RenderPresent(renderer);
		}

        // if player sucessfully guessed the answer
		if (player_answer == ans){
			// inform that player had completed this lv
			lv_completed();
            // next lv
			lv_num++;
            // save checkponit
			saveCurrentLv(lv_num);
		}
	}
	
	//	if all lv are completed, show a message
	if(lv_num == lv.size()){
		more_lv_coming_soon();
	}

    // clean up before closing
	clean();

    return 0;
}


