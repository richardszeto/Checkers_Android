/** Stack that holds captured pieces, implemented by an array
  *
  * @author Richard Szeto
  *
  *
  *
  */

#ifndef CAPTURED_H
#define CAPTURED_H

#include "globals.h"
#include "ArrayStack.h"
#include "ArrayStack.cpp"

namespace CheckersSzeto
{
    using DataStructureSzeto::ArrayStack;

    class Captured : public ArrayStack<Piece>
    {
    public:
        Captured();
        Captured(int newCapacity);
        Captured(const Captured &capturedObject);
        virtual ~Captured();
        Captured& operator =(const Captured &rightSide);
        Piece peek();
        Piece pop();
        void clear();

    protected:
        void doubleCapacity();
    };
}

#endif