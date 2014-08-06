/** Queue of Action objects, implemented by a linked list
  *
  * @author Richard Szeto
  *
  *
  *
  */

package com.RichardSzeto.checkers.NotActivities;

class ActionQueue implements QueueInterface<Action>
{
    protected QueueInterface<Action> queue;
    
	public ActionQueue()
	{
	    queue = new LinkedQueue<Action>();
	}
	
    public Action getFront()
    {
        return queue.getFront();
    }
    
    public Action removeFront()
    {
        return queue.removeFront();
    }
    
    public void addToBack(Action newElement)
    {
        queue.addToBack(newElement);
    }
    
    public int getLength()
    {
        return queue.getLength();
    }
    
    public boolean isEmpty()
    {
        return queue.isEmpty();
    }
    
    public void clear()
    {
        queue.clear();
    }
}