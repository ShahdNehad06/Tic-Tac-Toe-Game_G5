#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>
#include <limits>
using namespace std;

/* ----Enum---- */
// Represents AI difficulty levels
enum Difficulty { EASY, HARD };

/* ---------- BOARD CLASS ---------- */
/* Responsibilities:
- Store the game grid
- Validate moves
- Update board state
- Check win and draw conditions */
class Board {
private:
    vector<vector<char>> grid;
    int size;

public:
    Board(int s = 3){
        // TODO: your implementation here
        size=s;
        grid = vector<vector<char>>(size, vector<char>(size,' '));
    }

    void display() const {
        // TODO: your implementation here
        int num =1;
        for (int i = 0; i < size; i++) {
            cout<<" ";
            for (int j = 0; j < size; j++) {
                if (grid[i][j]==' ') {
                    cout<<num;
                }
                else {
                    cout<<grid[i][j];
                }
                if (j<size-1) {
                    cout<<" | " ;
                }
                num++;
            }
            cout<<endl;
            if (i<size-1) {
                for (int k=0;k<size;k++) {
                    cout<<"----";
                    if (k<size-1) {
                        cout<<"+";
                    }
                }
                cout<<endl;
            }
        }
        cout<<endl;
    }

    bool isValidMove(int row, int col) const {
        // TODO: your implementation here
        if (row<0||row>=size||col<0||col>=size||grid[row][col]!=' ') {
            return false;
        }
        return true;
    }

    bool makeMove(int row, int col, char symbol) {
        // TODO: your implementation here
        if (isValidMove(row,col)) {
            grid[row][col] = symbol;
            return true;
        }
        return false;
    }

    bool checkWin(char symbol) const {
        // TODO: your implementation here
        int count=0;
        for (int i = 0; i < size; i++) {
            count=0;
            for (int j = 0; j < size; j++) {
                if (grid[i][j]==symbol) {
                    count++;
                }
            }
            if (count==size) {
                return true;
            }
        }
        for (int j=0; j<size; j++) {
            count =0;
            for (int i=0;i<size;i++) {
                if (grid[i][j]==symbol) {
                    count++;
                }
            }
            if (count==size) {
                return true;
            }
        }
        count =0;
        for (int i=0; i<size; i++) {
            if (grid[i][i]==symbol) {
                count++;
            }
        }
        if (count==size) {
            return true;
        }

        count=0;
        for (int i=0;i<size;i++) {
            if (grid[i][size-i-1]==symbol) {
                count++;
            }
        }
        if (count==size) {
            return true;
        }
        return false;
    }

    bool isFull() const {
        // TODO: your implementation here
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                if (grid[i][j]==' ') {
                    return false;
                }
            }
        }
        return true;
    }

    char getCell(int row, int col) const {
        // TODO: your implementation here
        return grid [row][col];
    }

    void reset() {
        // TODO: your implementation here
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                grid[i][j]= ' ';
            }
        }
    }

    int getSize() const {
        // TODO: your implementation here
        return size;
    }
};

/* ---------- PLAYER CLASS ---------- */
/* Responsibilities:
 - Represent a generic player
 - Store name and symbol
 - Provide interface for getting moves */
class Player {
protected:
    string name;
    char symbol;

public:
    Player(const string& n, char s) {
        // TODO: your implementation here
        this->name = n;
        this->symbol = s;
    }

    virtual void getMove(const Board& board, int& row, int& col) = 0;

    string getName() const {
        // TODO: your implementation here
        return name;
    }

    char getSymbol() const {
        // TODO: your implementation here
        return symbol;
    }

    void setName(const string& name) {
        // TODO: your implementation here
        this->name = name;
    }
};

/* ----------- HUMAN PLAYER ----------- */
/* Responsibilities:
- Handle user input from console */
class HumanPlayer : public Player {
public:
    HumanPlayer(const string& name, char symbol)
        : Player(name, symbol) {}

    void getMove(const Board& board, int& row, int& col) override {
        // TODO: your implementation here
        int n = board.getSize();
        int maxMove = n * n;
        int index;
        bool valid = false;

        while (!valid) {
            cout << name << " (" << symbol << "), enter move (1-" << maxMove << "): ";

            if (!(cin >> index)) {
                cout << "Invalid input. Please enter a number." << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                continue;
            }

            if (index < 1 || index > maxMove) {
                cout << "Out of bounds! Choose a number between 1 and " << maxMove << "." << endl;
                continue;
            }

            index--;
            row = index / n;
            col = index % n;

            if (board.isValidMove(row, col)) {
                valid = true;
            } else {
                cout << "Invalid move! Spot taken. Try again." << endl;
            }
        }
    }
};

