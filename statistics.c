#include <stdio.h>
#include <time.h>
#include <stdlib.h>

int read_purchases(PurchaseEntry *entries, int max_entries) {
        FILE *file = fopen("user_purchases.txt", "r");
        if (file == NULL) {
            perror("Failed to open file");
            return -1;
        }

        int count = 0;
        while (count < max_entries && fscanf(file, "%49[^,],%f,%49[^\n]\n", entries[count].username, &entries[count].final_amount, entries[count].time_str) == 3) {
            count++;
        }

        fclose(file);
        return count;
    }
int main(){
    
}