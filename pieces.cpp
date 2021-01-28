#include "pieces.h"
#include "board.h"
#include <iostream>
#include <cstdlib>
#include <cmath>

//GENERAL PIECE METHODS
bool Piece::tryMove(int startRow, int startCol, int endRow, int endCol, Piece *board[8][8])
{
    return false;
}

char Piece::getColor()
{
    return color;
}

char Piece::getIcon()
{
    return icon;
}

char Piece::getValue()
{
    return value;
}

//PAWN

Pawn::Pawn(char newcolor)
{

    color = newcolor;
    value = 1;
    if (color == 'w')
    {
        icon = 'P';
    }
    else
    {
        icon = 'p';
    }
};

bool Pawn::tryMove(int startRow, int startCol, int endRow, int endCol, Piece *board[8][8])
{

    if (board[endRow][endCol] != 0)
    {
        if (startCol == endCol)
        {
            return false;
        }
    }
    // pawn's diagonal capturing
    if (color == 'w' && startCol == endCol - 1 || color == 'w' && startCol == endCol + 1)
    {
        if (startRow == endRow - 1)
        {
            if (board[endRow][endCol] != 0)
            {
                if (board[endRow][endCol]->getColor() != color)
                {
                    return true;
                }
            }
        }
    }
    // pawn's diagonal capturing
    if (color == 'b' && startCol == endCol - 1 || color == 'b' && startCol == endCol + 1)
    {
        if (startRow == endRow + 1)
        {
            if (board[endRow][endCol] != 0)
            {
                if (board[endRow][endCol]->getColor() != color)
                {
                    return true;
                }
            }
        }
    }

    if (color == 'w' && startRow == endRow - 1 && startCol == endCol)
    {
        return true;
    }

    if (color == 'b' && startRow == endRow + 1 && startCol == endCol)
    {
        return true;
    }

    return false;
};

//ROOK

Rook::Rook(char newcolor)
{

    color = newcolor;
    value = 5;
    if (color == 'w')
    {
        icon = 'R';
    }
    else
    {
        icon = 'r';
    }
};

bool Rook::tryMove(int startRow, int startCol, int endRow, int endCol, Piece *board[8][8])
{

    //check straight line
    if ((endRow - startRow) != 0 && (endCol - startCol) != 0)
    {
        return false;
    }

    //capturing
    if (board[endRow][endCol] != 0)
    {
        if (board[endRow][endCol]->getColor() == color)
        {
            return false;
        }
    }

    int rdirection, cdirection;

    //check if there are any pieces between start and destination
    if (startRow == endRow)
    {
        cdirection = (endCol - startCol) / std::abs((endCol - startCol));

        while (startCol != endCol)
        {
            startCol += cdirection;
            if (board[startRow][startCol] != 0 && startCol != endCol)
            {
                return false;
            }
        }
    }
    else
    {
        rdirection = (endRow - startRow) / std::abs((endRow - startRow));

        while (startRow != endRow)
        {

            startRow += rdirection;
            if (board[startRow][startCol] != 0 && startRow != endRow)
            {
                return false;
            }
        }
    }

    return true;
}

//KNIGHT

Knight::Knight(char newcolor)
{

    color = newcolor;
    value = 3;
    if (color == 'w')
    {
        icon = 'N';
    }
    else
    {
        icon = 'n';
    }
};

bool Knight::tryMove(int startRow, int startCol, int endRow, int endCol, Piece *board[8][8])
{

    //capturing
    if (board[endRow][endCol] != 0)
    {
        if (board[endRow][endCol]->getColor() == color)
        {
            return false;
        }
    }

    if (startRow == endRow + 1 || startRow == endRow - 1)
    {
        if (startCol == endCol + 2 || startCol == endCol - 2)
        {
            return true;
        }
    }

    if (startRow == endRow + 2 || startRow == endRow - 2)
    {
        if (startCol == endCol + 1 || startCol == endCol - 1)
        {
            return true;
        }
    }

    return false;
}

