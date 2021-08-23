//
//  enemies.h
//  gen_shmupc
//
//  Created by Victor "dicelander" Sander on 23/08/21.
//

#ifndef enemies_h
#define enemies_h

#define MAX_ACTIONS 30
#define MAX_ENEMY_SHOTS 100

#include <genesis.h>
#include "engine.h"
#include "player.h"

typedef struct Enemy Enemy;

struct Behaviour;

struct en_type; //contains pointers to functions enemy uses to do actions that are specific to them.

struct Player;

typedef union Action_Arg {
    fix16 fix16;
    u16 u16;
} Action_Arg;

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
    // movement related stuff (can change every frame)
    fix16 pos_x;
    fix16 pos_y;
    fix16 vel_x;
    fix16 vel_y;
    u16 direction;
    //hitbox/dimensions related stuff (suposedly constant)
    fix16 offset_x;
    fix16 offset_y;
    fix16 width;
    fix16 height;
    //other properties (needs organizing)
    s16 health;
    u16 nextpatternstate;
    u16 timer;
    u16 status;
    Sprite* sprite;
    const struct en_type* type;
    const struct Behaviour* pattern;
};

typedef struct Enemies {
    Enemy enemy[MAX_ENEMIES];
    u16 enemiesOnScreen;
} Enemies;

typedef struct En_Shot {
        fix16 pos_x;
        fix16 pos_y;
        fix16 vel_x;
        fix16 vel_y;
        u16 direction;
        //hitbox/dimensions related stuff (suposedly constant)
        fix16 offset_x;
        fix16 offset_y;
        fix16 width;
        fix16 height;
        //other properties (needs organizing)
        s16 health;
        u16 timer;
        u16 status;
        Sprite* sprite;
        struct shot_type* type;
} En_Shot;
    
typedef struct En_Shots {
    struct En_Shot shot[MAX_ENEMY_SHOTS];
    u16 en_shotsonscreen;
} En_Shots;

void EN_killEnemy(Enemy* e);

void EN_updateEnemies(Enemies *enemies);

void en1_changeVelocity(Enemy* enemy, Action_Arg vel_x, Action_Arg vel_y, Action_Arg pos_x, Action_Arg pos_y, Action_Arg dir, Action_Arg arg5);

void en1_changePosition(Enemy* enemy, Action_Arg pos_x, Action_Arg pos_y, Action_Arg dir, Action_Arg zerospeed, Action_Arg arg5);

void en1_spawnEnemy(Enemies* enemies, const u16 type, s16 pos_x, s16 pos_y, const Behaviour* behaviour);

void en_chgaction(Enemy* enemy, Action_Arg arg0, Action_Arg arg1, Action_Arg arg2, Action_Arg arg3, Action_Arg arg4, Action_Arg arg5);

void en_condchgaction(Action_Arg arg0, Action_Arg arg1, Action_Arg arg2, Action_Arg arg3, Action_Arg arg4, Action_Arg arg5);

void EN_initShots(En_Shots *shots);

void en1_Shoot(Enemy* enemyptr, Action_Arg arg0, Action_Arg arg1, Action_Arg arg2, Action_Arg arg3, Action_Arg arg4, Action_Arg arg5);

void EN_setShotsPtr(En_Shots *shots);

void EN_moveShots(En_Shots *shots);

En_Shots *EN_getShotsPtr();

#endif /* enemies_h */
