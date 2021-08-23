//
//  player.h
//  gen_shmup
//
//  Created by Victor "dicelander" Sander on 20/08/21.
//

#ifndef player_h
#define player_h

#include <genesis.h>

struct Shots; // forward declaration of shots struct declared in engine.h

typedef struct Player Player;

struct Player {
    fix16 pos_x;
    fix16 pos_y;
    fix16 offset_x;
    fix16 offset_y;
    fix16 width;
    fix16 height;
    fix16 vel_x;
    fix16 vel_y;
    s16 health;
    Sprite* sprite;
    void (*eqweapon)(struct Shots* shots, Player *player); //function pointer to weapon player is currently using
};

void setPointerPlayer(Player* player);

Player *getPointerPlayer();

void movePlayer(Player* player);

#endif /* player_h */
