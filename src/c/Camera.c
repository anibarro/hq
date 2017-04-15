#include <pebble.h>
#include <inttypes.h>
#include "Camera.h"
#include "settings.h"
#include "data_types.h"
#include "helpers.h"

static struct Camera _cam; /*La camara que define el punto central del scroll en pixels relativos a todo el tablero*/
static struct Point _destino; /*La camara que define el punto central del scroll en pixels relativos a todo el tablero*/

void Camera_set(struct Point p){
  if ((p.x > CAMERA_WIDTH_HALF) && (p.x < (BOARD_WIDTH_PX-CAMERA_WIDTH_HALF))){
    _cam.p.x = p.x;
  }else if (p.x <= CAMERA_WIDTH_HALF){
    _cam.p.x = CAMERA_WIDTH_HALF;
  }else if (p.x >= (BOARD_WIDTH_PX-CAMERA_WIDTH_HALF)){
    _cam.p.x = BOARD_WIDTH_PX-CAMERA_WIDTH_HALF;
  }
  
  if ((p.y > CAMERA_HEIGHT_HALF) && (p.y < (BOARD_HEIGHT_PX-CAMERA_HEIGHT_HALF))){
    _cam.p.y = p.y;
  }else if (p.y <= CAMERA_HEIGHT_HALF){
    _cam.p.y = CAMERA_HEIGHT_HALF;
  }else if (p.y >= (BOARD_HEIGHT_PX-CAMERA_HEIGHT_HALF)){
    _cam.p.y = BOARD_HEIGHT_PX-CAMERA_HEIGHT_HALF;
  }
}

void Camera_get(struct Point* p){
  p->x = _cam.p.x;
  p->y = _cam.p.y;
}

void _camera_goto(void * data){
  _destino.x = ((struct Point*)data)->x;
  _destino.y = ((struct Point*)data)->y;
  struct Point current_cam;
  Camera_get(&current_cam);
  animPoint(&current_cam, _destino, 2);
  APP_LOG(APP_LOG_LEVEL_DEBUG, "cam: %"PRIu32",%"PRIu32"", current_cam.x, current_cam.y);
  APP_LOG(APP_LOG_LEVEL_DEBUG, "destino: %"PRIu32",%"PRIu32"", _destino.x, _destino.y);
  Camera_set(current_cam);
  Board_update_layer();
  
  if ((current_cam.x != _destino.x) && (current_cam.y != _destino.y)){
      app_timer_register(34, (AppTimerCallback)_camera_goto, &_destino);
  }
}

void Camera_goto(void *context, struct Point destino){
  _camera_goto(&destino);
}