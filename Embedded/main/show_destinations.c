#include "show_destinations.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "cJSON.h"


// Funktion för att läsa en fil till en buffer
char *read_file(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Kunde inte öppna filen");
        return NULL;
    }

    fseek(file, 0, SEEK_END);
    long filesize = ftell(file);
    rewind(file);

    char *buffer = (char *)malloc(filesize + 1);
    if (!buffer) {
        perror("Kunde inte allokera minne");
        fclose(file);
        return NULL;
    }

    fread(buffer, 1, filesize, file);
    buffer[filesize] = '\0';

    fclose(file);
    return buffer;
}

void check_availability(char* json_input) {

    // TODO: Kolla vilka destinationer som är tillgängliga det datumet

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
