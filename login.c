#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include "textField.h"
#include "partner_path.h"
#include "delivery_boy_selection.h"
#include "map.h"
#include <stdbool.h>
#include "add_cart.h"
#include <ctype.h>
#include "buttonCreator.h"
#include "theme.h"
#include "delivery_boy_selection.h"
#include "illustrations.h"
#include "login.h"
#include <windows.h>
#include "food_order_page.h"
#include "food_items.h"
#include "settings.h"
#include "profile.h"
#include "sounds.h"
#include "restaurants_home.h"
#include "snake_ladder_game.h"
#include "snake_game.h"
#include "cricket_game.h"
#include "notification.h"
#include "favourites.h"

UserDeliveryInfo user_delivery_info;
char current_user[USERNAME_MAX_LEN]="None";
User current_user_details;
User Users[MAX_USERS];
int num_users;
char current_restaurant_name[100];


void home_page_banner(){
    int x = 30, y =0;
    setCursor_inc(x , y++);
    set_text_color(WHITE,YELLOW);
    printf("                                                                                                                                                               ");
    set_text_color(WHITE,RED);
    printf("                           ");
    set_text_color(WHITE,YELLOW);
    setCursor_inc(x , y++);
    printf("                                                                                                                                                           ");
    set_text_color(WHITE,RED);
    printf("                              ");
    set_text_color(WHITE,YELLOW);
    setCursor_inc(x , y++);
    printf("                                                                                                                                                       ");
    set_text_color(WHITE,RED);
    printf("                                 ");
    set_text_color(WHITE,YELLOW);
    set_text_color(RED,YELLOW);
    setCursor_inc(x , y++);
    printf("    F O O D  Y O U  L O V E.                                                                                                                     ");
    set_text_color(WHITE,RED);
    printf("                                      ");
    set_text_color(WHITE,YELLOW);
    setCursor_inc(x , y++);
    set_text_color(WHITE,YELLOW);
    printf("                                                                                                                                             ");
    set_text_color(WHITE,RED);
    printf("                                            ");
    set_text_color(WHITE,YELLOW);
    setCursor_inc(x , y++);
    printf("    D E L I V E R E D  T O  Y O U                                                                                                      ");
    set_text_color(WHITE,RED);
    printf("                                                           ");
    set_text_color(WHITE,YELLOW);
    setCursor_inc(x , y++);
    printf("                                                                                                                                     ");
    set_text_color(WHITE,RED);
    printf("                                                ");
    set_text_color(WHITE,YELLOW);
    setCursor_inc(x , y++);
    printf("                                                                                                                                 ");
    set_text_color(WHITE,RED);
    printf("                                                        ");
    set_text_color(WHITE,YELLOW);
    setCursor_inc(x , y++);
    printf("    G E T  Y O U R                                                                                                          ");
    set_text_color(WHITE,RED);
    printf("                                                           ");
    set_text_color(WHITE,YELLOW);
    setCursor_inc(x , y++);
    set_text_color(RED,YELLOW);
    printf("    D E S I R E  F O O D            ");                          
    set_text_color(BLACK,WHITE);
    printf(" O R D E R  N O W ");
    set_text_color(WHITE,YELLOW);
    printf("                                                                  ");
    set_text_color(WHITE,RED);
    printf("                                                                 ");
    setCursor_inc(x , y++);
    set_text_color(WHITE,YELLOW);
    printf("    I N  3 0  M I N U T E S                                                                                         ");
    set_text_color(WHITE,RED);
    printf("                                                                   ");
    set_text_color(WHITE,YELLOW);
    setCursor_inc(x , y++);
    printf("                                                                                                                 ");
    set_text_color(WHITE,RED);
    printf("                                                                        ");
    set_text_color(WHITE,YELLOW);
    setCursor_inc(x , y++);
    printf("                                                                                                             ");
    set_text_color(WHITE,RED);
    printf("                                                                          ");
    set_text_color(WHITE,YELLOW);
    setCursor_inc(x , y++);
    printf("                                                                                                         ");
    set_text_color(WHITE,RED);
    printf("                                                                              ");
    set_text_color(WHITE,YELLOW);
    setCursor_inc(x , y++);
    printf("                                                                                                     ");
    set_text_color(WHITE,RED);
    printf("                                                                                  ");
    set_text_color(WHITE,WHITE);
}

void print_category(char *category, int n,bool selected){
    int y,x;
    if (n<14)
    {
        y = 18;
        x = (n-1) * 13 + 43;
    }else{
        y = 20;
        x = (n-15) * 13 + 43;
    }
    

    setCursor_inc(x,y);
    set_text_color(WHITE,selected ? YELLOW : RED );
    y++;
    printf(" %s ",category);

}

