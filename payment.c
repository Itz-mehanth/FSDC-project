#include <stdio.h>
#include <string.h>
#include <time.h>
#include <conio.h>
#include "restaurants_home.h"
#include "food_order_page.h"
#include "delivery_boy_selection.h"
#include "partner_path.h"
#include <windows.h>
#include "login.h"
#include <stdlib.h>
#include "theme.h"
#include "animations.h"
#include "illustrations.h"
#include "payment.h"
#include "notification.h"


char* generate_transaction_id() {
  char *transaction_id = (char*)malloc(11 * sizeof(char)); // Allocate memory for 10 digits + null terminator

  // Seed the random number generator
  srand(time(NULL));

  for (int i = 0; i < 10; i++) {
    transaction_id[i] = '0' + rand() % 10; // Generate random digits between '0' and '9'
  }
  transaction_id[10] = '\0'; // Add null terminator

  return transaction_id;
}
int simulate_processing() {
  printf("Processing transaction...\n");
  loadingBar();
  return 1;
}
void display_confirmation(float amount) {
    time_t current_time = time(NULL);
    struct tm *local_time = localtime(&current_time);
    if (local_time == NULL) {
        perror("localtime");  // Print error message
    // Handle the error here
    }

    print_success("\t\tTransaction successful for FOOD DELIVERY APP!\n");
    printf("\t\t\tDetails:                      \n");
    printf("\t\t\tAmount: Rs.%.2f               \n", amount);
    printf("\t\t\tPaid to FOOD DELIVERY APP     \n");
    printf("\t\t\tUPI ID: 9849849484            \n");
    printf("\t\t\tDate of Payment: %02d/%02d/%04d           ", local_time->tm_mday, local_time->tm_mon + 1, local_time->tm_year + 1900);
    printf("    %02d:%02d:%02d\n", local_time->tm_hour, local_time->tm_min, local_time->tm_sec);
    printf("\t\t\tUPI transaction ID: %s      \n", generate_transaction_id());
    getchar();
}

