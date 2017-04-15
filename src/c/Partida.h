#pragma once
#include "Tile.h"
#include "Hero.h"
#include "Monster.h"
#include "Camera.h"
  
enum StatusPartida {
  ACCION
};

/*
  Partida debe contener todo lo necesario para reconstruir una partida
  desde el punto en que se dejo.
*/
struct Partida{
  Window *window; /*Puntero a la ventana principal, para poder crear nuevos layers, etc. */
  uint16_t turn_count; /* Lleva la cuenta de los turnos */
  struct Hero heroes[sizeof(enum HeroesNames)]; /* El array de heroes, los ordenamos al iniciar partida segun toque */
  struct Hero *current_hero; /* Puntero al heroe jugando el turno actual, lo vamos avanzando por el array */
  struct Monster *monsters; /* Los monstruos de la partida, tantos como haya en la quest */
  struct Forniture *fornitures; /* Los muebles de adorno, tantos como haya en la quest */
  enum StatusPartida status;
};


void Partida_init(Window *main_window);

void Partida_deinit(void);

void Partida_turn_handle(void);