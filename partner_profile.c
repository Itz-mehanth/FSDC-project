#include <stdio.h>
#include <stdbool.h>
#include <Windows.h>
#include "illustrations.h"
#include "map.h"
#include "partner_profile.h"
#include "login.h"
#include "delivery_boy_selection.h"
#include "theme.h"
#include "profile.h"
#include "food_order_page.h"
#include "notification.h"
#include "favourites.h"
#include "history.h"
#define MAX_STRING_LENGTH 100

typedef struct {
    char deliveryPersonName[MAX_STRING_LENGTH];
    char deliveryAddress[MAX_STRING_LENGTH];
    char startDateTime[MAX_STRING_LENGTH];
    char endDateTime[MAX_STRING_LENGTH];
} DeliveryEntry;

void partner_profile_detail_div(){
    readCurrentPartner();
    int x=0,y=15;
    setCursor_inc(x,y++);
    set_text_color(BLACK,WHITE);
    printf("                                                                   ");
    setCursor_inc(x,y++);
    printf("                                                                   ");
    setCursor_inc(x,y++);
    printf("      Username:                         %-20s       ",current_del_boy_details.username);
    setCursor_inc(x,y++);
    printf("                                                                   ");
    setCursor_inc(x,y++);
    printf("      Password                          %-20s       ",current_del_boy_details.password);
    setCursor_inc(x,y++);
    printf("                                                                   ");
    setCursor_inc(x,y++);
    printf("      Email:                            %-20s       ",current_del_boy_details.email);
    setCursor_inc(x,y++);
    printf("                                                                   ");
    setCursor_inc(x,y++);
    printf("      Phone no:                         %-20s       ",current_del_boy_details.phone_no);
    setCursor_inc(x,y++);
    printf("                                                                   ");
    setCursor_inc(x,y++);
    printf("      Ratings:                          %-20.2f       ",current_del_boy_details.ratings);
    setCursor_inc(x,y++);
    printf("                                                                   ");
    setCursor_inc(x,y++);
    printf("      Total ratings:                    %-20d       ",current_del_boy_details.total_ratings);
    setCursor_inc(x,y++);
    printf("                                                                   ");
    setCursor_inc(x,y++);
    set_text_color(WHITE,YELLOW);
    printf("      ");
    set_text_color(WHITE,GREEN);
    printf("                   ");
    set_text_color(WHITE,YELLOW);
    printf("      ");
    printf("                                     ");
    set_text_color(WHITE,YELLOW);
    setCursor_inc(x,y++);
    printf("      ");
    set_text_color(WHITE,GREEN);
    printf("   Edit profile    ");
    set_text_color(WHITE,YELLOW);
    printf("      ");
    printf("                                     ");
    set_text_color(WHITE,YELLOW);
    setCursor_inc(x,y++);
    printf("      ");
    set_text_color(WHITE,GREEN);
    printf("                   ");
    set_text_color(WHITE,YELLOW);
    printf("      ");
    printf("                                     ");
    set_text_color(WHITE,YELLOW);
    setCursor_inc(x,y++);
    printf("                                                                    ");
    setCursor_inc(x,y++);
    printf("                                                                    ");
    setCursor_inc(x,y++);

    set_text_color(BLACK,WHITE);
}
int readDeliveryStatus(const char *filename, DeliveryEntry entries[], int maxEntries) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error opening file.\n");
        return -1;
    }

    char name[MAX_NAME_LENGTH];
    char address[MAX_STRING_LENGTH];
    char startDateTime[25];
    char endDateTime[25];
    int entryCount = 0;

    while (fscanf(file, "%[^,],%[^,],%[^,],%[^\n]\n", name, address, startDateTime, endDateTime) == 4) {
        strcpy(entries[entryCount].deliveryPersonName, name);
        strcpy(entries[entryCount].deliveryAddress, address);
        strcpy(entries[entryCount].startDateTime, startDateTime);
        strcpy(entries[entryCount].endDateTime, endDateTime);
        entryCount++;
    }

    fclose(file);
    return entryCount;
}
void print_deliveries_info(){
    const char *filename = "delivery_boys_status.txt";
    DeliveryEntry entries[20];
    // printf("reading deliveries from %s\n", filename);
    int numEntries = readDeliveryStatus(filename, entries, 20);
    // printf("read deliveries from %s\n", filename);
    // getchar();
    int x=60;
    set_text_color(BLACK,WHITE);
    for (int y = 10; y < numEntries+10; y++)
    {
        if (strcmp(entries[y-10].deliveryPersonName,current_del_boy_details.username)==0)
        {
            printf(" %-50s Start Date&time: %22s End Date&time: %22s\n", entries[y-10].deliveryAddress, entries[y-10].startDateTime, entries[y-10].endDateTime);
        }
    }
    getchar();
}