int upi_simulation(){
    float amount;
    char confirmation;
    int upi_pin;
    system("cls");
    top_bar();
    // set_text_color(YELLOW,CURRENT_BACKGROUND_COLOR);
    // printf("--------------------------------------------------------------------------------------------------\n");
    // printf("\t\t\t\tPaying FOOD DELIVERY APP                \n");
    // printf("\t\t\t\tBanking name: FOOD DELIVERY APP         \n");
    // printf("\t\t\t\tAccount number: 1234567890              \n");
    // printf("\t\t\t\tUPI ID: 1234567890                      \n");
    // printf("\t\t\t\t\tAmount: Rs.");
    // scanf("%f", &amount);
    // set_text_color(CURRENT_FOREGROUND_COLOR,CURRENT_BACKGROUND_COLOR);
    // system("cls");
    // top_bar();
    // set_text_color(RED,YELLOW);
    // printf("\n");
    // printf("                                                                To:%20s\n","FOOD DELIVERY APP");
    // printf("                                                                Sending:%.2f          \n",amount);
    // printf("\n");
    // set_text_color(YELLOW,CURRENT_BACKGROUND_COLOR);
    // printf("\tYou're transferring money from your acccount to FOOD DELIVERY APP\n\n");
    // set_text_color(CURRENT_FOREGROUND_COLOR,CURRENT_BACKGROUND_COLOR);
    // printf("\t\t\t\tEnter 4-digit upi pin: ");
    // scanf("%d", &upi_pin);
    A:
    printf("\t\t\t\tConfirm payment(");
    set_text_color(GREEN,CURRENT_BACKGROUND_COLOR);
    printf("Y");
    set_text_color(CURRENT_FOREGROUND_COLOR,CURRENT_BACKGROUND_COLOR);
    printf("/");
    set_text_color(RED,CURRENT_BACKGROUND_COLOR);
    printf("n");
    set_text_color(CURRENT_FOREGROUND_COLOR,CURRENT_BACKGROUND_COLOR);
    printf(")?");
    scanf(" %c", &confirmation);
    if(confirmation == 'Y'){
        set_text_color(YELLOW,CURRENT_BACKGROUND_COLOR);
        if(simulate_processing()){
            return 1;
        } 
        set_text_color(CURRENT_FOREGROUND_COLOR,CURRENT_BACKGROUND_COLOR);
        display_confirmation(amount);
    }else if(confirmation == 'n'){
        return 0;
    }else{
        printf("Invalid input\n");
        goto A;
    }

}
int simulate_payment() {
    char num_char[5];
    int count = 0;
    char ch;
    int y=18,x=90;
    int selected;
    char nums[4];
    system("cls");
        home();
        printUserDetails();
        side_menu(-1);
        setCursor_inc(x,y++);
        set_text_color(YELLOW,YELLOW);
        printf("                                                      ");
        setCursor_inc(x,y++);
        printf("                                                      ");
        setCursor_inc(x,y++);
        printf("                                                      ");
        setCursor_inc(x,y++);
        printf("                                                      ");
        setCursor_inc(x,y++);
        printf("      ");
        set_text_color(WHITE,WHITE);
        printf("      ");
        set_text_color(YELLOW,YELLOW);
        printf("      ");
        set_text_color(WHITE,WHITE);
        printf("      ");
        set_text_color(YELLOW,YELLOW);
        printf("      ");
        set_text_color(WHITE,WHITE);
        printf("      ");
        set_text_color(YELLOW,YELLOW);
        printf("      ");
        set_text_color(WHITE,WHITE);
        printf("      ");
        set_text_color(YELLOW,YELLOW);
        printf("      ");
        setCursor_inc(x,y++);
        printf("      ");
        set_text_color(BLACK,WHITE);
        printf("      ");
        set_text_color(YELLOW,YELLOW);
        printf("      ");
        set_text_color(BLACK,WHITE);
        printf("      ");   
        set_text_color(YELLOW,YELLOW);
        printf("      ");
        set_text_color(BLACK,WHITE);
        printf("      ");
        set_text_color(YELLOW,YELLOW);
        printf("      ");
        set_text_color(BLACK,WHITE);
        printf("      ");
        set_text_color(YELLOW,YELLOW);
        printf("      ");
        setCursor_inc(x,y++);
        printf("      ");
        set_text_color(WHITE,WHITE);
        printf("      ");
        set_text_color(YELLOW,YELLOW);
        printf("      ");
        set_text_color(WHITE,WHITE);
        printf("      ");
        set_text_color(YELLOW,YELLOW);
        printf("      ");
        set_text_color(WHITE,WHITE);
        printf("      ");
        set_text_color(YELLOW,YELLOW);
        printf("      ");
        set_text_color(WHITE,WHITE);
        printf("      ");
        set_text_color(YELLOW,YELLOW);
        printf("      ");
        setCursor_inc(x,y++);


        printf("                                                      ");
        setCursor_inc(x,y++);
        printf("                                                      ");
        setCursor_inc(x,y++);
        printf("                                                      ");
        setCursor_inc(x,y++);
        printf("                                                      ");
        setCursor_inc(x,y++);
        printf("                                                      ");
        setCursor_inc(x,y++);
        printf("                                                      ");
        setCursor_inc(x,y++);
        printf("                                                      ");
        setCursor_inc(x,y++);
        printf("                                                      ");
        setCursor_inc(x,y++);
        printf("                                                      ");
        setCursor_inc(x,y++);
        printf("                                                      ");
        setCursor_inc(x,y++);

        printf(" ");
        set_text_color(BLACK,WHITE);
        printf("                 ");
        set_text_color(YELLOW,YELLOW);
        printf(" ");
        set_text_color(BLACK,WHITE);
        printf("                 ");
        set_text_color(YELLOW,YELLOW);
        printf(" ");
        set_text_color(BLACK,WHITE);
        printf("                ");
        set_text_color(YELLOW,YELLOW);
        printf(" ");
        setCursor_inc(x,y++);
        set_text_color(YELLOW,YELLOW);
        printf(" ");
        set_text_color(BLACK,WHITE);
        printf("        7        ");
        set_text_color(YELLOW,YELLOW);
        printf(" ");
        set_text_color(BLACK,WHITE);
        printf("        8        ");
        set_text_color(YELLOW,YELLOW);
        printf(" ");
        set_text_color(BLACK,WHITE);
        printf("        9       ");
        set_text_color(YELLOW,YELLOW);
        printf(" ");

        setCursor_inc(x,y++);
        printf(" ");
        set_text_color(YELLOW,WHITE);
        printf("_________________");
        set_text_color(YELLOW,YELLOW);
        printf(" ");
        set_text_color(YELLOW,WHITE);
        printf("_________________");
        set_text_color(YELLOW,YELLOW);
        printf(" ");
        set_text_color(YELLOW,WHITE);
        printf("________________");
        set_text_color(YELLOW,YELLOW);
        printf(" ");
        
        setCursor_inc(x,y++);
        set_text_color(YELLOW,YELLOW);
        printf(" ");
        set_text_color(BLACK,WHITE);
        printf("                 ");
        set_text_color(YELLOW,YELLOW);
        printf(" ");
        set_text_color(BLACK,WHITE);
        printf("                 ");
        set_text_color(YELLOW,YELLOW);
        printf(" ");
        set_text_color(BLACK,WHITE);
        printf("                ");
        set_text_color(YELLOW,YELLOW);
        printf(" ");

        setCursor_inc(x,y++);
        set_text_color(YELLOW,YELLOW);
        printf(" ");
        set_text_color(BLACK,WHITE);
        printf("        4        ");
        set_text_color(YELLOW,YELLOW);
        printf(" ");
        set_text_color(BLACK,WHITE);
        printf("        5        ");
        set_text_color(YELLOW,YELLOW);
        printf(" ");
        set_text_color(BLACK,WHITE);
        printf("        6       ");
        set_text_color(YELLOW,YELLOW);
        printf(" ");

        setCursor_inc(x,y++);
        printf(" ");
        set_text_color(YELLOW,WHITE);
        printf("_________________");
        set_text_color(YELLOW,YELLOW);
        printf(" ");
        set_text_color(YELLOW,WHITE);
        printf("_________________");
        set_text_color(YELLOW,YELLOW);
        printf(" ");
        set_text_color(YELLOW,WHITE);
        printf("________________");
        
        set_text_color(YELLOW,YELLOW);
        setCursor_inc(x,y++);
        printf(" ");
        set_text_color(BLACK,WHITE);
        printf("                 ");
        set_text_color(YELLOW,YELLOW);
        printf(" ");
        set_text_color(BLACK,WHITE);
        printf("                 ");
        set_text_color(YELLOW,YELLOW);
        printf(" ");
        set_text_color(BLACK,WHITE);
        printf("                ");
        set_text_color(YELLOW,YELLOW);
        printf(" ");
        setCursor_inc(x,y++);
        set_text_color(YELLOW,YELLOW);
        printf(" ");
        set_text_color(BLACK,WHITE);
        printf("        1        ");
        set_text_color(YELLOW,YELLOW);
        printf(" ");
        set_text_color(BLACK,WHITE);
        printf("        2        ");
        set_text_color(YELLOW,YELLOW);
        printf(" ");
        set_text_color(BLACK,WHITE);
        printf("        3       ");
        set_text_color(YELLOW,YELLOW);
        printf(" ");

        setCursor_inc(x,y++);
        printf(" ");
        set_text_color(YELLOW, WHITE);
        printf("_________________");
        set_text_color(YELLOW,YELLOW);
        printf(" ");
        set_text_color(YELLOW,WHITE);
        printf("_________________");
        set_text_color(YELLOW,YELLOW);
        printf(" ");
        set_text_color(YELLOW,WHITE);
        printf("________________");
        set_text_color(YELLOW,YELLOW);
        printf(" ");

        setCursor_inc(x,y++);
        set_text_color(YELLOW,YELLOW);
        printf(" ");
        set_text_color(WHITE, WHITE);
        printf("                 ");
        set_text_color(YELLOW,YELLOW);
        printf(" ");
        set_text_color(BLACK,WHITE);
        printf("                 ");
        set_text_color(YELLOW,YELLOW);
        printf(" ");
        set_text_color(WHITE,WHITE);
        printf("                ");
        set_text_color(YELLOW,YELLOW);
        printf(" ");

        setCursor_inc(x,y++);
        printf(" ");
        set_text_color(WHITE, WHITE);
        printf("                 ");
        set_text_color(YELLOW,YELLOW);
        printf(" ");
        set_text_color(BLACK,WHITE);
        printf("                 ");
        set_text_color(YELLOW,YELLOW);
        printf(" ");
        set_text_color(WHITE,WHITE);
        printf("                ");
        set_text_color(YELLOW,YELLOW);
        printf(" ");


        setCursor_inc(x,y++);
        set_text_color(YELLOW,YELLOW);
        printf(" ");
        set_text_color(WHITE,WHITE);
        printf("                 ");
        set_text_color(YELLOW,YELLOW);
        printf(" ");
        set_text_color(BLACK, WHITE);
        printf("        0        ");
        set_text_color(YELLOW,YELLOW);
        printf(" ");
        set_text_color(WHITE,WHITE);
        printf("                ");
        set_text_color(YELLOW,YELLOW);
        printf(" ");
        set_text_color(WHITE,WHITE);
        setCursor_inc(x,y++);
        set_text_color(YELLOW,YELLOW);
        printf(" ");
        set_text_color(YELLOW,WHITE);
        printf("_________________");
        set_text_color(YELLOW,YELLOW);
        printf(" ");
        set_text_color(YELLOW,WHITE);
        printf("_________________");
        set_text_color(YELLOW,YELLOW);
        printf(" ");
        set_text_color(YELLOW,WHITE);
        printf("________________");
        set_text_color(YELLOW,YELLOW);
        printf(" ");
        setCursor_inc(x,y++);
        set_text_color(BLACK,WHITE);
    while (count < 4)
    {
        
        
        if(isdigit(ch = _getch()) == 0 ){
            continue;
        }
        num_char[count] = ch;
        switch(ch){
            case '1':
                selected = 1;
                break;
            case '2':
                selected = 2;
                break;
            case '3':
                selected = 3;
                break;
            case '4':
                selected = 4;
                break;
            case '5':
                selected = 5;
                break;
            case '6':
                selected = 6;
                break;
            case '7':
                selected = 7;
                break;
            case '8':
                selected = 8;
                break;
            case '9':
                selected = 9;
                break;
            case '0':
                selected = 0;
                break;
        }
        nums[count]=selected;
        count++;
        system("cls");
        home();
        printUserDetails();
        side_menu(-1);
        y=18,x=90;
        setCursor_inc(x,y++);
        set_text_color(YELLOW,YELLOW);
        printf("                                                      ");
        setCursor_inc(x,y++);
        printf("                                                      ");
        setCursor_inc(x,y++);
        printf("                                                      ");
        setCursor_inc(x,y++);
        printf("                                                      ");
        setCursor_inc(x,y++);
        printf("      ");
        set_text_color(WHITE,WHITE);
        printf("      ");
        set_text_color(YELLOW,YELLOW);
        printf("      ");
        set_text_color(WHITE,WHITE);
        printf("      ");
        set_text_color(YELLOW,YELLOW);
        printf("      ");
        set_text_color(WHITE,WHITE);
        printf("      ");
        set_text_color(YELLOW,YELLOW);
        printf("      ");
        set_text_color(WHITE,WHITE);
        printf("      ");
        set_text_color(YELLOW,YELLOW);
        printf("      ");
        setCursor_inc(x,y++);
        printf("      ");
        set_text_color(BLACK,WHITE);
        printf("   %1d  ",isdigit( num_char[0]) ? nums[0] : 0);
        set_text_color(YELLOW,YELLOW);
        printf("      ");
        set_text_color(BLACK,WHITE);
        printf("   %1d  ",isdigit( num_char[1]) ? nums[1] : 0);   
        set_text_color(YELLOW,YELLOW);
        printf("      ");
        set_text_color(BLACK,WHITE);
        printf("   %1d  ",isdigit( num_char[2]) ? nums[2] : 0);
        set_text_color(YELLOW,YELLOW);
        printf("      ");
        set_text_color(BLACK,WHITE);
        printf("   %1d  ",isdigit( num_char[3]) ? nums[3] : 0);
        set_text_color(YELLOW,YELLOW);
        printf("      ");
        setCursor_inc(x,y++);
        printf("      ");
        set_text_color(WHITE,WHITE);
        printf("      ");
        set_text_color(YELLOW,YELLOW);
        printf("      ");
        set_text_color(WHITE,WHITE);
        printf("      ");
        set_text_color(YELLOW,YELLOW);
        printf("      ");
        set_text_color(WHITE,WHITE);
        printf("      ");
        set_text_color(YELLOW,YELLOW);
        printf("      ");
        set_text_color(WHITE,WHITE);
        printf("      ");
        set_text_color(YELLOW,YELLOW);
        printf("      ");
        setCursor_inc(x,y++);


        printf("                                                      ");
        setCursor_inc(x,y++);
        printf("                                                      ");
        setCursor_inc(x,y++);
        printf("                                                      ");
        setCursor_inc(x,y++);
        printf("                                                      ");
        setCursor_inc(x,y++);
        printf("                                                      ");
        setCursor_inc(x,y++);
        printf("                                                      ");
        setCursor_inc(x,y++);
        printf("                                                      ");
        setCursor_inc(x,y++);
        printf("                                                      ");
        setCursor_inc(x,y++);
        printf("                                                      ");
        setCursor_inc(x,y++);
        printf("                                                      ");
        setCursor_inc(x,y++);

        printf(" ");
        set_text_color(BLACK,selected==7 ? CYAN : WHITE);
        printf("                 ");
        set_text_color(YELLOW,YELLOW);
        printf(" ");
        set_text_color(BLACK,selected==8 ? CYAN : WHITE);
        printf("                 ");
        set_text_color(YELLOW,YELLOW);
        printf(" ");
        set_text_color(BLACK,selected==9 ? CYAN : WHITE);
        printf("                ");
        set_text_color(YELLOW,YELLOW);
        printf(" ");
        setCursor_inc(x,y++);
        set_text_color(YELLOW,YELLOW);
        printf(" ");
        set_text_color(BLACK,selected==7 ? CYAN : WHITE);
        printf("        7        ");
        set_text_color(YELLOW,YELLOW);
        printf(" ");
        set_text_color(BLACK,selected==8 ? CYAN : WHITE);
        printf("        8        ");
        set_text_color(YELLOW,YELLOW);
        printf(" ");
        set_text_color(BLACK,selected==9 ? CYAN : WHITE);
        printf("        9       ");
        set_text_color(YELLOW,YELLOW);
        printf(" ");

        setCursor_inc(x,y++);
        printf(" ");
        set_text_color(YELLOW,selected==7 ? CYAN : WHITE);
        printf("_________________");
        set_text_color(YELLOW,YELLOW);
        printf(" ");
        set_text_color(YELLOW,selected==8 ? CYAN : WHITE);
        printf("_________________");
        set_text_color(YELLOW,YELLOW);
        printf(" ");
        set_text_color(YELLOW,selected==9 ? CYAN : WHITE);
        printf("________________");
        set_text_color(YELLOW,YELLOW);
        printf(" ");
        
        setCursor_inc(x,y++);
        set_text_color(YELLOW,YELLOW);
        printf(" ");
        set_text_color(BLACK,selected==4 ? CYAN : WHITE);
        printf("                 ");
        set_text_color(YELLOW,YELLOW);
        printf(" ");
        set_text_color(BLACK,selected==5 ? CYAN : WHITE);
        printf("                 ");
        set_text_color(YELLOW,YELLOW);
        printf(" ");
        set_text_color(BLACK,selected==6 ? CYAN : WHITE);
        printf("                ");
        set_text_color(YELLOW,YELLOW);
        printf(" ");

        setCursor_inc(x,y++);
        set_text_color(YELLOW,YELLOW);
        printf(" ");
        set_text_color(BLACK,selected==4 ? CYAN : WHITE);
        printf("        4        ");
        set_text_color(YELLOW,YELLOW);
        printf(" ");
        set_text_color(BLACK,selected==5 ? CYAN : WHITE);
        printf("        5        ");
        set_text_color(YELLOW,YELLOW);
        printf(" ");
        set_text_color(BLACK,selected==6 ? CYAN : WHITE);
        printf("        6       ");
        set_text_color(YELLOW,YELLOW);
        printf(" ");

        setCursor_inc(x,y++);
        printf(" ");
        set_text_color(YELLOW,selected==4 ? CYAN : WHITE);
        printf("_________________");
        set_text_color(YELLOW,YELLOW);
        printf(" ");
        set_text_color(YELLOW,selected==5 ? CYAN : WHITE);
        printf("_________________");
        set_text_color(YELLOW,YELLOW);
        printf(" ");
        set_text_color(YELLOW,selected==6 ? CYAN : WHITE);
        printf("________________");
        
        set_text_color(YELLOW,YELLOW);
        setCursor_inc(x,y++);
        printf(" ");
        set_text_color(BLACK,selected==1 ? CYAN : WHITE);
        printf("                 ");
        set_text_color(YELLOW,YELLOW);
        printf(" ");
        set_text_color(BLACK,selected==2 ? CYAN : WHITE);
        printf("                 ");
        set_text_color(YELLOW,YELLOW);
        printf(" ");
        set_text_color(BLACK,selected==3 ? CYAN : WHITE);
        printf("                ");
        set_text_color(YELLOW,YELLOW);
        printf(" ");
        setCursor_inc(x,y++);
        set_text_color(YELLOW,YELLOW);
        printf(" ");
        set_text_color(BLACK,selected==1 ? CYAN : WHITE);
        printf("        1        ");
        set_text_color(YELLOW,YELLOW);
        printf(" ");
        set_text_color(BLACK,selected==2 ? CYAN : WHITE);
        printf("        2        ");
        set_text_color(YELLOW,YELLOW);
        printf(" ");
        set_text_color(BLACK,selected==3 ? CYAN : WHITE);
        printf("        3       ");
        set_text_color(YELLOW,YELLOW);
        printf(" ");

        setCursor_inc(x,y++);
        printf(" ");
        set_text_color(YELLOW,selected==1 ? CYAN : WHITE);
        printf("_________________");
        set_text_color(YELLOW,YELLOW);
        printf(" ");
        set_text_color(YELLOW,selected==2 ? CYAN : WHITE);
        printf("_________________");
        set_text_color(YELLOW,YELLOW);
        printf(" ");
        set_text_color(YELLOW,selected==3 ? CYAN : WHITE);
        printf("________________");
        set_text_color(YELLOW,YELLOW);
        printf(" ");

        setCursor_inc(x,y++);
        set_text_color(YELLOW,YELLOW);
        printf(" ");
        set_text_color(WHITE, WHITE);
        printf("                 ");
        set_text_color(YELLOW,YELLOW);
        printf(" ");
        set_text_color(YELLOW,selected==0 ? CYAN : WHITE);
        printf("                 ");
        set_text_color(YELLOW,YELLOW);
        printf(" ");
        set_text_color(WHITE,WHITE);
        printf("                ");
        set_text_color(YELLOW,YELLOW);
        printf(" ");

        setCursor_inc(x,y++);
        printf(" ");
        set_text_color(WHITE, WHITE);
        printf("                 ");
        set_text_color(YELLOW,YELLOW);
        printf(" ");
        set_text_color(YELLOW,selected==0 ? CYAN : WHITE);
        printf("                 ");
        set_text_color(YELLOW,YELLOW);
        printf(" ");
        set_text_color(WHITE,WHITE);
        printf("                ");
        set_text_color(YELLOW,YELLOW);
        printf(" ");


        setCursor_inc(x,y++);
        set_text_color(YELLOW,YELLOW);
        printf(" ");
        set_text_color(WHITE,WHITE);
        printf("                 ");
        set_text_color(YELLOW,YELLOW);
        printf(" ");
        set_text_color(BLACK,selected==0 ? CYAN : WHITE);
        printf("        0        ");
        set_text_color(YELLOW,YELLOW);
        printf(" ");
        set_text_color(WHITE,WHITE);
        printf("                ");
        set_text_color(YELLOW,YELLOW);
        printf(" ");
        set_text_color(WHITE,WHITE);
        setCursor_inc(x,y++);
        set_text_color(YELLOW,YELLOW);
        printf(" ");
        set_text_color(YELLOW,WHITE);
        printf("_________________");
        set_text_color(YELLOW,YELLOW);
        printf(" ");
        set_text_color(YELLOW,selected==0 ? CYAN : WHITE);
        printf("_________________");
        set_text_color(YELLOW,YELLOW);
        printf(" ");
        set_text_color(YELLOW,WHITE);
        printf("________________");
        set_text_color(YELLOW,YELLOW);
        printf(" ");
        setCursor_inc(x,y++);
        set_text_color(BLACK,WHITE);

        
    }
    getchar();
    getchar();
    
    return 0;
}

void loadingbarpayment(){
    int x=90,y=18;
    for (int i = 0; i < 54; i++)
    {
        setCursor_inc(x+i,y);
        set_text_color(BLUE,BLUE);
        printf("=");
        Sleep(50);
    }
    
}

void success_popup(){
    int x=101,y=29;
    loadingbarpayment();
    setCursor_inc(x,y++);
    set_text_color(BLACK,GREEN);
    printf("                               ");
    setCursor_inc(x,y++);
    printf("       PAYMENT SUCCESSFUL      ");
    setCursor_inc(x,y++);
    printf("                               ");
}

int payment() {
    int payment_status;
    int choice;

    simulate_payment();
    success_popup();
    getchar();
    

    return 1;
}
