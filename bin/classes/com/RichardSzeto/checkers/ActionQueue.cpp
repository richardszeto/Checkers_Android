/** Queue of Action objects, implemented by a linked list
  *
  * @author Richard Szeto
  *
  *
  */

#include <cstddef>
#include "ActionQueue.h"

namespace CheckersSzeto
{
	ActionQueue::ActionQueue()
	{
		front = NULL;

		back = NULL;

		length = 0;
	}

    ActionQueue::ActionQueue(const ActionQueue &queueObject)
    {
    	ActionNode *otherNode;

    	front = NULL;

    	back = NULL;

    	otherNode = queueObject.front;

    	if(otherNode != NULL)
    	{
    		front = new ActionNode(otherNode->getData());

    		back = front;

    		otherNode = otherNode->getLink();
    	}

    	while(otherNode != NULL)
    	{
    		back->setLink(new ActionNode(otherNode->getData()));

    		back = back->getLink();

    		otherNode = otherNode->getLink();
    	}

    	length = queueObject.length;
    }

    ActionQueue::~ActionQueue()
    {
    	clear();
    }

    ActionQueue& ActionQueue::operator =(const ActionQueue &rightSide)
    {
        clear();

    	ActionNode *otherNode;

    	front = NULL;

    	back = NULL;

    	otherNode = rightSide.front;

    	if(otherNode != NULL)
    	{
    		front = new ActionNode(otherNode->getData());

    		back = front;

    		otherNode = otherNode->getLink();
    	}

    	while(otherNode != NULL)
    	{
    		back->setLink(new ActionNode(otherNode->getData()));

    		back = back->getLink();

    		otherNode = otherNode->getLink();
    	}

    	length = rightSide.length;

    	return *this;
    }

    Action ActionQueue::getFront() const
    {
        if(!isEmpty())
        {
    	   return front->getData();
        }

        return Action();
    }

    Action ActionQueue::removeFront()
    {
    	if(!isEmpty())
    	{
	    	Action result = front->getData();

	    	ActionNode *nextNode;

	    	nextNode = front->getLink();

	    	delete front;

	    	front = nextNode;

	    	length--;

	    	if(front == NULL)
	    	{
	    		back = NULL;
	    	}

	    	return result;
	    }

	    return Action();
    }

    void ActionQueue::addToBack(const Action &newElement)
    {
    	if(isEmpty())
    	{
    		front = new ActionNode(newElement);

    		back = front;
    	}
    	else
    	{
    		back->setLink(new ActionNode(newElement));

    		back = back->getLink();
    	}

    	length++;
    }

    int ActionQueue::getLength() const
    {
    	return length;
    }

    bool ActionQueue::isEmpty() const
    {
    	return (front == NULL &&
    		back == NULL &&
    		length == 0);
    }

    void ActionQueue::clear()
    {
        if(!isEmpty())
        {
        	ActionNode *nextNode;

        	while(front != NULL)
        	{
        		nextNode = front->getLink();

                front->clear();

        		delete front;
                
        		front = nextNode;
        	}

        	back = NULL;

        	length = 0;
        }
    }
}