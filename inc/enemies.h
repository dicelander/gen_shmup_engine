//
//  enemies.h
//  gen_shmupc
//
//  Created by Victor "dicelander" Sander on 23/08/21.
//

#ifndef enemies_h
#define enemies_h


#define MAX_ENEMIES 15
#define MAX_ACTIONS 30
#define MAX_ENEMY_SHOTS 50
#define ENEMY_DOWN 0
#define ENEMY_DOWN_RIGHT 1
#define ENEMY_DOWN_LEFT 2
#define ENEMY_RIGHT 3
#define ENEMY_LEFT 4
#define ENEMY_UP_RIGHT 5
#define ENEMY_UP_LEFT 6
#define ENEMY_UP 7

#include <genesis.h>
#include "engine.h"
#include "player.h"

typedef struct Enemy Enemy;

struct Behaviour;

struct en_type; //contains pointers to functions enemy uses to do actions that are specific to them.

struct Player;

#ifndef ACTION_ARG
#define ACTION_ARG

typedef union Action_Arg {
    fix16 fix16;
    u16 u16;
} Action_Arg;

#endif

typedef void en_Action(Enemy* enemyptr, Action_Arg arg0, Action_Arg arg1, Action_Arg arg2, Action_Arg arg3, Action_Arg arg4, Action_Arg arg5);

struct en_type {
    en_Action* move;
    en_Action* explode;
    en_Action* shoot;
};

typedef struct Behaviour {
    en_Action* const actions[MAX_ACTIONS];
    const u16 actionframes[MAX_ACTIONS];
    const union Action_Arg arg0[MAX_ACTIONS];
    const union Action_Arg arg1[MAX_ACTIONS];
    const union Action_Arg arg2[MAX_ACTIONS];
    const union Action_Arg arg3[MAX_ACTIONS];
    const union Action_Arg arg4[MAX_ACTIONS];
    const union Action_Arg arg5[MAX_ACTIONS];
} Behaviour;

struct Enemy {
    fix16 pos_x;
    fix16 pos_y;
    fix16 offset_x;
    fix16 offset_y;
    fix16 width;
    fix16 height;
    //other properties (needs organizing)
    fix16 vel_x;
    fix16 vel_y;
    u16 direction;
    s8 health;
    u16 nextpatternstate;
    u16 timer;
    u16 status;
    Sprite* sprite;
    struct en_type type;
    const struct Behaviour* pattern;
};

typedef struct Enemies {
    Enemy enemy[MAX_ENEMIES];
    u16 enemiesOnScreen;
} Enemies;


typedef struct En_Shot En_Shot;

//struct shot_type {
//    void (*move)(En_Shot* shot, Action_Arg arg0, Action_Arg arg1, Action_Arg arg2, Action_Arg arg3, Action_Arg arg4, Action_Arg arg5);
//};

struct En_Shot {
    fix16 pos_x;
    fix16 pos_y;
    //hitbox/dimensions related stuff (suposedly constant)
    fix16 offset_x;
    fix16 offset_y;
    fix16 width;
    fix16 height;
    //other properties (needs organizing)
    fix16 vel_x;
    fix16 vel_y;
    u16 direction;
    s8 health;
    u16 timer;
    u16 status;
    Sprite* sprite;
    union owner {
        Enemy* enemy;
        En_Shot* shot;
    } owner;
    struct {
        void (*move)(En_Shot* shot);
    } type;
};
    
typedef struct En_Shots {
    struct En_Shot shot[MAX_ENEMY_SHOTS];
    u16 en_shotsonscreen;
} En_Shots;

void EN_killEnemy(Enemy* e);

void EN_updateEnemies(Enemies *enemies);

void en_chgaction(Enemy* enemy, Action_Arg arg0, Action_Arg arg1, Action_Arg arg2, Action_Arg arg3, Action_Arg arg4, Action_Arg arg5);

void en_condchgaction(Action_Arg arg0, Action_Arg arg1, Action_Arg arg2, Action_Arg arg3, Action_Arg arg4, Action_Arg arg5);

void EN_initShots(En_Shots *shots);

En_Shots *EN_getShotsPtr();

void EN_setShotsPtr(En_Shots *shots);

void EN_moveShots(En_Shots *shots);

Enemies *EN_getEnemiesPtr();

void EN_setEnemiesPtr(Enemies *enemies);

void en2_spawnEnemy(Enemies* enemies, const u8 type, s16 pos_x, s16 pos_y, const Behaviour* behaviour);

#endif /* enemies_h */
