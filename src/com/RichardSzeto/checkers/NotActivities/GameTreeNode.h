/** Node that holds the possible states for the AI
  *
  * @author Richard Szeto
  *
  *
  *
  */

#ifndef GAMETREENODE_H
#define GAMETREENODE_H

#include "Board.h"
#include "ActionQueue.h"
#include "Action.h"
#include "GameTree.h"

namespace CheckersSzeto
{
    class GameTree;

    class Board;

    class GameTreeNode
    {
    public:
        GameTreeNode();
        GameTreeNode(const Board &newData);
        GameTreeNode(const GameTreeNode &nodeObject);
        ~GameTreeNode();
        void clear();
        GameTreeNode& operator =(const GameTreeNode &rightSide);
        Board* getData();
        int getValue() const;
        Action getAction();
        Action removeAction();
        bool noMoreAction() const;
        int getNumberOfChildren() const;
        GameTreeNode* getChild(int index);
        void setData(const Board &newData);
        void setValue(int newValue);
        void addAction(const Action &newAction);
        bool setNumberOfChildren(int newSize);
        bool setChild(int index, GameTreeNode* newNode);

        friend class GameTree;

    protected:
        Board *data;
        int utilityValue;
        ActionQueue actionQueue;
        int numberOfChildren;
        GameTreeNode **child;
    };
}

#endif