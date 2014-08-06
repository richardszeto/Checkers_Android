/** Various global variables and types
  *
  * @author Richard Szeto
  *
  *
  *
  */

#ifndef GLOBALS_H
#define GLOBALS_H

namespace CheckersSzeto
{
    const int MEN_SIZE = 2;
    const int GRID_LENGTH = 8;
    const int PLAYER_PIECES = 12;
    const int NUMBER_PLAYERS = 2;

    enum Color
    {
        WHITE, BLACK
    };

    enum Piece
    {
        NONE,
        WHITE_MAN, WHITE_KING,
        BLACK_MAN, BLACK_KING
    };

    enum Corner
    {
        TOP_LEFT, TOP_RIGHT, BOTTOM_LEFT, BOTTOM_RIGHT
    };
}

#endif