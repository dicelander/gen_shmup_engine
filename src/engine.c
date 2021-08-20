#include <genesis.h>
#include "../inc/engine.h"

static Entity *pplayer;
static Shots *pshots;
static Enemies *penemies;

static const fix16 f16sin[32][32] = { {0,64,64,64,64,64,64,64,64,64,64,64,64,64,64,64,64,64,64,64,64,64,64,64,64,64,64,64,64,64,64,64},{0,45,57,60,62,62,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63},{0,28,45,53,57,59,60,61,62,62,62,62,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63},{0,20,35,45,51,54,57,58,59,60,61,61,62,62,62,62,62,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63},{0,15,28,38,45,49,53,55,57,58,59,60,60,61,61,61,62,62,62,62,62,62,62,63,63,63,63,63,63,63,63,63},{0,12,23,32,39,45,49,52,54,55,57,58,59,59,60,60,61,61,61,61,62,62,62,62,62,62,62,62,63,63,63,63},{0,10,20,28,35,40,45,48,51,53,54,56,57,58,58,59,59,60,60,61,61,61,61,61,62,62,62,62,62,62,62,62},{0,9,17,25,31,37,41,45,48,50,52,53,55,56,57,57,58,59,59,60,60,60,60,61,61,61,61,61,62,62,62,62},{0,7,15,22,28,33,38,42,45,47,49,51,53,54,55,56,57,57,58,58,59,59,60,60,60,60,61,61,61,61,61,61},{0,7,13,20,25,31,35,39,42,45,47,49,51,52,53,54,55,56,57,57,58,58,59,59,59,60,60,60,60,61,61,61},{0,6,12,18,23,28,32,36,39,42,45,47,49,50,52,53,54,55,55,56,57,57,58,58,59,59,59,60,60,60,60,60},{0,5,11,16,21,26,30,34,37,40,43,45,47,48,50,51,52,53,54,55,56,56,57,57,58,58,58,59,59,59,60,60},{0,5,10,15,20,24,28,32,35,38,40,43,45,47,48,49,51,52,53,54,54,55,56,56,57,57,58,58,58,59,59,59},{0,4,9,14,18,22,26,30,33,36,39,41,43,45,46,48,49,50,51,52,53,54,55,55,56,56,57,57,58,58,58,59},{0,4,9,13,17,21,25,28,31,34,37,39,41,43,45,46,48,49,50,51,52,53,53,54,55,55,56,56,57,57,57,58},{0,4,8,12,16,20,23,27,30,32,35,37,39,41,43,45,46,47,49,50,51,52,52,53,54,54,55,55,56,56,57,57},{0,3,7,11,15,19,22,25,28,31,33,36,38,40,42,43,45,46,47,48,49,50,51,52,53,53,54,55,55,56,56,56},{0,3,7,11,14,18,21,24,27,29,32,34,36,38,40,42,43,45,46,47,48,49,50,51,52,52,53,54,54,55,55,56},{0,3,7,10,13,17,20,23,25,28,31,33,35,37,39,40,42,43,45,46,47,48,49,50,51,51,52,53,53,54,54,55},{0,3,6,9,13,16,19,22,24,27,29,32,34,36,37,39,41,42,44,45,46,47,48,49,50,50,51,52,52,53,54,54},{0,3,6,9,12,15,18,21,23,26,28,30,32,34,36,38,39,41,42,44,45,46,47,48,49,49,50,51,52,52,53,53},{0,3,6,9,11,14,17,20,22,25,27,29,31,33,35,37,38,40,41,42,44,45,46,47,48,49,49,50,51,51,52,52},{0,2,5,8,11,14,16,19,21,24,26,28,30,32,34,36,37,39,40,41,43,44,45,46,47,48,48,49,50,50,51,52},{0,2,5,8,10,13,16,18,21,23,25,27,29,31,33,34,36,38,39,40,41,43,44,45,46,47,47,48,49,50,50,51},{0,2,5,7,10,13,15,17,20,22,24,26,28,30,32,33,35,36,38,39,40,42,43,44,45,46,47,47,48,49,49,50},{0,2,5,7,10,12,14,17,19,21,23,25,27,29,31,32,34,35,37,38,39,41,42,43,44,45,46,46,47,48,49,49},{0,2,4,7,9,12,14,16,18,20,22,24,26,28,30,31,33,35,36,37,39,40,41,42,43,44,45,46,46,47,48,49},{0,2,4,7,9,11,13,16,18,20,22,24,25,27,29,31,32,34,35,36,38,39,40,41,42,43,44,45,46,46,47,48},{0,2,4,6,9,11,13,15,17,19,21,23,25,26,28,30,31,33,34,35,37,38,39,40,41,42,43,44,45,46,46,47},{0,2,4,6,8,10,12,15,17,18,20,22,24,26,27,29,30,32,33,35,36,37,38,39,40,41,42,43,44,45,46,46},{0,2,4,6,8,10,12,14,16,18,20,22,23,25,27,28,30,31,32,34,35,36,37,38,39,40,41,42,43,44,45,45},{0,2,4,6,8,10,12,14,15,17,19,21,23,24,26,27,29,30,32,33,34,35,37,38,39,40,41,42,42,43,44,45}
};

