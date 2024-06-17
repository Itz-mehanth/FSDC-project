#include <stdio.h>
#include <Windows.h>
#include "sounds.h"
#include "theme.h"
#include "animations.h"
#include "food_order_page.h"


char customer_head[]="O";
char customer_body[]="/|\\";
char customer_leg[]="/ \\";

void printCar(int position, int head, int body, int leg) {
        // printf("\r"); // Carriage return to move cursor to beginning of line
    set_text_color(CURRENT_FOREGROUND_COLOR,RED);
    for (int i = 0; i < position; i++) {
        printf(" "); // Print spaces for car position
    }
    set_text_color(WHITE,RED);
    printf("    ______");
    // printf("    ___\n");
    for(int i=head;i>=1;i--) {
        printf(" ");
    } 
    set_text_color(BLACK,RED);
    printf("%s\n",customer_head);
    set_text_color(CURRENT_FOREGROUND_COLOR,RED);
    for (int i = 0; i < position; i++) {
        printf(" "); // Print spaces for car position
    }
    set_text_color(WHITE,RED);
    printf(" __|       \\____");
    // printf(" __|   \\__\n"); //
    for(int i=body;i>=1;i--) {
        printf(" ");
    } 
    set_text_color(BLACK,RED);
    printf("%s\n",customer_body);
    set_text_color(CURRENT_FOREGROUND_COLOR,RED);
    for (int i = 0; i < position; i++) {
        printf(" "); // Print spaces for car position
    }
    set_text_color(WHITE,RED);
    printf("L--");
    set_text_color(BLACK,RED);
    printf("(o)");
    set_text_color(WHITE,RED);
    printf("-----");
    set_text_color(BLACK,RED);
    printf("(o)");
    set_text_color(WHITE,RED);
    printf("--I");
    // printf("I--o---o-I\n");
    for(int i=leg;i>=1;i--) {
        printf(" ");
    } 
    set_text_color(BLACK,RED);
    printf("%s\n",customer_leg);
    set_text_color(CURRENT_FOREGROUND_COLOR,RED);

    set_text_color(WHITE,BLACK);
    printf("===============================================\n"); 
    set_text_color(CURRENT_FOREGROUND_COLOR,RED);
  
    fflush(stdout); // Flush output buffer for immediate display
}

void slide(int i){
    int y = 0;
    for (int  j = 0; j < 20; j++)
    {
        setCursor_inc(i,j);
        printf("                      ");
    }
    
    set_text_color(WHITE,RED);
}
void slider(){
    for (int  i = 50 ;i >= 0; i--)
    {
        slide(i);
        Sleep(100);
    }
    
}

int carAnime() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    int head=33;
    int body=26;
    int leg=25;
    system("cls");
    set_text_color(CURRENT_FOREGROUND_COLOR,RED);
    for (int position = 0; position <= 26; position++) {
        printf("\n\n\n\n\n\n\n");
        set_text_color(YELLOW,CURRENT_BACKGROUND_COLOR);
        printf("\t  F O O D  D E L I V E R Y  A P P\n");
        set_text_color(CURRENT_FOREGROUND_COLOR,CURRENT_BACKGROUND_COLOR);
        printf("\t\t  Loading %d%%\n",position*4);
        set_text_color(CURRENT_FOREGROUND_COLOR,RED);
        printf("\v\v");
        if (position%8==0)
        {
            car_horn();
        }
        
        printCar(position,head,body,leg);
        if (position==25)
        {   
            printf("\n\t\t  ");
            for (int i = 0; i < 5; i++)
            {
                SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN |  FOREGROUND_RED | FOREGROUND_INTENSITY);
                printf("* ");
                sleep(0.5);
            }

            SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY);

            printf("\n\t  ");
            system("pause");
            select_beep();
            return 1;
        }
        if (head>0)
        {
            head--;
        }
        if (body>0)
        {
            body--;
        }
        if (leg>0)
        {
            leg--;
        }
        sleep(0.1);
        system("cls"); 
        set_text_color(CURRENT_FOREGROUND_COLOR,RED);
    }
    
    set_text_color(CURRENT_FOREGROUND_COLOR,CURRENT_BACKGROUND_COLOR);

    return 0;
}
