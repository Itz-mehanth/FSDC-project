#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "settings.h"
#include "food_items.h"
#include "login.h"
#include "notification.h"
#include "theme.h"
#include "food_order_page.h"


Menu menu;

Category categories[MAX_CATEGORIES];


void initializeCategories(Menu *menu) {
    categories[0] = menu->indian;
    categories[1] = menu->chinese;
    categories[2] = menu->tamilnadu;
    categories[3] = menu->fastfood;
    categories[4] = menu->seafood;
    categories[5] = menu->breakfast;
    categories[6] = menu->mediterranean;
    categories[7] = menu->vietnamese;
    categories[8] = menu->italian;
    categories[9] = menu->mexican;
    categories[10] = menu->thai;
    categories[11] = menu->japanese;
    categories[12] = menu->caribbean;
    categories[13] = menu->greek;
    categories[14] = menu->french;
    categories[15] = menu->spanish;
    categories[16] = menu->middleEastern;
    categories[17] = menu->korean;
    categories[18] = menu->turkish;
    categories[19] = menu->australian;
    categories[20] = menu->ethiopian;
    categories[21] = menu->moroccan;
    categories[22] = menu->north_indian;
    categories[23] = menu->south_indian;
    categories[24] = menu->beverages;
    categories[25] = menu->breakfast;
    categories[26] = menu->snacks;
    categories[27] = menu->american;
}

