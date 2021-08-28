//
//  options.h
//  gen_shmupc
//
//  Created by Victor "dicelander" Sander on 27/08/21.
//

#ifndef options_h
#define options_h

#include <genesis.h>
#include "player.h"

#ifndef MAX_OPTIONS
#define MAX_OPTIONS 4
#endif

typedef struct Opt_Option {
    fix16 pos_x;
    fix16 pos_y;
    fix16 offset_x;
    fix16 offset_y;
    u8 timer;
    u8 status;
    Sprite* sprite;
} Opt_Option;

typedef struct Opt_Options {
    Opt_Option option[MAX_OPTIONS];
    u8 optionsonscreen;
} Opt_Options;

void OPT_initOptions(Opt_Options* options);

void OPT_addOption(Opt_Options* options, Pos_History* history);

void OPT_moveOptions(Opt_Options* options, Pos_History* history);

void OPT_setOptionsPtr(Opt_Options* options);

Opt_Options* OPT_getOptionsPtr();

#endif /* options_h */
