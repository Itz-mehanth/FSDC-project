#include <stdio.h>
#include "food_items.h"
#include "theme.h"
#include "favourites.h"
#include "food_order_page.h"
#include "login.h"
#include <string.h>

int view_favourites(){
    set_text_color(BLACK,BLACK);
    FoodItem food;
    char username[100], name[100], category[100], type[100];
    float price, rating;
    int total_ratings;

    FILE *fp = fopen("favourites.txt","r");
    if(fp == NULL){
        print_error("Error opening favourites.txt");
        return 0; // Indicate failure
    }
    printf("Favourites:\n");
    int index=0;
    while(fscanf(fp, "Username: %99[^,],Name: %99[^,], Price: %f, Category: %99[^,], Type: %99[^,], Ratings: %f, Total_ratings: %d", 
                  username, food.name, &food.price, food.category, food.type, &food.rating, &food.total_ratings) == 7) {
        if(strcmp(username, current_user_details.username) == 0){
            printFoodList(index+1,food,index);
            index++;
            // printf("Name: %s, Price: %.2f, Category: %s, Type: %s, Ratings: %.2f, Total_ratings: %d\n",
            //        name, price, category, type, rating, total_ratings);
        }
    }
    getchar();
    return 1;
}
