#include "pieces.h"
#include "board.h"
#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <utility>

Board::Board()
{

    for (int i = 0; i < 8; i++)
    {
        board[1][i] = new Pawn('w');
    }

    for (int i = 0; i < 8; i++)
    {
        board[6][i] = new Pawn('b');
    }

    board[0][0] = new Rook('w');
    board[0][7] = new Rook('w');
    board[7][0] = new Rook('b');
    board[7][7] = new Rook('b');

    board[0][1] = new Knight('w');
    board[0][6] = new Knight('w');
    board[7][1] = new Knight('b');
    board[7][6] = new Knight('b');

    board[0][2] = new Bishop('w');
    board[0][5] = new Bishop('w');
    board[7][2] = new Bishop('b');
    board[7][5] = new Bishop('b');

    board[0][3] = new Queen('w');
    board[7][3] = new Queen('b');

    board[0][4] = new King('w');
    board[7][4] = new King('b');
};

Board::~Board()
{
    for (int r = 0; r < 8; r++)
    {
        for (int c = 0; c < 8; c++)
        {
            delete board[r][c];
            board[r][c] = 0;
        }
    }
}

char Board::getCurrentcolor(){
    return currentcolor;
}

//human player tries to make a move
bool Board::startMove(std::string move)
{

    Piece *takenpiece;

    int startCol = move[0] - 97;
    int startRow = move[1] - '1';
    int endCol = move[3] - 97;
    int endRow = move[4] - '1';

    if (board[startRow][startCol] == 0)
    {
        std::cout << "No piece found!";
        return false;
    }

    if (board[startRow][startCol]->getColor() != currentcolor)
    {
        std::cout << "Not your piece!";
        return false;
    }

    if (board[startRow][startCol]->tryMove(startRow, startCol, endRow, endCol, board))
    {
        takenpiece = board[endRow][endCol];
        board[endRow][endCol] = board[startRow][startCol];
        board[startRow][startCol] = 0;
    }
    else
    {
        std::cout << "Invalid move!";
        return false;
    }

    if (testCheck())
    {
        //undo
        board[startRow][startCol] = board[endRow][endCol];
        board[endRow][endCol] = takenpiece;
        std::cout << "You would be in a check!!!";
        return false;
    }

    alternateColor();

    delete takenpiece;
    return true;
};

void Board::printBoard()
{

    std::cout << "\n ---------------------------------\n";
    int rank = 8;

    for (int i = 7; i >= 0; i--)
    {
        std::cout << i + 1;

        for (int j = 0; j < 8; j++)
        {

            std::cout << "| ";
            if (board[i][j] == 0)
            {
                std::cout << " ";
            }
            else
            {
                std::cout << board[i][j]->getIcon();
            }
            std::cout << " ";
        }
        std::cout << "|\n";
        std::cout << " ---------------------------------\n";
    }

    std::cout << "   a   b   c   d   e   f   g   h";
}


Piece *Board::makeMove(struct Move move)
{
    Piece *takenpiece = board[move.end.r][move.end.c];
    board[move.end.r][move.end.c] = board[move.start.r][move.start.c];
    board[move.start.r][move.start.c] = 0;
    return takenpiece;
}

void Board::undoMove(struct Move move, Piece *takenpiece)
{
    board[move.start.r][move.start.c] = board[move.end.r][move.end.c];
    board[move.end.r][move.end.c] = takenpiece;
}

void Board::alternateColor()
{
    if (currentcolor == 'w')
    {
        currentcolor = 'b';
    }
    else
    {
        currentcolor = 'w';
    }
}

//retuns true if king is in check
bool Board::testCheck()
{

    int kingRow, kingCol;
    //finds current player's king
    for (int r = 0; r < 8; r++)
    {
        for (int c = 0; c < 8; c++)
        {
            if (board[r][c] != 0)
            {
                if (currentcolor == 'w')
                {
                    if (board[r][c]->getIcon() == 'K')
                    {
                        kingRow = r;
                        kingCol = c;
                        break;
                    }
                }
                else
                {
                    if (board[r][c]->getIcon() == 'k')
                    {
                        kingRow = r;
                        kingCol = c;
                        break;
                    }
                }
            }
        }
    }

    //checks if it is being attacked
    for (int r = 0; r < 8; r++)
    {
        for (int c = 0; c < 8; c++)
        {
            if (board[r][c] != 0)
            {
                if (board[r][c]->getColor() != currentcolor)
                {
                    if (board[r][c]->tryMove(r, c, kingRow, kingCol, board))
                    {
                        return true;
                    }
                }
            }
        }
    }

    return false;
}

