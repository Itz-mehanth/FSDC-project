#include <stdio.h>
#include <time.h>
#include "login.h"
#include "notification.h"
#include "theme.h"
#include <string.h>

int add_notification(char *notification)
{
    printf("adding notification\n");
    char name[100];
    time_t now;
    struct tm *tm_info;
    char timestamp[26];

    // Prompt user for name
    if(readCurrentUser()==1){
        strcpy(name, current_user_details.username);
    }else{
        strcpy(name, "unknown");
    }
    // Get current time
    time(&now);
    tm_info = localtime(&now);

    // Format time as string
    strftime(timestamp, sizeof(timestamp), "%Y-%m-%d %H:%M:%S", tm_info);

    printf("calculating time\n");
    // Open file for appending
    FILE *file = fopen("notification.txt", "a");
    if (file == NULL) {
        printf("Error opening file for writing.\n");
        return 0;
    }

    // Write data to file
    fprintf(file, "Name: %s notification: ", name);
    fputs(notification, file);
    fprintf(file, "~Timestamp: %s\n",timestamp);
    fclose(file);
}

int view_notifications(){
    char notification[1024],name[20],time[20];
    FILE *fp = fopen("notification.txt","r");
    if(fp == NULL){
        print_error("Error opening notification.txt");
    }
    while(fscanf(fp,"Name: %s notification: %[^~]~Timestamp: %s\n",name,notification,time)==3){
        if(strcmp(name,current_user_details.username)==0){
            printf("| To:%s\t\t\tTIME: %s \n",name,time);
            printf("| %s \n",notification);
            printf("  ----------------------------------------------\n");
        }

    }
    return 1;
    
}
