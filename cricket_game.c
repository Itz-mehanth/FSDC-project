#include <stdio.h>
#include <windows.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>
#include "login.h"
#include "food_order_page.h"
#include "sounds.h"
#include "cricket_game.h"
#include <conio.h>  // For kbhit() and getch()
#include "theme.h"

enum Direction { UP, DOWN, LEFT, RIGHT };

void setCursor(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
float ballsToOvers(int balls) {
    float overs = balls / 6;
    float remainingBalls = balls % 6;
    float Inovers = overs + remainingBalls/10;
    return Inovers;
}
void print_scoreboard(char *team,char *opponent,int runs,int balls){  
    setCursor(0,2);  
    printf("+===============+\n");
    printf("|%5s V/S %-5s|\n",team,opponent);
    printf("+===============+\n");
    printf("You are Batting\n");
    printf("Target: %d Runs in %.1f Overs\n",runs,ballsToOvers(balls));
}
void print_score(int score){
        setCursor(0,1);
        printf("Score: %d\n",score);
}
void print_ground() {
    printf("\n\n\n\n\n\n\n");
    printf("     O                                                 O\n");
    printf("||| /|\\                                     |||       /|\\ \n");
    printf("||| / \\\\                                    |||       / \\ \n");
    set_text_color(CURRENT_FOREGROUND_COLOR,GREEN);
    printf("                                                        \n");
    set_text_color(CURRENT_FOREGROUND_COLOR,CURRENT_BACKGROUND_COLOR);
}
void print_hit() {
    hit();
    setCursor(0,6);
    printf("\n\n\n");
    printf("       O                                               O\n");
    printf("|||   /|\\/                                  |||       /|\\ \n");
    printf("|||   / \\                                   |||       / \\ \n");
    set_text_color(CURRENT_FOREGROUND_COLOR,GREEN);
    printf("                                                        \n");
    set_text_color(CURRENT_FOREGROUND_COLOR,CURRENT_BACKGROUND_COLOR);
}

void print_bowl(int score,char *team,char *opponent,int runs,int balls) {
        print_score(score);
        print_scoreboard(team,opponent,runs,balls);
        printf("\n\n");
        printf("     O                                                 O\n");
        printf("||| /|\\                                     |||       /|\\ \n");
        printf("||| / \\\\                                    |||       / \\ \n");
        set_text_color(CURRENT_FOREGROUND_COLOR,GREEN);
        printf("                                                        \n");
        set_text_color(CURRENT_FOREGROUND_COLOR,CURRENT_BACKGROUND_COLOR);
        Sleep(1000);
        system("cls");
        print_score(score);
        print_scoreboard(team,opponent,runs,balls);
        printf("\n\n");
        printf("     O                                               O\n");
        printf("||| /|\\                                     |||     /|\\ \n");
        printf("||| / \\\\                                    |||     / \\ \n");
        set_text_color(CURRENT_FOREGROUND_COLOR,GREEN);
        printf("                                                        \n");
        set_text_color(CURRENT_FOREGROUND_COLOR,CURRENT_BACKGROUND_COLOR);
        Sleep(1000);
        system("cls");
        print_score(score);
        print_scoreboard(team,opponent,runs,balls);
        printf("\n\n");
        printf("     O                                             O\n");
        printf("||| /|\\                                     |||   /|\\ \n");
        printf("||| / \\\\                                    |||   / \\ \n");
        set_text_color(CURRENT_FOREGROUND_COLOR,GREEN);
        printf("                                                        \n");
        set_text_color(CURRENT_FOREGROUND_COLOR,CURRENT_BACKGROUND_COLOR);
        Sleep(1000);

    
}


void printBall(int x, int y) {
    setCursor(x, y);
    printf(" ");
}

void clearBall(int x, int y) {
    setCursor(x, y);
    printf(" "); // Clear by printing a space
}

int kbhit(void) {
    HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE);
    DWORD nEvents;
    INPUT_RECORD *eventBuffer;
    DWORD i;
    int result = 0;

    if (hStdin == INVALID_HANDLE_VALUE) {
        return 0;
    }

    GetNumberOfConsoleInputEvents(hStdin, &nEvents);
    if (nEvents == 0) {
        return 0;
    }

    eventBuffer = (INPUT_RECORD *)malloc(sizeof(INPUT_RECORD) * nEvents);
    if (eventBuffer == NULL) {
        return 0;
    }

    if (!ReadConsoleInput(hStdin, eventBuffer, nEvents, &nEvents)) {
        free(eventBuffer);
        return 0;
    }

    for (i = 0; i < nEvents; ++i) {
        if (eventBuffer[i].EventType == KEY_EVENT && eventBuffer[i].Event.KeyEvent.bKeyDown) {
            result = 1;
            break;
        }
    }

    free(eventBuffer);
    return result;
}