//returns true if there is a mate
bool Board::testMate()
{
    Piece *takenpiece;

    std::vector<struct Move> movelist = getPossibleMoves();

    for (int i = 0; i < movelist.size(); i++)
    {

        Piece *takenpiece = makeMove(movelist[i]);

        //if check gets removed there is no mate
        if (!testCheck())
        {
            //undo move
            undoMove(movelist[i], takenpiece);
            return false;
        }
        else
        {
            //undo move
            undoMove(movelist[i], takenpiece);
        }
    }

    return true;
}

//calculates value of the board using piece values
int Board::getBoardValue()
{
    int value = 0;

    for (int r = 0; r < 8; r++)
    {
        for (int c = 0; c < 8; c++)
        {
            if (board[r][c] != 0)
            {
                if (board[r][c]->getColor() == 'b')
                {
                    value += board[r][c]->getValue();
                    
                }
                else
                {
                    value += -board[r][c]->getValue();
                    
                }
                
            }
        }
    }

    return value;
}


//returns a vector of all possible moves
std::vector<struct Move> Board::getPossibleMoves()
{

    int count = 0;
    std::vector<struct Move> movelist;
    Piece *takenpiece;

    for (int startRow = 0; startRow < 8; startRow++)
    {
        for (int startCol = 0; startCol < 8; startCol++)
        {
            if (board[startRow][startCol] != 0)
            {
                if (board[startRow][startCol]->getColor() == currentcolor)
                {
                    //checks moves
                    for (int endRow = 0; endRow < 8; endRow++)
                    {
                        for (int endCol = 0; endCol < 8; endCol++)
                        {
                            if (board[startRow][startCol]->tryMove(startRow, startCol, endRow, endCol, board))
                            {
                                struct Move newmove;

                                newmove.start.r = startRow;
                                newmove.start.c = startCol;
                                newmove.end.r = endRow;
                                newmove.end.c = endCol;

                                Piece *takenpiece = makeMove(newmove);

                                if (testCheck())
                                {
                                    undoMove(newmove, takenpiece);
                                }
                                else
                                {
                                    undoMove(newmove, takenpiece);

                                    movelist.push_back(newmove);
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    return movelist;
}

//computer makes a move
void Board::computerMove()
{

    struct Move bestMove;

    if (testMate())
    {
        std::cout << "CHECKMATE!";
        return;
    }

    // 5 is the number of moves computer looks ahead. Change it to modify difficulty.
    bestMove = minimax(5,-1000,1000, true);
    makeMove(bestMove);

    alternateColor();
}

//minimax algorithm with alpha-beta pruning 
//https://en.wikipedia.org/wiki/Alpha%E2%80%93beta_pruning
struct Move Board::minimax(int depth, int alpha, int beta, bool maximizingPlayer)
{

    Piece *takenpiece;
    int maxEval, minEval, eval;
    struct Move bestMove;

    if (depth == 0 || testMate())
    {
        int value = getBoardValue();
        bestMove.value = value;
        return bestMove;
    }

    if (maximizingPlayer)
    {
        bestMove.value = -1000;
        std::vector<struct Move> movelist = getPossibleMoves();

        for (int i = 0; i < movelist.size(); i++)
        {
            Piece *takenpiece = makeMove(movelist[i]);

            alternateColor();
            eval = minimax(depth - 1, alpha, beta, false).value;

            if (eval > bestMove.value)
            {
                bestMove.start.r = movelist[i].start.r;
                bestMove.start.c = movelist[i].start.c;
                bestMove.end.r = movelist[i].end.r;
                bestMove.end.c = movelist[i].end.c;
                bestMove.value = eval;
            }
            undoMove(movelist[i], takenpiece);
            alternateColor();
            if(eval > alpha){
                alpha = eval;
                if(beta <= alpha){
                    break;
                }
            }


        }
        
        return bestMove;
    }
    else
    {
        bestMove.value = 1000;
        std::vector<struct Move> movelist = getPossibleMoves();

        for (int i = 0; i < movelist.size(); i++)
        {
            
            //make move
            Piece *takenpiece = makeMove(movelist[i]);

            alternateColor();
            eval = minimax(depth - 1, alpha, beta, true).value;

            if (eval < bestMove.value)
            {
                bestMove.start.r = movelist[i].start.r;
                bestMove.start.c = movelist[i].start.c;
                bestMove.end.r = movelist[i].end.r;
                bestMove.end.c = movelist[i].end.c;
                bestMove.value = eval;
            }
            //undo
            undoMove(movelist[i], takenpiece);
            alternateColor();
            if(eval < beta){
                beta = eval;
                if(beta <= alpha){
                    break;
                }
            }


        }
        
        return bestMove;
    }
}
