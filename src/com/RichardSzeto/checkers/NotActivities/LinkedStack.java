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
    
    public LinkedStack(final LinkedStack<T> linkedStack)
    {
        length = linkedStack.length;
        
        top = null;
        
        Node<T> otherNode = linkedStack.top;
        
        Node<T> bottom = null;
        
        if(otherNode != null)
        {
            top = new Node<T>(otherNode.getData());
            
            bottom = top;
            
            otherNode = otherNode.getLink();
        }
        
        while(otherNode != null)
        {
            bottom.setLink(new Node<T>(otherNode.getData()));
            
            bottom = bottom.getLink();
            
            otherNode = otherNode.getLink();
        }
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
    
    public boolean push(T newElement)
    {
        if(newElement != null)
        {
            if(isEmpty())
            {
                top = new Node<T>(newElement);
            }
            else
            {
                top = new Node<T>(newElement, top);
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
