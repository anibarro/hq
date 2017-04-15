#pragma once
#include "data_types.h"
  
struct Armor{
  uint8_t dados_defensa;
  uint8_t dados_defensa_extra;
  enum HeroesNames prohibido_para[sizeof(enum HeroesNames)];
  enum WeaponsNames incompatible_con[sizeof(enum WeaponsNames)];
  enum Extra_effects efectos[sizeof(enum Extra_effects)];
};