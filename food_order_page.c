#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include "food_order_page.h"
#include "restaurants_home.h"
#include "login.h"
#include "settings.h"
#include "collaborative_filter.h"
#include "illustrations.h"
#include <ctype.h>
#include "settings.h"
#include "partner_path.h"
#include "delivery_boy_selection.h"
#include <conio.h>
#include "sounds.h"
#include <windows.h>
#include "add_cart.h"
#include "food_items.h"
#include "payment.h"
#include "notification.h"



FoodItem select_food(int restaurant_type,Category category){
    int choice;
    A:
    printf("===========================================\n");
    printf("Enter the food: ");
    scanf("%d", &choice);
    select_beep();
    if (veg_mode)
    {    
        if(choice > FOOD_EACH_CATEGORY/2 || choice <= 0){
            print_error("Please select a category");
            goto A;
        }
    }else
    {
        if(choice > FOOD_EACH_CATEGORY || choice <= 0){
            print_error("Please select a category");
            goto A;
        }
    }
    

    FoodItem food;
    if (veg_mode)
    {
        food = category.veg[choice-1];
    }else{
        food = category.nonVeg[choice-1];
    }

    return food;

}
void setCursor_inc(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void printCartFood(int n,const FoodItemCart item) {
    int y,x;
    if(n < 6){
        y = 20;
        x = (n-1) * 35 + 30;
    }else{
        y = 26;
        x = (n-6) * 35 + 30;
    }
    setCursor_inc(x,y++); 
    set_text_color(WHITE,RED);   
    printf("[%d]      Food Details       ",n);
    setCursor_inc(x,y++);    
    set_text_color(YELLOW,WHITE);
    printf("                            ");

    setCursor_inc(x,y++);

    set_text_color(YELLOW,WHITE);
    printf("  Cuisine: ");
    set_text_color(BLACK,WHITE);
    printf("%-15s  ", item.category);

    setCursor_inc(x,y++);    
    printf("                            ");
    setCursor_inc(x,y++);
    set_text_color(YELLOW,WHITE);
    printf("  Category: ");
    set_text_color(BLACK,WHITE);
    printf("%-14s  ", item.type);

    setCursor_inc(x,y++);    
    printf("                            ");
    setCursor_inc(x,y++);
    set_text_color(RED,WHITE);
    printf("            %-14s  ", item.name);
    setCursor_inc(x,y++);    
    printf("                            ");

    setCursor_inc(x,y++);

    set_text_color(CYAN,WHITE);
    printf("       $ %-17.2f  ", item.price);

    setCursor_inc(x,y++);

    set_text_color(YELLOW,WHITE);
    printf("     *");
    set_text_color(BLACK,WHITE);
    printf(" %.2f (", item.rating);

    set_text_color(YELLOW,WHITE);
    printf("%d", item.total_ratings);
    set_text_color(BLACK,WHITE);
    printf(")             ");

    setCursor_inc(x,y++);    
    printf("                            ");
    setCursor_inc(x,y++);
    set_text_color(WHITE,YELLOW);
    printf(" Quantity: %-10d       ", item.count);
    set_text_color(CURRENT_FOREGROUND_COLOR,CURRENT_BACKGROUND_COLOR);
    printf("\n");
}



void printFoodItem(const FoodItem item) {
    set_text_color(RED,YELLOW);
    printf("            Food Details                \n");

    set_text_color(YELLOW,WHITE);
    printf("  Cuisine: ");
    set_text_color(BLACK,WHITE);
    printf("%-27s  \n", item.category);

    set_text_color(YELLOW,WHITE);
    printf("  Category: ");
    set_text_color(BLACK,WHITE);
    printf("%-26s  \n", item.type);

    printf("                                        \n");
    set_text_color(RED,WHITE);
    printf("            %-26s  \n", item.name);
    printf("                                        \n");

    set_text_color(CYAN,WHITE);
    printf("       $ %-29.2f  \n", item.price);
    printf("                                        \n");

    set_text_color(YELLOW,WHITE);
    printf("     *");
    set_text_color(BLACK,WHITE);
    printf(" %.2f (", item.rating);

    set_text_color(YELLOW,WHITE);
    printf("%d", item.total_ratings);
    set_text_color(BLACK,WHITE);
    printf(")                         \n");

    printf("                                        ");
    set_text_color(CURRENT_FOREGROUND_COLOR,CURRENT_BACKGROUND_COLOR);
    printf("\n");
}

void printFoodList(int n,const FoodItem item, int order) {
    int y,x;
    if(order < 5){
        y = 20;
        x = order * 35 + 30;
    }else if(order < 10){
        y = 26;
        x = (order-5) * 35 + 30;
    }else if(order < 15){
        y = 32;
        x = (order-10) * 35 + 30;
    }

    set_text_color(CURRENT_FOREGROUND_COLOR,CURRENT_BACKGROUND_COLOR);

    set_text_color(RED,YELLOW);
    setCursor_inc(x,y);
    y++;

    printf("[%d]         Food Details        ",n);
    set_text_color(CURRENT_FOREGROUND_COLOR,CURRENT_BACKGROUND_COLOR);

    setCursor_inc(x,y);
    y++;
    set_text_color(YELLOW,WHITE);

    printf("  Cuisine: ");
    set_text_color(BLACK,WHITE);
    printf("%-17s    ", item.category);


    setCursor_inc(x,y);
    y++;
    set_text_color(YELLOW,WHITE);

    printf("  Category: ");
    set_text_color(BLACK,WHITE);
    printf("%-15s     ", item.type);
    setCursor_inc(x,y);
    y++;


    set_text_color(RED,WHITE);
    printf("   Food: %-16s       ", item.name);

    setCursor_inc(x,y);
    y++;

    set_text_color(CYAN,WHITE);
    printf("       $ %-16.2f       ", item.price);

    setCursor_inc(x,y);
    y++;

    set_text_color(WHITE,GREEN);
    printf("    ");
    set_text_color(YELLOW,GREEN);
    printf(" *");
    set_text_color(WHITE,GREEN);
    printf(" %.2f (", item.rating);
    set_text_color(WHITE,GREEN);
    printf("%d", item.total_ratings);
    printf(")");
    printf("                 ");
    set_text_color(BLACK,WHITE);
    setCursor_inc(x,y);        
    y++;
    if (order == 9)
    {
        setCursor_inc(0,32);        
    }
    
    set_text_color(CURRENT_FOREGROUND_COLOR,CURRENT_BACKGROUND_COLOR);
}

void printPopularFoodList(int n,const FoodItem item, int order) {
    int y,x;
    y = 26;
    x = order * 35 + 30;
    set_text_color(CURRENT_FOREGROUND_COLOR,CURRENT_BACKGROUND_COLOR);

    set_text_color(RED,YELLOW);
    setCursor_inc(x,y);
    y++;

    printf("[%d]         Food Details         ",n);
    set_text_color(CURRENT_FOREGROUND_COLOR,CURRENT_BACKGROUND_COLOR);

    setCursor_inc(x,y);
    y++;
    set_text_color(YELLOW,WHITE);

    printf("  Cuisine: ");
    set_text_color(BLACK,WHITE);
    printf("%-15s       ", item.category);


    setCursor_inc(x,y);
    y++;
    set_text_color(YELLOW,WHITE);

    printf("  Category: ");
    set_text_color(BLACK,WHITE);
    printf("%-16s     ", item.type);
    setCursor_inc(x,y);
    y++;


    set_text_color(RED,WHITE);
    printf("      Food: %-16s     ", item.name);

    setCursor_inc(x,y);
    y++;

    set_text_color(CYAN,WHITE);
    printf("       $ %-19.2f     ", item.price);

    setCursor_inc(x,y);
    y++;

    set_text_color(YELLOW,GREEN);
    printf("    ");
    printf(" *");
    set_text_color(WHITE,GREEN);
    printf(" %.2f (", item.rating);
    set_text_color(WHITE,GREEN);
    printf("%d", item.total_ratings);
    printf(")");
    printf("                  ");
    set_text_color(BLACK,WHITE);
    setCursor_inc(x,y);        
    y++;
    if (order == 9)
    {
        setCursor_inc(0,32);        
    }
    
    set_text_color(CURRENT_FOREGROUND_COLOR,CURRENT_BACKGROUND_COLOR);
}

FoodItem displayMenu(int type,int category_no,Menu menu) {
        FoodItem item;
        readMenuFromFile(&menu);

        // printMenu(&menu);
        if(veg_mode){
            switch (category_no)
            {
                case 1:
                            printf("Italian items:\n");
                            for (int i = 0; i < FOOD_EACH_CATEGORY/2; i++){
                                printFoodList(i+1,menu.italian.veg[i],i);
                                
                            }
                            item=select_food(restaurant_no,menu.italian);
                            // printf("%s\n",item.name);
                            return item;
                            break;
                        case 2:
                        printf("Chinese items:\n");
                            for (int i = 0; i < FOOD_EACH_CATEGORY/2; i++){
                                printFoodList(i+1,menu.chinese.veg[i],i);
                                
                            }
                            item=select_food(restaurant_no,menu.chinese);
                            // printf("%s\n",item.name);
                            return item;
                            break;
                        case 3:
                        printf("Tamil nadu items:\n");
                            for (int i = 0; i < FOOD_EACH_CATEGORY/2; i++){
                                printFoodList(i+1,menu.tamilnadu.veg[i],i);
                                
                            }
                            item=select_food(restaurant_no,menu.tamilnadu);
                            // printf("%s\n",item.name);
                            return item;
                            break;
                        case 4:
                        printf("Fast food items:\n");
                            for (int i = 0; i < FOOD_EACH_CATEGORY/2; i++){
                                printFoodList(i+1,menu.fastfood.veg[i],i);
                                
                            }
                            item=select_food(restaurant_no,menu.fastfood);
                            // printf("%s\n",item.name);
                            return item;
                            break;
                        case 5:
                        printf("Sea food items:\n");
                            for (int i = 0; i < FOOD_EACH_CATEGORY/2; i++){
                                printFoodList(i+1,menu.seafood.veg[i],i);
                                
                            }
                            item=select_food(restaurant_no,menu.seafood);
                            // printf("%s\n",item.name);
                            return item;
                            break;
                        case 6:
                        printf("Break fast items:\n");
                            for (int i = 0; i < FOOD_EACH_CATEGORY/2; i++){
                                printFoodList(i+1,menu.breakfast.veg[i],i);
                                
                            }
                            item=select_food(restaurant_no,menu.breakfast);
                            // printf("%s\n",item.name);
                            return item;
                            break;
                        case 7:
                        printf("Mediterranean items:\n");
                            for (int i = 0; i < FOOD_EACH_CATEGORY/2; i++){
                                printFoodList(i+1,menu.mediterranean.veg[i],i);
                                
                            }
                            item=select_food(restaurant_no,menu.mediterranean);
                            // printf("%s\n",item.name);
                            return item;
                            break;
                        case 8:
                        printf("Vietnamese items:\n");
                            for (int i = 0; i < FOOD_EACH_CATEGORY/2; i++){
                                printFoodList(i+1,menu.vietnamese.veg[i],i);
                                
                            }
                            item=select_food(restaurant_no,menu.vietnamese);
                            // printf("%s\n",item.name);
                            return item;
                            break;
                        case 9:
                        printf("Italian items: \n");
                            for (int i = 0; i < FOOD_EACH_CATEGORY/2; i++){
                                printFoodList(i+1,menu.italian.veg[i],i);
                                
                            }
                            item=select_food(restaurant_no,menu.italian);
                            // printf("%s\n",item.name);
                            return item;
                            break;
                        case 10:
                        printf("Mexican:\n");
                            for (int i = 0; i < FOOD_EACH_CATEGORY/2; i++){
                                printFoodList(i+1,menu.mexican.veg[i],i);
                                
                            }
                            item=select_food(restaurant_no,menu.mexican);
                            // printf("%s\n",item.name);
                            return item;
                            break;
                        case 11:
                        printf("Thai:\n");
                            for (int i = 0; i < FOOD_EACH_CATEGORY/2; i++){
                                printFoodList(i+1,menu.thai.veg[i],i);
                                
                            }
                            item=select_food(restaurant_no,menu.thai);
                            // printf("%s\n",item.name);
                            return item;
                            break;
                        case 12:
                        printf("Japanese:\n");
                            for (int i = 0; i < FOOD_EACH_CATEGORY/2; i++){
                                printFoodList(i+1,menu.japanese.veg[i],i);
                                
                            }
                            item=select_food(restaurant_no,menu.japanese);
                            // printf("%s\n",item.name);
                            return item;
                            break;
                        case 13:
                        printf("Caribbean:\n");
                            for (int i = 0; i < FOOD_EACH_CATEGORY/2; i++){
                                printFoodList(i+1,menu.caribbean.veg[i],i);
                                
                            }
                            item=select_food(restaurant_no,menu.caribbean);
                            // printf("%s\n",item.name);
                            return item;
                            break;
                        case 14:
                        printf("Greek:\n");
                            for (int i = 0; i < FOOD_EACH_CATEGORY/2; i++){
                                printFoodList(i+1,menu.greek.veg[i],i);
                                
                            }
                            item=select_food(restaurant_no,menu.greek);
                            // printf("%s\n",item.name);
                            return item;
                            break;
                        case 15:
                        printf("French:\n");
                            for (int i = 0; i < FOOD_EACH_CATEGORY/2; i++){
                                printFoodList(i+1,menu.french.veg[i],i);
                                
                            }
                            item=select_food(restaurant_no,menu.french);
                            // printf("%s\n",item.name);
                            return item;
                            break;
                        case 16:
                        printf("Spanish:\n");
                            for (int i = 0; i < FOOD_EACH_CATEGORY/2; i++){
                                printFoodList(i+1,menu.spanish.veg[i],i);
                                
                            }
                            item=select_food(restaurant_no,menu.spanish);
                            // printf("%s\n",item.name);
                            return item;
                            break;
                        case 17:
                        printf("MIddle eastern:\n");
                            for (int i = 0; i < FOOD_EACH_CATEGORY/2; i++){
                                printFoodList(i+1,menu.middleEastern.veg[i],i);
                                
                            }
                            item=select_food(restaurant_no,menu.middleEastern);
                            // printf("%s\n",item.name);
                            return item;
                            break;
                        case 18:
                        printf("Korean:\n");
                            for (int i = 0; i < FOOD_EACH_CATEGORY/2; i++){
                                printFoodList(i+1,menu.korean.veg[i],i);
                                
                            }
                            item=select_food(restaurant_no,menu.korean);
                            // printf("%s\n",item.name);
                            return item;
                            break;
                        case 19:
                        printf("Turkish:\n");
                            for (int i = 0; i < FOOD_EACH_CATEGORY/2; i++){
                                printFoodList(i+1,menu.turkish.veg[i],i);
                                
                            }
                            item=select_food(restaurant_no,menu.turkish);
                            // printf("%s\n",item.name);
                            return item;
                            break;
                        case 20:
                        printf("Australian:\n");
                            for (int i = 0; i < FOOD_EACH_CATEGORY/2; i++){
                                printFoodList(i+1,menu.australian.veg[i],i);
                                
                            }
                            item=select_food(restaurant_no,menu.australian);
                            // printf("%s\n",item.name);
                            return item;
                            break;
                        case 21:
                        printf("Ethiopian:\n");
                            for (int i = 0; i < FOOD_EACH_CATEGORY/2; i++){
                                printFoodList(i+1,menu.ethiopian.veg[i],i);
                                
                            }
                            item=select_food(restaurant_no,menu.ethiopian);
                            // printf("%s\n",item.name);
                            return item;
                            break;
                        case 22:
                        printf("Moroccan:\n");
                            for (int i = 0; i < FOOD_EACH_CATEGORY/2; i++){
                                printFoodList(i+1,menu.moroccan.veg[i],i);
                                
                            }
                            item=select_food(restaurant_no,menu.moroccan);
                            // printf("%s\n",item.name);
                            return item;
                            break;
                        case 23:
                        printf("North Indian:\n");
                            for (int i = 0; i < FOOD_EACH_CATEGORY/2; i++){
                                printFoodList(i+1,menu.north_indian.veg[i],i);
                                
                            }
                            item=select_food(restaurant_no,menu.north_indian);
                            // printf("%s\n",item.name);
                            return item;
                            break;
                        case 24:
                        printf("South Indian:\n");
                            for (int i = 0; i < FOOD_EACH_CATEGORY/2; i++){
                                printFoodList(i+1,menu.south_indian.veg[i],i);
                                
                            }
                            item=select_food(restaurant_no,menu.south_indian);
                            // printf("%s\n",item.name);
                            return item;
                            break;
                        case 25:
                        printf("Beverages:\n");
                            for (int i = 0; i < FOOD_EACH_CATEGORY/2; i++){
                                printFoodList(i+1,menu.beverages.veg[i],i);
                                
                            }
                            item=select_food(restaurant_no,menu.beverages);
                            // printf("%s\n",item.name);
                            return item;
                            break;
                        case 26:
                        printf("Break fast:\n");
                            for (int i = 0; i < FOOD_EACH_CATEGORY/2; i++){
                                printFoodList(i+1,menu.breakfast.veg[i],i);
                                
                            }
                            item=select_food(restaurant_no,menu.breakfast);
                            // printf("%s\n",item.name);
                            return item;
                            break;
                        case 27:
                        printf("Snacks:\n");
                            for (int i = 0; i < FOOD_EACH_CATEGORY/2; i++){
                                printFoodList(i+1,menu.snacks.veg[i],i);
                                
                            }
                            item=select_food(restaurant_no,menu.snacks);
                            // printf("%s\n",item.name);
                            return item;
                            break;
                        case 28:
                        printf("American:\n");
                            for (int i = 0; i < FOOD_EACH_CATEGORY/2; i++){
                                printFoodList(i+1,menu.american.veg[i],i);
                                
                            }
                            item=select_food(restaurant_no,menu.american);
                            // printf("%s\n",item.name);
                            return item;
                            break;
                default:
                    break;
            }
        }else
        {
                switch (category_no)
                    {
                        case 1:
                            printf("Italian items:\n");
                            for (int i = 0; i < FOOD_EACH_CATEGORY; i++){
                                printFoodList(i+1,menu.italian.nonVeg[i],i);
                                
                            }
                            
                            item=select_food(restaurant_no,menu.italian);
                            // printf("%s\n",item.name);
                            return item;
                            break;
                        case 2:
                        printf("Chinese items:\n");
                            for (int i = 0; i < FOOD_EACH_CATEGORY; i++){
                                printFoodList(i+1,menu.chinese.nonVeg[i],i);
                                
                            }
                            
                            item=select_food(restaurant_no,menu.chinese);
                            // printf("%s\n",item.name);
                            return item;
                            break;
                        case 3:
                        printf("Tamil nadu items:\n");
                            for (int i = 0; i < FOOD_EACH_CATEGORY/2; i++){
                                printFoodList(i+1,menu.tamilnadu.nonVeg[i],i);
                                
                            }
                            
                            item=select_food(restaurant_no,menu.tamilnadu);
                            // printf("%s\n",item.name);
                            return item;
                            break;
                        case 4:
                        printf("Fast food items:\n");
                            for (int i = 0; i < FOOD_EACH_CATEGORY; i++){
                                printFoodList(i+1,menu.fastfood.nonVeg[i],i);
                                
                            }
                            
                            item=select_food(restaurant_no,menu.fastfood);
                            // printf("%s\n",item.name);
                            return item;
                            break;
                        case 5:
                        printf("Sea food items:\n");
                            for (int i = 0; i < FOOD_EACH_CATEGORY; i++){
                                printFoodList(i+1,menu.seafood.nonVeg[i],i);
                                
                            }
                            
                            item=select_food(restaurant_no,menu.seafood);
                            // printf("%s\n",item.name);
                            return item;
                            break;
                        case 6:
                        printf("Break fast items:\n");
                            for (int i = 0; i < FOOD_EACH_CATEGORY; i++){
                                printFoodList(i+1,menu.breakfast.nonVeg[i],i);
                                
                            }
                            
                            item=select_food(restaurant_no,menu.breakfast);
                            // printf("%s\n",item.name);
                            return item;
                            break;
                        case 7:
                        printf("Mediterranean items:\n");
                            for (int i = 0; i < FOOD_EACH_CATEGORY; i++){
                                printFoodList(i+1,menu.mediterranean.nonVeg[i],i);
                                
                            }
                            
                            item=select_food(restaurant_no,menu.mediterranean);
                            // printf("%s\n",item.name);
                            return item;
                            break;
                        case 8:
                        printf("Vietnamese items:\n");
                            for (int i = 0; i < FOOD_EACH_CATEGORY; i++){
                                printFoodList(i+1,menu.vietnamese.nonVeg[i],i);
                                
                            }
                            
                            item=select_food(restaurant_no,menu.vietnamese);
                            // printf("%s\n",item.name);
                            return item;
                            break;
                        case 9:
                        printf("Italian items: \n");
                            for (int i = 0; i < FOOD_EACH_CATEGORY; i++){
                                printFoodList(i+1,menu.italian.nonVeg[i],i);
                                
                            }
                            
                            item=select_food(restaurant_no,menu.italian);
                            // printf("%s\n",item.name);
                            return item;
                            break;
                        case 10:
                        printf("Mexican:\n");
                            for (int i = 0; i < FOOD_EACH_CATEGORY; i++){
                                printFoodList(i+1,menu.mexican.nonVeg[i],i);
                                
                            }
                            
                            item=select_food(restaurant_no,menu.mexican);
                            // printf("%s\n",item.name);
                            return item;
                            break;
                        case 11:
                        printf("Thai:\n");
                            for (int i = 0; i < FOOD_EACH_CATEGORY; i++){
                                printFoodList(i+1,menu.thai.nonVeg[i],i);
                                
                            }
                            
                            item=select_food(restaurant_no,menu.thai);
                            // printf("%s\n",item.name);
                            return item;
                            break;
                        case 12:
                        printf("Japanese:\n");
                            for (int i = 0; i < FOOD_EACH_CATEGORY; i++){
                                printFoodList(i+1,menu.japanese.nonVeg[i],i);
                                
                            }
                            
                            item=select_food(restaurant_no,menu.japanese);
                            // printf("%s\n",item.name);
                            return item;
                            break;
                        case 13:
                        printf("Caribbean:\n");
                            for (int i = 0; i < FOOD_EACH_CATEGORY; i++){
                                printFoodList(i+1,menu.caribbean.nonVeg[i],i);
                                
                            }
                            
                            item=select_food(restaurant_no,menu.caribbean);
                            // printf("%s\n",item.name);
                            return item;
                            break;
                        case 14:
                        printf("Greek:\n");
                            for (int i = 0; i < FOOD_EACH_CATEGORY; i++){
                                printFoodList(i+1,menu.greek.nonVeg[i],i);
                                
                            }
                            
                            item=select_food(restaurant_no,menu.greek);
                            // printf("%s\n",item.name);
                            return item;
                            break;
                        case 15:
                        printf("French:\n");
                            for (int i = 0; i < FOOD_EACH_CATEGORY; i++){
                                printFoodList(i+1,menu.french.nonVeg[i],i);
                                
                            }
                            
                            item=select_food(restaurant_no,menu.french);
                            // printf("%s\n",item.name);
                            return item;
                            break;
                        case 16:
                        printf("Spanish:\n");
                            for (int i = 0; i < FOOD_EACH_CATEGORY; i++){
                                printFoodList(i+1,menu.spanish.nonVeg[i],i);
                                
                            }
                            
                            item=select_food(restaurant_no,menu.spanish);
                            // printf("%s\n",item.name);
                            return item;
                            break;
                        case 17:
                        printf("MIddle eastern:\n");
                            for (int i = 0; i < FOOD_EACH_CATEGORY; i++){
                                printFoodList(i+1,menu.middleEastern.nonVeg[i],i);
                                
                            }
                            
                            item=select_food(restaurant_no,menu.middleEastern);
                            // printf("%s\n",item.name);
                            return item;
                            break;
                        case 18:
                        printf("Korean:\n");
                            for (int i = 0; i < FOOD_EACH_CATEGORY; i++){
                                printFoodList(i+1,menu.korean.nonVeg[i],i);
                                
                            }
                            
                            item=select_food(restaurant_no,menu.korean);
                            // printf("%s\n",item.name);
                            return item;
                            break;
                        case 19:
                        printf("Turkish:\n");
                            for (int i = 0; i < FOOD_EACH_CATEGORY; i++){
                                printFoodList(i+1,menu.turkish.nonVeg[i],i);
                                
                            }
                            
                            item=select_food(restaurant_no,menu.turkish);
                            // printf("%s\n",item.name);
                            return item;
                            break;
                        case 20:
                        printf("Australian:\n");
                            for (int i = 0; i < FOOD_EACH_CATEGORY; i++){
                                printFoodList(i+1,menu.australian.nonVeg[i],i);
                                
                            }
                            
                            item=select_food(restaurant_no,menu.australian);
                            // printf("%s\n",item.name);
                            return item;
                            break;
                        case 21:
                        printf("Ethiopian:\n");
                            for (int i = 0; i < FOOD_EACH_CATEGORY; i++){
                                printFoodList(i+1,menu.ethiopian.nonVeg[i],i);
                                
                            }
                            
                            item=select_food(restaurant_no,menu.ethiopian);
                            // printf("%s\n",item.name);
                            return item;
                            break;
                        case 22:
                        printf("Moroccan:\n");
                            for (int i = 0; i < FOOD_EACH_CATEGORY; i++){
                                printFoodList(i+1,menu.moroccan.nonVeg[i],i);
                                
                            }
                            
                            item=select_food(restaurant_no,menu.moroccan);
                            // printf("%s\n",item.name);
                            return item;
                            break;
                        case 23:
                        printf("North Indian:\n");
                            for (int i = 0; i < FOOD_EACH_CATEGORY; i++){
                                printFoodList(i+1,menu.north_indian.nonVeg[i],i);
                                
                            }
                            
                            item=select_food(restaurant_no,menu.north_indian);
                            // printf("%s\n",item.name);
                            return item;
                            break;
                        case 24:
                        printf("South Indian:\n");
                            for (int i = 0; i < FOOD_EACH_CATEGORY/2; i++){
                                printFoodList(i+1,menu.south_indian.nonVeg[i],i);
                                
                            }
                            
                            item=select_food(restaurant_no,menu.south_indian);
                            // printf("%s\n",item.name);
                            return item;
                            break;
                        case 25:
                        printf("Beverages:\n");
                            for (int i = 0; i < FOOD_EACH_CATEGORY; i++){
                                printFoodList(i+1,menu.beverages.nonVeg[i],i);
                                
                            }
                            
                            item=select_food(restaurant_no,menu.beverages);
                            // printf("%s\n",item.name);
                            return item;
                            break;
                        case 26:
                        printf("Break fast:\n");
                            for (int i = 0; i < FOOD_EACH_CATEGORY; i++){
                                printFoodList(i+1,menu.breakfast.nonVeg[i],i);
                                
                            }
                            
                            item=select_food(restaurant_no,menu.breakfast);
                            // printf("%s\n",item.name);
                            return item;
                            break;
                        case 27:
                        printf("Snacks:\n");
                            for (int i = 0; i < FOOD_EACH_CATEGORY; i++){
                                printFoodList(i+1,menu.snacks.nonVeg[i],i);
                                
                            }
                            
                            item=select_food(restaurant_no,menu.snacks);
                            // printf("%s\n",item.name);
                            return item;
                            break;
                        case 28:
                        printf("American:\n");
                            for (int i = 0; i < FOOD_EACH_CATEGORY; i++){
                                printFoodList(i+1,menu.american.nonVeg[i],i);
                                
                            }
                            
                            item=select_food(restaurant_no,menu.american);
                            
                            // printf("%s\n",item.name);
                            return item;
                            break;
                        default:
                            break;
                    }

        }
}

int remove_items(const char *filename, int target_line){
    int count = 1;
    FILE *file = fopen(filename, "r");
    if(file == NULL){
        printf("Error opening file\n");
        return 0;
    }
    FILE *temp = fopen("temp.txt", "w");
    if (temp == NULL)
    {
        printf("Error opening file\n");
        fclose(file);
        return 0;
    }

    FoodItemCart item;
    while (fscanf(file, "%s %s %f %s %s %f %d %d",item.username ,item.name, &item.price, item.category, item.type, &item.rating, &item.total_ratings,&item.count) == 8) {
        if (count != target_line) {
            fprintf(temp, "%s %s %.2f %s %s %.2f %d %d",item.username ,item.name, item.price, item.category, item.type, item.rating, item.total_ratings,item.count);
        }
        count++;
    }
    getchar();
    getchar();
    
    fclose(file);
    fclose(temp);

    temp = fopen("temp.txt", "r");
    if(file == NULL){
        print_error("Error opening file");
        return 0;
    }
    file = fopen(filename, "w");
    if (temp == NULL)
    {
        print_error("Error opening file");
        fclose(file);
        return 0;
    }

    while (fscanf(temp, "%s %s %f %s %s %f %d %d",item.username ,item.name, &item.price, item.category, item.type ,&item.rating, &item.total_ratings,&item.count) == 8) {
        fprintf(file, "%s %s %.2f %s %s %.2f %d %d\n",item.username ,item.name, item.price, item.category, item.type, item.rating, item.total_ratings,item.count);
    }

    fclose(file);
    fclose(temp);

    return 1;
}

int change_count(const char *filename, int target_line){
    char username[50];
    int count = 1;
    int quantity;

    if(readCurrentUser()==1){
        strcpy(username,current_user_details.username);
    }else{
        return 0;
    }
    FILE *file = fopen(filename, "r");
    if(file == NULL){
        print_error("Error opening file");
        return 0;
    }
    FILE *temp = fopen("temp.txt", "w");
    if (temp == NULL)
    {
        print_error("Error opening file");
        return 0;
    }

    FoodItemCart item;
    while (fscanf(file, "%s %s %f %s %s %f %d %d",item.username ,item.name, &item.price, item.category, item.type, &item.rating, &item.total_ratings,&item.count) == 8) {
        if (strcmp(item.username, username) == 0)
        {   
            if (target_line == count) {
                printf("Enter the quantity of the item: ");
                scanf("%d", &quantity);
                select_beep();
                fprintf(temp, "%s %s %.2f %s %s %.2f %d %d",item.username ,item.name, item.price, item.category, item.type, item.rating,item.total_ratings, quantity);
            }  else 
            {
                fprintf(temp, "%s %s %.2f %s %s %.2f %d %d\n", item.username, item.name, item.price, item.category, item.type, item.rating, item.total_ratings, item.count);
            }
            count++;
        }else 
        {
            fprintf(temp, "%s %s %.2f %s %s %.2f %d %d",item.username ,item.name, item.price, item.category, item.type, item.rating,item.total_ratings, item.count);
        }
        
    }

    fclose(file);
    fclose(temp);

    temp = fopen("temp.txt", "r");
    if(file == NULL){
        print_error("Error opening file");
        return 0;
    }
    file = fopen(filename, "w");
    if (temp == NULL)
    {
        print_error("Error opening file");
        fclose(file);
        return 0;
    }

    while (fscanf(temp, "%s %s %f %s %s %f %d %d", item.username ,item.name, &item.price, item.category, item.type ,&item.rating, &item.total_ratings,&item.count) == 8) {
        fprintf(file, "%s %s %.2f %s %s %.2f %d %d\n",item.username , item.name, item.price, item.category, item.type, item.rating, item.total_ratings,item.count);
    }

    fclose(file);
    fclose(temp);
    system("pause");
    return 1;
}
    

int view_cart(){
    system("cls");
    side_menu(-1);
    home();
    printUserDetails();
    float total_price=0;
    int total_count=1;
    char username[100];
    FILE *fp;
    fp = fopen("cart.txt", "r");
    if (fp == NULL) {
        print_error("ERROR: Could not open cart file\n");
        return 0;
    }
    if (readCurrentUser()==1)
    {
        strcpy(username,current_user_details.username);
    }else{
        return 0;
    }
    setCursor_inc(90,5);
    set_text_color(WHITE,GREEN);
    printf("              ");
    setCursor_inc(90,6);
    printf(" M Y  C A R T ");
    setCursor_inc(90,7);
    printf("              ");
    FoodItemCart item;
    // int counts=fscanf(fp, "%s %s %f %s %s %f %d %d",item.username ,item.name, &item.price, item.category, item.type, &item.rating, &item.total_ratings, &item.count);
    // printf("%d",counts);
    while (fscanf(fp, "%s %s %f %s %s %f %d %d",item.username ,item.name, &item.price, item.category, item.type, &item.rating, &item.total_ratings, &item.count) == 8) {
        {
            if (strcmp(item.username ,username)==0){
                printCartFood(total_count, item);
                total_price += item.price*item.count;
                total_count++;
            }
        }
        
    }
    setCursor_inc(80,50);
    set_text_color(WHITE, YELLOW);
    printf("                     ");
    setCursor_inc(80,51);
    printf(" TOTAL PRIE   $%.2f ", total_price);
    setCursor_inc(80,52);
    printf("                     ");
    set_text_color(WHITE, GREEN);
    setCursor_inc(110,50);
    printf("                    ");
    setCursor_inc(110,51);
    printf("     CHECK OUT      ");
    setCursor_inc(110,52);
    printf("                    ");
    set_text_color(CURRENT_FOREGROUND_COLOR, CURRENT_BACKGROUND_COLOR);
    printf("\n\n");
    fclose(fp);

    return 1;
}

int add_order_details(){
    float total_price=0;
    int total_count=1;
    char username[100];

    time_t now;
    time(&now);
    struct tm *local = localtime(&now);

    FILE *fp,*order_details_file;
    fp = fopen("cart.txt", "r");
    if (fp == NULL) {
        print_error("ERROR: Could not open cart file\n");
        return 0;
    }

    order_details_file = fopen("order_details.txt", "a");
    if (readCurrentUser()==1)
    {
        strcpy(username,current_user_details.username);
    }else{
        return 0;
    }
    FoodItemCart item;
    Order_details order_details[10];
    FoodItemCart cartItems[10];
    // int counts=fscanf(fp, "%s %s %f %s %s %f %d %d",item.username ,item.name, &item.price, item.category, item.type, &item.rating, &item.total_ratings, &item.count);
    // printf("%d",counts);
    int i=0;
    while (fscanf(fp, "%s %s %f %s %s %f %d %d",item.username ,item.name, &item.price, item.category, item.type, &item.rating, &item.total_ratings, &item.count) == 8) {
        {
            // printf("%s,%s,%s,%s,%f,%d,%02d-%02d-%d/%02d:%02d:%02d\n",item.username ,item.name, item.category, item.type, item.price,item.count,local->tm_mday, local->tm_mon + 1, local->tm_year + 1900, local->tm_hour, local->tm_min, local->tm_sec);
            // printf("-%s==%s-\n",item.username ,username);
            if (strcmp(item.username ,username)==0){
                char time[30];

                fprintf(order_details_file,"%s,%s,%s,%s,%f,%d,%02d-%02d-%d/%02d:%02d:%02d\n",item.username ,item.name, item.category, item.type, item.price,item.count,local->tm_mday, local->tm_mon + 1, local->tm_year + 1900, local->tm_hour, local->tm_min, local->tm_sec);

                total_price += item.price*item.count;
                total_count++;

            }else{
                strcpy(cartItems[i].username,item.username);
                strcpy(cartItems[i].name,item.name);
                strcpy(cartItems[i].category,item.category);
                strcpy(cartItems[i].type,item.type);
                cartItems[i].count = item.count;
                cartItems[i].price = item.price;
                cartItems[i].rating = item.rating;
                cartItems[i].total_ratings = item.total_ratings;
                i++;
            }
        }
        
    }
    fclose(fp);
    fclose(order_details_file);
    fp = fopen("cart.txt","w");
    if (fp == NULL) {
        print_error("ERROR: Could not open cart file\n");
        return 0;
    }
    for(int j=0; j<i ; j++){
        fprintf(fp, "%s %s %f %s %s %f %d %d\n",cartItems[j].username ,cartItems[j].name, cartItems[j].price, cartItems[j].category, cartItems[j].type, cartItems[j].rating, cartItems[j].total_ratings, cartItems[j].count);
    }
    fclose(fp);
    return 1;
}


int edit_cart(){
        int choice;
        int line_no;
        int x=85,y=0;
        setCursor_inc(x,y++);
        set_text_color(BLACK,YELLOW_BACKGROUND);
        printf("1.      Place order      ");
        setCursor_inc(x,y++);
        printf("2.      Change count     ");
        setCursor_inc(x,y++);
        printf("3.      Remove items     ");
        setCursor_inc(x,y++);
        printf("4.      Back             ");
        setCursor_inc(x,y++);
        printf("    Enter your choice:   ");
        set_text_color(BLACK,WHITE);
        scanf("%d", &choice);
        select_beep();

        switch (choice)
        {
        case 1:
            UserDeliveryInfo UserDeliveryInfo;
            UserDeliveryInfo = readUserDeliveryInfo();
            if(strcmp(user_delivery_info.address,"none")==0){
                print_error("Please add a delivery address");
                return 1;
            }
             if(payment()){
                if(add_order_details()){
                    return 2;
                }
             }
            break;
        case 2:
            printf("Enter the item to be updated: ");
            scanf("%d", &line_no);
            select_beep();

            if(change_count("cart.txt",line_no)==1){
                print_success("Quantity updated\n");
                view_cart();
            }else{
                print_success("Quantity not updated\n");
            }
            break;

        case 3:
            printf("Enter the item to be removed: ");
            scanf("%d", &line_no);
            select_beep();

            int res =remove_items("cart.txt",line_no);
            if(res==1){
                print_success("Item removed\n");
                view_cart();
            } else if(res==-1){ 
                print_error("Item not removed\n");
            }else{
                print_error("Item not found\n");
            }
            break;
        case 4:
            break;
        default:
            break;
        }   
        return 1;

}

void convertToLowerCase(char *sentence) {
    int i = 0;
    while (sentence[i] != '\0') {
        sentence[i] = tolower(sentence[i]);
        i++;
    }
}


FoodItem searchFoodItem(int restaurant_no, Menu menu) {
    int x = 100,y = 2;
    char ItemName[100]="";
    FILE *file = fopen("foods.txt", "r");
    if (file == NULL) {
        print_error("Error opening file");
    }
    char *type=restaurant_no==0? "veg" : "nonveg";
    char *type_token;
    char line[MAX_LINE_LENGTH];
    char *token;
    int item;
    int count;
    int found = 0;
    FoodItem food;
        system("cls");
        home();
        side_menu(-1);
        // home_page_banner();
        set_text_color(WHITE,DARK_GRAY);
        setCursor_inc(x,y++);
        printf("                                          ");
        setCursor_inc(x,y++);
        printf(" Search: ");
        set_text_color(BLACK,DARK_GRAY);
        printf("%15s               O-",ItemName);
        setCursor_inc(x,y++);
        set_text_color(BLACK,DARK_GRAY);
        printf("                                          ");
    while (1)
    {

        FoodItem food_list[5];
        found = 0;
        count =1;
        y=2;
        char ch  = _getch();
        if (ch==13)
        {
            int selected;
            printf("Enter your choice: ");
            scanf("%d",&selected);
            return food_list[selected-1];

        }else if (ch=='\b'){
            removeLastChar(ItemName);
        }else{
            strncat(ItemName, &ch, 1);
            convertToLowerCase(ItemName);
        }
        system("cls");
        home();
        side_menu(-1);
        // home_page_banner();
        set_text_color(WHITE,DARK_GRAY);
        setCursor_inc(x,y++);
        printf("                                          ");
        setCursor_inc(x,y++);
        printf(" Search: ");
        set_text_color(WHITE,DARK_GRAY);
        printf("%15s               O-",ItemName);
        setCursor_inc(x,y++);
        set_text_color(WHITE,DARK_GRAY);
        printf("                                          ");
        
        // Read each line of the file
        // convertToLowerCase(token);
        while (fgets(line, MAX_LINE_LENGTH, file) != NULL) {
            convertToLowerCase(line);
            if ((token = strstr(line, ItemName)) != NULL && (type_token = strstr(line, type)) != NULL) {
                sscanf(line,"%[^,],%f,%[^,],%[^,],%f,%d\n",food.name,&food.price,food.category,food.type,&food.rating,&food.total_ratings); // Print the line if the item name is found
                printFoodList(count,food,count-1);
                food_list[count-1] = food;
                count++;
                found = 1;
            }

            if (count ==5)
            {
                break;
            }
            
            
        }


        if (!found) {
            print_error("Item not found in the menu");
            fseek(file, 0, SEEK_SET); // Reset file pointer to the beginning

        }

    }
    fclose(file);
    return food;
}

// int main(){
//     foodItemsFunction();
//     return 0;
// }
int foodOrder() {

    int choice;
    Category food_category;
    int food_category_num;
    FoodItem food_selected;
    Menu menu;

    do
    {
        system("cls");
        home();
        printUserDetails();
        home_page_banner();
        set_text_color(BLACK,WHITE);
        int x=90,y=20;
        setCursor_inc(x,y++);
        printf("=========================");
        setCursor_inc(x,y++);
        printf("                        ");
        setCursor_inc(x,y++);
        printf("  1. Select Category    ");
        setCursor_inc(x,y++);
        printf("                        ");
        setCursor_inc(x,y++);
        printf("  2. Back               ");
        setCursor_inc(x,y++);
        printf("                        ");
        setCursor_inc(x,y++);
        printf("  3. Exit               ");
        setCursor_inc(x,y++);
        printf("                        ");
        setCursor_inc(x,y++);
        printf("=========================");
        setCursor_inc(x,y++);
        printf("Enter your choice: ");
        scanf("%d", &choice);
        select_beep();

        switch (choice) 
        {
            case 1:
                    menu = readMenuFromFile(&menu);
                    system("cls");
                    home();
                    side_menu(-1);
                    home_page_banner();
                    printUserDetails();
                    x=70,y=10;
                    setCursor_inc(x,y++);
                    set_text_color(BLACK,YELLOW);
                    printf("    ================  ");
                    setCursor_inc(x,y++);
                    printf("    1. Indian         ");
                    printf("    2. Chinese        ");
                    printf("    3. Tamil Nadu     ");
                    setCursor_inc(x,y++);
                    printf("    4. Fast Food      ");
                    printf("    5. Seafood        ");
                    printf("    6. Breakfast      ");
                    setCursor_inc(x,y++);
                    printf("    7. Mediterranean  ");
                    printf("    8. Vietnamese     ");
                    printf("    9. Italian        ");
                    setCursor_inc(x,y++);
                    printf("    10. Mexican       ");
                    printf("    11. Thai          ");
                    printf("    12. Japanese      ");
                    setCursor_inc(x,y++);
                    printf("    13. Caribbean     ");
                    printf("    14. Greek         ");
                    printf("    15. French        ");
                    setCursor_inc(x,y++);
                    printf("    16. Spanish       ");
                    printf("    17. Middle Eastern");
                    printf("    18. Korean        ");
                    setCursor_inc(x,y++);
                    printf("    19. Turkish       ");
                    printf("    20. Australian    ");
                    printf("    21. Ethiopian     ");
                    setCursor_inc(x,y++);
                    printf("    22. Moroccan      ");
                    printf("    23. North Indian  ");
                    printf("    24. South Indian  ");
                    setCursor_inc(x,y++);
                    printf("  25. Beverages  ");
                    printf("  26. Breakfast  ");
                    printf("  27. Snacks  ");
                    printf("  28. American  ");
                    setCursor_inc(x,y++);
                    printf("    Enter your choice: ");
                    scanf("%d", &food_category_num);
                    select_beep();
                    system("cls");
                    home();
                    printUserDetails();
                    home_page_banner();
                    food_selected=displayMenu(restaurant_no,food_category_num,menu);

                    system("cls");
                    home();
                    printUserDetails();
                    home_page_banner();
                    A:
                    printFoodItem(food_selected);
                    food_selected = addCartFunction(food_selected);
                    if(strcmp(food_selected.name,"none")!=0){
                        goto A;
                    }
                
                if(getchar()=='\n') {
                    break;
                }
                select_beep();

            case 2:
                system("cls");
                // restaurantsHomeFunction();
                return 2;
                // break;
            case 3:
                return 0;
            default:
                print_error("Invalid choice. Please try again.");

        
    }

    }while (1);
    return 0;
}
