#ifndef ULTIMATE_H
#define ULTIMATE_H
#include "BoardGame_Classes.h"
#include "3x3X_O.h"
#include <bits/stdc++.h>
using namespace std;
int board_index;
vector<bool> is_free(9,true);
template <typename T>
class ultimate_Board:public Board<T> {
private:
    X_O_Board<T>* boards;
public:
    ultimate_Board ();
    bool update_board (int x , int y , T symbol);
    void display_board () ;
    bool is_win() ;
    bool is_draw();
    bool game_is_over();
    ~ultimate_Board();
};

template <typename T>
class ultimate_Player : public Player<T> {
public:
    ultimate_Player (string name, T symbol);
    void getmove(int& x, int& y) ;
};

template <typename T>
class ultimate_Random_Player : public RandomPlayer<T>{
public:
    ultimate_Random_Player (T symbol);
    void getmove(int &x, int &y) ;
};





//--------------------------------------- IMPLEMENTATION



// Constructor for ultimate_Board
template <typename T>
ultimate_Board<T>::ultimate_Board()
 {
    for (int i = 0; i < 9; i++)is_free[i]=true;
    this->boards = new X_O_Board<T>[9];
    this->rows = this->columns = 3;
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
ultimate_Board<T>::~ultimate_Board() {

    // Clean up the array of X_O_Board objects
    delete[] this->boards;

    // Clean up the ultimate board
    for (int i = 0; i < this->rows; i++) {
        delete[] this->board[i];
    }
    delete[] this->board;
}
template <typename T>
bool ultimate_Board<T>::update_board(int x, int y, T mark) {
    if (board_index>=0 && board_index<9 and is_free[board_index]){
        if (boards[board_index].update_board(x,y,mark)) {
            if (boards[board_index].is_win()) {
                is_free[board_index]=false;
                int i = board_index / 3; // Row in ultimate board
                int j = board_index % 3;
                this->board[i][j]=mark;
                this->n_moves++;
            }
            else if (boards[board_index].is_draw()) {
                is_free[board_index]=false;
                int i = board_index / 3; // Row in ultimate board
                int j = board_index % 3;
                this->board[i][j]='-';
                this->n_moves++;
            }
            return true;
        }
    }
    return false;
}

// Display the board and the pieces on it
template <typename T>
void ultimate_Board<T>::display_board() {
    cout<<string(7,' ') <<"Ultimate board";
    for (int i = 0; i < this->rows; i++) {
        cout << "\n|";
        for (int j = 0; j < this->columns; j++) {
            cout << "(" << i << "," << j << ")";
            cout << setw(2) << this->board[i][j] << " |";
        }
        cout << "\n----------------------------";
    }
    cout << endl;

    // Print boards in a 3x3 grid
    for (int boardRow = 0; boardRow < 3; ++boardRow) { // Each row of boards
        for (int smallRow = 0; smallRow < 3; ++smallRow) { // Rows inside each board
            if (smallRow==0) {
                for (int smallColumn = 0; smallColumn < 3; ++smallColumn) {
                    cout<<string(12,' ')<<boardRow * 3 + smallColumn<<string(16,' ');
                }
            }
            else {
                for (int smallColumn = 0; smallColumn < 3; ++smallColumn) {
                    cout << "---------------------------- ";
                }
            }
            cout<<endl;
            for (int boardCol = 0; boardCol < 3; ++boardCol) { // Each board in a row
                int boardIndex = boardRow * 3 + boardCol; // Map to 1D vector
                char** board = boards[boardIndex].get_board(); // Get the board

                // Print one row of the current board
                cout << "|";
                for (int smallCol = 0; smallCol < 3; ++smallCol) {
                    cout << "(" << smallRow << "," << smallCol << ")";
                    cout << setw(2) << board[smallRow][smallCol] << " |";
                    if (smallCol==2)cout<<' ';
                }
            }
            cout << endl; // Move to the next row of small boards
        }
        // Print separators between rows of boards
        for (int col = 0; col < 3; ++col) {
            cout << "---------------------------- ";
        }
        cout << endl;
    }
}

// Returns true if there is any winner
template <typename T>
bool ultimate_Board<T>::is_win() {
    // Check rows and columns
    for (int i = 0; i < this->rows; i++) {
        if ((this->board[i][0] == this->board[i][1] && this->board[i][1] == this->board[i][2] && this->board[i][0] != 0) ||
            (this->board[0][i] == this->board[1][i] && this->board[1][i] == this->board[2][i] && this->board[0][i] != 0)) {
            return true;
        }
    }

    // Check diagonals
    if ((this->board[0][0] == this->board[1][1] && this->board[1][1] == this->board[2][2] && this->board[0][0] != 0) ||
        (this->board[0][2] == this->board[1][1] && this->board[1][1] == this->board[2][0] && this->board[0][2] != 0)) {
        return true;
    }

    return false;
}

// Return true if 9 moves are done and no winner
template <typename T>
bool ultimate_Board<T>::is_draw() {
    return (this->n_moves == 9 && !is_win());
}

template <typename T>
bool ultimate_Board<T>::game_is_over() {
    return is_win() || is_draw();
}

//--------------------------------------

// Constructor for ultimate_Player
template <typename T>
ultimate_Player<T>::ultimate_Player(string name, T symbol) : Player<T>(name, symbol) {}

template <typename T>
void ultimate_Player<T>::getmove(int& x, int& y) {
    cout << "\nPlease enter the board number (0 to 8): ";
    cin>>board_index;
    cout << "\nPlease enter your move x and y (0 to 2) separated by spaces: ";
    cin >> x >> y;
}

// Constructor for ultimate_Random_Player
template <typename T>
ultimate_Random_Player<T>::ultimate_Random_Player(T symbol) : RandomPlayer<T>(symbol) {
    this->dimension = 3;
    this->name = "Random Computer Player";
    srand(static_cast<unsigned int>(time(0)));  // Seed the random number generator
}

template <typename T>
void ultimate_Random_Player<T>::getmove(int& x, int& y) {
    x = rand() % this->dimension;  // Random number between 0 and 2
    y = rand() % this->dimension;
    board_index=rand()%9;
}






#endif //ULTIMATE_H
