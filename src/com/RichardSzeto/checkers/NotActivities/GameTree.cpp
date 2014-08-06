/** GameTree for the AI
  *
  * @author Richard Szeto
  *
  *
  *
  */

#include <cstddef>
#include <climits>
#include "GameTree.h"
#include "globals.h"
#include "LinkedQueue.h"
#include "LinkedQueue.cpp"
#include "ActionQueue.h"
#include "Timer.h"

namespace CheckersSzeto
{
    using DataStructureSzeto::LinkedQueue;

    const int INFINITY = INT_MAX;

    const int NEG_INFINITY = INT_MIN;

    GameTree::GameTree()
    {
        root = NULL;
        milliseconds = 1000; // 1 second
    }

    GameTree::~GameTree()
    {
        clear();
    }

    void GameTree::clear()
    {
        deleteSubTree(root);

        root = NULL;
    }

    void GameTree::setTime(const unsigned long &milliseconds)
    {
        this->milliseconds = milliseconds;
    }

    unsigned long GameTree::getTime() const
    {
        return milliseconds;
    }

    PostOrderIterator GameTree::getPostOrderIterator()
    {
        return PostOrderIterator(root);
    }

    ActionQueue GameTree::alphaBetaSearch(const Board &currentBoard, int maxDepth)
    {
        int utilityValue;

        deleteSubTree(root);

        root = NULL;

        root = new GameTreeNode(currentBoard);

        timer.start();

        utilityValue = maxValue(root, NEG_INFINITY, INFINITY, maxDepth - 1);

        if(timer.isOver(milliseconds))
        {
            timer.stop();

            timer.reset();

            deleteSubTree(root);

            root = NULL;

            return ActionQueue();
        }

        if(root != NULL)
        {
            for(int i = 0; i < root->getNumberOfChildren(); i++)
            {
                if(root->getChild(i) != NULL &&
                    root->getChild(i)->getValue() == utilityValue)
                {
                    ActionQueue result = root->getChild(i)->actionQueue;

                    deleteSubTree(root);

                    root = NULL;

                    return result;
                }
            }
        }

        deleteSubTree(root);

        root = NULL;

        return ActionQueue();
    }

    int GameTree::maxValue(GameTreeNode *state, int alpha, int beta, int maxDepth)
    {
        state->getData()->scanCapture();

        state->getData()->scanMove();

        if(maxDepth <= 0 || isTerminalState(state))
        {
            state->setValue(computeBoardValue(*(state->getData())));

            return state->getValue();
        }

        if(timer.isOver(milliseconds))
        {
            return 0;
        }

        createChildren(state);

        if(timer.isOver(milliseconds))
        {
            for(int i = 0; i < state->getNumberOfChildren(); i++)
            {
                if(state->getChild(i) != NULL)
                {
                    if(state != root)
                    {
                        deleteSubTree(state->getChild(i));

                        state->setChild(i, NULL);
                    }
                }
            }

            return 0;
        }

        int utilityValue;

        utilityValue = NEG_INFINITY;

        for(int i = 0; i < state->getNumberOfChildren(); i++)
        {
            if(state->getChild(i) != NULL)
            {
                utilityValue = max(utilityValue, minValue(state->getChild(i), 
                    alpha, beta, maxDepth - 1));

                if(state != root)
                {
                    deleteSubTree(state->getChild(i));

                    state->setChild(i, NULL);
                }

                if(utilityValue >= beta)
                {
                    state->setValue(utilityValue);

                    return utilityValue;
                }

                alpha = max(alpha, utilityValue);
            }
        }

        state->setValue(utilityValue);

        return utilityValue;
    }

    int GameTree::minValue(GameTreeNode *state, int alpha, int beta, int maxDepth)
    {
        state->getData()->scanCapture();

        state->getData()->scanMove();

        if(maxDepth <= 0 || isTerminalState(state))
        {
            state->setValue(computeBoardValue(*(state->getData())));

            return state->getValue();
        }

        if(timer.isOver(milliseconds))
        {
            return 0;
        }

        createChildren(state);

        if(timer.isOver(milliseconds))
        {
            for(int i = 0; i < state->getNumberOfChildren(); i++)
            {
                if(state->getChild(i) != NULL)
                {
                    if(state != root)
                    {
                        deleteSubTree(state->getChild(i));

                        state->setChild(i, NULL);
                    }
                }
            }

            return 0;
        }

        int utilityValue;

        utilityValue = INFINITY;

        for(int i = 0; i < state->getNumberOfChildren(); i++)
        {
            if(state->getChild(i) != NULL)
            {
                utilityValue = min(utilityValue, maxValue(state->getChild(i), 
                    alpha, beta, maxDepth - 1));

                if(state != root)
                {
                    deleteSubTree(state->getChild(i));

                    state->setChild(i, NULL);
                }

                if(utilityValue <= alpha)
                {
                    state->setValue(utilityValue);

                    return utilityValue;
                }

                beta = min(beta, utilityValue);
            }
        }

        state->setValue(utilityValue);

        return utilityValue;
    }

