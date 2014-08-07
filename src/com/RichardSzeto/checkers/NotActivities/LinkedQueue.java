/** Queue of pointers implemented by a linked list
  *
  * @author Richard
  *
  *
  *
  */

package com.RichardSzeto.checkers.NotActivities;


public class LinkedQueue<T> implements QueueInterface<T>
{
    protected Node<T> front;
    protected Node<T> back;
    protected int length;
    
    public LinkedQueue()
    {
        front = null;
        
        back = null;
        
        length = 0;
    }
    
    public LinkedQueue(final LinkedQueue<T> linkedQueue)
    {
        length = linkedQueue.length;
        
        front = null;
        
        back = null;
        
        Node<T> otherNode = linkedQueue.front;
        
        if(otherNode != null)
        {
            front = new Node<T>(otherNode.getData());
            
            back = front;
            
            otherNode = otherNode.getLink();
        }
        
        while(otherNode != null)
        {
            back.setLink(new Node<T>(otherNode.getData()));
            
            back = back.getLink();
            
            otherNode = otherNode.getLink();
        }
    }
    
    public T getFront()
    {
        if(!isEmpty())
        {
            return front.getData();
        }
        
        return null;
    }
    
    public T removeFront()
    {
        if(!isEmpty())
        {
            T result = front.getData();
            
            Node<T> next = front.getLink();
            
            front.setLink(null);
            
            front = next;
            
            if(front == null)
            {
                back = null;
            }
            
            length--;
            
            return result;
        }
        
        return null;
    }
    
    public boolean addToBack(T newElement)
    {
        if(newElement != null)
        {
            if(isEmpty())
            {
                front = new Node<T>(newElement);
                
                back = front;
            }
            else
            {
                back.setLink(new Node<T>(newElement));
                
                back = back.getLink();
            }
            
            length++;
            
            return true;
        }
        
        return false;
    }
    
    public int getLength()
    {
        return length;
    }
    
    public boolean isEmpty()
    {
        return front == null &&
                back == null &&
                length == 0;
    }
    
    public void clear()
    {
        Node<T> next;
        
        while(front != null)
        {
            next = front.getLink();
            
            front.setLink(null);
            
            front = next;
        }
        
        back = null;
        
        length = 0;
    }
}