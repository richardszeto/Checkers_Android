/** Queue of Action objects, implemented by a linked list
  *
  * @author Richard Szeto
  *
  *
  *
  */

#ifndef ACTIONQUEUE_H
#define ACTIONQUEUE_H

#include "ActionNode.h"

namespace CheckersSzeto
{
	class ActionQueue
	{
	public:
		ActionQueue();
        ActionQueue(const ActionQueue &queueObject);
        ~ActionQueue();
        ActionQueue& operator =(const ActionQueue &rightSide);
        Action getFront() const;
        Action removeFront();
        void addToBack(const Action &newElement);
        int getLength() const;
        bool isEmpty() const;
        void clear();

    protected:
    	ActionNode *front;
        ActionNode *back;
        int length;
	};
}

#endif