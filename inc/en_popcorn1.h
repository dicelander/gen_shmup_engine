//
//  en_popcorn1.h
//  gen_shmupc
//
//  Created by Victor "dicelander" Sander on 31/08/21.
//

#ifndef en_popcorn1_h
#define en_popcorn1_h

#include <genesis.h>
#include "enemies.h"

void en_pc1_spawn(Enemies* enemies, const u8 type, s16 pos_x, s16 pos_y, const Behaviour* behaviour);

void en_pc1_updatePosition(Enemy* enemy, Action_Arg arg0, Action_Arg arg1, Action_Arg arg2, Action_Arg arg3, Action_Arg arg4, Action_Arg arg5);

void en_pc1_changeVelocity(Enemy* enemy, Action_Arg vel_x, Action_Arg vel_y, Action_Arg pos_x, Action_Arg pos_y, Action_Arg dir, Action_Arg arg5);

void en_pc1_changePosition(Enemy* enemy, Action_Arg pos_x, Action_Arg pos_y, Action_Arg dir, Action_Arg zerospeed, Action_Arg arg5);

void en_pc1_shoot(Enemy* enemyptr, Action_Arg arg0, Action_Arg arg1, Action_Arg arg2, Action_Arg arg3, Action_Arg arg4, Action_Arg arg5);

#endif /* en_popcorn1_h */
