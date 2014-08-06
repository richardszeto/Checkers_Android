/** Stack implemented by an array
  *
  * @author Richard Szeto
  *
  *
  */

#ifndef ARRAYSTACK_H
#define ARRAYSTACK_H

namespace DataStructureSzeto
{
    template<class T>
    class ArrayStack
    {
    public:
        ArrayStack();
        ArrayStack(int newCapacity);
        ArrayStack(const ArrayStack<T> &arrayStackObject);
        ~ArrayStack();
        ArrayStack<T>& operator =(const ArrayStack<T> &rightSide);
        T peek();
        T pop();
        void push(T newElement);
        int getLength() const;
        int getCapacity() const;
        bool isEmpty() const;
        void clear();

    protected:
        void doubleCapacity();

        T *stack;
        int capacity;
        int length;
    };
}

#endif