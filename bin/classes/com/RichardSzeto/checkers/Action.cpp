/** Class to hold an action with start and end coordinates
  *
  * @author Richard Szeto
  *
  *
  */

#include "Action.h"

namespace CheckersSzeto
{
    Action::Action()
    {
        startX = 0;
        startY = 0;
        endX = 0;
        endY = 0;
    }

    Action::Action(int newStartX, int newStartY,
        int newEndX, int newEndY)
    {
        startX = newStartX;
        startY = newStartY;
        endX = newEndX;
        endY = newEndY;
    }

    Action::~Action()
    {
        // deliberately left empty
    }

    int Action::getStartX() const
    {
        return startX;
    }

    int Action::getStartY() const
    {
        return startY;
    }

    int Action::getEndX() const
    {
        return endX;
    }

    int Action::getEndY() const
    {
        return endY;
    }

    void Action::setStartX(int newStartX)
    {
        startX = newStartX;
    }

    void Action::setStartY(int newStartY)
    {
        startY = newStartY;
    }

    void Action::setEndX(int newEndX)
    {
        endX = newEndX;
    }

    void Action::setEndY(int newEndY)
    {
        endY = newEndY;
    }
}