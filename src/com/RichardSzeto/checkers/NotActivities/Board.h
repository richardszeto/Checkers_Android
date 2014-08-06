/** Class that holds the board, all the pieces, and the state of the game
  *
  * @author Richard Szeto
  *
  *
  */

#ifndef BOARD_H
#define BOARD_H

#include "Captured.h"
#include "globals.h"
#include "GameTree.h"

namespace CheckersSzeto
{   
    class Board
    {
    public:
        Board();
        Board(const Board &boardObject);
        virtual ~Board();
        Board& operator =(const Board &rightSide);
        void clear();
        void scanCapture();
        void scanMove();
        bool isEndGame();
        bool move(int startX, int startY,
                int endX, int endY);
        void printBoard();
        void printTurn();
        bool getIsMultiJump() const;

        friend class GameTree;

    protected:
        bool isPieceColor(Color color, int xCoord, int yCoord) const;
        bool isMan(int xCoord, int yCoord) const;
        bool isKing(int xCoord, int yCoord) const;
        bool canCapture(int xCoord, int yCoord,
            Corner corner) const;
        bool canMove(int xCoord, int yCoord,
            Corner corner) const;
        void movePiece(int startX, int startY,
                int endX, int endY);
        bool moveMan(int startX, int startY,
                int endX, int endY);
        bool moveKing(int startX, int startY,
                int endX, int endY);
        void initializePieces();
        void moveAllToCaptured();
        bool moveToCaptured(int xCoord, int yCoord);
        bool createKing(int xCoord, int yCoord);

        Piece grid[GRID_LENGTH][GRID_LENGTH];
        Captured *captured[NUMBER_PLAYERS];
        Color turn;
        bool isMultiJump;
        bool needToCapture;
        bool needToMove;
    }; // end Board
} // end CheckersSzeto

#endif