/* ----------- AI PLAYER ----------- */
/* Responsibilities:
 - Generate moves automatically
 - Support Easy (random) and Hard (minimax) */
class AIPlayer : public Player {
private:
    Difficulty difficulty;

public:
    AIPlayer(const string& name, char symbol, Difficulty difficulty)
        : Player(name, symbol), difficulty(difficulty) {
    }

    void setDifficulty(Difficulty newDifficulty) {
        difficulty = newDifficulty;
    }

    int evaluateBoard(const Board& board) const {
        char aiSymbol = symbol;
        char opponentSymbol = (symbol == 'X') ? 'O' : 'X';

        if (board.checkWin(aiSymbol))
            return 10;

        if (board.checkWin(opponentSymbol))
            return -10;

        return 0;
    }

    int minimax(Board& board, bool isMax) const {
        int score = evaluateBoard(board);

        if (score == 10 || score == -10)
            return score;

        if (board.isFull())
            return 0;

        char aiSymbol = symbol;
        char opponentSymbol = (symbol == 'X') ? 'O' : 'X';

        if (isMax) {
            int best = -1000;

            for (int i = 0; i < board.getSize(); i++) {
                for (int j = 0; j < board.getSize(); j++) {
                    if (board.getCell(i, j) == ' ') {
                        board.makeMove(i, j, aiSymbol);
                        int value = minimax(board, false);
                        board.makeMove(i, j, ' ');

                        if (value > best)
                            best = value;
                    }
                }
            }

            return best;
        } else {
            int best = 1000;

            for (int i = 0; i < board.getSize(); i++) {
                for (int j = 0; j < board.getSize(); j++) {
                    if (board.getCell(i, j) == ' ') {
                        board.makeMove(i, j, opponentSymbol);
                        int value = minimax(board, true);
                        board.makeMove(i, j, ' ');

                        if (value < best)
                            best = value;
                    }
                }
            }

            return best;
        }
    }

    void getRandomMove(const Board& board, int& row, int& col) const {
        vector<pair<int, int>> emptyCells;

        for (int i = 0; i < board.getSize(); i++) {
            for (int j = 0; j < board.getSize(); j++) {
                if (board.getCell(i, j) == ' ') {
                    emptyCells.push_back({i, j});
                }
            }
        }

        if (!emptyCells.empty()) {
            int index = rand() % emptyCells.size();
            row = emptyCells[index].first;
            col = emptyCells[index].second;
        }
    }

    void getBestMove(Board& board, int& row, int& col) const {
        int bestValue = -1000;
        row = -1;
        col = -1;

        for (int i = 0; i < board.getSize(); i++) {
            for (int j = 0; j < board.getSize(); j++) {
                if (board.getCell(i, j) == ' ') {
                    board.makeMove(i, j, symbol);

                    int moveValue = minimax(board, false);

                    board.makeMove(i, j, ' ');

                    if (moveValue > bestValue) {
                        bestValue = moveValue;
                        row = i;
                        col = j;
                    }
                }
            }
        }
    }

    void getMove(Board& board, int& row, int& col) {
        if (difficulty == EASY)
            getRandomMove(board, row, col);
        else
            getBestMove(board, row, col);
    }

    void getMove(int& row, int& col) override {
        row = -1;
        col = -1;
    }
};

/* ----------- GAME CLASS ----------- */
/* Responsibilities:
 - Control game flow
 - Manage players and turns
 - Handle game modes (PvP, PvC)
 - Display results */
class Game {
private:
    Board board;
    Player* player1;
    Player* player2;
    Player* currentPlayer;
    AIPlayer* aiPlayer;

public:
    Game() {
        // TODO: your implementation here
    }

    void start() {
        // TODO: your implementation here
    }

    void showMenu() {
        // TODO: your implementation here
    }

    void setupPvP() {
        // TODO: your implementation here
    }

    void setupPvC(Difficulty difficulty) {
        // TODO: your implementation here
    }

    void switchPlayer() {
        // TODO: your implementation here
    }

    void handleHumanMove(Player* player) {
        // TODO: your implementation here
    }

    void handleAIMove(AIPlayer* aiPlayer) {
        // TODO: your implementation here
    }

    bool checkGameEnd() {
        // TODO: your implementation here
        return false;
    }

    void displayResult() const {
        // TODO: your implementation here
    }

    void reset() {
        // TODO: your implementation here
    }
};

/* ----------- MAIN ----------- */
int main() {
    Game game;
    game.start();
    return 0;
}