void category_list(int focus){
    bool selected;
    char category[28][16] = {
        "INDIAN",
        "CHINESE",
        "TAMILNADU",
        "FASTFOOD",
        "SEAFOOD",
        "BREAKFAST",
        "MEDITERRANEAN",
        "VIETNAMESE",
        "ITALIAN",
        "MEXICAN",
        "THAI",
        "JAPANESE",
        "CARIBBEAN",
        "GREEK",
        "FRENCH",
        "SPANISH",
        "MIDDLE EASTERN",
        "KOREAN",
        "TURKISH",
        "AUSTRALIAN",
        "ETHIOPIAN",
        "MOROCCAN",
        "NORTH_INDIAN",
        "SOUTH_INDIAN",
        "BEVERAGES",
        "BREAKFAST",
        "SNACKS",
        "AMERICAN"
    };
    setCursor_inc(90,16);
    set_text_color(BLACK,WHITE);
    printf("M E N U  C A T E G O R I E S");
    for (int i = 0; i < 28; i++)
    {
        if (i==focus)
        {
            selected = true;
        }else{
            selected = false;
        }
        
        print_category(category[i],i,selected);
    }
    
}

bool isPhoneNumberValid(const char *phoneNumber) {
    int len = strlen(phoneNumber);
    
    // Check if the length is valid
    if (len != 10)
        return false;
    
    // Check if all characters are digits
    for (int i = 0; i < len; i++) {
        if (!isdigit(phoneNumber[i]))
            return false;
    }
    
    return true;
}

bool isEmailValid(const char *email) {
    int len = strlen(email);
    int atCount = 0;
    int dotCount = 0;
    
    // Check if the first character is a letter
    if (!isalpha(email[0]))
        return false;
    
    for (int i = 0; i < len; i++) {
        if (email[i] == '@') {
            atCount++;
            if (i == 0 || i == len - 1) // '@' should not be first or last character
                return false;
        } else if (email[i] == '.') {
            dotCount++;
            if (i == 0 || i == len - 1 || email[i + 1] == '.') // '.' should not be first, last, or repeat consecutively
                return false;
        } else if (!(isalnum(email[i]) || email[i] == '_' || email[i] == '-')) {
            return false; // invalid character
        }
    }
    
    if (atCount != 1 || dotCount < 1)
        return false; // must have exactly one '@' and at least one '.'
    
    return true;
}


void side_menu(int selectedOption){

        int x = 0, y=15;

        set_text_color(BLACK,BLACK);  
        if (selectedOption == 0)
        {
            set_text_color(WHITE,BLUE);  
        }
        
        setCursor_inc(x,y);
        y+=1;
        printf("                           ");
        setCursor_inc(x,y);
        y+=1;
        printf("          HOME             ");
        setCursor_inc(x,y);
        y+=1;
        printf("                           ");




        set_text_color(BLACK,BLACK);
        if (selectedOption == 1)
        {
            set_text_color(WHITE,BLUE);    
        }
        setCursor_inc(x,y);
        y+=1;
        printf("                           ");
        setCursor_inc(x,y);
        y+=1;
        printf("         PROFILE           ");
        setCursor_inc(x,y);
        y+=1;
        printf("                           ");
        setCursor_inc(x,y);
        y+=1;
       

        set_text_color(BLACK,BLACK);
        if (selectedOption == 2)
        {
            set_text_color(WHITE,BLUE);    
        }
        printf("                           ");
        setCursor_inc(x,y);
        y+=1;
        printf("          HISTORY          ");
        setCursor_inc(x,y);
        y+=1;
        printf("                           ");
        setCursor_inc(x,y);
        y+=1;
       


        set_text_color(BLACK,BLACK);
        if (selectedOption == 3)
        {
            set_text_color(WHITE,BLUE);    
        }
        printf("                           ");
        setCursor_inc(x,y);
        y+=1;
        printf("         SETTINGS          ");
        setCursor_inc(x,y);
        y+=1;
        printf("                           ");
        setCursor_inc(x,y);
        y+=1;
       


        set_text_color(BLACK,BLACK);
        if (selectedOption == 4)
        {
            set_text_color(WHITE,BLUE);    
        }
        printf("                           ");
        setCursor_inc(x,y);
        y+=1;
        printf("          LOGOUT           ");
        setCursor_inc(x,y);
        y+=1;
        printf("                           ");


        set_text_color(BLACK,BLACK);
        if (selectedOption == 5)
        {
            set_text_color(WHITE,BLUE);
        }
        setCursor_inc(x,y);
        y+=1;
        printf("                           ");
        setCursor_inc(x,y);
        y+=1;
        printf("      VIEW RESTAURANT      ");
        setCursor_inc(x,y);
        y+=1;
        printf("                           ");

        set_text_color(BLACK,BLACK);
        if (selectedOption == 6)
        {
            set_text_color(WHITE,BLUE);
        }
        setCursor_inc(x,y);
        y+=1;
        printf("                           ");
        setCursor_inc(x,y);
        y+=1;
        printf("         PLAY GAMES        ");
        setCursor_inc(x,y);
        y+=1;
        printf("                           ");
      
      
        set_text_color(BLACK,BLACK);
        if (selectedOption == 7)
        {
            set_text_color(WHITE,BLUE);
        }
        setCursor_inc(x,y);
        y+=1;
        printf("                           ");
        setCursor_inc(x,y);
        y+=1;
        printf("            CART           ");
        setCursor_inc(x,y);
        y+=1;
        printf("                           ");
        
        
        set_text_color(BLACK,BLACK);
        if (selectedOption == 8)
        {
            set_text_color(WHITE,BLUE);
        }
        setCursor_inc(x,y);
        y+=1;
        printf("                           ");
        setCursor_inc(x,y);
        y+=1;
        printf("            SEARCH         ");
        setCursor_inc(x,y);
        y+=1;
        printf("                           ");
        
        set_text_color(BLACK,BLACK);
        if (selectedOption == 9)
        {
            set_text_color(WHITE,BLUE);
        }
        setCursor_inc(x,y);
        y+=1;
        printf("                           ");
        setCursor_inc(x,y);
        y+=1;
        printf("     NEARBY RESTAURANTS    ");
        setCursor_inc(x,y);
        y+=1;
        printf("                           ");

        setCursor_inc(x,y);
        set_text_color(BLACK,BLACK);
        y+=1;
        printf("                           ");
        setCursor_inc(x,y);
        y+=1;
        printf("                           ");
        setCursor_inc(x,y);
        y+=1;
        printf("                           ");
        setCursor_inc(x,y);
        y+=1;
        printf("                           ");
        setCursor_inc(x,y);
        y+=1;
        printf("                           ");
        set_theme();
    
}

