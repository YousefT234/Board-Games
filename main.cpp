#include <bits/stdc++.h>
#include "BoardGame_Classes.h"
#include "5_5_XO.h"
#include "four_in_a_row.h"
#include "numerical_tic_tac_toe.h"
#include "SUS.H"
#include "Ultimate.h"
#include "misere.h"
#include "pyramidal.h"
#include "word.h"
using namespace std;
void numerical() {
    long long choice;
    Player<long long>* players[2];
    numerical_Board<long long>* B = new numerical_Board<long long>();
    string playerXName, player2Name;

    cout << "Welcome to numerical tic tac toe game. :)\n";

    cout << "Enter Player 1 name: ";
    cin >> playerXName;
    cout << "Choose Player 1 type:\n";
    cout << "1. Human\n";
    cout << "2. Random Computer\n";
    cin >> choice;

    switch(choice) {
        case 1:
            players[0] = new numerical_Player<long long>(playerXName, 0);
        break;
        case 2:
            players[0] = new numerical_Random_Player<long long>(0);
        break;
        default:
            cout << "Invalid choice for Player 1. Exiting the game.\n";
        return;
    }

    cout << "Enter Player 2 name: ";
    cin >> player2Name;
    cout << "Choose Player 2 type:\n";
    cout << "1. Human\n";
    cout << "2. Random Computer\n";
    cin >> choice;

    switch(choice) {
        case 1:
            players[1] = new numerical_Player<long long>(player2Name, 0);
        break;
        case 2:
            players[1] = new numerical_Random_Player<long long>(0);
        break;
        default:
            cout << "Invalid choice for Player 2. Exiting the game.\n";
        return;
    }

    GameManager<long long> numerical_game(B, players);
    numerical_game.run();

    delete B;
    for (long long i = 0; i < 2; ++i) {
        delete players[i];
    }
}
void four(){
    long long choice;
    Player<char>* players[2];
    four_in_a_row_Board<char>* B = new four_in_a_row_Board<char>();
    string playerXName, player2Name;

    cout << "Welcome to Four in a row game. :)\n";

    cout << "Enter Player 1 name: ";
    cin >> playerXName;
    cout << "Choose Player 1 type:\n";
    cout << "1. Human\n";
    cout << "2. Random Computer\n";
    cin >> choice;

    switch(choice) {
        case 1:
            players[0] = new four_in_a_row_Player<char>(playerXName, 'X');
        break;
        case 2:
            players[0] = new four_in_a_row_Random_Player<char>('X');
        break;
        default:
            cout << "Invalid choice for Player 1. Exiting the game.\n";
        return;
    }

    cout << "Enter Player 2 name: ";
    cin >> player2Name;
    cout << "Choose Player 2 type:\n";
    cout << "1. Human\n";
    cout << "2. Random Computer\n";
    cin >> choice;

    switch(choice) {
        case 1:
            players[1] = new four_in_a_row_Player<char>(player2Name, 'O');
        break;
        case 2:
            players[1] = new four_in_a_row_Random_Player<char>('O');
        break;
        default:
            cout << "Invalid choice for Player 2. Exiting the game.\n";
        return;
    }

    GameManager<char> four_in_a_row_game(B, players);
    four_in_a_row_game.run();

    delete B;
    for (long long i = 0; i < 2; ++i) {
        delete players[i];
    }
}
void sus(){
    long long choice;
    bool SUS=false;
    Player<char>* players[2];
    SUS_Board<char>* B = new SUS_Board<char>();
    string playerXName, player2Name;

    cout << "Welcome to SUS game. :)\n";

    cout << "Enter Player 1 name: ";
    cin >> playerXName;
    cout << "Choose Player 1 type:\n";
    cout << "1. Human\n";
    cout << "2. Random Computer\n";
    cin >> choice;

    switch(choice) {
        case 1:
            cout << "Choose Player 1 character :\n";
            cout << "1. S\n";
            cout << "2. U\n";
            cin >> choice;
            switch(choice) {
                case 1:
                    players[0] = new SUS_Player<char>(playerXName, 'S');
                    SUS = true;
                break;
                case 2:
                    players[0] = new SUS_Player<char>(playerXName,'U');
                break;
                default:
                    cout << "Invalid choice for Player 1. Exiting the game.\n";
                return;
            }
        break;
        case 2:
            cout << "Choose Player 1 character :\n";
            cout << "1. S\n";
            cout << "2. U\n";
            cin >> choice;
            switch(choice) {
                case 1:
                    players[0] = new SUS_Random_Player<char>( 'S');
                    SUS = true;
                break;
                case 2:
                    players[0] = new SUS_Random_Player<char>( 'U');
                break;
                default:
                    cout << "Invalid choice for Player 1. Exiting the game.\n";
                return;
            }
        break;
        default:
            cout << "Invalid choice for Player 1. Exiting the game.\n";
        return;
    }

    cout << "Enter Player 2 name: ";
    cin >> player2Name;
    cout << "Choose Player 2 type:\n";
    cout << "1. Human\n";
    cout << "2. Random Computer\n";
    cin >> choice;

    switch(choice) {
        case 1:
            if (SUS) players[1] = new SUS_Player<char>(player2Name, 'U');
            else players[1] = new SUS_Player<char>(player2Name, 'S');
        break;
        case 2:
           if (SUS) players[1] = new SUS_Random_Player<char>('U');
            else players[1] = new SUS_Random_Player<char>('S');
        break;
        default:
            cout << "Invalid choice for Player 2. Exiting the game.\n";
        return;
    }

    GameManager<char> SUS_game(B, players);
    SUS_game.run();
    cout<<players[0]->getname()<<" has got: "<<B->sus_count[0]<<" SUS"<<endl;
    cout<<players[1]->getname()<<" has got: "<<B->sus_count[1]<<" SUS"<<endl;
    switch(B->who_wins()) {
        case 0:
            cout << " Draw\n";
        break;
        case 1:
            cout << players[0]->getname() << " wins\n";
        break;
        case 2:
            cout << players[1]->getname() << " wins\n";
        break;
    }
    delete B;
    for (long long i = 0; i < 2; ++i) {
        delete players[i];
    }
}
void ultimate() {
    long long choice;
    Player<char>* players[2];
    ultimate_Board<char>* B = new ultimate_Board<char>();
    string playerXName, player2Name;

    cout << "Welcome to Ultimate X-O Game. :)\n";

    // Set up player 1
    cout << "Enter Player X name: ";
    cin >> playerXName;
    cout << "Choose Player X type:\n";
    cout << "1. Human\n";
    cout << "2. Random Computer\n";
    cin >> choice;

    switch(choice) {
        case 1:
            players[0] = new ultimate_Player<char>(playerXName, 'X');
        break;
        case 2:
            players[0] = new ultimate_Random_Player<char>('X');
        break;

        default:
            cout << "Invalid choice for Player 1. Exiting the game.\n";
        return ;
    }

    // Set up player 2
    cout << "Enter Player 2 name: ";
    cin >> player2Name;
    cout << "Choose Player 2 type:\n";
    cout << "1. Human\n";
    cout << "2. Random Computer\n";
    cin >> choice;

    switch(choice) {
        case 1:
            players[1] = new ultimate_Player<char>(player2Name, 'O');
        break;
        case 2:
            players[1] = new ultimate_Random_Player<char>('O');
        break;
        default:
            cout << "Invalid choice for Player 2. Exiting the game.\n";
        return;
    }

    // Create the game manager and run the game
    GameManager<char> ultimate_game(B, players);
    ultimate_game.run();

    // Clean up
    delete B;
    for (long long i = 0; i < 2; ++i) {
        delete players[i];
    }

}
void five_X_O() {
    int choice;
    Player<char>* players[2];
    five_X_O_Board<char>* B = new five_X_O_Board<char>();
    string playerXName, player2Name;

    cout << "Welcome to 5x5 Tic Tac Toe Game. :)\n";

    // Set up player 1
    cout << "Enter Player X name: ";
    cin >> playerXName;
    cout << "Choose Player X type:\n";
    cout << "1. Human\n";
    cout << "2. Random Computer\n";
    cin >> choice;

    switch(choice) {
        case 1:
            players[0] = new five_X_O_Player<char>(playerXName, 'X');
        break;
        case 2:
            players[0] = new five_X_O_Random_Player<char>('X');
        break;
        default:
            cout << "Invalid choice for Player 1. Exiting the game.\n";
        return ;
    }

    // Set up player 2
    cout << "Enter Player 2 name: ";
    cin >> player2Name;
    cout << "Choose Player 2 type:\n";
    cout << "1. Human\n";
    cout << "2. Random Computer\n";
    cin >> choice;

    switch(choice) {
        case 1:
            players[1] = new five_X_O_Player<char>(player2Name, 'O');
        break;
        case 2:
            players[1] = new five_X_O_Random_Player<char>('O');
        break;
        default:
            cout << "Invalid choice for Player 2. Exiting the game.\n";
        return ;
    }

    // Create the game manager and run the game
    GameManager<char> five_X_O_game(B, players);
    five_X_O_game.run();

    switch(B->checkwinner()) {
        case 0:
            cout << " Draw\n";
        break;
        case 1:
            cout << players[0]->getname() << " wins\n";
        break;
        case 2:
            cout << players[1]->getname() << " wins\n";
        break;
    }
    cout<<players[0]->getname()<<" has got: "<<B->count[0]<<" three-in-a-rows"<<endl;
    cout<<players[1]->getname()<<" has got: "<<B->count[1]<<" three-in-a-rows"<<endl;
    // Clean up
    delete B;
    for (int i = 0; i < 2; ++i) {
        delete players[i];
    }

}
void pyramidal() {
    PyramidalBoard board;
    pyramdialPlayer player1("Player 1", 'X');
    RandompyramdialPlayer player2('O');

    player1.setBoard(&board);
    player2.setBoard(&board);

    Player<char>* players[2] = { &player1, &player2 };
    GameManager<char> gameManager(&board, players);

    gameManager.run();
}
void word() {
    string path;
    cout << "Enter the dictionary file name: ";
    cin >> path;

    // Create the WordBoard object with the given dictionary file
    WordBoard board(path);

    // Create the players
    WordPlayer player1("Player 1", 'A');
    WordRandomPlayer player2('B');

    // Set the board for each player
    player1.setBoard(&board);
    player2.setBoard(&board);

    // Start the game by calling the play method
    board.play(&player1, &player2);
}
void misere (){
    int choice;
    Player<char>* players[2];
    misere_Board<char>* B = new misere_Board<char>();
    string playerXName, player2Name;

    cout << "Welcome to Misere Tic Tac Toe Game. :)\n";

    // Set up player 1
    cout << "Enter Player X name: ";
    cin >> playerXName;
    cout << "Choose Player 2 type:\n";
    cout << "1. Human\n";
    cout << "2. Random Computer\n";
    cin >> choice;

    switch(choice) {
        case 1:
            cout << "Enter Player 2 name: ";
            cin >> player2Name;
            players[0] = new misere_Player<char>(player2Name, 'X');
            players[1] = new misere_Player<char>(playerXName, 'O');
        break;
        case 2:
            players[0] = new misere_Player<char>("Random Computer Player", 'X');
            players[1] = new misere_Random_Player<char>(playerXName,'O');
        break;
        default:
            cout << "Invalid choice for Player 2. Exiting the game.\n";
        return ;
    }

    // Create the game manager and run the game
    GameManager<char> misere_game(B, players);
    misere_game.run();

    // Clean up
    delete B;
    for (int i = 0; i < 2; ++i) {
        delete players[i];
    }
}
int main() {
// #ifndef ONLINE_JUDGE
//     freopen("input.txt", "r", stdin);
//     freopen("output.txt", "w", stdout);
// #endif
    cout<<"Welcome to our combined board games program!\n";
    while (true) {
        cout<<"1-Pyramid Tic-Tac-Toe\n2-Four-in-a-row\n3-5 x 5 Tic Tac Toe\n4-Word Tic Tac Toe\n5-Numerical Tic Tac Toe";
        cout<<"\n6-Misere Tic-Tac-Toe\n7-Ultimate Tic Tac Toe\n8-SUS\n9-Exit\n";
        int choice;
        bool check = false;
        while (!check) {
            check = true;
            cout<<"Please choose from 1 to 9: ";
            cin>>choice;
            switch(choice) {
                case 1:
                    pyramidal();
                    break;
                case 2:
                    four();
                break;
                case 3:
                    five_X_O();
                    break;
                case 4:
                    word();
                    break;
                case 5:
                    numerical();
                break;
                case 6:
                    misere();
                    break;
                case 7:
                    ultimate();
                break;
                case 8:
                    sus();
                break;
                case 9:
                    cout<<"Exiting the game.\n";
                    return 0;
                default:
                    check = false;
                cout << "Invalid choice\n";
            }
        }
    }

}

