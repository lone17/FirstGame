#include <iostream>
#include <fstream>
#include <string.h>
#include <vector>
#include <time.h>
#include <cstdlib>
#include <thread>
#include <chrono>
#include "mylib.h"

using namespace std;

struct pos{
    char symbol=0;
    int x, y, prevX, prevY;
    pos(int _x = 0, int _y = 0){
        x = _x;
        y = _y;
    }
};


struct level{
    int num;
    string hint;
    string answer;
};

void initBoard(pos board[], pos play_board[], int len);
void setBoard(pos board[], const level current_lv);
void drawBoard(pos board[]);
void getData(vector<level>& lv, int& lv_num);
bool readDir(pos& dir, bool& over);
void moveCur(const pos& dir, pos& cur_pos);
void pickLetter(pos play_board[], pos board[], string& player_answer,
                const pos& cur_pos);
void deleteLetter(pos play_board[], pos board[], string& player_answer,
                    const pos cur_pos);
void saveCurrentLv(const int& lv_num);

int main() {
    bool over = false;
    pos dir, cur_pos(18,7);
    vector<level> lv;
    pos board[20];
    int lv_num;
    getData(lv, lv_num);
    while(!over){
        level current_lv = lv[lv_num];
        int len = current_lv.answer.size();
        pos play_board[len];
        string player_answer(len,'-');
        cout << "Level " << lv_num+1 << endl;
        cout << current_lv.hint;
        gotoxy(0,3);
        for(int i=0; i<len; i++){
            cout << player_answer[i] << " ";
        }
        initBoard(board, play_board, len);
        setBoard(board, current_lv);
        drawBoard(board);
        moveCur(dir, cur_pos);
        while(player_answer != current_lv.answer){
            if (readDir(dir, over)) moveCur(dir, cur_pos);
            dir.x = 0; dir.y = 0;
            if(checkKey(KEY_ENTER)){
                pickLetter(play_board, board, player_answer, cur_pos);
                deleteLetter(play_board, board, player_answer, cur_pos);
            }
            this_thread::sleep_for(chrono::milliseconds(150));
        }
        if (lv_num+1 == lv.size()) over = true;
        else {
            lv_num++;
            saveCurrentLv(lv_num);
        }
        system("cls");
    }
    cout << "game over";
    return 0;
}

void initBoard(pos board[], pos play_board[], int len){
    for(int i = 0; i < 20; i++){
        if (i < len){
            play_board[i].symbol = 0; // init with null
            play_board[i].x = i*2;
            play_board[i].y = 3;
        }

        if (i < 10){
            board[i].symbol = 0; // init with null
            board[i].x = i*2;
            board[i].y = 6;
        }
        else{
            board[i].symbol = 0; // init with null
            board[i].x = (i-10)*2;
            board[i].y = 7;
        }
    }
}

void setBoard(pos board[], const level current_lv){
    srand(time(0));
    for (int i=0; i < current_lv.answer.size(); i++){
        int temp = rand() % 20;
        if(board[temp].symbol == 0){
            board[temp].symbol = (current_lv.answer[i]);
        }
        else i--;
    }
    for (int i=0; i<20; i++){
        if(board[i].symbol == 0)
            board[i].symbol = rand() % 26 + 65;
    }
}

void drawBoard(pos board[]){
    for (int i = 0; i < 20; i++){
        gotoxy(board[i].x,board[i].y);
        cout << board[i].symbol;
    }
}

void getData(vector<level>& lv, int& lv_num){
    ifstream data("current_lv.txt");
    data >> lv_num;
    data.close();
    data.open("data.txt");
    while(!data.eof()){
        level temp;
        getline(data,temp.hint);
        getline(data,temp.answer);
        lv.push_back(temp);
    }
    data.close();
}

bool readDir(pos& dir, bool& over) {
	if (checkKey(KEY_LEFT)) {
        dir.x = -2;
        dir.y = 0;
    }
    else if (checkKey(KEY_RIGHT)) {
        dir.x = 2;
        dir.y = 0;
    }
    else if (checkKey(KEY_UP)) {
        dir.y = -1;
        dir.x = 0;
    }
    else if (checkKey(KEY_DOWN)) {
        dir.y = 1;
        dir.x = 0;
    }
    else if (checkKey(KEY_ESC)) over = true;
    // else if(checkKey(KEY_ENTER)) cout << " ";
	else return false;
    return true;
}

void pickLetter(pos play_board[], pos board[], string& player_answer,
                const pos& cur_pos){
    // if(checkKey(KEY_ENTER)
    {
        for(int i = 0; i < 20; i++){
            if(board[i].x == cur_pos.x && board[i].y == cur_pos.y
                 && board[i].symbol != 0){
                for(int j = 0; j < player_answer.size(); j++){
                    if(play_board[j].symbol == 0){
                        cout << " \b";
                        play_board[j].prevX = board[i].x;
                        play_board[j].prevY = board[i].y;
                        play_board[j].symbol = board[i].symbol;
                        player_answer[j] = board[i].symbol;
                        board[i].symbol = 0;
                        gotoxy(play_board[j].x, play_board[j].y);
                        cout << player_answer[j];
                        gotoxy(cur_pos.x, cur_pos.y);
                        break;
                    }
                }
                break;
            }
        }
    }

}

void deleteLetter(pos play_board[], pos board[], string& player_answer,
                    const pos cur_pos){
    // if(checkKey(KEY_ENTER))
    {
        for(int i = 0; i < player_answer.size(); i++){
            if(play_board[i].x == cur_pos.x && play_board[i].y == cur_pos.y
                && play_board[i].symbol != 0){
                cout << "-";
                for(int j=0; j < 20; j++){
                    if(play_board[i].prevX == board[j].x &&
                        play_board[i].prevY == board[j].y){
                        gotoxy(board[j].x,board[j].y);
                        cout << play_board[i].symbol;
                        board[j].symbol = play_board[i].symbol;
                        play_board[i].symbol = 0;
                        player_answer[i] = '-';
                        break;
                    }
                }
                break;
            }
        }
    }
}

void moveCur(const pos& dir, pos& cur_pos){
    cur_pos.x += dir.x;
    cur_pos.y += dir.y;
    if(cur_pos.x < 0) cur_pos.x = 29;
    if(cur_pos.y < 3) cur_pos.y = 7;
    if(cur_pos.x > 29) cur_pos.x = 0;
    if(cur_pos.y > 7) cur_pos.y = 3;
    gotoxy(cur_pos.x, cur_pos.y);
}

void saveCurrentLv(const int& lv_num){
    ofstream outfile("current_lv.txt");
    outfile << lv_num;
    outfile.close();
}
