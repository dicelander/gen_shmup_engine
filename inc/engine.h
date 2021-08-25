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

/* Entity Structure */

//typedef struct {
//    fix16 pos_x;
//    fix16 pos_y;
//    fix16 offset_x;
//    fix16 offset_y;
//    fix16 width;
//    fix16 height;
//    //int weapon_x;
//    //int weapon_y;
//    fix16 vel_x;
//    fix16 vel_y;
//    int health;
//    Sprite* sprite;
//    char name[6];
//    int type;
//    int path;
//    int pathstate;
//    int timer;
//    int direction;
//    u16 status; //alive = 1, //dead = 0; explosion = 2;
//} Entity;

/* Level Structure */

typedef struct Level {
    u16 levelNumber;
    u16 levelEvents[MAX_EVENTS];
    u16 eventCoordinate[MAX_EVENTS];
    u16 currentEvent;
} Level;

/*Player shots attributes*/

//typedef struct {
//    u16 dx;
//    u16 dy;
//    fix16 sin;
//    fix16 cos;
//} Angle;

/* Diagonal Speed */

//void killEntity(Entity* e);

//void reviveEntity(Entity* e);

//int collideEntities(Entity* a, Entity* b);

//void initShots(Shots* shots);

//void moveShots(Shots* shots);

//void enemyShoot(Shots* shots, Entity* enemy);

//void enShotCollisions (Enemies* enemies, Shots* shots);
//
//void enPlayerCollisions (Enemies* enemies, Entity* player);

int sign(int x);

void getSinCos(int dx, int dy, fix16 sincos[2]);

//void PL_setShotsPtr(Shots *shots);

//Shots *PL_getShotsPtr();

#endif /* engine_h */