void printMenu(const Menu *menu) {
    printf("---------- Menu ----------\n");

    // Indian
    printf("Indian:\n");
    printf("Vegetarian:\n");
    for (int i = 0; i < menu->indian.count_veg; ++i) {
        printf("%s - %.2f\n", menu->indian.veg[i].name, menu->indian.veg[i].price);
    }
    printf("Non-Vegetarian:\n");
    for (int i = 0; i < menu->indian.count_non_veg; ++i) {
        printf("%s - %.2f\n", menu->indian.nonVeg[i].name, menu->indian.nonVeg[i].price);
    }

    // Chinese
    printf("Chinese:\n");
    printf("Vegetarian:\n");
    for (int i = 0; i < menu->chinese.count_veg; ++i) {
        printf("%s - %.2f\n", menu->chinese.veg[i].name, menu->chinese.veg[i].price);
    }
    printf("Non-Vegetarian:\n");
    for (int i = 0; i < menu->chinese.count_non_veg; ++i) {
        printf("%s - %.2f\n", menu->chinese.nonVeg[i].name, menu->chinese.nonVeg[i].price);
    }

    // Japanese
    printf("Japanese:\n");
    printf("Vegetarian:\n");
    for (int i = 0; i < menu->japanese.count_veg; ++i) {
        printf("%s - %.2f\n", menu->japanese.veg[i].name, menu->japanese.veg[i].price);
    }
    printf("Non-Vegetarian:\n");
    for (int i = 0; i < menu->japanese.count_non_veg; ++i) {
        printf("%s - %.2f\n", menu->japanese.nonVeg[i].name, menu->japanese.nonVeg[i].price);
    }
    // Thai
    printf("Thai:\n");
    printf("Vegetarian:\n");
    for (int i = 0; i < menu->thai.count_veg; ++i) {
        printf("%s - %.2f\n", menu->thai.veg[i].name, menu->thai.veg[i].price);
    }
    printf("Non-Vegetarian:\n");
    for (int i = 0; i < menu->thai.count_non_veg; ++i) {
        printf("%s - %.2f\n", menu->thai.nonVeg[i].name, menu->thai.nonVeg[i].price);
    }

    // American
    printf("American:\n");
    printf("Vegetarian:\n");
    for (int i = 0; i < menu->american.count_veg; ++i) {
        printf("%s - %.2f\n", menu->american.veg[i].name, menu->american.veg[i].price);
    }
    printf("Non-Vegetarian:\n");
    for (int i = 0; i < menu->american.count_non_veg; ++i) {
        printf("%s - %.2f\n", menu->american.nonVeg[i].name, menu->american.nonVeg[i].price);
    }

    // Mexican
    printf("Mexican:\n");
    printf("Vegetarian:\n");
    for (int i = 0; i < menu->mexican.count_veg; ++i) {
        printf("%s - %.2f\n", menu->mexican.veg[i].name, menu->mexican.veg[i].price);
    }
    printf("Non-Vegetarian:\n");
    for (int i = 0; i < menu->mexican.count_non_veg; ++i) {
        printf("%s - %.2f\n", menu->mexican.nonVeg[i].name, menu->mexican.nonVeg[i].price);
    }

    // French
    printf("French:\n");
    printf("Vegetarian:\n");
    for (int i = 0; i < menu->french.count_veg; ++i) {
        printf("%s - %.2f\n", menu->french.veg[i].name, menu->french.veg[i].price);
    }
    printf("Non-Vegetarian:\n");
    for (int i = 0; i < menu->french.count_non_veg; ++i) {
        printf("%s - %.2f\n", menu->french.nonVeg[i].name, menu->french.nonVeg[i].price);
    }

    // Spanish
    printf("Spanish:\n");
    printf("Vegetarian:\n");
    for (int i = 0; i < menu->spanish.count_veg; ++i) {
        printf("%s - %.2f\n", menu->spanish.veg[i].name, menu->spanish.veg[i].price);
    }
    printf("Non-Vegetarian:\n");
    for (int i = 0; i < menu->spanish.count_non_veg; ++i) {
        printf("%s - %.2f\n", menu->spanish.nonVeg[i].name, menu->spanish.nonVeg[i].price);
    }

    // Greek
    printf("Greek:\n");
    printf("Vegetarian:\n");
    for (int i = 0; i < menu->greek.count_veg; ++i) {
        printf("%s - %.2f\n", menu->greek.veg[i].name, menu->greek.veg[i].price);
    }
    printf("Non-Vegetarian:\n");
    for (int i = 0; i < menu->greek.count_non_veg; ++i) {
        printf("%s - %.2f\n", menu->greek.nonVeg[i].name, menu->greek.nonVeg[i].price);
    }

    // _
    printf("_:\n");
    printf("Vegetarian:\n");
    for (int i = 0; i < menu->middleEastern.count_veg; ++i) {
        printf("%s - %.2f\n", menu->middleEastern.veg[i].name, menu->middleEastern.veg[i].price);
    }
    printf("Non-Vegetarian:\n");
    for (int i = 0; i < menu->middleEastern.count_non_veg; ++i) {
        printf("%s - %.2f\n", menu->middleEastern.nonVeg[i].name, menu->middleEastern.nonVeg[i].price);
    }

    // Korean
    printf("Korean:\n");
    printf("Vegetarian:\n");
    for (int i = 0; i < menu->korean.count_veg; ++i) {
        printf("%s - %.2f\n", menu->korean.veg[i].name, menu->korean.veg[i].price);
    }
    printf("Non-Vegetarian:\n");
    for (int i = 0; i < menu->korean.count_non_veg; ++i) {
        printf("%s - %.2f\n", menu->korean.nonVeg[i].name, menu->korean.nonVeg[i].price);
    }

    // Vietnamese
    printf("Vietnamese:\n");
    printf("Vegetarian:\n");
    for (int i = 0; i < menu->vietnamese.count_veg; ++i) {
        printf("%s - %.2f\n", menu->vietnamese.veg[i].name, menu->vietnamese.veg[i].price);
    }
    printf("Non-Vegetarian:\n");
    for (int i = 0; i < menu->vietnamese.count_non_veg; ++i) {
        printf("%s - %.2f\n", menu->vietnamese.nonVeg[i].name, menu->vietnamese.nonVeg[i].price);
    }

    // Brazilian
    printf("Brazilian:\n");
    printf("Vegetarian:\n");
    for (int i = 0; i < menu->brazilian.count_veg; ++i) {
        printf("%s - %.2f\n", menu->brazilian.veg[i].name, menu->brazilian.veg[i].price);
    }
    printf("Non-Vegetarian:\n");
    for (int i = 0; i < menu->brazilian.count_non_veg; ++i) {
        printf("%s - %.2f\n", menu->brazilian.nonVeg[i].name, menu->brazilian.nonVeg[i].price);
    }

    // Caribbean
    printf("Caribbean:\n");
    printf("Vegetarian:\n");
    for (int i = 0; i < menu->caribbean.count_veg; ++i) {
        printf("%s - %.2f\n", menu->caribbean.veg[i].name, menu->caribbean.veg[i].price);
    }
    printf("Non-Vegetarian:\n");
    for (int i = 0; i < menu->caribbean.count_non_veg; ++i) {
        printf("%s - %.2f\n", menu->caribbean.nonVeg[i].name, menu->caribbean.nonVeg[i].price);
    }

    // Mediterranean
    printf("Mediterranean:\n");
    printf("Vegetarian:\n");
    for (int i = 0; i < menu->mediterranean.count_veg; ++i) {
        printf("%s - %.2f\n", menu->mediterranean.veg[i].name, menu->mediterranean.veg[i].price);
    }
    printf("Non-Vegetarian:\n");
    for (int i = 0; i < menu->mediterranean.count_non_veg; ++i) {
        printf("%s - %.2f\n", menu->mediterranean.nonVeg[i].name, menu->mediterranean.nonVeg[i].price);
    }

    // Turkish
    printf("Turkish:\n");
    printf("Vegetarian:\n");
    for (int i = 0; i < menu->turkish.count_veg; ++i) {
        printf("%s - %.2f\n", menu->turkish.veg[i].name, menu->turkish.veg[i].price);
    }
    printf("Non-Vegetarian:\n");
    for (int i = 0; i < menu->turkish.count_non_veg; ++i) {
        printf("%s - %.2f\n", menu->turkish.nonVeg[i].name, menu->turkish.nonVeg[i].price);
    }

    // Moroccan
    printf("Moroccan:\n");
    printf("Vegetarian:\n");
    for (int i = 0; i < menu->moroccan.count_veg; ++i) {
        printf("%s - %.2f\n", menu->moroccan.veg[i].name, menu->moroccan.veg[i].price);
    }
    printf("Non-Vegetarian:\n");
    for (int i = 0; i < menu->moroccan.count_non_veg; ++i) {
        printf("%s - %.2f\n", menu->moroccan.nonVeg[i].name, menu->moroccan.nonVeg[i].price);
    }

    // Ethiopian
    printf("Ethiopian:\n");
    printf("Vegetarian:\n");
    for (int i = 0; i < menu->ethiopian.count_veg; ++i) {
        printf("%s - %.2f\n", menu->ethiopian.veg[i].name, menu->ethiopian.veg[i].price);
    }
    printf("Non-Vegetarian:\n");
    for (int i = 0; i < menu->ethiopian.count_non_veg; ++i) {
        printf("%s - %.2f\n", menu->ethiopian.nonVeg[i].name, menu->ethiopian.nonVeg[i].price);
    }

    // Australian
    printf("Australian:\n");
    printf("Vegetarian:\n");
    for (int i = 0; i < menu->australian.count_veg; ++i) {
        printf("%s - %.2f\n", menu->australian.veg[i].name, menu->australian.veg[i].price);
    }
    printf("Non-Vegetarian:\n");
    for (int i = 0; i < menu->australian.count_non_veg; ++i) {
        printf("%s - %.2f\n", menu->australian.nonVeg[i].name, menu->australian.nonVeg[i].price);
    }

    // North Indian
    printf("North Indian:\n");
    printf("Vegetarian:\n");
    for (int i = 0; i < menu->north_indian.count_veg; ++i) {
        printf("%s - %.2f\n", menu->north_indian.veg[i].name, menu->north_indian.veg[i].price);
    }
    printf("Non-Vegetarian:\n");
    for (int i = 0; i < menu->north_indian.count_non_veg; ++i) {
        printf("%s - %.2f\n", menu->north_indian.nonVeg[i].name, menu->north_indian.nonVeg[i].price);
    }

    // South Indian
    printf("South Indian:\n");
    printf("Vegetarian:\n");
    for (int i = 0; i < menu->south_indian.count_veg; ++i) {
        printf("%s - %.2f\n", menu->south_indian.veg[i].name, menu->south_indian.veg[i].price);
    }
    printf("Non-Vegetarian:\n");
    for (int i = 0; i < menu->south_indian.count_non_veg; ++i) {
        printf("%s - %.2f\n", menu->south_indian.nonVeg[i].name, menu->south_indian.nonVeg[i].price);
    }

    // Fast Food
    printf("Fast Food:\n");
    printf("Vegetarian:\n");
    for (int i = 0; i < menu->fastfood.count_veg; ++i) {
        printf("%s - %.2f\n", menu->fastfood.veg[i].name, menu->fastfood.veg[i].price);
    }
    printf("Non-Vegetarian:\n");
    for (int i = 0; i < menu->fastfood.count_non_veg; ++i) {
        printf("%s - %.2f\n", menu->fastfood.nonVeg[i].name, menu->fastfood.nonVeg[i].price);
    }

    // Seafood
    printf("Seafood:\n");
    printf("Vegetarian:\n");
    for (int i = 0; i < menu->seafood.count_veg; ++i) {
        printf("%s - %.2f\n", menu->seafood.veg[i].name, menu->seafood.veg[i].price);
    }
    printf("Non-Vegetarian:\n");
    for (int i = 0; i < menu->seafood.count_non_veg; ++i) {
        printf("%s - %.2f\n", menu->seafood.nonVeg[i].name, menu->seafood.nonVeg[i].price);
    }
    // Breakfast
    printf("Breakfast:\n");
    printf("Vegetarian:\n");
    for (int i = 0; i < menu->breakfast.count_veg; ++i) {
        printf("%s - %.2f\n", menu->breakfast.veg[i].name, menu->breakfast.veg[i].price);
    }
    printf("Non-Vegetarian:\n");
    for (int i = 0; i < menu->breakfast.count_non_veg; ++i) {
        printf("%s - %.2f\n", menu->breakfast.nonVeg[i].name, menu->breakfast.nonVeg[i].price);
    }

    // Snacks
    printf("Snacks:\n");
    printf("Vegetarian:\n");
    for (int i = 0; i < menu->snacks.count_veg; ++i) {
        printf("%s - %.2f\n", menu->snacks.veg[i].name, menu->snacks.veg[i].price);
    }
    printf("Non-Vegetarian:\n");
    for (int i = 0; i < menu->snacks.count_non_veg; ++i) {
        printf("%s - %.2f\n", menu->snacks.nonVeg[i].name, menu->snacks.nonVeg[i].price);
    }

    // Beverages
    printf("Beverages:\n");
    printf("Vegetarian:\n");
    for (int i = 0; i < menu->beverages.count_veg; ++i) {
        printf("%s - %.2f\n", menu->beverages.veg[i].name, menu->beverages.veg[i].price);
    }
    printf("Non-Vegetarian:\n");
    for (int i = 0; i < menu->beverages.count_non_veg; ++i) {
        printf("%s - %.2f\n", menu->beverages.nonVeg[i].name, menu->beverages.nonVeg[i].price);
    }

    // American
    printf("American:\n");
    printf("Vegetarian:\n");
    for (int i = 0; i < menu->american.count_veg; ++i) {
        printf("%s - %.2f\n", menu->american.veg[i].name, menu->american.veg[i].price);
    }
    printf("Non-Vegetarian:\n");
    for (int i = 0; i < menu->american.count_non_veg; ++i) {
        printf("%s - %.2f\n", menu->american.nonVeg[i].name, menu->american.nonVeg[i].price);
    }

    // Repeat the same structure for other cuisine categories...
    // Remember to replace placeholders like "Indian", "Chinese", etc., with the actual category names.

    printf("--------------------------\n");
}