int menu_navigator(){
    int num_options = 11;
    int selectedOption = 0;
    char side_menu_options[12][20] = 
    {
        "home", "profile", "history", "settings", "logout","view restaurants","play games","cart","search","nearby_restaurants"
    };
    char ch;
    bool exit = false;
    int x = 0, y=5;
    while (1)
    {
       
                ch = _getch();
                select_beep();

                switch (ch)
                {
                case 72:
                    if(selectedOption > 0) selectedOption--;
                    break;
                
                case 80:
                    if(selectedOption < num_options-1) selectedOption++;
                    break;
                
                // case 13:
                //     printf(" \nSelected: %s\n", side_menu_options[selectedOption]);
                //     break;

                case '\t':
                    return -1;
                    break;
                case 13:
                    return selectedOption; 
                    break;
                default:
                    break;
                }

                side_menu(selectedOption);

            
    }
    
}


void find_user_details(User Users[],const char *target_username,User *destination){
    for (int i = 0; i < num_users; i++) {
        if (strcmp(Users[i].username, target_username) == 0) {
            destination[i]=Users[i];
        }
    }
}
int play_games(){
        
        int x=80,y=20;
        setCursor_inc(x,y++);
        set_text_color(BLACK,GREEN);
        printf("                            \n");
        setCursor_inc(x,y++);
        printf("1.    Cricket               \n");
        setCursor_inc(x,y++);
        printf("2.    Snake and Ladder      \n");
        setCursor_inc(x,y++);
        printf("3.    Snake                 \n");
        setCursor_inc(x,y++);
        printf("4.    Exit                  \n");
        setCursor_inc(x,y++);
        printf("                            \n");
        int choice;
        setCursor_inc(x,y++);
        printf("      Enter your choice:   \n");
        scanf("%d",&choice);
        set_text_color(BLACK,WHITE);
        if(choice==1){
            cricket_game();
            return 1;
        }
        else if(choice==2){
            snake_ladder_game();
            return 1;
        }
        else if(choice==3){
            snake_game();
            return 1;
        }
        else if(choice==4){
            return 0;
        }else{
            print_error("Invalid choice");
            return -1;
        }
    
}
void printUserDetails(){
    set_text_color(WHITE,RED);
    printf("USERNAME:%-18s\n",current_user_details.username);
    printf("EMAIL:%-21s\n",current_user_details.email);
    set_text_color(BLACK,BLACK);
}

void top_bar(){
    home();
    printUserDetails();
    side_menu(false);
    home_page_banner();
    category_list(-1);
    displayPopularItems(menu);
    if(readRestaurants()){
        print_restaurants();
    }
}
int writeCurrentUser(User current_user_details) {
    // printf("writing current user\n");
    FILE *file = fopen("current_user.txt", "w");
    if (file == NULL) {
        print_error("Error opening file 'current_user.txt' for writing");
        return 0;
    }
    fprintf(file, "%s %s %s %s %d", current_user_details.username, current_user_details.password, current_user_details.email, current_user_details.phone_no, current_user_details.isveg);
    
    fclose(file);
}


