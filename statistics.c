#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "theme.h"
#include "statistics.h"
#include "conio.h"
#include "food_order_page.h"
#include <string.h>
#include <time.h>

#define MAX_HEIGHT 20
#define MAX_ENTRIES 100

stats daily_stats[7];

// Custom strptime function for Windows
int custom_strptime(const char *buf, const char *fmt, struct tm *tm) {
    return sscanf(buf, fmt,
                  &tm->tm_wday, &tm->tm_mon, &tm->tm_mday,
                  &tm->tm_hour, &tm->tm_min, &tm->tm_sec,
                  &tm->tm_year) == 7;
}

// Function to read the file and populate the entries
int read_purchases(const char *filename, PurchaseEntry *entries, int max_entries) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        print_error("Failed to open file");
        return -1;
    }

    int count = 0;
    while (count < max_entries && fscanf(file, "%[^,],%f,%[^\n]\n", entries[count].username, &entries[count].final_amount, entries[count].time_str) == 3) {
        // printf("%s %.2f %s\n", entries[count].username, entries[count].final_amount, entries[count].time_str);
        count++;
    }

    fclose(file);
    return count;
}
float find_min_float(float arr[], int size) {
    if (size <= 0) {
        // Handle invalid input
        print_error("Error: Array size must be greater than 0\n");
        return 0.0; // Return a default value or handle error as needed
    }

    float min = arr[0];

    for (int i = 1; i < size; ++i) {
        // printf("%f ", arr[i]);
        if (arr[i] < min) {
            min = arr[i];
        }
    }
    // printf("\n");
    return min;
}


float find_max_float(float arr[], int size) {
    if (size <= 0) {
        // Handle invalid input
        print_error("Error: Array size must be greater than 0\n");
        return 0.0; // Return a default value or handle error as needed
    }

    float max = arr[0];

    for (int i = 1; i < size; ++i) {
        // printf("%f ", arr[i]);
        if (arr[i] > max) {
            max = arr[i];
        }
    }
    // printf("\n");
    return max;
}


void normalizeHeights(float *heights, int numheights) {
    float max = find_max_float(heights, numheights);
    float min = find_min_float(heights, numheights);
     if (max == min) {
        // Handle case where all values are the same (to prevent division by zero)
        for (int i = 0; i < numheights; ++i) {
            heights[i] = 0.0; // Set all to 0
        }
    } else {
        for (int i = 0; i < numheights; ++i) {
            heights[i] = (heights[i] - min) / (max - min) *20;
        }
    }
}

int parse_time_str(const char *time_str, struct tm *tm_entry) {
    char month_str[4];
    int month;
    static const char month_names[] = "JanFebMarAprMayJunJulAugSepOctNovDec";

    // Parse the time string manually
    sscanf(time_str, "%*s %s %d %d:%d:%d %d", month_str, &tm_entry->tm_mday, &tm_entry->tm_hour,
           &tm_entry->tm_min, &tm_entry->tm_sec, &tm_entry->tm_year);

    // Convert month_str to month number
    month = (strstr(month_names, month_str) - month_names) / 3 + 1;
    tm_entry->tm_mon = month - 1; // tm_mon is 0-based

    // Adjust year to years since 1900
    tm_entry->tm_year -= 1900;
    return 1;
}

// Function to parse date-time and summarize daily prices in the last 7 days
DailySummary* summarize_last_7_days(PurchaseEntry *entries, int size, int *num_days) {
    time_t now = time(NULL);
    struct tm tm_entry;
    time_t entry_time;
    DailySummary *daily_summaries = (DailySummary *)malloc(7 * sizeof(DailySummary));
    *num_days = 0;

    // Initialize daily summaries
    for (int i = 0; i < 7; ++i) {
        daily_summaries[i].day = i + 1;
        daily_summaries[i].total_prices = 0.0;
    }

    for (int i = 0; i < size; ++i) {
        if (parse_time_str(entries[i].time_str,&tm_entry)) {
            entry_time = mktime(&tm_entry);
            double seconds_diff = difftime(now, entry_time);
            double days_diff = seconds_diff / (60 * 60 * 24);

            if (days_diff >= 0 && days_diff < 7) {
                int day_index = 6 - (int)days_diff; // Calculate the day index in reverse order
                daily_summaries[day_index].total_prices += entries[i].final_amount;
            }
        }
    }

    *num_days = 7;
    return daily_summaries;
}

const char *getDayFromToday(int daysFromToday) {
    if (daysFromToday == 0)
    {
        return "Today";
    }
    
    // Get the current time
    time_t t = time(NULL);
    struct tm *today = localtime(&t);

    // Adjust the current day by the number of days from today
    today->tm_mday += daysFromToday;

    // Normalize the time using mktime (handles overflow/underflow of fields)
    mktime(today);

    // Define day names
    static const char *dayNames[] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

    // Return the corresponding day name
    return dayNames[today->tm_wday];
}

void print_bar(int x, int y,int height){
    int posY = y;
    int width = 10;
    int maxHeight = 20;
    static int i =0;
    setCursor_inc(x,posY--);
    set_text_color(BLACK,LIGHT_GRAY);
    printf("%-9s",daily_stats[i].day);

    setCursor_inc(x,posY--);
    set_text_color(GREEN,LIGHT_GRAY);
    printf("(");
    printf("$");
    
    printf(".%.2lf)",daily_stats[i].total_amount);

    i++;
    for (int i = 0; i < height; i++)
    {        
        setCursor_inc(x,posY--);
        set_text_color(WHITE,BLUE);
        printf("%*s",width," ");
        Sleep(40);
    }
    set_text_color(BLACK,BLACK);
}

// Function to print the daily summaries
void print_daily_summaries(DailySummary *daily_summaries, int num_days) {
    for (int i = 0; i < num_days; ++i) {
        int days_diff = daily_summaries[i].day -7;
        strcpy(daily_stats[i].day,getDayFromToday(days_diff));
        daily_stats[i].total_amount = daily_summaries[i].total_prices;
    }
}

void print_bar_div(){
    int x = 45;
    int y = 15;
    for (int i = 0; i < 26; i++)
    {
        setCursor_inc(x,y++);
        set_text_color(BLACK,LIGHT_GRAY);
        printf("%*s",150," ");
    }
}

int statBars() {
    PurchaseEntry entries[MAX_ENTRIES];
    int num_entries = read_purchases("user_purchases.txt", entries, MAX_ENTRIES);
    if (num_entries < 0) {
        return 1; // Exit if reading file fails
    }
    int num_days;
    DailySummary *daily_summaries = summarize_last_7_days(entries, num_entries, &num_days);
    if (daily_summaries == NULL) {
        return 1; // Exit if summarizing fails
    }
    // printf("printting daily summary\n");
    print_daily_summaries(daily_summaries, num_days);
    float heights[7];
    for (int i = 0; i < 7; i++)
    {
        heights[i] = daily_stats[i].total_amount;
        // printf("%f\n", heights[i]);
    }
    
    print_bar_div();
    set_text_color(BLACK,WHITE);
    // printf("heights copied\n");
    normalizeHeights(heights,7);

    for (int i = 0; i < 7; i++)
    {
        // printf("Bar %d (%d,%d)\t\t\t", i+1,i*15+5,(int)heights[i]);
        print_bar(i*18+50,40,(int)heights[i]);
    }
    // printf("printed bars\n");

    // Free allocated memory for daily summaries
    free(daily_summaries);
    char ch;
    while((ch = getch()!='\t')){
        continue;
    }



    return 0;
}