void displayCategoryCounts(Menu *menu) {
    printf("Vegetarian counts:\n");
    printf("Indian: %d\n", menu->indian.count_veg);
    printf("Chinese: %d\n", menu->chinese.count_veg);
    printf("Tamilnadu: %d\n", menu->tamilnadu.count_veg);
    printf("Fast food: %d\n", menu->fastfood.count_veg);
    printf("Seafood: %d\n", menu->seafood.count_veg);
    printf("Breakfast: %d\n", menu->breakfast.count_veg);
    printf("Snacks: %d\n", menu->snacks.count_veg);
    printf("Mediterranean: %d\n", menu->mediterranean.count_veg);
    printf("Vietnamese: %d\n", menu->vietnamese.count_veg);
    printf("Italian: %d\n", menu->italian.count_veg);
    printf("Mexican: %d\n", menu->mexican.count_veg);
    printf("Thai: %d\n", menu->thai.count_veg);
    printf("Japanese: %d\n", menu->japanese.count_veg);
    printf("Caribbean: %d\n", menu->caribbean.count_veg);
    printf("Greek: %d\n", menu->greek.count_veg);
    printf("French: %d\n", menu->french.count_veg);
    printf("Spanish: %d\n", menu->spanish.count_veg);
    printf("Middle Eastern: %d\n", menu->middleEastern.count_veg);
    printf("Korean: %d\n", menu->korean.count_veg);
    printf("Turkish: %d\n", menu->turkish.count_veg);
    printf("Australian: %d\n", menu->australian.count_veg);
    printf("Ethiopian: %d\n", menu->ethiopian.count_veg);
    printf("Moroccan: %d\n", menu->moroccan.count_veg);
    printf("North Indian: %d\n", menu->north_indian.count_veg);
    printf("South Indian: %d\n", menu->south_indian.count_veg);
    printf("Beverages: %d\n", menu->beverages.count_veg);
    printf("Breakfast: %d\n", menu->breakfast.count_veg);
    printf("American: %d\n", menu->american.count_veg);

    printf("\nNon-Vegetarian counts:\n");
    printf("Indian: %d\n", menu->indian.count_non_veg);
    printf("Chinese: %d\n", menu->chinese.count_non_veg);
    printf("Tamilnadu: %d\n", menu->tamilnadu.count_non_veg);
    printf("Fast food: %d\n", menu->fastfood.count_non_veg);
    printf("Seafood: %d\n", menu->seafood.count_non_veg);
    printf("Breakfast: %d\n", menu->breakfast.count_non_veg);
    printf("Snacks: %d\n", menu->snacks.count_non_veg);
    printf("Mediterranean: %d\n", menu->mediterranean.count_non_veg);
    printf("Vietnamese: %d\n", menu->vietnamese.count_non_veg);
    printf("Italian: %d\n", menu->italian.count_non_veg);
    printf("Mexican: %d\n", menu->mexican.count_non_veg);
    printf("Thai: %d\n", menu->thai.count_non_veg);
    printf("Japanese: %d\n", menu->japanese.count_non_veg);
    printf("Caribbean: %d\n", menu->caribbean.count_non_veg);
    printf("Greek: %d\n", menu->greek.count_non_veg);
    printf("French: %d\n", menu->french.count_non_veg);
    printf("Spanish: %d\n", menu->spanish.count_non_veg);
    printf("Middle Eastern: %d\n", menu->middleEastern.count_non_veg);
    printf("Korean: %d\n", menu->korean.count_non_veg);
    printf("Turkish: %d\n", menu->turkish.count_non_veg);
    printf("Australian: %d\n", menu->australian.count_non_veg);
    printf("Ethiopian: %d\n", menu->ethiopian.count_non_veg);
    printf("Moroccan: %d\n", menu->moroccan.count_non_veg);
    printf("North Indian: %d\n", menu->north_indian.count_non_veg);
    printf("South Indian: %d\n", menu->south_indian.count_non_veg);
    printf("Beverages: %d\n", menu->beverages.count_non_veg);
    printf("Breakfast: %d\n", menu->breakfast.count_non_veg);
    printf("American: %d\n", menu->american.count_non_veg);
}


