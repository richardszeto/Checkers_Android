package com.RichardSzeto.checkers.NotActivities;

public interface QueueInterface<T>
{
    public T getFront();
    
    public T removeFront();
    
    public boolean addToBack(T newElement);
    
    public int getLength();
    
    public boolean isEmpty();
    
    public void clear();
}
