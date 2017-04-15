#pragma once
#include "data_types.h"
  
enum MonstersNames { ORC, GOBLIN, FIMIR, CHAOS_WARRIOR, CHAOS_WARLOCK, GARGOYLE, SKELETON, ZOMBIE, MUMMIE};

struct Monster{
  enum MonstersNames nombre;
  uint8_t dados_ataque;
  uint8_t dados_defensa;
  uint8_t movimientos;
  uint8_t puntos_salud;
  uint8_t puntos_mente;
  struct Posicion posicion;
  uint16_t turn_count; /* Lleva la cuenta de los turnos */
  enum StatusCharacter estado;
};