    bool GameTree::isTerminalState(GameTreeNode *state)
    {
        Board *currentBoard;

        currentBoard = state->getData();

        if(!(currentBoard->needToCapture) &&
            !(currentBoard->needToMove))
        {
            return true;
        }

        return false;
    }

    int GameTree::computeBoardValue(const Board &currentBoard)
    {
        Color playerColor = root->getData()->turn;

        Color enemyColor;

        if(playerColor == WHITE)
        {
            enemyColor = BLACK;
        }
        else
        {
            enemyColor = WHITE;
        }

        if(!(currentBoard.needToCapture) &&
            !(currentBoard.needToMove))
        {
            if(currentBoard.turn == 
                playerColor)
            {
                return -9999;
            }
            else
            {
                return 9999;
            }
        }

        int playerValue = 0;

        int enemyValue = 0;

        for(int startingIndex = 0; startingIndex < 2; startingIndex++)
        {
            for(int i = startingIndex; i < GRID_LENGTH; i += 2)
            {
                for(int j = startingIndex; j < GRID_LENGTH; j += 2)
                {
                    if(currentBoard.grid[i][j] != NONE)
                    {
                        if(currentBoard.isPieceColor(playerColor, i, j))
                        {
                            if(currentBoard.isMan(i, j))
                            {
                                playerValue += 2;
                            }
                            else if(currentBoard.isKing(i, j))
                            {
                                playerValue += 3;
                            }
                        }
                        else if(currentBoard.isPieceColor(enemyColor, i, j))
                        {
                            if(currentBoard.isMan(i, j))
                            {
                                enemyValue += 2;
                            }
                            else if(currentBoard.isKing(i, j))
                            {
                                enemyValue += 3;
                            }
                        }
                    }
                }
            }
        }

        return (playerValue - enemyValue);
    }

    void GameTree::createChildren(GameTreeNode *state)
    {
        Board *currentBoard;

        currentBoard = state->getData();

        LinkedQueue<GameTreeNode> nodeQueue;

        Color currentTurn = currentBoard->turn;

        for(int startingIndex = 0; startingIndex < 2; startingIndex++)
        {
            for(int i = startingIndex; i < GRID_LENGTH; i += 2)
            {
                for(int j = startingIndex; j < GRID_LENGTH; j += 2)
                {
                    if(timer.isOver(milliseconds))
                    {
                        nodeQueue.deleteNodes();

                        return;
                    }

                    if(currentBoard->isPieceColor(currentTurn, i, j))
                    {
                        if(currentBoard->needToCapture)
                        {
                            GameTreeNode *nextState;

                            nextState = new GameTreeNode(*currentBoard);

                            queueAllNextCaptureStates(nextState, 
                                currentTurn, i, j, nodeQueue);

                            if(timer.isOver(milliseconds))
                            {
                                nodeQueue.deleteNodes();

                                return;
                            }
                        }
                        else
                        {
                            if(timer.isOver(milliseconds))
                            {
                                nodeQueue.deleteNodes();

                                return;
                            }

                            if((currentBoard->isPieceColor(WHITE, i, j) &&
                                currentBoard->isMan(i, j)) || 
                                    (currentBoard->isKing(i, j)))
                            {
                                if(currentBoard->canMove(i, j, TOP_LEFT))
                                {
                                    nodeQueue.addToBack(createNextMoveState(state, 
                                        i, j, i - 1, j + 1));
                                }

                                if(currentBoard->canMove(i, j, TOP_RIGHT))
                                {
                                    nodeQueue.addToBack(createNextMoveState(state, 
                                        i, j, i + 1, j + 1));
                                }
                            }

                            if ((currentBoard->isPieceColor(BLACK, i, j) &&
                                currentBoard->isMan(i, j)) ||
                                (currentBoard->isKing(i, j)))
                            {

                                if(currentBoard->canMove(i, j, BOTTOM_LEFT))
                                {
                                    nodeQueue.addToBack(createNextMoveState(state, 
                                        i, j, i - 1, j - 1));
                                }

                                if(currentBoard->canMove(i, j, BOTTOM_RIGHT))
                                {
                                    nodeQueue.addToBack(createNextMoveState(state, 
                                        i, j, i + 1, j - 1));
                                }
                            }
                        }
                    }
                }
            }
        }

        if(!nodeQueue.isEmpty())
        {
            state->setNumberOfChildren(nodeQueue.getLength());

            for(int i = 0; i < state->getNumberOfChildren(); i++)
            {
                if(!nodeQueue.isEmpty())
                {
                    state->setChild(i, nodeQueue.removeFront());
                }
            }
        }
    }

