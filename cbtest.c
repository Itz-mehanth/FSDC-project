#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>


int findUserId(char *user_name) {
    FILE *file = fopen("users.txt", "r");
    if (file == NULL) {
        printf("Error opening file.\n");
        exit(1);
    }
    char user[50];
    char password[50];
    char email[50];
    char phone[50];
    int count = 0; // Initialize count to 0
    while (fscanf(file, "%s %s %s %s", user, password, email, phone) == 4) {
        count++; // Increment count before checking
        // printf("running while loop for findind userid\n");
        // printf("%s == %s\n", user, user_name);
        if (strcmp(user_name, user) == 0) {
            fclose(file); // Close the file before returning
            return count; // Return the 1-based index
        }
    }
    fclose(file); // Close the file if user is not found
    return -1;
}

int findFoodIndex(char *food_name) {
    FILE *file = fopen("foods.txt", "r");
    if (file == NULL) {
        printf("Error opening file.\n");
        exit(1);
    }
    char food[50];
    float price;
    char cuisine[50];
    char category[50];
    float rating;
    int total_rating;
    float current_rating;
    int count = 0; // Initialize count to 0
    while (fscanf(file, "%[^,],%f,%[^,],%[^,],%f,%d,%f\n", food, &price, cuisine, category, &rating, &total_rating, &current_rating) == 7) {
        count++; // Increment count before checking
        // printf("%s == %s",food,food_name);
        if (strcmp(food_name, food) == 0) {
            fclose(file); // Close the file before returning
            return count; // Return the 1-based index
        }
    }
    fclose(file); // Close the file if food is not found
    return -1;
}
// Function to calculate the cosine similarity between two items
double cosine_similarity(double *item1, double *item2, int length) {
    double dot_product = 0.0;
    double norm_item1 = 0.0;
    double norm_item2 = 0.0;

    for (int i = 0; i < length; i++) {
        dot_product += item1[i] * item2[i];
        norm_item1 += item1[i] * item1[i];
        norm_item2 += item2[i] * item2[i];
    }

    if (norm_item1 == 0 || norm_item2 == 0) {
        return 0.0;
    }

    return dot_product / (sqrt(norm_item1) * sqrt(norm_item2));
}

// Function to calculate item-item similarity matrix
void calculate_similarity_matrix(double **user_item_matrix, double **similarity_matrix, int num_users, int num_items) {
    for (int i = 0; i < num_items; i++) {
        for (int j = 0; j < num_items; j++) {
            double item_i[num_users];
            double item_j[num_users];

            for (int k = 0; k < num_users; k++) {
                item_i[k] = user_item_matrix[k][i];
                item_j[k] = user_item_matrix[k][j];
            }

            similarity_matrix[i][j] = cosine_similarity(item_i, item_j, num_users);
        }
    }
}

// Function to recommend items for a given user
void recommend_items(double **user_item_matrix, double **similarity_matrix, int user, int num_users, int num_items) {
    double scores[num_items];
    for (int i = 0; i < num_items; i++) {
        scores[i] = 0.0;
        double similarity_sum = 0.0;
        for (int j = 0; j < num_items; j++) {
            scores[i] += similarity_matrix[i][j] * user_item_matrix[user][j];
            similarity_sum += similarity_matrix[i][j];
        }
        if (similarity_sum != 0) {
            scores[i] /= similarity_sum;
        }
    }

    // Print the recommendation scores
    printf("Recommendation scores for user %d:\n", user);
    for (int i = 0; i < num_items; i++) {
        printf("Item %d: %f\n", i, scores[i]);
    }
}

void create_user_item_matrix(double user_item_matrix_data[5][279]){
    // Initialize matrix with zeros
    for(int i = 0; i < 5; i++) {
        for(int j = 0; j < 279; j++) {
            user_item_matrix_data[i][j] = 0.0;
        }
    }
    
    // Load ratings from ratings.txt
    FILE *ratings_file = fopen("ratings.txt", "r");
    if (ratings_file == NULL) {
        perror("Error opening ratings.txt");
        exit(EXIT_FAILURE);
    }
    
    int user_id, food_id;
    char user[50], food[50];
    double rating;
    printf("scanning ratings.txt\n");

    while(fscanf(ratings_file, "%[^,],%[^,],%lf\n", user, food, &rating) != EOF ) {
        printf("runnig while\n");
        user_id = findUserId(user);
        printf("user_id %d ",user_id);

        food_id = findFoodIndex(food);
        printf("food_id %d\n",food_id);
        if (user_id <= 5 && food_id <= 279)
        {
            printf("%d : %f -> %f\n",food_id-1,user_id-1,rating);
            user_item_matrix_data[user_id - 1][food_id - 1] = rating;
        }
    }
    fclose(ratings_file);
}

int main() {
    // Sample user-item interaction matrix
    int num_users = 1;
    int num_items = 279;
    double user_item_matrix_data[5][279];

    create_user_item_matrix(user_item_matrix_data);
    for (int i = 0; i < 1; i++)
    {
        for (int j = 0; j < 279; j++)
        {
            printf("%f ", user_item_matrix_data[i][j]);
        }
        printf("\n");
    }
    

    // Allocate memory for user-item matrix pointers
    double **user_item_matrix = (double **)malloc(num_users * sizeof(double *));
    for (int i = 0; i < num_users; i++) {
        user_item_matrix[i] = user_item_matrix_data[i];
    }

    // Allocate memory for the similarity matrix
    double **similarity_matrix = (double **)malloc(num_items * sizeof(double *));
    for (int i = 0; i < num_items; i++) {
        similarity_matrix[i] = (double *)malloc(num_items * sizeof(double));
    }

    // Calculate the item-item similarity matrix
    calculate_similarity_matrix(user_item_matrix, similarity_matrix, num_users, num_items);

    // Recommend items for a specific user (e.g., user 0)
    recommend_items(user_item_matrix, similarity_matrix, 0, num_users, num_items);

    // Free the allocated memory
    for (int i = 0; i < num_items; i++) {
        free(similarity_matrix[i]);
    }
    free(similarity_matrix);
    free(user_item_matrix);

    return 0;
}
