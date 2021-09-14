//
//  player.h
//  gen_shmup
//
//  Created by Victor "dicelander" Sander on 20/08/21.
//

#ifndef player_h
#define player_h

#include <genesis.h>
#include "entity.h"
#include "../res/resources.h"

#define MAX_PLAYER_SHOTS 3
#define ALIVE 1
#define DEAD 0
#define EXPLOSION 2

struct Shots; // forward declaration of shots struct declared in engine.h

typedef Entity Player;

typedef Entity Pl_Shot;

typedef struct Pl_Shots {
    Pl_Shot shot[MAX_PLAYER_SHOTS];
    u16 pl_shotsonscreen;
} Pl_Shots;

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
