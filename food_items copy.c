#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "food_items.h"
#include "notification.h"


#define MAX_ITEMS 30
#define MAX_CATEGORIES 13
#define MAX_NAME_LENGTH 50
#define MAX_CATEGORY_LENGTH 30
#define MAX_TYPE_LENGTH 20

Menu menu;

typedef struct {
    char name[MAX_NAME_LENGTH];
    float price;
    float rating;
    int total_ratings;
    char category[MAX_CATEGORY_LENGTH];
    char type[MAX_TYPE_LENGTH];
} FoodItem;

typedef struct {
    FoodItem veg[MAX_ITEMS];
    FoodItem nonVeg[MAX_ITEMS];
    char name[MAX_NAME_LENGTH];
    int count; // Variable to keep track of the number of items in the category
} Category;

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
    Category french;
    Category breakfast;
    Category snacks;
} Menu;

void initializeMenu(Menu *menu) {
    FILE *file = fopen("food_items.txt", "r");
    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }

    FoodItem item;
    while (fscanf(file, "%[^,],%f,%[^,],%[^,],%f,%d\n", item.name, &item.price, item.category, item.type,item.rating,item.total_ratings) == 6) {
        if (strcmp(item.category, "Italian") == 0) {
            if (strcmp(item.type, "Veg") == 0) {
                strcpy(menu->italian.veg[menu->italian.count].name, item.name);
                menu->italian.veg[menu->italian.count].price = item.price;
                strcpy(menu->italian.veg[menu->italian.count].category, item.category);
                menu->italian.veg[menu->italian.count].rating = item.rating;
                menu->italian.veg[menu->italian.count].total_ratings = item.total_ratings;
                strcpy(menu->italian.veg[menu->italian.count].type ,item.type);
                menu->italian.count++;
            } else if (strcmp(item.type, "NonVeg") == 0) {
                strcpy(menu->italian.nonVeg[menu->italian.count].name, item.name);
                menu->italian.nonVeg[menu->italian.count].price = item.price;
                strcpy(menu->italian.nonVeg[menu->italian.count].category, item.category);
                menu->italian.nonVeg[menu->italian.count].rating = item.rating;
                menu->italian.nonVeg[menu->italian.count].total_ratings = item.total_ratings;
                strcpy(menu->italian.nonVeg[menu->italian.count].type ,item.type);
                menu->italian.count++;
            }
        } else if (strcmp(item.category, "Indian") == 0) {
            if (strcmp(item.type, "Veg") == 0) {
                strcpy(menu->indian.veg[menu->indian.count].name, item.name);
                menu->indian.veg[menu->indian.count].price = item.price;
                strcpy(menu->indian.veg[menu->indian.count].category, item.category);
                menu->indian.veg[menu->indian.count].rating = item.rating;
                menu->indian.veg[menu->indian.count].total_ratings = item.total_ratings;
                strcpy(menu->indian.veg[menu->indian.count].type ,item.type);
                menu->indian.count++;
            } else if (strcmp(item.type, "NonVeg") == 0) {
                strcpy(menu->indian.nonVeg[menu->indian.count].name, item.name);
                menu->indian.nonVeg[menu->indian.count].price = item.price;
                strcpy(menu->indian.nonVeg[menu->indian.count].category, item.category);
                menu->indian.nonVeg[menu->indian.count].rating = item.rating;
                menu->indian.nonVeg[menu->indian.count].total_ratings = item.total_ratings;
                strcpy(menu->indian.nonVeg[menu->indian.count].type ,item.type);
                menu->indian.count++;
            }
        }else if (strcmp(item.category, "Chinese") == 0) {
            if (strcmp(item.type, "Veg") == 0) {
                strcpy(menu->chinese.veg[menu->chinese.count].name, item.name);
                menu->chinese.veg[menu->chinese.count].price = item.price;
                strcpy(menu->chinese.veg[menu->chinese.count].category, item.category);
                menu->chinese.veg[menu->chinese.count].rating = item.rating;
                menu->chinese.veg[menu->chinese.count].total_ratings = item.total_ratings;
                strcpy(menu->chinese.veg[menu->chinese.count].type ,item.type);
                menu->chinese.count++;
            } else if (strcmp(item.type, "NonVeg") == 0) {
                strcpy(menu->chinese.nonVeg[menu->chinese.count].name, item.name);
                menu->chinese.nonVeg[menu->chinese.count].price = item.price;
                strcpy(menu->chinese.nonVeg[menu->chinese.count].category, item.category);
                menu->chinese.nonVeg[menu->chinese.count].rating = item.rating;
                menu->chinese.nonVeg[menu->chinese.count].total_ratings = item.total_ratings;
                strcpy(menu->chinese.nonVeg[menu->chinese.count].type ,item.type);
                menu->chinese.count++;
            }
        }else if (strcmp(item.category, "Japanese") == 0) {
            if (strcmp(item.type, "Veg") == 0) {
                strcpy(menu->japanese.veg[menu->japanese.count].name, item.name);
                menu->japanese.veg[menu->japanese.count].price = item.price;
                strcpy(menu->japanese.veg[menu->japanese.count].category, item.category);
                menu->japanese.veg[menu->japanese.count].rating = item.rating;
                menu->japanese.veg[menu->japanese.count].total_ratings = item.total_ratings;
                strcpy(menu->japanese.veg[menu->japanese.count].type ,item.type);
                menu->japanese.count++;
            } else if (strcmp(item.type, "NonVeg") == 0) {
                strcpy(menu->japanese.nonVeg[menu->japanese.count].name, item.name);
                menu->japanese.nonVeg[menu->japanese.count].price = item.price;
                strcpy(menu->japanese.nonVeg[menu->japanese.count].category, item.category);
                menu->japanese.nonVeg[menu->japanese.count].rating = item.rating;
                menu->japanese.nonVeg[menu->japanese.count].total_ratings = item.total_ratings;
                strcpy(menu->japanese.nonVeg[menu->japanese.count].type ,item.type);
                menu->japanese.count++;
            }
        }else if (strcmp(item.category, "Thai") == 0) {
            if (strcmp(item.type, "Veg") == 0) {
                strcpy(menu->thai.veg[menu->thai.count].name, item.name);
                menu->thai.veg[menu->thai.count].price = item.price;
                strcpy(menu->thai.veg[menu->thai.count].category, item.category);
                menu->thai.veg[menu->thai.count].rating = item.rating;
                menu->thai.veg[menu->thai.count].total_ratings = item.total_ratings;
                strcpy(menu->thai.veg[menu->thai.count].type ,item.type);
                menu->thai.count++;
            } else if (strcmp(item.type, "NonVeg") == 0) {
                strcpy(menu->thai.nonVeg[menu->thai.count].name, item.name);
                menu->thai.nonVeg[menu->thai.count].price = item.price;
                strcpy(menu->thai.nonVeg[menu->thai.count].category, item.category);
                menu->thai.nonVeg[menu->thai.count].rating = item.rating;
                menu->thai.nonVeg[menu->thai.count].total_ratings = item.total_ratings;
                strcpy(menu->thai.nonVeg[menu->thai.count].type ,item.type);
                menu->thai.count++;
            }
        }else if (strcmp(item.category, "Mexican") == 0) {
            if (strcmp(item.type, "Veg") == 0) {
                strcpy(menu->mexican.veg[menu->mexican.count].name, item.name);
                menu->mexican.veg[menu->mexican.count].price = item.price;
                strcpy(menu->mexican.veg[menu->mexican.count].category, item.category);
                menu->mexican.veg[menu->mexican.count].rating = item.rating;
                menu->mexican.veg[menu->mexican.count].total_ratings = item.total_ratings;
                strcpy(menu->mexican.veg[menu->mexican.count].type ,item.type);
                menu->mexican.count++;
            } else if (strcmp(item.type, "NonVeg") == 0) {
                strcpy(menu->mexican.nonVeg[menu->mexican.count].name, item.name);
                menu->mexican.nonVeg[menu->mexican.count].price = item.price;
                strcpy(menu->mexican.nonVeg[menu->mexican.count].category, item.category);
                menu->mexican.nonVeg[menu->mexican.count].rating = item.rating;
                menu->mexican.nonVeg[menu->mexican.count].total_ratings = item.total_ratings;
                strcpy(menu->mexican.nonVeg[menu->mexican.count].type ,item.type);
                menu->mexican.count++;
            }
        }else if (strcmp(item.category, "American") == 0) {
            if (strcmp(item.type, "Veg") == 0) {
                strcpy(menu->american.veg[menu->american.count].name, item.name);
                menu->american.veg[menu->american.count].price = item.price;
                strcpy(menu->american.veg[menu->american.count].category, item.category);
                menu->american.veg[menu->american.count].rating = item.rating;
                menu->american.veg[menu->american.count].total_ratings = item.total_ratings;
                strcpy(menu->american.veg[menu->american.count].type ,item.type);
                menu->american.count++;
            } else if (strcmp(item.type, "NonVeg") == 0) {
                strcpy(menu->american.nonVeg[menu->american.count].name, item.name);
                menu->american.nonVeg[menu->american.count].price = item.price;
                strcpy(menu->american.nonVeg[menu->american.count].category, item.category);
                menu->american.nonVeg[menu->american.count].rating = item.rating;
                menu->american.nonVeg[menu->american.count].total_ratings = item.total_ratings;
                strcpy(menu->american.nonVeg[menu->american.count].type ,item.type);
                menu->american.count++;
            }
        }else if (strcmp(item.category, "French") == 0) {
            if (strcmp(item.type, "Veg") == 0) {
                strcpy(menu->french.veg[menu->french.count].name, item.name);
                menu->french.veg[menu->french.count].price = item.price;
                strcpy(menu->french.veg[menu->french.count].category, item.category);
                menu->french.veg[menu->french.count].rating = item.rating;
                menu->french.veg[menu->french.count].total_ratings = item.total_ratings;
                strcpy(menu->french.veg[menu->french.count].type ,item.type);
                menu->french.count++;
            } else if (strcmp(item.type, "NonVeg") == 0) {
                strcpy(menu->french.nonVeg[menu->french.count].name, item.name);
                menu->french.nonVeg[menu->french.count].price = item.price;
                strcpy(menu->french.nonVeg[menu->french.count].category, item.category);
                menu->french.nonVeg[menu->french.count].rating = item.rating;
                menu->french.nonVeg[menu->french.count].total_ratings = item.total_ratings;
                strcpy(menu->french.nonVeg[menu->french.count].type ,item.type);
                menu->french.count++;
            }
        }else if (strcmp(item.category, "Spanish") == 0) {
            if (strcmp(item.type, "Veg") == 0) {
                strcpy(menu->.veg[menu->.count].name, item.name);
                menu->.veg[menu->.count].price = item.price;
                strcpy(menu->.veg[menu->.count].category, item.category);
                menu->.veg[menu->.count].rating = item.rating;
                menu->.veg[menu->.count].total_ratings = item.total_ratings;
                strcpy(menu->.veg[menu->.count].type ,item.type);
                menu->.count++;
            } else if (strcmp(item.type, "NonVeg") == 0) {
                strcpy(menu->.nonVeg[menu->.count].name, item.name);
                menu->.nonVeg[menu->.count].price = item.price;
                strcpy(menu->.nonVeg[menu->.count].category, item.category);
                menu->.nonVeg[menu->.count].rating = item.rating;
                menu->.nonVeg[menu->.count].total_ratings = item.total_ratings;
                strcpy(menu->.nonVeg[menu->.count].type ,item.type);
                menu->.count++;
            }
        }else if (strcmp(item.category, "Greek") == 0) {
            if (strcmp(item.type, "Veg") == 0) {
                strcpy(menu->greek.veg[menu->greek.count].name, item.name);
                menu->greek.veg[menu->greek.count].price = item.price;
                strcpy(menu->greek.veg[menu->greek.count].category, item.category);
                menu->greek.veg[menu->greek.count].rating = item.rating;
                menu->greek.veg[menu->greek.count].total_ratings = item.total_ratings;
                strcpy(menu->greek.veg[menu->greek.count].type ,item.type);
                menu->greek.count++;
            } else if (strcmp(item.type, "NonVeg") == 0) {
                strcpy(menu->greek.nonVeg[menu->greek.count].name, item.name);
                menu->greek.nonVeg[menu->greek.count].price = item.price;
                strcpy(menu->greek.nonVeg[menu->greek.count].category, item.category);
                menu->greek.nonVeg[menu->greek.count].rating = item.rating;
                menu->greek.nonVeg[menu->greek.count].total_ratings = item.total_ratings;
                strcpy(menu->greek.nonVeg[menu->greek.count].type ,item.type);
                menu->greek.count++;
            }
        }else if (strcmp(item.category, "Mid_east") == 0) {
            if (strcmp(item.type, "Veg") == 0) {
                strcpy(menu->middleEastern.veg[menu->middleEastern.count].name, item.name);
                menu->middleEastern.veg[menu->middleEastern.count].price = item.price;
                strcpy(menu->middleEastern.veg[menu->middleEastern.count].category, item.category);
                menu->middleEastern.veg[menu->middleEastern.count].rating = item.rating;
                menu->middleEastern.veg[menu->middleEastern.count].total_ratings = item.total_ratings;
                strcpy(menu->middleEastern.veg[menu->middleEastern.count].type ,item.type);
                menu->middleEastern.count++;
            } else if (strcmp(item.type, "NonVeg") == 0) {
                strcpy(menu->middleEastern.nonVeg[menu->middleEastern.count].name, item.name);
                menu->middleEastern.nonVeg[menu->middleEastern.count].price = item.price;
                strcpy(menu->middleEastern.nonVeg[menu->middleEastern.count].category, item.category);
                menu->middleEastern.nonVeg[menu->middleEastern.count].rating = item.rating;
                menu->middleEastern.nonVeg[menu->middleEastern.count].total_ratings = item.total_ratings;
                strcpy(menu->middleEastern.nonVeg[menu->middleEastern.count].type ,item.type);
                menu->middleEastern.count++;
            }
        }else if (strcmp(item.category, "Korean") == 0) {
            if (strcmp(item.type, "Veg") == 0) {
                strcpy(menu->korean.veg[menu->korean.count].name, item.name);
                menu->korean.veg[menu->korean.count].price = item.price;
                strcpy(menu->korean.veg[menu->korean.count].category, item.category);
                menu->korean.veg[menu->korean.count].rating = item.rating;
                menu->korean.veg[menu->korean.count].total_ratings = item.total_ratings;
                strcpy(menu->korean.veg[menu->korean.count].type ,item.type);
                menu->korean.count++;
            } else if (strcmp(item.type, "NonVeg") == 0) {
                strcpy(menu->korean.nonVeg[menu->korean.count].name, item.name);
                menu->korean.nonVeg[menu->korean.count].price = item.price;
                strcpy(menu->korean.nonVeg[menu->korean.count].category, item.category);
                menu->korean.nonVeg[menu->korean.count].rating = item.rating;
                menu->korean.nonVeg[menu->korean.count].total_ratings = item.total_ratings;
                strcpy(menu->korean.nonVeg[menu->korean.count].type ,item.type);
                menu->korean.count++;
            }
        }else if (strcmp(item.category, "Vietnamese") == 0) {
            if (strcmp(item.type, "Veg") == 0) {
                strcpy(menu->vietnamese.veg[menu->vietnamese.count].name, item.name);
                menu->vietnamese.veg[menu->vietnamese.count].price = item.price;
                strcpy(menu->vietnamese.veg[menu->vietnamese.count].category, item.category);
                menu->vietnamese.veg[menu->vietnamese.count].rating = item.rating;
                menu->vietnamese.veg[menu->vietnamese.count].total_ratings = item.total_ratings;
                strcpy(menu->vietnamese.veg[menu->vietnamese.count].type ,item.type);
                menu->vietnamese.count++;
            } else if (strcmp(item.type, "NonVeg") == 0) {
                strcpy(menu->vietnamese.nonVeg[menu->vietnamese.count].name, item.name);
                menu->vietnamese.nonVeg[menu->vietnamese.count].price = item.price;
                strcpy(menu->vietnamese.nonVeg[menu->vietnamese.count].category, item.category);
                menu->vietnamese.nonVeg[menu->vietnamese.count].rating = item.rating;
                menu->vietnamese.nonVeg[menu->vietnamese.count].total_ratings = item.total_ratings;
                strcpy(menu->vietnamese.nonVeg[menu->vietnamese.count].type ,item.type);
                menu->vietnamese.count++;
            }
        }else if (strcmp(item.category, "Brazilian") == 0) {
            if (strcmp(item.type, "Veg") == 0) {
                strcpy(menu->brazilian.veg[menu->brazilian.count].name, item.name);
                menu->brazilian.veg[menu->brazilian.count].price = item.price;
                strcpy(menu->brazilian.veg[menu->brazilian.count].category, item.category);
                menu->brazilian.veg[menu->brazilian.count].rating = item.rating;
                menu->brazilian.veg[menu->brazilian.count].total_ratings = item.total_ratings;
                strcpy(menu->brazilian.veg[menu->brazilian.count].type ,item.type);
                menu->brazilian.count++;
            } else if (strcmp(item.type, "NonVeg") == 0) {
                strcpy(menu->brazilian.nonVeg[menu->brazilian.count].name, item.name);
                menu->brazilian.nonVeg[menu->brazilian.count].price = item.price;
                strcpy(menu->brazilian.nonVeg[menu->brazilian.count].category, item.category);
                menu->brazilian.nonVeg[menu->brazilian.count].rating = item.rating;
                menu->brazilian.nonVeg[menu->brazilian.count].total_ratings = item.total_ratings;
                strcpy(menu->brazilian.nonVeg[menu->brazilian.count].type ,item.type);
                menu->brazilian.count++;
            }
        }else if (strcmp(item.category, "Caribbean") == 0) {
            if (strcmp(item.type, "Veg") == 0) {
                strcpy(menu->caribbean.veg[menu->caribbean.count].name, item.name);
                menu->caribbean.veg[menu->caribbean.count].price = item.price;
                strcpy(menu->caribbean.veg[menu->caribbean.count].category, item.category);
                menu->caribbean.veg[menu->caribbean.count].rating = item.rating;
                menu->caribbean.veg[menu->caribbean.count].total_ratings = item.total_ratings;
                strcpy(menu->caribbean.veg[menu->caribbean.count].type ,item.type);
                menu->caribbean.count++;
            } else if (strcmp(item.type, "NonVeg") == 0) {
                strcpy(menu->caribbean.nonVeg[menu->caribbean.count].name, item.name);
                menu->caribbean.nonVeg[menu->caribbean.count].price = item.price;
                strcpy(menu->caribbean.nonVeg[menu->caribbean.count].category, item.category);
                menu->caribbean.nonVeg[menu->caribbean.count].rating = item.rating;
                menu->caribbean.nonVeg[menu->caribbean.count].total_ratings = item.total_ratings;
                strcpy(menu->caribbean.nonVeg[menu->caribbean.count].type ,item.type);
                menu->caribbean.count++;
            }
        }else if (strcmp(item.category, "Mediterranean") == 0) {
            if (strcmp(item.type, "Veg") == 0) {
                strcpy(menu->mediterranean.veg[menu->mediterranean.count].name, item.name);
                menu->mediterranean.veg[menu->mediterranean.count].price = item.price;
                strcpy(menu->mediterranean.veg[menu->mediterranean.count].category, item.category);
                menu->mediterranean.veg[menu->mediterranean.count].rating = item.rating;
                menu->mediterranean.veg[menu->mediterranean.count].total_ratings = item.total_ratings;
                strcpy(menu->mediterranean.veg[menu->mediterranean.count].type ,item.type);
                menu->mediterranean.count++;
            } else if (strcmp(item.type, "NonVeg") == 0) {
                strcpy(menu->mediterranean.nonVeg[menu->mediterranean.count].name, item.name);
                menu->mediterranean.nonVeg[menu->mediterranean.count].price = item.price;
                strcpy(menu->mediterranean.nonVeg[menu->mediterranean.count].category, item.category);
                menu->mediterranean.nonVeg[menu->mediterranean.count].rating = item.rating;
                menu->mediterranean.nonVeg[menu->mediterranean.count].total_ratings = item.total_ratings;
                strcpy(menu->mediterranean.nonVeg[menu->mediterranean.count].type ,item.type);
                menu->mediterranean.count++;
            }
        }else if (strcmp(item.category, "Turkish") == 0) {
            if (strcmp(item.type, "Veg") == 0) {
                strcpy(menu->turkish.veg[menu->turkish.count].name, item.name);
                menu->turkish.veg[menu->turkish.count].price = item.price;
                strcpy(menu->turkish.veg[menu->turkish.count].category, item.category);
                menu->turkish.veg[menu->turkish.count].rating = item.rating;
                menu->turkish.veg[menu->turkish.count].total_ratings = item.total_ratings;
                strcpy(menu->turkish.veg[menu->turkish.count].type ,item.type);
                menu->turkish.count++;
            } else if (strcmp(item.type, "NonVeg") == 0) {
                strcpy(menu->turkish.nonVeg[menu->turkish.count].name, item.name);
                menu->turkish.nonVeg[menu->turkish.count].price = item.price;
                strcpy(menu->turkish.nonVeg[menu->turkish.count].category, item.category);
                menu->turkish.nonVeg[menu->turkish.count].rating = item.rating;
                menu->turkish.nonVeg[menu->turkish.count].total_ratings = item.total_ratings;
                strcpy(menu->turkish.nonVeg[menu->turkish.count].type ,item.type);
                menu->turkish.count++;
            }
        }else if (strcmp(item.category, "Moroccan") == 0) {
            if (strcmp(item.type, "Veg") == 0) {
                strcpy(menu->moroccan.veg[menu->moroccan.count].name, item.name);
                menu->moroccan.veg[menu->moroccan.count].price = item.price;
                strcpy(menu->moroccan.veg[menu->moroccan.count].category, item.category);
                menu->moroccan.veg[menu->moroccan.count].rating = item.rating;
                menu->moroccan.veg[menu->moroccan.count].total_ratings = item.total_ratings;
                strcpy(menu->moroccan.veg[menu->moroccan.count].type ,item.type);
                menu->moroccan.count++;
            } else if (strcmp(item.type, "NonVeg") == 0) {
                strcpy(menu->moroccan.nonVeg[menu->moroccan.count].name, item.name);
                menu->moroccan.nonVeg[menu->moroccan.count].price = item.price;
                strcpy(menu->moroccan.nonVeg[menu->moroccan.count].category, item.category);
                menu->moroccan.nonVeg[menu->moroccan.count].rating = item.rating;
                menu->moroccan.nonVeg[menu->moroccan.count].total_ratings = item.total_ratings;
                strcpy(menu->moroccan.nonVeg[menu->moroccan.count].type ,item.type);
                menu->moroccan.count++;
            }
        }else if (strcmp(item.category, "Ethiopian") == 0) {
            if (strcmp(item.type, "Veg") == 0) {
                strcpy(menu->ethiopian.veg[menu->ethiopian.count].name, item.name);
                menu->ethiopian.veg[menu->ethiopian.count].price = item.price;
                strcpy(menu->ethiopian.veg[menu->ethiopian.count].category, item.category);
                menu->ethiopian.veg[menu->ethiopian.count].rating = item.rating;
                menu->ethiopian.veg[menu->ethiopian.count].total_ratings = item.total_ratings;
                strcpy(menu->ethiopian.veg[menu->ethiopian.count].type ,item.type);
                menu->ethiopian.count++;
            } else if (strcmp(item.type, "NonVeg") == 0) {
                strcpy(menu->ethiopian.nonVeg[menu->ethiopian.count].name, item.name);
                menu->ethiopian.nonVeg[menu->ethiopian.count].price = item.price;
                strcpy(menu->ethiopian.nonVeg[menu->ethiopian.count].category, item.category);
                menu->ethiopian.nonVeg[menu->ethiopian.count].rating = item.rating;
                menu->ethiopian.nonVeg[menu->ethiopian.count].total_ratings = item.total_ratings;
                strcpy(menu->ethiopian.nonVeg[menu->ethiopian.count].type ,item.type);
                menu->ethiopian.count++;
            }
        }else if (strcmp(item.category, "Australian") == 0) {
            if (strcmp(item.type, "Veg") == 0) {
                strcpy(menu->australian.veg[menu->australian.count].name, item.name);
                menu->australian.veg[menu->australian.count].price = item.price;
                strcpy(menu->australian.veg[menu->australian.count].category, item.category);
                menu->australian.veg[menu->australian.count].rating = item.rating;
                menu->australian.veg[menu->australian.count].total_ratings = item.total_ratings;
                strcpy(menu->australian.veg[menu->australian.count].type ,item.type);
                menu->australian.count++;
            } else if (strcmp(item.type, "NonVeg") == 0) {
                strcpy(menu->australian.nonVeg[menu->australian.count].name, item.name);
                menu->australian.nonVeg[menu->australian.count].price = item.price;
                strcpy(menu->australian.nonVeg[menu->australian.count].category, item.category);
                menu->australian.nonVeg[menu->australian.count].rating = item.rating;
                menu->australian.nonVeg[menu->australian.count].total_ratings = item.total_ratings;
                strcpy(menu->australian.nonVeg[menu->australian.count].type ,item.type);
                menu->australian.count++;
            }
        }else if (strcmp(item.category, "North_indian") == 0) {
            if (strcmp(item.type, "Veg") == 0) {
                strcpy(menu->north_indian.veg[menu->north_indian.count].name, item.name);
                menu->north_indian.veg[menu->north_indian.count].price = item.price;
                strcpy(menu->north_indian.veg[menu->north_indian.count].category, item.category);
                menu->north_indian.veg[menu->north_indian.count].rating = item.rating;
                menu->north_indian.veg[menu->north_indian.count].total_ratings = item.total_ratings;
                strcpy(menu->north_indian.veg[menu->north_indian.count].type ,item.type);
                menu->north_indian.count++;
            } else if (strcmp(item.type, "NonVeg") == 0) {
                strcpy(menu->north_indian.nonVeg[menu->north_indian.count].name, item.name);
                menu->north_indian.nonVeg[menu->north_indian.count].price = item.price;
                strcpy(menu->north_indian.nonVeg[menu->north_indian.count].category, item.category);
                menu->north_indian.nonVeg[menu->north_indian.count].rating = item.rating;
                menu->north_indian.nonVeg[menu->north_indian.count].total_ratings = item.total_ratings;
                strcpy(menu->north_indian.nonVeg[menu->north_indian.count].type ,item.type);
                menu->north_indian.count++;
            }
        }else if (strcmp(item.category, "South_indian") == 0) {
            if (strcmp(item.type, "Veg") == 0) {
                strcpy(menu->south_indian.veg[menu->south_indian.count].name, item.name);
                menu->south_indian.veg[menu->south_indian.count].price = item.price;
                strcpy(menu->south_indian.veg[menu->south_indian.count].category, item.category);
                menu->south_indian.veg[menu->south_indian.count].rating = item.rating;
                menu->south_indian.veg[menu->south_indian.count].total_ratings = item.total_ratings;
                strcpy(menu->south_indian.veg[menu->south_indian.count].type ,item.type);
                menu->south_indian.count++;
            } else if (strcmp(item.type, "NonVeg") == 0) {
                strcpy(menu->south_indian.nonVeg[menu->south_indian.count].name, item.name);
                menu->south_indian.nonVeg[menu->south_indian.count].price = item.price;
                strcpy(menu->south_indian.nonVeg[menu->south_indian.count].category, item.category);
                menu->south_indian.nonVeg[menu->south_indian.count].rating = item.rating;
                menu->south_indian.nonVeg[menu->south_indian.count].total_ratings = item.total_ratings;
                strcpy(menu->south_indian.nonVeg[menu->south_indian.count].type ,item.type);
                menu->south_indian.count++;
            }
        }else if (strcmp(item.category, "Tamilnadu") == 0) {
            if (strcmp(item.type, "Veg") == 0) {
                strcpy(menu->tamilnadu.veg[menu->tamilnadu.count].name, item.name);
                menu->tamilnadu.veg[menu->tamilnadu.count].price = item.price;
                strcpy(menu->tamilnadu.veg[menu->tamilnadu.count].category, item.category);
                menu->tamilnadu.veg[menu->tamilnadu.count].rating = item.rating;
                menu->tamilnadu.veg[menu->tamilnadu.count].total_ratings = item.total_ratings;
                strcpy(menu->tamilnadu.veg[menu->tamilnadu.count].type ,item.type);
                menu->tamilnadu.count++;
            } else if (strcmp(item.type, "NonVeg") == 0) {
                strcpy(menu->tamilnadu.nonVeg[menu->tamilnadu.count].name, item.name);
                menu->tamilnadu.nonVeg[menu->tamilnadu.count].price = item.price;
                strcpy(menu->tamilnadu.nonVeg[menu->tamilnadu.count].category, item.category);
                menu->tamilnadu.nonVeg[menu->tamilnadu.count].rating = item.rating;
                menu->tamilnadu.nonVeg[menu->tamilnadu.count].total_ratings = item.total_ratings;
                strcpy(menu->tamilnadu.nonVeg[menu->tamilnadu.count].type ,item.type);
                menu->tamilnadu.count++;
            }
        }else if (strcmp(item.category, "Fastfood") == 0) {
            if (strcmp(item.type, "Veg") == 0) {
                strcpy(menu->fastfood.veg[menu->fastfood.count].name, item.name);
                menu->fastfood.veg[menu->fastfood.count].price = item.price;
                strcpy(menu->fastfood.veg[menu->fastfood.count].category, item.category);
                menu->fastfood.veg[menu->fastfood.count].rating = item.rating;
                menu->fastfood.veg[menu->fastfood.count].total_ratings = item.total_ratings;
                strcpy(menu->fastfood.veg[menu->fastfood.count].type ,item.type);
                menu->fastfood.count++;
            } else if (strcmp(item.type, "NonVeg") == 0) {
                strcpy(menu->fastfood.nonVeg[menu->fastfood.count].name, item.name);
                menu->fastfood.nonVeg[menu->fastfood.count].price = item.price;
                strcpy(menu->fastfood.nonVeg[menu->fastfood.count].category, item.category);
                menu->fastfood.nonVeg[menu->fastfood.count].rating = item.rating;
                menu->fastfood.nonVeg[menu->fastfood.count].total_ratings = item.total_ratings;
                strcpy(menu->fastfood.nonVeg[menu->fastfood.count].type ,item.type);
                menu->fastfood.count++;
            }
        }else if (strcmp(item.category, "Seafood") == 0) {
            if (strcmp(item.type, "Veg") == 0) {
                strcpy(menu->seafood.veg[menu->seafood.count].name, item.name);
                menu->seafood.veg[menu->seafood.count].price = item.price;
                strcpy(menu->seafood.veg[menu->seafood.count].category, item.category);
                menu->seafood.veg[menu->seafood.count].rating = item.rating;
                menu->seafood.veg[menu->seafood.count].total_ratings = item.total_ratings;
                strcpy(menu->seafood.veg[menu->seafood.count].type ,item.type);
                menu->seafood.count++;
            } else if (strcmp(item.type, "NonVeg") == 0) {
                strcpy(menu->seafood.nonVeg[menu->seafood.count].name, item.name);
                menu->seafood.nonVeg[menu->seafood.count].price = item.price;
                strcpy(menu->seafood.nonVeg[menu->seafood.count].category, item.category);
                menu->seafood.nonVeg[menu->seafood.count].rating = item.rating;
                menu->seafood.nonVeg[menu->seafood.count].total_ratings = item.total_ratings;
                strcpy(menu->seafood.nonVeg[menu->seafood.count].type ,item.type);
                menu->seafood.count++;
            }
        }else if (strcmp(item.category, "Breakfast") == 0) {
            if (strcmp(item.type, "Veg") == 0) {
                strcpy(menu->breakfast.veg[menu->breakfast.count].name, item.name);
                menu->breakfast.veg[menu->breakfast.count].price = item.price;
                strcpy(menu->breakfast.veg[menu->breakfast.count].category, item.category);
                menu->breakfast.veg[menu->breakfast.count].rating = item.rating;
                menu->breakfast.veg[menu->breakfast.count].total_ratings = item.total_ratings;
                strcpy(menu->breakfast.veg[menu->breakfast.count].type ,item.type);
                menu->breakfast.count++;
            } else if (strcmp(item.type, "NonVeg") == 0) {
                strcpy(menu->breakfast.nonVeg[menu->breakfast.count].name, item.name);
                menu->breakfast.nonVeg[menu->breakfast.count].price = item.price;
                strcpy(menu->breakfast.nonVeg[menu->breakfast.count].category, item.category);
                menu->breakfast.nonVeg[menu->breakfast.count].rating = item.rating;
                menu->breakfast.nonVeg[menu->breakfast.count].total_ratings = item.total_ratings;
                strcpy(menu->breakfast.nonVeg[menu->breakfast.count].type ,item.type);
                menu->breakfast.count++;
            }
        }else if (strcmp(item.category, "Snacks") == 0) {
            if (strcmp(item.type, "Veg") == 0) {
                strcpy(menu->snacks.veg[menu->snacks.count].name, item.name);
                menu->snacks.veg[menu->snacks.count].price = item.price;
                strcpy(menu->snacks.veg[menu->snacks.count].category, item.category);
                menu->snacks.veg[menu->snacks.count].rating = item.rating;
                menu->snacks.veg[menu->snacks.count].total_ratings = item.total_ratings;
                strcpy(menu->snacks.veg[menu->snacks.count].type ,item.type);
                menu->snacks.count++;
            } else if (strcmp(item.type, "NonVeg") == 0) {
                strcpy(menu->snacks.nonVeg[menu->snacks.count].name, item.name);
                menu->snacks.nonVeg[menu->snacks.count].price = item.price;
                strcpy(menu->snacks.nonVeg[menu->snacks.count].category, item.category);
                menu->snacks.nonVeg[menu->snacks.count].rating = item.rating;
                menu->snacks.nonVeg[menu->snacks.count].total_ratings = item.total_ratings;
                strcpy(menu->snacks.nonVeg[menu->snacks.count].type ,item.type);
                menu->snacks.count++;
            }
        }else if (strcmp(item.category, "Breakfast") == 0) {
            if (strcmp(item.type, "Veg") == 0) {
                strcpy(menu->breakfast.veg[menu->breakfast.count].name, item.name);
                menu->breakfast.veg[menu->breakfast.count].price = item.price;
                strcpy(menu->breakfast.veg[menu->breakfast.count].category, item.category);
                menu->breakfast.veg[menu->breakfast.count].rating = item.rating;
                menu->breakfast.veg[menu->breakfast.count].total_ratings = item.total_ratings;
                strcpy(menu->breakfast.veg[menu->breakfast.count].type ,item.type);
                menu->breakfast.count++;
            } else if (strcmp(item.type, "NonVeg") == 0) {
                strcpy(menu->breakfast.nonVeg[menu->breakfast.count].name, item.name);
                menu->breakfast.nonVeg[menu->breakfast.count].price = item.price;
                strcpy(menu->breakfast.nonVeg[menu->breakfast.count].category, item.category);
                menu->breakfast.nonVeg[menu->breakfast.count].rating = item.rating;
                menu->breakfast.nonVeg[menu->breakfast.count].total_ratings = item.total_ratings;
                strcpy(menu->breakfast.nonVeg[menu->breakfast.count].type ,item.type);
                menu->breakfast.count++;
            }
        }
    }

    fclose(file);
}

int main() {


    initializeMenu(&menu);

    // Print the menu for testing
    printf("Italian (Veg):\n");
    for (int i = 0; i < menu.italian.count; i++) {
        printf("%s: $%.2f\n", menu.italian.veg[i].name, menu.italian.veg[i].price);
    }

    printf("\nItalian (Non-Veg):\n");
    for (int i = 0; i < menu.italian.count; i++) {
        printf("%s: $%.2f\n", menu.italian.nonVeg[i].name, menu.italian.nonVeg[i].price);
    }

    // Print other categories similarly...

    return 0;
}
