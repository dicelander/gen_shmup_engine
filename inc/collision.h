//
//  collision.h
//  gen_shmupc
//
//  Created by Victor "dicelander" Sander on 23/08/21.
//

#ifndef collision_h
#define collision_h

#include <genesis.h>
#include "player.h"
#include "enemies.h"

bool collideENPlayer(Enemy* enemy, Player* player);

bool collideENShotPlayer(En_Shot* shot, Player* player);

bool collidePLShotEnemy(Pl_Shot* shot, Enemy* enemy);

void COL_PLShotsEnemies(Pl_Shots* shots, Enemies* enemies);

void COL_ENShotsPlayer(En_Shots* shots, Player* player);

void COL_EnemiesPlayer(Enemies* enemies, Player* player);

#endif /* collision_h */
