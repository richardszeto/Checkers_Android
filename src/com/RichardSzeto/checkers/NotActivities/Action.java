/** Class to hold an action with start and end coordinates
  *
  * @author Richard Szeto
  *
  *
  */

package com.RichardSzeto.checkers.NotActivities;


public class Action
{
    protected int startX;
    protected int startY;
    protected int endX;
    protected int endY;
    
    public Action()
    {
        startX = 0;
        startY = 0;
        endX = 0;
        endY = 0;
    }
    
    public Action(int newStartX, int newStartY,
        int newEndX, int newEndY)
    {
        startX = newStartX;
        startY = newStartY;
        endX = newEndX;
        endY = newEndY;
    }
    
    public Action(final Action action)
    {
        startX = action.startX;
        
        startY = action.startY;
        
        endX = action.endX;
        
        endY = action.endY;
    }
    
    public int getStartX()
    {
        return startX;
    }
    
    public int getStartY()
    {
        return startY;
    }
    
    public int getEndX()
    {
        return endX;
    }
    
    public int getEndY()
    {
        return endY;
    }
    
    public void setStartX(int newStartX)
    {
        startX = newStartX;
    }
    
    public void setStartY(int newStartY)
    {
        startY = newStartY;
    }
    
    public void setEndX(int newEndX)
    {
        endX = newEndX;
    }
    
    public void setEndY(int newEndY)
    {
        endY = newEndY;
    }
}