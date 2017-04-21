#pragma once

#include "Vinglish_Materials.h"

void getData(vector<level>& lv, int& lv_num);
void saveCurrentLv(const int& lv_num);

/*	read data from local file	*/
void getData(vector<level>& lv, int& lv_num){
	// get current level's serial number
	// computer count from 0 but we count from 1
	// so we will need +1 to lv_num when we show it
    ifstream data("data/current_lv.txt");
    data >> lv_num;
    data.close();

    // get all level's data
    data.open("data/levels_data.txt");
    while(!data.eof()){
        level temp;
        getline(data,temp.hint);
        getline(data,temp.answer);
        lv.push_back(temp);
    }
    data.close();
}

// save player's progress
// lv_num is the currently playing lv
void saveCurrentLv(const int& lv_num){
	int temp;
	// open file
    fstream f("data/current_lv.txt");
    // read data from file
    f >> temp;
    // if lv_num is greater than data in file
    if (lv_num > temp)
	{
		// go to begin of file
		f.seekg (0, ios::beg);
		// rewrite data
		f << lv_num;
	}
	// close file
    f.close();
}

