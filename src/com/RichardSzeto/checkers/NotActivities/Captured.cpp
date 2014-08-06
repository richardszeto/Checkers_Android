/** Stack that holds captured pieces, implemented by an array
  *
  * @author Richard Szeto
  *
  *
  *
  */

#include <cstddef>
#include "Captured.h"

namespace CheckersSzeto
{
    using DataStructureSzeto::ArrayStack;

    using DataStructureSzeto::DEFAULT_STACK_SIZE;

    Captured::Captured() 
    {
        length = 0;

        capacity = DEFAULT_STACK_SIZE;

        stack = new Piece[capacity];

        for(int i = 0; i < capacity; i++)
        {
            stack[i] = NONE;
        }
    }

    Captured::Captured(int newCapacity) 
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

        stack = new Piece[capacity];

        for(int i = 0; i < capacity; i++)
        {
            stack[i] = NONE;
        }
    }

    Captured::Captured(const Captured &capturedObject)
    {
        capacity = capturedObject.capacity;

        length = capturedObject.length;

        stack = new Piece[capacity];

        for(int i = 0; i < capacity; i++)
        {
            stack[i] = NONE;
        }

        for(int i = 0; i < length; i++)
        {
            stack[i] = capturedObject.stack[i];
        }
    }

    Captured::~Captured()
    {
        clear();

        delete [] stack;

        stack = NULL;
    }

    Captured& Captured::operator =(const Captured &rightSide)
    {
        clear();

        if(stack != NULL)
        {
            delete [] stack;

            stack = NULL;
        }
        
        capacity = rightSide.capacity;

        length = rightSide.length;

        stack = new Piece[capacity];

        for(int i = 0; i < capacity; i++)
        {
            stack[i] = NONE;
        }

        for(int i = 0; i < length; i++)
        {
            stack[i] = rightSide.stack[i];
        }

        return *this;
    }

    Piece Captured::peek()
    {
        if(!isEmpty())
        {
            return stack[length - 1];
        }

        return NONE;
    }

    Piece Captured::pop()
    {
        if(!isEmpty())
        {
            Piece result = stack[length - 1];

            stack[length - 1] = NONE;

            length--;

            return result;
        }

        return NONE;
    }

    void Captured::clear()
    {
        for(int i = 0; i < length; i++)
        {
            stack[i] = NONE;
        }

        length = 0;
    }

    void Captured::doubleCapacity()
    {
        int newCapacity = 2 * capacity;
        Piece *newStack = new Piece[newCapacity];

        for(int i = 0; i < newCapacity; i++)
        {
            newStack[i] = NONE;
        }

        for (int i = 0; i < length; i++)
        {
            newStack[i] = stack[i];
        }

        capacity = newCapacity;

        delete [] stack;

        stack = newStack;
    }
}