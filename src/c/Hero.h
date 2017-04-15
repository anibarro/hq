#pragma once
#include "data_types.h"
#include "Weapons.h"
#include "Armors.h"
  
#define MAX_WEAPONS 10
#define MAX_ARMORS 10



/* TODO: aniadir el sprite tambien */
struct Hero{
  enum HeroesNames nombre;
  uint8_t dados_ataque;
  uint8_t dados_defensa;
  uint8_t dados_movimiento;
  uint8_t puntos_salud;
  uint8_t puntos_mente;
  struct Armor armaduras[MAX_WEAPONS];
  struct Armor armadura_actual;
  struct Weapon armas[MAX_ARMORS];
  struct Weapon arma_actual;
  struct Posicion posicion;
  uint16_t turn_count; /* Lleva la cuenta de los turnos */
  enum StatusCharacter estado;
};

/* FUNCTIONS */
void Hero_init(struct Hero* hero);
struct Cell Hero_get_cell(struct Hero* hero);
struct Point Hero_get_coord(struct Hero* hero);
void Hero_move(struct Hero* hero, enum Direction direccion);
