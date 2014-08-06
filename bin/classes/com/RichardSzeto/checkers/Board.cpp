/** Class that holds the board, all the pieces, and the state of the game
  *
  * @author Richard Szeto
  *
  *
  */

#include <iostream>
#include <cstdlib>
#include "Board.h"

namespace CheckersSzeto
{   
    Board::Board()
    {
        turn = WHITE;

        isMultiJump = false;

        needToCapture = false;

        needToMove = true;

        captured[WHITE] = new Captured(PLAYER_PIECES);

        captured[BLACK] = new Captured(PLAYER_PIECES);

        for (int i = 0; i < GRID_LENGTH; i++)
        {
            for (int j = 0; j < GRID_LENGTH; j++)
            {
                grid[i][j] = NONE;
            } // end for
        } // end for

        initializePieces();
    } // end Board

    Board::Board(const Board &boardObject)
    {
        for(int i = 0; i < GRID_LENGTH; i++)
        {
            for(int j = 0; j < GRID_LENGTH; j++)
            {
                grid[i][j] = boardObject.grid[i][j];
            }
        }

        captured[WHITE] = new Captured(*(boardObject.captured[WHITE]));

        captured[BLACK] = new Captured(*(boardObject.captured[BLACK]));

        turn = boardObject.turn;

        isMultiJump = boardObject.isMultiJump;

        needToCapture = boardObject.needToCapture;

        needToMove = boardObject.needToMove;
    }

    Board::~Board()
    {
        captured[WHITE]->clear();

        captured[BLACK]->clear();

        delete captured[WHITE];

        delete captured[BLACK];

        captured[WHITE] = NULL;

        captured[BLACK] = NULL;
    }

    Board& Board::operator =(const Board &rightSide)
    {
        if(captured[WHITE] != NULL)
        {
            captured[WHITE]->clear();

            delete captured[WHITE];

            captured[WHITE] = NULL;
        }

        if(captured[BLACK] != NULL)
        {
            captured[BLACK]->clear();

            delete captured[BLACK];

            captured[BLACK] = NULL;
        }

        for(int i = 0; i < GRID_LENGTH; i++)
        {
            for(int j = 0; j < GRID_LENGTH; j++)
            {
                grid[i][j] = rightSide.grid[i][j];
            }
        }

        captured[WHITE] = new Captured(*(rightSide.captured[WHITE]));

        captured[BLACK] = new Captured(*(rightSide.captured[BLACK]));

        turn = rightSide.turn;

        isMultiJump = rightSide.isMultiJump;

        needToCapture = rightSide.needToCapture;

        needToMove = rightSide.needToMove;

        return *this;
    }

    void Board::clear()
    {
        captured[WHITE]->clear();

        captured[BLACK]->clear();

        for(int i = 0; i < GRID_LENGTH; i++)
        {
            for(int j = 0; j < GRID_LENGTH; j++)
            {
                grid[i][j] = NONE;
            }
        }

        initializePieces();

        turn = WHITE;

        isMultiJump = false;

        needToCapture = false;

        needToMove = true;
    } // end clear

    bool Board::isPieceColor(Color color, int xCoord, int yCoord) const
    {
        return ((color == WHITE && (grid[xCoord][yCoord] == WHITE_MAN ||
                grid[xCoord][yCoord] == WHITE_KING)) || (color == BLACK &&
                (grid[xCoord][yCoord] == BLACK_MAN || 
                    grid[xCoord][yCoord] == BLACK_KING)));

        return false;
    }

    bool Board::isMan(int xCoord, int yCoord) const
    {
        return (grid[xCoord][yCoord] == WHITE_MAN ||
                    grid[xCoord][yCoord] == BLACK_MAN);

        return false;
    }

    bool Board::isKing(int xCoord, int yCoord) const
    {
        return (grid[xCoord][yCoord] == WHITE_KING ||
                    grid[xCoord][yCoord] == BLACK_KING);

        return false;
    }