Menu readMenuFromFile(Menu *menu) {
    FILE *file = fopen("foods.txt", "r");
    FoodItem item;
    // Initialize counts for all categories
    menu->indian.count_veg = 0;
    menu->chinese.count_veg = 0;
    menu->tamilnadu.count_veg = 0;
    menu->fastfood.count_veg = 0;
    menu->seafood.count_veg = 0;
    menu->breakfast.count_veg = 0;
    menu->snacks.count_veg = 0;
    menu->mediterranean.count_veg = 0;
    menu->vietnamese.count_veg = 0;
    menu->italian.count_veg = 0;
    menu->mexican.count_veg = 0;
    menu->thai.count_veg = 0;
    menu->japanese.count_veg = 0;
    menu->caribbean.count_veg = 0;
    menu->greek.count_veg = 0;
    menu->french.count_veg = 0;
    menu->spanish.count_veg = 0;
    menu->middleEastern.count_veg = 0;
    menu->korean.count_veg = 0;
    menu->turkish.count_veg = 0;
    menu->australian.count_veg = 0;
    menu->ethiopian.count_veg = 0;
    menu->moroccan.count_veg = 0;
    menu->north_indian.count_veg = 0;
    menu->south_indian.count_veg = 0;
    menu->beverages.count_veg = 0;
    menu->breakfast.count_veg = 0;
    menu->american.count_veg = 0;
    menu->indian.count_non_veg = 0;
    menu->chinese.count_non_veg = 0;
    menu->tamilnadu.count_non_veg = 0;
    menu->fastfood.count_non_veg = 0;
    menu->seafood.count_non_veg = 0;
    menu->breakfast.count_non_veg = 0;
    menu->snacks.count_non_veg = 0;
    menu->mediterranean.count_non_veg = 0;
    menu->vietnamese.count_non_veg = 0;
    menu->italian.count_non_veg = 0;
    menu->mexican.count_non_veg = 0;
    menu->thai.count_non_veg = 0;
    menu->japanese.count_non_veg = 0;
    menu->caribbean.count_non_veg = 0;
    menu->greek.count_non_veg = 0;
    menu->french.count_non_veg = 0;
    menu->spanish.count_non_veg = 0;
    menu->middleEastern.count_non_veg = 0;
    menu->korean.count_non_veg = 0;
    menu->turkish.count_non_veg = 0;
    menu->australian.count_non_veg = 0;
    menu->ethiopian.count_non_veg = 0;
    menu->moroccan.count_non_veg = 0;
    menu->north_indian.count_non_veg = 0;
    menu->south_indian.count_non_veg = 0;
    menu->beverages.count_non_veg = 0;
    menu->breakfast.count_non_veg = 0;
    menu->american.count_non_veg = 0;

    while (fscanf(file, "%[^,],%f,%[^,],%[^,],%f,%d,%f\n", item.name, &item.price, item.category, item.type,&item.rating,&item.total_ratings,&item.current_user_rating) == 7) {
        if (strcmp(item.category, "Italian") == 0) {
            if (strcmp(item.type, "Veg") == 0) {
                memcpy(&menu->italian.veg[menu->italian.count_veg], &item, sizeof(FoodItem));
                menu->italian.count_veg++;
            } 
           
                memcpy(&menu->italian.nonVeg[menu->italian.count_non_veg], &item, sizeof(FoodItem));
                menu->italian.count_non_veg++;
           
        } else if (strcmp(item.category, "Indian") == 0) {
            if (strcmp(item.type, "Veg") == 0) {
                memcpy(&menu->indian.veg[menu->indian.count_veg], &item, sizeof(FoodItem));
                menu->indian.count_veg++;
            } 
           
                memcpy(&menu->indian.nonVeg[menu->indian.count_non_veg], &item, sizeof(FoodItem));
                menu->indian.count_non_veg++;
           
        } else if (strcmp(item.category, "Chinese") == 0) {
            if (strcmp(item.type, "Veg") == 0) {
                memcpy(&menu->chinese.veg[menu->chinese.count_veg], &item, sizeof(FoodItem));
                menu->chinese.count_veg++;
            } 
           
                memcpy(&menu->chinese.nonVeg[menu->chinese.count_non_veg], &item, sizeof(FoodItem));
                menu->chinese.count_non_veg++;
           
        } else if (strcmp(item.category, "Japanese") == 0) {
            if (strcmp(item.type, "Veg") == 0) {
                memcpy(&menu->japanese.veg[menu->japanese.count_veg], &item, sizeof(FoodItem));
                menu->japanese.count_veg++;
            } 
           
                memcpy(&menu->japanese.nonVeg[menu->japanese.count_non_veg], &item, sizeof(FoodItem));
                menu->japanese.count_non_veg++;
           
        }else if (strcmp(item.category, "Thai") == 0) {
            if (strcmp(item.type, "Veg") == 0) {
                memcpy(&menu->thai.veg[menu->thai.count_veg], &item, sizeof(FoodItem));
                menu->thai.count_veg++;
            } 
           
                memcpy(&menu->thai.nonVeg[menu->thai.count_non_veg], &item, sizeof(FoodItem));
                menu->thai.count_non_veg++;
           
        } else if (strcmp(item.category, "American") == 0) {
            if (strcmp(item.type, "Veg") == 0) {
                memcpy(&menu->american.veg[menu->american.count_veg], &item, sizeof(FoodItem));
                menu->american.count_veg++;
            } 
           
                memcpy(&menu->american.nonVeg[menu->american.count_non_veg], &item, sizeof(FoodItem));
                menu->american.count_non_veg++;
           
        } else if (strcmp(item.category, "Mexican") == 0) {
            if (strcmp(item.type, "Veg") == 0) {
                memcpy(&menu->mexican.veg[menu->mexican.count_veg], &item, sizeof(FoodItem));
                menu->mexican.count_veg++;
            } 
           
                memcpy(&menu->mexican.nonVeg[menu->mexican.count_non_veg], &item, sizeof(FoodItem));
                menu->mexican.count_non_veg++;
           
        } else if (strcmp(item.category, "French") == 0) {
            if (strcmp(item.type, "Veg") == 0) {
                memcpy(&menu->french.veg[menu->french.count_veg], &item, sizeof(FoodItem));
                menu->french.count_veg++;
            } 
           
                memcpy(&menu->french.nonVeg[menu->french.count_non_veg], &item, sizeof(FoodItem));
                menu->french.count_non_veg++;
           
        } else if (strcmp(item.category, "Spanish") == 0) {
            if (strcmp(item.type, "Veg") == 0) {
                memcpy(&menu->spanish.veg[menu->spanish.count_veg], &item, sizeof(FoodItem));
                menu->spanish.count_veg++;
            } 
           
                memcpy(&menu->spanish.nonVeg[menu->spanish.count_non_veg], &item, sizeof(FoodItem));
                menu->spanish.count_non_veg++;
           
        } else if (strcmp(item.category, "Greek") == 0) {
            if (strcmp(item.type, "Veg") == 0) {
                memcpy(&menu->greek.veg[menu->greek.count_veg], &item, sizeof(FoodItem));
                menu->greek.count_veg++;
            } 
           
                memcpy(&menu->greek.nonVeg[menu->greek.count_non_veg], &item, sizeof(FoodItem));
                menu->greek.count_non_veg++;
           
        }else if (strcmp(item.category, "Middle_Eastern") == 0) {
            if (strcmp(item.type, "Veg") == 0) {
                memcpy(&menu->middleEastern.veg[menu->middleEastern.count_veg], &item, sizeof(FoodItem));
                menu->middleEastern.count_veg++;
            } 
           
                memcpy(&menu->middleEastern.nonVeg[menu->middleEastern.count_non_veg], &item, sizeof(FoodItem));
                menu->middleEastern.count_non_veg++;
           
        } else if (strcmp(item.category, "Korean") == 0) {
            if (strcmp(item.type, "Veg") == 0) {
                memcpy(&menu->korean.veg[menu->korean.count_veg], &item, sizeof(FoodItem));
                menu->korean.count_veg++;
            } 
           
                memcpy(&menu->korean.nonVeg[menu->korean.count_non_veg], &item, sizeof(FoodItem));
                menu->korean.count_non_veg++;
           
        } else if (strcmp(item.category, "Vietnamese") == 0) {
            if (strcmp(item.type, "Veg") == 0) {
                memcpy(&menu->vietnamese.veg[menu->vietnamese.count_veg], &item, sizeof(FoodItem));
                menu->vietnamese.count_veg++;
            } 
           
                memcpy(&menu->vietnamese.nonVeg[menu->vietnamese.count_non_veg], &item, sizeof(FoodItem));
                menu->vietnamese.count_non_veg++;
           
        } else if (strcmp(item.category, "Brazilian") == 0) {
            if (strcmp(item.type, "Veg") == 0) {
                memcpy(&menu->brazilian.veg[menu->brazilian.count_veg], &item, sizeof(FoodItem));
                menu->brazilian.count_veg++;
            } 
           
                memcpy(&menu->brazilian.nonVeg[menu->brazilian.count_non_veg], &item, sizeof(FoodItem));
                menu->brazilian.count_non_veg++;
           
        } else if (strcmp(item.category, "Caribbean") == 0) {
            if (strcmp(item.type, "Veg") == 0) {
                memcpy(&menu->caribbean.veg[menu->caribbean.count_veg], &item, sizeof(FoodItem));
                menu->caribbean.count_veg++;
            } 
           
                memcpy(&menu->caribbean.nonVeg[menu->caribbean.count_non_veg], &item, sizeof(FoodItem));
                menu->caribbean.count_non_veg++;
           
        } else if (strcmp(item.category, "Mediterranean") == 0) {
            if (strcmp(item.type, "Veg") == 0) {
                memcpy(&menu->mediterranean.veg[menu->mediterranean.count_veg], &item, sizeof(FoodItem));
                menu->mediterranean.count_veg++;
            } 
           
                memcpy(&menu->mediterranean.nonVeg[menu->mediterranean.count_non_veg], &item, sizeof(FoodItem));
                menu->mediterranean.count_non_veg++;
           
        } else if (strcmp(item.category, "Turkish") == 0) {
            if (strcmp(item.type, "Veg") == 0) {
                memcpy(&menu->turkish.veg[menu->turkish.count_veg], &item, sizeof(FoodItem));
                menu->turkish.count_veg++;
            } 
           
                memcpy(&menu->turkish.nonVeg[menu->turkish.count_non_veg], &item, sizeof(FoodItem));
                menu->turkish.count_non_veg++;
           
        } else if (strcmp(item.category, "Moroccan") == 0) {
            if (strcmp(item.type, "Veg") == 0) {
                memcpy(&menu->moroccan.veg[menu->moroccan.count_veg], &item, sizeof(FoodItem));
                menu->moroccan.count_veg++;
            } 
           
                memcpy(&menu->moroccan.nonVeg[menu->moroccan.count_non_veg], &item, sizeof(FoodItem));
                menu->moroccan.count_non_veg++;
           
        } else if (strcmp(item.category, "Ethiopian") == 0) {
            if (strcmp(item.type, "Veg") == 0) {
                memcpy(&menu->ethiopian.veg[menu->ethiopian.count_veg], &item, sizeof(FoodItem));
                menu->ethiopian.count_veg++;
            } 
           
                memcpy(&menu->ethiopian.nonVeg[menu->ethiopian.count_non_veg], &item, sizeof(FoodItem));
                menu->ethiopian.count_non_veg++;
           
        } else if (strcmp(item.category, "Australian") == 0) {
            if (strcmp(item.type, "Veg") == 0) {
                memcpy(&menu->australian.veg[menu->australian.count_veg], &item, sizeof(FoodItem));
                menu->australian.count_veg++;
            } 
           
                memcpy(&menu->australian.nonVeg[menu->australian.count_non_veg], &item, sizeof(FoodItem));
                menu->australian.count_non_veg++;
           
        } else if (strcmp(item.category, "NorthIndian") == 0) {
            if (strcmp(item.type, "Veg") == 0) {
                memcpy(&menu->north_indian.veg[menu->north_indian.count_veg], &item, sizeof(FoodItem));
                menu->north_indian.count_veg++;
            } 
           
                memcpy(&menu->north_indian.nonVeg[menu->north_indian.count_non_veg], &item, sizeof(FoodItem));
                menu->north_indian.count_non_veg++;
           
        } else if (strcmp(item.category, "SouthIndian") == 0) {
            if (strcmp(item.type, "Veg") == 0) {
                memcpy(&menu->south_indian.veg[menu->south_indian.count_veg], &item, sizeof(FoodItem));
                menu->south_indian.count_veg++;
            } 
           
                memcpy(&menu->south_indian.nonVeg[menu->south_indian.count_non_veg], &item, sizeof(FoodItem));
                menu->south_indian.count_non_veg++;
           
        } else if (strcmp(item.category, "FastFood") == 0) {
            if (strcmp(item.type, "Veg") == 0) {
                memcpy(&menu->fastfood.veg[menu->fastfood.count_veg], &item, sizeof(FoodItem));
                menu->fastfood.count_veg++;
            } 
           
                memcpy(&menu->fastfood.nonVeg[menu->fastfood.count_non_veg], &item, sizeof(FoodItem));
                menu->fastfood.count_non_veg++;
           
        } else if (strcmp(item.category, "Seafood") == 0) {
            if (strcmp(item.type, "Veg") == 0) {
                memcpy(&menu->seafood.veg[menu->seafood.count_veg], &item, sizeof(FoodItem));
                menu->seafood.count_veg++;
            } 
           
                memcpy(&menu->seafood.nonVeg[menu->seafood.count_non_veg], &item, sizeof(FoodItem));
                menu->seafood.count_non_veg++;
           
        } else if (strcmp(item.category, "Breakfast") == 0) {
            if (strcmp(item.type, "Veg") == 0) {
                memcpy(&menu->breakfast.veg[menu->breakfast.count_veg], &item, sizeof(FoodItem));
                menu->breakfast.count_veg++;
            } 
           
                memcpy(&menu->breakfast.nonVeg[menu->breakfast.count_non_veg], &item, sizeof(FoodItem));
                menu->breakfast.count_non_veg++;
           
        } else if (strcmp(item.category, "Snacks") == 0) {
            if (strcmp(item.type, "Veg") == 0) {
                memcpy(&menu->snacks.veg[menu->snacks.count_veg], &item, sizeof(FoodItem));
                menu->snacks.count_veg++;
            } 
           
                memcpy(&menu->snacks.nonVeg[menu->snacks.count_non_veg], &item, sizeof(FoodItem));
                menu->snacks.count_non_veg++;
           
        } else if (strcmp(item.category, "Beverages") == 0) {
            if (strcmp(item.type, "Veg") == 0) {
                memcpy(&menu->beverages.veg[menu->beverages.count_veg], &item, sizeof(FoodItem));
                menu->beverages.count_veg++;
            } 
           
                memcpy(&menu->beverages.nonVeg[menu->beverages.count_non_veg], &item, sizeof(FoodItem));
                menu->beverages.count_non_veg++;
           
        } else if (strcmp(item.category, "TamilNadu") == 0) {
            if (strcmp(item.type, "Veg") == 0) {
                memcpy(&menu->tamilnadu.veg[menu->tamilnadu.count_veg], &item, sizeof(FoodItem));
                menu->tamilnadu.count_veg++;
            } 
           
                memcpy(&menu->tamilnadu.nonVeg[menu->tamilnadu.count_non_veg], &item, sizeof(FoodItem));
                menu->tamilnadu.count_non_veg++;
           
        }
    }
    print_success("starting initialisation");

    initializeCategories(menu);

    fclose(file);

    return *menu;
}

