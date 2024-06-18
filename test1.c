#include <stdio.h>
#include <windows.h>
void setCursor_inc(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
int F(int x,int y){
    setCursor_inc(x,y++);
        printf("%c%c%c%c%c",220,220,220,220,220);
    setCursor_inc(x,y++);
        printf("%c%c    ",220,220);
    setCursor_inc(x,y++);
        printf("%c%c%c%c%c",220,220,220,220,220);
    setCursor_inc(x,y++);
        printf("%c%c    ",220,220);
    setCursor_inc(x,y++);
        printf("%c%c    ",220,220);
    setCursor_inc(x,y++);
    
}
int O(int x,int y){
    setCursor_inc(x,y++);
        printf("%c%c%c%c%c",220,220,220,220,220);
    setCursor_inc(x,y++);
        printf("%c      %c",220,220);
    setCursor_inc(x,y++);
        printf("%c      %c",220,220);
    setCursor_inc(x,y++);
        printf("%c      %c",220,220);
    setCursor_inc(x,y++);
        printf("%c%c%c%c%c",220,220,220,220,220);
}

int V(int x,int y){
    setCursor_inc(x,y++);
        printf("%c   %c",220,220);
    setCursor_inc(x,y++);
        printf("%c   %c",220,220);
    setCursor_inc(x,y++);
        printf("%c   %c",220,220);
    setCursor_inc(x,y++);
        printf(" %c %c ",220,220);
    setCursor_inc(x,y++);
        printf("  %c  ",220);
}

int V(int x,int y){
    setCursor_inc(x,y++);
        printf("%c   %c",220,220);
    setCursor_inc(x,y++);
        printf(" %c %c ",220,220);
    setCursor_inc(x,y++);
        printf("  %c  ",220);
    setCursor_inc(x,y++);
        printf("  %c  ",220);
    setCursor_inc(x,y++);
        printf("  %c  ",220);
}
int A(int x,int y){
    setCursor_inc(x,y++);
        printf("%c%c%c%c%c",220,220,220,220,220);
    setCursor_inc(x,y++);
        printf("%c      %c",220,220);
    setCursor_inc(x,y++);
    setCursor_inc(x,y++);
        printf("%c%c%c%c%c",220,220,220,220,220);
        printf("%c      %c",220,220);
    setCursor_inc(x,y++);
        printf("%c      %c",220,220);
}
int D(int x,int y){
    setCursor_inc(x,y++);
        printf("%c%c%c%c%c",220,220,220,220,220);
    setCursor_inc(x,y++);
        printf("%c%c     %c",220,220,220);
    setCursor_inc(x,y++);
        printf("%c%c     %c",220,220,220);
    setCursor_inc(x,y++);
        printf("%c%c     %c",220,220,220);
    setCursor_inc(x,y++);
        printf("%c%c%c%c%c",220,220,220,220,220);
}

int I(int x,int y){
    setCursor_inc(x,y++);
        printf("%c%c%c%c%c",220,220,220,220,220);
    setCursor_inc(x,y++);
        printf("  %c  ",220);
    setCursor_inc(x,y++);
        printf("  %c  ",220);
    setCursor_inc(x,y++);
        printf("  %c  ",220);
    setCursor_inc(x,y++);
        printf("%c%c%c%c%c",220,220,220,220,220);
}

int E(int x,int y){
    setCursor_inc(x,y++);
        printf("%c%c%c%c%c",220,220,220,220,220);
    setCursor_inc(x,y++);
        printf("%c%c    ",220,220);
    setCursor_inc(x,y++);
        printf("%c%c%c%c%c",220,220,220,220,220);
    setCursor_inc(x,y++);
        printf("%c%c    ",220,220);
    setCursor_inc(x,y++);
        printf("%c%c%c%c%c",220,220,220,220,220);
}
int L(int x,int y){
    setCursor_inc(x,y++);
        printf("%c%c    ",220,220);
    setCursor_inc(x,y++);
        printf("%c%c    ",220,220);
    setCursor_inc(x,y++);
        printf("%c%c    ",220,220);
    setCursor_inc(x,y++);
        printf("%c%c    ",220,220);
    setCursor_inc(x,y++);
        printf("%c%c%c%c%c",220,220,220,220,220);
}
int R(int x,int y){
    setCursor_inc(x,y++);
    printf("%c%c%c%c%c",220,220,220,220,220);
    setCursor_inc(x,y++);
    printf("%c    %c",220,220);
    setCursor_inc(x,y++);
    printf("%c%c%c%c%c",220,220,220,220,220);
    setCursor_inc(x,y++);
    printf("%c %c  ",220,220);
    setCursor_inc(x,y++);
    printf("%c  %c",220,220);
    setCursor_inc(x,y++);
    printf("%c   %c",220,220);
}
int P(int x,int y){
    setCursor_inc(x,y++);
    printf("%c%c%c%c%c",220,220,220,220,220);
    setCursor_inc(x,y++);
    printf("%c    %c",220,220);
    setCursor_inc(x,y++);
    printf("%c%c%c%c%c",220,220,220,220,220);
    setCursor_inc(x,y++);
    printf("%c    ",220);
    setCursor_inc(x,y++);
    printf("%c   ",220);
    setCursor_inc(x,y++);
    printf("%c    ",220);
}

int main(){
    F(0,0);
    O(0,5);
    O(0,10);
    D(0,15);
    D(0,20);
    E(0,25);
    L(0,30);
    I(0,35);
    V(0,40);
    E(0,45);
    R(0,50);
    Y(0,55);
    A(0,60);
    P(0,65);
    P(0,70);
}