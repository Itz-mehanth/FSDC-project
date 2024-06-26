#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "settings.h"
#include <time.h>
#include "map.h"
#include "nlprecommendation.h"
#include "restaurants_home.h"
#include "textField.h"
#include "illustrations.h"
#include "login.h"
#include "buttonCreator.h"
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
restaurant vegRestaurants[5];
restaurant nonvegRestaurants[10];


int compare_restaurants(const void *a, const void *b) {
    const restaurant *ra = (const restaurant *)a;
    const restaurant *rb = (const restaurant *)b;
    return strcmp(ra->name, rb->name);
}

int compare_counts(const void *a, const void *b) {
    const restaurant_count *rca = (const restaurant_count *)a;
    const restaurant_count *rcb = (const restaurant_count *)b;
    return rcb->count - rca->count;
}

restaurant *unique_sorted_restaurants(restaurant *restaurants, int num_restaurants, int *result_size) {
    qsort(restaurants, num_restaurants, sizeof(restaurant), compare_restaurants);

    restaurant_count *count_array = malloc(num_restaurants * sizeof(restaurant_count));
    int unique_count = 0;

    for (int i = 0; i < num_restaurants; i++) {
        if (unique_count == 0 || strcmp(restaurants[i].name, count_array[unique_count - 1].res.name) != 0) {
            count_array[unique_count].res = restaurants[i];
            count_array[unique_count].count = 1;
            unique_count++;
        } else {
            count_array[unique_count - 1].count++;
        }
    }

    qsort(count_array, unique_count, sizeof(restaurant_count), compare_counts);

    restaurant *sorted_unique_restaurants = malloc(unique_count * sizeof(restaurant));
    for (int i = 0; i < unique_count; i++) {
        sorted_unique_restaurants[i] = count_array[i].res;
    }

    free(count_array);
    *result_size = unique_count;
    return sorted_unique_restaurants;
}
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
    int veg_idx = 0;
    int nonveg_idx = 0;
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

restaurant *find_restaurant(char *name)
{
    for (int i = 0; i < TOTAL_RESTAURANTS; i++)
    {
        // printf("%s == %s", name, restaurants[i].name);
        if (compare_strings(restaurants[i].name, name))
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
        char *ratingsLabels[] = { "1 Star","2 Star","3 Star","4 Star","5 Star"};
        InputPopup(ratingsLabels,5);
        user_rating = current_button;
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

void printRestaurants(int n, char *restaurant_name)
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
void printRestaurant(int n, char *restaurant_name)
{
    waterMelon(50,20);
    readRestaurants();
    restaurant *res = find_restaurant(restaurant_name);

    int y, x;
    y=20,x=95;

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

void printNearbyRestaurant(int n, char *restaurant_name,float distance)
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
    int veg_idx = 0;
    int nonveg_idx = 0;
    for (int i = 0; i < TOTAL_RESTAURANTS; i++) {

        if (strcmp(restaurants[i].type,"veg") == 0)
        {
            vegRestaurants[veg_idx++] = restaurants[i];
        }
        if (strcmp(restaurants[i].type,"nonveg"  ) == 0 || strcmp(restaurants[i].type,"veg") == 0){
            nonvegRestaurants[nonveg_idx++] = restaurants[i];
        }
    }
    setCursor_inc(90,33);
    printf("%s","R E S T A R A U R A N T S");
    for (int i = 0; i < TOTAL_RESTAURANTS; i++)
    {
        if (veg_mode)
        {
            if (strcmp(restaurants[i].type, "veg") == 0)
            {
                printRestaurants(index, restaurants[i].name);
                vegRestaurants[veg_idx++] = restaurants[i];
                index++;
            }
            
        }else{
            printRestaurants(index, restaurants[i].name);
            nonvegRestaurants[nonveg_idx++] = restaurants[i];
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
    readRestaurants();
    if (veg_mode)
    {
        char *editProfileLabels[] = { vegRestaurants[0].name, vegRestaurants[1].name, vegRestaurants[2].name, vegRestaurants[3].name, vegRestaurants[4].name };
        InputPopup(editProfileLabels,5);
    }else{
        char *editProfileLabels[] = { nonvegRestaurants[0].name, nonvegRestaurants[1].name, nonvegRestaurants[2].name, nonvegRestaurants[3].name, nonvegRestaurants[4].name, nonvegRestaurants[5].name, nonvegRestaurants[6].name, nonvegRestaurants[7].name, nonvegRestaurants[8].name, nonvegRestaurants[9].name};
        InputPopup(editProfileLabels,10);
    }
    
    selected_restaurants = current_button;
    select_beep();
    return selected_restaurants;
}

void storeComment(char *restaurant_name)
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
    fprintf(file, "%s,%s%s~%s\n", name, comment,restaurant_name, timestamp);

    // Close file
    fclose(file);
    FILE *fp = fopen("usersChat.txt", "a");
    if (file == NULL) {
        perror("Error opening file for writing");
        return;
    }

    // Get current time and format it

    fprintf(fp, "%s,%s,%s\n", current_user_details.username, comment, timestamp);

    fclose(fp);
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

int review_restaurant(char *restaurant_name)
{
    int choice;
    if (0)
    {
    D:
        home();
        printUserDetails();
        home_page_banner();
        side_menu(-1);
        printRestaurant(1, restaurant_name);
    }

    char *restaurantOptions[] = { "Rate restaurant", "Add comment", "View comment", "View menu"};
    InputPopup(restaurantOptions,4);
    choice = current_button;
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
    return -1;
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
                printRestaurants(index, restaurants[i].name);
                index++;
            }
        }else{
            printRestaurants(index, restaurants[i].name);
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
    sscanf(comment_details, "%s,%s%s~%s\n", name, comment,restaurant_name, time);
    printf("| USER: %s\t\tTIME: %s \n", name, time);
    printf("| COMMENT: %s \n", comment);
    printf("  ----------------------------------------------\n");
}

int viewLastFiveComments(char *restaurant_name)
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
        side_menu(-1);
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
                        FILE *fp = fopen("current_restaurant.txt", "w");
                        if (fp == NULL)
                        {
                            print_error("Couldn't open current restaurant file");
                        }
                        fprintf(fp, "%s", restaurants[i].name);
                        fclose(fp);
                        // printf("****-%s:-****",restaurants[i].name);
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
