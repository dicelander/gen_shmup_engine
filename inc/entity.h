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
    u16 nextpatternstate;
    u16 timer;
    u16 status;
    Sprite* sprite;
    Entity* parent;
    const struct Behaviour* pattern;
    enum {player, shot, enemy} Type;
    struct {
        void (*move)();
        void (*shoot)();
        void (*explode)();
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
