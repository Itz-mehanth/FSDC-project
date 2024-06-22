#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "nlprecommendation.h"
#include <ctype.h>
#include <math.h>
#include "login.h"
#include "restaurants_home.h"
#include "food_order_page.h"

char** get_unique_words(const char* filename, int* num_words) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        perror("File opening failed");
        return NULL;
    }

    char** unique_words = (char**)malloc(MAX_WORDS * sizeof(char*));
    if (!unique_words) {
        perror("Memory allocation failed");
        fclose(file);
        return NULL;
    }

    char buffer[MAX_WORD_LENGTH];
    char delimiters[] = " \t\n,.?!;:\"(){}[]";  // List of punctuation characters to use as delimiters
    *num_words = 0;

    while (fgets(buffer, MAX_WORD_LENGTH, file)) {
        // Tokenize the input line by delimiters
        char* token = strtok(buffer, delimiters);
        while (token != NULL) {
            // Convert token to lowercase
            for (int i = 0; token[i]; i++) {
                token[i] = tolower(token[i]);
            }

            // Check if the word is already in unique_words
            int found = 0;
            for (int i = 0; i < *num_words; i++) {
                if (strcmp(unique_words[i], token) == 0) {
                    found = 1;
                    break;
                }
            }

            // Add the word to unique_words if not already present
            if (!found) {
                unique_words[*num_words] = strdup(token);
                (*num_words)++;
                if (*num_words >= MAX_WORDS) {
                    fprintf(stderr, "Maximum number of words exceeded.\n");
                    break;
                }
            }

            token = strtok(NULL, delimiters);
        }
    }

    fclose(file);
    return unique_words;
}
void free_unique_words(char** unique_words, int num_words) {
    for (int i = 0; i < num_words; i++) {
        free(unique_words[i]);
    }
    free(unique_words);
}

UserComment* read_user_comments(const char* filename, int* num_users) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        perror("File community chat opening failed");

        return NULL;
    }

    UserComment* user_comments = malloc(20 * sizeof(UserComment));
    char buffer[5000];
    *num_users = 0;

    while (fgets(buffer, sizeof(buffer), file)) {
        char user_id[20];
        char comment[200];
        char time[20];
        // %s,%s%s~%s\n", name, comment,restaurant_name, time
        sscanf(buffer,"%[^,],%[^,],%[^\n]\n", user_id, comment, time);
        // printf("%s\n", user_id);
        // char* user_id = strtok(buffer, ",");
        // char* comment = strtok(NULL, "\n");
        user_comments[*num_users].user_id = strdup(user_id);
        user_comments[*num_users].comment = strdup(comment);
        // printf("%s: %s\n", user_id, comment);
        (*num_users)++;
    }
    getchar();
    fclose(file);
    return user_comments;
}

char** read_lines(const char* filename, int* num_lines) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        perror("File opening food description failed");
        return NULL;
    }

    char** lines = malloc(1000 * sizeof(char*));
    char buffer[5000];
    *num_lines = 0;

    while (fgets(buffer, sizeof(buffer), file)) {
        lines[*num_lines] = strdup(buffer);
        (*num_lines)++;
    }

    fclose(file);
    return lines;
}

void preprocess_text(char** text, int num_lines) {
    for (int i = 0; i < num_lines; i++) {
        for (char* p = text[i]; *p; p++) {
            *p = tolower(*p);
        }

        char* p = text[i];
        char* q = text[i];
        while (*q) {
            if (!ispunct(*q)) {
                *p++ = *q;
            }
            q++;
        }
        *p = '\0';
    }
}

void preprocess_user_comments(UserComment* user_comments, int num_users) {
    for (int i = 0; i < num_users; i++) {
        char* text = user_comments[i].comment;
        for (char* p = text; *p; p++) {
            *p = tolower(*p);
        }

        char* p = text;
        char* q = text;
        while (*q) {
            if (!ispunct(*q)) {
                *p++ = *q;
            }
            q++;
        }
        *p = '\0';
    }
}
void calculate_tf(char** documents, int num_docs, char** terms, int num_terms, float** tf_matrix) {
    for (int i = 0; i < num_docs; i++) {
        char* token = strtok(documents[i], " ");
        while (token) {
            for (int j = 0; j < num_terms; j++) {
                if (strcmp(token, terms[j]) == 0) {
                    tf_matrix[i][j]++;
                    break;
                }
            }
            token = strtok(NULL, " ");
        }

        // Normalize TF values
        int total_terms = 0;
        for (int j = 0; j < num_terms; j++) {
            total_terms += tf_matrix[i][j];
        }
        for (int j = 0; j < num_terms; j++) {
            if (total_terms > 0) {
                tf_matrix[i][j] /= total_terms;
            }
        }
    }
}

