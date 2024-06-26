#ifndef RESTAURANTS_HOME
#define RESTAURANTS_HOME
#define TOTAL_RESTAURANTS 27
#define MAX_COMMENT_LENGTH 2000 
#define MINIMUM_RATINGS 50
#include "food_items.h"
#include "map.h"

extern int restaurant_no;
extern char restaurantType[20];
// int restaurant_no;
extern char restaurant_filename[];
extern char current_restaurant_name[100];

typedef struct{
    Category category1;
    Category category2;
    Category category3;
    Category category4;
    Category category5;
} dif_categories;

typedef struct {
    char name[50];
    char type[50];
    double lat;
    double lon;
    float rating;
    int total_ratings;
    float weighted_rating;
    dif_categories categories;
} restaurant;

typedef struct {
    restaurant res;
    int count;
} restaurant_count;

int compare_restaurants(const void *a, const void *b);
int compare_counts(const void *a, const void *b);

restaurant *unique_sorted_restaurants(restaurant *restaurants, int num_restaurants, int *result_size);

extern restaurant restaurants[];
extern restaurant vegRestaurants[];
extern restaurant nonvegRestaurants[];

int review_restaurant(char *restaurant_name);

restaurant *find_restaurant(char *name);

Node enter_delivery_address(Node *graph);

void storeComment(char *restaurant_name);

void printNearbyRestaurant(int n, char *restaurant_name,float distance);
// void nearby_restaurants(char node_name[],float distance_max);
int isrestaurant(char *res_name);
int viewLastFiveComments(char *restaurant_name);

Category select_food_Category();

// int create_restaurant(restaurant *restaurants);

// int create_restaurant(restaurant *restaurants);
// int update_restaurant(const char *filename, struct restaurant *restaurants);
void print_restaurants();

// int initialize_restaurant(restaurant *Restaurant, char name[20],char type[20], double lat, double lon, float rating , int total_ratings);
// Category select_food_Category();
// int writeToRestaurants(restaurant *restaurants);
void printRestaurants(int n, char *restaurant_name);

int readRestaurants();

void rate_restaurant(const char *restaurant_name);

void printRestaurant(int n, char *restaurant_name);

void display_restaurants();
int select_restaurants();

void print_restaurants();

void sortRestaurantsByWeightedRating() ;
// void display_restaurant(const char *restaurant);

int restaurantsHomeFunction();

#endif // !RESTAURANTS_HOME