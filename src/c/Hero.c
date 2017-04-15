#include <pebble.h>
#include "Hero.h"
#include "settings.h"


void Hero_init(struct Hero* hero){
  hero->posicion.casilla.x = 0;
  hero->posicion.casilla.y = 0;
  hero->posicion.punto.x = TILE_SIZE/2;
  hero->posicion.punto.y = TILE_SIZE/2;
}

struct Cell Hero_get_cell(struct Hero* hero){
  return hero->posicion.casilla;
}

struct Point Hero_get_coord(struct Hero* hero){
  return hero->posicion.punto;
}

void Hero_move(struct Hero* hero, enum Direction direccion){
  switch(direccion){
    case UP:
      if (hero->posicion.casilla.y > 0){
        hero->posicion.casilla.y--;
        hero->posicion.punto.y = (hero->posicion.casilla.y*TILE_SIZE)+TILE_SIZE_HALF;
      }
      break;
    case DOWN:
      if (hero->posicion.casilla.y < (BOARD_HEIGHT-1)){
        hero->posicion.casilla.y++;
        hero->posicion.punto.y = (hero->posicion.casilla.y*TILE_SIZE)+TILE_SIZE_HALF;
      }
      break;
    case LEFT:
      break;
    case RIGHT:
      break;
    default: break;
  }
}