    bool Board::move(int startX, int startY, int endX, int endY)
    {
        bool xBounds = startX >= 0 && startX < GRID_LENGTH &&
                endX >= 0 && endX < GRID_LENGTH;

        bool yBounds = startY >= 0 && startY < GRID_LENGTH &&
                endY >= 0 && endY < GRID_LENGTH;

        bool sourceExists = grid[startX][startY] != NONE;

        bool endIsNone = grid[endX][endY] == NONE;

        bool diagonalMove = abs(startX - endX) == abs(startY - endY);

        bool correctTurn = false;

        bool startIsMan = false;

        bool startIsKing = false;

        if(sourceExists)
        {
            correctTurn = isPieceColor(turn, startX, startY);

            startIsMan = isMan(startX, startY);

            startIsKing = isKing(startX, startY);
        }

        if (xBounds && yBounds && sourceExists && endIsNone &&
                correctTurn && diagonalMove)
        {
            if(startIsMan)
            {
                return moveMan(startX, startY, endX, endY);
            }
            else if(startIsKing)
            {
                return moveKing(startX, startY, endX, endY);
            }
        }

        return false;
    }

    bool Board::canCapture(int xCoord, int yCoord, Corner corner) const
    {
        Color enemyColor;

        if(turn == WHITE)
        {
            enemyColor = BLACK;
        }
        else if(turn == BLACK)
        {
            enemyColor = WHITE;
        }

        if(isPieceColor(turn, xCoord, yCoord))
        {
            if(corner == TOP_LEFT)
            {
                return (xCoord - 1 >= 0 &&
                    yCoord + 1 < GRID_LENGTH &&
                    isPieceColor(enemyColor, xCoord - 1, yCoord + 1) &&
                    xCoord - 2 >= 0 &&
                    yCoord + 2 < GRID_LENGTH &&
                    grid[xCoord - 2][yCoord + 2] == NONE);
            }
            else if(corner == TOP_RIGHT)
            {
                return (xCoord + 1 < GRID_LENGTH &&
                    yCoord + 1 < GRID_LENGTH &&
                    isPieceColor(enemyColor, xCoord + 1, yCoord + 1) &&
                    xCoord + 2 < GRID_LENGTH &&
                    yCoord + 2 < GRID_LENGTH &&
                    grid[xCoord + 2][yCoord + 2] == NONE);
            }
            else if(corner == BOTTOM_LEFT)
            {
                return (xCoord - 1 >= 0 &&
                    yCoord - 1 >= 0 &&
                    isPieceColor(enemyColor, xCoord - 1, yCoord - 1) &&
                    xCoord - 2 >= 0 &&
                    yCoord - 2 >= 0 &&
                    grid[xCoord - 2][yCoord - 2] == NONE);
            }
            else if(corner == BOTTOM_RIGHT)
            {
                return (xCoord + 1 < GRID_LENGTH &&
                    yCoord - 1 >= 0 &&
                    isPieceColor(enemyColor, xCoord + 1, yCoord - 1) &&
                    xCoord + 2 < GRID_LENGTH &&
                    yCoord - 2 >= 0 &&
                    grid[xCoord + 2][yCoord - 2] == NONE);
            }
        }

        return false;
    }

    void Board::scanCapture()
    {
        for(int startingIndex = 0; startingIndex < 2; startingIndex++)
        {
            for(int i = startingIndex; i < GRID_LENGTH; i += 2)
            {
                for(int j = startingIndex; j < GRID_LENGTH; j += 2)
                {
                    if(isPieceColor(turn, i, j))
                    {
                        if((isPieceColor(WHITE, i, j) && isMan(i, j)) ||
                            isKing(i, j))
                        {
                            if(canCapture(i, j, TOP_LEFT) ||
                                canCapture(i, j, TOP_RIGHT))
                            {
                                needToCapture = true;
                                return;
                            }
                        }

                        if((isPieceColor(BLACK, i, j) && isMan(i, j)) ||
                            isKing(i, j))
                        {
                            if(canCapture(i, j, BOTTOM_LEFT) ||
                                canCapture(i, j, BOTTOM_RIGHT))
                            {
                                needToCapture = true;
                                return;
                            }
                        }
                    }
                }
            }
        }

        needToCapture = false;
    }

