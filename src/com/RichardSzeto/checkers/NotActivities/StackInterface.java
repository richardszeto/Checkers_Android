package com.RichardSzeto.checkers.NotActivities;

public interface StackInterface<T>
{
    public T peek();
    
    public T pop();
    
    public boolean push(T newElement);
    
    public int getLength();
    
    public boolean isEmpty();
    
    public void clear();
}
