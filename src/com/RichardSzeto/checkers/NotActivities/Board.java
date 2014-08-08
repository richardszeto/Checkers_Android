/** Class that holds the board, all the pieces, and the state of the game
  *
  * @author Richard Szeto
  *
  *
  */

package com.RichardSzeto.checkers.NotActivities;

import java.lang.reflect.InvocationTargetException;

public class Board
{
    protected Piece[][] grid;
    protected ArrayStack<Piece>[] captured;
    protected Color turn;
    protected boolean isMultiJump;
    protected boolean needToCapture;
    protected boolean needToMove;
    
    @SuppressWarnings("unchecked")
    public Board()
    {
        turn = Color.WHITE;
        
        isMultiJump = false;
        
        needToCapture = false;
        
        needToMove = true;
        
        grid = new Piece[Globals.GRID_LENGTH][Globals.GRID_LENGTH];
        
        Object[] tempArray = new Object[Globals.NUMBER_PLAYERS];
        
        tempArray[Color.WHITE.getValue()] = new ArrayStack<Piece>(Globals.PLAYER_PIECES);
        
        tempArray[Color.BLACK.getValue()] = new ArrayStack<Piece>(Globals.PLAYER_PIECES);
        
        captured = (ArrayStack<Piece>[]) tempArray;
        
        for(int i = 0; i < Globals.GRID_LENGTH; i++)
        {
            for(int j = 0; j < Globals.GRID_LENGTH; j++)
            {
                grid[i][j] = Piece.NONE;
            }
        }
        
        initializePieces();
    }
    
    @SuppressWarnings("unchecked")
    public Board(final Board board) throws NoSuchMethodException, 
        InstantiationException, IllegalAccessException, IllegalArgumentException, 
        InvocationTargetException
    {
        turn = board.turn;
        
        isMultiJump = board.isMultiJump;
        
        needToCapture = board.needToCapture;
        
        needToMove = board.needToMove;
        
        grid = new Piece[Globals.GRID_LENGTH][Globals.GRID_LENGTH];
        
        for(int i = 0; i < Globals.GRID_LENGTH; i++)
        {
            for(int j = 0; j < Globals.GRID_LENGTH; j++)
            {
                grid[i][j] = board.grid[i][j];
            }
        }
        
        Object[] tempArray = new Object[Globals.NUMBER_PLAYERS];
        
        tempArray[Color.WHITE.getValue()] = new ArrayStack<Piece>(
                board.captured[Color.WHITE.getValue()]);
        
        tempArray[Color.BLACK.getValue()] = new ArrayStack<Piece>(
                board.captured[Color.BLACK.getValue()]);
        
        captured = (ArrayStack<Piece>[]) tempArray;
    }
    
    public void clear()
    {
        turn = Color.WHITE;
        
        isMultiJump = false;
        
        needToCapture = false;
        
        needToMove = true;
        
        for(int i = 0; i < Globals.GRID_LENGTH; i++)
        {
            for(int j = 0; j < Globals.GRID_LENGTH; j++)
            {
                grid[i][j] = Piece.NONE;
            }
        }
        
        captured[Color.WHITE.getValue()].clear();
        
        captured[Color.BLACK.getValue()].clear();
        
        initializePieces();
    }
    
