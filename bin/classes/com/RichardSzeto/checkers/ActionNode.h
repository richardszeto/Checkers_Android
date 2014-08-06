/** Class used to hold Actions for linked lists
  *
  * @author Richard Szeto
  *
  *
  */

#ifndef ACTIONNODE_H
#define ACTIONNODE_H

#include "Action.h"

namespace CheckersSzeto
{
	class ActionNode
	{
	public:
		ActionNode();
		ActionNode(const Action &newData);
		ActionNode(const Action &newData, ActionNode *newLink);
		ActionNode(const ActionNode& nodeObject);
		~ActionNode();
		void clear();
		ActionNode& operator =(const ActionNode& rightSide);
		Action getData() const;
		ActionNode* getLink();
		void setData(const Action &newData);
		void setLink(ActionNode *newLink);

	protected:
		Action data;
		ActionNode *link;
	};
}

#endif