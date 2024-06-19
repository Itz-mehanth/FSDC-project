#include "food_items.h"
#ifndef FOOD_ORDER_PAGE
#define FOOD_ORDER_PAGE
#define FOOD_EACH_CATEGORY 10
#define MAX_FOOD_ITEMS 10
#define MAX_FOOD_NAME_LEN 50
#define MAX_ADDRESS_LEN 100
#define TOTAL_FOOD 20

typedef struct {
    char name[50];
    char dish[50];
    char category[50];
    char type[10];
    int quantity;
    char datetime[20];
    float amount;
} FoodEntry;


void printFoodItem(const FoodItem item);

void printPopularFoodList(int n,const FoodItem item, int order);

void setCursor_inc(int x, int y) ;

FoodItem displayMenu(int type,int category_no, Menu menu);

FoodItem select_food(int restaurant_type,Category category);

int remove_items(const char *filename, int target_line);

int change_count(const char *filename, int target_line);

int view_cart();


int edit_cart();

void printFoodList(int n,const FoodItem item, int order);

FoodItem searchFoodItem(int restaurant_no, Menu menu);

int foodOrder();

#endif // !FOOD_ORDER_PAGE