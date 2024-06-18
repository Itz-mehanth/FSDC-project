#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "settings.h"
#include <time.h>
#include "map.h"
#include "restaurants_home.h"
#include "illustrations.h"
#include "login.h"
#include "theme.h"
#include "food_order_page.h"
#include "food_items.h"
#include "sounds.h"
#include "notification.h"
#include <stdbool.h>

// int restaurant_no;
char restaurant_filename[] = "restaurants_new.txt";

int restaurant_no;

char restaurantType[20];

restaurant restaurants[TOTAL_RESTAURANTS];

void printf_restaurants(restaurant *restaurants) {
    for (int i = 0; i < TOTAL_RESTAURANTS; i++) {
            printf("%s, %s, %lf, %lf, %f, %d, %f\n", restaurants[i].name, restaurants[i].type, restaurants[i].lat, restaurants[i].lon, restaurants[i].rating, restaurants[i].total_ratings, restaurants[i].weighted_rating);
    }
    getchar();
}
void calculateWeightedRatings() {
    float C = 0.0;
    int totalRatingsCount = 0;
    int totalRestaurantsWithRatings = 0;

    // Calculate the mean rating C
    for (int i = 0; i < TOTAL_RESTAURANTS; i++) {
        if (restaurants[i].total_ratings > 0) {
            C += restaurants[i].rating * restaurants[i].total_ratings;
            totalRatingsCount += restaurants[i].total_ratings;
            totalRestaurantsWithRatings++;
        }
    }

    if (totalRatingsCount > 0) {
        C /= totalRatingsCount;
    }

    // Calculate the weighted rating for each restaurant
    for (int i = 0; i < TOTAL_RESTAURANTS; i++) {
        float R = restaurants[i].rating;
        int v = restaurants[i].total_ratings;
        float weighted_rating;
        
        if (v > 0) {
            weighted_rating = (v / (float)(v + MINIMUM_RATINGS)) * R + (MINIMUM_RATINGS / (float)(v + MINIMUM_RATINGS)) * C;
        } else {
            weighted_rating = C;
        }

        restaurants[i].weighted_rating = weighted_rating;
    }
}

int compareWeightedRatings(const void *a, const void *b) {
    const restaurant *restaurantA = (const restaurant*)a;
    const restaurant *restaurantB = (const restaurant*)b;

    float weightedRatingA = ((float)restaurantA->total_ratings / (restaurantA->total_ratings + MIN_VOTES)) * restaurantA->rating 
                           + ((float)MIN_VOTES / (restaurantA->total_ratings + MIN_VOTES)) * MIN_RATING;

    // Calculate weighted rating for item B
    float weightedRatingB = ((float)restaurantB->total_ratings / (restaurantB->total_ratings + MIN_VOTES)) * restaurantB->rating 
                           + ((float)MIN_VOTES / (restaurantB->total_ratings + MIN_VOTES)) * MIN_RATING;

    // Compare by weighted rating in descending order

    if (weightedRatingA < weightedRatingB) return 1;
    if (weightedRatingA > weightedRatingB) return -1;
    return 0;
}

void sortRestaurantsByWeightedRating() {
    // printf_restaurants(restaurants);
    // calculateWeightedRatings(restaurants);
    qsort(restaurants, TOTAL_RESTAURANTS, sizeof(restaurant), compareWeightedRatings);
    // printf_restaurants(restaurants);
}

int readRestaurants() {
    FILE *fp = fopen("restaurants_new.txt", "r");
    if (fp == NULL) {
        print_error("Error opening file:restaurants_new.txt");
        return 0;
    }
    for (int i = 0; i < TOTAL_RESTAURANTS; i++) {
        fscanf(fp, "%[^,],%[^,],%lf,%lf,%f,%d\n", restaurants[i].name, restaurants[i].type, &restaurants[i].lat, &restaurants[i].lon, &restaurants[i].rating, &restaurants[i].total_ratings);
    }
    fclose(fp);
    sortRestaurantsByWeightedRating(restaurants);
    return 1;
}
Category select_food_Category()
{
    int category_num;
    printf("\t\t\t===========================================\n");
    printf("\t\t\tEnter the food category: ");
    scanf("%d", &category_num);
    return categories[category_num - 1];
}

int update_restaurant(const char *filename, restaurant *restaurants)
{
    FILE *fp = fopen(filename, "w"); // Open in write mode to overwrite existing data
    if (fp == NULL)
    {
        print_error("Error opening file");
        return 0;
    }

    if (readRestaurants(filename) == 1)
    {
        for (int i = 0; i < TOTAL_RESTAURANTS; i++)
        {
            fprintf(fp, "%s,%s,%lf,%lf,%f,%d\n", restaurants[i].name, restaurants[i].type, restaurants[i].lat, restaurants[i].lon, restaurants[i].rating, restaurants[i].total_ratings);
        }
    }
    else
    {
        print_error("Error reading file");
    }
    fclose(fp);
    return 1;
}