int readCurrentUser(){
    FILE *file=fopen("current_user.txt","r");
    if (file == NULL) {
        print_error("Error opening file 'current_user.txt' for reading");
        return 0;
    }
    if (fscanf(file,"%s %s %s %s %d",current_user_details.username,current_user_details.password,current_user_details.email,current_user_details.phone_no,&current_user_details.isveg) != 5) {
        print_error("Error reading from file 'current_user.txt'");
        getchar();
        fclose(file);
        return 0;
    }    
    strcpy(current_user,current_user_details.username);
    fclose(file);
    return 1;
}

int readUsersFromFile() {

    FILE *file = fopen("users.txt", "r");
    if (file == NULL) {
        print_error("Error opening file.\n");
        return 0;
    }

    num_users = 0;
    while (fscanf(file, "%s %s %s %s %d", Users[num_users].username, Users[num_users].password, Users[num_users].email, Users[num_users].phone_no, &Users[num_users].isveg) == 5 && num_users < MAX_USERS) {
        // printf("%s %s %s %s %d\n",Users[num_users].username, Users[num_users].password, Users[num_users].email, Users[num_users].phone_no, Users[num_users].isveg);
        // getchar();
        num_users++;
    }

    fclose(file);
    return 1;
}


void writeUsersToFile(User user)
{
    FILE *file = fopen("delivery_boys_details.txt", "a");
    if (file == NULL)
    {
        print_error("Error opening file.\n");
        return;
    }
    fprintf(file, "%s %s %s %s %d\n", user.username, user.password, user.email, user.phone_no, 0);

    fclose(file);
}

int hasAlphabet(char *password)
{
    for (int i = 0; password[i] != '\0'; i++)
    {
        if (isalpha(password[i]))
        {
            return 1;
        }
    }
    return 0;
}

int hasNumber(char *password)
{
    for (int i = 0; password[i] != '\0'; i++)
    {
        if (isdigit(password[i]))
        {
            return 1;
        }
    }
    return 0;
}

int hasPunctuation(char *password)
{
    for (int i = 0; password[i] != '\0'; i++)
    {
        if (!isalnum(password[i]))
        {
            return 1;
        }
    }
    return 0;
}

int authenticate(char *password)
{
    if (strlen(password) < 8)
    {
        print_error("the length of the password must be greater than 8");
        return 0; // Password is too short
    }

    if (!hasAlphabet(password) || !hasNumber(password) || !hasPunctuation(password))
    {
        print_error("Passwords must contain at least 1 alphabet numeric character special character");
        return 0; // Password does not meet complexity requirements
    }

    // Authentication successful
    return 1;
}


int isUsernameExists(char *username)
{
    set_text_color(MAGENTA,GREEN);
    for (int i = 0; i < num_users; i++)
    {
        if (strcmp(Users[i].username, username) == 0 && username[0] != '\0')
        {
            return 1; // Username already exists
        }
    }
    return 0; 
}// Username does not exist
void removeLastChar(char *str) {
    if (str[0] == '\0') return;
    int len = strlen(str);
    str[len - 1] = '\0';
}

