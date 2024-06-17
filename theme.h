#include "windows.h"
#ifndef THEME
#define THEME
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

#ifdef _WIN32
#define COLOR_CODES_SUPPORTED 1
#else
#define COLOR_CODES_SUPPORTED 0  // Assume color codes not supported on non-Windows
#endif
extern int CURRENT_FOREGROUND_COLOR;
extern int CURRENT_BACKGROUND_COLOR;
int change_theme();
void set_text_color(int foreground_color, int background_color);
void welcome_pop();
void set_theme();
void theme_reset();
void print_error(char *message);
void print_success(char *message);
#endif // !THEME