//
//  enemies.c
//  gen_shmupc
//
//  Created by Victor "dicelander" Sander on 23/08/21.
//

#include <enemies.h>
#include "../inc/enemies.h"

#define LEFT_EDGE FIX16(0)
#define RIGHT_EDGE FIX16(320)
#define TOP_EDGE FIX16(0)
#define BOTTOM_EDGE FIX16(224)

static Enemies *en_enemies_ptr;

Enemies *EN_getEnemiesPtr() {
    return en_enemies_ptr;
}

void EN_setEnemiesPtr(Enemies *enemies) {
    en_enemies_ptr = enemies;
}

static En_Shots *en_shots_ptr;

En_Shots *EN_getShotsPtr() {
    return en_shots_ptr;
}

void EN_setShotsPtr(En_Shots *shots) {
    en_shots_ptr = shots;
}

void EN_initShots(En_Shots *shots) {
    u16 ii;
    for (ii=0; ii<MAX_ENEMY_SHOTS; ii++) {
        shots->shot[ii].pos_x = 0;
        shots->shot[ii].pos_y = 0;
        shots->shot[ii].offset_x = 0;
        shots->shot[ii].offset_y = 0;
        shots->shot[ii].width = 0;
        shots->shot[ii].height = 0;
        shots->shot[ii].vel_x = 0;
        shots->shot[ii].vel_y = 0;
        shots->shot[ii].health = 0;
        shots->shot[ii].sprite = NULL;
        shots->shot[ii].type = 0;
        shots->shot[ii].timer = 0;
        shots->shot[ii].direction = 0;
        shots->shot[ii].status = DEAD;
    }
    shots->en_shotsonscreen = 0;
    en_shots_ptr = shots;
}

void EN_killEnemy(Enemy* e){
    e->health = 0;
    SPR_setVisibility(e->sprite,HIDDEN);
    SPR_releaseSprite(e->sprite);
    e->status = DEAD;
};

