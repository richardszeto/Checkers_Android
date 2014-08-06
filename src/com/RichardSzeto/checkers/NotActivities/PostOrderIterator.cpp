/** Post order iterator for GameTree
  *
  * @author Richard Szeto
  *
  *
  *
  */

#include <cstddef>
#include "PostOrderIterator.h"

namespace CheckersSzeto
{
    using DataStructureSzeto::LinkedStack;
    
    PostOrderIterator::PostOrderIterator()
    {
        currentNode = NULL;

        childNumber = 0;
    }

    PostOrderIterator::PostOrderIterator(GameTreeNode *subTreeRoot)
    {
        currentNode = subTreeRoot;

        childNumber = 0;

        findTerminalNode();
    }

    PostOrderIterator::PostOrderIterator(const PostOrderIterator &iteratorObject)
    {
        currentNode = iteratorObject.currentNode;

        stack = iteratorObject.stack;

        childNumber = iteratorObject.childNumber;
    }

    PostOrderIterator::~PostOrderIterator()
    {
        clear();
    }

    void PostOrderIterator::clear()
    {
        currentNode = NULL;
    }

    PostOrderIterator& PostOrderIterator::operator =(const PostOrderIterator &rightSide)
    {
        clear();

        currentNode = rightSide.currentNode;

        stack = rightSide.stack;

        childNumber = rightSide.childNumber;

        return *this;
    }

    GameTreeNode* PostOrderIterator::getNode()
    {
        return currentNode;
    }

    PostOrderIterator PostOrderIterator::operator ++() // Prefix form
    {
        if(!stack.isEmpty())
        {
            GameTreeNode *topTreeNode;

            topTreeNode = stack.peek();

            for(int i = childNumber + 1; i < topTreeNode->getNumberOfChildren(); i++)
            {
                if(topTreeNode->getChild(i) != NULL)
                {
                    childNumber = i;

                    currentNode = topTreeNode->getChild(i);

                    findTerminalNode();

                    return *this;
                }
            }

            currentNode = stack.pop();
        }
        else
        {
            currentNode = NULL;
        }

        return *this;
    }

    PostOrderIterator PostOrderIterator::operator ++(int ignoreMe) // Postfix form
    {
        PostOrderIterator startVersion(*this);

        if(!stack.isEmpty())
        {
            GameTreeNode *topTreeNode;

            topTreeNode = stack.peek();

            for(int i = childNumber + 1; i < topTreeNode->getNumberOfChildren(); i++)
            {
                if(topTreeNode->getChild(i) != NULL)
                {
                    childNumber = i;

                    currentNode = topTreeNode->getChild(i);

                    findTerminalNode();

                    return startVersion;
                }
            }

            currentNode = stack.pop();
        }
        else
        {
            currentNode = NULL;
        }

        return startVersion;
    }

    void PostOrderIterator::findTerminalNode()
    {
        bool isTerminalNode = false;

        while(!isTerminalNode)
        {
            isTerminalNode = true;

            if(currentNode != NULL)
            {
                for(int i = 0; i < currentNode->getNumberOfChildren(); i++)
                {
                    if(currentNode->getChild(i) != NULL)
                    {
                        childNumber = i;

                        stack.push(currentNode);

                        currentNode = currentNode->getChild(i);

                        isTerminalNode = false;

                        break;
                    }
                }
            }
        }
    }
}