    public void scanCapture()
    {
        for(int startingIndex = 0; startingIndex < 2; startingIndex++)
        {
            for(int i = startingIndex; i < Globals.GRID_LENGTH; i += 2)
            {
                for(int j = startingIndex; j < Globals.GRID_LENGTH; j += 2)
                {
                    if(isPieceColor(turn, i, j))
                    {
                        if((isPieceColor(Color.WHITE, i, j) && isMan(i, j)) ||
                            isKing(i, j))
                        {
                            if(canCapture(i, j, Corner.TOP_LEFT) ||
                                canCapture(i, j, Corner.TOP_RIGHT))
                            {
                                needToCapture = true;
                                return;
                            }
                        }

                        if((isPieceColor(Color.BLACK, i, j) && isMan(i, j)) ||
                            isKing(i, j))
                        {
                            if(canCapture(i, j, Corner.BOTTOM_LEFT) ||
                                canCapture(i, j, Corner.BOTTOM_RIGHT))
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
    
    public void scanMove()
    {
        for(int startingIndex = 0; startingIndex < 2; startingIndex++)
        {
            for(int i = startingIndex; i < Globals.GRID_LENGTH; i += 2)
            {
                for(int j = startingIndex; j < Globals.GRID_LENGTH; j += 2)
                {
                    if(isPieceColor(turn, i, j))
                    {
                        if((isPieceColor(Color.WHITE, i, j) && isMan(i, j)) ||
                            isKing(i, j))
                        {
                            if(canMove(i, j, Corner.TOP_LEFT) ||
                                canMove(i, j, Corner.TOP_RIGHT))
                            {
                                needToMove = true;
                                return;
                            }
                        }

                        if((isPieceColor(Color.BLACK, i, j) && isMan(i, j)) ||
                            isKing(i, j))
                        {
                            if(canMove(i, j, Corner.BOTTOM_LEFT) ||
                                canMove(i, j, Corner.BOTTOM_RIGHT))
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
    
    public boolean isEndGame()
    {
        if(!needToCapture && !needToMove)
        {
            return true;
        }

        return false;
    }
    
    public boolean move(int startX, int startY,
            int endX, int endY)
    {
        boolean xBounds = startX >= 0 && startX < Globals.GRID_LENGTH &&
                endX >= 0 && endX < Globals.GRID_LENGTH;

        boolean yBounds = startY >= 0 && startY < Globals.GRID_LENGTH &&
                endY >= 0 && endY < Globals.GRID_LENGTH;

        boolean sourceExists = grid[startX][startY] != Piece.NONE;

        boolean endIsNone = grid[endX][endY] == Piece.NONE;

        boolean diagonalMove = Math.abs(startX - endX) == Math.abs(startY - endY);

        boolean correctTurn = false;

        boolean startIsMan = false;

        boolean startIsKing = false;

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
    
    public Piece getPiece(int x, int y)
    {
        return grid[x][y];
    }
    
    public Color getTurn()
    {
        return turn;
    }
    
    public boolean getIsMultiJump()
    {
        return isMultiJump;
    }

    protected boolean isPieceColor(Color color, int xCoord, int yCoord)
    {
        return ((color == Color.WHITE && (grid[xCoord][yCoord] == Piece.WHITE_MAN ||
                grid[xCoord][yCoord] == Piece.WHITE_KING)) || (color == Color.BLACK &&
                (grid[xCoord][yCoord] == Piece.BLACK_MAN || 
                    grid[xCoord][yCoord] == Piece.BLACK_KING)));
    }
    
    protected boolean isMan(int xCoord, int yCoord)
    {
        return (grid[xCoord][yCoord] == Piece.WHITE_MAN ||
                grid[xCoord][yCoord] == Piece.BLACK_MAN);
    }
    
    protected boolean isKing(int xCoord, int yCoord)
    {
        return (grid[xCoord][yCoord] == Piece.WHITE_KING ||
                grid[xCoord][yCoord] == Piece.BLACK_KING);
    }
    
    protected boolean canCapture(int xCoord, int yCoord,
        Corner corner)
    {
        Color enemyColor;

        if(turn == Color.WHITE)
        {
            enemyColor = Color.BLACK;
        }
        else // turn == Color.BLACK
        {
            enemyColor = Color.WHITE;
        }

        if(isPieceColor(turn, xCoord, yCoord))
        {
            if(corner == Corner.TOP_LEFT)
            {
                return (xCoord - 1 >= 0 &&
                    yCoord + 1 < Globals.GRID_LENGTH &&
                    isPieceColor(enemyColor, xCoord - 1, yCoord + 1) &&
                    xCoord - 2 >= 0 &&
                    yCoord + 2 < Globals.GRID_LENGTH &&
                    grid[xCoord - 2][yCoord + 2] == Piece.NONE);
            }
            else if(corner == Corner.TOP_RIGHT)
            {
                return (xCoord + 1 < Globals.GRID_LENGTH &&
                    yCoord + 1 < Globals.GRID_LENGTH &&
                    isPieceColor(enemyColor, xCoord + 1, yCoord + 1) &&
                    xCoord + 2 < Globals.GRID_LENGTH &&
                    yCoord + 2 < Globals.GRID_LENGTH &&
                    grid[xCoord + 2][yCoord + 2] == Piece.NONE);
            }
            else if(corner == Corner.BOTTOM_LEFT)
            {
                return (xCoord - 1 >= 0 &&
                    yCoord - 1 >= 0 &&
                    isPieceColor(enemyColor, xCoord - 1, yCoord - 1) &&
                    xCoord - 2 >= 0 &&
                    yCoord - 2 >= 0 &&
                    grid[xCoord - 2][yCoord - 2] == Piece.NONE);
            }
            else if(corner == Corner.BOTTOM_RIGHT)
            {
                return (xCoord + 1 < Globals.GRID_LENGTH &&
                    yCoord - 1 >= 0 &&
                    isPieceColor(enemyColor, xCoord + 1, yCoord - 1) &&
                    xCoord + 2 < Globals.GRID_LENGTH &&
                    yCoord - 2 >= 0 &&
                    grid[xCoord + 2][yCoord - 2] == Piece.NONE);
            }
        }

        return false;
    }
    
    protected boolean canMove(int xCoord, int yCoord,
        Corner corner)
    {
        if(isPieceColor(turn, xCoord, yCoord))
        {
            if(corner == Corner.TOP_LEFT)
            {
                return (xCoord - 1 >= 0 &&
                    yCoord + 1 < Globals.GRID_LENGTH &&
                    grid[xCoord - 1][yCoord + 1] == Piece.NONE);
            }
            else if(corner == Corner.TOP_RIGHT)
            {
                return (xCoord + 1 < Globals.GRID_LENGTH &&
                    yCoord + 1 < Globals.GRID_LENGTH &&
                    grid[xCoord + 1][yCoord + 1] == Piece.NONE);
            }
            else if(corner == Corner.BOTTOM_LEFT)
            {
                return (xCoord - 1 >= 0 &&
                    yCoord - 1 >= 0 &&
                    grid[xCoord - 1][yCoord - 1] == Piece.NONE);
            }
            else if(corner == Corner.BOTTOM_RIGHT)
            {
                return (xCoord + 1 < Globals.GRID_LENGTH &&
                    yCoord - 1 >= 0 &&
                    grid[xCoord + 1][yCoord - 1] == Piece.NONE);
            }
        }

        return false;
    }
    
    protected void movePiece(int startX, int startY,
            int endX, int endY)
    {
        grid[endX][endY] = grid[startX][startY];

        grid[startX][startY] = Piece.NONE;
    }
    
    protected boolean moveMan(int startX, int startY,
            int endX, int endY)
    {
        int absXMove;
        int diffYMove;
        int kingYMove;

        int absXCapture;
        int diffYCapture;

        Color enemyColor;

        if(turn == Color.WHITE)
        {
            absXMove = 1;
            diffYMove = -1;
            kingYMove = 7;

            absXCapture = 2;
            diffYCapture = -2;

            enemyColor = Color.BLACK;
        }
        else // turn == Color.BLACK
        {
            absXMove = 1;
            diffYMove = 1;
            kingYMove = 0;

            absXCapture = 2;
            diffYCapture = 2;

            enemyColor = Color.WHITE;
        }

        if(grid[endX][endY] == Piece.NONE)
        {
            if (Math.abs(startX - endX) == absXMove && 
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
            else if (Math.abs(startX - endX) == absXCapture && 
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

                    boolean changeTurns = true;

                    if (endY == kingYMove)
                    {
                        createKing(endX, endY);
                    }
                    else if (isPieceColor(Color.WHITE, endX, endY) &&
                        (canCapture(endX, endY, Corner.TOP_LEFT) ||
                            canCapture(endX, endY, Corner.TOP_RIGHT)))
                    {
                        // allow multi-jump

                        changeTurns = false;

                        isMultiJump = true;
                    }
                    else if (isPieceColor(Color.BLACK, endX, endY) &&
                        (canCapture(endX, endY, Corner.BOTTOM_LEFT) ||
                            canCapture(endX, endY, Corner.BOTTOM_RIGHT)))
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
    
    protected boolean moveKing(int startX, int startY,
            int endX, int endY)
    {
        Color enemyColor;

        if(turn == Color.WHITE)
        {
            enemyColor = Color.BLACK;
        }
        else // turn == Color.BLACK
        {
            enemyColor = Color.WHITE;
        }

        if(grid[endX][endY] == Piece.NONE)
        {
            if(Math.abs(startX - endX) == 1 && 
                Math.abs(startY - endY) == 1 && 
                !isMultiJump &&
                !needToCapture)
            {
                movePiece(startX, startY, endX, endY);

                turn = enemyColor;

                return true;
            }
            else if(Math.abs(startX - endX) == 2 && 
                Math.abs(startY - endY) == 2 &&
                needToCapture)
            {
                isMultiJump = false;

                int eatX = (startX + endX) / 2;
                int eatY = (startY + endY) / 2;

                if(isPieceColor(enemyColor, eatX, eatY))
                {
                    movePiece(startX, startY, endX, endY);

                    moveToCaptured(eatX, eatY);

                    boolean changeTurns = true;

                    if(canCapture(endX, endY, Corner.TOP_LEFT) ||
                        canCapture(endX, endY, Corner.TOP_RIGHT) ||
                        canCapture(endX, endY, Corner.BOTTOM_LEFT) ||
                        canCapture(endX, endY, Corner.BOTTOM_RIGHT))
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
    
    protected void initializePieces()
    {
        for (int i = 0; i < Globals.GRID_LENGTH; i += 2)
        {
            for (int j = 0; j < 3; j += 2)
            {
                grid[i][j] = Piece.WHITE_MAN;
            } // end for
        } // end for

        for (int i = 1; i < Globals.GRID_LENGTH; i += 2)
        {
            grid[i][1] = Piece.WHITE_MAN;
        } // end for

        for (int i = 1; i < Globals.GRID_LENGTH; i += 2)
        {
            for (int j = 5; j < Globals.GRID_LENGTH; j += 2)
            {
                grid[i][j] = Piece.BLACK_MAN;
            } // end for
        } // end for

        for (int i = 0; i < Globals.GRID_LENGTH; i += 2)
        {
            grid[i][6] = Piece.BLACK_MAN;
        } // end for
    }
    
    protected void moveAllToCaptured()
    {
        for(int startingIndex = 0; startingIndex < 2; startingIndex++)
        {
            for(int i = startingIndex; i < Globals.GRID_LENGTH; i += 2)
            {
                for(int j = startingIndex; j < Globals.GRID_LENGTH; j += 2)
                {
                    if(grid[i][j] != Piece.NONE)
                    {
                        moveToCaptured(i, j);
                    }
                }
            }
        }
    }
    
    protected boolean moveToCaptured(int xCoord, int yCoord)
    {
        Color pieceColor;

        Color enemyColor;

        if(grid[xCoord][yCoord] != Piece.NONE)
        {
            if(isPieceColor(Color.WHITE, xCoord, yCoord))
            {
                pieceColor = Color.WHITE;
            }
            else
            {
                pieceColor = Color.BLACK;
            }

            if(pieceColor == Color.WHITE)
            {
                enemyColor = Color.BLACK;
            }
            else // pieceColor == Color.BLACK
            {
                enemyColor = Color.WHITE;
            }

            if(captured[enemyColor.getValue()].getLength() + 1 < Globals.PLAYER_PIECES &&
                isKing(xCoord, yCoord))
            {
                captured[enemyColor.getValue()].push(grid[xCoord][yCoord]);

                captured[enemyColor.getValue()].push(grid[xCoord][yCoord]);

                grid[xCoord][yCoord] = Piece.NONE;

                return true;
            }
            else if(captured[enemyColor.getValue()].getLength() < Globals.PLAYER_PIECES &&
                isMan(xCoord, yCoord))
            {
                captured[enemyColor.getValue()].push(grid[xCoord][yCoord]);

                grid[xCoord][yCoord] = Piece.NONE;

                return true;
            }
        }

        return false;
    }
    
    protected boolean createKing(int xCoord, int yCoord)
    {
        Color pieceColor;

        Color enemyColor;

        if(grid[xCoord][yCoord] != Piece.NONE)
        {
            if(isPieceColor(Color.WHITE, xCoord, yCoord))
            {
                pieceColor = Color.WHITE;
            }
            else
            {
                pieceColor = Color.BLACK;
            }

            if(pieceColor == Color.WHITE)
            {
                if(yCoord != 7)
                {
                    return false;
                }

                enemyColor = Color.BLACK;
            }
            else // pieceColor == Color.BLACK
            {
                if(yCoord != 0)
                {
                    return false;
                }

                enemyColor = Color.WHITE;
            }

            if(captured[enemyColor.getValue()].getLength() > 0)
            {
                final int usableTilesPerRow = 4;

                int[] xTiles = new int[usableTilesPerRow];

                if(pieceColor == Color.WHITE)
                {
                    for(int i = 0; i < usableTilesPerRow; i++)
                    {
                        xTiles[i] = (2 * i) + 1;
                    }
                }
                else if(pieceColor == Color.BLACK)
                {
                    for(int i = 0; i < usableTilesPerRow; i++)
                    {
                        xTiles[i] = 2 * i;
                    }
                }

                boolean kingTilesMatch = false;

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
                        captured[enemyColor.getValue()].pop();

                        if(pieceColor == Color.WHITE)
                        {
                            grid[xCoord][yCoord] = Piece.WHITE_KING;
                        }
                        else
                        {
                            grid[xCoord][yCoord] = Piece.BLACK_KING;
                        }

                        return true;
                    }
                }
            }
        }

        return false;
    }  
}