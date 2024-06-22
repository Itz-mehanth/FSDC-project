#define _XOPEN_SOURCE 700  // Needed for strptime

#include <stdio.h>
#include <time.h>
#include <windows.h>
#include <conio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "CommunityChat.h"
#include "theme.h"
#include "food_order_page.h"
#include "login.h"
#include "illustrations.h"
#include "sounds.h"

// Function to read messages from a CSV file
int readMessages(Message messages[], const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening file for reading");
        return 0;
    }

    int count = 0;
    while (fscanf(file, "%[^,],%[^,],%[^\n]\n",messages[count].username, messages[count].message,
                   messages[count].timestamp) == 3) {
        count++;
        if (count >= 100) {
            printf("Warning: Maximum number of records reached (%d)\n", 100);
            break;
        }
    }

    fclose(file);
    return count;
}

// Function to write messages to a CSV file
void writeMessages(Message message, const char *filename) {
    FILE *file = fopen(filename, "a");
    if (file == NULL) {
        perror("Error opening file for writing");
        return;
    }
    FILE *fp = fopen("usersChats.txt", "a");
    if (fp == NULL) {
        perror("Error opening file for writing");
        return;
    }

    // Get current time and format it
    time_t currentTime = time(NULL);
    struct tm *tm_info = localtime(&currentTime);
    strftime(message.timestamp, sizeof(message.timestamp), "%Y-%m-%d %H:%M:%S", tm_info);

    fprintf(file, "%s,%s,%s\n", message.username, message.message, message.timestamp);
    fprintf(fp, "%s,%s,%s\n", message.username, message.message, message.timestamp);

    fclose(file);
    fclose(fp);
    // printf("Message written to %s successfully.\n", filename);
}

void chatPageDiv() {
    int x = 40, y = 17;
    for (int i = 0; i < DIV_HEIGHT; i++) {
        setCursor_inc(x, y++);
        set_text_color(WHITE, LIGHT_GRAY);
        printf("%*s", 150, " ");
    }
    setCursor_inc(x, y++);
    set_text_color(WHITE, DARK_BLUE);
    printf("%*s", 150, " ");
    setCursor_inc(x, y++);
    printf("%*s", 150, " ");
    setCursor_inc(x, y++);
    printf("%*s", 150, " ");
    setCursor_inc(x, y++);
}

void chatTopBar(char username[]) {
    int x = 40, y = 14;
    setCursor_inc(x, y++);
    set_text_color(WHITE, ORANGE);
    printf("  %-*s", 148, " ");
    setCursor_inc(x, y++);
    printf("  %-*s", 148, username);
    setCursor_inc(x, y++);
    printf("  %-*s", 148, " ");
}

int calculateNumLines(char *message, int maxLineLength) {
    int messageLength = strlen(message);
    return (messageLength / maxLineLength) + 1;
}

int getTotalChatBoxHeight(char *message, int maxLineLength) {
    int numLines = calculateNumLines(message, maxLineLength);
    return numLines + CHATBOX_PADDING;
}

int canAddChatBox(int currentHeight, char *message, int maxLineLength) {
    int newHeight = getTotalChatBoxHeight(message, maxLineLength);
    return (currentHeight + newHeight) <= DIV_HEIGHT;
}

// void calculateElapsedTime(const char *timestamp, char *elapsedTime) {
//     struct tm tm = {0};
//     time_t messageTime, currentTime;
//     double diff;

//     strptime(timestamp, "%Y-%m-%d %H:%M:%S", &tm);
//     messageTime = mktime(&tm);
//     time(&currentTime);

//     diff = difftime(currentTime, messageTime);

//     int days = diff / (60 * 60 * 24);
//     diff -= days * 60 * 60 * 24;
//     int hours = diff / (60 * 60);
//     diff -= hours * 60 * 60;
//     int minutes = diff / 60;
//     diff -= minutes * 60;
//     int seconds = diff;

//     if (days > 0) {
//         sprintf(elapsedTime, "%d days ago", days);
//     } else if (hours > 0) {
//         sprintf(elapsedTime, "%d hours ago", hours);
//     } else if (minutes > 0) {
//         sprintf(elapsedTime, "%d minutes ago", minutes);
//     } else {
//         sprintf(elapsedTime, "%d seconds ago", seconds);
//     }
// }

// Function to parse timestamp string into struct tm
int parseTimestamp(const char *timestamp, struct tm *tm_info) {
    // Example format: "2024-06-21 15:30:45"
    if (timestamp == NULL || tm_info == NULL) {
        return 0;
    }

    if (sscanf(timestamp, "%d-%d-%d %d:%d:%d",
               &tm_info->tm_year, &tm_info->tm_mon, &tm_info->tm_mday,
               &tm_info->tm_hour, &tm_info->tm_min, &tm_info->tm_sec) != 6) {
        return 0;  // Parsing failed
    }

    // Adjust tm_year to be relative to 1900
    tm_info->tm_year -= 1900;
    // Adjust tm_mon to be in the range 0-11
    tm_info->tm_mon -= 1;

    return 1;  // Parsing successful
}

