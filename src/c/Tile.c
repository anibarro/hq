#include <pebble.h>
#include <inttypes.h>
#include "Tile.h"
#include "settings.h"
#include "data_types.h"
#include "Camera.h"
#include "BOARD.h"

static GBitmap *s_tiles_bitmap;
static BitmapLayer *s_board_layer;

#define TILE_COUNT 12
static GBitmap* tiles[TILE_COUNT];

/* Inicializar el tablero con su layer */
void Board_init(void){
  s_tiles_bitmap = gbitmap_create_with_resource(RESOURCE_ID_TILES_IMAGE);
  /* Cuando se crean sub_bitmaps, son referencias al bitmap inicial, por lo que hay
  que mantener el bitmap original en memoria y al final eliminar primero los sub_bitmaps
  y luego el bitmap original */
  for (int i=0;i<TILE_COUNT;i++){
    tiles[i] = gbitmap_create_as_sub_bitmap(s_tiles_bitmap, GRect(i*32,0,32,32));
  }
  
  GRect window_bounds = GRect(0,0,CAMERA_WIDTH,CAMERA_HEIGHT);
  /* Creo el layer del mapa con el tamanio de la camara */
  s_board_layer = bitmap_layer_create(window_bounds);

  /*bitmap_layer_set_bitmap(s_board_layer, s_tiles_bitmap);*/
}
/* Llamar para destruir el layer */
void Board_deinit(void){
  for (uint32_t i=0; i<TILE_COUNT; i++) gbitmap_destroy(tiles[i]);
  gbitmap_destroy(s_tiles_bitmap);
  bitmap_layer_destroy(s_board_layer);
}

/* Marcar como dirty para actualizar despues de algun cambio en la camara */
void Board_update_layer(void){
  layer_mark_dirty(bitmap_layer_get_layer(s_board_layer));
}

void Board_add_layer(Window *window){ 
  layer_set_update_proc(bitmap_layer_get_layer(s_board_layer), _update_board_layer);
  //Aniadir el layer del board al root layer
  layer_add_child(window_get_root_layer(window), bitmap_layer_get_layer(s_board_layer));
  Board_update_layer();
}

/*
  PRIVATE FUNCTIONS
*/

/* Rutina para actualizar el tablero cuando se mueve la camara o similar */
static void _update_board_layer(Layer *layer, GContext *ctx)
{ 
  /* Modo de agregar graficos al layer */
  graphics_context_set_compositing_mode(ctx, GCompOpAssign);
  
  struct Point cam_point;
  Camera_get(&cam_point);
  
  //APP_LOG(APP_LOG_LEVEL_DEBUG, "Campoint: %d,%d", 1,2);
    
  uint32_t array_pos[50];
  uint32_t total_count = 0;
  uint32_t width_count = 0;
  /* Llenar el array_pos con posiciones del board a pintar */
  _get_array_pos_to_draw(cam_point, array_pos, &total_count, &width_count);
  
  struct Point top_left_sub_tile_corner = _get_board_point(_get_board_cell(array_pos[0]));
  struct Coord offset;
  /* Sacar el offset del rectangulo de tiles que pintaremos para que el centro
  se corresponda con el centro de la camara */
  _get_tiles_offset(cam_point, top_left_sub_tile_corner, &offset);
  
  /* Especificar nuevas dimensiones del layer */
  layer_set_frame(layer, GRect(0,0, CAMERA_WIDTH, CAMERA_HEIGHT)); /*GRect(10, 10, 20, 20) para un cuadrado de 20x20 empezando en 10,10*/
  uint32_t bound_width = width_count*TILE_SIZE;
  uint32_t bound_height = (total_count/width_count)*TILE_SIZE;
  layer_set_bounds(layer, GRect(offset.x,offset.y, bound_width, bound_height)); /* Bounds seran negativas y se extienden al tamanio del tile*/

  /* Recorrer y pintar los tiles. Seria mas rapido hacerlo en el mismo bucle que
  saca el array de posiciones a buscar, pero asi es mas claro y va rapido tambien. De momento lo dejo. */
  for (uint32_t i=0; i<total_count; i++){
    uint32_t pos = array_pos[i];
    /* coordenadas para pintar cada tile: */
    struct Point p_topleft = _get_board_point(_get_board_cell(pos));
    uint32_t coord_x = p_topleft.x;/*+offset.x;*/
    uint32_t coord_y = p_topleft.y;/*+offset.y;*/

    /* Vamos agregando todos los tiles que se van a ver en la pantalla con sus posiciones correctas dentro del layer */
    graphics_draw_bitmap_in_rect(ctx, tiles[Board[pos].tile_desc], GRect(coord_x , coord_y, TILE_SIZE, TILE_SIZE));
    
    /*Pintamos los muros si hace falta:*/
    uint32_t wall_val = Board[pos].wall;
    uint32_t ancho_muro = 3;
    if ((wall_val & ((uint32_t)MURO_ARRIBA)) == ((uint32_t)MURO_ARRIBA)) graphics_fill_rect(ctx, GRect(coord_x, coord_y, TILE_SIZE, ancho_muro), 0, GCornerNone);
    if ((wall_val & ((uint32_t)MURO_ABAJO)) == ((uint32_t)MURO_ABAJO)) graphics_fill_rect(ctx, GRect(coord_x, coord_y+TILE_SIZE-ancho_muro, TILE_SIZE, ancho_muro), 0, GCornerNone);
    if ((wall_val & ((uint32_t)MURO_DERECHA)) == ((uint32_t)MURO_DERECHA)) graphics_fill_rect(ctx, GRect(coord_x+TILE_SIZE-ancho_muro, coord_y, ancho_muro, TILE_SIZE), 0, GCornerNone);
    if ((wall_val & ((uint32_t)MURO_IZQUIERDA)) == ((uint32_t)MURO_IZQUIERDA)) graphics_fill_rect(ctx, GRect(coord_x, coord_y, ancho_muro, TILE_SIZE), 0, GCornerNone);
  }
}