/*
static const fix16 f16sin[32][32] = {
    {0x00,0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x40},
    {0x00,0x2d,0x39,0x3c,0x3e,0x3e,0x3f,0x3f,0x3f,0x3f,0x3f,0x3f,0x3f,0x3f,0x3f,0x3f,0x3f,0x3f,0x3f,0x3f,0x3f,0x3f,0x3f,0x3f,0x3f,0x3f,0x3f,0x3f,0x3f,0x3f,0x3f,0x3f},
    {0x00,0x1c,0x2d,0x35,0x39,0x3b,0x3c,0x3d,0x3e,0x3e,0x3e,0x3e,0x3f,0x3f,0x3f,0x3f,0x3f,0x3f,0x3f,0x3f,0x3f,0x3f,0x3f,0x3f,0x3f,0x3f,0x3f,0x3f,0x3f,0x3f,0x3f,0x3f},
    {0x00,0x14,0x23,0x2d,0x33,0x36,0x39,0x3a,0x3b,0x3c,0x3d,0x3d,0x3e,0x3e,0x3e,0x3e,0x3e,0x3f,0x3f,0x3f,0x3f,0x3f,0x3f,0x3f,0x3f,0x3f,0x3f,0x3f,0x3f,0x3f,0x3f,0x3f},
    {0x00,0x0f,0x1c,0x26,0x2d,0x31,0x35,0x37,0x39,0x3a,0x3b,0x3c,0x3c,0x3d,0x3d,0x3d,0x3e,0x3e,0x3e,0x3e,0x3e,0x3e,0x3e,0x3f,0x3f,0x3f,0x3f,0x3f,0x3f,0x3f,0x3f,0x3f},
    {0x00,0x0c,0x17,0x20,0x27,0x2d,0x31,0x34,0x36,0x37,0x39,0x3a,0x3b,0x3b,0x3c,0x3c,0x3d,0x3d,0x3d,0x3d,0x3e,0x3e,0x3e,0x3e,0x3e,0x3e,0x3e,0x3e,0x3f,0x3f,0x3f,0x3f},
    {0x00,0x0a,0x14,0x1c,0x23,0x28,0x2d,0x30,0x33,0x35,0x36,0x38,0x39,0x3a,0x3a,0x3b,0x3b,0x3c,0x3c,0x3d,0x3d,0x3d,0x3d,0x3d,0x3e,0x3e,0x3e,0x3e,0x3e,0x3e,0x3e,0x3e},
    {0x00,0x09,0x11,0x19,0x1f,0x25,0x29,0x2d,0x30,0x32,0x34,0x35,0x37,0x38,0x39,0x39,0x3a,0x3b,0x3b,0x3c,0x3c,0x3c,0x3c,0x3d,0x3d,0x3d,0x3d,0x3d,0x3e,0x3e,0x3e,0x3e},
    {0x00,0x07,0x0f,0x16,0x1c,0x21,0x26,0x2a,0x2d,0x2f,0x31,0x33,0x35,0x36,0x37,0x38,0x39,0x39,0x3a,0x3a,0x3b,0x3b,0x3c,0x3c,0x3c,0x3c,0x3d,0x3d,0x3d,0x3d,0x3d,0x3d},
    {0x00,0x07,0x0d,0x14,0x19,0x1f,0x23,0x27,0x2a,0x2d,0x2f,0x31,0x33,0x34,0x35,0x36,0x37,0x38,0x39,0x39,0x3a,0x3a,0x3b,0x3b,0x3b,0x3c,0x3c,0x3c,0x3c,0x3d,0x3d,0x3d},
    {0x00,0x06,0x0c,0x12,0x17,0x1c,0x20,0x24,0x27,0x2a,0x2d,0x2f,0x31,0x32,0x34,0x35,0x36,0x37,0x37,0x38,0x39,0x39,0x3a,0x3a,0x3b,0x3b,0x3b,0x3c,0x3c,0x3c,0x3c,0x3c},
    {0x00,0x05,0x0b,0x10,0x15,0x1a,0x1e,0x22,0x25,0x28,0x2b,0x2d,0x2f,0x30,0x32,0x33,0x34,0x35,0x36,0x37,0x38,0x38,0x39,0x39,0x3a,0x3a,0x3a,0x3b,0x3b,0x3b,0x3c,0x3c},
    {0x00,0x05,0x0a,0x0f,0x14,0x18,0x1c,0x20,0x23,0x26,0x28,0x2b,0x2d,0x2f,0x30,0x31,0x33,0x34,0x35,0x36,0x36,0x37,0x38,0x38,0x39,0x39,0x3a,0x3a,0x3a,0x3b,0x3b,0x3b},
    {0x00,0x04,0x09,0x0e,0x12,0x16,0x1a,0x1e,0x21,0x24,0x27,0x29,0x2b,0x2d,0x2e,0x30,0x31,0x32,0x33,0x34,0x35,0x36,0x37,0x37,0x38,0x38,0x39,0x39,0x3a,0x3a,0x3a,0x3b},
    {0x00,0x04,0x09,0x0d,0x11,0x15,0x19,0x1c,0x1f,0x22,0x25,0x27,0x29,0x2b,0x2d,0x2e,0x30,0x31,0x32,0x33,0x34,0x35,0x35,0x36,0x37,0x37,0x38,0x38,0x39,0x39,0x39,0x3a},
    {0x00,0x04,0x08,0x0c,0x10,0x14,0x17,0x1b,0x1e,0x20,0x23,0x25,0x27,0x29,0x2b,0x2d,0x2e,0x2f,0x31,0x32,0x33,0x34,0x34,0x35,0x36,0x36,0x37,0x37,0x38,0x38,0x39,0x39},
    {0x00,0x03,0x07,0x0b,0x0f,0x13,0x16,0x19,0x1c,0x1f,0x21,0x24,0x26,0x28,0x2a,0x2b,0x2d,0x2e,0x2f,0x30,0x31,0x32,0x33,0x34,0x35,0x35,0x36,0x37,0x37,0x38,0x38,0x38},
    {0x00,0x03,0x07,0x0b,0x0e,0x12,0x15,0x18,0x1b,0x1d,0x20,0x22,0x24,0x26,0x28,0x2a,0x2b,0x2d,0x2e,0x2f,0x30,0x31,0x32,0x33,0x34,0x34,0x35,0x36,0x36,0x37,0x37,0x38},
    {0x00,0x03,0x07,0x0a,0x0d,0x11,0x14,0x17,0x19,0x1c,0x1f,0x21,0x23,0x25,0x27,0x28,0x2a,0x2b,0x2d,0x2e,0x2f,0x30,0x31,0x32,0x33,0x33,0x34,0x35,0x35,0x36,0x36,0x37},
    {0x00,0x03,0x06,0x09,0x0d,0x10,0x13,0x16,0x18,0x1b,0x1d,0x20,0x22,0x24,0x25,0x27,0x29,0x2a,0x2c,0x2d,0x2e,0x2f,0x30,0x31,0x32,0x32,0x33,0x34,0x34,0x35,0x36,0x36},
    {0x00,0x03,0x06,0x09,0x0c,0x0f,0x12,0x15,0x17,0x1a,0x1c,0x1e,0x20,0x22,0x24,0x26,0x27,0x29,0x2a,0x2c,0x2d,0x2e,0x2f,0x30,0x31,0x31,0x32,0x33,0x34,0x34,0x35,0x35},
    {0x00,0x03,0x06,0x09,0x0b,0x0e,0x11,0x14,0x16,0x19,0x1b,0x1d,0x1f,0x21,0x23,0x25,0x26,0x28,0x29,0x2a,0x2c,0x2d,0x2e,0x2f,0x30,0x31,0x31,0x32,0x33,0x33,0x34,0x34},
    {0x00,0x02,0x05,0x08,0x0b,0x0e,0x10,0x13,0x15,0x18,0x1a,0x1c,0x1e,0x20,0x22,0x24,0x25,0x27,0x28,0x29,0x2b,0x2c,0x2d,0x2e,0x2f,0x30,0x30,0x31,0x32,0x32,0x33,0x34},
    {0x00,0x02,0x05,0x08,0x0a,0x0d,0x10,0x12,0x15,0x17,0x19,0x1b,0x1d,0x1f,0x21,0x22,0x24,0x26,0x27,0x28,0x29,0x2b,0x2c,0x2d,0x2e,0x2f,0x2f,0x30,0x31,0x32,0x32,0x33},
    {0x00,0x02,0x05,0x07,0x0a,0x0d,0x0f,0x11,0x14,0x16,0x18,0x1a,0x1c,0x1e,0x20,0x21,0x23,0x24,0x26,0x27,0x28,0x2a,0x2b,0x2c,0x2d,0x2e,0x2f,0x2f,0x30,0x31,0x31,0x32},
    {0x00,0x02,0x05,0x07,0x0a,0x0c,0x0e,0x11,0x13,0x15,0x17,0x19,0x1b,0x1d,0x1f,0x20,0x22,0x23,0x25,0x26,0x27,0x29,0x2a,0x2b,0x2c,0x2d,0x2e,0x2e,0x2f,0x30,0x31,0x31},
    {0x00,0x02,0x04,0x07,0x09,0x0c,0x0e,0x10,0x12,0x14,0x16,0x18,0x1a,0x1c,0x1e,0x1f,0x21,0x23,0x24,0x25,0x27,0x28,0x29,0x2a,0x2b,0x2c,0x2d,0x2e,0x2e,0x2f,0x30,0x31},
    {0x00,0x02,0x04,0x07,0x09,0x0b,0x0d,0x10,0x12,0x14,0x16,0x18,0x19,0x1b,0x1d,0x1f,0x20,0x22,0x23,0x24,0x26,0x27,0x28,0x29,0x2a,0x2b,0x2c,0x2d,0x2e,0x2e,0x2f,0x30},
    {0x00,0x02,0x04,0x06,0x09,0x0b,0x0d,0x0f,0x11,0x13,0x15,0x17,0x19,0x1a,0x1c,0x1e,0x1f,0x21,0x22,0x23,0x25,0x26,0x27,0x28,0x29,0x2a,0x2b,0x2c,0x2d,0x2e,0x2e,0x2f},
    {0x00,0x02,0x04,0x06,0x08,0x0a,0x0c,0x0f,0x11,0x12,0x14,0x16,0x18,0x1a,0x1b,0x1d,0x1e,0x20,0x21,0x23,0x24,0x25,0x26,0x27,0x28,0x29,0x2a,0x2b,0x2c,0x2d,0x2e,0x2e},
    {0x00,0x02,0x04,0x06,0x08,0x0a,0x0c,0x0e,0x10,0x12,0x14,0x16,0x17,0x19,0x1b,0x1c,0x1e,0x1f,0x20,0x22,0x23,0x24,0x25,0x26,0x27,0x28,0x29,0x2a,0x2b,0x2c,0x2d,0x2d,},
    {0x00,0x02,0x04,0x06,0x08,0x0a,0x0c,0x0e,0x0f,0x11,0x13,0x15,0x17,0x18,0x1a,0x1b,0x1d,0x1e,0x20,0x21,0x22,0x23,0x25,0x26,0x27,0x28,0x29,0x2a,0x2a,0x2b,0x2c,0x2d}
}
*/

