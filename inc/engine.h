//
//  engine.h
//  src
//
//  Created by Victor "dicelander" Sander on 20/06/21.
//

#ifndef engine_h
#define engine_h

#include <genesis.h>
#include <string.h>
#include <resources.h>
#include "../res/resources.h"

#define MAX_EVENTS 300

#define PLAYER_IDLE 0
#define PLAYER_RIGHT 1
#define PLAYER_LEFT 2

#define ALIVE 1
#define DEAD 0
#define EXPLOSION 2

#define EXPLOSION_LENGHT 8

#define LEFT_EDGE FIX16(0)
#define RIGHT_EDGE FIX16(320)
#define TOP_EDGE FIX16(0)
#define BOTTOM_EDGE FIX16(224)


int sign(int x);

void getSinCos(int dx, int dy, fix16 sincos[2]);

#endif /* engine_h */
