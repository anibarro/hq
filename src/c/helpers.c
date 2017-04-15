#include <pebble.h>
#include "helpers.h"

/* Animar p hasta destino a velocidad v */
void animPoint(struct Point *p, struct Point destino, uint32_t speed){
  int32_t len_x = p->x - destino.x;
  int32_t len_y = p->y - destino.y;
  //Si ya no puedo ir mas cerca, salgo
  if ((abs(len_x)<speed) && (abs(len_y)<speed)){
    p->x = destino.x;
    p->y = destino.y;
    return;
  }
  
  if ( abs(len_x) > abs(len_y) ){
    p->x += (len_x<0)?speed:-speed;
  }else{
    p->y += (len_y<0)?speed:-speed;
  }
}