void killEntity(Entity* e){
    e->health = 0;
    SPR_setVisibility(e->sprite,HIDDEN);
    SPR_releaseSprite(e->sprite);
    e->state = DEAD;
};

void reviveEntity(Entity* e){
    e->health = 1;
    SPR_setVisibility(e->sprite,VISIBLE);
};

int collideEntities(Entity* a, Entity* b) {
    return (a->x + a->offset_x < b->x + b->offset_x + b->w && a->x + a->offset_x + a->w > b->x + b->offset_x && a->y + a->offset_y < b->y + b->offset_y + b->h && a->y + a->offset_y + a->h >= b->y + b->offset_y);
};

void spawnEnemy(Enemies* enemies, u16 type, u16 path, s16 pos_x, s16 pos_y, const Pathing* Behaviour) {
    int i = 0;
    VDP_drawText("SPAWN_ENEMY", 0, 6);
    if (enemies->enemiesOnScreen < MAX_ENEMIES) {
        while (enemies->enemy[i].state != DEAD) {
            i++;
            VDP_drawText("A", 5, i);
        }
        enemies->enemy[i].x = pos_x;
        enemies->enemy[i].y = pos_y;
        enemies->enemy[i].w = FIX16(16);
        enemies->enemy[i].h = FIX16(16);
        enemies->enemy[i].velx = 0;
        enemies->enemy[i].vely = 0;
        enemies->enemy[i].health = 1;
        //enemies->enemy[i].weapon_x = 6;
        //enemies->enemy[i].weapon_y = 16;
        enemies->enemy[i].state = ALIVE;
        enemies->enemy[i].sprite = SPR_addSprite(&enemy1,enemies->enemy[i].x,enemies->enemy[i].y,TILE_ATTR(PAL1,0,0,0));
        enemies->enemy[i].type = type;
        enemies->enemy[i].path = path;
        enemies->enemy[i].pathstate = 0;
        enemies->enemy[i].timer = 0;
        enemies->enemy[i].actionpointer = Behaviour->action;
        enemies->enemy[i].directionpointer = Behaviour->direction;
        enemies->enemy[i].velxpointer = Behaviour->velx;
        enemies->enemy[i].velypointer = Behaviour->vely;
        enemies->enemiesOnScreen++;
    }
};