/* Devolver posiciones del array que tenemos que pintar de izquierda a derecha. */
/* Devolver tambien el numero de celdas en horizontal para saber cuando saltar de fila */
void _get_array_pos_to_draw(struct Point cam, uint32_t *out_array_pos, uint32_t *total_count, uint32_t *width_count){
  struct Point from;
  from.x = cam.x - CAMERA_WIDTH_HALF;
  from.y = cam.y - CAMERA_HEIGHT_HALF;
  struct Point to;
  to.x = cam.x + CAMERA_WIDTH_HALF;
  to.y = cam.y + CAMERA_HEIGHT_HALF;
  
  struct Cell fromCell;
  fromCell = _get_board_pos(from);
  struct Cell toCell;
  toCell = _get_board_pos(to);
   
  *width_count = toCell.x-fromCell.x+1;
  *total_count = *width_count * (toCell.y-fromCell.y+1);
  uint32_t count = 0;
  for (uint32_t j=fromCell.y; j<=toCell.y; j++){
    for (uint32_t i=fromCell.x; i<=toCell.x; i++){
      struct Cell thecell;
      thecell.x = i;
      thecell.y = j;
      out_array_pos[count] = _get_array_pos_cell(thecell);
      count++;
    }
  }
}

/* Devolver el numero de pixels (x,y) que hay que desplazar el layer del tablero */
/* en el que tenemos los tiles que nos hacen falta (no todos los tiles, solo los que se ven) */
/* para centrarlo en un punto dado */
void _get_tiles_offset(struct Point centro, struct Point topLeftSubTileCorner, struct Coord* out){
  struct Point windowTopLeft;
  windowTopLeft.x = centro.x-CAMERA_WIDTH_HALF;
  windowTopLeft.y = centro.y-CAMERA_HEIGHT_HALF;
  /*APP_LOG(APP_LOG_LEVEL_DEBUG, "center topleft: (%d, %d)", windowTopLeft.x, windowTopLeft.y);*/
  out->x = (topLeftSubTileCorner.x - windowTopLeft.x)-topLeftSubTileCorner.x;
  out->y = (topLeftSubTileCorner.y - windowTopLeft.y)-topLeftSubTileCorner.y;
}

/*
  FUNCIONES DE CONVERSION PUNTO-CELDA-POSICION ARRAY
*/

/* Devolver esquina top-left en pixels para una posicion en el array */
struct Point _get_board_point(struct Cell c){
  struct Point p;
  p.x = c.x * TILE_SIZE;
  p.y = c.y * TILE_SIZE;
  return p;
}

/* Devolver Cell para una posicion en el array */
struct Cell _get_board_cell(uint32_t pos){
  struct Cell c;
  c.x = pos % BOARD_WIDTH;
  c.y = pos / BOARD_WIDTH;
  return c;
}

/* Devolver posicion en el array para esas coordenadas en pixels */
uint32_t _get_array_pos(struct Point p){
  struct Cell c = _get_board_pos(p);
  uint32_t res = (c.y * BOARD_WIDTH) + c.x;
  return res;
}

/* Devolver posicion en el array para esa celda */
uint32_t _get_array_pos_cell(struct Cell c){
  return (c.y*BOARD_WIDTH) + c.x;
}

/* Devolver posicion en celdas del mapa para esas coordenadas en pixels */
struct Cell _get_board_pos(struct Point p){
  struct Cell c;
  c.x = p.x / TILE_SIZE;
  //c.x = min(c.x,BOARD_WIDTH-1);
  c.y = p.y / TILE_SIZE;
  //c.y = min(c.y,BOARD_HEIGHT-1);
  return c;
}
