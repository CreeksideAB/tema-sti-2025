#ifndef WIFI_HANDLER_H
#define WIFI_HANDLER_H

#include "freertos/FreeRTOS.h"
#include "freertos/event_groups.h"

#define WIFI_CONNECTED_BIT BIT0

void init_wifi();

#endif