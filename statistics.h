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



// Custom strptime function for Windows
int custom_strptime(const char *buf, const char *fmt, struct tm *tm);// to read the file and populate the entries
int read_purchases(const char *filename, PurchaseEntry *entries, int max_entries);
float find_min_float(float arr[], int size) ;


float find_max_float(float arr[], int size) ;
void normalizeHeights(float *heights, int numheights);

int parse_time_str(const char *time_str, struct tm *tm_entry);

// Function to parse date-time and summarize daily prices in the last 7 days
DailySummary* summarize_last_7_days(PurchaseEntry *entries, int size, int *num_days);
const char *getDayFromToday(int daysFromToday);
void print_bar(int x, int y,int height);
void print_daily_summaries(DailySummary *daily_summaries, int num_days);

void print_bar_div();

int statBars();

#endif // !STATISTICS