    void GameTree::queueAllNextCaptureStates(GameTreeNode *currentState, Color currentTurn, 
        int startX, int startY, LinkedQueue<GameTreeNode> &nodeQueue)
    {
        if(timer.isOver(milliseconds))
        {
            delete currentState;

            currentState = NULL;

            nodeQueue.deleteNodes();

            return;
        }

        Board *currentBoard;

        currentBoard = currentState->getData();

        if(currentBoard->turn != currentTurn)
        {
            nodeQueue.addToBack(currentState);

            return;
        }

        currentBoard->scanCapture();

        if ((currentBoard->isPieceColor(WHITE, startX, startY) &&
            currentBoard->isMan(startX, startY)) ||
            (currentBoard->isKing(startX, startY)))
        {
            if(currentBoard->canCapture(startX, startY, TOP_LEFT))
            {
                GameTreeNode *nextState;

                nextState = new GameTreeNode(*currentState);

                nextState->getData()->move(startX, startY, startX - 2, startY + 2);

                nextState->addAction(Action(startX, startY, startX - 2, startY + 2));

                queueAllNextCaptureStates(nextState, currentTurn,
                    startX - 2, startY + 2, nodeQueue);

                if(timer.isOver(milliseconds))
                {
                    delete currentState;

                    currentState = NULL;

                    nodeQueue.deleteNodes();

                    return;
                }
            }

            if(currentBoard->canCapture(startX, startY, TOP_RIGHT))
            {
                GameTreeNode *nextState;

                nextState = new GameTreeNode(*currentState);

                nextState->getData()->move(startX, startY, startX + 2, startY + 2);

                nextState->addAction(Action(startX, startY, startX + 2, startY + 2));

                queueAllNextCaptureStates(nextState, currentTurn,
                    startX + 2, startY + 2, nodeQueue);

                if(timer.isOver(milliseconds))
                {
                    delete currentState;

                    currentState = NULL;

                    nodeQueue.deleteNodes();

                    return;
                }
            }
        }

        if ((currentBoard->isPieceColor(BLACK, startX, startY) &&
            currentBoard->isMan(startX, startY)) ||
            (currentBoard->isKing(startX, startY)))
        {
            if(currentBoard->canCapture(startX, startY, BOTTOM_LEFT))
            {
                GameTreeNode *nextState;

                nextState = new GameTreeNode(*currentState);

                nextState->getData()->move(startX, startY, startX - 2, startY - 2);

                nextState->addAction(Action(startX, startY, startX - 2, startY - 2));

                queueAllNextCaptureStates(nextState, currentTurn,
                    startX - 2, startY - 2, nodeQueue);

                if(timer.isOver(milliseconds))
                {
                    delete currentState;

                    currentState = NULL;

                    nodeQueue.deleteNodes();

                    return;
                }
            }

            if(currentBoard->canCapture(startX, startY, BOTTOM_RIGHT))
            {
                GameTreeNode *nextState;

                nextState = new GameTreeNode(*currentState);

                nextState->getData()->move(startX, startY, startX + 2, startY - 2);

                nextState->addAction(Action(startX, startY, startX + 2, startY - 2));

                queueAllNextCaptureStates(nextState, currentTurn,
                    startX + 2, startY - 2, nodeQueue);

                if(timer.isOver(milliseconds))
                {
                    delete currentState;

                    currentState = NULL;

                    nodeQueue.deleteNodes();

                    return;
                }
            }
        }

        delete currentState;

        currentState = NULL;
    }

    GameTreeNode* GameTree::createNextMoveState(GameTreeNode *currentState, int startX,
        int startY, int endX, int endY)
    {
        GameTreeNode *nextState;

        nextState = new GameTreeNode(*(currentState->getData()));

        nextState->getData()->move(startX, startY, endX, endY);

        nextState->addAction(Action(startX, startY, endX, endY));

        return nextState;
    }

    int GameTree::max(int value1, int value2)
    {
        if(value1 >= value2)
        {
            return value1;
        }

        return value2;
    }

    int GameTree::min(int value1, int value2)
    {
        if(value1 <= value2)
        {
            return value1;
        }

        return value2;
    }

    void GameTree::deleteSubTree(GameTreeNode *subTreeRoot)
    {
        if(subTreeRoot != NULL)
        {
            for(int i = 0; i < subTreeRoot->getNumberOfChildren(); i++)
            {
                if(subTreeRoot->getChild(i) != NULL)
                {
                    deleteSubTree(subTreeRoot->getChild(i));
                }
            }

            delete subTreeRoot;

            subTreeRoot = NULL;
        }
    }
}