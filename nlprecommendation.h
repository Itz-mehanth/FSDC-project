#ifndef NLP_RESTAURANTS
#define NLP_RESTAURANTS

#include "restaurants_home.h"

#define MAX_WORD_LENGTH 100
#define MAX_WORDS 1000

typedef struct {
    char* user_id;
    char* comment;
} UserComment;

typedef struct {
    int num_documents;
    int num_terms;
    float** tfidf_matrix;
} TFIDF;

int compare_strings(const char* str1, const char* str2);

void recommend_restaurants_for_users(TFIDF* user_tfidf, TFIDF* restaurant_tfidf, UserComment* user_comments, char** restaurant_descriptions,int *num_recommended , restaurant recommended_restaurants[10]) ;

void print_tfidf_matrix(TFIDF* tfidf) ;
int recommend_restaurants(int *num_recommended , restaurant recommended_restaurants[10]);


#endif // !NLP_RESTAURANTS