void shoot(Shots* shots, Entity* player){
//    KLog("Shot function called");
//    KLog_U1("shots->shotsOnScreen = ", shots->shotsOnScreen);
    int i = 0;
    if (shots->shotsOnScreen < 2*MAX_SHOTS) {
        while (shots->playerShot[i].health > 0) {
            i++;
        }
//        KLog_U1("Shots Function [i]  = ", i);
        shots->playerShot[i].x = player->x+FIX16(8);
//        KLog_f1("player->x = ", player->x);
//        KLog_f1("shots->playerShot[i].x = ", shots->playerShot[i].x);
        shots->playerShot[i].y = player->y;
//        KLog_f1("player->y = ", player->y);
//        KLog_f1("shots->playerShot[i].y = ", shots->playerShot[i].y);
        shots->playerShot[i].w = FIX16(8);
//        KLog_f1("shots->playerShot[i].w = ", shots->playerShot[i].w);
        shots->playerShot[i].h = FIX16(8);
//        KLog_f1("shots->playerShot[i].h = ", shots->playerShot[i].h);
        //        reviveEntity(&shots[i]);
        shots->playerShot[i].vely = FIX16(-5);
        shots->playerShot[i].velx = 0;
        shots->playerShot[i].health = 1;
        shots->playerShot[i].sprite = SPR_addSprite(&peashtr,fix16ToInt(shots->playerShot[i].x),fix16ToInt(shots->playerShot[i].y),TILE_ATTR(PAL1,0,FALSE,FALSE));
        
        KLog_U2("Shot position on screen x = ", fix16ToInt(shots->playerShot[i].x), ", y = ", fix16ToInt(shots->playerShot[i].y));
        shots->shotsOnScreen++;
    }
    //    if (nShotsOnScreen < MAX_SHOTS) {
    //        while (shots[i] == TRUE) {
    //            i++;
    //        }
    //        shotPos[i][0] = (player.x+12)%39;
    //        shotPos[i][1] = (player.y+PLAYER_Y_OFFSET-2);
    //        shots0[i] = TRUE;
    //        nShotsOnScreen++;
    //    }
};

