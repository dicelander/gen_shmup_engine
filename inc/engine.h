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

#define MAX_ENEMIES 10
#define MAX_SHOTS 10

#define MAX_BEHAVIOURS 30
#define MAX_PATHS 30
#define MAX_PATHS_ENTRIES 30
#define MAX_SWITCH_TIMES 30
#define MAX_X_VELS 30
#define MAX_Y_VELS 30

#define MAX_EVENTS 300

#define LEFT_EDGE 0
#define RIGHT_EDGE 320
#define TOP_EDGE 0
#define BOTTOM_EDGE 224
#define DIAGONAL 0.71

#define PLAYER_IDLE 0
#define PLAYER_RIGHT 1
#define PLAYER_LEFT 2

#define ENEMY_DOWN 0
#define ENEMY_DOWN_RIGHT 1
#define ENEMY_DOWN_LEFT 2
#define ENEMY_RIGHT 3
#define ENEMY_LEFT 4
#define ENEMY_UP_RIGHT 5
#define ENEMY_UP_LEFT 6
#define ENEMY_UP 7

#define ALIVE 1
#define DEAD 0
#define EXPLOSION 2

#define EXPLOSION_LENGHT 8

#define PLAYER_Y_OFFSET 7 //hitbox 5px menor que sprite no eixo y pra cima e para baixo;
#define PLAYER_X_OFFSET 2

#define PATH_LOOP 200
#define PATH_END 201

#define SPAWN_ENEMY1_1 1
#define SPAWN_ENEMY1_2 2

/* Enemy Pathing Structure */

typedef enum {enemy_shoot, change_movement, change_speed, change_direction, do_nothing, remove_enemy} actions;

/* Entity Structure */

typedef struct {
    int x;
    int y;
    int offset_x;
    int offset_y;
    int w;
    int h;
    //int weapon_x;
    //int weapon_y;
    fix16 velx;
    fix16 vely;
    int health;
    Sprite* sprite;
    char name[6];
    int type;
    int path;
    int pathstate;
    int timer;
    int direction;
    u16 state; //alive = 1, //dead = 0; explosion = 2;
    const actions* actionpointer;
    const fix16* velxpointer;
    const fix16* velypointer;
    const u16* directionpointer;
} Entity;

typedef struct {
    u16 switchtimes[MAX_SWITCH_TIMES];
    actions action[MAX_SWITCH_TIMES];
    fix16 velx[MAX_SWITCH_TIMES];
    fix16 vely[MAX_SWITCH_TIMES];
    u16 direction[MAX_SWITCH_TIMES];
} Pathing;

/* enemy actions enum */

/* Level Structure */

typedef struct {
    u16 levelNumber;
    u16 levelEvents[MAX_EVENTS];
    u16 eventCoordinate[MAX_EVENTS];
    u16 currentEvent;
} Level;

/*Enemy Attributes*/

typedef struct {
    Entity enemy[MAX_ENEMIES];
    u16 enemiesOnScreen;
} Enemies;

/*Player shots attributes*/

typedef struct {
    Entity playerShot[MAX_SHOTS];
    Entity enShot[MAX_SHOTS];
    u16 shotsOnScreen;
} Shots;

//typedef struct {
//    u16 dx;
//    u16 dy;
//    fix16 sin;
//    fix16 cos;
//} Angle;

/*Enemy shots attributes*/

//typedef void JoyEventCallback(u16 joy, u16 changed, u16 state, Shots* shots, Entity* player);

/* Diagonal Speed */

void killEntity(Entity* e);

void reviveEntity(Entity* e);

int collideEntities(Entity* a, Entity* b);

void spawnEnemy(Enemies* enemies, u16 type, u16 path, s16 pos_x, s16 pos_y, Pathing* Behaviour);

void shoot(Shots* shots, Entity* player);

void initShots(Shots* shots);

void setPointerShots(Shots *shots);

Shots *getPointerShots();

void moveShots(Shots* shots);

void enemyShoot(Shots* shots, Entity* enemy);

void setPointerPlayer(Entity* player);

Entity *getPointerPlayer();

void enShotCollisions (Enemies* enemies, Shots* shots);

void enPlayerCollisions (Enemies* enemies, Entity* player);

void movePlayer(Entity* player);

int sign(int x);

void getSinCos(int dx, int dy, fix16 sincos[2]);

#endif /* engine_h */
