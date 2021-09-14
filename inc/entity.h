//
//  entity.h
//  gen_shmupc
//
//  Created by Victor "dicelander" Sander on 13/09/21.
//

#ifndef entity_h
#define entity_h

#include <genesis.h>

typedef struct Entity Entity;

typedef union Action_Arg {
    fix16 fix16;
    u16 u16;
} Action_Arg;

typedef void (*Action)(Entity* entity, Action_Arg arg0, Action_Arg arg1, Action_Arg arg2, Action_Arg arg3);

struct Entity {
    fix16 pos_x;
    fix16 pos_y;
    //hitbox/dimensions related stuff (suposedly constant)
    fix16 offset_x;
    fix16 offset_y;
    fix16 width;
    fix16 height;
    //other properties (needs organizing)
    fix16 vel_x;
    fix16 vel_y;
    u16 direction;
    s8 health;
    u16 timer;
    u16 status;
    Sprite* sprite;
    Entity* parent;
    enum {player, shot, enemy} Type;
    struct {
        void (*move)(Entity* entity, Action_Arg arg0, Action_Arg arg1, Action_Arg arg2, Action_Arg arg3); //enough args?
        union {
            void (*en_Shoot)(Entity* entity, Action_Arg arg0, Action_Arg arg1, Action_Arg arg2, Action_Arg arg3);
            void (*pl_Shoot)(Entity* entity, Action_Arg arg0, Action_Arg arg1, Action_Arg arg2, Action_Arg arg3);
        } shoot;
        void (*explode)(Entity* entity, Action_Arg arg0, Action_Arg arg1, Action_Arg arg2, Action_Arg arg3);
    } Action;
    union {
        u16 u16;
        fix16 fix16;
        u8 u8;
        Entity* entityptr;
        void* voidptr;
    } Other;
};

#endif /* entity_h */
