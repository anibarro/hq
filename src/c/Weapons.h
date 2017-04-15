#pragma once
#include "data_types.h"

struct Weapon{
  enum WeaponsNames nombre;
  uint8_t dados_ataque;
  uint8_t dados_ataque_extra;
  enum HeroesNames prohibido_para[sizeof(enum HeroesNames)];
  enum ArmorsNames incompatible_con[sizeof(enum ArmorsNames)];
  enum Extra_effects efectos[sizeof(enum Extra_effects)];
};