restaurant *find_restaurant(const char *name)
{
    for (int i = 0; i < TOTAL_RESTAURANTS; i++)
    {
        if (strcmp(restaurants[i].name, name) == 0)
        {
            return &restaurants[i]; // return a pointer to the original object
        }
    }
    restaurant* rest = (restaurant*)malloc(sizeof(restaurant));
    if (rest == NULL) {
        print_error("Memory allocation failed");
        return NULL; // Return NULL if memory allocation fails
    }

    // Initialize the restaurant structure
    strcpy(rest->name, "none");
    return rest; // return a pointer to the first object as a default value
}

void rate_restaurant(const char *restaurant_name)
{
    int user_rating;
    char choice;
B:

    int response = MessageBox(NULL, "Wanna add rating", "Warning",MB_ICONQUESTION | MB_YESNOCANCEL);
    if(response == IDYES){
        MessageBox(NULL, "You chose to proceed.", "Proceeding", MB_ICONINFORMATION | MB_OK);
        printf("Enter your rating: ");
        scanf("%d", &user_rating);
        select_beep();
        if (user_rating > 0 && user_rating < 6)
        {
            print_success("Thank you for your feedback");
        }
        else
        {
            print_error("Invalid rating");
            goto B;
        }
    }
    else if (response == IDNO)
    {
        return;
    }
   
    for (int i = 0; i < TOTAL_RESTAURANTS; i++)
    {
        if (strcmp(restaurants[i].name, restaurant_name) == 0)
        {
            restaurants[i].rating = (restaurants[i].rating * restaurants[i].total_ratings + user_rating) / (restaurants[i].total_ratings + 1);
            restaurants[i].total_ratings++;

            update_restaurant(restaurant_filename, restaurants);
        }
    }
}

void printRestaurant(int n, const char *restaurant_name)
{
    readRestaurants();
    restaurant *res = find_restaurant(restaurant_name);

    int y, x;
    if (n - 1 < 5)
    {
        y = 35;
        x = (n - 1) * 35 + 30;
    }
    else
    {
        y = 45;
        x = (n - 6) * 35 + 30;
    }

    setCursor_inc(x, y);
    y++;
    set_text_color(RED, YELLOW);
    printf("[%d] Restaurant Details          ", n);
    set_text_color(CURRENT_FOREGROUND_COLOR, CURRENT_BACKGROUND_COLOR);

    setCursor_inc(x, y);
    y++;
    set_text_color(GREEN, WHITE);
    printf("  Category: ");
    set_text_color(BLACK, WHITE);
    printf("%-18s  ", res->type);

    setCursor_inc(x, y);
    y++;
    printf("                                ");
    setCursor_inc(x, y);
    y++;
    set_text_color(RED, WHITE);
    printf("         %-21s  ", res->name);

    setCursor_inc(x, y);
    y++;
    printf("                                ");

    setCursor_inc(x, y);
    y++;
    set_text_color(YELLOW, WHITE);
    printf("     *");
    set_text_color(BLACK, WHITE);
    printf(" %.2f (", res->rating);

    set_text_color(GREEN, WHITE);
    printf("%d", res->total_ratings);
    set_text_color(BLACK, WHITE);
    printf(")                 ");

    setCursor_inc(x, y);
    y++;
    if (n == 9)
    {
        setCursor_inc(0, 32);
    }

    set_text_color(CURRENT_FOREGROUND_COLOR, WHITE);
}

void printNearbyRestaurant(int n, const char *restaurant_name,float distance)
{
    readRestaurants();
    restaurant *res = find_restaurant(restaurant_name);

    int y, x;
    if (n - 1 < 5)
    {
        y = 35;
        x = (n - 1) * 35 + 30;
    }
    else
    {
        y = 45;
        x = (n - 6) * 35 + 30;
    }

    setCursor_inc(x, y);
    y++;
    set_text_color(RED, YELLOW);
    printf("[%d] Restaurant Details          ", n);
    set_text_color(CURRENT_FOREGROUND_COLOR, CURRENT_BACKGROUND_COLOR);

    setCursor_inc(x, y);
    y++;
    set_text_color(GREEN, WHITE);
    printf("  Category: ");
    set_text_color(BLACK, WHITE);
    printf("%-18s  ", res->type);

    setCursor_inc(x, y);
    y++;
    printf("                                ");
    setCursor_inc(x, y);
    y++;
    set_text_color(RED, WHITE);
    printf("         %-21s  ", res->name);

    setCursor_inc(x, y);
    y++;
    printf("                                ");

    setCursor_inc(x, y);
    y++;
    set_text_color(YELLOW, WHITE);
    printf("     *");
    set_text_color(BLACK, WHITE);
    printf(" %.2f (", res->rating);

    set_text_color(GREEN, WHITE);
    printf("%d", res->total_ratings);
    set_text_color(BLACK, WHITE);
    printf(")      ");
    set_text_color(BLUE, WHITE);
    printf("%-8.2f Km",distance);

    setCursor_inc(x, y);
    y++;
    if (n == 9)
    {
        setCursor_inc(0, 32);
    }

    set_text_color(CURRENT_FOREGROUND_COLOR, WHITE);
}

