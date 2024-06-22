#include <stdio.h>
#include "theme.h"
#include "login.h"
#include "delivery_boy_selection.h"
#include "food_order_page.h"
#include "partner_path.h"
#include "partner_profile.h"
#include "illustrations.h"
#include <stdbool.h>

#include <conio.h>


int num_del_boys;

char current_del_boy[USERNAME_MAX_LEN]="None";
Partner current_del_boy_details;
Partner partners[MAX_USERS];

void find_partner_details(Partner partners[],const char *target_username,Partner *destination){
    for (int i = 0; i < num_del_boys; i++) {
        if (strcmp(partners[i].username, target_username) == 0) {
            destination[i]=partners[i];
        }
    }
}

void printPartnerDetails(){
    set_text_color(WHITE,RED);
    printf("USERNAME:%-18s\n",current_del_boy_details.username);
    printf("EMAIL:%-21s\n",current_del_boy_details.email);
    set_text_color(CURRENT_FOREGROUND_COLOR,WHITE);
}

int writeCurrentPartner(Partner currentPartner) {
    // printf("writing current partner\n");
    FILE *file = fopen("current_del_boy.txt", "w");
    if (file == NULL) {
        print_error("Error opening file 'current_del_boy.txt' for writing");
        return 0;
    }

    
    fprintf(file, "%s %s %s %s %lf %lf %f %d %d", currentPartner.username, currentPartner.password, currentPartner.email, currentPartner.phone_no, currentPartner.lat, currentPartner.lon, currentPartner.ratings, currentPartner.total_ratings, currentPartner.estimated_sec);
    // }
    fclose(file);
    return 1;
}


int readCurrentPartner(){
    FILE *file=fopen("current_del_boy.txt","r");
    if (file == NULL) {
        print_error("Error opening file 'current_del_boy.txt' for reading");
        return 0;
    }

    if (fscanf(file,"%s %s %s %s %lf %lf %f %d %d",current_del_boy_details.username,current_del_boy_details.password,current_del_boy_details.email,current_del_boy_details.phone_no,&current_del_boy_details.lat,&current_del_boy_details.lon, &current_del_boy_details.ratings, &current_del_boy_details.total_ratings,&current_del_boy_details.estimated_sec) != 9) {
        print_error("Error reading from file 'current_del_boy.txt'");
        fclose(file);
        return 0;
    }    
    strcpy(current_del_boy,current_del_boy_details.username);
    fclose(file);
    return 1;
}

void writePartnersToFile(Partner partner)
{
    FILE *file = fopen("delivery_boys_details.txt", "a");
    if (file == NULL)
    {
        print_error("Error opening file");
        return;
    }
    fprintf(file, "%s %s %s %s %lf %lf %f %d %d\n", partner.username, partner.password, partner.email, partner.phone_no, 12.790126782731512,80.22165662386577,0,0,0);

    fclose(file);
}

int isPartnernameExists(char *username)
{
    set_text_color(MAGENTA,GREEN);
    for (int i = 0; i < num_del_boys; i++)
    {
        if (strcmp(partners[i].username, username) == 0 && username[0] != '\0')
        {
            return 1; // Username already exists
        }
    }
    return 0; 
}// Username does not exist