void getLastPathForUser(const char *filename, const char *target_username, char cities[MAX_CITIES][MAX_CITY_NAME_LENGTH], int *num_cities) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }

    char line[5000];
    char last_path[5000] = "";
    char username[100];
    char *token;
    *num_cities = 0;

    printf("Parsing the file\n");
    while (fgets(line, sizeof(line), file)) {
        // Remove the newline character at the end of the line
        line[strcspn(line, "\n")] = '\0';

        // Extract the username from the line
        char *cities_part = strtok(line, ",");
        token = strtok(NULL, ",");
        if (token == NULL) continue;
        strcpy(username, token);

        if (strcmp(username, target_username) == 0) {
            // Username matches, store this line as the last matching path
            strcpy(last_path, cities_part);
        }
    }

    if (strlen(last_path) > 0) {
        // Username matches, parse the cities
        token = strtok(last_path, " ");
        *num_cities = 0;
        while (token != NULL && *num_cities < MAX_CITIES) {
            strcpy(cities[*num_cities], token);
            (*num_cities)++;
            token = strtok(NULL, " ");
        }
    }

    fclose(file);
}

void print_path(){
    char filename[] = "delivery_details.txt";
    char cities[MAX_CITIES][MAX_CITY_NAME_LENGTH];
    set_text_color(RED,WHITE);
    int num_cities;
    printf("getting the last path\n");
    getchar();
    getLastPathForUser(filename, current_del_boy_details.username, cities, &num_cities);
    printf("got the last path\n");
    getchar();
    int x=130;
    for (int y = 0; y < num_cities; y++)
    {
        setCursor_inc(x,y);
        printf("%d. %50s ",y+1,cities[y]);
    }
    printf("printting the last path\n");
    getchar();
    

}

int edit_partner_profile()
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
    readPartnersFromFile();
    readCurrentPartner();
    FILE *file = fopen("delivery_boys_details.txt", "r+");
    if (file == NULL) {
        print_error("Error opening file!\n");
        return 0;
    }
    for (int i = 0; i < num_del_boys; i++) {
        if (strcmp(partners[i].username, current_del_boy_details.username) == 0) {
            switch (choice) {
                case 1:
                    printf("Enter new password: ");
                    scanf("%s", new_value);
                    strcpy(partners[i].password, new_value);
                    break;
                case 2:
                    printf("Enter new email: ");
                    scanf("%s", new_value);
                    strcpy(partners[i].email, new_value);
                    break;
                case 3:
                    printf("Enter new phone number: ");
                    scanf("%s", new_value);
                    strcpy(partners[i].phone_no, new_value);
                    break;
                case 4:
                    return 1;
                    break;
                default:
                    print_error("Invalid choice.\n");
                    break;
            }
            // Write updated user information to file
            fprintf(file, "%s %s %s %s %lf %lf %f %d %d\n", partners[i].username, partners[i].password, partners[i].email, partners[i].phone_no,partners[i].lat,partners[i].lon,partners[i].ratings,partners[i].total_ratings,partners[i].estimated_sec);
            strcpy(current_del_boy_details.email,partners[i].email);
            strcpy(current_del_boy_details.password,partners[i].password);
            strcpy(current_del_boy_details.username,partners[i].username);
            strcpy(current_del_boy_details.phone_no,partners[i].phone_no);
            current_del_boy_details.lat = partners[i].lat;
            current_del_boy_details.lon = partners[i].lon;
            current_del_boy_details.ratings = partners[i].ratings;
            current_del_boy_details.total_ratings = partners[i].total_ratings;
            current_del_boy_details.estimated_sec = partners[i].estimated_sec;
            writeCurrentPartner(current_del_boy_details);
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
            fprintf(file, "%s %s %s %s %lf %lf %f %d %d\n", partners[i].username, partners[i].password, partners[i].email, partners[i].phone_no,partners[i].lat,partners[i].lon,partners[i].ratings,partners[i].total_ratings,partners[i].estimated_sec);
        }
    }
    partner_profile_detail_div();
    return 1;
}

int partner_profile_options(){

        printf("1. Edit profile\n");
        printf("2. View past order Details\n");
        printf("3. Current delivery location path\n");
        printf("4. Logout\n");
        printf("Enter your choice (1-4): ");
        int choice;
        scanf("%d", &choice);
        switch (choice) {
        case 1:
            edit_partner_profile();
            getchar();
            return 1;
            break;
        case 2:
            print_deliveries_info();
            getchar();
            return 1;
            break;
        case 3: 
            print_path();
            getchar();
            return 1;
            break;
        case 4:
            FILE *fp = fopen("current_del_boy.txt", "w");
            fclose(fp);
            return 0;
        default:
            break;
        
    
    }
}
int display_partner_profile() {

    while (1)
    {
        system("cls");
        set_text_color(BLACK,WHITE);
        home();
        printPartnerDetails();
        home_page_banner();
        partner_profile_detail_div();
        if(partner_profile_options()==0) return 1;
    }

}

