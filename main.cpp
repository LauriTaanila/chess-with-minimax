#include "pieces.h"
#include "board.h"
#include <iostream>
#include <string>
#include <regex>

void gameLoop(bool vsComputer);

int main()
{


    int choice;
    Board autoboard;
    while (1)
    {
        std::cout   << "       _                   \n" 
                    << "   ___| |__   ___  ___ ___ \n" 
                    << "  / __| '_ \\ / _ \\/ __/ __|\n" 
                    << " | (__| | | |  __/\\__ \\__ \\\n" 
                    << "  \\___|_| |_|\\___||___/___/\n\n";


        std::cout << "\n1.Play vs another human\n2.Play vs computer\n3.Help\n> ";
        std::cin >> choice;
        switch (choice)
        {
        case 1:
            gameLoop(false);
            break;

        case 2:
            gameLoop(true);
            break;

        case 3:
            std::cout << "Enter moves using the board coordinates. For example \"e2 e3\" or \"b2 c3\".\n Following features are still missing: \n-stalemate\n-pawn double move\n-castling\n-promotion\n-en passant\n\n";

        default:
            break;
        }
        std::cin.clear();
        std::cin.ignore(50, '\n');

    }

    return 0;
}

void gameLoop(bool vsComputer)
{
    std::regex notation("[a-h][1-8]\\s[a-h][1-8]");
    Board board;
    std::string move;
    std::getline(std::cin, move);
    board.printBoard();

    struct move *bestmove;

    while (1)
    {
        do
        {
            if (board.getCurrentcolor() == 'w')
            {
                std::cout << "\nWHITE'S TURN\n";
            }
            else
            {
                std::cout << "\nBLACK'S TURN\n";
            }
            if (board.testCheck())
            {
                if (board.testMate())
                {
                    std::cout << "\n!!!CHECKMATE!!!";
                    return;
                }
                else
                {
                    std::cout << "\n!!!CHECK!!!";
                }
            }
            std::cout << "\nEnter what piece to move> ";
            std::getline(std::cin, move);

        } while (!std::regex_match(move, notation));

        if (board.startMove(move))
        {
            if (vsComputer)
            {
                board.computerMove();
            }
            board.printBoard();
        }
    }
}
