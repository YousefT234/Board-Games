
#include "BoardGame_Classes.h"

template <typename T>
class misere_Board : public Board<T>
{
  public:
	misere_Board();
	bool update_board(int x, int y, T symbol);
	void display_board();
	bool is_win();
	bool is_draw();
	bool game_is_over();
	~misere_Board();
};

template <typename T>
class misere_Player : public Player<T>
{
  public:
	misere_Player(string name, T symbol);
	void getmove(int &x, int &y);
};

template <typename T>
class misere_Random_Player : public Player<T>
{
protected:
	int dimension;
  public:
	misere_Random_Player(string name, T symbol);
	void getmove(int &x, int &y);
};

//--------------------------------------- IMPLEMENTATION

#include <iostream>
#include <iomanip>
#include <cctype> // for toupper()

using namespace std;

// Constructor for misere_Board
template <typename T>
misere_Board<T>::misere_Board()
{
	this->rows = this->columns = 3;
	this->board = new char *[this->rows];
	for (int i = 0; i < this->rows; i++)
	{
		this->board[i] = new char[this->columns];
		for (int j = 0; j < this->columns; j++)
		{
			this->board[i][j] = 0;
		}
	}
	this->n_moves = 0;
}

template <typename T>
misere_Board<T>::~misere_Board() {
	// Deallocate the dynamically allocated memory for the board
	for (int i = 0; i < this->rows; i++) {
		delete[] this->board[i]; // Delete each row
	}
	delete[] this->board; // Delete the array of row pointers
}

template <typename T>
bool misere_Board<T>::update_board(int x, int y, T mark)
{
	// Only update if move is valid
	if (!(x < 0 || x >= this->rows || y < 0 || y >= this->columns) && (this->board[x][y] == 0 || mark == 0))
	{
		if (mark == 0)
		{
			this->n_moves--;
			this->board[x][y] = 0;
		}
		else
		{
			this->n_moves++;
			this->board[x][y] = toupper(mark);
		}

		return true;
	}
	return false;
}

// Display the board and the pieces on it
template <typename T>
void misere_Board<T>::display_board()
{
	for (int i = 0; i < this->rows; i++)
	{
		cout << "\n| ";
		for (int j = 0; j < this->columns; j++)
		{
			cout << "(" << i << "," << j << ")";
			cout << setw(2) << this->board[i][j] << " |";
		}
		cout << "\n-----------------------------";
	}
	cout << endl;
}

// Returns true if there is any winner
template <typename T>
bool misere_Board<T>::is_win()
{

	// Check rows and columns
	for (int i = 0; i < this->rows; i++)
	{
		if ((this->board[i][0] == this->board[i][1] && this->board[i][1] == this->board[i][2] && this->board[i][0] != 0) ||
			(this->board[0][i] == this->board[1][i] && this->board[1][i] == this->board[2][i] && this->board[0][i] != 0))
		{
			return true;
		}
	}

	// Check diagonals
	if ((this->board[0][0] == this->board[1][1] && this->board[1][1] == this->board[2][2] && this->board[0][0] != 0) ||
		(this->board[0][2] == this->board[1][1] && this->board[1][1] == this->board[2][0] && this->board[0][2] != 0))
	{
		return true;
	}

	return false;
}

// Return true if 9 moves are done and no winner
template <typename T>
bool misere_Board<T>::is_draw()
{
	return (this->n_moves == 9 && !is_win());
}

template <typename T>
bool misere_Board<T>::game_is_over()
{
	return is_win() || is_draw();
}

//--------------------------------------

// Constructor for misere_Player
template <typename T>
misere_Player<T>::misere_Player(string name, T symbol) : Player<T>(name, symbol) {}

template <typename T>
void misere_Player<T>::getmove(int &x, int &y)
{
	cout << "\nPlease enter your move x and y (0 to 2) separated by spaces: ";
	cin >> x >> y;
}

// Constructor for misere_Random_Player
template <typename T>
misere_Random_Player<T>::misere_Random_Player(string name,T symbol) : Player<T>(name, symbol)
{
	this->dimension = 3;
	srand(static_cast<unsigned int>(time(0)));
}

template <typename T>
void misere_Random_Player<T>::getmove(int &x, int &y)
{
	x = rand() % this->dimension; // Random number between 0 and 2
	y = rand() % this->dimension;
}