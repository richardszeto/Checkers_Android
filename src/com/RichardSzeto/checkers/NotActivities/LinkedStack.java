/** Stack of pointers implemented by a linked list
  *
  * @author Richard
  *
  *
  *
  */

package com.RichardSzeto.checkers.NotActivities;

public class LinkedStack<T> implements StackInterface<T>
{
    protected Node<T> top;
    protected int length;
    
    public LinkedStack()
    {
        top = null;
        
        length = 0;
    }
    
    public T peek()
    {
        if(!isEmpty())
        {
            return top.getData();
        }
        
        return null;
    }
    
    public T pop()
    {
        if(!isEmpty())
        {
            T result = top.getData();
            
            Node<T> next = top.getLink();
            
            top.setLink(null);
            
            top = next;
            
            length--;
            
            return result;
        }
        
        return null;
    }
    
    public void push(T newElement)
    {
        if(isEmpty())
        {
            top = new Node<T>(newElement);
            
            length++;
        }
        else
        {
            top = new Node<T>(newElement, top);
            
            length++;
        }
    }
    
    public int getLength()
    {
        return length;
    }
    
    public boolean isEmpty()
    {
        return top == null &&
                length == 0;
    }
    
    public void clear()
    {
        Node<T> next;
        
        while(top != null)
        {
            next = top.getLink();
            
            top.setLink(null);
            
            top = next;
        }
        
        length = 0;
    }
}
