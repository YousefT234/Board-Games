#ifndef WORD_H
#define WORD_H
#include "BoardGame_Classes.h"
#include <bits/stdc++.h>
using namespace std;

// Load dictionary from file
inline unordered_set<string> load_dictionary(const string& filename) {
    unordered_set<string> dictionary;
    ifstream file(filename);

    if (!file.is_open()) {
        cerr << "Error opening file: " << filename << endl;
        return dictionary;
    }

    string word;
    while (file >> word) {
        // Remove leading and trailing spaces
        size_t start = word.find_first_not_of(" \t\n\r");
        size_t end = word.find_last_not_of(" \t\n\r");

        if (start != string::npos && end != string::npos) {
            word = word.substr(start, end - start + 1);
        }

        dictionary.insert(word);
    }




    return dictionary;
}

// Custom Board class for Word Tic-Tac-Toe
class WordBoard : public Board<char> {
private:
    unordered_set<string> dictionary;

public:
    WordBoard(const string& dictionary_file) {
        rows = 3;
        columns = 3;
        n_moves = 0;
        dictionary = load_dictionary(dictionary_file);

        board = new char*[rows];
        for (int i = 0; i < rows; ++i) {
            board[i] = new char[columns];
            for (int j = 0; j < columns; ++j) {
                board[i][j] = ' ';
            }
        }
    }
    void play(Player<char>* player1, Player<char>* player2) {
        int currentPlayer = 0;  // Start with player 1
        display_board();  // Call the display_board method to show the board

        while (!game_is_over()) {
            int x, y;
            Player<char>* current = (currentPlayer == 0) ? player1 : player2;
            current->getmove(x, y);
            char symbol = current->getsymbol();

            // Ensure valid move
            while (!update_board(x, y, symbol)) {
                cout << "Invalid move. Try again.\n";
                current->getmove(x, y);
            }

            display_board();  // Display the updated board after the move

            // Check for winner
            if (is_win()) {
                cout << current->getname() << " wins!" << endl;
                break;
            }

            // Check for draw
            if (is_draw()) {
                cout << "It's a draw!" << endl;
                break;
            }

            // Switch player turn
            currentPlayer = (currentPlayer + 1) % 2;
        }
    }
    ~WordBoard() {
        for (int i = 0; i < rows; ++i) {
            delete[] board[i];
        }
        delete[] board;
    }

    bool update_board(int x, int y, char symbol) override {
        if (x >= 0 && x < rows && y >= 0 && y < columns && board[x][y] == ' ') {
            board[x][y] = symbol;
            n_moves++;
            return true;
        }
        return false;
    }

    void display_board() override {
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < columns; ++j) {
                cout << (board[i][j] == ' ' ? '.' : board[i][j]) << " ";
            }
            cout << endl;
        }
    }

    bool is_word(const string& str) {
        return dictionary.find(str) != dictionary.end();
    }

    bool check_word(int x1, int y1, int x2, int y2, int x3, int y3) {
        if (board[x1][y1] == ' ' || board[x2][y2] == ' ' || board[x3][y3] == ' ') {
            return false; // Skip empty cells
        }
        string word;
        word += board[x1][y1];
        word += board[x2][y2];
        word += board[x3][y3];

        cout << "Checking word: " << word << endl; // Debugging line

        return is_word(word); // Check if the word is in the dictionary
    }



    bool is_win() override {
        // Check rows
        for (int i = 0; i < 3; ++i) {
            if (check_word(i, 0, i, 1, i, 2)) return true;
        }

        // Check columns
        for (int j = 0; j < 3; ++j) {
            if (check_word(0, j, 1, j, 2, j)) return true;
        }

        // Check diagonals
        if (check_word(0, 0, 1, 1, 2, 2)) return true;
        if (check_word(0, 2, 1, 1, 2, 0)) return true;

        return false;
    }



    bool is_draw() override {
        return n_moves == rows * columns && !is_win();
    }

    bool game_is_over() override {
        return is_win() || is_draw();
    }
};

// Custom Player class for Word Tic-Tac-Toe
class WordPlayer : public Player<char> {
public:
    WordPlayer(string name, char symbol) : Player<char>(name, symbol) {}

    void getmove(int& x, int& y) override {
        char letter;
        cout << name << ", enter your move (row column letter): ";
        cin >> x >> y >> letter;
        letter = toupper(letter); // Ensure uppercase for consistency
        while (x < 0 || x >= 3 || y < 0 || y >= 3 || !isalpha(letter)) {
            cout << "Invalid input. Enter row, column, and a valid letter: ";
            cin >> x >> y >> letter;
            letter = toupper(letter);
        }
        symbol = letter; // Assign the valid letter to the player's symbol
    }

};

// Random computer player for Word Tic-Tac-Toe
class WordRandomPlayer : public RandomPlayer<char> {
public:
    WordRandomPlayer(char symbol) : RandomPlayer<char>(symbol) {
        srand(time(0));
    }

    void getmove(int& x, int& y) override {
        x = rand() % 3;
        y = rand() % 3;
        symbol = 'A' + rand() % 26; // Generate a random uppercase letter
        cout << "Computer placed " << symbol << " at position (" << x << ", " << y << ")\n";
    }

};


#endif //WORD_H
