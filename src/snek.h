#ifndef __SNEK__H__
#define __SNEK__H__ 1

#define __PORT_z80 1


#include "snektiles.h"
#include <gb/gb.h>
#include <stdint.h>

typedef unsigned char u8;
typedef unsigned short u16;

#define BUFFER_WIDTH 20
#define BUFFER_HEIGHT 18
#define BUFFER_SIZE (BUFFER_HEIGHT * BUFFER_WIDTH)

#define SNEK_DIR_UP 0
#define SNEK_DIR_DOWN 1
#define SNEK_DIR_LEFT 2
#define SNEK_DIR_RIGHT 3

const u8 TILE_SNEK[] = {0x01, 0x02};
const u8 TILE_SCORE[] = {0x03, 0x04, 0x05};
const u8 TILE_HEART[] = {0x06};
const u8 TILE_DIAMOND[] = {0x07};

const u8 TILE_SCORENUMS[] = {0x08, 0x09, 0x0A, 0x0B, 0x0C,
                             0x0D, 0x0E, 0x0F, 0x10, 0x11};

const u8 TILE_SNEK_HEAD[] = {0x12, 0x13, 0x14, 0x15};
const u8 TILE_SNEK_LR[] = {0x16};
const u8 TILE_SNEK_UD[] = {0x17};
const u8 TILE_SNEK_TAIL[] = {0x18, 0x19, 0x1A, 0x1B};

void seed_game();
void seed_round();
void process_game();
void process_round();
void process_round_input();
void process_round_movement();
u8 process_round_collision();

void do_titlescreen();

#endif