void signup_side_page(bool focus){
    int x = 117, y = 20;
    setCursor_inc(x,y++);
    set_text_color(WHITE,YELLOW);
    printf("                                              ");
    setCursor_inc(x,y++);
    printf("                                              ");
    setCursor_inc(x,y++);
    printf("                                              ");
    setCursor_inc(x,y++);
    printf("                                              ");
    setCursor_inc(x,y++);
    printf("                                              ");
    setCursor_inc(x,y++);
    printf("           %-15s         ","H E L L O  F R I E N D !  ");
    setCursor_inc(x,y++);
    printf("                                              ");
    setCursor_inc(x,y++);
    printf("                                              ");
    setCursor_inc(x,y++);
    printf("         %-20s         ","Enter you personal details  ");
    setCursor_inc(x,y++);
    printf("        %-17s      ","and start your journey with us  ");
    setCursor_inc(x,y++);
    printf("                                              ");
    setCursor_inc(x,y++);

    printf("                 ");
    set_text_color(WHITE,focus ? BLUE : YELLOW);
    printf("%-10s ","L O G I N");
    set_text_color(WHITE,YELLOW);
    printf("                   ");
    setCursor_inc(x,y++);
    printf("                                              ");
    setCursor_inc(x,y++);
    printf("                                              ");
    setCursor_inc(x,y++);
    printf("                                              ");

    
}
void login_side_page(bool focus){
    int x = 80, y = 20;
    setCursor_inc(x,y++);
    set_text_color(WHITE,YELLOW);
    printf("                                            ");
    setCursor_inc(x,y++);
    printf("                                            ");
    setCursor_inc(x,y++);
    printf("                                            ");
    setCursor_inc(x,y++);
    printf("                                            ");
    setCursor_inc(x,y++);
    printf("                                            ");
    setCursor_inc(x,y++);
    printf("           %-20s         ","W E L C O M E  B A C K !");
    setCursor_inc(x,y++);
    printf("                                            ");
    setCursor_inc(x,y++);
    printf("                                            ");
    setCursor_inc(x,y++);
    printf("        %-20s    ","To keep connected with us please");
    setCursor_inc(x,y++);
    printf("           %-20s      ","enter your personal details");
    setCursor_inc(x,y++);
    printf("                                            ");
    setCursor_inc(x,y++);
    printf("                ");
    set_text_color(WHITE,focus ? BLUE : YELLOW);
    printf(" %-12s","S I G N U P");
    set_text_color(WHITE,YELLOW);
    printf("               ");
    setCursor_inc(x,y++);
    printf("                                            ");
    setCursor_inc(x,y++);
    printf("                                            ");
    setCursor_inc(x,y++);
    printf("                                            ");

}
int registerUser()
{
    readUsersFromFile();
    int currentField = 0;
    bool success = false;
    char username[USERNAME_MAX_LEN]="";
    char password[PASSWORD_MAX_LEN]="";
    char email[EMAIL_MAX_LEN] = "";
    char phone[PHONE_NO_MAX_LEN] = "";
    User user;
    int focusSide = 0; // 0 for main form, 1 for side page (signup)

    while (!success) {
        // system("cls");
        int x = 80, y = 20;
        // Print sign-up form
        setCursor_inc(x, y++);
        set_text_color(WHITE,YELLOW);
        printf("            S I G N   U P            ");
        setCursor_inc(x, y++);
        printf("                                     ");
        setCursor_inc(x, y);
        y++;
        set_text_color(BLACK,YELLOW);
        printf("Username                             ");

        setCursor_inc(x, y++);
        set_text_color(DARK_GRAY,WHITE);
        if (currentField == 0)
        {
            set_text_color(WHITE,DARK_GRAY);
        }
        
         printf(" %-36s ", username);


        setCursor_inc(x, y++);
        set_text_color(BLACK,YELLOW);
        printf("Password                             ");

        setCursor_inc(x, y++);
        set_text_color(DARK_GRAY,WHITE);
        if (currentField == 1) 
        {
            set_text_color(WHITE,DARK_GRAY);
            
        }
        printf(" %-36s ", password);
        setCursor_inc(x, y++);


        set_text_color(BLACK,YELLOW);
        printf("Email                                ");

        setCursor_inc(x, y++);
        set_text_color(DARK_GRAY,WHITE);
        if (currentField == 2) 
        {
            set_text_color(WHITE,DARK_GRAY);
            
        }
        printf(" %-36s ", email);
        setCursor_inc(x, y++);

        set_text_color(BLACK,YELLOW);
        printf("Phone Number                         ");

        setCursor_inc(x, y++);
        set_text_color(DARK_GRAY,WHITE);
        if (currentField == 3) 
        {
            set_text_color(WHITE,DARK_GRAY);
            
        }
        printf(" %-36s ", phone);
        setCursor_inc(x, y++);


        set_text_color(WHITE,DARK_BLUE);
        if (currentField == 4)
        {
            set_text_color(WHITE,BLUE);
        }
        
        printf("                                     ");
        setCursor_inc(x, y++);
        printf("            S I G N   U P            ");
        setCursor_inc(x, y++);
        printf("                                     ");
        setCursor_inc(x, y++);
        set_text_color(WHITE,YELLOW);
        printf("                                     ");
        setCursor_inc(x, y++);
        set_text_color(WHITE,YELLOW);
        printf("                                     ");
        if (focusSide == 1)
        {
            signup_side_page(true);
        }else{
            signup_side_page(false);
        }
        
        set_text_color(BLACK,WHITE);

        char ch = _getch();

        // Move between fields and button using arrow keys
        switch(ch) {
            case 75: // Left arrow
                if (focusSide > 0) focusSide--;
                    currentField = 0;
                break;
            case 77: // Right arrow
                if (focusSide < 1) focusSide++;
                    currentField = -1;
                break;
            case '\t':
                return 1;
            case 72: // Up arrow
                if (currentField > 0 && focusSide == 0) currentField--;
                break;
            case 80: // Down arrow
                if (currentField < 4 && focusSide == 0) currentField++;
                break;
            case 13: // Enter key
                if (focusSide == 1) 
                {
                    return 0;
                }
                
                
                
                if(!isUsernameExists(username) && authenticate(password) && currentField == 4 && isPhoneNumberValid(phone) && isEmailValid(email)){
                        setCursor_inc(80,33);
                        set_text_color(WHITE,YELLOW);
                        print_success("   Signing up...\n");
                        setCursor_inc(80,34);
                        set_text_color(WHITE,BLUE);
                        for (int i = 0; i < 37; i++)
                        {
                            printf("=");
                            Sleep(200);
                        }
                        setCursor_inc(80,34);
                        set_text_color(WHITE,YELLOW);
                        print_success("Sign-up successful!\n");
                        strcpy(user.email, email);
                        strcpy(user.username, username);
                        strcpy(user.password,  password);
                        strcpy(user.phone_no, phone);
                        num_users++;
                        writeUsersToFile(user);
                        success = true;
                }
                if (currentField == 4)
                {

                    if (isUsernameExists(username))
                    {
                        setCursor_inc(80,33);
                        print_error("Username already exists");
                        continue;
                    }
                    if (!authenticate(password))
                    {
                        setCursor_inc(80,33);
                        print_error("Password is not strong");
                        continue;
                    }
                    if (!isPhoneNumberValid(phone))
                    {
                        setCursor_inc(80,33);
                        print_error("Invalid phone number");
                        continue;
                    }
                    if (!isEmailValid(email))
                    {
                        setCursor_inc(80,33);
                        print_error("Invalid email");
                        break;
                    }
                    
                }
                break;
            case '\b':
                if (currentField == 0 && strlen(username) > 0) {
                    removeLastChar(username);
                } else if (currentField == 1 && strlen(password) > 0) {
                    removeLastChar(password);
                } else if (currentField == 2 && strlen(email) > 0) {
                    removeLastChar(email);
                }
                 else if (currentField == 3 && strlen(password) > 0) {
                    removeLastChar(phone);
                }
            default:
                // Capture username, password, or email characters
                if (currentField == 0 && strlen(username) < USERNAME_MAX_LEN) {
                    if (isalnum(ch) != 0 || ispunct(ch) != 0)
                    {
                            strncat(username, &ch, 1);                        
                    }
                    
                } else if (currentField == 1 && strlen(password) < PASSWORD_MAX_LEN) {
                    if (isalnum(ch) != 0 || ispunct(ch) != 0)
                    {
                            strncat(password, &ch, 1);
                    }
                } else if (currentField == 2 && strlen(email) < EMAIL_MAX_LEN) {
                    if (isalnum(ch) != 0 || ispunct(ch) != 0)
                    {
                            strncat(email, &ch, 1);
                    }
                }
                else if (currentField == 3 && strlen(phone) < PHONE_NO_MAX_LEN) {
                    if (isalnum(ch) != 0 || ispunct(ch) != 0)
                    {
                            strncat(phone, &ch, 1);
                    }
                }
                break;
        }
    }
    return 0;
}

