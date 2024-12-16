
#ifndef PYRAMIDAL_H
#define PYRAMIDAL_H
#include <bits/stdc++.h>

#include "BoardGame_Classes.h"

using namespace std;

class PyramidalBoard : public Board<char> {
public:
    PyramidalBoard() {
        rows = 3; // Pyramid with 3 levels
        columns = 5; // Maximum width at the base
        board = new char*[rows];

        // Initialize board with spaces
        for (int i = 0; i < rows; ++i) {
            board[i] = new char[columns];
            for (int j = 0; j < columns; ++j) {
                board[i][j] = ' '; // Empty spots
            }
        }
    }

    ~PyramidalBoard() {
        for (int i = 0; i < rows; ++i) {
            delete[] board[i];
        }
        delete[] board;
    }

    // Implement the pure virtual function from Board
    bool update_board(int x, int y, char symbol) override {
        if (x < 0 || x >= rows || y < 0 || y >= columns) {
            return false;
        }

        if (!valid_position(x, y)) {
            cout << "Invalid move: Position not part of the pyramid.\n";
            return false;
        }

        if (board[x][y] != ' ') {
            return false;
        }

        board[x][y] = symbol;
        n_moves++;
        return true;
    }

    void display_board() override {
        for (int i = 0; i < rows; ++i) {
            // Add spaces to align the pyramid
            for (int j = 0; j < (rows - i -1); ++j) {
                cout << " ";
            }

            // Print the row
            for (int j = 0; j < columns; ++j) {
                if (valid_position(i, j)) {
                    if(board[i][j]!=' ')
                        cout << "|" << board[i][j];
                    else {
                        cout << "|_";
                    }
                } else if(j < columns - 2) {
                    cout << " ";
                }
            }
            cout << "|\n";
        }
        cout << endl;
    }

    bool is_win() override {
        // Check for horizontal, vertical, and diagonal wins
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < columns; ++j) {
                if (board[i][j] != ' ' && valid_position(i, j)) {
                    if (check_win(i, j)) return true;
                }
            }
        }
        return false;
    }

    bool is_draw() override {
        return n_moves == 9 && !is_win();
    }

    bool game_is_over() override {
        return is_win() || is_draw();
    }

    bool valid_position(int x, int y) {
        // Pyramid shape validation
        if (x == 0 && y == 2) return true; // Top
        if (x == 1 && (y >= 1 && y <= 3)) return true; // Second row
        if (x == 2 && (y >= 0 && y <= 4)) return true; // Base row
        return false;
    }

    char get_board_cell(int x, int y) {
        if (x >= 0 && x < rows && y >= 0 && y < columns) {
            return board[x][y];
        }
        return ' '; // If out of bounds, return empty
    }

private:
    bool check_win(int x, int y) {
        char symbol = board[x][y];

        // Check horizontal
        if (y + 2 < columns && valid_position(x, y + 1) && valid_position(x, y + 2) && board[x][y + 1] == symbol && board[x][y + 2] == symbol) return true;

        // Check vertical
        if (x + 2 < rows && valid_position(x + 1, y) && valid_position(x + 2, y) && board[x + 1][y] == symbol && board[x + 2][y] == symbol) return true;

        // Check diagonal (down-right and down-left)
        if (x + 2 < rows && y + 2 < columns && valid_position(x + 1, y + 1) && valid_position(x + 2, y + 2) && board[x + 1][y + 1] == symbol && board[x + 2][y + 2] == symbol) return true;

        if (x + 2 < rows && y - 2 >= 0 && valid_position(x + 1, y - 1) && valid_position(x + 2, y - 2) && board[x + 1][y - 1] == symbol && board[x + 2][y - 2] == symbol) return true;

        return false;
    }
};

class pyramdialPlayer : public Player<char> {
public:
    pyramdialPlayer(string n, char symbol) : Player<char>(n, symbol) {}

    void getmove(int& x, int& y) override {
        while (true) {
            cout << name << "'s turn. Enter row and column (0-based index): ";
            cin >> x >> y;

            if (cin.fail()) { // Check for invalid input
                cin.clear(); // Clear error flag
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
                cout << "Invalid input. Please enter integers for row and column.\n";
                continue;
            }

            PyramidalBoard* pyramidalBoard = dynamic_cast<PyramidalBoard*>(boardPtr);
            if (pyramidalBoard != nullptr) {
                // Check if position is valid and empty
                if (pyramidalBoard->valid_position(x, y) && pyramidalBoard->get_board_cell(x, y) == ' ') {
                    break;
                }
            }

            // If the move is invalid, prompt again
            cout << "Invalid move: Position already occupied or out of bounds.\n";
        }
    }
};

class RandompyramdialPlayer : public RandomPlayer<char> {
public:
    RandompyramdialPlayer(char symbol) : RandomPlayer<char>(symbol) {
        srand(time(nullptr));
    }

    void getmove(int& x, int& y) override {
        do {
            x = rand() % 3;
            y = rand() % 5;
        } while (!dynamic_cast<PyramidalBoard*>(boardPtr)->valid_position(x, y) || dynamic_cast<PyramidalBoard*>(boardPtr)->get_board_cell(x, y) != ' ');
    }
};

#endif //PYRAMIDAL_H
