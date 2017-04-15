#pragma once
#include "data_types.h"
/* La imagen con todos los muebles */
static GBitmap *forniture_bitmap;

/* Los rectangulos que definen cada mueble */
#define FORNITURE_MESA GRect(0,0,32,32)
#define FORNITURE_SILLA GRect(32,0,32,32)

/*
#define FORNITURE_COUNT 8
static GBitmap* tiles[TILE_COUNT];

  s_tiles_bitmap = gbitmap_create_with_resource(RESOURCE_ID_TILES_IMAGE);

  tiles[0] = gbitmap_create_as_sub_bitmap(s_tiles_bitmap, TILE_PIEDRA1);
  tiles[1] = gbitmap_create_as_sub_bitmap(s_tiles_bitmap, TILE_VACIO);
  tiles[2] = gbitmap_create_as_sub_bitmap(s_tiles_bitmap, TILE_PIEDRA2);
  tiles[3] = gbitmap_create_as_sub_bitmap(s_tiles_bitmap, TILE_LADRILLO);
  tiles[4] = gbitmap_create_as_sub_bitmap(s_tiles_bitmap, TILE_PARQUET);
  tiles[5] = gbitmap_create_as_sub_bitmap(s_tiles_bitmap, TILE_CHESS);
  tiles[6] = gbitmap_create_as_sub_bitmap(s_tiles_bitmap, TILE_CRUZ);
  tiles[7] = gbitmap_create_as_sub_bitmap(s_tiles_bitmap, TILE_ESPECIAL);
*/
struct Forniture{
  struct Posicion posicion;
  int rotation;
  
};