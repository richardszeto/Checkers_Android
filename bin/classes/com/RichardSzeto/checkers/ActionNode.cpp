/** Class used to hold Actions for linked lists
  *
  * @author Richard Szeto
  *
  *
  */

#include <cstddef>
#include "ActionNode.h"

namespace CheckersSzeto
{
	ActionNode::ActionNode()
	{
		link = NULL;
	}

	ActionNode::ActionNode(const Action &newData)
	{
		data = newData;

		link = NULL;
	}

	ActionNode::ActionNode(const Action &newData, ActionNode* newLink)
	{
		data = newData;

		link = newLink;
	}

	ActionNode::ActionNode(const ActionNode &nodeObject)
	{
		data = nodeObject.data;

		link = NULL;
	}

	ActionNode::~ActionNode()
	{
		clear();
	}

	void ActionNode::clear()
	{
		data = Action();

		link = NULL;
	}

	ActionNode& ActionNode::operator =(const ActionNode &rightSide)
	{
		data = rightSide.data;

		link = NULL;

		return *this;
	}

	Action ActionNode::getData() const
	{
		return data;
	}

	ActionNode* ActionNode::getLink()
	{
		return link;
	}

	void ActionNode::setData(const Action &newData)
	{
		data = newData;
	}

	void ActionNode::setLink(ActionNode* newLink)
	{
		link = newLink;
	}
}