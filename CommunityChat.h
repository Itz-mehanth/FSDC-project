#include <stdio.h>
#include <time.h>
#include <windows.h>
#include <conio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h> // Include this to use strlen and strncpy

#define MESSAGE_MAX_LEN 1000


#define DIV_HEIGHT 38
#define CHATBOX_PADDING 6

typedef struct {
    char message[MESSAGE_MAX_LEN];
    char username[20];
    char timestamp[20];
} Message;

// Function to read messages from a CSV file
int readMessages(Message messages[], const char *filename);
// Function to write messages to a CSV file
void writeMessages(Message message, const char *filename);
void chatPageDiv();

void chatTopBar(char username[]);
int calculateNumLines(char *message, int maxLineLength);
int getTotalChatBoxHeight(char *message, int maxLineLength);
int canAddChatBox(int currentHeight, char *message, int maxLineLength) ;
void UserChatBox(char message[], int y, char username[], int is_current_user, char timestamp[20]);
void textField();
void calculateElapsedTime(const char *timestamp, char *elapsedTime) ;
int communityChat();