int sign(int x) {
    return (x > 0) - (x < 0);
}

void getSinCos(int dx, int dy, fix16 sincos[2]) {
    while (abs(dx) > 31 || abs(dy) > 31) {
        
//        KLog_S2("sc dx = ", dx, " sc dy = ", dy);
        
        dx >>= 1;
        dy >>= 1;
    }
//    KLog_S2("sc dx = ", dx, " sc dy = ", dy);
    sincos[0] = sign(dy)*f16sin[abs(dx)][abs(dy)];
    sincos[1] = sign(dx)*f16sin[abs(dy)][abs(dx)];
}

void enemyShoot(Shots* shots, Entity* enemy){
    u16 i;
    Entity *player = getPointerPlayer();
    if (shots->shotsOnScreen < 2*MAX_SHOTS) {
        while (shots->enShot[i].state != DEAD) {
            i++;
        }
        fix16 sincos[2];
        shots->enShot[i].x = enemy->x;
        shots->enShot[i].y = enemy->y;
        shots->enShot[i].w = FIX16(8);
        shots->enShot[i].h = FIX16(8);
        getSinCos(fix16ToInt(enemy->x - player->x),fix16ToInt(enemy->y - player->y),sincos);
        //        reviveEntity(&shots[i]);
        shots->enShot[i].vely = fix16Mul(sincos[0], FIX16(1));
        shots->enShot[i].velx = fix16Mul(sincos[1], FIX16(1));
        shots->enShot[i].health = 1;
        shots->enShot[i].sprite = SPR_addSprite(&peashtr,fix16ToInt(shots->enShot[i].x),fix16ToInt(shots->enShot[i].y),TILE_ATTR(PAL1,0,FALSE,FALSE));
        shots->shotsOnScreen++;
    }
}

