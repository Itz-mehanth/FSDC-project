#ifndef SETTINGS
#define SETTINGS
#include <stdbool.h>

extern bool veg_mode;


typedef struct {
    char address[100];
    float distance;
} UserDeliveryInfo;

extern UserDeliveryInfo user_delivery_info;

int settings();

UserDeliveryInfo readUserDeliveryInfo();

#endif // !SETTINGS