void UserChatBox(char message[], int y, char username[], int is_current_user, char timestamp[20]) {
    int x;
    int maxLineLength = 60;
    int numLines = calculateNumLines(message, maxLineLength);

    if (is_current_user) {
        x = 120;
        setCursor_inc(x, y++);
        set_text_color(WHITE, DARK_GRAY);
    } else {
        x = 50;
        setCursor_inc(x, y++);
        set_text_color(WHITE, BLUE);
    }


    set_text_color(BLACK, YELLOW);
    // Print username and elapsed time
    time_t currentTime = time(NULL);
    struct tm tm_info;
    parseTimestamp(timestamp,&tm_info);
    time_t messageTime = mktime(&tm_info);
    double diff = difftime(currentTime, messageTime);
    int days = diff / (60 * 60 * 24);
    diff -= days * 60 * 60 * 24;
    int hours = diff / (60 * 60);
    diff -= hours * 60 * 60;
    int minutes = diff / 60;
    diff -= minutes * 60;
    int seconds = diff;

    char elapsedTime[20];
    if (days > 0) {
        sprintf(elapsedTime, "%d days ago", days);
    } else if (hours > 0) {
        sprintf(elapsedTime, "%d hours ago", hours);
    } else if (minutes > 0) {
        sprintf(elapsedTime, "%d minutes ago", minutes);
    } else {
        sprintf(elapsedTime, "%d seconds ago", seconds);
    }

    printf("  %-*s %20s", maxLineLength - 21, username, elapsedTime);
    setCursor_inc(x, y++);
    printf("  %-*s", maxLineLength, " ");
    setCursor_inc(x, y++);

    if (is_current_user) {
        set_text_color(WHITE, DARK_GRAY);
    } else {
        set_text_color(WHITE, BLUE);
    }
    setCursor_inc(x, y++);

    // Print message, wrapping text if necessary
    for (int i = 0; i < numLines; i++) {
        char buffer[maxLineLength + 1];
        strncpy(buffer, message + i * maxLineLength, maxLineLength);
        buffer[maxLineLength] = '\0';
        printf("  %-*s", maxLineLength, buffer);
        setCursor_inc(x, y++);
    }

    // Print bottom padding
    for (int i = 0; i < 2; i++) {
        printf("  %-*s", maxLineLength, " ");
        setCursor_inc(x, y++);
    }
}



void textField() {
    int x = 40, y = 80;
    setCursor_inc(x, y++);
    set_text_color(WHITE, ORANGE);
    printf("  %-*s", 150, " ");
    setCursor_inc(x, y++);
    printf("  %-*s", 150, "message");
    setCursor_inc(x, y++);
    printf("  %-*s", 150, " ");
}

int communityChat() {
    char message[MESSAGE_MAX_LEN];
    Message messages[100];
    int num_messages;

    while (1) {
        system("cls");
        home();
        printUserDetails();
        home_page_banner();
        side_menu(-1);
        Message messageStruct;
        num_messages = readMessages(messages, "CommunityChat.txt");
        chatPageDiv();
        chatTopBar("username");

        int currentHeight = 0;
        int start_index = 0;

        // Calculate total height of all chat boxes
        for (int i = 0; i < num_messages; i++) {
            currentHeight += getTotalChatBoxHeight(messages[i].message, 60);
        }

        // Determine the start index to fit messages within the div height
        if (currentHeight > DIV_HEIGHT) {
            currentHeight = 0;
            for (int i = num_messages - 1; i >= 0; i--) {
                int chatBoxHeight = getTotalChatBoxHeight(messages[i].message, 60);
                currentHeight += chatBoxHeight;
                if (currentHeight > DIV_HEIGHT) {
                    start_index = i + 1;
                    break;
                }
            }
        }

        currentHeight = 0;

        // Display the messages within the visible area
        for (int i = start_index; i < num_messages; i++) {
            int chatBoxHeight = getTotalChatBoxHeight(messages[i].message, 60);
            UserChatBox(messages[i].message, 20 + currentHeight, messages[i].username, strcmp(messages[i].username,current_user_details.username) == 0, messages[i].timestamp);
            currentHeight += chatBoxHeight;
        }

        set_text_color(BLUE, WHITE);
        printf("Enter your message (press Tab to exit): ");
        set_text_color(BLACK, WHITE);
        if (fgets(messageStruct.message, MESSAGE_MAX_LEN, stdin) == NULL) {
            break; // Handle end of file or error
        }

        // Remove the newline character if it exists
        messageStruct.message[strcspn(messageStruct.message, "\n")] = '\0';

        if (strcmp(messageStruct.message, "\t") == 0) {
            break; // Exit loop if Tab is pressed
        }

        strcpy(messageStruct.username, current_user_details.username);
        writeMessages(messageStruct, "CommunityChat.txt");

    }

    return 0;
}