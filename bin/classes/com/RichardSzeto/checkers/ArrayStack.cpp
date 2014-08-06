/** Stack implemented by an array
  *
  * @author Richard Szeto
  *
  *
  *
  */

#ifndef ARRAYSTACK_CPP
#define ARRAYSTACK_CPP

#include <cstddef>
#include "ArrayStack.h"

namespace DataStructureSzeto
{
    const int DEFAULT_STACK_SIZE = 50;

    template<class T>
    ArrayStack<T>::ArrayStack()
    {
        length = 0;

        capacity = DEFAULT_STACK_SIZE;

        stack = new T[capacity];
    }

    template<class T>
    ArrayStack<T>::ArrayStack(int newCapacity)
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

        stack = new T[capacity];
    }

    template<class T>
    ArrayStack<T>::ArrayStack(const ArrayStack<T> &arrayStackObject)
    {
        capacity = arrayStackObject.capacity;

        length = arrayStackObject.length;

        stack = new T[capacity];

        for(int i = 0; i < length; i++)
        {
            stack[i] = arrayStackObject.stack[i];
        }
    }

    template<class T>
    ArrayStack<T>::~ArrayStack()
    {
        clear();

        delete [] stack;

        stack = NULL;
    }

    template<class T>
    ArrayStack<T>& ArrayStack<T>::operator =(const ArrayStack<T> &rightSide)
    {
        clear();

        if(stack != NULL)
        {
            delete [] stack;

            stack = NULL;
        }

        capacity = rightSide.capacity;

        length = rightSide.length;

        stack = new T[capacity];

        for(int i = 0; i < length; i++)
        {
            stack[i] = rightSide.stack[i];
        }

        return *this;
    }

    template<class T>
    T ArrayStack<T>::peek()
    {
        return stack[length - 1];
    }

    template<class T>
    T ArrayStack<T>::pop()
    {
        T result = stack[length - 1];

        length--;

        return result;
    }

    template<class T>
    void ArrayStack<T>::push(T newElement)
    {
        if(length == capacity)
        {
            doubleCapacity();
        }

        stack[length] = newElement;

        length++;
    }

    template<class T>
    int ArrayStack<T>::getLength() const
    {
        return length;
    }

    template<class T>
    int ArrayStack<T>::getCapacity() const
    {
        return capacity;
    }

    template<class T>
    bool ArrayStack<T>::isEmpty() const
    {
        return length == 0;
    }

    template<class T>
    void ArrayStack<T>::clear()
    {
        length = 0;
    }

    template<class T>
    void ArrayStack<T>::doubleCapacity()
    {
        int newCapacity = 2 * capacity;
        T *newStack = new T[newCapacity];

        for (int i = 0; i < length; i++)
        {
            newStack[i] = stack[i];
        }

        capacity = newCapacity;

        delete [] stack;

        stack = newStack;
    }
}

#endif