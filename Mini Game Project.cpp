#include <iostream>
#include <vector>
#include <limits>

class TicTacToe {
private:
    char board[3][3];
    char currentMarker;
    int currentTurn;

    // Resets structural configurations for a fresh game round
    void initializeBoard() {
        char startValue = '1';
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                board[i][j] = startValue++;
            }
        }
        currentMarker = 'X';
        currentTurn = 0;
    }

    // Prints the dynamic status layout to the interface frame
    void displayBoard() const {
        std::cout << "\n     |     |     ";
        std::cout << "\n  " << board[0][0] << "  |  " << board[0][1] << "  |  " << board[0][2] << " ";
        std::cout << "\n_____|_____|_____";
        std::cout << "\n     |     |     ";
        std::cout << "\n  " << board[1][0] << "  |  " << board[1][1] << "  |  " << board[1][2] << " ";
        std::cout << "\n_____|_____|_____";
        std::cout << "\n     |     |     ";
        std::cout << "\n  " << board[2][0] << "  |  " << board[2][1] << "  |  " << board[2][2] << " ";
        std::cout << "\n     |     |     \n\n";
    }

    // Places a tracking piece down safely if cell coordinates align
    bool placeMarker(int slot) {
        int row = (slot - 1) / 3;
        int col = (slot - 1) % 3;

        // Verify if matrix slot contains unselected numeric defaults
        if (board[row][col] != 'X' && board[row][col] != 'O') {
            board[row][col] = currentMarker;
            return true;
        }
        return false;
    }

    // Iterates loops and conditionals to process alignment victories
    bool checkWin() const {
        // Evaluate horizontal or vertical alignments
        for (int i = 0; i < 3; ++i) {
            if (board[i][0] == board[i][1] && board[i][1] == board[i][2]) return true;
            if (board[0][i] == board[1][i] && board[1][i] == board[2][i]) return true;
        }
        // Evaluate diagonal paths
        if (board[0][0] == board[1][1] && board[1][1] == board[2][2]) return true;
        if (board[0][2] == board[1][1] && board[1][1] == board[2][0]) return true;

        return false;
    }

    void swapPlayer() {
        currentMarker = (currentMarker == 'X') ? 'O' : 'X';
    }

public:
    void playGame() {
        bool playing = true;
        while (playing) {
            initializeBoard();
            bool gameWon = false;

            std::cout << "===================================\n";
            std::cout << "      WELCOME TO TIC-TAC-TOE       \n";
            std::cout << "===================================\n";

            while (!gameWon && currentTurn < 9) {
                displayBoard();
                int slot;
                std::cout << "Player " << currentMarker << ", enter choice (1-9): ";
                
                if (!(std::cin >> slot) || slot < 1 || slot > 9) {
                    std::cout << "Invalid spot choice! Pick an open number 1-9.\n";
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    continue;
                }

                if (placeMarker(slot)) {
                    currentTurn++;
                    gameWon = checkWin();
                    if (!gameWon) {
                        swapPlayer();
                    }
                } else {
                    std::cout << "Slot already occupied! Select an alternative target.\n";
                }
            }

            displayBoard();

            if (gameWon) {
                std::cout << "Congratulations! Player " << currentMarker << " wins this match!\n";
            } else {
                std::cout << "It's a tie match! Well played by both sides.\n";
            }

            char reply;
            std::cout << "\nDo you want to play another game? (y/n): ";
            std::cin >> reply;
            if (reply != 'y' && reply != 'Y') {
                playing = false;
                std::cout << "\nThank you for playing! Exiting app process.\n";
            }
        }
    }
};

int main() {
    TicTacToe game;
    game.playGame();
    return 0;
}
