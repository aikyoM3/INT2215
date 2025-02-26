// 2048.cpp : This file contains the 'main' function. Program execution begins and ends there.
#include <iostream>
#include <vector>

using namespace std;

// Create a new blank board
vector<vector<int>> createBoard() {
    vector<vector<int>> board(4, vector<int>(4, 0)); // Initialize a 4x4 board with zeros (blank tiles)
    return board;
}

// Display the board
void displayBoard(const vector<vector<int>>& board) {
    int size = board.size();
    for (int i = 0; i < size; ++i) {
        cout << "+---+---+---+---+" << endl;
        for (int j = 0; j < size; ++j) {
            if (board[i][j] == 0) {
                cout << "|   ";
            }
            else {
                cout << "| " << board[i][j] << " ";
            }
        }
        cout << "|" << endl;
    }
    cout << "+---+---+---+---+" << endl;
}

// Start a game loop
void startGame() {
    vector<vector<int>> board = createBoard();
    bool isOver = 0;
/*    while (isOver != 1) {
        displayBoard(board);
    }
*/
    displayBoard(board);
}







int main()
{
    startGame();
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