    bool Board::canMove(int xCoord, int yCoord, Corner corner) const
    {
        if(isPieceColor(turn, xCoord, yCoord))
        {
            if(corner == TOP_LEFT)
            {
                return (xCoord - 1 >= 0 &&
                    yCoord + 1 < GRID_LENGTH &&
                    grid[xCoord - 1][yCoord + 1] == NONE);
            }
            else if(corner == TOP_RIGHT)
            {
                return (xCoord + 1 < GRID_LENGTH &&
                    yCoord + 1 < GRID_LENGTH &&
                    grid[xCoord + 1][yCoord + 1] == NONE);
            }
            else if(corner == BOTTOM_LEFT)
            {
                return (xCoord - 1 >= 0 &&
                    yCoord - 1 >= 0 &&
                    grid[xCoord - 1][yCoord - 1] == NONE);
            }
            else if(corner == BOTTOM_RIGHT)
            {
                return (xCoord + 1 < GRID_LENGTH &&
                    yCoord - 1 >= 0 &&
                    grid[xCoord + 1][yCoord - 1] == NONE);
            }
        }

        return false;
    }

    void Board::scanMove()
    {
        for(int startingIndex = 0; startingIndex < 2; startingIndex++)
        {
            for(int i = startingIndex; i < GRID_LENGTH; i += 2)
            {
                for(int j = startingIndex; j < GRID_LENGTH; j += 2)
                {
                    if(isPieceColor(turn, i, j))
                    {
                        if((isPieceColor(WHITE, i, j) && isMan(i, j)) ||
                            isKing(i, j))
                        {
                            if(canMove(i, j, TOP_LEFT) ||
                                canMove(i, j, TOP_RIGHT))
                            {
                                needToMove = true;
                                return;
                            }
                        }

                        if((isPieceColor(BLACK, i, j) && isMan(i, j)) ||
                            isKing(i, j))
                        {
                            if(canMove(i, j, BOTTOM_LEFT) ||
                                canMove(i, j, BOTTOM_RIGHT))
                            {
                                needToMove = true;
                                return;
                            }
                        }
                    }
                }
            }
        }

        needToMove = false;
    }

    bool Board::isEndGame()
    {
        using std::cout;
        using std::endl;

        if(!needToCapture && !needToMove)
        {
            if(turn == WHITE)
            {
                cout << "Black wins\n";

                return true;
            }
            else if(turn == BLACK)
            {
                cout << "White wins\n";

                return true;
            }
        }

        return false;
    }

    bool Board::moveMan(int startX, int startY, int endX, int endY)
    {
        int absXMove;
        int diffYMove;
        int kingYMove;

        int absXCapture;
        int diffYCapture;

        Color enemyColor;

        if(turn == WHITE)
        {
            absXMove = 1;
            diffYMove = -1;
            kingYMove = 7;

            absXCapture = 2;
            diffYCapture = -2;

            enemyColor = BLACK;
        }
        else if(turn == BLACK)
        {
            absXMove = 1;
            diffYMove = 1;
            kingYMove = 0;

            absXCapture = 2;
            diffYCapture = 2;

            enemyColor = WHITE;
        }

        if(grid[endX][endY] == NONE)
        {
            if (abs(startX - endX) == absXMove && 
                startY - endY == diffYMove && 
                !isMultiJump &&
                !needToCapture)
            {
                movePiece(startX, startY, endX, endY);

                if (endY == kingYMove)
                {
                    createKing(endX, endY);
                }

                turn = enemyColor;

                return true;
            }
            else if (abs(startX - endX) == absXCapture && 
                startY - endY == diffYCapture &&
                needToCapture)
            {
                isMultiJump = false;

                int eatX = (startX + endX) / 2;
                int eatY = (startY + endY) / 2;

                if (isPieceColor(enemyColor, eatX, eatY))
                {
                    movePiece(startX, startY, endX, endY);

                    moveToCaptured(eatX, eatY);

                    bool changeTurns = true;

                    if (endY == kingYMove)
                    {
                        createKing(endX, endY);
                    }
                    else if (isPieceColor(WHITE, endX, endY) &&
                        (canCapture(endX, endY, TOP_LEFT) ||
                            canCapture(endX, endY, TOP_RIGHT)))
                    {
                        // allow multi-jump

                        changeTurns = false;

                        isMultiJump = true;
                    }
                    else if (isPieceColor(BLACK, endX, endY) &&
                        (canCapture(endX, endY, BOTTOM_LEFT) ||
                            canCapture(endX, endY, BOTTOM_RIGHT)))
                    {
                        // allow multi-jump

                        changeTurns = false;

                        isMultiJump = true;
                    }

                    if (changeTurns)
                    {
                        turn = enemyColor;
                    }

                    return true;
                }
            }
        }

        return false;
    }

