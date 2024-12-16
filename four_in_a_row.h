#ifndef four_in_a_row_H
#define four_in_a_row_H

#include "BoardGame_Classes.h"
#include <bits/stdc++.h>

using namespace std;

vector<int>counter;

template <typename T>
class four_in_a_row_Board:public Board<T> {
private:
    int lastx;
    int lasty;
    T last_symbol;
public:
    four_in_a_row_Board ();
    bool update_board (int x , int y , T symbol);
    void display_board () ;
    bool is_win() ;
    bool is_draw();
    bool game_is_over();
    ~four_in_a_row_Board();
};

template <typename T>
class four_in_a_row_Player : public Player<T> {
public:
    four_in_a_row_Player (string name, T symbol);
    void getmove(int& x, int& y) ;

};

template <typename T>
class four_in_a_row_Random_Player : public RandomPlayer<T>{
public:
    four_in_a_row_Random_Player (T symbol);
    void getmove(int &x, int &y) ;
};


template <typename T>
four_in_a_row_Board<T>::four_in_a_row_Board() {
    this->rows =6;
    this->columns = 7;
    this->board = new char*[this->rows];
    for (int i = 0; i < this->columns; i++) {
        counter.push_back(0);
    }
    for (int i = 0; i < this->rows; i++) {
        this->board[i] = new char[this->columns];
        for (int j = 0; j < this->columns; j++) {
            this->board[i][j] = 0;
        }
    }
    this->n_moves = 0;
}
template <typename T>
four_in_a_row_Board<T>::~four_in_a_row_Board() {
    counter.clear();
    // Delete the dynamically allocated 2D board
    for (int i = 0; i < this->rows; i++) {
        delete[] this->board[i];  // Delete each row
    }
    delete[] this->board;  // Delete the main array

}

template <typename T>
bool four_in_a_row_Board<T>::update_board(int x, int y, T mark) {
    if (!(x < 0 || x >= this->rows || y < 0 || y >= this->columns) && (this->board[x][y] == 0)) {
        this->n_moves++;
        this->board[x][y] = toupper(mark);
        counter[y]++;
        lastx=x;
        lasty=y;
        last_symbol = mark;
        return true;
    }
    return false;
}

template <typename T>
void four_in_a_row_Board<T>::display_board() {
    for (int j = 0; j < this->columns; j++) {
        cout << setw(4) << j;
    }
    for (int i = 0; i < this->rows; i++) {
        cout << "\n| ";
        for (int j = 0; j < this->columns; j++) {
            cout << setw(2) << this->board[i][j] << " |";
        }
        cout << '\n'<<string(30,'-');
    }
    cout << endl;
}

template <typename T>
bool four_in_a_row_Board<T>::is_win() {
    if (this->n_moves == 0) return false;

    auto count_in_direction = [&](int start_x, int start_y, int dx, int dy) -> int {
        int count = 0;
        int x = start_x, y = start_y;

        while (x >= 0 && x < this->rows && y >= 0 && y < this->columns &&
               this->board[x][y] == last_symbol) {
            count++;
            x += dx;
            y += dy;
               }

        return count;
    };

    // Directions to check
    int directions[4][2] = {
        {0, 1},   // Horizontal right
        {1, 0},   // Vertical down
        {1, 1},   // Diagonal down-right
        {1, -1},  // Diagonal down-left
    };

    for (auto& dir : directions) {
        int dx = dir[0], dy = dir[1];

        // Count in the positive and negative direction
        int count = count_in_direction(lastx, lasty, dx, dy) +
                    count_in_direction(lastx, lasty, -dx, -dy) - 1;

        if (count >= 4) {
            return true;
        }
    }

    return false;
}





template <typename T>
bool four_in_a_row_Board<T>::is_draw() {
    return (this->n_moves == 42 && !is_win());
}

template <typename T>
bool four_in_a_row_Board<T>::game_is_over() {
    return is_win() || is_draw();
}


template <typename T>
four_in_a_row_Player<T>::four_in_a_row_Player(string name, T symbol) : Player<T>(name, symbol) {}

template <typename T>
void four_in_a_row_Player<T>::getmove(int& x, int& y) {
    cout << "\nPlease choose a column from 0 to 6: ";
    cin >> y;
    x=5-counter[y];
}

template <typename T>
four_in_a_row_Random_Player<T>::four_in_a_row_Random_Player(T symbol) : RandomPlayer<T>(symbol) {
    this->dimension = 7;
    this->name = "Random Computer Player";
    srand(static_cast<unsigned int>(time(0)));
}

template <typename T>
void four_in_a_row_Random_Player<T>::getmove(int& x, int& y) {
    y = rand() % this->dimension;
    x=5-counter[y];
}

#endif //four_in_a_row_H