void initShots(Shots* shots) {
    u16 i;
    for (i=0; i<MAX_SHOTS; i++) {
        shots->playerShot[i].x = 0;
        shots->playerShot[i].y = 0;
        shots->playerShot[i].offset_x = 0;
        shots->playerShot[i].offset_y = 0;
        shots->playerShot[i].w = 0;
        shots->playerShot[i].h = 0;
        shots->playerShot[i].velx = 0;
        shots->playerShot[i].vely = 0;
        shots->playerShot[i].health = 0;
        shots->playerShot[i].sprite = NULL;
        shots->playerShot[i].type = 0;
        shots->playerShot[i].path = 0;
        shots->playerShot[i].pathstate = 0;
        shots->playerShot[i].timer = 0;
        shots->playerShot[i].direction = 0;
        shots->playerShot[i].state = DEAD;
    }
    for (i=0; i<MAX_SHOTS; i++) {
        shots->enShot[i].x = 0;
        shots->enShot[i].y = 0;
        shots->enShot[i].offset_x = 0;
        shots->enShot[i].offset_y = 0;
        shots->enShot[i].w = 0;
        shots->enShot[i].h = 0;
        shots->enShot[i].velx = 0;
        shots->enShot[i].vely = 0;
        shots->enShot[i].health = 0;
        shots->enShot[i].sprite = NULL;
        shots->enShot[i].type = 0;
        shots->enShot[i].path = 0;
        shots->enShot[i].pathstate = 0;
        shots->enShot[i].timer = 0;
        shots->enShot[i].direction = 0;
        shots->enShot[i].state = DEAD;
    }
    shots->shotsOnScreen = 0;
    pshots = shots;
}

Shots *getPointerShots() {
    return pshots;
}

void setPointerShots(Shots *shots) {
    pshots = shots;
}

void setPointerPlayer(Entity *player) {
    pplayer = player;
}

Entity *getPointerPlayer() {
    return pplayer;
}

