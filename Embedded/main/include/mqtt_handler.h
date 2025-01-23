#ifndef MQTT_HANDLER_H
#define MQTT_HANDLER_H

#include "freertos/FreeRTOS.h"
#include "freertos/event_groups.h"

#define MQTT_CONNECTED_BIT BIT1

void init_mqtt();

#endif
