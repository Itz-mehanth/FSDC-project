#include <stdio.h>
#include <string.h>
#include "food_order_page.h"
#include "add_cart.h"
#include "collaborative_filter.h"
#include "login.h"
#include "sounds.h"
#include "restaurants_home.h"
#include "food_items.h"
#include "illustrations.h"
#include "food_items.h"
#include "notification.h"

const char filename[20]="menu.txt";


int addToCart(FoodItem food_item, int quantity) {
    char username[20];
    if(readCurrentUser()==1){
        strcpy(username,current_user_details.username);
    }else{
        strcpy(username,"unknown");
    }
    
    FILE *fp;
    fp = fopen("cart.txt", "a");
    if (fp == NULL) {
        printf("ERROR: Could not open cart file\n");
        return 0;
    }


    fprintf(fp, "%s %s %.2f %s %s %.2f %d %d\n",username, food_item.name, food_item.price,food_item.category,food_item.type, food_item.rating, food_item.total_ratings, quantity);
    fclose(fp);
    return 1;
}
int updateFoodItemRating(const char *itemName, float newRating) {
    readCurrentUser();
    FILE *file = fopen("foods.txt", "r+");
    if (file == NULL) {
        print_error("Error opening foods.txt file.\n");
        return 0;
    }

    char line[MAX_LINE_LENGTH];
    int updated = 0;

    while (fgets(line, sizeof(line), file) != NULL) {
        if (strstr(line, itemName) != NULL) {
            // Parse the line to extract the relevant data
            char name[50];
            float price;
            float rating;
            int total_ratings;
            char category[30];
            char type[20];
            float user_last_rating;

            sscanf(line, "%[^,],%f,%[^,],%[^,],%f,%d,%f", 
                name, &price, category, type, &rating, &total_ratings, &user_last_rating);

            // Update rating and total ratings
            if (user_last_rating > 0 && total_ratings > 1) {
                // Remove the old rating from the average
                rating = (rating * total_ratings - user_last_rating) / (total_ratings - 1);
            } else if (user_last_rating == 0) {
                total_ratings++;
            } else if (user_last_rating > 0 && total_ratings == 1) {
                rating = 0; // Reset the rating if there's only one rating to remove
            }

            // Calculate the new average rating with the new rating
            rating = (rating * (total_ratings - 1) + newRating) / total_ratings;

            // Move the file pointer back to the beginning of the line
            fseek(file, -(strlen(line)+1), SEEK_CUR);

            // Update the line with new rating, total ratings, and user last rating
            fprintf(file, "%s,%.2f,%s,%s,%.2f,%d,%.2f\n",
                name, price, category, type, rating, total_ratings, newRating);

            updated = 1;
            break;
        }
    }

    fclose(file);

    if (updated) {
        // Check if the rating already exists in ratings.txt
        FILE *ratingsFile = fopen("ratings.txt", "r+");
        if (ratingsFile == NULL) {
            print_error("Error opening ratings.txt file.\n");
            return 0;
        }

        char ratingsLine[MAX_LINE_LENGTH];
        int ratingUpdated = 0;
        long pos;

        while (fgets(ratingsLine, sizeof(ratingsLine), ratingsFile) != NULL) {
            char rUsername[50];
            char rItemName[50];
            float rRating;
            sscanf(ratingsLine, "%[^,],%[^,],%f", rUsername, rItemName, &rRating);

            if (strcmp(rUsername, current_user_details.username) == 0 && strcmp(rItemName, itemName) == 0) {
                // Move the file pointer back to the beginning of the line
                pos = ftell(ratingsFile) - (strlen(ratingsLine)+1);
                fseek(ratingsFile, pos, SEEK_SET);
                // Update the line with the new rating
                fprintf(ratingsFile, "%s,%s,%.2f\n", current_user_details.username, itemName, newRating);

                ratingUpdated = 1;
                break;
            }
        }

        if (!ratingUpdated) {
            // If the user's rating for this item does not exist, append it
            fprintf(ratingsFile, "%s,%s,%.2f\n", current_user_details.username, itemName, newRating);
        }
        
        fclose(ratingsFile);

        return 1;
    } else {
        print_error("Food item not found.\n");
        return 0;
    }
}

