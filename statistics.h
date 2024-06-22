#ifndef STATISTICS
#define STATISTICS


#define MAX_HEIGHT 20
#define MAX_ENTRIES 100



// Define the structure to hold the purchase details
typedef struct {
    char username[50];
    float final_amount;
    char time_str[50];
} PurchaseEntry;

// Define the structure to hold daily summaries
typedef struct {
    int day;
    float total_prices;
} DailySummary;

typedef struct {
    char day[50];
    float total_amount;
} stats;
extern stats daily_stats[7];




int statBars();

#endif // !STATISTICS

