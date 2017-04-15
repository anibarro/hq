#include <pebble.h>
#include "Partida.h"

struct Partida partida;

struct Hero *ptr_barbaro;
struct Hero *ptr_enano;
struct Hero *ptr_mago;
struct Hero *ptr_elfo;

void Partida_init(Window *main_window){
  //uint16_t turn_count; /* Lleva la cuenta de los turnos */
  //struct Hero heroes[sizeof(enum HeroesNames)]; /* El array de heroes, los ordenamos al iniciar partida segun toque */
  //struct Hero *current_hero; /* Puntero al heroe jugando el turno actual, lo vamos avanzando por el array */
  //struct Monster monsters[sizeof(enum MonstersNames)]; /* Los monstruos de la partida */
  
  ptr_barbaro = &partida.heroes[0];
  ptr_enano = &partida.heroes[1];
  ptr_mago = &partida.heroes[2];
  ptr_elfo = &partida.heroes[3];
  Hero_init(ptr_barbaro);
  Hero_init(ptr_enano);
  Hero_init(ptr_mago);
  Hero_init(ptr_elfo);
  
  partida.window = main_window;
  partida.turn_count = 0;
    
  partida.current_hero = ptr_barbaro; // Apunto al primero
  
  //Inicializar la camara, la pondremos donde este el personaje que le ha tocado primero
  struct Point cam_ini_p = {302,183};
  Camera_set(cam_ini_p);
  
  Board_init();
  Board_add_layer(partida.window);
  
  
}

void Partida_deinit(void){
  Board_deinit();
}

//Aqui se maneja todo el proceso de un turno. Se crean nuevas windows con los dados, las peleas...
void Partida_turn_handle(void){
  /*Si turno de heroe:
     - Tirar dados movimiento
     Loop de acciones hasta que se quede sin movimientos:
      -Mover
      -Atacar (solo 1 vez por turno)
      -etc
  
  //Si turno de monstruo
  
  //Si
  */
}