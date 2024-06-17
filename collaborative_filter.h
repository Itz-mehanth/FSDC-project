#ifndef COLLABORATIVE_FILTER
#define COLLABORATIVE_FILTER

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define TOTAL_FOOD_ITEMS 280
#define MAX_NAME_LENGTH 50
#define MAX_LINE_LENGTH 256

typedef struct {
    char userName[25];
    char itemName[25];
    float rating;
} Rating;


typedef struct {
    char itemName[25];
    float similarity;
} ItemSimilarity;

typedef struct {
    int numItems;
    ItemSimilarity* similarities;  // Dynamic array of similarities for each item
} ItemSimilarityList;

typedef struct {
    char itemName[25];
    float predictedRating;
} PredictedRating;

void print_similarity_matrix(ItemSimilarityList simList, int totalItems, FoodItem foodItems[]);

void loadFoodItems(FoodItem items[], int *count);

int find_item_id(const char *itemName, FoodItem foodItems[], int totalItems);

void computeSimilarities(Rating* ratings, int numRatings, ItemSimilarityList* simList, int totalItems, FoodItem foodItems[]) ;
Rating* readRatings(const char* filename, int* count);

// Function to predict ratings for a user
void predictRatingsForUser(const char *userName, Rating* ratings, int numRatings, ItemSimilarityList* simList, FoodItem foodItems[], int totalItems, PredictedRating* predictedRatings, int* numPredictions);
// Function to recommend top 5 food items for a user
void recommendTop5Foods(const char *userName, Rating* ratings, int numRatings, ItemSimilarityList* simList, FoodItem foodItems[], int totalItems);

int collaborative_filter(PredictedRating* predictedRatings,int *numPredictions);

#endif // COLLABORATIVE_FILTER