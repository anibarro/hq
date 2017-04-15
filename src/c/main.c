/*
 * main.c
 * Sets up the Window, ClickConfigProvider and ClickHandlers.
 */
#include <inttypes.h>
#include <pebble.h>
#include "Tile.h"
#include "Camera.h"
#include "settings.h"
#include "Partida.h"
#include "helpers.h"
  
bool moving_up = false;
bool moving_down = false;

static Window *s_main_window;
static TextLayer *s_output_layer;

struct Partida partida; /* Solo necesitamos una partida */


/*
  Handlers
*/
static void data_handler(AccelData *data, uint32_t num_samples) {
  struct Point current_cam;
  Camera_get(&current_cam);
  current_cam.x += data[0].x/40;
  current_cam.y -= data[0].y/40;
  Camera_set(current_cam);
  
  Board_update_layer();
}

static void up_click_handler(ClickRecognizerRef recognizer, void *context) {
  /*text_layer_set_text(s_output_layer, "Up pressed!");*/
  /*move_hero(&s_barbarian, UP);
  struct Point barb_pos = get_hero_coord(&s_barbarian);
  set_cam(barb_pos);
  */
  struct Point current_cam;
  Camera_get(&current_cam);
  current_cam.x -= 2;
  current_cam.y -= 2;
  Camera_set(current_cam);
  
  Board_update_layer();
}

static void select_click_handler(ClickRecognizerRef recognizer, void *context) {
  /*text_layer_set_text(s_output_layer, "Select pressed!");*/

  struct Point destiny_point;
  destiny_point.x = (BOARD_WIDTH/2*TILE_SIZE)+TILE_SIZE_HALF;
  destiny_point.y = (BOARD_HEIGHT/2*TILE_SIZE)+TILE_SIZE_HALF;
  //set_cam(current_cam);

  Camera_goto(context, destiny_point);
}

static void down_click_handler(ClickRecognizerRef recognizer, void *context) {
  /*text_layer_set_text(s_output_layer, "Down pressed!");*/
  /*
  move_hero(&s_barbarian, DOWN);
  struct Point barb_pos = get_hero_coord(&s_barbarian);
  set_cam(barb_pos);
  */
  
  /*struct Point current_cam;
  get_cam(&current_cam);
  current_cam.x += 2;
  current_cam.y += 2;
  set_cam(current_cam);*/
  
  Board_update_layer();
}

/*
  END Handlers
*/

static void click_config_provider(void *context) {
  // Register the ClickHandlers
  window_single_click_subscribe(BUTTON_ID_UP, up_click_handler);
  //window_single_repeating_click_subscribe(BUTTON_ID_UP, 34, up_click_handler);
  
  window_single_click_subscribe(BUTTON_ID_SELECT, select_click_handler);
  //window_single_repeating_click_subscribe(BUTTON_ID_SELECT, 34, select_click_handler);
  
  window_single_click_subscribe(BUTTON_ID_DOWN, down_click_handler);
  //window_single_repeating_click_subscribe(BUTTON_ID_DOWN, 34, down_click_handler);
}

static void main_window_load(Window *window) {
  Layer *window_layer = window_get_root_layer(window);
  GRect window_bounds = layer_get_bounds(window_layer);

  // Create output TextLayer
  /*
  s_output_layer = text_layer_create(GRect(5, 0, window_bounds.size.w - 5, window_bounds.size.h));
  text_layer_set_font(s_output_layer, fonts_get_system_font(FONT_KEY_GOTHIC_14));
  text_layer_set_text(s_output_layer, "No button pressed yet.");
  text_layer_set_overflow_mode(s_output_layer, GTextOverflowModeWordWrap);
  
  layer_add_child(window_layer, text_layer_get_layer(s_output_layer));
  */
  
    Partida_init(window); //Iniciar partida
}

static void main_window_unload(Window *window) {
  // Destroy output TextLayer
  /*text_layer_destroy(s_output_layer);*/
}


/*
static void timer_handler(void *context)
{
   Board_update_layer();
   app_timer_register(34, timer_handler, NULL);
}
*/

static void init() {
  
  // Create main Window
  s_main_window = window_create();
  window_set_window_handlers(s_main_window, (WindowHandlers) {
    .load = main_window_load,
    .unload = main_window_unload
  });
  
  //init_hero(&s_barbarian);

  window_set_click_config_provider(s_main_window, click_config_provider);
  window_stack_push(s_main_window, true);
 
  GRect window_bounds = layer_get_bounds(window_get_root_layer(s_main_window));
  CAMERA_WIDTH = window_bounds.size.w;
  CAMERA_HEIGHT = window_bounds.size.h;
  CAMERA_WIDTH_HALF = window_bounds.size.w / 2;
  CAMERA_HEIGHT_HALF = window_bounds.size.h / 2;
  
  //APP_LOG(APP_LOG_LEVEL_DEBUG, "bounds: %"PRIu32",%"PRIu32"", CAMERA_WIDTH, CAMERA_HEIGHT);
  
  /*
  int num_samples = 1;
  accel_data_service_subscribe(num_samples, data_handler);
  // Choose update rate
  //accel_service_set_sampling_rate(ACCEL_SAMPLING_25HZ);
  accel_service_set_sampling_rate(ACCEL_SAMPLING_10HZ);
  */
  
  //app_timer_register(34, timer_handler, NULL);
}

static void deinit() {
  Partida_deinit();
  // Destroy main Window
  window_destroy(s_main_window);
}

int main(void) {
  init();
  app_event_loop();
  deinit();
}