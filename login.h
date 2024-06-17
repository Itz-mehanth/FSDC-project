#ifndef LOGIN
#define LOGIN

#include <stdbool.h>

#define USERNAME_MAX_LEN 50
#define PASSWORD_MAX_LEN 50
#define EMAIL_MAX_LEN 50
#define PHONE_NO_MAX_LEN 20
#define MAX_USERS 10
#define MAX_RATINGS 10


typedef struct
{
    char username[USERNAME_MAX_LEN];
    char password[PASSWORD_MAX_LEN];
    char email[EMAIL_MAX_LEN];
    char phone_no[PHONE_NO_MAX_LEN];
    char rating_history[MAX_RATINGS][20];
    bool current_user;
    int isveg;
}User;


extern char current_user[USERNAME_MAX_LEN];
extern User current_user_details;
extern User Users[MAX_USERS];
extern int num_users;
// int restaurantsHomeFunction();

void find_user_details(User Users[],const char *target_username,User *destination);

int UserTypeScreen(int ScreenState,int selected);

void login_side_page(bool focus);

void signup_side_page(bool focus);
int UserType();

void top_bar();

int menu_navigator();
void removeLastChar(char *str);

void side_menu(int selectedOption);

void printUserDetails();

int writeCurrentUser();

int readCurrentUser();
int authenticate(char *password);
void home_page_banner();

int readUsersFromFile();

void writeUsersToFile(User user);
int hasAlphabet(char *password);

int hasNumber(char *password);

int hasPunctuation(char *password);

int authenticate(char *password);

int isUsernameExists(char *username);

int registerUser();

int loginUser();

int play_games();

int loginFunction();

#endif