void moveShots(Shots* shots) {
    u16 i = 0;
    for (i = 0; i < MAX_SHOTS; i++) {
        if(shots->playerShot[i].health > 0) {
            if(fix16Add(shots->playerShot[i].y, shots->playerShot[i].h) < TOP_EDGE || (shots->playerShot[i].x + shots->playerShot[i].w) < LEFT_EDGE || shots->playerShot[i].x > RIGHT_EDGE) {
//                KLog_f1("shots->playerShot[i].y + shots->playerShot[i].h = ", fix16Add(shots->playerShot[i].y, shots->playerShot[i].h));
//                KLog_f1("TOP_EDGE (<)", TOP_EDGE);
//                KLog_f1("shots->playerShot[i].x + shots->playerShot[i].w = ", fix16Add(shots->playerShot[i].x, shots->playerShot[i].w));
//                KLog_f1("LEFT_EDGE (<)", LEFT_EDGE);
//                KLog_f1("shots->playerShot[i].x = ", shots->playerShot[i].x);
//                KLog_f1("RIGHT_EDGE (>)", RIGHT_EDGE);
                killEntity(&shots->playerShot[i]);
                shots->shotsOnScreen--;
//                KLog_U2("Player shot on index ", i, " removed by moveShots, shotOnScreen now at ", shots->shotsOnScreen);
            }
            else {
                shots->playerShot[i].x += shots->playerShot[i].velx;
                shots->playerShot[i].y += shots->playerShot[i].vely;
                SPR_setPosition(shots->playerShot[i].sprite, fix16ToInt(shots->playerShot[i].x), fix16ToInt(shots->playerShot[i].y));
            }
        }
        if(shots->enShot[i].health > 0) {
            if(shots->enShot[i].y > BOTTOM_EDGE || (shots->enShot[i].x + shots->enShot[i].w) < LEFT_EDGE || shots->enShot[i].x > RIGHT_EDGE) {
//                KLog("Shot will be destroyed due to leaving screen, the following condition is true:");
//                KLog_U3("shots->enShot[i].y > BOTTOM_EDGE", shots->enShot[i].y > BOTTOM_EDGE, "(shots->enShot[i].x + shots->enShot[i].w) < LEFT_EDGE", (shots->enShot[i].x + shots->enShot[i].w) < LEFT_EDGE, "shots->enShot[i].x > RIGHT_EDGE", shots->enShot[i].x > RIGHT_EDGE);
                killEntity(&shots->enShot[i]);
                shots->shotsOnScreen--;
            } else {
//                KLog("Updating enemy shot positions");
                shots->enShot[i].x += shots->enShot[i].velx;
                shots->enShot[i].y += shots->enShot[i].vely;
                SPR_setPosition(shots->enShot[i].sprite, fix16ToInt(shots->enShot[i].x), fix16ToInt(shots->enShot[i].y));
            }
        }
    }
//        if(shots->enShot[i].state == ALIVE) {
//            if((shots->enShot[i].y + shots->enShot[i].h) > BOTTOM_EDGE || (shots->playerShot[i].x + shots->playerShot[i].w) < LEFT_EDGE || shots->playerShot[i].x > RIGHT_EDGE) {
//                killEntity(&shots->enShot[i]);
//                shots->shotsOnScreen--;
//            } else {
//                shots->enShot[i].x += fix16ToInt(shots->enShot[i].velx);
//                shots->enShot[i].y += fix16ToInt(shots->enShot[i].vely);
//                SPR_setPosition(shots->enShot[i].sprite, shots->enShot[i].x, shots->enShot[i].y);
//            }
//    }
}

void enShotCollisions (Enemies* enemies, Shots* shots) {
    int i = 0;
    int j = 0;
    for (i = 0; i < MAX_SHOTS; i++) {
        for (j = 0; j < MAX_ENEMIES; j++) {
            if (shots->playerShot[i].health > 0 && enemies->enemy[j].health > 0) {
                if(collideEntities(&shots->playerShot[i], &enemies->enemy[j])) {
                    enemies->enemy[j].health -= shots->playerShot[i].health;
                    killEntity(&shots->playerShot[i]);
                    shots->shotsOnScreen--;
                }
            }
        }
    }
}

