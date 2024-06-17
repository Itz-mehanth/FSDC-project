#ifndef ADD_TO_CART
#define ADD_TO_CART
#include "food_items.h"
int addToCart(FoodItem food_item, int quantity);

int updateFoodItemRating(const char *itemName, float newRating);
void rate_food_item(FoodItem food);

FoodItem addCartFunction(FoodItem food);

#endif // !ADD_TO_CART