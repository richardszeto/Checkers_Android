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
    
    public void printBoard()
    {
        
    }
    
    public void printTurn()
    {
        
    }
    
    public boolean getIsMultiJump()
    {
        
    }

    protected boolean isPieceColor(Color color, int xCoord, int yCoord)
    {
        
    }
    
    protected boolean isMan(int xCoord, int yCoord)
    {
        
    }
    
    protected boolean isKing(int xCoord, int yCoord)
    {
        
    }
    
    protected boolean canCapture(int xCoord, int yCoord,
        Corner corner)
    {
        
    }
    
    protected boolean canMove(int xCoord, int yCoord,
        Corner corner)
    {
        
    }
    
    protected void movePiece(int startX, int startY,
            int endX, int endY)
    {
        
    }
    
    protected boolean moveMan(int startX, int startY,
            int endX, int endY)
    {
        
    }
    
    protected boolean moveKing(int startX, int startY,
            int endX, int endY)
    {
        
    }
    
    protected void initializePieces()
    {
        
    }
    
    protected void moveAllToCaptured()
    {
        
    }
    
    protected boolean moveToCaptured(int xCoord, int yCoord)
    {
        
    }
    
    protected boolean createKing(int xCoord, int yCoord)
    {
        
    }  
}