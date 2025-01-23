#include "boking_3.h"
#include <freeRTOS./FreeRTOS.h>
#include <freertos/task.h>
#include <freeRTOS/event_groups.h>

void start_task_group3()
{
    printf("Starting task group 3\n");
    xTaskCreate(&task_group3, "Funktion", 2048, NULL, 5, NULL);
    
}


void task_group3(void* params)
{
    
}