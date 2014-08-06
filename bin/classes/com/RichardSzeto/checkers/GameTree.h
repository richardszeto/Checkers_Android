/** GameTree for the AI
  *
  * @author Richard Szeto
  *
  *
  *
  */

#ifndef GAMETREE_H
#define GAMETREE_H

#include "PostOrderIterator.h"
#include "GameTreeNode.h"
#include "globals.h"
#include "LinkedQueue.h"
#include "LinkedQueue.cpp"
#include "Timer.h"

namespace CheckersSzeto
{
    using DataStructureSzeto::LinkedQueue;

    class GameTreeNode;

    class PostOrderIterator;

    class ActionQueue;

    class Board;

    class GameTree
    {
    public:
        GameTree();
        ~GameTree();
        void clear();
        void setTime(const unsigned long &milliseconds);
        unsigned long getTime() const;
        PostOrderIterator getPostOrderIterator();
        ActionQueue alphaBetaSearch(const Board &currentBoard, int maxDepth);

    protected:
        int maxValue(GameTreeNode *state, int alpha, int beta, int maxDepth);
        int minValue(GameTreeNode *state, int alpha, int beta, int maxDepth);
        bool isTerminalState(GameTreeNode *state);
        int computeBoardValue(const Board &currentBoard);
        void createChildren(GameTreeNode *state);
        void queueAllNextCaptureStates(GameTreeNode *currentState, Color currentTurn, 
            int startX, int startY, LinkedQueue<GameTreeNode> &nodeQueue);
        GameTreeNode* createNextMoveState(GameTreeNode *currentState, int startX,
            int startY, int endX, int endY);
        int max(int value1, int value2);
        int min(int value1, int value2);
        void deleteSubTree(GameTreeNode *subTreeRoot);

        GameTreeNode *root;
        Timer timer;
        unsigned long milliseconds;
    };
}

#endif