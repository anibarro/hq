#pragma once
 
#include <pebble.h> 
#define max(a,b) (a>b?a:b)
#define min(a,b) (a<b?a:b)

#define MURO_ARRIBA 1
#define MURO_DERECHA 2
#define MURO_ABAJO 4
#define MURO_IZQUIERDA 8
enum Direction { UP, DOWN, LEFT, RIGHT };

enum StatusCharacter {
  MOVIENDO,
  LANZANDO_HECHIZO,
  BUSCANDO_TESORO,
  BUSCANDO_TRAMPAS_PUERTAS, //turno de heroe
  TIRANDO_DADOS_MOVIMIENTO, //heroes y enemigos
  TIRANDO_DADOS_ATAQUE, //heroes y enemigos
  TIRANDO_DADOS_DEFENSA,
  ATACANDO,
  DEFENDIENDO
};

enum ActionsCharacter {
  MOVER,
  LANZAR_HECHIZO,
  BUSCAR_TESORO,
  BUSCAR_TRAMPAS,
  BUSCAR_PUERTAS, 
  ABRIR_COFRE,
  DESARMAR_TRAMPA
};

  struct TileCell{
  uint8_t tile_desc; /* Tipo de tile */
  
  uint8_t wall; /* Si tiene un muro y la posicion:
    bit 0: muro arriba  
    bit 1: muro derecha 
    bit 2: muro abajo 
    bit 3: muro izquierda 
  */
  uint8_t info; /*Informacion variada:
    bit 0: indica si el tile es visible para el jugador: 0=no, 1=si. Se actualiza en cada movimiento.
  */
};

struct Coord{
  int32_t x;
  int32_t y;
};

struct Point{
  uint32_t x;
  uint32_t y;
};

struct Cell{
  uint32_t x;
  uint32_t y;
};

struct Camera{
  struct Point p; /* Punto del tile map en pixels en el que centro la camara */
  uint32_t speed; /* Pixels por frame */
};

/* Posicion en pixels y casillas del tablero */
struct Posicion{
  struct Point punto;
  struct Cell casilla;
};

/* Algunos enums genericos compartidos */
enum HeroesNames { BARBARIAN, DWARF, ELF, WIZARD };
enum ArmorsNames { CHAIN_MAIL, HELMET, PLATE_MAIL, SHIELD };
enum Extra_effects { THROWABLE, DIAGONAL_ATTACK, RANGE_ATTACK, REDUCED_MOVEMENT};
enum WeaponsNames { BATTLE_AXE, DAGGER, LONGSWORD, BROADSWORD, CROSSBOW, STAFF, SHORTSWORD };