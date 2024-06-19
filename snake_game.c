
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include "theme.h"

#define cols 50
#define rows 25
#define foods 50

char board[cols * rows];

int isGameOver = 0;

void fill_board() {
    int x,y;
    
    for(y=0; y<rows; y++) {
        for(x=0; x<cols; x++) {
            if(x==0||y==0||x==cols-1||y==rows-1) {
                board[y*cols + x] = '#';
            }else{
                board[y*cols + x] = ' ';
            }
        }
    }
}

void clear_screen() {
    // Hack clear screen on Windows. Do not use!
    system("cls");
    // on Linux & MAC
    // system("clear");
}

void print_board() {
    int x,y;
        
    for(y=0; y<rows; y++) {
        for(x=0; x<cols; x++) {
            putch(board[y*cols + x]);
        }
        putch('\n');
    }    
}

#define SNAKE_MAX_LEN 256
struct SnakePart {
    int x, y;
};
struct Snake {
    int length;
    struct SnakePart part[SNAKE_MAX_LEN];
};
struct Snake snake;

struct Food {
    int x, y;
    int consumed;
};
struct Food food;

void draw_snake() {
    int i;
    
    for(i=snake.length-1; i>0; i--) {
        board[snake.part[i].y*cols + snake.part[i].x] = '*';
    }
    board[snake.part[0].y*cols + snake.part[0].x] = 'O';
}

void move_snake(int deltaX, int deltaY) {
    int i;

    for(i=snake.length-1; i>0; i--) {
        snake.part[i] = snake.part[i-1];
    }
    
    snake.part[0].x += deltaX;
    snake.part[0].y += deltaY;
}

void read_keyboard() {
    int ch = getch();
    
    switch(ch) {
        case 'w': move_snake( 0,-1); break;
        case 's': move_snake( 0, 1); break;
        case 'a': move_snake(-1, 0); break;
        case 'd': move_snake( 1, 0); break;        
    }
}
void setup_food() {

        food.x = 1 + rand() % (cols-2);
        food.y = 1 + rand() % (rows-2);
        food.consumed = 0;

}

void draw_food() {
    if (food.consumed == 1) 
    {
        setup_food();
    }
    set_text_color(YELLOW,CURRENT_BACKGROUND_COLOR);
    if( !food.consumed ) {
        board[food.y*cols + food.x] = '+';
    } 
    set_text_color(CURRENT_FOREGROUND_COLOR,CURRENT_BACKGROUND_COLOR);
}

int calculate_final_score(int snake_length) {
    // The snake length is multiplied by 100, we need to map it to a score between 1 and 10.
    if (snake_length < 10) {
        return 1;
    } else if (snake_length < 20) {
        return 2;
    } else if (snake_length < 30) {
        return 3;
    } else if (snake_length < 40) {
        return 4;
    } else if (snake_length < 50) {
        return 5;
    } else if (snake_length < 60) {
        return 6;
    } else if (snake_length < 70) {
        return 7;
    } else if (snake_length < 80) {
        return 8;
    } else if (snake_length < 90) {
        return 9;
    } else {
        return 10;
    }
}
void setup_snake() {
    snake.length = 1;
    snake.part[0].x = 1 + rand() % (cols-2);
    snake.part[0].y = 1 + rand() % (rows-2);
}

void game_rules() {
    int i;
    if( !food.consumed ) {
        if( food.x == snake.part[0].x &&
            food.y == snake.part[0].y ) {
                food.consumed = 1;
                snake.length++;
        }
    }

    
    if( snake.part[0].x == 0 || snake.part[0].x == cols-1 ||
        snake.part[0].y == 0 || snake.part[0].y == rows-1 ) {
            isGameOver = 1;
    }
    
    for(i=1; i<snake.length; i++) {
        if( snake.part[0].x == snake.part[i].x &&
            snake.part[0].y == snake.part[i].y ) {
                isGameOver = 1;
        }
    }
}

int snake_game()
{
    char c;
    srand(time(0));
    
    setup_snake();
    setup_food();
    
    while(!isGameOver) {
        fill_board();
        draw_food();
        draw_snake();
        game_rules();
        clear_screen();
        set_text_color(YELLOW,CURRENT_BACKGROUND_COLOR);
        printf("Snake Game, Score: %d\n", snake.length * 100);
        set_text_color(CYAN,CURRENT_BACKGROUND_COLOR);
        print_board();
        set_text_color(CURRENT_FOREGROUND_COLOR,CURRENT_BACKGROUND_COLOR);
        if( !isGameOver ) read_keyboard();
    }
    int final_score = calculate_final_score(snake.length);
    print_error("Game Over\n");
    printf("Final score: %d\n", final_score);
    A:
    c = getchar();
    if (c == '\n') return final_score;
    else goto A;

}