int food_in_fav(char *food_name){
    FILE *file = fopen("favourites.txt", "r");
    if (file == NULL) {
        print_error("Error opening file\n");
        return 0;
    }
    int found = 0;
    char line[MAX_LINE_LENGTH];
    while (fgets(line,MAX_LINE_LENGTH, file) != NULL) 
    {
    if (strstr(line,food_name) != NULL)
        {
            found = 1;
            break;
        }
        
    }
    return found;
    
}
int food_exists(char *food_name){
    FILE *file = fopen("cart.txt", "r");
    if (file == NULL) {
        print_error("Error opening file\n");
        return 0;
    }
    int found = 0;
    char line[MAX_LINE_LENGTH];
    while (fgets(line,MAX_LINE_LENGTH, file) != NULL)
    {
    if (strstr(line,food_name) != NULL)
        {
            found = 1;
            break;
        }
        
    }
    return found;
    
}
FoodItem recommendedFoodDisplay(){
    PredictedRating* predictedRatings = malloc(sizeof(PredictedRating) * TOTAL_FOOD_ITEMS);
    FoodItem items[TOTAL_FOOD_ITEMS];
    FoodItem predFoods[5];
    int numPredictions = 0;
    int choice;
    int index = 1;
    int countFood;
    loadFoodItems(items,&countFood);
    collaborative_filter(predictedRatings,&numPredictions);
    // printf("%d is the num of predictions\n",numPredictions);
    for (int i = 0; i < numPredictions; i++) {
        for (int j = 0; j < TOTAL_FOOD_ITEMS; j++)
        {
            // printf("%s == %s\n",predictedRatings[i].itemName,items[j].name);
            if (strcmp(predictedRatings[i].itemName, items[j].name) == 0)
            {
                // printf("Match found\n");
                printFoodList(index,items[j],index-1);
                predFoods[index-1] = items[j];
                index++;
            }
        }
        
    }
    int response = MessageBox(NULL, "Wanna view recommended items", "Warning", MB_ICONWARNING | MB_OKCANCEL);
    if (response == IDOK) {
        MessageBox(NULL, "You chose to proceed.", "Proceeding", MB_ICONINFORMATION | MB_OK);
    } else {
        MessageBox(NULL, "You chose to cancel.", "Cancelled", MB_ICONINFORMATION | MB_OK);
        strcpy(predFoods[0].name,"none");
        return predFoods[0];
    }

    printf("Enter your choice: ");
    scanf("%d",&choice);
    return predFoods[choice-1];

}


void rate_food_item(FoodItem food){
    int user_rating;
    char choice;
    char add;
    int quantity;
    B:
    int response = MessageBox(NULL, "Wanna add rating", "Warning", MB_ICONWARNING | MB_OKCANCEL);

    if(response == IDOK){
        MessageBox(NULL, "You chose to proceed.", "Proceeding", MB_ICONINFORMATION | MB_OK);
        printf("Enter your rating: ");
        scanf("%d", &user_rating);
        select_beep();

        if(user_rating>0 && user_rating<6){
            print_success("Thank you for your feedback");
        }else{
            print_error("Invalid rating");
            goto B;
        }
    }else
    {
        MessageBox(NULL, "You chose to cancel.", "Cancelled", MB_ICONINFORMATION | MB_OK);
        goto C;
    }
    food.rating=user_rating;
            
    if(updateFoodItemRating(food.name,user_rating)==1){
    }else {
        print_error("Item not updated in the file\n");
    }
    

    C: 
    if(!food_exists(food.name)){
        response = MessageBox(NULL, "Add to cart", "Warning", MB_ICONWARNING | MB_OKCANCEL);
        scanf(" %c",&add);
        select_beep();

        if (response == IDOK)
        {
            MessageBox(NULL, "You chose to proceed.", "Proceeding", MB_ICONINFORMATION | MB_OK);
            printf("Enter the quantity:");
            scanf(" %d",&quantity);
            select_beep();

            if(addToCart(food,quantity)==1){
                print_success("Item added to cart\n");
            }else{
                print_error("Error adding item to cart\n");
            }
        }else{
            MessageBox(NULL, "You chose to cancel.", "Cancelled", MB_ICONINFORMATION | MB_OK);
        }
    }else{
        print_error("Item already added in cart");
    }
    if(!food_in_fav(food.name)){
        response = MessageBox(NULL, "Wanna add it to the favourites list", "Warning", MB_ICONWARNING | MB_OKCANCEL);
        if (response == IDOK)
        {
            MessageBox(NULL, "You chose to proceed.", "Proceeding", MB_ICONINFORMATION | MB_OK);
            FILE *file = fopen("favourites.txt", "a");
            if (file == NULL) {
                printf("Error opening file\n");
                return;
            }
            fprintf(file, "Username: %s,Name: %s, Price: %.2f, Category: %s, Type: %s, Ratings: %.2f, Total_ratings: %d\n",current_user_details.username ,food.name, food.price, food.category,food.type, food.rating, food.total_ratings);
            FILE *fp = fopen("current_resturant.txt", "w");
            if (fp == NULL){
                print_error("Error opening file\n");
                fclose(fp);
                exit(1);
            }
            fprintf(fp, "%s", current_restaurant_name);
            fclose(fp);

        }else{
            MessageBox(NULL, "You chose to cancel.", "Cancelled", MB_ICONINFORMATION | MB_OK);
        }
    }

    
}

FoodItem addCartFunction(FoodItem food) {
    rate_food_item(food);
    system("cls");
    home_page_banner();
    home();
    printUserDetails();
    return recommendedFoodDisplay(); 
}

