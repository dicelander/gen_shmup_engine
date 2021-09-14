//
//  player.h
//  gen_shmup
//
//  Created by Victor "dicelander" Sander on 20/08/21.
//

#ifndef player_h
#define player_h

#include <genesis.h>
#include "../res/resources.h"

#define MAX_PLAYER_SHOTS 3
#define ALIVE 1
#define DEAD 0
#define EXPLOSION 2

struct Shots; // forward declaration of shots struct declared in engine.h

typedef struct Player Player;

typedef struct Pl_Shot Pl_Shot;

#ifndef ACTION_ARG
#define ACTION_ARG

typedef union Action_Arg {
    fix16 fix16;
    u16 u16;
} Action_Arg;

#endif

struct Pl_Shot {
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
    u8 health;
    u16 timer;
    u8 status;
    Sprite* sprite;
    struct {
        void (*move)(Pl_Shot* shot, Action_Arg arg0, Action_Arg arg1, Action_Arg arg2, Action_Arg arg3, Action_Arg arg4, Action_Arg arg5);
    } type;
};

typedef struct Pl_Shots {
    Pl_Shot shot[MAX_PLAYER_SHOTS];
    u16 pl_shotsonscreen;
} Pl_Shots;

struct Player {
    fix16 pos_x;
    fix16 pos_y;
    fix16 offset_x;
    fix16 offset_y;
    fix16 width;
    fix16 height;
    fix16 vel_x;
    fix16 vel_y;
    s8 health;
    u8 timer;
    u8 status;
    Sprite* sprite;
    void (*eqweapon)(struct Pl_Shots* shots, Player *player); //function pointer to weapon player is currently using
};

void PL_setPlayerPtr(Player* player);

Player *PL_getPlayerPtr();

void PL_movePlayer(Player* player);

void PL_initShots(Pl_Shots* shots);

Pl_Shots *PL_getShotsPtr();

void PL_setShotsPtr(Pl_Shots *shots);

void PL_moveShots(Pl_Shots* shots);

void PL_explode(Player* player);

#ifndef POSITION_HISTORY_SIZE
#define POSITION_HISTORY_SIZE 40
#endif

typedef struct Pos_History Pos_History;

struct Pos_History {
    fix16 pos_x[POSITION_HISTORY_SIZE];
    fix16 pos_y[POSITION_HISTORY_SIZE];
    u8 current; //positions will be added here
};

void addPosHistory(Pos_History* history, Player* player);

void PL_initPosHistory (Pos_History* history);

Pos_History* PL_getPosHistoryPtr();

void PL_setPosHistoryPtr(Pos_History* history);

#endif /* player_h */
