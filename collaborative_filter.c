#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "food_items.h"
#include <string.h>
#include "login.h"

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

void print_similarity_matrix(ItemSimilarityList simList, int totalItems, FoodItem foodItems[]) {
    // Print the header row with item names
    printf("%-25s", ""); // Empty top-left corner
    for (int i = 0; i < totalItems; i++) {
        printf("%-25s", foodItems[i].name);
    }
    printf("\n");

    // Print each row of the matrix
    for (int i = 0; i < totalItems; i++) {
        // Print the item name for the row
        printf("%-25s", foodItems[i].name);

        // Print the similarity values
        for (int j = 0; j < totalItems; j++) {
            float similarity = simList.similarities[i * totalItems + j].similarity;
            if (similarity != 0.0f)    
            {
                printf("%-5.2f", similarity);
            }
            
        }
        printf("\n");
    }
}


int find_item_id(const char *itemName, FoodItem foodItems[], int totalItems) {
    for (int i = 0; i < totalItems; i++) {
        if (strcmp(foodItems[i].name, itemName) == 0) {
            return i;
        }
    }
    return -1;
}

void computeSimilarities(Rating* ratings, int numRatings, ItemSimilarityList* simList, int totalItems, FoodItem foodItems[]) {
    // Allocate memory for a 2D array of sums, counts, and magnitudes for each item
    float **dotProducts = (float**) calloc(totalItems, sizeof(float*));
    float *magnitudes = (float*) calloc(totalItems, sizeof(float));
    
    for (int i = 0; i < totalItems; i++) {
        dotProducts[i] = (float*) calloc(totalItems, sizeof(float));
    }

    // Initialize variables for computation
    for (int i = 0; i < numRatings; i++) {
        for (int j = i + 1; j < numRatings; j++) {
            if (strcmp(ratings[i].userName, ratings[j].userName) == 0) {
                // Only calculate for the same user
                int itemId1 = find_item_id(ratings[i].itemName, foodItems, totalItems);
                int itemId2 = find_item_id(ratings[j].itemName, foodItems, totalItems);
                if (itemId1 != -1 && itemId2 != -1) { // Ensure within bounds
                    dotProducts[itemId1][itemId2] += ratings[i].rating * ratings[j].rating;
                    dotProducts[itemId2][itemId1] = dotProducts[itemId1][itemId2]; // Symmetric matrix
                }
            }
        }
        // Calculate magnitude for each item
        int itemId  = find_item_id(ratings[i].itemName, foodItems, totalItems);
        if (itemId != -1) { // Ensure within bounds
            magnitudes[itemId] += ratings[i].rating * ratings[i].rating;
        }
    }

    // Calculate cosine similarities
    for (int i = 0; i < totalItems; i++) {
        for (int j = 0; j < totalItems; j++) {
            if (i != j && magnitudes[i] != 0 && magnitudes[j] != 0) { // Avoid division by zero and self-similarity
                float similarity = dotProducts[i][j] / (sqrt(magnitudes[i]) * sqrt(magnitudes[j]));
                strcpy(simList->similarities[i * totalItems + j].itemName, foodItems[j].name);
                simList->similarities[i * totalItems + j].similarity = similarity;
            } else {
                strcpy(simList->similarities[i * totalItems + j].itemName, foodItems[j].name);
                simList->similarities[i * totalItems + j].similarity = 0.0; // Set similarity to zero if no valid data
            }
        }
    }

    // Clean up
    for (int i = 0; i < totalItems; i++) {
        free(dotProducts[i]);
    }
    free(dotProducts);
    free(magnitudes);
}

Rating* readRatings(const char* filename, int* count) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        perror("Failed to open file");
        return NULL;
    }

    Rating* ratings = malloc(sizeof(Rating) * 100);
    int capacity = 100;
    *count = 0;

    while (fscanf(file, "%24[^,],%24[^,],%f\n", ratings[*count].userName, ratings[*count].itemName, &ratings[*count].rating) == 3) {
        (*count)++;
        if (*count >= capacity) {
            capacity *= 2;
            ratings = realloc(ratings, sizeof(Rating) * capacity);
        }
    }

    fclose(file);
    return ratings;
}

// Function to predict ratings for a user
void predictRatingsForUser(const char *userName, Rating* ratings, int numRatings, ItemSimilarityList* simList, FoodItem foodItems[], int totalItems, PredictedRating* predictedRatings, int* numPredictions) {
    // Initialize predicted ratings
    *numPredictions = 0;

    for (int i = 0; i < totalItems; i++) {
        float numerator = 0.0;
        float denominator = 0.0;
        int itemRatedByUser = 0;

        for (int j = 0; j < numRatings; j++) {
            if (strcmp(ratings[j].userName, userName) == 0) {
                int ratedItemId = find_item_id(ratings[j].itemName, foodItems, totalItems);
                if (ratedItemId == i) {
                    itemRatedByUser = 1;
                    break;
                }
                float similarity = simList->similarities[i * totalItems + ratedItemId].similarity;
                numerator += similarity * ratings[j].rating;
                denominator += fabs(similarity);
            }
        }

        if (!itemRatedByUser && denominator != 0.0) {
            predictedRatings[*numPredictions].predictedRating = numerator / denominator;
            strcpy(predictedRatings[*numPredictions].itemName, foodItems[i].name);
            (*numPredictions)++;
        }
    }
}

// Function to recommend top 5 food items for a user
void recommendTop5Foods(const char *userName, Rating* ratings, int numRatings, ItemSimilarityList* simList, FoodItem foodItems[], int totalItems,PredictedRating* predictedRatings,int* numPredictions) {


    predictRatingsForUser(userName, ratings, numRatings, simList, foodItems, totalItems, predictedRatings, numPredictions);

    // Sort predicted ratings in descending order
    for (int i = 0; i < *numPredictions - 1; i++) {
        for (int j = i + 1; j < *numPredictions; j++) {
            if (predictedRatings[i].predictedRating < predictedRatings[j].predictedRating) {
                PredictedRating temp = predictedRatings[i];
                predictedRatings[i] = predictedRatings[j];
                predictedRatings[j] = temp;
            }
        }
    }

    // // Print top 5 recommendations
    // printf("Top 5 recommendations for %s:\n", userName);
    // for (int i = 0; i < 5 && i < *numPredictions; i++) {
    //     printf("%s with predicted rating of %.2f\n", predictedRatings[i].itemName, predictedRatings[i].predictedRating);
    // }

    // free(predictedRatings);
}

int collaborative_filter(PredictedRating* predictedRatings,int *numPredictions) {
    int foodCount;
    int numRatings;
    FoodItem foodItems[TOTAL_FOOD_ITEMS];
    loadFoodItems(foodItems, &foodCount);

    Rating* ratings = readRatings("ratings.txt", &numRatings);

    if (ratings == NULL) {
        return 1;
    }

    ItemSimilarityList simList;
    simList.numItems = TOTAL_FOOD_ITEMS * TOTAL_FOOD_ITEMS;
    simList.similarities = malloc(sizeof(ItemSimilarity) * simList.numItems);

    computeSimilarities(ratings, numRatings, &simList, TOTAL_FOOD_ITEMS, foodItems);

    // printf("Similarity Matrix:\n");
    // print_similarity_matrix(simList, TOTAL_FOOD_ITEMS, foodItems);

    // Recommend top 5 foods for a specific user

    recommendTop5Foods(current_user_details.username, ratings, numRatings, &simList, foodItems, TOTAL_FOOD_ITEMS,predictedRatings,numPredictions);

    // Free memory
    free(ratings);
    free(simList.similarities);
    return 0;
}
