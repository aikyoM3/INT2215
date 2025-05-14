#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <conio.h>
#include <iomanip>
#include <string>
#include "SFML/include/SFML/Graphics.hpp"

using namespace std;

vector<vector<int>> createBoard()
{
    return vector<vector<int>>(4, vector<int>(4, 0));
}

// Comment out unused code for the text-based UI
/*
void displayBoard(const vector<vector<int>>& board)
{
    system("cls"); // Clear screen
    cout << "\n2048 Game\n\n";
    cout << "+------+------+------+------+\n";
    for (const auto& row : board)
    {
        for (int val : row)
        {
            if (val == 0)
                cout << "|      ";
            else
                cout << "| " << setw(4) << val << " ";
        }
        cout << "|\n+------+------+------+------+\n";
    }
}
*/

void addRandomTile(vector<vector<int>> &board)
{
    vector<pair<int, int>> emptyTiles;
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            if (board[i][j] == 0)
                emptyTiles.push_back({i, j});

    if (!emptyTiles.empty())
    {
        int idx = rand() % emptyTiles.size();
        board[emptyTiles[idx].first][emptyTiles[idx].second] = (rand() % 10 < 9) ? 2 : 4;
    }
}

// Rename processLine to combineTiles
vector<int> combineTiles(vector<int> line)
{
    vector<int> newLine(4, 0);
    int index = 0;
    for (int i = 0; i < 4; i++)
    {
        if (line[i] == 0)
            continue;
        if (index > 0 && newLine[index - 1] == line[i])
        {
            newLine[index - 1] *= 2;
        }
        else
        {
            newLine[index++] = line[i];
        }
    }
    return newLine;
}

void moveBoard(vector<vector<int>> &board, char move)
{
    vector<vector<int>> tempBoard = board;
    bool moved = false;

    if (move == 'W' || move == 'w')
    {
        for (int col = 0; col < 4; col++)
        {
            vector<int> line(4);
            for (int row = 0; row < 4; row++)
                line[row] = board[row][col];
            vector<int> newLine = combineTiles(line);
            for (int row = 0; row < 4; row++)
            {
                if (board[row][col] != newLine[row])
                {
                    board[row][col] = newLine[row];
                    moved = true;
                }
            }
        }
    }
    else if (move == 'S' || move == 's')
    {
        for (int col = 0; col < 4; col++)
        {
            vector<int> line(4);
            for (int row = 0; row < 4; row++)
                line[row] = board[3 - row][col];
            vector<int> newLine = combineTiles(line);
            for (int row = 0; row < 4; row++)
            {
                if (board[row][col] != newLine[3 - row])
                {
                    board[row][col] = newLine[3 - row];
                    moved = true;
                }
            }
        }
    }
    else if (move == 'A' || move == 'a')
    {
        for (int row = 0; row < 4; row++)
        {
            vector<int> newLine = combineTiles(board[row]);
            if (board[row] != newLine)
            {
                board[row] = newLine;
                moved = true;
            }
        }
    }
    else if (move == 'D' || move == 'd')
    {
        for (int row = 0; row < 4; row++)
        {
            vector<int> line(4);
            for (int col = 0; col < 4; col++)
                line[col] = board[row][3 - col];
            vector<int> newLine = combineTiles(line);
            for (int col = 0; col < 4; col++)
            {
                if (board[row][col] != newLine[3 - col])
                {
                    board[row][col] = newLine[3 - col];
                    moved = true;
                }
            }
        }
    }

    if (moved)
        addRandomTile(board);
}

bool isGameOver(const vector<vector<int>> &board)
{
    // Check for empty cells first
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            if (board[i][j] == 0)
                return false;
        }
    }

    // Check for possible merges
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            int current = board[i][j];
            // Check right neighbor
            if (j < 3 && current == board[i][j + 1])
                return false;
            // Check bottom neighbor
            if (i < 3 && current == board[i + 1][j])
                return false;
        }
    }
    return true;
}

void startGame()
{
    vector<vector<int>> board = createBoard();
    addRandomTile(board);
    addRandomTile(board);

    while (true)
    {
        // Comment out unused code for the text-based UI
        /*
        displayBoard(board);
        */
        if (isGameOver(board))
        {
            cout << "\nGame Over!\n";
            break;
        }
        char move = _getch();
        if (move == 27)
            break;
        moveBoard(board, move);
    }
}

// Constants for the graphical interface
const int WINDOW_SIZE = 600;
const int GRID_SIZE = 4;
const int CELL_SIZE = WINDOW_SIZE / GRID_SIZE;
const int PADDING = 10;

// Color mapping for different tile values
sf::Color getTileColor(int value)
{
    switch (value)
    {
    case 0:
        return sf::Color(205, 193, 180); // Empty tile
    case 2:
        return sf::Color(238, 228, 218);
    case 4:
        return sf::Color(237, 224, 200);
    case 8:
        return sf::Color(242, 177, 121);
    case 16:
        return sf::Color(245, 149, 99);
    case 32:
        return sf::Color(246, 124, 95);
    case 64:
        return sf::Color(246, 94, 59);
    case 128:
        return sf::Color(237, 207, 114);
    case 256:
        return sf::Color(237, 204, 97);
    case 512:
        return sf::Color(237, 200, 80);
    case 1024:
        return sf::Color(237, 197, 63);
    case 2048:
        return sf::Color(237, 194, 46);
    default:
        return sf::Color(60, 58, 50);
    }
}

