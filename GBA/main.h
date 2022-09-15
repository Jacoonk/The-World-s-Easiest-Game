#ifndef MAIN_H
#define MAIN_H

#include "gba.h"

struct player {
    int row;
    int col;
    int dr;
    int cd;
    u16 color;
    int size;
};

struct ball {
    int row;
    int col;
    int dr;
    int cd;
    u16 color;
    int size;
};

struct wall {
    int row;
    int col;
    u16 color;
    int length;
    int w;
};

struct state {
    int currentState;
    int nextState;
    struct ball balls[3];
    struct player mc;
    struct wall obstacle;
};

/*
* For example, for a Snake game, one could be:
*
* struct snake {
*   int heading;
*   int length;
*   int row;
*   int col;
* };
*
* Example of a struct to hold state machine data:
*
* struct state {
*   int currentState;
*   int nextState;
* };
*
*/

#endif