// Function to compare food items by rating for qsort
int compareByWeightedRating(const void *a, const void *b) {
    const FoodItem *itemA = (const FoodItem *)a;
    const FoodItem *itemB = (const FoodItem *)b;

    // Calculate weighted rating for item A
    double weightedRatingA = ((double)itemA->total_ratings / (itemA->total_ratings + MIN_VOTES)) * itemA->rating 
                           + ((double)MIN_VOTES / (itemA->total_ratings + MIN_VOTES)) * MIN_RATING;

    // Calculate weighted rating for item B
    double weightedRatingB = ((double)itemB->total_ratings / (itemB->total_ratings + MIN_VOTES)) * itemB->rating 
                           + ((double)MIN_VOTES / (itemB->total_ratings + MIN_VOTES)) * MIN_RATING;

    // Compare by weighted rating in descending order
    if (weightedRatingA < weightedRatingB)
        return 1;
    else if (weightedRatingA > weightedRatingB)
        return -1;
    else
        return 0;
}

// Function to sort food items by rating
void sortFoodItemsByRating(FoodItem items[], int count) {
    qsort(items, count, sizeof(FoodItem), compareByWeightedRating);
}

// Function to display the most popular food items by rating
void displayPopularItems(Menu menu) {
    FoodItem allItems[400]; // Assuming MAX_ITEMS and MAX_CATEGORIES are defined
    int totalItemCount = 0;
    readMenuFromFile(&menu);
    // Iterate through each category and copy food items into allItems array
    set_text_color(YELLOW,RED);
    for (int i = 0; i < MAX_CATEGORIES; i++) {
        Category category = categories[i];
        if (veg_mode)
        {
            for (int j = 0; j < category.count_veg; j++) {
                allItems[totalItemCount++] = category.veg[j];
            }
        }else{

            for (int j = 0; j < category.count_non_veg; j++) {
                allItems[totalItemCount++] = category.nonVeg[j];
            }

        }
        
    }
    

    // Sort all food items by rating
    sortFoodItemsByRating(allItems, totalItemCount);
    // Display the top-rated items
    setCursor_inc(95,24);
    set_text_color(YELLOW,RED);
    printf("Most Popular Food Items:\n");
    for (int i = 0; i < totalItemCount && i < 5; i++) { 
        printPopularFoodList(i+1,allItems[i],i);
        // printf("%d. Name: %s, Category: %s, Rating: %.2f", i+1, allItems[i].name, allItems[i].category, allItems[i].rating);
    }

}

