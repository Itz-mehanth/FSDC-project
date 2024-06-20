
#include <stdio.h>
#include <windows.h>
#include <stdio.h>
#include <windows.h>
#include "illustrations.h"
#include "login.h"
#include "food_order_page.h"
#include "theme.h"
void home()
{
    int x = 0,y = 0;
    setCursor_inc(x,y++);
    set_text_color(YELLOW,RED);
    printf("       ___                  ");
    setCursor_inc(x,y++);
    printf("   ___/   |_________    __  ");
    setCursor_inc(x,y++);
    printf("  /       |         \\__/  \\ ");
    setCursor_inc(x,y++);
    printf("_/                   \\____/ ");
    setCursor_inc(x,y++);
    printf("|  ___  ___  ___  ___   |   ");
    setCursor_inc(x,y++);
    printf("| |___||___||___||___|  |   ");
    setCursor_inc(x,y++);
    printf("|                         | ");
    setCursor_inc(x,y++);
    printf("\\_________________________/ ");
    setCursor_inc(x,y++);
    printf(" /~~~~~~~~~~~~~~~~~~~~~\\    ");
    setCursor_inc(x,y++);
    printf("|      I LOVE FOOD      |   ");
    setCursor_inc(x,y++);
    printf(" \\_____________________/    ");
    setCursor_inc(x,y++);
    set_text_color(WHITE,RED);
    setCursor_inc(x,y++);
    printf("     FOOD DELIVERY APP     ");
    setCursor_inc(x,y++);
    set_text_color(CURRENT_FOREGROUND_COLOR,CURRENT_BACKGROUND_COLOR);

    return;
}

void face(){
    printf("       _____   \n");
    printf("     /       \\ \n");
    printf("     | o   o |\n");
    printf("     |   ^   |\n");
    printf("     \\  \\_/  / \n");
    printf("       \\___/  \n");
}

void loadingBar() {
    const int barWidth = 30;  // Width of the loading bar
    // Print the initial state of the loading bar
    printf("[");
    for (int i = 0; i < barWidth; ++i) {
        printf(" ");
    }
    printf("]\r[");  // Return to the start of the bar after printing it

    // Fill the loading bar gradually
    for (int i = 0; i <= barWidth; ++i) {
        Sleep(100);  // Sleep 100 milliseconds before filling the next block of the bar
        printf("=");  // Print the next block
        fflush(stdout);  // Flush stdout to ensure the bar is updated in real time
    }
    printf("]\n");
}

