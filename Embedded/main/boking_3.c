#include "boking_3.h"
#include <freeRTOS./FreeRTOS.h>
#include <freertos/task.h>
#include <freeRTOS/event_groups.h>
#include <freeRTOS/queue.h>

QueueHandle_t xQueue;

void start_task_group3()
{
    printf("Starting task group 3\n");
    xTaskCreate(&task_group3, "Funktion", 2048, NULL, 5, NULL);
    printf("Task group 3 started\n");
}


void task_group3(void* params)
{
    // send message to mqtt
    //TODO FIX DATABASE
    while(true){
        for(int i = 0; i < 4; i++){
            send_data_to_mqtt(DB);
        }
        vTaskDelay(pdMS_TO_TICKS(5000));
    }   
}