void calculate_idf(char** documents, int num_docs, char** terms, int num_terms, float* idf_vector) {
    for (int i = 0; i < num_terms; i++) {
        int doc_count = 0;
        for (int j = 0; j < num_docs; j++) {
            if (strstr(documents[j], terms[i])) {
                doc_count++;
            }
        }
        idf_vector[i] = log((float)num_docs / (doc_count + 1));
    }
}

TFIDF* compute_tfidf(char** documents, int num_docs, char** terms, int num_terms) {
    TFIDF* tfidf = malloc(sizeof(TFIDF));
    tfidf->num_documents = num_docs;
    tfidf->num_terms = num_terms;
    tfidf->tfidf_matrix = malloc(num_docs * sizeof(float*));
    for (int i = 0; i < num_docs; i++) {
        tfidf->tfidf_matrix[i] = calloc(num_terms, sizeof(float));
    }

    float** tf_matrix = malloc(num_docs * sizeof(float*));
    for (int i = 0; i < num_docs; i++) {
        tf_matrix[i] = calloc(num_terms, sizeof(float));
    }

    float* idf_vector = calloc(num_terms, sizeof(float));

    calculate_tf(documents, num_docs, terms, num_terms, tf_matrix);
    calculate_idf(documents, num_docs, terms, num_terms, idf_vector);

    for (int i = 0; i < num_docs; i++) {
        for (int j = 0; j < num_terms; j++) {
            tfidf->tfidf_matrix[i][j] = tf_matrix[i][j] * idf_vector[j];
        }
    }

    for (int i = 0; i < num_docs; i++) {
        free(tf_matrix[i]);
    }
    free(tf_matrix);
    free(idf_vector);

    return tfidf;
}

float cosine_similarity(float* vec1, float* vec2, int length) {
    float dot_product = 0.0;
    float norm_vec1 = 0.0;
    float norm_vec2 = 0.0;

    for (int i = 0; i < length; i++) {
        dot_product += vec1[i] * vec2[i];
        norm_vec1 += vec1[i] * vec2[i];
        norm_vec2 += vec2[i] * vec2[i];
    }

    return dot_product / (sqrt(norm_vec1) * sqrt(norm_vec2));
}
char* remove_punctuation(const char* str) {
    int len = strlen(str);
    char* result = (char*)malloc((len + 1) * sizeof(char));
    if (!result) {
        perror("Memory allocation failed");
        return NULL;
    }
    
    int j = 0;
    for (int i = 0; i < len; i++) {
        if (!ispunct((unsigned char)str[i])) {
            result[j++] = str[i];
        }
    }
    result[j] = '\0';
    return result;
}

// Function to compare two strings after removing punctuation
int compare_strings(const char* str1, const char* str2) {
    char* processed_str1 = remove_punctuation(str1);
    char* processed_str2 = remove_punctuation(str2);

    if (!processed_str1 || !processed_str2) {
        free(processed_str1);
        free(processed_str2);
        return 0;
    }

    int result = strcmp(processed_str1, processed_str2) == 0;

    free(processed_str1);
    free(processed_str2);

    return result;
}

// Function to keep only the last n elements in an array
void keep_last_n_elements(restaurant *array, int *size, int n) {
    // Check if n is greater than the size of the array
    if (n >= *size) {
        // If so, do nothing
        return;
    }

    // Shift the last n elements to the front
    for (int i = 0; i < n; i++) {
        array[i] = array[*size - n + i];
    }

    // Update the size of the array
    *size = n;
}
void recommend_restaurants_for_users(TFIDF* user_tfidf, TFIDF* restaurant_tfidf, UserComment* user_comments, char** restaurant_descriptions,int *num_recommended , restaurant recommended_restaurants[10]) {
    for (int i = 0; i < user_tfidf->num_documents; i++) {
        int best_match = -1;
        float best_similarity = -1.0;

        for (int j = 0; j < restaurant_tfidf->num_documents; j++) {
            float similarity = cosine_similarity(user_tfidf->tfidf_matrix[i], restaurant_tfidf->tfidf_matrix[j], restaurant_tfidf->num_terms);
            if (similarity > best_similarity) {
                best_similarity = similarity;
                best_match = j;
            }
        }
        readRestaurants();
        if (best_match != -1) {
            if (strcmp(user_comments[i].user_id , current_user_details.username)==0)
            {
                // printf("-%s-\n",restaurant_descriptions[best_match]);
                restaurant* Restaurant = find_restaurant(restaurant_descriptions[best_match]);
                recommended_restaurants[*num_recommended] = *Restaurant;
                // printf("User %s is recommended to visit: %s\n", user_comments[i].user_id, restaurant_descriptions[best_match]);
                // printf("User %s is recommended to visit: %s\n", user_comments[i].user_id,Restaurant->name);
                *num_recommended=*num_recommended+1;
            }
            
        } else {
            if (strcmp(user_comments[i].user_id , current_user_details.username)==0)
            {
                // printf("User %s: No suitable recommendation found.\n", user_comments[i].user_id);
            }
        }
    }
    keep_last_n_elements(recommended_restaurants,num_recommended,10);
    // printf("num of recommendations: %d\n",*num_recommended);
    // getchar();
}

