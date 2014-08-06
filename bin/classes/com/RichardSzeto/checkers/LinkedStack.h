/** Stack of pointers implemented by a linked list
  *
  * @author Richard
  *
  *
  *
  */

#ifndef LINKEDSTACK_H
#define LINKEDSTACK_H

#include "Node.h"
#include "Node.cpp"

namespace DataStructureSzeto
{
    template<class T>
    class LinkedStack
    {
    public:
        LinkedStack();
        LinkedStack(const LinkedStack<T> &linkedStackObject);
        ~LinkedStack();
        LinkedStack<T>& operator =(const LinkedStack<T> &rightSide);
        T* peek();
        T* pop();
        void push(T *newElement);
        int getLength() const;
        bool isEmpty() const;
        void clear();
        void deleteNodes();

    protected:
        Node<T> *top;
        int length;
    };
}

#endif