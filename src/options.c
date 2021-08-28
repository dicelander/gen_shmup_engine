//
//  options.c
//  gen_shmupc
//
//  Created by Victor "dicelander" Sander on 27/08/21.
//

#include "../inc/options.h"
#include <options.h>

#ifndef POSITION_HISTORY_SIZE
#define POSITION_HISTORY_SIZE 40
#endif

#define OPTION_DISTANCE (POSITION_HISTORY_SIZE/MAX_OPTIONS)

void OPT_moveOptions(Opt_Options* options, Pos_History* history) {
    u8 ii = 0;
    for(ii = 0; ii < MAX_OPTIONS; ii++) {
        if ((history->current + mulu(ii+1, OPTION_DISTANCE)) < POSITION_HISTORY_SIZE) {
            options->option[ii].pos_x = history->pos_x[(history->current)+mulu(ii+1, OPTION_DISTANCE)];
            options->option[ii].pos_y = history->pos_y[(history->current)+mulu(ii+1, OPTION_DISTANCE)];
        } else {
            options->option[ii].pos_x = history->pos_x[(history->current)+mulu(ii+1, OPTION_DISTANCE)-POSITION_HISTORY_SIZE];
            options->option[ii].pos_y = history->pos_y[(history->current)+mulu(ii+1, OPTION_DISTANCE)-POSITION_HISTORY_SIZE];
        }
//        KLog_f3("option ", FIX16(ii), " position x: ", options->option[ii].pos_x, ", y: ", options->option[ii].pos_y);
//        KLog_U3("option ", ii, " position x: ", fix16ToInt(options->option[ii].pos_x), ", y: ", fix16ToInt(options->option[ii].pos_y));
        SPR_setPosition(options->option[ii].sprite, fix16ToInt(options->option[ii].pos_x), fix16ToInt(options->option[ii].pos_y));
    }
}

void OPT_addOption(Opt_Options* options, Pos_History* history) {
    u8 ii = 0;
    if (options->optionsonscreen < MAX_OPTIONS) {
        while (options->option[ii].status == ALIVE) {
            ii++;
        }
        options->option[ii].status = ALIVE;
        options->option[ii].sprite = SPR_addSprite(&explos, fix16ToInt(options->option[ii].pos_x), fix16ToInt(options->option[ii].pos_y), TILE_ATTR(PAL1,0,0,0));
        options->optionsonscreen++;
    }
}

Opt_Options* options_ptr;

void OPT_initOptions(Opt_Options* options) {
    u8 ii;
    for (ii = 0; ii < MAX_OPTIONS; ii++) {
        options->option[ii].pos_x = 0;
        options->option[ii].pos_y = 0;
        options->option[ii].offset_x = 0;
        options->option[ii].offset_y = 0;
        options->option[ii].sprite = NULL;
        options->option[ii].status = DEAD;
        options->option[ii].timer = 0;
    }
    options_ptr = options;
}

void OPT_setOptionsPtr(Opt_Options* options) {
    options_ptr = options;
}

Opt_Options* OPT_getOptionsPtr() {
    return options_ptr;
}
