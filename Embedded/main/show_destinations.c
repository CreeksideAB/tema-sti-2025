#include "show_destinations.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "cJSON.h"

void check_availability(char* json_input) {
    
}

void show_destinations_task(void *pvParameters) {

    

    while (1) {
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
    vTaskDelete(NULL);
}

void start_task_group1() {
    xTaskCreate(show_destinations_task, "show_destinations_task", 4096, NULL, 5, NULL);
}
