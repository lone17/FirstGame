//#include "headers/Vinglish_Materials.h"
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
	playMixer("music/background_music.mp3", -1);
	
	// game's introduction
	imgTexture gamelogo("image/game_logo.png");
	imgTexture lonelogo("image/lone_logo.png");
	imgTexture sologan("image/sologan.png");
	Button play("image/play_default.png", "image/play_hover.png");
	Button quit("image/quit_default.png", "image/quit_hover.png");
	drawRect(0, 0, screenW, screenH, DARK_GREY);
	drawRect(2, 2, screenW-4, screenH-4, PURE_WHITE);
	lonelogo.show({0,0,screenW,screenH});
	sologan.show({0,screenH*0.9,screenW,screenH*0.1});
	SDL_RenderPresent(renderer);
	SDL_Delay(2000);
	drawRect(2, 2, screenW-4, screenH-4, PURE_WHITE);
	gamelogo.show({0,_3rdB,screenW,_3rdH});
	SDL_RenderPresent(renderer);
	SDL_Delay(1000);
	
	for (int x = screenW; x >= 0; x-=screenW/67){
		if(x < 10) x = 0;
		drawRect(x, _1stB, screenW, _1stH, BROWN_RED);
		drawText(_1stH, "CURRENT LV: " + to_string(lv_num), "font/lato/lato-light.ttf", 43, PURE_WHITE, x, _1stB);
		
		drawRect(-x, _2ndB, screenW, _2ndH, SALMON_RED);
		play.showIdle({-x, _2ndB, screenW, _2ndH});
		
		drawRect(x, _3rdB, screenW, _3rdH, CREAM_WHITE);
		
		gamelogo.show({0, _3rdB, screenW, _3rdH});
		
		drawRect(-x, _4thB, screenW, _4thH, MINT);
		quit.showIdle({-x, _4thB, screenW, _4thH});
		
		SDL_RenderPresent(renderer);
		SDL_Delay(10);
	}
	bool over = false;
	while(!over){
		if (SDL_WaitEvent(&event) == 0) continue;
		
		if (event.type == SDL_KEYDOWN)
			if (event.key.keysym.sym == SDLK_RETURN){
				lv_num = 1;
				drawRect(0, _1stB, screenW, _1stH, BROWN_RED);
				drawText(_1stH, "CURRENT LV: " + to_string(lv_num), "font/lato/lato-light.ttf", 43, PURE_WHITE, 0, _1stB);
			}
		
		if (play.being_hovered()){
			drawRect(0, _2ndB, screenW, _2ndH, SALMON_RED);
			play.showHover({0, _2ndB, screenW, _2ndH});
		}
		else play.showIdle({0, _2ndB, screenW, _2ndH});
		
		if (quit.being_hovered()){
			drawRect(0, _4thB, screenW, _4thH, MINT);
			quit.showHover({0, _4thB, screenW, _4thH});
		}
		else quit.showIdle({0, _4thB, screenW, _4thH});
		
		if (event.type == SDL_MOUSEBUTTONUP){
			
			if (play.being_hovered()) break;
			
			if (quit.being_hovered()) over = true;
		}
		SDL_RenderPresent(renderer);
	}
    // main game loop, play until you completed all lv
	while (lv_num < lv.size() && !over)
	{
        /* initialize stuffs for current lv */
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
		SDL_RenderPresent(renderer);

        // if player didn't get the right answer yet and wish to keep playing
		while(player_answer != ans){
            // ignore all mouse event during initialization
			SDL_FlushEvents(SDL_MOUSEMOTION, SDL_MOUSEBUTTONUP);

            // get the start time of current loop
            // this is used to control frame rate
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
	if(lv_num == lv.size()){
		more_lv_coming_soon();
	}

    // clean up before closing
	clean();

    return 0;
}


