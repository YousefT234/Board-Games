#define _5_5_XO
#include "BoardGame_Classes.h"
#include <bits/stdc++.h>
using namespace std;


template <typename T>
class five_X_O_Board:public Board<T> {
public:
    five_X_O_Board ();
    bool update_board (int x , int y , T symbol);
    void display_board () ;
    bool is_win() ;
    bool is_draw();
    bool game_is_over();
    int checkwinner();
    ~five_X_O_Board();
    int count[2];
};

template <typename T>
class five_X_O_Player : public Player<T> {
public:
    five_X_O_Player (string name, T symbol);
    void getmove(int& x, int& y) ;

};

template <typename T>
class five_X_O_Random_Player : public RandomPlayer<T>{
public:
    five_X_O_Random_Player (T symbol);
    void getmove(int &x, int &y) ;
};





//--------------------------------------- IMPLEMENTATION


// Constructor for five_X_O_Board
template <typename T>
five_X_O_Board<T>::five_X_O_Board() {
    this->count[0] = 0;
    this->count[1] = 0;
    this->rows = this->columns = 5;
    this->board = new char*[this->rows];
    for (int i = 0; i < this->rows; i++) {
        this->board[i] = new char[this->columns];
        for (int j = 0; j < this->columns; j++) {
            this->board[i][j] = 0;
        }
    }
    this->n_moves = 0;
}
template <typename T>
five_X_O_Board<T>::~five_X_O_Board() {
    // Free the dynamically allocated memory for the board
    for (int i = 0; i < this->rows; i++) {
        delete[] this->board[i]; // Delete each row
    }
    delete[] this->board; // Delete the array of row pointers
}

template <typename T>
bool five_X_O_Board<T>::update_board(int x, int y, T mark) {
    // Only update if move is valid
    if (!(x < 0 || x >= this->rows || y < 0 || y >= this->columns) && (this->board[x][y] == 0|| mark == 0)) {

            this->n_moves++;
            this->board[x][y] = toupper(mark);


        return true;
    }
    return false;
}

// Display the board and the pieces on it
template <typename T>
void five_X_O_Board<T>::display_board() {
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
bool five_X_O_Board<T>::is_win() {
    return false;
}
template <typename T>
int five_X_O_Board<T>::checkwinner() {

    // Lambda to update count based on symbol
    auto update_count = [&](char symbol) {
        if (symbol == 'X') this->count[0]++;
        else if (symbol == 'O') this->count[1]++;
    };

    // Check rows
    for (int i = 0; i < this->rows; i++) {
        for (int j = 0; j <= this->columns - 3; j++) {
            if (this->board[i][j] != 0 && this->board[i][j] == this->board[i][j + 1] && this->board[i][j] == this->board[i][j + 2]) {
                update_count(this->board[i][j]);
            }
        }
    }

    // Check columns
    for (int i = 0; i <= this->rows - 3; i++) {
        for (int j = 0; j < this->columns; j++) {
            if (this->board[i][j] != 0 && this->board[i][j] == this->board[i + 1][j] && this->board[i][j] == this->board[i + 2][j]) {
                update_count(this->board[i][j]);
            }
        }
    }

    // Check main diagonals
    for (int i = 0; i <= this->rows - 3; i++) {
        for (int j = 0; j <= this->columns - 3; j++) {
            if (this->board[i][j] != 0 && this->board[i][j] == this->board[i + 1][j + 1] && this->board[i][j] == this->board[i + 2][j + 2]) {
                update_count(this->board[i][j]);
            }
        }
    }

    // Check anti-diagonals
    for (int i = 0; i <= this->rows - 3; i++) {
        for (int j = 2; j < this->columns; j++) {
            if (this->board[i][j] != 0 && this->board[i][j] == this->board[i + 1][j - 1] && this->board[i][j] == this->board[i + 2][j - 2]) {
                update_count(this->board[i][j]);
            }
        }
    }
    if (this->count[0] == this->count[1]) return 0;
    if (this->count[1] < this->count[0]) return 1;
    if (this->count[1] > this->count[0]) return 2;

}



template <typename T>
bool five_X_O_Board<T>::is_draw() {
    return false;
}

template <typename T>
bool five_X_O_Board<T>::game_is_over() {
    if (this->n_moves == 24) {
        return  true;
    }
    return false;
}

template <typename T>
five_X_O_Player<T>::five_X_O_Player(string name, T symbol) : Player<T>(name, symbol) {}

template <typename T>
void five_X_O_Player<T>::getmove(int& x, int& y) {
    cout << "\nPlease enter your move x and y (0 to 4) separated by spaces: ";
    cin >> x >> y;
}

// Constructor for five_X_O_Random_Player
template <typename T>
five_X_O_Random_Player<T>::five_X_O_Random_Player(T symbol) : RandomPlayer<T>(symbol) {
    this->dimension = 5;
    this->name = "Random Computer Player";
    srand(static_cast<unsigned int>(time(0)));  // Seed the random number generator
}

template <typename T>
void five_X_O_Random_Player<T>::getmove(int& x, int& y) {
    x = rand() % this->dimension;
    y = rand() % this->dimension;
}
