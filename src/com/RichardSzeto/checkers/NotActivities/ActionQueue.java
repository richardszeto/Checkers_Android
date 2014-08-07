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
	
	public ActionQueue(ActionQueue actionQueue)
	{
	    queue = new LinkedQueue<Action>((LinkedQueue<Action>) actionQueue.queue);
	}
	
    public Action getFront()
    {
        return queue.getFront();
    }
    
    public Action removeFront()
    {
        return queue.removeFront();
    }
    
    public boolean addToBack(Action newElement)
    {
        return queue.addToBack(newElement);
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