void print_tfidf_matrix(TFIDF* tfidf) {
    printf("TF-IDF Matrix:\n");
    for (int i = 0; i < tfidf->num_documents; i++) {
        printf("Document %d:\n", i + 1);
        for (int j = 0; j < tfidf->num_terms; j++) {
            printf("%s: %.6f\t", "Term", tfidf->tfidf_matrix[i][j]);
        }
        printf("\n");
    }
}

int recommend_restaurants(int *num_recommended , restaurant recommended_restaurants[10]) {
    // Load user comments
    int num_user_comments;
    UserComment* user_comments = read_user_comments("usersChats.txt", &num_user_comments);
    // printf("chats read successfully\n");
    // getchar();
    // Load restaurant descriptions
    int num_restaurant_descriptions;
    char** restaurant_descriptions = read_lines("restaurant_description.txt", &num_restaurant_descriptions);
    // printf("foods read successfully\n");
    // getchar();
    // Preprocess text data
    preprocess_user_comments(user_comments, num_user_comments);
    // for (int i = 0; i < num_user_comments; i++)
    // {
    //     printf("%s\n", user_comments[i].comment);
    // }
    // getchar();
    
    preprocess_text(restaurant_descriptions, num_restaurant_descriptions);
    // printf("Printing the restaurant description\n\n");
    // getchar();
    // for (int i = 0; i < num_restaurant_descriptions; i++)
    // {
    //     printf("%s\n", restaurant_descriptions[i]);
    // }
    // getchar();
    

    // // Define a list of terms (vocabulary)
    // char* terms[] = {"pizza", "burger", "sushi", "pasta", "salad"};
    // int num_words = sizeof(terms) / sizeof(terms[0]);
    const char* filename = "CommunityChat.txt";
    int num_words;
    char** terms = get_unique_words(filename, &num_words);

    // if (terms) {
    //     printf("Unique Words:\n");
    //     for (int i = 0; i < num_words; i++) {
    //         printf("%s\n", terms[i]);
    //     }
    //     // free_unique_words(terms, num_words);
    // }
    // getchar();

    // Compute TF-IDF for user comments and restaurant descriptions
    char** user_comments_texts = malloc(num_user_comments * sizeof(char*));
    for (int i = 0; i < num_user_comments; i++) {
        user_comments_texts[i] = user_comments[i].comment;
    }

    TFIDF* user_tfidf = compute_tfidf(user_comments_texts, num_user_comments, terms, num_words);
    TFIDF* restaurant_tfidf = compute_tfidf(restaurant_descriptions, num_restaurant_descriptions, terms, num_words);

    // print_tfidf_matrix(user_tfidf);
    // printf("\n=================================================================\n");
    // print_tfidf_matrix(restaurant_tfidf);
    // Recommend restaurants for each user
    recommend_restaurants_for_users(user_tfidf, restaurant_tfidf, user_comments, restaurant_descriptions,num_recommended,recommended_restaurants);

    // Free allocated memory
    for (int i = 0; i < num_user_comments; i++) {
        free(user_comments[i].user_id);
        free(user_comments[i].comment);
    }
    free(user_comments);
    for (int i = 0; i < num_restaurant_descriptions; i++) {
        free(restaurant_descriptions[i]);
    }
    free(restaurant_descriptions);
    for (int i = 0; i < user_tfidf->num_documents; i++) {
        free(user_tfidf->tfidf_matrix[i]);
    }
    free(user_tfidf->tfidf_matrix);
    free(user_tfidf);
    for (int i = 0; i < restaurant_tfidf->num_documents; i++) {
        free(restaurant_tfidf->tfidf_matrix[i]);
    }
    free(restaurant_tfidf->tfidf_matrix);
    free(restaurant_tfidf);

    return 0;
}
