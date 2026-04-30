#include <iostream>
#include <vector>
#include <string>
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
    Board(int size = 3){
        // TODO: your implementation here
    }

    void display() const {
        // TODO: your implementation here
    }

    bool makeMove(int row, int col, char symbol) {
        // TODO: your implementation here
        return false;
    }

    bool isValidMove(int row, int col) const {
        // TODO: your implementation here
        return false;
    }

    bool checkWin(char symbol) const {
        // TODO: your implementation here
        return false;
    }

    bool isFull() const {
        // TODO: your implementation here
        return false;
    }

    char getCell(int row, int col) const {
        // TODO: your implementation here
        return ' ';
    }

    void reset() {
        // TODO: your implementation here
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
    Player(const string& name, char symbol) {
        // TODO: your implementation here
    }

    virtual void getMove(int& row, int& col) = 0;
    // TODO:your implementation here

    string getName() const {
        // TODO: your implementation here
        return "";
    }

    char getSymbol() const {
        // TODO: your implementation here
        return symbol;
    }

    void setName(const string& name) {
        // TODO: your implementation here
    }
};

/* ----------- HUMAN PLAYER ----------- */
/* Responsibilities:
- Handle user input from console */
class HumanPlayer : public Player {
public:
    HumanPlayer(const string& name, char symbol)
        : Player(name, symbol) {}

    void getMove(int& row, int& col) override {
        // TODO: your implementation here
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
        : Player(name, symbol), difficulty(difficulty) {}

    void getMove(int& row, int& col) override {
        // TODO: your implementation here
        // - If EASY => call getRandomMove
        // - If HARD => call getBestMove
    }

    void setDifficulty(Difficulty newDifficulty) {
        // TODO: your implementation here
    }

    void getRandomMove(const Board& board, int& row, int& col) const {
        // TODO: your implementation here
    }

    void getBestMove(Board& board, int& row, int& col) const {
        // TODO: your implementation here
        // - Use minimax algorithm
    }

    int evaluateBoard(const Board& board) const {
        // TODO: your implementation here
        return 0;
    }

    int minimax(Board& board, bool isMax) const {
        // TODO: your implementation here
        return 0;
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