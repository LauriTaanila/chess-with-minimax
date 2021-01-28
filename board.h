#pragma once
#include "pieces.h"
#include <string>
#include <vector>
#include <memory>
#include <utility>

struct Position
    {

        int r;
        int c;
    };

struct Move
    {
        Position start;
        Position end;
        int value;
    };


class Board
{

private:
    Piece *board[8][8] = {};
    char currentcolor = 'w';

public:
    Board();
    ~Board();

    char getCurrentcolor();
    bool startMove(std::string move);
    void printBoard();
    Piece* makeMove(struct Move);
    void undoMove(struct Move move, Piece* takenpiece);
    void alternateColor();
    bool testCheck();
    bool testMate();
    int getBoardValue();
    std::vector<struct Move> getPossibleMoves();
    void computerMove();
    struct Move minimax(int depth,int alpha, int beta, bool maximizingPlayer);
};