int heart() {
    const char *frames[] = {
        // ASCII art frames representing different stages of the heart breaking
        "     ######   ######\n"
        "   ######### #########\n"
        "  #####################\n"
        " #######################\n"
        "  ######################\n"
        "   ####################\n"
        "     ################\n"
        "       ############\n"
        "        #########\n"
        "          #####\n"
        "            #  \n"        ,
        "\n"
        "     ######   ######\n"
        "   ######### #########\n"
        "  #####################\n"
        "  #####################\n"
        "   ###################\n"
        "     ################\n"
        "       ############\n"
        "        #########\n"
        "          #####\n"
        "            #  \n"        ,
        "\n"
        "\n"
        "     ######   ######\n"
        "   ######### #########\n"
        "  ######################\n"
        "   ####################\n"
        "     ################\n"
        "       ############\n"
        "        #########\n"
        "          #####\n"
        "            #  \n"        ,
        "\n"
        "\n"
        "\n"
        "      #####   ######\n"
        "    ######## #########\n"
        "    ##################\n"
        "     ################\n"
        "       ############\n"
        "        #########\n"
        "          #####\n"
        "            #  \n"        ,
        "\n"
        "\n"
        "\n"
        "\n"
        "     ######   ######\n"
        "    ######## #########\n"
        "     ################\n"
        "       ############\n"
        "        #########\n"
        "          #####\n"
        "            #  \n"        ,
        "\n"
        "\n"
        "\n"
        "\n"
        "\n"
        "     ######   ######\n"
        "   ######### #########\n"
        "     ################\n"
        "       ############\n"
        "        #########\n"
        "          #####\n"
        "            #  \n"        ,
        "\n"
        "\n"
        "\n"
        "\n"
        "\n"
        "     ######   ######\n"
        "    #################\n"
        "      #############\n"
        "        #########\n"
        "          #####\n"
        "            #  \n"        ,
        "\n"
        "\n"
        "\n"
        "\n"
        "\n"
        "\n"

        "      ######  ######\n"
        "       ############\n"
        "        #########\n"
        "          #####\n"
        "            #  \n"        ,
        "\n"
        "\n"
        "\n"
        "\n"
        "\n"
        "\n"
        "       ####   #####\n"
        "      ###### ######\n"
        "        #########\n"
        "          #####\n"
        "            #  \n"        ,
        "\n"
        "\n"
        "\n"
        "\n"
        "\n"
        "\n"
        "\n"
        "        ###   ###\n"
        "        #########\n"
        "          #####\n"
        "            #  \n"        ,
        "\n"
        "\n"
        "\n"
        "\n"
        "\n"
        "\n"        
        "\n"
        "         ##   ##\n"
        "        #########\n"
        "          #####\n"
        "            #  \n"        ,
        "\n"
        "\n"
        "\n"
        "\n"
        "\n"
        "\n"
        "\n"
        "         ##   ##\n"
        "        #### ####\n"
        "          #####\n"
        "            #  \n"        ,
        "\n"
        "\n"
        "\n"
        "\n"
        "\n"
        "\n"
        "\n"
        "         ##   ##\n"
        "          #####\n"
        "            #  \n"        ,

       
    };

    const int numFrames = sizeof(frames) / sizeof(frames[0]);
    const int animationSpeed = 50;  // Milliseconds per frame
    set_text_color(RED,CURRENT_BACKGROUND_COLOR);
    // Loop through frames and display them in sequence
    for (int i = numFrames-1; i > 0 ; --i) 
    {
            system("cls");
            printf("s",frames[i]);
            Sleep(animationSpeed);
    }
    set_text_color(CURRENT_FOREGROUND_COLOR,CURRENT_BACKGROUND_COLOR);

    return 0;
}

void print_avatar(){
    printf("  O\n");
    printf("//|\\\n");
    printf("// \\\n");
}


void waterMelon(int x, int y) {
    // int x = 50;
    // int y=20;
    set_text_color(BLACK,WHITE);
    for (int i = 1; i < 11; i++)
    {
        setCursor_inc(x-1.3*i, y++);
        set_text_color(BLACK,DARK_GRAY*2);
        printf(" ");
        set_text_color(BLACK,RED);
        printf("%*s",i*3," ");
        set_text_color(BLACK,DARK_GRAY*2);
        printf(" ");
        
    }
    for (int i = 9; i > 5; i--)
    {
        setCursor_inc(x-i-3, y++);
        set_text_color(BLACK,GREEN);
        printf("  ");
        set_text_color(BLACK,RED);
        printf("%*s",i*3," ");
        set_text_color(BLACK,GREEN);
        printf("  ");
        
    }
    setCursor_inc(x-7, y++);
    printf("                   ");
    setCursor_inc(x, y-10);
    set_text_color(BLACK,DARK_GRAY*2);
    printf(" ");
    setCursor_inc(x+4, y-10);
    set_text_color(BLACK,DARK_GRAY*2);
    printf(" ");
    setCursor_inc(x-3, y-5);
    set_text_color(BLACK,DARK_GRAY*2);
    printf(" ");
    setCursor_inc(x+7, y-4);
    set_text_color(BLACK,DARK_GRAY*2);
    printf(" ");

    set_text_color(BLACK,WHITE);
    setCursor_inc(x-4, y+1);
    printf("WELCOME FRIEND");
}

