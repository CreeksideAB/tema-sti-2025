#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "mqtt_handler.h"
#include "mqtt_client.h"
#include "esp_log.h"

#define TAG "Bekrafta_Bokning"
#define BROKER_URL "mqtt://broker.emqx.io:1883"

static int reconnect_counter = 0;

esp_mqtt_client_handle_t client;

static void mqtt_event_handler(void *handler_args, esp_event_base_t base, int32_t event_id, void *event_data)
{
    EventGroupHandle_t mqtt_event_group = (EventGroupHandle_t)handler_args;
    esp_mqtt_event_handle_t event = (esp_mqtt_event_handle_t)event_data;
    esp_mqtt_client_handle_t client = event->client;
    switch (event_id)
    {

// /bokning/uplink
// /bokning/downlink
    case MQTT_EVENT_CONNECTED:
        ESP_LOGI(TAG, "MQTT connected");
        xEventGroupSetBits(mqtt_event_group, MQTT_CONNECTED_BIT);

        /*
            TODO: SUBSCRIBE TO TOPICS HERE
        */

        break;
    case MQTT_EVENT_DISCONNECTED:
        ESP_LOGI(TAG, "MQTT disconnected");
        xEventGroupClearBits(mqtt_event_group, MQTT_CONNECTED_BIT);
        if (reconnect_counter < 5)
        {
            reconnect_counter++;
            ESP_LOGI(TAG, "Trying to reconnect to MQTT");
            esp_mqtt_client_reconnect(client);
        }
        else
        {
            ESP_LOGI(TAG, "Max reconnect attempts reached");
        }
        break;
    case MQTT_EVENT_SUBSCRIBED:
        ESP_LOGI(TAG, "MQTT subscribed");
        
        break;
    case MQTT_EVENT_DATA:
        ESP_LOGI(TAG, "MQTT data received");
        break;
    default:
        break;
    }
}

void bekrafta_bokning_task(void *p);
void start_bekrafta_bokning_task(void* p)
{
    xTaskCreate(bekrafta_bokning_task, "bekrafta_bokning_task", 4000, p, 5, NULL);
}

// /bokning/uplink
// /bokning/downlink

void bekrafta_bokning_task(void *p)
{
    ESP_LOGI(TAG, "Initializing MQTT");

    esp_mqtt_client_config_t mqtt_cfg = {
        .broker.address.uri = BROKER_URL,
    };

    client = esp_mqtt_client_init(&mqtt_cfg);
    ESP_ERROR_CHECK(esp_mqtt_client_register_event(client, MQTT_EVENT_ANY, mqtt_event_handler, NULL));
    ESP_ERROR_CHECK(esp_mqtt_client_start(client));
    while (1)
    {
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}