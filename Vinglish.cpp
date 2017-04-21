//#include "headers/Vinglish_Materials.h"
#include "headers/Vinglish_Data.h"
#include "headers/Vinglish_Draw.h"
#include "headers/Vinglish_Setup.h"
#include "headers/Vinglish_Control.h"

int main(int argc, char *argv[]){
	// load data
	getData(lv, lv_num);

	// initialize stuffs
	Vinglish_init_materials // see macro in Vinglish_Setup.h
	
    // main game loop, play until you completed all lv
	while (lv_num < lv.size())
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

            // index of last button the mouse cursor collided with
			
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