void loadFoodItems(FoodItem items[], int *count) {
    FILE *file = fopen("foods.txt", "r");
    if (!file) {
        perror("Failed to open foods.txt");
        return;
    }

    *count = 0;
    while (fscanf(file, "%[^,],%f,%[^,],%[^,],%f,%d,%f\n",
                  items[*count].name,
                  &items[*count].price,
                  items[*count].category,
                  items[*count].type,
                  &items[*count].rating,
                  &items[*count].total_ratings,
                  &items[*count].current_user_rating) == 7) {
        (*count)++;
    }

    fclose(file);
}

void updateRatings(FoodItem items[], int count) {
    FILE *file = fopen("ratings.txt", "r");
    if (!file) {
        perror("Failed to open ratings.txt");
        return;
    }

    char username[50];
    char foodname[50];
    float rating;

    while (fscanf(file, "%[^,],%[^,],%f\n", username, foodname, &rating) == 3) {
        for (int i = 0; i < count; i++) {
            if (strcmp(items[i].name, foodname) == 0) {
                items[i].current_user_rating = rating;
                break;
            }
        }
    }

    fclose(file);
}

void saveFoodItems(FoodItem items[], int count) {
    FILE *file = fopen("foods.txt", "w");
    if (!file) {
        perror("Failed to open foods.txt");
        return;
    }

    for (int i = 0; i < count; i++) {
        fprintf(file, "%s,%.2f,%s,%s,%.2f,%d,%.2f\n",
                items[i].name,
                items[i].price,
                items[i].category,
                items[i].type,
                items[i].rating,
                items[i].total_ratings,
                items[i].current_user_rating);
    }

    fclose(file);
}

int updateCurrentUserFoodRatings() {
    FoodItem items[TOTAL_FOOD_ITEMS];
    int count;

    // Load food items from foods.txt
    loadFoodItems(items, &count);
    // printf("food loaded successfully\n");
    // Update ratings based on ratings.txt
    updateRatings(items, count);
    // printf("updated ratings in the menu successfully\n");

    // Save updated food items back to foods.txt
    saveFoodItems(items, count);
    // printf("updated ratings in the file successfully\n");

    return 0;
}

