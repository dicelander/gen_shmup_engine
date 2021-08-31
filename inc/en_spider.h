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

void en_spawnSpider(Enemies* enemies, const u8 type, s16 pos_x, s16 pos_y, const Behaviour* behaviour);

void en_spiderShoot(Enemy* enemyptr, Action_Arg arg0, Action_Arg arg1, Action_Arg arg2, Action_Arg arg3, Action_Arg arg4, Action_Arg arg5);


#endif /* en_spider_h */
