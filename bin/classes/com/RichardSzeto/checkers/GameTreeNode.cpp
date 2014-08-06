/** Node that holds the possible states for the AI
  *
  * @author Richard Szeto
  *
  *
  *
  */

#include <cstddef>
#include "GameTreeNode.h"

namespace CheckersSzeto
{
    using DataStructureSzeto::LinkedQueue;

    GameTreeNode::GameTreeNode()
    {
        data = NULL;

        utilityValue = 0;

        numberOfChildren = 0;

        child = NULL;
    }

    GameTreeNode::GameTreeNode(const Board &newData)
    {
        data = new Board(newData);

        utilityValue = 0;

        numberOfChildren = 0;

        child = NULL;
    }

    GameTreeNode::GameTreeNode(const GameTreeNode &nodeObject)
    {
        if(nodeObject.data != NULL)
        {
            data = new Board(*(nodeObject.data));
        }
        else
        {
            data = NULL;
        }

        utilityValue = nodeObject.utilityValue;

        actionQueue = nodeObject.actionQueue;

        numberOfChildren = 0;

        child = NULL;
    }

    GameTreeNode::~GameTreeNode()
    {
        clear();
    }

    void GameTreeNode::clear()
    {
        if(child != NULL)
        {
            delete [] child;

            child = NULL;
        }

        if(data != NULL)
        {
            delete data;

            data = NULL;
        }

        actionQueue.clear();

        numberOfChildren = 0;

        utilityValue = 0;
    }

    GameTreeNode& GameTreeNode::operator =(const GameTreeNode &rightSide)
    {
        clear();

        if(rightSide.data != NULL)
        {
            data = new Board(*(rightSide.data));
        }
        else
        {
            data = NULL;
        }

        utilityValue = rightSide.utilityValue;

        actionQueue = rightSide.actionQueue;

        numberOfChildren = 0;

        child = NULL;

        return *this;
    }

    Board* GameTreeNode::getData()
    {
        return data;
    }

    int GameTreeNode::getValue() const
    {
        return utilityValue;
    }

    Action GameTreeNode::getAction()
    {
        return actionQueue.getFront();
    }

    Action GameTreeNode::removeAction()
    {
        return actionQueue.removeFront();
    }

    bool GameTreeNode::noMoreAction() const
    {
        return actionQueue.isEmpty();
    }

    int GameTreeNode::getNumberOfChildren() const
    {
        return numberOfChildren;
    }

    GameTreeNode* GameTreeNode::getChild(int index)
    {
        if(child != NULL &&
            index >= 0 &&
            index < numberOfChildren)
        {
            return child[index];
        }

        return NULL;
    }

    void GameTreeNode::setData(const Board &newData)
    {
        if(data != NULL)
        {
            delete data;

            data = NULL;
        }

        data = new Board(newData);
    }

    void GameTreeNode::setValue(int newValue)
    {
        utilityValue = newValue;
    }

    void GameTreeNode::addAction(const Action &newAction)
    {
        actionQueue.addToBack(newAction);
    }

    bool GameTreeNode::setNumberOfChildren(int newSize)
    {
        if(child == NULL &&
            newSize > 0)
        {
            numberOfChildren = newSize;

            child = new GameTreeNode*[numberOfChildren];

            for(int i = 0; i < numberOfChildren; i++)
            {
                child[i] = NULL;
            }

            return true;
        }

        return false;
    }

    bool GameTreeNode::setChild(int index, GameTreeNode* newNode)
    {
        if(child != NULL &&
            index >= 0 &&
            index < numberOfChildren)
        {
            child[index] = newNode;

            return true;
        }

        return false;
    }
}