void en1_Shoot(Enemy* enemyptr, Action_Arg arg0, Action_Arg arg1, Action_Arg arg2, Action_Arg arg3, Action_Arg arg4, Action_Arg arg5) {
    
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

void en1_changeVelocity(Enemy* enemy, Action_Arg vel_x, Action_Arg vel_y, Action_Arg pos_x, Action_Arg pos_y, Action_Arg dir, Action_Arg arg5) {
    enemy->vel_x = vel_x.fix16;
    enemy->vel_y = vel_y.fix16;
//    enemy->pos_x += fix16ToInt(enemy->vel_x);
//    enemy->pos_y += fix16ToInt(enemy->vel_y); usar outra função pra atualizar a posição ou atualizar a posição de todo mundo em todo frame (SPR_setPosition(Sproite *sprite, s16 x, s16 y) ja existe pra isso).
    enemy->direction = dir.u16;
    SPR_setAnim(enemy->sprite, enemy->direction); //isso precisa ficar aqui?
//    KLog_f2("vel_x recebido = ", *((fix16*) vel_x), " vel_y recebido = ", *((fix16*) vel_y));
//    KLog_f2("vel_x colocado = ", enemy->vel_x , " vel_y colocado = ", enemy->vel_y);
//    KLog_U1("direction = ", (int) enemy->direction);
//    KLog_U1("frame = ", (int) enemy->timer);
}


void en1_changePosition(Enemy* enemy, Action_Arg pos_x, Action_Arg pos_y, Action_Arg dir, Action_Arg zerospeed, Action_Arg arg5) { //pretty much teleports
    enemy->pos_y = pos_y.fix16;
    enemy->pos_x = pos_x.fix16;
    enemy->direction = dir.u16;
    //colocar opcao de zerar velocidade ou nao
}

void en1_chgaction(Enemy* enemy, Action_Arg arg0, Action_Arg arg1, Action_Arg arg2, Action_Arg arg3, Action_Arg arg4, Action_Arg arg5) {

}

void en1_condchgaction(Action_Arg arg0, Action_Arg arg1, Action_Arg arg2, Action_Arg arg3, Action_Arg arg4, Action_Arg arg5) {
    
}

void EN_updateEnemies(Enemies *enemies){
    u16 ii = 0;
    for (ii = 0; ii < MAX_ENEMIES; ii++) {
        switch (enemies->enemy[ii].status) {
            case DEAD:
                break;
            case ALIVE:
                if(enemies->enemy[ii].health > 0) {
                    while(enemies->enemy[ii].timer == enemies->enemy[ii].pattern->actionframes[enemies->enemy[ii].nextpatternstate]) {
                        enemies->enemy[ii].pattern->actions[enemies->enemy[ii].nextpatternstate](&enemies->enemy[ii], enemies->enemy[ii].pattern->arg0[enemies->enemy[ii].nextpatternstate], enemies->enemy[ii].pattern->arg1[enemies->enemy[ii].nextpatternstate], enemies->enemy[ii].pattern->arg2[enemies->enemy[ii].nextpatternstate], enemies->enemy[ii].pattern->arg3[enemies->enemy[ii].nextpatternstate], enemies->enemy[ii].pattern->arg4[enemies->enemy[ii].nextpatternstate], enemies->enemy[ii].pattern->arg5[enemies->enemy[ii].nextpatternstate]);
                        enemies->enemy[ii].nextpatternstate++;
                    }
                    enemies->enemy[ii].pos_x += enemies->enemy[ii].vel_x;
                    enemies->enemy[ii].pos_y += enemies->enemy[ii].vel_y;
                    SPR_setPosition(enemies->enemy[ii].sprite, fix16ToInt(enemies->enemy[ii].pos_x), fix16ToInt(enemies->enemy[ii].pos_y));
                    enemies->enemy[ii].timer++;
                } else if(enemies->enemy[ii].health <= 0) {
                    enemies->enemy[ii].status = EXPLOSION;
                    SPR_releaseSprite(enemies->enemy[ii].sprite);
                    enemies->enemy[ii].sprite = SPR_addSprite(&explos, fix16ToInt(enemies->enemy[ii].pos_x), fix16ToInt(enemies->enemy[ii].pos_y), TILE_ATTR(PAL1,0,0,0));
                    enemies->enemy[ii].timer = 0;
                    enemies->enemy[ii].width = 0;
                    enemies->enemy[ii].height = 0;
                    enemies->enemy[ii].offset_x = 0;
                    enemies->enemy[ii].offset_y = 0;
                }
                break;
            case EXPLOSION:
                if(enemies->enemy[ii].timer < EXPLOSION_LENGHT) {
                    enemies->enemy[ii].timer++;
                } else if(enemies->enemy[ii].timer == EXPLOSION_LENGHT) {
                    EN_killEnemy(&enemies->enemy[ii]);
                    enemies->enemiesOnScreen--;
                }
                break;
            default:
                break;
        }
    }
}

void en1_spawnEnemy(Enemies* enemies, const u16 type, s16 pos_x, s16 pos_y, const Behaviour* behaviour){
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
        enemies->enemiesOnScreen++;
    }
}

void EN_killShot(En_Shot* e){
    e->health = 0;
    SPR_setVisibility(e->sprite,HIDDEN);
    SPR_releaseSprite(e->sprite);
    e->status = DEAD;
};

void EN_moveShots(En_Shots *shots) {
    u16 i = 0;
    for (i = 0; i < MAX_ENEMY_SHOTS; i++) {
        if(shots->shot[i].status == ALIVE) {
            if(shots->shot[i].pos_y > BOTTOM_EDGE || (shots->shot[i].pos_x + shots->shot[i].width) < LEFT_EDGE || shots->shot[i].pos_x > RIGHT_EDGE || (shots->shot[i].pos_y + shots->shot[i].height) < TOP_EDGE) {
                EN_killShot(&shots->shot[i]);
                shots->en_shotsonscreen--;
            } else {
                //                KLog("Updating enemy shot positions");
                shots->shot[i].pos_x += shots->shot[i].vel_x;
                shots->shot[i].pos_y += shots->shot[i].vel_y;
                SPR_setPosition(shots->shot[i].sprite, fix16ToInt(shots->shot[i].pos_x), fix16ToInt(shots->shot[i].pos_y));
            }
        }
    }
}
