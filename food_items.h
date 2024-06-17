#ifndef FOODITEMS
#define FOODITEMS

#define TOTAL_FOOD_ITEMS 280
#define MAX_LINE_LENGTH 256
#define NUM_CATEGORIES 30
#define MAX_ITEMS 30
#define MAX_CATEGORIES 30
#define MAX_NAME_LENGTH 50
#define MAX_CATEGORY_LENGTH 30
#define MAX_TYPE_LENGTH 20
#define MIN_VOTES 10  // Minimum number of votes required
#define MIN_RATING 1.0 // Minimum rating considered

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// Define the FoodItem struct containing name and price attributes
typedef struct {
    char name[50];
    float price;
    float rating;
    int total_ratings;
    char category[30];
    char type[20];
    float current_user_rating;
} FoodItem;

typedef struct {
    char username[50];
    char name[50];
    float price;
    float rating;
    int total_ratings;
    char category[30];
    char type[20];
    int count;
} FoodItemCart;

typedef struct {
    FoodItem veg[MAX_ITEMS];
    FoodItem nonVeg[MAX_ITEMS];
    char name[MAX_NAME_LENGTH];
    int count_veg; // Variable to keep track of the number of items in the category
    int count_non_veg; // Variable to keep track of the number of items in the category
} Category;
// Define the Category struct containing veg and nonVeg attributes
// Define the Menu struct containing veg and nonVeg categories
typedef struct {

    Category italian;
    Category chinese;
    Category indian;
    Category mexican;
    Category japanese;
    Category american;
    Category middleEastern;
    Category spanish;
    Category thai;
    Category greek;
    Category korean;
    Category french;
    Category caribbean;
    Category mediterranean;
    Category turkish;
    Category moroccan;
    Category ethiopian;
    Category brazilian;
    Category vietnamese;
    Category australian;
    Category north_indian;
    Category south_indian;
    Category tamilnadu;
    Category fastfood;
    Category seafood;
    Category beverages;
    Category breakfast;
    Category snacks;
} Menu;

extern Menu menu;

extern Category categories[MAX_CATEGORIES];

int updateCurrentUserFoodRatings();

Menu readMenuFromFile(Menu *menu);

void printMenu(const Menu *menu);
void loadFoodItems(FoodItem items[], int *count);
void displayPopularItems(Menu menu);

#endif // !FOODITEMS