int score_manager(int hitpoint,int *score){
    if(hitpoint == 7){
        *score = *score + 6;
        print_score(*score);
        set_text_color(GREEN,CURRENT_BACKGROUND_COLOR);
        printf("=================\n");
        printf("|      S I X     |\n");
        printf("=================\n");
        set_text_color(CURRENT_FOREGROUND_COLOR,CURRENT_BACKGROUND_COLOR);
        applause();
        return 0;
    }else if (hitpoint >=8 && hitpoint <=9)
    {
        *score = *score + 4;
        print_score(*score);
        set_text_color(GREEN,CURRENT_BACKGROUND_COLOR);
        printf("=================\n");
        printf("|    F O U R     |\n");
        printf("=================\n");
        set_text_color(CURRENT_FOREGROUND_COLOR,CURRENT_BACKGROUND_COLOR);
        applause();
        return 0;
    }else if (hitpoint >=11 && hitpoint <=12){
        *score = *score + 3;
        print_score(*score);
        set_text_color(GREEN,CURRENT_BACKGROUND_COLOR);
        printf("=================\n");
        printf("|    T H R E E   |\n");
        printf("=================\n");
        set_text_color(CURRENT_FOREGROUND_COLOR,CURRENT_BACKGROUND_COLOR);
        applause();
        return 0;
    }
    else if (hitpoint >=13 && hitpoint <=13){
        *score = *score + 2;
        print_score(*score);
        set_text_color(GREEN,CURRENT_BACKGROUND_COLOR);
        printf("=================\n");
        printf("|      T W O     |\n");
        printf("=================\n");
        set_text_color(CURRENT_FOREGROUND_COLOR,CURRENT_BACKGROUND_COLOR);
        applause();
        return 0;
    }
    else if (hitpoint >=14 && hitpoint <=14){
        *score = *score + 1;
        print_score(*score);
        set_text_color(GREEN,CURRENT_BACKGROUND_COLOR);
        printf("=================\n");
        printf("|      O N E    |\n");
        printf("=================\n");
        set_text_color(CURRENT_FOREGROUND_COLOR,CURRENT_BACKGROUND_COLOR);
        applause();
        return 0;
    }
    else {
        set_text_color(RED,CURRENT_BACKGROUND_COLOR);
        printf("=================\n");
        printf("|      O U T    |\n");
        printf("=================\n");
        set_text_color(CURRENT_FOREGROUND_COLOR,CURRENT_BACKGROUND_COLOR);
        out();
        print_error("YOU LOSE THE GAME\n");
        return 1;
    }
}

char* choose_team(int rand){
    switch (rand)
    {
    case 1:

        return "CSK";
        break;
    case 2:
    
        return "DC";
        break;
    case 3:
    
        return "GT";
        break;
    case 4:
    
        return "KKR";
        break;
    case 5:
    
        return "LGS";
        break;
    case 6:
    
        return "MI";
        break;
    case 7:
    
        return "PBKS";
        break;
    case 8:
    
        return "RR";
        break;
    case 9:
    
        return "RCB";
        break;
    case 10:
    
        return "SRH";
        break;
    
    default:
        break;
    }
}


int cricket_game() {
    crowd();
    int score =0, match_over = 0;
    char opponent[10],team_name[10];
    int rand_op;
    int rand_balls;
    int rand_target;
    int team;
    srand(time(NULL)); // Seed the random number generator with current time

    system("cls");
    print_ground();
    int x = 80,Y=15;
    setCursor_inc(x,Y++);
    printf("1.CSK   2.DC   3.GT   4.KKR   5.LSG");
    setCursor_inc(x,Y++);
    printf("6.MI    7.PK   8.RR   9.RCB   10.SRH\n");
    printf("Select your team: ");
    scanf("%d",&team);
    strcpy(team_name ,choose_team(team));
    A:
    rand_op = rand() % 10 + 1;
    if (rand_op == team)
    {
        goto A;
    }
    
    strcpy(opponent ,choose_team(rand_op));
    rand_target = rand() % 50 + 20;
    D:
    rand_balls = rand() % 20 + 5;
    if (rand_balls < rand_target/6+4)
    {
        goto D;
    }

    print_scoreboard(team_name, opponent,rand_target-score,ballsToOvers(rand_balls));
    printf("Press Enter to start the game: ");
    char c = getchar();
    system("cls");
    if (c != '\n') {
        return 0;
    }
    B:
    print_bowl(score,team_name, opponent,rand_target-score,rand_balls);

    int startX = 45; // Start position
    int endX = 7;    // End position
    float y = 9;     // Vertical position

    // Move the ball from right to left
    while (startX >= endX && !match_over) {
        print_scoreboard(team_name, opponent,rand_target-score,rand_balls);
        print_score(score);
        printBall(startX, (int)y);
        Sleep(1);
        clearBall(startX, (int)y);
        float deltaY = (rand() % 6 + 3) / 100.0f; // Random value between 0.03 and 0.08
        y += deltaY;                              // Update the vertical position
        startX--;                                 // Decrement the horizontal position
        Sleep(50);  
        if(kbhit()){
            print_hit();
            setCursor(0,3);
            match_over = score_manager(startX,&score);
            rand_balls -=1;
            if (rand_balls == 0)
            {
                if (score>=rand_target)
                {
                    print_success("CONGRATULATIONS YOU WON THE GAME\n");
                    applause();
                    return 1; 
                }
                else if (score<rand_target)
                {
                    print_error("YOU LOSE THE GAME\n");
                    return 1;
                }
                
            }
            
            if(match_over){
                print_hit();
                return 1;
            }
            getchar();
            goto B;
        }                              // Control the speed of the ball
    }
    if(!kbhit()){
        print_hit();
        setCursor(0,3);
        set_text_color(RED,CURRENT_BACKGROUND_COLOR);
        printf("=================\n");
        printf("|     O U T     |\n");
        printf("=================\n");      
        set_text_color(CURRENT_FOREGROUND_COLOR,CURRENT_BACKGROUND_COLOR);
        out();
        print_error("YOU LOSE THE GAME\n");
    }

    setCursor(0, 0); // Set cursor to default position
    return 0;
}
