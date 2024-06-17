#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>

// Function to check if today is Wednesday
bool isWednesday(struct tm *currentDate) {
    return currentDate->tm_wday == 3; // tm_wday: 0=Sunday, 1=Monday, ..., 3=Wednesday
}

// Function to check if today is a festival (Diwali, New Year, Pongal, Christmas)
bool isFestival(struct tm *currentDate) {
    return ((currentDate->tm_mon == 10 && currentDate->tm_mday == 4) ||   // Diwali (November 4th)
            (currentDate->tm_mon == 0 && currentDate->tm_mday == 1) ||    // New Year (January 1st)
            (currentDate->tm_mon == 0 && currentDate->tm_mday == 14) ||   // Pongal (January 14th)
            (currentDate->tm_mon == 11 && currentDate->tm_mday == 25));  // Christmas (December 25th)
}

// Function to check if today is during the summer season (June, July, August)
bool isSummer(struct tm *currentDate) {
    return (currentDate->tm_mon == 5 || currentDate->tm_mon == 6 || currentDate->tm_mon == 7);
}

// Function to check if today is during the winter season (December, January, February)
bool isWinter(struct tm *currentDate) {
    return (currentDate->tm_mon == 11 || currentDate->tm_mon == 0 || currentDate->tm_mon == 1);
}

// Function to convert game points to discount percentage
float convertPointsToDiscount(int points) {
    return points * 0.01; // 100 points = 1% discount
}

// Function to check if today is within the special discount hour (e.g., 15:00 to 16:00)
bool isSpecialHour(struct tm *currentTime) {
    return (currentTime->tm_hour >= 15 && currentTime->tm_hour < 16); // Special hour from 15:00 to 16:00
}

// Function to calculate the final bill amount after applying discounts
float calculateFinalBill(float amount, bool isWed, bool isFest, float pointsDiscount, bool isSpecHour, bool isSummer, bool isWinter) {
    float totalDiscount = 0.0;

    // Apply Wednesday discount (5%)
    if (isWed) {
        totalDiscount += 0.05;
    }

    // Apply festival discounts (15%)
    if (isFest) {
        totalDiscount += 0.15;
    }

    // Apply special hour discount (5%)
    if (isSpecHour) {
        totalDiscount += 0.05;
    }

    // Apply summer discount (10%)
    if (isSummer) {
        
        totalDiscount += 0.10;

    }

    // Apply winter discount (10%)
    if (isWinter) {
        totalDiscount += 0.10;
    }

    totalDiscount += pointsDiscount;

    // Cap the total discount at 30%
    if (totalDiscount > 0.30) {
        totalDiscount = 0.30;
    }

    float finalAmount = amount * (1 - totalDiscount);
    return finalAmount;
}

int main() {
    time_t t = time(NULL);
    struct tm *currentTime = localtime(&t);

    float billAmount;
    int gamePoints;

    printf("Enter the amount of the bill: ");
    scanf("%f", &billAmount);

    printf("Enter the game points (between 1 and 10): ");
    scanf("%d", &gamePoints);

    if (gamePoints < 1 || gamePoints > 10) {
        printf("Invalid game points. Must be between 1 and 10.\n");
        return 1;
    }

    bool todayIsWednesday = isWednesday(currentTime);
    bool todayIsFestival = isFestival(currentTime);
    bool todayIsSummer = isSummer(currentTime);
    bool todayIsWinter = isWinter(currentTime);
    float pointsDiscount = convertPointsToDiscount(gamePoints);
    bool todayIsSpecialHour = isSpecialHour(currentTime);

    float finalBill = calculateFinalBill(billAmount, todayIsWednesday, todayIsFestival, pointsDiscount, todayIsSpecialHour, todayIsSummer, todayIsWinter);

    printf("Original Bill Amount: %.2f\n", billAmount);

    if (todayIsWednesday) {
        printf("Applying 5%% discount for Wednesday.\n");
    }

    if (todayIsFestival) {
        printf("Applying 15%% discount for festival.\n");
    }

    if (todayIsSummer) {
        printf("Applying 10%% discount for summer offer.\n");
    }

    if (todayIsWinter) {
        printf("Applying 10%% discount for winter offer.\n");
    }

    if (pointsDiscount > 0) {
        printf("Applying %.2f%% discount from game points.\n", pointsDiscount * 100);
    }

    if (todayIsSpecialHour) {
        printf("Applying 5%% discount for special hour as you ordered within 3pm to 4pm.\n");
    }

    printf("Final Bill Amount after discounts: %.2f\n", finalBill);

    return  0;
}