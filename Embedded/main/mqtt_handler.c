#include "mqtt_handler.h"
#include "mqtt_client.h"
#include "esp_log.h"
#include "cJSON.h"
#include "show_destinations.h"

#define TAG "mqtt_handler"
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
    case MQTT_EVENT_CONNECTED:
        ESP_LOGI(TAG, "MQTT connected");
        xEventGroupSetBits(mqtt_event_group, MQTT_CONNECTED_BIT);

        esp_mqtt_client_subscribe(client, "/travel/uplink", 0);

        break;
    case MQTT_EVENT_DISCONNECTED:
        ESP_LOGI(TAG, "MQTT disconnected");
        xEventGroupClearBits(mqtt_event_group, MQTT_CONNECTED_BIT);
        if (reconnect_counter < 30)
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
        ESP_LOGI(TAG, "TOPIC=%.*s\r\n", event->topic_len, event->topic);
        ESP_LOGI(TAG, "DATA=%.*s\r\n", event->data_len, event->data);

        if (strcmp(event->topic, "/travel/uplink") == 0)
        {
            ESP_LOGI(TAG, "Received data on /travel/uplink");
            ESP_LOGI(TAG, "Processing travel data");

            char* data = strndup(event->data, event->data_len);
            cJSON *json = cJSON_Parse(data);
            free(data);

            if (json) {
                cJSON *date_item = cJSON_GetObjectItem(json, "date");
                cJSON *duration_item = cJSON_GetObjectItem(json, "duration");

                if (cJSON_IsString(date_item) && cJSON_IsNumber(duration_item)) {
                    ESP_LOGI(TAG, "Date: %s", date_item->valuestring);
                    ESP_LOGI(TAG, "Duration: %d", duration_item->valueint);

                    cJSON* response = cJSON_CreateObject();
                    cJSON_AddStringToObject(response, "date", date_item->valuestring);
                    cJSON_AddNumberToObject(response, "duration", duration_item->valueint);
                    char* response_str = cJSON_Print(response);

                    check_availability(response_str);

                    free (response_str);
                    cJSON_Delete(response);
                } else {
                    ESP_LOGE(TAG, "Invalid JSON format");
                }
            }
            break;
        }
        break;
    default:
        break;
    }
}

void init_mqtt(EventGroupHandle_t mqtt_event_group)
{
    ESP_LOGI(TAG, "Initializing MQTT");

    esp_mqtt_client_config_t mqtt_cfg = {
        .broker.address.uri = BROKER_URL,
    };

    client = esp_mqtt_client_init(&mqtt_cfg);
    ESP_ERROR_CHECK(esp_mqtt_client_register_event(client, MQTT_EVENT_ANY, mqtt_event_handler, (void*)mqtt_event_group));
    ESP_ERROR_CHECK(esp_mqtt_client_start(client));
}