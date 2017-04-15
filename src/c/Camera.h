#pragma once

#include "data_types.h"
  
void Camera_set(struct Point p);
void Camera_get(struct Point* p);

void Camera_goto(void *context, struct Point destino);