#ifndef SHOW_DESTINATIONS_H
#define SHOW_DESTINATIONS_H

char *read_file(const char *filename);
void check_availability(char* json_input);
void show_destinations_task(void *pvParameters);
void start_task_group1();

#endif