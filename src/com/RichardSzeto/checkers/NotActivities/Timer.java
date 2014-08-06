/** Class that holds a timer
  *
  * @author Richard Szeto
  *
  *
  */

package com.RichardSzeto.checkers.NotActivities;

public class Timer
{
    protected boolean resetted;
    protected boolean running;
    protected long beg;
    protected long end;
    
	public Timer()
	{
	    resetted = true;
        running = false;
        beg = 0;
        end = 0;
	}

	public void start()
	{
	    if(!running)
        {
            if(resetted)
            {
                beg = System.currentTimeMillis();
            }
            else
            {
                beg = beg - end - System.currentTimeMillis();
            }

            running = true;

            resetted = true;
        }
	}
	
	public void stop()
	{
	    if(running)
        {
            end = System.currentTimeMillis();

            running = false;
        }
	}
	
	public void reset()
	{
	    boolean wereRunning = running;

        if(wereRunning)
        {
            stop();
        }

        resetted = true;

        beg = 0;

        end = 0;

        if(wereRunning)
        {
            start();
        }
	}
	
	public boolean isRunning()
	{
	    return running;
	}
	
	public long getTime()
	{
	    if(running)
        {
            return System.currentTimeMillis() - beg;
        }
        else
        {
            return end - beg;
        }
	}
	
	public boolean isOver(long milliseconds)
	{
	    return milliseconds <= getTime();
	}
}