Node enter_delivery_address(Node *graph)
{
    char address[100];
    getchar();
A:
    printf("Search for the delivery address:");
    fgets(address, 100, stdin);
    address[strcspn(address, "\n")] = '\0'; // Remove trailing newline

    printf("Searching for relevant nodes for address: %s\n", address);

    // Loop through all nodes and check if the address is relevant
    printf("Most relevant node names:\n");
    int n = 1;
    int index[MAX_CITIES];
    int choice;
    int found = 0;
    for (int i = 0; i < V; i++)
    {
        if ((strstr(graph[i].name, address) != NULL))
        {
            printf("%d. %s\n", n++, graph[i].name);
            index[n - 1] = i;
            found = 1;
        }
    }
    if (found == 0)
    {
        print_error("No relevant nodes found");
        goto A;
    }
    printf("Enter your choice:");
    scanf("%d", &choice);
    if (choice > sizeof(index) / sizeof(index[0]))
    {
        print_error("Invalid choice");
        goto A;
    }
    return graph[index[choice]];
}

void display_restaurants()
{
    int index = 1;
    setCursor_inc(90,33);
    printf("%s","R E S T A R A U R A N T S");
    for (int i = 0; i < TOTAL_RESTAURANTS; i++)
    {
        if (veg_mode)
        {
            if (strcmp(restaurants[i].type, "veg") == 0)
            {
                printRestaurant(index, restaurants[i].name);
                index++;
            }
            
        }else{
            printRestaurant(index, restaurants[i].name);
            index++;
        }
        if (index == 10)
        {
            break;
        }
    }
    set_text_color(CURRENT_FOREGROUND_COLOR, CURRENT_BACKGROUND_COLOR);
    return;
}

int select_restaurants()
{
    int selected_restaurants;
    printf("Enter the restaurant number to select:");
    scanf("%d", &selected_restaurants);
    select_beep();
    return selected_restaurants;
}

void storeComment(const char *restaurant_name)
{
    char name[100];
    char comment[1000];
    time_t now;
    struct tm *tm_info;
    char timestamp[26];

    // Prompt user for name
    if (readCurrentUser() == 1)
    {
        strcpy(name, current_user_details.username);
    }
    else
    {
        strcpy(name, "unknown");
    }

    int c;
    while ((c = getchar()) != '\n' && c != EOF)
        ;
    // Prompt user for comment
    printf("\nEnter your comment: ");
    fgets(comment, sizeof(comment), stdin);
    // Remove trailing newline from comment
    if (comment[strlen(comment) - 1] == '\n')
        comment[strlen(comment) - 1] = '\0';

    // Get current time
    time(&now);
    tm_info = localtime(&now);

    // Format time as string
    strftime(timestamp, sizeof(timestamp), "%Y-%m-%d %H:%M:%S", tm_info);

    // Open file for appending
    FILE *file = fopen("restaurant_comments.txt", "a");
    if (file == NULL)
    {
        print_error("Error opening file for writing");
        return;
    }

    // Write data to file
    fprintf(file, "Name: %s Comment: %s~Timestamp: %s~RestaurantName: %s\n", name, comment, timestamp, restaurant_name);

    // Close file
    fclose(file);
    print_success("Thank You! Comment added successfully");
}

int isrestaurant(char *res_name){
    for (int i = 0; i < TOTAL_RESTAURANTS; i++)
    {
        // printf("%s == %s\n", res_name,restaurants[i].name);
        if (strcmp(res_name,restaurants[i].name)==0)
        {
            return 1;
        }
        
    }
    return 0;
}

