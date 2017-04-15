#pragma once

#include <pebble.h>
#include "data_types.h"

#define TILE_1 GRect(0,0,32,32)
#define TILE_2 GRect(32,0,32,32)
#define TILE_3 GRect(64,0,32,32)
#define TILE_4 GRect(96,0,32,32)
#define TILE_PARQUET GRect(128,0,32,32)
#define TILE_CHESS GRect(160,0,32,32)
#define TILE_CRUZ GRect(192,0,32,32)
#define TILE_ESPECIAL GRect(224,0,32,32)
  
void Board_init(void);
void Board_deinit(void);
void Board_add_layer(Window *window);
void Board_update_layer(void);



/*
  PRIVATE FUNCTIONS
*/

static void _update_board_layer(Layer *layer, GContext *ctx);
void _get_array_pos_to_draw(struct Point cam, uint32_t *out_array_pos, uint32_t *total_count, uint32_t *width_count);
void _get_tiles_offset(struct Point centro, struct Point topLeftSubTileCorner, struct Coord* out);
struct Point _get_board_point(struct Cell c);
struct Cell _get_board_cell(uint32_t pos);
uint32_t _get_array_pos(struct Point p);
uint32_t _get_array_pos_cell(struct Cell c);
struct Cell _get_board_pos(struct Point p);