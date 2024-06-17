#include <stdio.h>
#include <stdbool.h>
#include <Windows.h>
#include "illustrations.h"
#include "login.h"
#include "theme.h"
#include "profile.h"
#include "food_order_page.h"
#include "notification.h"
#include "favourites.h"
#include "history.h"


void profile_page_banner(){
    int x=30,y=0;
    system("cls");
    home();
    printUserDetails();
    side_menu(false);
    setCursor_inc(x,y++);
    set_text_color(WHITE,YELLOW);
    printf("                                                                                                                                                            ");
    setCursor_inc(x,y++);
    printf("                                                                                                                                                            ");
    setCursor_inc(x,y++);
    printf("                                                                                                                                                            ");
    setCursor_inc(x,y++);
    printf("                                                                                                                                                            ");
    setCursor_inc(x,y++);
    printf("                                                                                                                                                            ");
    setCursor_inc(x,y++);
    printf("                                                                                                                                                            ");
    setCursor_inc(x,y++);
    printf("                                                                                                                                                            ");
    setCursor_inc(x,y++);
    printf("                                                                                                                                                            ");
    setCursor_inc(x,y++);
    printf("                                                                                                                                                            ");
    setCursor_inc(x,y++);
    printf("                                                                                                                                                            ");
    setCursor_inc(x,y++);
    printf("                                                                                                                                                            ");
    setCursor_inc(x,y++);
    printf("                                                                                                                                                            ");
    setCursor_inc(x,y++);
    printf("                                                                                                                                                            ");
    setCursor_inc(x,y++);
    printf("                                                                                                                                                            ");
    setCursor_inc(x,y++);
    printf("                                                                                                                                                            ");
    setCursor_inc(x,y++);
    printf("                                                                                                                                                            ");
    setCursor_inc(x,y++);
    printf("                                                                                                                                                            ");
    set_text_color(BLACK,BLACK);
}

void profile_detail_div(){
    readCurrentUser();
    int x=60,y=12;
    setCursor_inc(x,y++);
    set_text_color(BLACK,WHITE);
    printf("                                                                                                       ");
    setCursor_inc(x,y++);
    printf("                                                                                                       ");
    setCursor_inc(x,y++);
    printf("      Username:                         %-20s                                           ",current_user_details.username);
    setCursor_inc(x,y++);
    printf("                                                                                                       ");
    setCursor_inc(x,y++);
    printf("      Password                          %-20s                                           ",current_user_details.password);
    setCursor_inc(x,y++);
    printf("                                                                                                       ");
    setCursor_inc(x,y++);
    printf("      Email:                            %-20s                                           ",current_user_details.email);
    setCursor_inc(x,y++);
    printf("                                                                                                       ");
    setCursor_inc(x,y++);
    printf("      Phone no:                         %-20s                                           ",current_user_details.phone_no);
    setCursor_inc(x,y++);
    printf("                                                                                                       ");
    setCursor_inc(x,y++);
    set_text_color(WHITE,YELLOW);
    printf("      ");
    set_text_color(WHITE,GREEN);
    printf("                   ");
    set_text_color(WHITE,YELLOW);
    printf("      ");
    printf("                                                                        ");
    set_text_color(WHITE,YELLOW);
    setCursor_inc(x,y++);
    printf("      ");
    set_text_color(WHITE,GREEN);
    printf("   Edit profile    ");
    set_text_color(WHITE,YELLOW);
    printf("      ");
    printf("                                                                        ");
    set_text_color(WHITE,YELLOW);
    setCursor_inc(x,y++);
    printf("      ");
    set_text_color(WHITE,GREEN);
    printf("                   ");
    set_text_color(WHITE,YELLOW);
    printf("      ");
    printf("                                                                        ");
    set_text_color(WHITE,YELLOW);
    setCursor_inc(x,y++);
    printf("                                                                                                       ");
    setCursor_inc(x,y++);
    printf("                                                                                                       ");
    setCursor_inc(x,y++);

    set_text_color(BLACK,BLACK);
}

int edit_profile()
{   
    printf("What would you like to edit?\n");
    printf("1. Password\n");
    printf("2. Email\n");
    printf("3. Phone number\n");
    printf("4. back\n");
    printf("Enter your choice (1-4): ");

    int choice;
    char new_value[100]; // Buffer for new input

    scanf("%d", &choice);
    char email[100], password[20],phone[20];
    readUsersFromFile();
    readCurrentUser();
    FILE *file = fopen("users.txt", "r+");
    if (file == NULL) {
        print_error("Error opening file!\n");
        return 0;
    }
    for (int i = 0; i < num_users; i++) {
        if (strcmp(Users[i].username, current_user_details.username) == 0) {
            switch (choice) {
                case 1:
                    printf("Enter new password: ");
                    scanf("%s", new_value);
                    strcpy(Users[i].password, new_value);
                    break;
                case 2:
                    printf("Enter new email: ");
                    scanf("%s", new_value);
                    strcpy(Users[i].email, new_value);
                    break;
                case 3:
                    printf("Enter new phone number: ");
                    scanf("%s", new_value);
                    strcpy(Users[i].phone_no, new_value);
                    break;
                case 4:
                    return 1;
                    break;
                default:
                    print_error("Invalid choice.\n");
                    break;
            }
            // Write updated user information to file
            fprintf(file, "%s %s %s %s\n", Users[i].username, Users[i].password, Users[i].email, Users[i].phone_no);
            writeCurrentUser();
            // switch (choice) {
            //     case 1:
            //         add_notification("You have changed your password successfully");
            //         break;
            //     case 2:
            //         add_notification("You have changed your email successfully");
            //         break;
            //     case 3:
            //         add_notification("You have changed your phone number successfully");
            //         break;
            //     default:
            //         break;
            // }
            fclose(file);
            break;
        } else {
            // Write existing user information to file
            fprintf(file, "%s %s %s %s\n", Users[i].username, Users[i].password, Users[i].email, Users[i].phone_no);
        }
    }
    return 1;
}

int profile_options(){
    while (1)
    {
        printf("1. Edit profile\n");
        printf("2. Favourites\n");
        printf("3. notifications\n");
        printf("4. comments\n");
        printf("5. Ratings\n");
        printf("6. Statistics\n");
        printf("7. History\n");
        printf("8. back\n");
        printf("Enter your choice (1-8): ");
        getchar(); // Consume newline character left in the buffer

        int choice;
        scanf("%d", &choice);
        switch (choice) {
        
        case 1: 
            edit_profile();
            break;
        case 2: 
            system("cls");
            home();
            printUserDetails();
            home_page_banner();
            view_favourites();
            getchar();
            break;
        case 3: 
            system("cls");
            top_bar();
            view_notifications();
            getchar();
            getchar();
            break;
        case 4: 
            
            break;
        case 5: 
            
            break;
        case 6: 
            
            break;
        case 7: 
            calender();
            break;
        case 8: 
            return 1;
            break;
        default:
            break;
        
    }
    

    }
}
void display_user_profile() {
    // profile_page_banner();
    profile_detail_div();
    

    profile_options();
    

}

