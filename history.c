#include <stdio.h>

int calender() {
    int year, month, daysInMonth, startingDay;
    
    // Input year and month
    printf("Enter year: ");
    scanf("%d", &year);
    printf("Enter month (1-12): ");
    scanf("%d", &month);

    // Calculate number of days in the month
    if (month == 4 || month == 6 || month == 9 || month == 11)
        daysInMonth = 30;
    else if (month == 2) {
        // Check for leap year
        if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0))
            daysInMonth = 29;
        else
            daysInMonth = 28;
    } else
        daysInMonth = 31;

    // Calculate starting day of the month
    startingDay = (year - 1) * 365 + (year - 1) / 4 - (year - 1) / 100 + (year - 1) / 400;
    for (int i = 1; i < month; ++i) {
        if (i == 4 || i == 6 || i == 9 || i == 11)
            startingDay += 30;
        else if (i == 2) {
            if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0))
                startingDay += 29;
            else
                startingDay += 28;
        } else
            startingDay += 31;
    }
    startingDay %= 7;

    // Print calendar header
    printf("\n---------------------------\n");
    printf("   %d/%d\n", month, year);
    printf("---------------------------\n");
    printf(" Sun Mon Tue Wed Thu Fri Sat\n");

    // Print spaces for the first day
    for (int i = 0; i < startingDay; ++i)
        printf("    ");

    // Print the days of the month
    for (int i = 1; i <= daysInMonth; ++i) {
        printf("%4d", i);
        if ((i + startingDay) % 7 == 0 || i == daysInMonth)
            printf("\n");
    }

    printf("---------------------------\n");

    return 0;
}
