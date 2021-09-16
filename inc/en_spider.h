//
//  en_spider.h
//  gen_shmupc
//
//  Created by Victor "dicelander" Sander on 28/08/21.
//

#ifndef en_spider_h
#define en_spider_h

#include <genesis.h>
#include "enemies.h"
#include "engine.h"

void en_spider_spawn(Enemies* enemies, const u8 type, s16 pos_x, s16 pos_y, const Behaviour* behaviour);

void en_spider_shoot(Enemy* enemyptr, Action_Arg arg0, Action_Arg arg1, Action_Arg arg2, Action_Arg arg3, Action_Arg arg4, Action_Arg arg5);

void en_spider_changeVelocity(Enemy* enemy, Action_Arg vel_x, Action_Arg vel_y, Action_Arg pos_x, Action_Arg pos_y, Action_Arg dir, Action_Arg arg5);

void en_spider_changeType(Enemy* spider, Action_Arg action, Action_Arg type, Action_Arg arg2, Action_Arg arg3, Action_Arg arg4, Action_Arg arg5);

void en_spider_kill(Enemy* spider, Action_Arg arg0, Action_Arg arg1, Action_Arg arg2, Action_Arg arg3, Action_Arg arg4, Action_Arg arg5);

void en_spider_mvShot(En_Shot* shot, En_Shots* shots);

void en_spider_chargeShot(Enemy* spider, Action_Arg vel_x, Action_Arg vel_y, Action_Arg pos_x, Action_Arg pos_y, Action_Arg dir, Action_Arg mode);

void en_spider_beginShot(Enemy* spider, Action_Arg vel_x, Action_Arg vel_y, Action_Arg pos_x, Action_Arg pos_y, Action_Arg dir, Action_Arg mode);

void en_spider_stopShoot(Enemy* spider, Action_Arg arg0, Action_Arg arg1, Action_Arg arg2, Action_Arg arg3, Action_Arg arg4, Action_Arg arg5);

void en_spider_setAnim(Enemy* spider, Action_Arg anim, Action_Arg vel_y, Action_Arg pos_x, Action_Arg pos_y, Action_Arg dir, Action_Arg mode);

#endif /* en_spider_h */
