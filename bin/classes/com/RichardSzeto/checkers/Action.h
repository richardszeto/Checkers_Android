/** Class to hold an action with start and end coordinates
  *
  * @author Richard Szeto
  *
  *
  */

#ifndef ACTION_H
#define ACTION_H

namespace CheckersSzeto
{
    class Action
    {
    public:
        Action();
        Action(int newStartX, int newStartY,
            int newEndX, int newEndY);
        ~Action();
        int getStartX() const;
        int getStartY() const;
        int getEndX() const;
        int getEndY() const;
        void setStartX(int newStartX);
        void setStartY(int newStartY);
        void setEndX(int newEndX);
        void setEndY(int newEndY);
        
    protected:
        int startX;
        int startY;
        int endX;
        int endY;
    };
}

#endif