void enPlayerCollisions (Enemies* enemies, Entity* player) {
    u16 j;
    for (j = 0; j < MAX_ENEMIES; j++) {
        if (enemies->enemy[j].state == ALIVE) {
            if(collideEntities(&enemies->enemy[j], player)) {
                //do something
            }
        }
    }
}

fix16 diagonal() {
    return 0x2D; //0,71*64
    //return FIX16(DIAGONAL);
}

fix16 diagonalAdjust(fix16 value) {
    return fix16Mul(value, diagonal());
}

void movePlayer(Entity* player) {
    
    if((player->velx != 0) & (player->vely != 0)) {
        player->x += fix16Mul(player->velx, diagonal());
        player->y += fix16Mul(player->vely, diagonal());
    } else {
        player->x += player->velx;
        player->y += player->vely;
    }
    
    if (player->x + player->offset_x < LEFT_EDGE) player->x = LEFT_EDGE - player->offset_x;
    else if (player->x + player->offset_x + player->w > RIGHT_EDGE) player->x = RIGHT_EDGE - (player->w + player->offset_x);
    if (player->y + player->offset_y < TOP_EDGE) player->y = TOP_EDGE - player->offset_y;
    else if (player->y + player->h + player->offset_y > BOTTOM_EDGE) {
        player->y = BOTTOM_EDGE - (player->h + player->offset_y);
    }
    
    SPR_setPosition(player->sprite, fix16ToInt(player->x), fix16ToInt(player->y));
}

//u16 getShotsOnScreen() {
//    return shots.ShotsOnScreen;
//}

//void changeEnemyDirection(Entity* e){
//    switch (e->direction) {
//        case ENEMY_DOWN:
//            SPR_setHFlip(e->sprite, 0);
//            SPR_setVFlip(e->sprite, 0);
//            SPR_setAnim(e->sprite, 0);
//            break;
//        case ENEMY_DOWN_RIGHT:
//            SPR_setHFlip(e->sprite, 0);
//            SPR_setVFlip(e->sprite, 0);
//            SPR_setAnim(e->sprite, ENEMY_DOWN_RIGHT);
//            break;
//        case ENEMY_DOWN_LEFT:
//            SPR_setHFlip(e->sprite, 0);
//            SPR_setVFlip(e->sprite, 0);
//            SPR_setAnim(e->sprite, ENEMY_DOWN_LEFT);
//            break;
//        case ENEMY_RIGHT:
//            SPR_setHFlip(e->sprite, 0);
//            SPR_setVFlip(e->sprite, 0);
//            SPR_setAnim(e->sprite, ENEMY_RIGHT);
//            break;
//        case ENEMY_LEFT:
//            SPR_setHFlip(e->sprite, 0);
//            SPR_setVFlip(e->sprite, 0);
//            SPR_setAnim(e->sprite, ENEMY_LEFT);
//            break;
//        case ENEMY_UP_RIGHT:
//            SPR_setHFlip(e->sprite, 0);
//            SPR_setVFlip(e->sprite, 0);
//            SPR_setAnim(e->sprite, ENEMY_UP_RIGHT);
//            break;
//        case ENEMY_UP_LEFT:
//            SPR_setHFlip(e->sprite, 0);
//            SPR_setVFlip(e->sprite, 0);
//            SPR_setAnim(e->sprite, ENEMY_UP_LEFT);
//            break;
//        case ENEMY_UP:
//            SPR_setHFlip(e->sprite, 0);
//            SPR_setVFlip(e->sprite, 0);
//            SPR_setAnim(e->sprite, ENEMY_UP);
//            break;
//    }
//}

//static void restart() {
//    if (gameover) {
//        killEntity(&player);
//        shotsOnScreen = 0;
//        enemies.enemiesOnScreen = 0;
//        for (int i = 0; i<MAX_SHOTS; i++) killEntity(&shots[i]);
//        for (int i = 0; i<MAX_ENEMIES; i++) killEntity(&enemies.enemy[i]);
//        difficulty = 1;
//        score = 0;
//        prevDifficulty = 0;
//        combo = 1;
//        state = TRUE;
//    }
//}
