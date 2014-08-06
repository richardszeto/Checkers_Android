/** Stack of pointers implemented by a linked list
  *
  * @author Richard
  *
  *
  *
  */

#ifndef LINKEDSTACK_CPP
#define LINKEDSTACK_CPP

#include <cstddef>
#include "LinkedStack.h"

namespace DataStructureSzeto
{
    template<class T>
    LinkedStack<T>::LinkedStack()
    {
        top = NULL;

        length = 0;
    }

    template<class T>
    LinkedStack<T>::LinkedStack(const LinkedStack<T> &linkedStackObject)
    {
        Node<T> *currentNode;

        Node<T> *otherNode;

        top = NULL;

        otherNode = linkedStackObject.top;

        if(otherNode != NULL)
        {
            top = new Node<T>(otherNode->getData());

            currentNode = top;

            otherNode = otherNode->getLink();
        }

        while(otherNode != NULL)
        {
            currentNode->setLink(new Node<T>(otherNode->getData()));

            currentNode = currentNode->getLink();

            otherNode = otherNode->getLink();
        }

        length = linkedStackObject.length;
    }

    template<class T>
    LinkedStack<T>::~LinkedStack()
    {
        clear();
    }

    template<class T>
    LinkedStack<T>& LinkedStack<T>::operator =(const LinkedStack<T> &rightSide)
    {
        clear();

        Node<T> *currentNode;

        Node<T> *otherNode;

        top = NULL;

        otherNode = rightSide.top;

        if(otherNode != NULL)
        {
            top = new Node<T>(otherNode->getData());

            currentNode = top;

            otherNode = otherNode->getLink();
        }

        while(otherNode != NULL)
        {
            currentNode->setLink(new Node<T>(otherNode->getData()));

            currentNode = currentNode->getLink();

            otherNode = otherNode->getLink();
        }

        length = rightSide.length;

        return *this;
    }

    template<class T>
    T* LinkedStack<T>::peek()
    {
        if(!isEmpty())
        {
            return top->getData();
        }

        return NULL;
    }

    template<class T>
    T* LinkedStack<T>::pop()
    {
        if(!isEmpty())
        {
            T *result;

            result = top->getData();

            Node<T> *nextNode;

            nextNode = top->getLink();

            delete top;

            top = nextNode;

            length--;

            return result;
        }

        return NULL;
    }

    template<class T>
    void LinkedStack<T>::push(T *newElement)
    {
        top = new Node<T>(newElement, top);

        length++;
    }

    template<class T>
    int LinkedStack<T>::getLength() const
    {
        return length;
    }

    template<class T>
    bool LinkedStack<T>::isEmpty() const
    {
        return (top == NULL && length == 0);
    }

    template<class T>
    void LinkedStack<T>::clear()
    {
        if(!isEmpty())
        {
            Node<T> *nextNode;

            while(top != NULL)
            {
                nextNode = top->getLink();

                top->clear();

                delete top;

                top = nextNode;
            }

            length = 0;
        }
    }

    template<class T>
    void LinkedStack<T>::deleteNodes()
    {
        if(!isEmpty())
        {
            Node<T> *nextNode;

            while(top != NULL)
            {
                nextNode = top->getLink();

                top->deleteData();

                delete top;

                top = nextNode;
            }

            length = 0;
        }
    }
}

#endif