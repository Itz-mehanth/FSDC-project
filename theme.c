#include <stdlib.h>
#include <stdio.h>
#include <Windows.h>
#include "illustrations.h"
#include "theme.h"
#include "food_order_page.h"
#include "sounds.h"
#include "notification.h"
#include "login.h"

int CURRENT_FOREGROUND_COLOR = BLACK;
int CURRENT_BACKGROUND_COLOR = WHITE;
void set_text_color(int foreground_color, int background_color) {
#if COLOR_CODES_SUPPORTED
    // Windows-specific color codes using escape sequences
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, foreground_color | (background_color << 4));
#else
    // Handle color codes not supported (optional: print a message)
    printf("Color codes not supported on this system.\n");
#endif
}

void set_theme(){
    set_text_color(CURRENT_FOREGROUND_COLOR,CURRENT_BACKGROUND_COLOR);
}

void theme_reset(){
    set_text_color(BLACK,WHITE);
}
int change_theme() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    int choice;
    int x = 50, y=6;

    setCursor_inc(x,y++);
    set_text_color(WHITE,RED);
    printf("Select a theme:");
    set_text_color(BLACK,CURRENT_BACKGROUND_COLOR);
    setCursor_inc(x,y++);
    printf("1. Dark Mode");
    setCursor_inc(x,y++);
    printf("2. Light Mode");
    setCursor_inc(x,y++);
    printf("3. Fire theme");
    setCursor_inc(x,y++);
    printf("4. Ocean Theme");
    setCursor_inc(x,y++);
    printf("5. Nature Theme");
    setCursor_inc(x,y++);
    printf("6. Grape Theme");    
    setCursor_inc(x,y++);
    printf("7. Honey Theme");    
    setCursor_inc(x,y++);
    printf("8. Back");

    setCursor_inc(x,y++);
    printf("Enter your choice: ");
    scanf("%d", &choice);
    select_beep();
    switch (choice) {
        case 1:
            CURRENT_FOREGROUND_COLOR=WHITE;
            CURRENT_BACKGROUND_COLOR=BLACK;
            break;

        case 2:   
            CURRENT_FOREGROUND_COLOR=BLACK;
            CURRENT_BACKGROUND_COLOR= LIGHT_GRAY;
            break;

        case 3:   
            CURRENT_BACKGROUND_COLOR=RED;
            CURRENT_FOREGROUND_COLOR=WHITE;
            break;

        case 4:   
            CURRENT_BACKGROUND_COLOR=CYAN;
            CURRENT_FOREGROUND_COLOR=WHITE;
            break;

        case 5:   
            CURRENT_FOREGROUND_COLOR=WHITE;
            CURRENT_BACKGROUND_COLOR=GREEN;
            break;

        case 6:  
            CURRENT_FOREGROUND_COLOR=WHITE;
            CURRENT_BACKGROUND_COLOR=MAGENTA;
            break;

        case 7:  
            CURRENT_BACKGROUND_COLOR=YELLOW;
            CURRENT_FOREGROUND_COLOR=WHITE;
            break;

        case 8:  
            return 0;
            break;

        default:
            print_error("Invalid input\n");
            break;
    }

    if(readCurrentUser()==1){
        top_bar();
    }
    return 1;
}

void print_error(char *message){
    error_beep();
    MessageBox(NULL, message, "Error", MB_ICONERROR | MB_OK);

}

void print_success(char *message){
    notification_beep();
    MessageBox(NULL, message, "Success", MB_ICONINFORMATION | MB_OK);
}

void welcome_pop(){
    notification_beep();
    MessageBox(NULL, "Welcome to the Food Delivery App!", "Welcome", MB_ICONINFORMATION | MB_OK);
}