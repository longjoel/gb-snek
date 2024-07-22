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
/*
Global Variables
*/

u8 snekTileBuffer[BUFFER_SIZE]; // The tiles making up the level
u8 snekBodyBuffer[BUFFER_SIZE]; // The tiles making up the snek body
u8 finalBuffer[BUFFER_SIZE];    // The tiles that will be coppied to memory

u8 snekX; // position of the snek
u8 snekY;
u8 snekDir;   //  the direction the snek is facing
u8 snekScore; //  the score
u8 snekLives; //  the lives left
u8 snekLevel; //  what level we are on

/*
Seed the game
*/
void seed_game() {
  snekScore = 0;
  snekLives = 3;
  snekLevel = 0;
}

/*
Seed the level
*/
void seed_round() {

  snekDir = SNEK_DIR_RIGHT;
  snekX = 1;
  snekY = 1;

  for (u8 y = 0; y < BUFFER_HEIGHT; y++) {
    for (u8 x = 0; x < BUFFER_WIDTH; x++) {
      snekBodyBuffer[y * BUFFER_WIDTH + x] = 0;
      snekTileBuffer[y * BUFFER_WIDTH + x] = 0;
      if (x == 0 || y == 0 || x == BUFFER_WIDTH - 1 || y == BUFFER_HEIGHT - 1) {
        snekTileBuffer[y * BUFFER_WIDTH + x] = 40;
      }
    }
  }
}

void process_game() {
  while (snekLives > 0) {
    seed_round();
    process_round();
  }
}

void process_round() {
  // process the round input

  do {

    for (u8 inptCounter = 0; inptCounter <= 3; inptCounter++) {

      process_round_input();

      // update the buffer
      u16 snekHead = snekY * BUFFER_WIDTH + snekX;
      for (u16 i = 0; i < BUFFER_SIZE; i++) {
        finalBuffer[i] = snekTileBuffer[i];
        if (snekBodyBuffer[i] > 0) {
          finalBuffer[i] = TILE_DIAMOND[0];
        }
        if (snekHead == i ) {

          finalBuffer[i] = TILE_SNEK_HEAD[snekDir];
        }
      }

      set_tile_map(0, 0, BUFFER_WIDTH, BUFFER_HEIGHT, finalBuffer);
    }

    process_round_movement();

    for (u16 i = 0; i < BUFFER_SIZE; i++) {

      if (snekBodyBuffer[i] > 0) {
        snekBodyBuffer[i] = snekBodyBuffer[i] - 1;
      }
    }

    // delay(100);
    vsync();
  } while (process_round_collision());

  // if we left the loop that means we dead
  // lower the number of lives and fall out to process game
  snekLives--;
}

u8 process_round_collision() {
  // check collision with the level
  u16 playerLinearPos = snekY * BUFFER_WIDTH + snekX;

  if (snekTileBuffer[playerLinearPos]) {
    return 0;
  }
  if (snekBodyBuffer[playerLinearPos]) {
    return 0;
  }

  snekBodyBuffer[playerLinearPos] = snekLevel * 3 + 15;
  snekScore++;

  return 1;
}

void process_round_movement() {
  snekScore++;
  switch (snekDir) {
  case SNEK_DIR_UP:
    snekY--;
    break;
  case SNEK_DIR_DOWN:
    snekY++;
    break;
  case SNEK_DIR_LEFT:
    snekX--;
    break;
  case SNEK_DIR_RIGHT:
    snekX++;
    break;
  }
}

void process_round_input() {
  u8 input = joypad();

  if (input & J_LEFT) {
    snekDir = SNEK_DIR_LEFT;
  } else if (input & J_RIGHT) {
    snekDir = SNEK_DIR_RIGHT;
  } else if (input & J_UP) {
    snekDir = SNEK_DIR_UP;
  } else if (input & J_DOWN) {
    snekDir = SNEK_DIR_DOWN;
  }
}

void main() {

  DISPLAY_ON;
  SHOW_BKG;
  set_bkg_data(0, 41, (u8 *)snektiles);

  while (1) {
    seed_game();
    process_game();
  }
}