int loginUser()
{
    // home();
    // side_menu(false);
    // home_page_banner();
    readUsersFromFile();
    int currentField = 0;
    bool success = false;
    int x,y;
    char username[USERNAME_MAX_LEN]="";
    char password[PASSWORD_MAX_LEN]="";
    int focusSide = 1; // 0 for main form, 1 for side page (signup)

    while(!success){

        int x = 124, y = 20;

        setCursor_inc(x, y++);
        set_text_color(WHITE,YELLOW);
        printf("               L O G I N              ");
        setCursor_inc(x, y++);
        printf("                                      ");
        setCursor_inc(x, y);
        y++;
        set_text_color(BLACK,YELLOW);
        printf("Username                              ");

        setCursor_inc(x, y++);
        set_text_color(DARK_GRAY,WHITE);
        if (currentField == 0) 
        {
            set_text_color(WHITE,DARK_GRAY);
        }
        
         printf(" %-36s ", username);
        
        setCursor_inc(x, y++);

        set_text_color(BLACK,YELLOW);
        printf("Password                              ");

        setCursor_inc(x, y++);
        set_text_color(DARK_GRAY,WHITE);
        if (currentField == 1)
        {
            set_text_color(WHITE,DARK_GRAY);
            
        }
        printf(" %-36s ", password);

        setCursor_inc(x, y++);
        set_text_color(WHITE,DARK_BLUE);
        if (currentField == 2)
        {
            set_text_color(WHITE,BLUE);
        }
        printf("                                      ");
        setCursor_inc(x, y++);
        printf("              L  O G I N              ");
        setCursor_inc(x, y++);
        printf("                                      ");
        setCursor_inc(x, y++);
        set_text_color(WHITE,YELLOW);
        printf("                                      ");
        setCursor_inc(x, y++);
        printf("                                      ");
        setCursor_inc(x, y++);
        printf("                                      ");
        setCursor_inc(x, y++);
        printf("                                      ");
        setCursor_inc(x, y++);
        printf("                                      ");
        setCursor_inc(x, y++);
        printf("                                      ");
        if (focusSide == 1)
        {
            login_side_page(false);
        }else{
            login_side_page(true);
        }
        
        
        char ch = _getch();

        // Move between fields and button using arrow keys
        switch(ch) {
            case 75: // Left arrow
                if (focusSide > 0) focusSide--;
                currentField = -1;
                break;
            case 77: // Right arrow
                if (focusSide < 1) focusSide++;
                currentField = 0;
                break;
            case '\t':
                return 0;
            case 72: // Up arrow
                if (currentField > 0 && focusSide ==1) currentField--;
                break;
            case 80: // Down arrow
                if (currentField < 2 && focusSide ==1) currentField++;
                break;
            case 13: // Enter key
                readUsersFromFile();
                if (focusSide == 0)
                {
                    return 0;
                }
                if (currentField == 2) {
                    // set_text_color(RED,GREEN);
                    // printf("==========%d==================",num_users);
                    for (int i = 0; i < num_users; i++)
                    {
                        // printf("%s == %s\n",Users[i].username,username);
                        // printf("%s == %s\n",Users[i].password,password);
                        // getchar();
                        if (strcmp(Users[i].username, username) == 0 && strcmp(Users[i].password, password) == 0 && username[0] != '\0')
                        {
                            strcpy(current_user,username);
                            setCursor_inc(52,90);
                            set_text_color(WHITE,YELLOW);
                            print_success("  Logging in...");
                            if(writeCurrentUser(current_user_details)==1){
                                set_text_color(WHITE,BLUE);
                                for (int i = 0; i < 37; i++)
                                {
                                    printf("=");
                                    Sleep(200);
                                }
                                setCursor_inc(52,91);
                                set_text_color(WHITE,YELLOW);
                                print_success("Login successful");
                                success = true;
                                return 1;
                            }else{
                                return 0;
                            }
                        }
                    }
                    print_error("Invalid username or password");
                }
                break;
            case '\b':
                if (currentField == 0 && strlen(username) > 0) {
                    removeLastChar(username);
                } else if (currentField == 1 && strlen(password) > 0) {
                    removeLastChar(password);
                }
            default:
                // Capture username or password characters
                if (currentField == 0 && strlen(username) < 20) {
                    if (isalnum(ch) != 0 || ispunct(ch) != 0)
                    {
                            strncat(username, &ch, 1);
                    }
                    
                } else if (currentField == 1 && strlen(password) < 20) {
                    if (isalnum(ch) != 0 || ispunct(ch) != 0)
                    {
                            strncat(password, &ch, 1);
                    }
                }
                break;
        }
    }

    return 1;
}
int UserTypeScreen(int ScreenState,int selected){
    int x = 80, y = 20;
    setCursor_inc(x, y++);
    set_text_color(BLACK,YELLOW);
    printf("                                                  ");
    setCursor_inc(x, y++);
    printf("                                                  ");
    setCursor_inc(x, y++);
    printf("           S E L E C T  U S E R  T Y P E          ");
    setCursor_inc(x, y++);
    printf("                                                  ");
    setCursor_inc(x, y++);
    printf("        ");
    ScreenState == 1 ? set_text_color(BLACK,WHITE) : set_text_color(BLACK,YELLOW);
    printf("        Customer     :   ");
    if (selected == 1)
    {
        set_text_color(GREEN,YELLOW);
        printf("   %c",508);
    }else if (selected == 2)
    {
        set_text_color(WHITE,YELLOW);
        printf("   %c",511);
    }else{
        set_text_color(WHITE,YELLOW);
        printf("   %c",511);
    }
    set_text_color(WHITE,YELLOW);
    printf("             ");
    setCursor_inc(x, y++);
    printf("                                                  ");
    setCursor_inc(x, y++);
    printf("        ");
    ScreenState == 2 ? set_text_color(BLACK,WHITE) : set_text_color(BLACK,YELLOW);
    printf("        Delivery boy :   ");
    if (selected == 1)
    {
        set_text_color(WHITE,YELLOW);
        printf("   %c",511);
    }else if (selected == 2)
    {
        set_text_color(GREEN,YELLOW);
        printf("   %c",508);
    }else{
        set_text_color(WHITE,YELLOW);
        printf("   %c",511);
    }
    set_text_color(WHITE,YELLOW);
    printf("             ");
    setCursor_inc(x, y++);
    printf("                                                  ");
    setCursor_inc(x, y++);
    printf("                       ");
    if (ScreenState == 3)
    {
        set_text_color(WHITE,BLUE);
        printf(" CONTINUE  ");  
    }else{
        set_text_color(WHITE,CYAN);
        printf(" CONTINUE  ");
    }
    set_text_color(WHITE,YELLOW);
    printf("                 ");
    setCursor_inc(x, y++);
    set_text_color(WHITE,YELLOW);
    printf("                                                  ");
    setCursor_inc(x, y++);
    printf("                                                  ");
    setCursor_inc(x, y++);
    
}

