package com.RichardSzeto.checkers.NotActivities;

public enum Color
{
    WHITE(0), 
    BLACK(1);
    
    private final int value;
    
    private Color(final int newValue)
    {
        value = newValue;
    }
    
    public int getValue()
    {
        return value;
    }
}