    bool Board::moveKing(int startX, int startY, int endX, int endY)
    {
        Color enemyColor;

        if(turn == WHITE)
        {
            enemyColor = BLACK;
        }
        else if(turn == BLACK)
        {
            enemyColor = WHITE;
        }

        if(grid[endX][endY] == NONE)
        {
            if(abs(startX - endX) == 1 && 
                abs(startY - endY) == 1 && 
                !isMultiJump &&
                !needToCapture)
            {
                movePiece(startX, startY, endX, endY);

                turn = enemyColor;

                return true;
            }
            else if(abs(startX - endX) == 2 && 
                abs(startY - endY) == 2 &&
                needToCapture)
            {
                isMultiJump = false;

                int eatX = (startX + endX) / 2;
                int eatY = (startY + endY) / 2;

                if(isPieceColor(enemyColor, eatX, eatY))
                {
                    movePiece(startX, startY, endX, endY);

                    moveToCaptured(eatX, eatY);

                    bool changeTurns = true;

                    if(canCapture(endX, endY, TOP_LEFT) ||
                        canCapture(endX, endY, TOP_RIGHT) ||
                        canCapture(endX, endY, BOTTOM_LEFT) ||
                        canCapture(endX, endY, BOTTOM_RIGHT))
                    {
                        // allow multi-jump

                        changeTurns = false;

                        isMultiJump = true;
                    }

                    if(changeTurns)
                    {
                        turn = enemyColor;
                    }

                    return true;
                }
            }
        }

        return false;
    }

    void Board::movePiece(int startX, int startY, int endX, int endY)
    {
        grid[endX][endY] = grid[startX][startY];

        grid[startX][startY] = NONE;
    }

    void Board::printBoard()
    {
        using std::cout;
        using std::endl;

        for (int i = 0; i < captured[BLACK]->getLength(); i++)
        {
            cout << "w ";
        }

        cout << endl;

        for (int j = GRID_LENGTH - 1; j >= 0; j--)
        {

            cout << "  ---------------------------------" << endl;

            cout << j << " |";

            for (int i = 0; i < GRID_LENGTH; i++)
            {
                if (grid[i][j] != NONE)
                {
                    if (isPieceColor(WHITE, i, j))
                    {
                        if (isMan(i, j))
                        {
                            cout << " w ";
                        }
                        else if (isKing(i, j))
                        {
                            cout << " W ";
                        }
                    }
                    else if (isPieceColor(BLACK, i, j))
                    {
                        if (isMan(i, j))
                        {
                            cout << " b ";
                        }
                        else if (isKing(i, j))
                        {
                            cout << " B ";
                        }
                    }
                }
                else
                {
                    cout << "   ";
                }

                cout << "|";
            }

            cout << endl;
        }

        cout << "  ---------------------------------" << endl;

        cout << "   ";

        for (int i = 0; i < GRID_LENGTH; i++)
        {
            cout << " " << i << "  ";
        }

        cout << endl;

        for (int i = 0; i < captured[WHITE]->getLength(); i++)
        {
            cout << "b ";
        }

        cout << endl << endl;
    }

    void Board::printTurn()
    {
        using std::cout;
        using std::endl;

        if (turn == WHITE)
        {
            cout << "White's Turn" << endl;
        }
        else if (turn == BLACK)
        {
            cout << "Black's Turn" << endl;
        }
    }

    bool Board::getIsMultiJump() const
    {
        return isMultiJump;
    }

