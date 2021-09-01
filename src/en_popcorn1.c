//
//  en_popcorn1.c
//  gen_shmupc
//
//  Created by Victor "dicelander" Sander on 31/08/21.
//

#include "../inc/en_popcorn1.h"

void en_pc1_move(Enemy* enemy, Action_Arg arg0, Action_Arg arg1, Action_Arg arg2, Action_Arg arg3, Action_Arg arg4, Action_Arg arg5) {
    enemy->pos_x += enemy->vel_x;
    enemy->pos_y += enemy->vel_y;
    SPR_setPosition(enemy->sprite, fix16ToInt(enemy->pos_x), fix16ToInt(enemy->pos_y));
}

void en_pc1_spawn(Enemies* enemies, const u8 type, s16 pos_x, s16 pos_y, const Behaviour* behaviour){
    u16 i = 0;
    if (enemies->enemiesOnScreen < MAX_ENEMIES) {
        while (enemies->enemy[i].status != DEAD) {
            i++;
        }
        enemies->enemy[i].pos_x = FIX16(pos_x);
        enemies->enemy[i].pos_y = FIX16(pos_y);
        enemies->enemy[i].width = FIX16(16);
        enemies->enemy[i].height = FIX16(16);
        enemies->enemy[i].vel_x = 0;
        enemies->enemy[i].vel_y = 0;
        enemies->enemy[i].health = 1;
        //enemies->enemy[i].weapon_x = 6;
        //enemies->enemy[i].weapon_y = 16;
        enemies->enemy[i].status = ALIVE;
        enemies->enemy[i].sprite = SPR_addSprite(&enemy1,fix16ToInt(enemies->enemy[i].pos_x),fix16ToInt(enemies->enemy[i].pos_y),TILE_ATTR(PAL1,0,0,0));
        SPR_setDepth(enemies->enemy[i].sprite, SPR_MIN_DEPTH+1);
        //enemies->enemy[i].type = type;
        enemies->enemy[i].nextpatternstate = 0;
        enemies->enemy[i].timer = 0;
        enemies->enemy[i].pattern = behaviour;
        enemies->enemy[i].type.move = &en_pc1_move;
        enemies->enemiesOnScreen++;
    }
}

void en1_chgaction(Enemy* enemy, Action_Arg arg0, Action_Arg arg1, Action_Arg arg2, Action_Arg arg3, Action_Arg arg4, Action_Arg arg5) {

}

void en1_condchgaction(Action_Arg arg0, Action_Arg arg1, Action_Arg arg2, Action_Arg arg3, Action_Arg arg4, Action_Arg arg5) {
    
}

void en_pc1_changePosition(Enemy* enemy, Action_Arg pos_x, Action_Arg pos_y, Action_Arg dir, Action_Arg zerospeed, Action_Arg arg5) { //pretty much teleports
    enemy->pos_y = pos_y.fix16;
    enemy->pos_x = pos_x.fix16;
    enemy->direction = dir.u16;
    //colocar opcao de zerar velocidade ou nao
}

void en_pc1_changeVelocity(Enemy* enemy, Action_Arg vel_x, Action_Arg vel_y, Action_Arg pos_x, Action_Arg pos_y, Action_Arg dir, Action_Arg arg5) {
    enemy->vel_x = vel_x.fix16;
    enemy->vel_y = vel_y.fix16;
    enemy->direction = dir.u16;
    SPR_setAnim(enemy->sprite, enemy->direction);
}

void en_pc1_shoot(Enemy* enemyptr, Action_Arg arg0, Action_Arg arg1, Action_Arg arg2, Action_Arg arg3, Action_Arg arg4, Action_Arg arg5) {
    
    u16 ii;
    Player *player = PL_getPlayerPtr();
    En_Shots *shots = EN_getShotsPtr();
    Enemy* enemy = (Enemy *) enemyptr;
    if (shots->en_shotsonscreen < MAX_ENEMY_SHOTS) {
        while (shots->shot[ii].status != DEAD) {
            ii++;
        }
        shots->shot[ii].status = ALIVE;
        fix16 sincos[2];
        shots->shot[ii].pos_x = enemy->pos_x;
        shots->shot[ii].pos_y = enemy->pos_y;
        shots->shot[ii].width = FIX16(8);
        shots->shot[ii].height = FIX16(8);
        getSinCos(fix16ToInt(player->pos_x + FIX16(12) - enemy->pos_x), fix16ToInt(player->pos_y + FIX16(16) - enemy->pos_y), sincos);
        shots->shot[ii].vel_y = fix16Mul(sincos[0], FIX16(3));
        shots->shot[ii].vel_x = fix16Mul(sincos[1], FIX16(3));
        shots->shot[ii].health = 1;
        shots->shot[ii].sprite = SPR_addSprite(&en_bllt,fix16ToInt(shots->shot[ii].pos_x),fix16ToInt(shots->shot[ii].pos_y),TILE_ATTR(PAL1,0,FALSE,FALSE));
        SPR_setDepth(shots->shot[ii].sprite, SPR_MIN_DEPTH);
        shots->en_shotsonscreen++;
        }
}