// Convert game move to SFML key
char getMoveFromKey(sf::Keyboard::Key key)
{
    switch (key)
    {
    case sf::Keyboard::Key::W:
        return 'W';
    case sf::Keyboard::Key::S:
        return 'S';
    case sf::Keyboard::Key::A:
        return 'A';
    case sf::Keyboard::Key::D:
        return 'D';
    default:
        return 0;
    }
}

// Add a global font variable to load the font once
sf::Font globalFont;
bool globalFontLoaded = false;

// Draw the game board using SFML
void drawBoard(sf::RenderWindow &window, const vector<vector<int>> &board)
{
    // Draw background
    sf::RectangleShape background(sf::Vector2f(static_cast<float>(WINDOW_SIZE), static_cast<float>(WINDOW_SIZE)));
    background.setFillColor(sf::Color(187, 173, 160));
    window.draw(background);

    // Draw tiles
    for (int i = 0; i < GRID_SIZE; i++)
    {
        for (int j = 0; j < GRID_SIZE; j++)
        {
            int value = board[i][j];

            // Create tile rectangle
            sf::RectangleShape tile(sf::Vector2f(
                static_cast<float>(CELL_SIZE - PADDING * 2),
                static_cast<float>(CELL_SIZE - PADDING * 2)));
            tile.setPosition(
                sf::Vector2f(
                    static_cast<float>(j * CELL_SIZE + PADDING),
                    static_cast<float>(i * CELL_SIZE + PADDING)));
            tile.setFillColor(getTileColor(value));
            window.draw(tile);

            // Draw number if tile is not empty
            if (value != 0)
            {
                if (!globalFontLoaded)
                {
                    globalFontLoaded = globalFont.openFromFile("arial.ttf");
                }
                if (globalFontLoaded)
                {
                    sf::Text text(globalFont);
                    text.setString(to_string(value));
                    text.setCharacterSize(static_cast<unsigned int>(CELL_SIZE / 3));
                    text.setFillColor(value <= 4 ? sf::Color(119, 110, 101) : sf::Color(249, 246, 242));

                    // Center text in tile
                    sf::FloatRect textBounds = text.getLocalBounds();
                    text.setPosition(
                        sf::Vector2f(
                            static_cast<float>(j * CELL_SIZE + (CELL_SIZE - textBounds.size.x) / 2),
                            static_cast<float>(i * CELL_SIZE + (CELL_SIZE - textBounds.size.y) / 2)));
                    window.draw(text);
                }
            }
        }
    }
}

int main()
{
    // Initialize random seed
    srand(static_cast<unsigned int>(time(nullptr)));

    // Load the font once
    if (!globalFontLoaded)
    {
        globalFontLoaded = globalFont.openFromFile("arial.ttf");
    }

    // Create SFML window
    sf::RenderWindow window(sf::VideoMode({WINDOW_SIZE, WINDOW_SIZE}), "2048");
    window.setFramerateLimit(60);

    // Initialize game board
    vector<vector<int>> board = createBoard();
    addRandomTile(board);
    addRandomTile(board);

    // Game loop
    while (window.isOpen())
    {
        // Process all events in the queue
        while (auto event = window.pollEvent())
        {
            event->visit([&](const auto &e)
                         {
                using T = std::decay_t<decltype(e)>;
                if constexpr (std::is_same_v<T, sf::Event::Closed>)
                {
                    window.close();
                }
                else if constexpr (std::is_same_v<T, sf::Event::KeyPressed>)
                {
                    char move = getMoveFromKey(e.code);
                    if (move)
                    {
                        moveBoard(board, move);
                    }
                } });
        }

        // Clear window
        window.clear();

        // Draw game board
        drawBoard(window, board);

        // Display everything
        window.display();

        // Check for game over
        if (isGameOver(board))
        {
            // Display game over message
            if (globalFontLoaded)
            {
                sf::Text gameOverText(globalFont);
                gameOverText.setString("Game Over!");
                gameOverText.setCharacterSize(50);
                gameOverText.setFillColor(sf::Color::Red);

                sf::FloatRect textBounds = gameOverText.getLocalBounds();
                gameOverText.setPosition(
                    sf::Vector2f(
                        static_cast<float>((WINDOW_SIZE - textBounds.size.x) / 2),
                        static_cast<float>((WINDOW_SIZE - textBounds.size.y) / 2)));

                window.draw(gameOverText);
                window.display();

                // Wait for a moment before closing
                sf::sleep(sf::seconds(3));
                window.close();
            }
        }
    }

    return 0;
}

// Add TODO comments
// TODO: Optimize the game logic further
// TODO: Add more features to the game