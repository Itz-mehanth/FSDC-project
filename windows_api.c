#include <Windows.h>
#include <stdio.h>
#include <conio.h>

int main() {
    _getch(); // Wait for a key press
    // Check if the 'A' key is pressed
    if (GetAsyncKeyState('A') & 0x8000) {
        printf("The 'A' key is currently pressed.\n");
    }
// Check if the arrow keys, tab, or space bar are pressed
    if (GetAsyncKeyState(VK_LEFT) & 0x8000) {
        printf("The left arrow key is currently pressed.\n");
    }
    if (GetAsyncKeyState(VK_RIGHT) & 0x8000) {
        printf("The right arrow key is currently pressed.\n");
    }
    if (GetAsyncKeyState(VK_UP) & 0x8000) {
        printf("The up arrow key is currently pressed.\n");
    }
    if (GetAsyncKeyState(VK_DOWN) & 0x8000) {
        printf("The down arrow key is currently pressed.\n");
    }
    if (GetAsyncKeyState(VK_TAB) & 0x8000) {
        printf("The tab key is currently pressed.\n");
    }
    if (GetAsyncKeyState(VK_SPACE) & 0x8000) {
        printf("The space bar is currently pressed.\n");
    }
    if (GetAsyncKeyState(VK_RETURN) & 0x8000) {
        printf("The enter key is currently pressed.\n");
    }
    return 0;
}