int review_restaurant(const char *restaurant_name)
{
    int choice;
    if (0)
    {
    D:
        home();
        printUserDetails();
        printRestaurant(1, restaurant_name);
    }
    printf("1.Rate restaurant:\n");
    printf("2.Add comment:\n");
    printf("3.View comment:\n");
    printf("4.View menu:\n");
    printf("5.back:\n");
    printf("Enter your choice:");
    scanf("%d", &choice);
    select_beep();
    switch (choice)
    {
    case 1:
        rate_restaurant(restaurant_name);
        break;
    case 2:
        storeComment(restaurant_name);
        break;
    case 3:
        if (viewLastFiveComments(restaurant_name) == 1)
        {
            getchar();
            getchar();
            break;
        }
    case 4:
        return 0;
        break;
    case 5:
        return 2;
    default:
        print_error("Enter a valid input");
        break;
    }
    system("cls");
    goto D;
    return 0;
}

void print_restaurants()
{
    
    int index = 1;
    for (int i = 0; i < TOTAL_RESTAURANTS; i++)
    {
        if (veg_mode)
        {
            if (strcmp(restaurants[i].type,"veg") == 0)
            {
                printRestaurant(index, restaurants[i].name);
                index++;
            }
            
        }else{

            printRestaurant(index, restaurants[i].name);
            index++;
        }
        if (index == 11)
        {
            break;
        }
    }
    set_text_color(CURRENT_FOREGROUND_COLOR, CURRENT_BACKGROUND_COLOR);
    return;
}
void formatted_comment(char *comment_details)
{
    char name[20];
    char time[20];
    char comment[MAX_COMMENT_LENGTH];
    char restaurant_name[20];
    sscanf(comment_details, "Name: %s Comment: %[^~]~Timestamp: %[^~]~RestaurantName: %s\n", name, comment, time, restaurant_name);
    printf("| USER: %s\t\tTIME: %s \n", name, time);
    printf("| COMMENT: %s \n", comment);
    printf("  ----------------------------------------------\n");
}

int viewLastFiveComments(const char *restaurant_name)
{
    int num_lines = 0;
    char line[MAX_COMMENT_LENGTH];
    int index = 0;
    int found=0;
    char comments[5][MAX_COMMENT_LENGTH];
    FILE *file = fopen("restaurant_comments.txt", "r");
    if (file == NULL)
    {
        print_error("Error opening file for reading");
        return 0;
    }

    while (fgets(line, MAX_COMMENT_LENGTH, file) != NULL)
    {
        if (strstr(line, restaurant_name) != NULL)
        {
            strcpy(comments[index], line);
            num_lines++;
            found =1;
            index++;
        }
    }
    if (!found)
    {
        print_error("No comments available");
        return 1;
    }
    
    printf("Total number of comments: %d\n", num_lines);
    printf("-===============================================-\n\n");
    int i = num_lines - 1;
    while (1)
    {
        formatted_comment(comments[i]);
        if (i == 0 || i == num_lines - 5)
        {
            break;
        }
        i--;
    }
    printf("-===============================================-\n");

    fclose(file);
    return 1;
}

int restaurantsHomeFunction()
{
    readRestaurants();
    // Category category;
    int choice;
    bool veg = false;
    bool non_veg = false;
    bool nearby = false;
    bool valid_choice = false;
    bool valid = false;

    if (veg_mode)
    {
        strcpy(restaurantType, "veg");
    }
    else
    {
        strcpy(restaurantType, "nonveg");
    }
    
    system("cls");
    top_bar();
    display_restaurants();
   

        readRestaurants();
        int response;
        int selection = INT_MAX;
        while (selection > 10 && printf("invalid selection\n"))
        {
            selection = select_restaurants();
        }
        system("cls");
        home();
        printUserDetails();
        home_page_banner();
        int restaurant_count = 0;
        for (int i = 0; i < TOTAL_RESTAURANTS; i++)
        {
            if(veg_mode){
                if (strcmp(restaurants[i].type,restaurantType))
                {
                    restaurant_count++;
                    if (selection == restaurant_count)
                    {

                        printf("****-%s:-****",restaurants[i].name);
                        printRestaurant(restaurant_count,restaurants[i].name);
                        response = review_restaurant(restaurants[i].name);
                        strcpy(current_restaurant_name,restaurants[i].name);
                        if (response == 2)
                        {
                            return 2;
                        }else if (response == 0)
                        {
                            return 0; 
                        }
                        
                        restaurant_no = 0;
                    }
                    
                }
            }else{
                restaurant_count++;
                if (selection == restaurant_count)
                {
                
                    printf("****-%s:-****",restaurants[i].name);
                    printRestaurant(restaurant_count,restaurants[i].name);
                    response = review_restaurant(restaurants[i].name);
                    if (response == 2)
                    {
                        return 2;
                    }else if (response == 0)
                    {
                        return 0; 
                    }
                    restaurant_no = 0;
                }
            }
            
        }
        
    
    return 3;
    
}