    void Board::initializePieces()
    {
        for (int i = 0; i < GRID_LENGTH; i += 2)
        {
            for (int j = 0; j < 3; j += 2)
            {
                grid[i][j] = WHITE_MAN;
            } // end for
        } // end for

        for (int i = 1; i < GRID_LENGTH; i += 2)
        {
            grid[i][1] = WHITE_MAN;
        } // end for

        for (int i = 1; i < GRID_LENGTH; i += 2)
        {
            for (int j = 5; j < GRID_LENGTH; j += 2)
            {
                grid[i][j] = BLACK_MAN;
            } // end for
        } // end for

        for (int i = 0; i < GRID_LENGTH; i += 2)
        {
            grid[i][6] = BLACK_MAN;
        } // end for
    } // end initializePieces

    void Board::moveAllToCaptured()
    {
        for(int startingIndex = 0; startingIndex < 2; startingIndex++)
        {
            for(int i = startingIndex; i < GRID_LENGTH; i += 2)
            {
                for(int j = startingIndex; j < GRID_LENGTH; j += 2)
                {
                    if(grid[i][j] != NONE)
                    {
                        moveToCaptured(i, j);
                    }
                }
            }
        }
    }

    bool Board::moveToCaptured(int xCoord, int yCoord)
    {
        Color pieceColor;

        Color enemyColor;

        if(grid[xCoord][yCoord] != NONE)
        {
            if(isPieceColor(WHITE, xCoord, yCoord))
            {
                pieceColor = WHITE;
            }
            else
            {
                pieceColor = BLACK;
            }

            if(pieceColor == WHITE)
            {
                enemyColor = BLACK;
            }
            else if(pieceColor == BLACK)
            {
                enemyColor = WHITE;
            }

            if(captured[enemyColor]->getLength() + 1 < PLAYER_PIECES &&
                isKing(xCoord, yCoord))
            {
                captured[enemyColor]->push(grid[xCoord][yCoord]);

                captured[enemyColor]->push(grid[xCoord][yCoord]);

                grid[xCoord][yCoord] = NONE;

                return true;
            }
            else if(captured[enemyColor]->getLength() < PLAYER_PIECES &&
                isMan(xCoord, yCoord))
            {
                captured[enemyColor]->push(grid[xCoord][yCoord]);

                grid[xCoord][yCoord] = NONE;

                return true;
            }
        }

        return false;
    } // end moveToCaptured

    bool Board::createKing(int xCoord, int yCoord)
    {
        using std::cout;
        using std::endl;

        Color pieceColor;

        Color enemyColor;

        if(grid[xCoord][yCoord] != NONE)
        {
            if(isPieceColor(WHITE, xCoord, yCoord))
            {
                pieceColor = WHITE;
            }
            else
            {
                pieceColor = BLACK;
            }

            if(pieceColor == WHITE)
            {
                if(yCoord != 7)
                {
                    cout << "pieceColor == WHITE\n";
                    return false;
                }

                enemyColor = BLACK;
            }
            else if(pieceColor == BLACK)
            {
                if(yCoord != 0)
                {
                    cout << "pieceColor == BLACK\n";
                    return false;
                }

                enemyColor = WHITE;
            }

            if(captured[enemyColor]->getLength() > 0)
            {
                const int usableTilesPerRow = 4;

                int xTiles[usableTilesPerRow];

                if(pieceColor == WHITE)
                {
                    for(int i = 0; i < usableTilesPerRow; i++)
                    {
                        xTiles[i] = (2 * i) + 1;
                    }
                }
                else if(pieceColor == BLACK)
                {
                    for(int i = 0; i < usableTilesPerRow; i++)
                    {
                        xTiles[i] = 2 * i;
                    }
                }

                bool kingTilesMatch = false;

                for(int i = 0; i < usableTilesPerRow &&
                    !kingTilesMatch; i++)
                {
                    if(xCoord == xTiles[i])
                    {
                        kingTilesMatch = true;
                    }
                }

                if(kingTilesMatch)
                {
                    if(isMan(xCoord, yCoord))
                    {
                        captured[enemyColor]->pop();

                        if(pieceColor == WHITE)
                        {
                            grid[xCoord][yCoord] = WHITE_KING;
                        }
                        else
                        {
                            grid[xCoord][yCoord] = BLACK_KING;
                        }

                        return true;
                    }
                }
            }
        }

        return false;
    } // end createKing
} // end CheckersSzeto