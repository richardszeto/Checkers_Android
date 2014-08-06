/** Stack implemented by an array
  *
  * @author Richard Szeto
  *
  *
  */

package com.RichardSzeto.checkers.NotActivities;

public class ArrayStack<T> implements StackInterface<T>
{
    protected final static int DEFAULT_STACK_SIZE = 50;
    
    protected T[] stack;
    protected int capacity;
    protected int length;
    
    @SuppressWarnings("unchecked")
    public ArrayStack()
    {
        length = 0;

        capacity = DEFAULT_STACK_SIZE;
        
        stack = (T[]) new Object[capacity];
    }
    
    @SuppressWarnings("unchecked")
    public ArrayStack(int newCapacity)
    {
        length = 0;

        if(newCapacity > 0)
        {
            capacity = newCapacity;
        }
        else
        {
            capacity = DEFAULT_STACK_SIZE;
        }

        stack = (T[]) new Object[capacity];
    }
    
    public T peek()
    {
        if(!isEmpty())
        {
            return stack[length - 1];
        }
        
        return null;
    }
    
    public T pop()
    {
        if(!isEmpty())
        {
            T result = stack[length - 1];
            
            stack[length - 1] = null;

            length--;

            return result;
        }
        
        return null;
    }
    
    public void push(T newElement)
    {
        if(length == capacity)
        {
            doubleCapacity();
        }

        stack[length] = newElement;

        length++;
    }
    
    public int getLength()
    {
        return length;
    }
    
    public int getCapacity()
    {
        return capacity;
    }
    
    public boolean isEmpty()
    {
        return length == 0;
    }
    
    public void clear()
    {
        for(int i = 0; i < length; i++)
        {
            stack[i] = null;
        }
        
        length = 0;
    }
    
    protected void doubleCapacity()
    {
        int newCapacity = 2 * capacity;
        
        @SuppressWarnings("unchecked")
        T[] newStack = (T[]) new Object[newCapacity];

        for (int i = 0; i < length; i++)
        {
            newStack[i] = stack[i];
            
            stack[i] = null;
        }

        capacity = newCapacity;

        stack = newStack;
    }
}