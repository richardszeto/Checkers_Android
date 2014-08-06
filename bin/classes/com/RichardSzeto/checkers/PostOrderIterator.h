/** Post order iterator for GameTree
  *
  * @author Richard Szeto
  *
  *
  *
  */

#ifndef POSTORDERITERATOR_H
#define POSTORDERITERATOR_H

#include "GameTreeNode.h"
#include "LinkedStack.h"
#include "LinkedStack.cpp"

namespace CheckersSzeto
{
    using DataStructureSzeto::LinkedStack;

    class GameTreeNode;
    
    class PostOrderIterator
    {
    public:
        PostOrderIterator();
        PostOrderIterator(GameTreeNode *subTreeRoot);
        PostOrderIterator(const PostOrderIterator &iteratorObject);
        ~PostOrderIterator();
        void clear();
        PostOrderIterator& operator =(const PostOrderIterator &rightSide);
        GameTreeNode* getNode();
        PostOrderIterator operator ++(); // Prefix form
        PostOrderIterator operator ++(int); // Postfix form

    protected:
        void findTerminalNode();

        GameTreeNode *currentNode;
        LinkedStack<GameTreeNode> stack;
        int childNumber;
    };
}

#endif