<<<<<<< HEAD
﻿#include <iostream>
=======
#include <iostream>
>>>>>>> d2bd643a1f3e6a2dc8273c704c2cfc3af18c5120
#include <vector>
#include <cstdlib>
#include <ctime>
#include <conio.h>
#include <iomanip>
#include <string>

using namespace std;

vector<vector<int>> createBoard() {
    return vector<vector<int>>(4, vector<int>(4, 0));
}

void displayBoard(const vector<vector<int>>& board) {
    system("cls");  // Clear screen
    cout << "\n2048 Game\n\n";
    cout << "+------+------+------+------+\n";
    for (const auto& row : board) {
        for (int val : row) {
            if (val == 0) cout << "|      ";
            else cout << "| " << setw(4) << val << " ";
        }
        cout << "|\n+------+------+------+------+\n";
    }
}

void addRandomTile(vector<vector<int>>& board) {
    vector<pair<int, int>> emptyTiles;
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            if (board[i][j] == 0) emptyTiles.push_back({ i, j });

    if (!emptyTiles.empty()) {
        int idx = rand() % emptyTiles.size();
        board[emptyTiles[idx].first][emptyTiles[idx].second] = (rand() % 10 < 9) ? 2 : 4;
    }
}

vector<int> processLine(vector<int> line) {
    vector<int> newLine(4, 0);
    int index = 0;
    for (int i = 0; i < 4; i++) {
        if (line[i] == 0) continue;
        if (index > 0 && newLine[index - 1] == line[i]) {
            newLine[index - 1] *= 2;
        }
        else {
            newLine[index++] = line[i];
        }
    }
    return newLine;
}

void moveBoard(vector<vector<int>>& board, char move) {
    vector<vector<int>> tempBoard = board;

    if (move == 'W' || move == 'w') {
        for (int col = 0; col < 4; col++) {
            vector<int> line;
            for (int row = 0; row < 4; row++) line.push_back(board[row][col]);
            vector<int> newLine = processLine(line);
            for (int row = 0; row < 4; row++) board[row][col] = newLine[row];
        }
    }
    else if (move == 'S' || move == 's') {
        for (int col = 0; col < 4; col++) {
            vector<int> line;
            for (int row = 3; row >= 0; row--) line.push_back(board[row][col]);
            vector<int> newLine = processLine(line);
            for (int row = 3; row >= 0; row--) board[row][col] = newLine[3 - row];
        }
    }
    else if (move == 'A' || move == 'a') {
        for (int row = 0; row < 4; row++) {
            board[row] = processLine(board[row]);
        }
    }
    else if (move == 'D' || move == 'd') {
        for (int row = 0; row < 4; row++) {
            vector<int> line(board[row].rbegin(), board[row].rend());
            vector<int> newLine = processLine(line);
            for (int col = 0; col < 4; col++) board[row][col] = newLine[3 - col];
        }
    }

    if (board != tempBoard) addRandomTile(board);
}

bool isGameOver(const vector<vector<int>>& board) {
    for (char move : {'W', 'A', 'S', 'D'}) {
        vector<vector<int>> temp = board;
        moveBoard(temp, move);
        if (temp != board) return false;
    }
    return true;
}

void startGame() {
    vector<vector<int>> board = createBoard();
    addRandomTile(board);
    addRandomTile(board);

    while (true) {
        displayBoard(board);
        if (isGameOver(board)) {
            cout << "\nGame Over!\n";
            break;
        }
        char move = _getch();
        if (move == 27) break;
        moveBoard(board, move);
    }
}

int main() {
    srand(static_cast<unsigned int>(time(nullptr)));
    cout << "Welcome to 2048!\nUse W/A/S/D to move tiles. Press ESC to quit.\n";
    startGame();
    return 0;
}
