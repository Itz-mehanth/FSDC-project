#ifndef DELIVERY_BOY_SELECTION
#define DELIVERY_BOY_SELECTION


#include <stdio.h>
#include "theme.h"

#include <stdbool.h>
#include <conio.h>

#define USERNAME_MAX_LEN 50
#define PASSWORD_MAX_LEN 50
#define EMAIL_MAX_LEN 50
#define PHONE_NO_MAX_LEN 20
#define MAX_USERS 10
#define MAX_RATINGS 10
#define BLACK         0
#define RED           (FOREGROUND_RED | FOREGROUND_INTENSITY)
#define GREEN         (FOREGROUND_GREEN | FOREGROUND_INTENSITY)
#define YELLOW        (FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY)
#define ORANGE        (FOREGROUND_RED | FOREGROUND_GREEN)
#define BLUE          (FOREGROUND_BLUE)
#define MAGENTA       (FOREGROUND_RED | FOREGROUND_BLUE)
#define CYAN          (FOREGROUND_GREEN | FOREGROUND_BLUE| FOREGROUND_INTENSITY)
#define WHITE         (FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY)

#define DARK_RED      (FOREGROUND_RED | FOREGROUND_INTENSITY)
#define DARK_GREEN    (FOREGROUND_GREEN | FOREGROUND_INTENSITY)
#define DARK_YELLOW   (YELLOW | FOREGROUND_INTENSITY)
#define DARK_BLUE     (FOREGROUND_BLUE | FOREGROUND_INTENSITY)
#define DARK_MAGENTA  (MAGENTA | FOREGROUND_INTENSITY)
#define DARK_CYAN     (CYAN | FOREGROUND_INTENSITY)
#define DARK_GRAY     (FOREGROUND_INTENSITY)
#define LIGHT_GRAY    (WHITE | FOREGROUND_INTENSITY)

#define BACKGROUND_BLACK   0
#define RED_BACKGROUND     (BACKGROUND_INTENSITY | BACKGROUND_RED)
#define GREEN_BACKGROUND  (BACKGROUND_INTENSITY | BACKGROUND_GREEN)
#define YELLOW_BACKGROUND  (BACKGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN)
#define BLUE_BACKGROUND   (BACKGROUND_INTENSITY | BACKGROUND_BLUE)
#define MAGENTA_BACKGROUND (BACKGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_BLUE)
#define CYAN_BACKGROUND   (BACKGROUND_INTENSITY | BACKGROUND_GREEN | BACKGROUND_BLUE)
#define WHITE_BACKGROUND  (BACKGROUND_INTENSITY |FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE)

typedef struct
{
    char username[USERNAME_MAX_LEN];
    char password[PASSWORD_MAX_LEN];
    char email[EMAIL_MAX_LEN];
    char phone_no[PHONE_NO_MAX_LEN];
    float ratings;
    int total_ratings;
    bool current_del_boy;
    double lat;
    double lon;
    int estimated_sec;
}Partner;

extern int num_del_boys;
extern char current_del_boy[USERNAME_MAX_LEN];
extern Partner current_del_boy_details;
extern Partner partners[MAX_USERS];


void home_page_banner();

bool isPhoneNumberValid(const char *phoneNumber);

bool isEmailValid(const char *email);

void side_menu(int selectedOption);

int menu_navigator();

int readPartnersFromFile();
int delivery_boy_login();
int UserType();
void find_partner_details(Partner partners[],const char *target_username,Partner *destination);
void printPartnerDetails();

int writeCurrentPartner(Partner currentPartner);
int readCurrentPartner();
void writePartnersToFile(Partner partner);
int isPartnernameExists(char *username);
int registerPartner();

int loginPartner();

#endif // !DELIVERY_BOY_SELECTION