int UserType(){
    system("cls");
    set_text_color(BLACK,BLACK);
    char option;
    int selected=1;
    int focusSide;
    int currentField = 1;
    while (1)
    {
        switch (option)
        {
            case 72: // Up arrow
                if (currentField > 1) currentField--;
                break;
            case 80: // Down arrow
                if (currentField < 3) currentField++;
                break;
            case 13:
                if (currentField == 1)
                {
                    selected = 1;
                }else if (currentField == 2)
                {
                    selected = 2;
                }else if (currentField == 3)
                {
                    return selected;
                }
                break;
            case 75: // Left arrow
            default:
                break;
        }
        UserTypeScreen(currentField,selected);
        option = _getch();
    }
    

}

int loginFunction()
{
    int choice;
    char *editProfileLabels[] = { "Password", "Email", "Phone", "Back" };
    InputPopup(editProfileLabels,4);

    char *buttonsLabels[] ={"Fuck you","Kiss you"};
    int numButtons = InputPopup(buttonsLabels, 2);


    printf("%d is cliked\n",current_button);
    // int userType = UserType();
    // print_error("error");
    set_text_color(BLACK,BLACK);
    updateCurrentUserFoodRatings();
    // printf("running login function\n");
    FoodItem food_selected;
    UserDeliveryInfo user_delivery_info;
    int res = 1;
    float max_dist;
    double cost_matrix[V][V];
    Node *graph = create_graph_from_file("new_loc_data.txt");
    char ch;
   
    if(readCurrentUser() == 1){
        if (current_user_details.isveg)
        {
            veg_mode = true;
        }else{
            veg_mode = false;
        }
        
    }
    while(1)
    {
        set_text_color(BLACK,WHITE);

        if(readCurrentUser()!=1){

            system("cls");
            home_page_banner();
            home();
            A:
            if (loginUser()){
                // if(getchar()=='\n'){
                    system("cls");
                    top_bar();
                    // restaurantsHomeFunction();
                // }
            }else{
                if(!registerUser()){
                    goto A;
                }

            }// Exit the program after successful logi           
        }else{
            select_beep();
            system("cls");
            top_bar();
            choice = menu_navigator();
            switch (choice)
            {
                case 2:
                    break;
                case 4:
                    FILE *fp = fopen("current_user.txt", "w");
                    if (fp == NULL)
                    {
                        printf("error opening delivery_boys_details.txt");
                    }
                    
                    fclose(fp);
                    return 0;
                    
                    break;
                case 1:
                    system("cls");
                    home();
                    printUserDetails();
                    home_page_banner();
                    display_user_profile();
                    break;
                case 7:
                    system("cls");
                    if(view_cart()!=1) {
                        print_error("Error opening cart");
                    }else
                    {
                        if(edit_cart() == 2){
                            FILE *fp = fopen("current_resturant.txt", "r");
                            if (fp == NULL){
                                fclose(fp);
                                print_error("Error opening file");
                                exit(1);
                            }
                            fscanf(fp, "%s", current_restaurant_name);
                            char sourcename[100];
                            strcpy(sourcename ,readUserDeliveryInfo().address);
                            partnerMap(sourcename,current_restaurant_name,20);
                        }
                    }
                    break;
                case 3:
                    settings();
                    break;
                case 5:
                    return 2;
                    break;
                case 6:
                    res=1;
                    while (res != 0)
                    {
                        system("cls");
                        home_page_banner();
                        home();
                        printUserDetails();
                        side_menu(-1);
                        res = play_games();
                        getchar();
                        system("cls");
                        top_bar();
                    }
                    getchar();
                    break;
                case 8:
                    printf(" Enter food item to search:\n");
                    food_selected = searchFoodItem(restaurant_no,menu);
                    if (food_selected.name != NULL) 
                    {
                        system("cls");
                        top_bar();
                        printFoodItem(food_selected);
                        addCartFunction(food_selected);
                    }
                    
                    getchar();
                    getchar();
                    break;
                case 9:
                    // test_print();
                    int result;
                    // double dist[V];
                    // create_cost_matrix(cost_matrix,dist);
                    user_delivery_info = readUserDeliveryInfo();
                    // printf("%s %f",user_delivery_info.address,user_delivery_info.distance);
                    // nearby_restaurants(user_delivery_info.address,user_delivery_info.distance);
                    result = map(user_delivery_info.address,user_delivery_info.distance);
                    if(result == 0) return 0;
                    getchar();
                    break;
                default:
                    print_error("Invalid choice. Please try again");
                    break;
            }
        }

        
    }

    return 0;

}



