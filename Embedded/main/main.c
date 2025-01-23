#include <stdio.h>
#include "wifi_handler.h"
#include "mqtt_handler.h"
#include "freertos/FreeRTOS.h"
#include "freertos/event_groups.h"

EventGroupHandle_t wifi_event_group;
EventGroupHandle_t mqtt_event_group;

void app_main(void)
{
<<<<<<< HEAD
       
=======
    wifi_event_group = xEventGroupCreate();
    mqtt_event_group = xEventGroupCreate();
    init_wifi(wifi_event_group);
    xEventGroupWaitBits(wifi_event_group, WIFI_CONNECTED_BIT, pdFALSE, pdTRUE, portMAX_DELAY);
    init_mqtt(mqtt_event_group);
    xEventGroupWaitBits(mqtt_event_group, MQTT_CONNECTED_BIT, pdFALSE, pdTRUE, portMAX_DELAY);

    // Kalla på "start_task_<namn>" här, 1 rad per grupp
    // EXAMPLE: start_task_group1();
>>>>>>> 26802b6ce6c836f106a0302c9164e2eea4a59f39
}