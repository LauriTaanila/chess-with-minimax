#pragma once

class Piece{

    protected:
        char color;
        char icon;
        int value;

    public:
        virtual bool tryMove(int startRow,int startCol, int endRow, int endCol, Piece* board[8][8]);
        char getColor();
        char getIcon();
        char getValue();
};

class Pawn : public Piece{

    public:
        Pawn(char color);
        bool tryMove(int startRow,int startCol, int endRow, int endCol, Piece* board[8][8]);


};

class Rook : public Piece{
    public: 
        Rook(char color);
        bool tryMove(int startRow,int startCol, int endRow, int endCol, Piece* board[8][8]);
};

class Knight : public Piece{
    public: 
        Knight(char color);
        bool tryMove(int startRow,int startCol, int endRow, int endCol, Piece* board[8][8]);
};

class Bishop : public Piece{
    public: 
        Bishop(char color);
        bool tryMove(int startRow,int startCol, int endRow, int endCol, Piece* board[8][8]);
};

class Queen : public Piece{
    public: 
        Queen(char color);
        bool tryMove(int startRow,int startCol, int endRow, int endCol, Piece* board[8][8]);

};

class King : public Piece{
    public: 
        King(char color);
        bool tryMove(int startRow,int startCol, int endRow, int endCol, Piece* board[8][8]);
};
