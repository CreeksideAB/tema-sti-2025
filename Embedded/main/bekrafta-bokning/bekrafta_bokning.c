#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

void start_bekrafta_bokning_task(void* p)
{
    xTaskCreate(bekrafta_bokning_task, "bekrafta_bokning_task", 4000, p, 5, NULL);
}

// /bokning/uplink
// /bokning/downlink

void bekrafta_bokning_task(void *p)
{
    while (1)
    {
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}