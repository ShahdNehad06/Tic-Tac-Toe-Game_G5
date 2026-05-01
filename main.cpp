#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>
#include <limits>
using namespace std;

/* ----Enum---- */
// Represents AI difficulty levels
enum Difficulty { EASY, HARD };//0,1

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

    virtual void getMove(Board &board, int &row, int &col) = 0;

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

    void getMove(Board &board, int &row, int &col) override {
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

        for (int i = 0; i < board.getSize(); i++) {
            for (int j = 0; j < board.getSize(); j++) {
                if (board.getCell(i, j) == ' ') {
                    board.makeMove(i, j, symbol);

                    int moveValue = minimax(board, false);

                    board.makeMove(i, j, ' ');/////////////////////

                    if (moveValue > bestValue) {
                        bestValue = moveValue;
                        row = i;
                        col = j;
                    }
                }
            }
        }
    }

    void getMove(Board &board, int &row, int &col)override {
        if (difficulty == 0)
            getRandomMove(board, row, col);
        if (difficulty== 1)
            getBestMove(board, row, col);
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
    Game(){
        srand(time(0));
        player1 = nullptr;
        player2 = nullptr;
        currentPlayer = nullptr;
        aiPlayer = nullptr;
    }

    void start(){
        bool running = true;
        while(running){
            showMenu();
            int choice;
            cin >> choice;

            if(choice == 1){
                setupPvP();
            }else if(choice == 2){
                setupPvC(EASY);
            }else if(choice == 3){
                setupPvC(HARD);
            }else if(choice == 4){
                cout << "Goodbye!" << endl;
                running = false;
                continue;
            }else{
                cout << "Invalid choice. Try again." << endl;
                continue;
            }

            // Game looop
            board.reset();
            currentPlayer = player1;
            bool gameOver = false;

            while(!gameOver){
                board.display();

                if(currentPlayer == aiPlayer){
                    handleAIMove(aiPlayer);
                }else{
                    handleHumanMove(currentPlayer);
                }

                if(checkGameEnd()){
                    board.display();
                    displayResult();
                    gameOver = true;
                }else{
                    switchPlayer();
                }
            }

            // Ask to play again
            cout << "Play again? (y/n): ";
            char again;
            cin >> again;
            if(again != 'y' && again != 'Y'){
                running = false;
            }

            // Cleanup
            delete player1;
            delete player2;
            player1 = nullptr;
            player2 = nullptr;
            currentPlayer = nullptr;
            aiPlayer = nullptr;
        }
    }

    void showMenu(){
        cout << "TIC-TAC-TOE GAME" << endl;
        cout << "================" << endl;
        cout << "1. Player vs Player" << endl;
        cout << "2. Player vs Computer (Easy)" << endl;
        cout << "3. Player vs Computer (Hard)" << endl;
        cout << "4. Exit" << endl;
        cout << "Select game mode: ";
    }

    void setupPvP(){
        string name1, name2;
        char s1,s2;
        cout << "Enter Player 1 name and your symbol : ";
        cin >> name1>>s1;
        cout << "Enter Player 2 name and your symbol: ";
        cin >> name2>>s2;

        player1 = new HumanPlayer(name1, s1);
        player2 = new HumanPlayer(name2, s2);
        aiPlayer = nullptr;
    }

    void setupPvC(Difficulty difficulty){
        string name;
        char sh;
        char sc;
        cout << "Enter your name and your symbol: ";
        cin >> name>>sh;
        if (sh=='X'||sh=='x') {
            sc='O';
        }
        if (sh=='O'||sh=='o') {
            sc='X';
        }
        player1 = new HumanPlayer(name, sh);
        aiPlayer = new AIPlayer("Computer", sc, difficulty);
        player2 = aiPlayer;
    }

    void switchPlayer(){
        if (currentPlayer == player1) currentPlayer = player2;
        else currentPlayer = player1;
    }

    void handleHumanMove(Player* player){
        HumanPlayer* human = static_cast<HumanPlayer*>(player);
        int row, col;
        human->getMove(board, row, col);
        board.makeMove(row, col, human->getSymbol());
    }

    void handleAIMove(AIPlayer* ai){
        int row, col;
        cout << ai->getName() << " (" << ai->getSymbol() << ") is making a move..." << endl;
        ai->getMove(board, row, col);
        board.makeMove(row, col, ai->getSymbol());
    }

    bool checkGameEnd(){
        if(board.checkWin(currentPlayer->getSymbol())) return true;
        if(board.isFull()) return true;
        return false;
    }

    void displayResult() const {
        if(board.checkWin(currentPlayer->getSymbol()))
            cout << currentPlayer->getName() << " (" << currentPlayer->getSymbol() << ") wins!" << endl;
        else
            cout << "It's a draw!" << endl;
    }

    void reset(){
        board.reset();
        currentPlayer = player1;
    }
};

/* ----------- MAIN ----------- */
int main() {
    Game game;
    game.start();
    return 0;
}