int readPartnersFromFile() {

    FILE *file = fopen("delivery_boys_details.txt", "r");
    if (file == NULL) {
        print_error("Error opening file");
        return 0;
    }
    num_del_boys = 0;
    while (fscanf(file, "%s %s %s %s %lf %lf %f %d %d\n", partners[num_del_boys].username, partners[num_del_boys].password, partners[num_del_boys].email, partners[num_del_boys].phone_no, &partners[num_del_boys].lat, &partners[num_del_boys].lon, &partners[num_del_boys].ratings,&partners[num_del_boys].total_ratings,&current_del_boy_details.estimated_sec) == 9 && num_del_boys < MAX_USERS)  {
        // printf("%s %s %s %s %lf %lf %f %d\n",partners[num_del_boys].username, partners[num_del_boys].password, partners[num_del_boys].email, partners[num_del_boys].phone_no, partners[num_del_boys].lat, partners[num_del_boys].lon, partners[num_del_boys].ratings,partners[num_del_boys].total_ratings);
        num_del_boys++;
    }
    // printf("%d is the number of users\n",num_del_boys);

    fclose(file);
    return 1;
}
int registerPartner()
{
    readPartnersFromFile();
    int currentField = 0;
    bool success = false;
    char username[USERNAME_MAX_LEN]="";
    char password[PASSWORD_MAX_LEN]="";
    char email[EMAIL_MAX_LEN] = "";
    char phone[PHONE_NO_MAX_LEN] = "";
    Partner partner;
    int focusSide = 0; // 0 for main form, 1 for side page (signup)

    while (!success) {
        // system("cls");
        int x = 80, y = 20;
        // Print sign-up form
        setCursor_inc(x, y++);
        set_text_color(BLACK,YELLOW);
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


        set_text_color(BLACK,DARK_BLUE);
        if (currentField == 4)
        {
            set_text_color(BLACK,BLUE);
        }
        
        printf("                                     ");
        setCursor_inc(x, y++);
        printf("            S I G N   U P            ");
        setCursor_inc(x, y++);
        printf("                                     ");
        setCursor_inc(x, y++);
        set_text_color(BLACK,YELLOW);
        printf("                                     ");
        setCursor_inc(x, y++);
        set_text_color(BLACK,YELLOW);
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
                
                
                
                if(!isPartnernameExists(username) && authenticate(password) && currentField == 4 && isPhoneNumberValid(phone) && isEmailValid(email)){
                        setCursor_inc(80,33);
                        set_text_color(BLACK,YELLOW);
                        print_success("   Signing up...");
                        setCursor_inc(80,34);
                        set_text_color(BLACK,BLUE);
                        for (int i = 0; i < 37; i++)
                        {
                            printf("=");
                            Sleep(200);
                        }
                        setCursor_inc(80,34);
                        set_text_color(BLACK,YELLOW);
                        print_success("Sign-up successful!");
                        strcpy(partner.email, email);
                        strcpy(partner.username, username);
                        strcpy(partner.password,  password);
                        strcpy(partner.phone_no, phone);
                        num_del_boys++;
                        writePartnersToFile(partner);
                        success = true;
                }
                if (currentField == 4)
                {

                    if (isPartnernameExists(username))
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

int loginPartner()
{
    // home();
    // side_menu(false);
    // home_page_banner();
    readPartnersFromFile();
    int currentField = 0;
    bool success = false;
    int x,y;
    char username[USERNAME_MAX_LEN]="";
    char password[PASSWORD_MAX_LEN]="";
    int focusSide = 1; // 0 for main form, 1 for side page (signup)

    while(!success){

        int x = 124, y = 20;

        setCursor_inc(x, y++);
        set_text_color(BLACK,YELLOW);
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
        set_text_color(BLACK,DARK_BLUE);
        if (currentField == 2)
        {
            set_text_color(BLACK,BLUE);
        }
        printf("                                      ");
        setCursor_inc(x, y++);
        printf("              L  O G I N              ");
        setCursor_inc(x, y++);
        printf("                                      ");
        setCursor_inc(x, y++);
        set_text_color(BLACK,YELLOW);
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
                int num_partners;
                num_partners = readPartnersFromFile();
                // printf("num of partners: %d\n", num_partners);
                if (focusSide == 0)
                {
                    return 0;
                }
                if (currentField == 2) {
                    for (int i = 0; i < num_del_boys; i++)
                    {

                        if (strcmp(partners[i].username, username) == 0 && strcmp(partners[i].password, password) == 0 && username[0] != '\0')
                        {
                            strcpy(current_del_boy,username);
                            current_del_boy_details = partners[i];
                            setCursor_inc(52,90);
                            set_text_color(BLACK,YELLOW);
                            print_success("  Logging in...");
                            if(writeCurrentPartner(current_del_boy_details)==1){
                                set_text_color(BLACK,BLUE);
                                for (int i = 0; i < 37; i++)
                                {
                                    printf("=");
                                    Sleep(200);
                                }
                                setCursor_inc(52,91);
                                set_text_color(BLACK,YELLOW);
                                print_success("Login successful");
                                success = true;
                                return 1;
                            }else{
                                print_error("Current is not getting written");
                                return 0;
                            }
                        }
                    }
                    print_error("Partner not found");
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

int delivery_boy_login()
{
    // int option = UserType();
    // printf("%d\n",option);
    // getchar();
    // if (option == 2)
    // {
     if(readCurrentPartner()!=1){
            system("cls");
            A:
            if (loginPartner()){
                if(getchar()=='\n'){
                    system("cls");
                }
            }else{
                if(!registerPartner()){
                    goto A;
                }

            }// Exit the program after successful logi       
        }
        
        {
            if(display_partner_profile()==1){
                return 0;
            }
            // displayPopularI
        }
    //     printf("calling map");
    // //     getchar();
    //     char restaurant[50] = "padur";
    //     partnerMap("sri_chenganmaaleeswarar_shiva_temple",restaurant,20);
    // }
    return 0;
}