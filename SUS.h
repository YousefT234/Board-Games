#ifndef SUS_H
#define SUS_H

#include "BoardGame_Classes.h"
#include <bits/stdc++.h>

using namespace std;
int moves=0;
template <typename T>
class SUS_Board:public Board<T> {
private:
    int last_sus=0;
    int current_sus=0;
    void count_sus();
public:
    SUS_Board ();
    bool update_board (int x , int y , T character);
    void display_board () ;
    bool is_win() ;
    int who_wins();
    bool is_draw();
    bool game_is_over();
    ~SUS_Board();
    int sus_count[2];
};

template <typename T>
class SUS_Player : public Player<T> {
public:
    SUS_Player (string name, T character);
    void getmove(int& x, int& y) ;
};

template <typename T>
class SUS_Random_Player : public RandomPlayer<T>{
public:
    SUS_Random_Player (T character);
    void getmove(int &x, int &y) ;

};





//--------------------------------------- IMPLEMENTATION



// Constructor for SUS_Board
template <typename T>
SUS_Board<T>::SUS_Board() {
    this->sus_count[0]=0;
    this->sus_count[1]=0;
    this->rows = this->columns = 3;
    this->board = new T*[this->rows];
    for (int i = 0; i < this->rows; i++) {
        this->board[i] = new char[this->columns];
        for (int j = 0; j < this->columns; j++) {
            this->board[i][j] = 0;
        }
    }
    this->n_moves = 0;
}
template <typename T>
SUS_Board<T>::~SUS_Board() {
    moves=0;
    // Free the dynamically allocated memory for the board
    for (int i = 0; i < this->rows; i++) {
        delete[] this->board[i];  // Delete each row
    }
    delete[] this->board;  // Delete the main array
}

template <typename T>
bool SUS_Board<T>::update_board(int x, int y, T mark) {
    if (moves>=9)return true;
    if (!(x < 0 || x >= this->rows || y < 0 || y >= this->columns) && (this->board[x][y] == 0)) {
        this->board[x][y] = mark;
        this->count_sus();
        this->n_moves++;
        moves=this->n_moves;
        return true;
    }
    return false;
}


// Display the board and the pieces on it
template <typename T>
void SUS_Board<T>::display_board() {
    if (moves==10)return;
    if (moves==9) moves++;
    for (int i = 0; i < this->rows; i++) {
        cout << "\n| ";
        for (int j = 0; j < this->columns; j++) {
            cout << "(" << i << "," << j << ")";
            cout << setw(2) << this->board[i][j] << " |";
        }
        cout << "\n-----------------------------";
    }
    cout << endl;
}

template <typename T>
void SUS_Board<T>::count_sus() {
    // Check rows and columns
    for (int i = 0; i < this->rows; i++) {
        if ( this->board[i][0] =='S' && this->board[i][1] == 'U' && this->board[i][2] == 'S' )this->current_sus++;
        if ( this->board[0][i] =='S' && this->board[1][i] == 'U' && this->board[2][i] == 'S' )this->current_sus++;
    }
    // Check diagonals
    if ( this->board[0][0] == 'S' && this->board[1][1] == 'U' && this->board[2][2] == 'S' )this->current_sus++;
    if ( this->board[0][2] == 'S' && this->board[1][1] == 'U' && this->board[2][0] == 'S' )this->current_sus++;
    if (this->n_moves%2==0)this->sus_count[0] += (this->current_sus - this->last_sus);
    else this->sus_count[1] += (this->current_sus - this->last_sus);
    this->last_sus = this->current_sus;
    this->current_sus = 0;
}

template <typename T>
bool SUS_Board<T>::is_win() {
    return false;
}
// Return true if 9 moves are done and no winner
template <typename T>
bool SUS_Board<T>::is_draw() {
    return false;
}

template <typename T>
bool SUS_Board<T>::game_is_over() {
    return this->n_moves == 9;
}
template <typename T>
int SUS_Board<T>::who_wins() {
    if (this->sus_count[0]==this->sus_count[1])return 0;
    if (this->sus_count[0]>this->sus_count[1])return 1;
    return 2;
}

//--------------------------------------

// Constructor for SUS_Player
template <typename T>
SUS_Player<T>::SUS_Player(string name, T character) : Player<T>(name, character) {}

template <typename T>
void SUS_Player<T>::getmove(int& x, int& y) {
    if (moves==10)return;
    cout << "\nPlease enter your move x and y (0 to 2) separated by spaces: ";
    cin >> x >> y;
}


// Constructor for SUS_Random_Player
template <typename T>
SUS_Random_Player<T>::SUS_Random_Player(T character) : RandomPlayer<T>(character) {
    this->dimension = 3;
    this->name = "Random Computer Player";
    srand(static_cast<unsigned int>(time(0)));  // Seed the random character generator
}

template <typename T>
void SUS_Random_Player<T>::getmove(int& x, int& y) {
    if (moves==10)return;
    x = rand() % this->dimension;  // Random character between 0 and 2
    y = rand() % this->dimension;
}



#endif //SUS_H
