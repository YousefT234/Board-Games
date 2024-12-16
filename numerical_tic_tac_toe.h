#ifndef NUMERICAL_TIC_TAC_TOE_H
#define NUMERICAL_TIC_TAC_TOE_H

#include "BoardGame_Classes.h"
#include <bits/stdc++.h>

using namespace std;

template <typename T>
class numerical_Board:public Board<T> {
private:
    map<T,bool> even;
    map<T,bool> odd;
public:
    numerical_Board ();
    bool update_board (int x , int y , T number);
    void display_board () ;
    bool is_win() ;
    bool is_draw();
    bool game_is_over();
    ~numerical_Board();

};

template <typename T>
class numerical_Player : public Player<T> {
public:
    numerical_Player (string name, T number);
    void getmove(int& x, int& y) ;
};

template <typename T>
class numerical_Random_Player : public RandomPlayer<T>{
public:
    numerical_Random_Player (T number);
    void getmove(int &x, int &y) ;
};





//--------------------------------------- IMPLEMENTATION



// Constructor for numerical_Board
template <typename T>
numerical_Board<T>::numerical_Board() {
    for (int i = 1; i <= 9; i++) {
        if(i % 2 == 0) {
            even[i]=1;
            odd[i]=0;
        }
        else {
            odd[i]=1;
            even[i]=0;
        }
    }
    this->rows = this->columns = 3;
    this->board = new T*[this->rows];
    for (int i = 0; i < this->rows; i++) {
        this->board[i] = new T[this->columns];
        for (int j = 0; j < this->columns; j++) {
            this->board[i][j] = 0;
        }
    }
    this->n_moves = 0;
}

// Destructor for numerical_Board
template <typename T>
numerical_Board<T>::~numerical_Board() {

    for (int i = 0; i < this->rows; i++) {
        delete[] this->board[i];  // Delete each row
    }
    delete[] this->board;  // Delete the main pointer to the rows
}

template <typename T>
bool numerical_Board<T>::update_board(int x, int y, T mark) {
    if ((this->n_moves % 2 == 0 and odd[mark]==false) or (this->n_moves % 2 == 1 and even[mark]==false))return false;
    if (!(x < 0 || x >= this->rows || y < 0 || y >= this->columns) && (this->board[x][y] == 0)) {
        this->n_moves++;
        this->board[x][y] = mark;
        even[mark] = false;
        odd[mark] = false;
        return true;
    }
    return false;
}

// Display the board and the pieces on it
template <typename T>
void numerical_Board<T>::display_board() {
    for (int i = 0; i < this->rows; i++) {
        cout << "\n| ";
        for (int j = 0; j < this->columns; j++) {
            cout << "(" << i << "," << j << ")";
            if(this->board[i][j]!=0)cout << setw(2) << this->board[i][j] << " |";
            else cout << setw(2) << " |";
        }
        cout << "\n-----------------------------";
    }
    cout << endl;
}

// Returns true if there is any winner
template <typename T>
bool numerical_Board<T>::is_win() {
    // Check rows and columns
    for (int i = 0; i < this->rows; i++) {
        if ((this->board[i][0] + this->board[i][1] + this->board[i][2]==15 && this->board[i][0] != 0 && this->board[i][1] != 0 && this->board[i][2] != 0) ||
            (this->board[0][i] + this->board[1][i] + this->board[2][i]==15 && this->board[0][i] != 0 && this->board[1][i] != 0 && this->board[2][i] != 0)) {
            return true;
        }
    }

    // Check diagonals
    if ((this->board[0][0] + this->board[1][1] + this->board[2][2]==15 && this->board[0][0] != 0 && this->board[1][1] != 0 && this->board[2][2] != 0 ) ||
        (this->board[0][2]+ this->board[1][1] + this->board[2][0]==15 && this->board[0][2] != 0 && this->board[1][1] != 0 && this->board[2][0] != 0)) {
        return true;
    }

    return false;
}

// Return true if 9 moves are done and no winner
template <typename T>
bool numerical_Board<T>::is_draw() {
    return (this->n_moves == 9 && !is_win());
}

template <typename T>
bool numerical_Board<T>::game_is_over() {
    return is_win() || is_draw();
}

//--------------------------------------

// Constructor for numerical_Player
template <typename T>
numerical_Player<T>::numerical_Player(string name, T number) : Player<T>(name, number) {}

template <typename T>
void numerical_Player<T>::getmove(int& x, int& y) {
    cout << "\nPlease enter your move x and y (0 to 2) separated by spaces: ";
    cin >> x >> y;
    cout << "\nPlease enter a number: ";
    int number;
    cin >> number;
    this->symbol = number;

}


// Constructor for numerical_Random_Player
template <typename T>
numerical_Random_Player<T>::numerical_Random_Player(T number) : RandomPlayer<T>(number) {
    this->dimension = 3;
    this->name = "Random Computer Player";
    srand(static_cast<unsigned int>(time(0)));  // Seed the random number generator
}

template <typename T>
void numerical_Random_Player<T>::getmove(int& x, int& y) {
    x = rand() % this->dimension;  // Random number between 0 and 2
    y = rand() % this->dimension;
    int number = rand() % 9+1;
    this->symbol = number;
}



#endif //NUMERICAL_TIC_TAC_TOE_H