//BISHOP

Bishop::Bishop(char newcolor)
{

    color = newcolor;
    value = 3;
    if (color == 'w')
    {
        icon = 'B';
    }
    else
    {
        icon = 'b';
    }
};

bool Bishop::tryMove(int startRow, int startCol, int endRow, int endCol, Piece *board[8][8])
{
    //diagonal line check
    if (std::abs((endRow - startRow)) != std::abs((endCol - startCol)))
    {
        return false;
    }
    //capturing
    if (board[endRow][endCol] != 0)
    {
        if (board[endRow][endCol]->getColor() == color)
        {
            return false;
        }
    }

    int rdirection, cdirection;
    //calculaters the direction of the move
    rdirection = (endRow - startRow) / std::abs((endRow - startRow));
    cdirection = (endCol - startCol) / std::abs((endCol - startCol));

    //checks if there are any pieces between start and destination
    while (startRow != endRow && startCol != endCol)
    {
        startRow += rdirection;
        startCol += cdirection;
        if (board[startRow][startCol] != 0 && startRow != endRow && startCol != endCol)
        {
            return false;
        }
    }
    return true;
}

//QUEEN

Queen::Queen(char newcolor)
{

    color = newcolor;
    value = 9;
    if (color == 'w')
    {
        icon = 'Q';
    }
    else
    {
        icon = 'q';
    }
};

bool Queen::tryMove(int startRow, int startCol, int endRow, int endCol, Piece *board[8][8])
{

    //capturing
    if (board[endRow][endCol] != 0)
    {
        if (board[endRow][endCol]->getColor() == color)
        {
            return false;
        }
    }

    int rdirection, cdirection;

    //check rook move
    if (startRow == endRow || startCol == endCol)
    {

        if (startRow == endRow)
        {
            cdirection = (endCol - startCol) / std::abs((endCol - startCol));

            while (startCol != endCol)
            {
                startCol += cdirection;
                if (board[startRow][startCol] != 0 && startCol != endCol)
                {
                    return false;
                }
            }
        }
        else
        {
            rdirection = (endRow - startRow) / std::abs((endRow - startRow));

            while (startRow != endRow)
            {

                startRow += rdirection;
                if (board[startRow][startCol] != 0 && startRow != endRow)
                {
                    return false;
                }
            }
        }

        return true;
    }

    //check bishop move
    if (std::abs((endRow - startRow)) == std::abs((endCol - startCol)))
    {

        rdirection = (endRow - startRow) / std::abs((endRow - startRow));
        cdirection = (endCol - startCol) / std::abs((endCol - startCol));

        while (startRow != endRow && startCol != endCol)
        {

            startRow += rdirection;
            startCol += cdirection;
            if (board[startRow][startCol] != 0 && startRow != endRow && startCol != endCol)
            {
                return false;
            }
        }
        return true;
    }

    return false;
}

//KING

King::King(char newcolor)
{

    color = newcolor;
    value = 100;
    if (color == 'w')
    {
        icon = 'K';
    }
    else
    {
        icon = 'k';
    }
};

bool King::tryMove(int startRow, int startCol, int endRow, int endCol, Piece *board[8][8])
{
    //capturing
    if (board[endRow][endCol] != 0)
    {
        if (board[endRow][endCol]->getColor() == color)
        {
            return false;
        }
    }

    if (endRow - startRow == 0 || endRow - startRow == 1 || endRow - startRow == -1)
    {
        if (endCol - startCol == 0 || endCol - startCol == 1 || endCol - startCol == -1)
        {
            return true;
        }
    }

    if (endCol - startCol == 0 || endCol - startCol == 1 || endCol - startCol == -1)
    {
        if (endRow - startRow == 0 || endRow - startRow == 1 || endRow - startRow == -1)
        {
            return true;
        }
    }

    return false;
}