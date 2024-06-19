#include "buttoncreator.h"
#include <windows.h>
#include <stdio.h>
int current_button = -1;
LRESULT CALLBACK WindowProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    switch (msg) {
        case WM_COMMAND:
            {
                int wmId = LOWORD(wParam);  // Extract the identifier of the button clicked
                char string[256];
                current_button = wmId - 999;
                sprintf(string, "%s.%d", "Button Clicked", current_button);
                DestroyWindow(hWnd);
                // switch (wmId) {
                //     case ID_BASE_BUTTON + 0:
                //     case ID_BASE_BUTTON + 1:
                //     case ID_BASE_BUTTON + 2:
                //         // Handle button click actions here
                //         MessageBox(hWnd, string, "Info", MB_OK | MB_ICONINFORMATION);
                //         // printf("button %d clicked", wmId);
                //         break;
                //     default:
                //         return DefWindowProc(hWnd, msg, wParam, lParam);
                // }
            }
            break;
        case WM_CLOSE:
            DestroyWindow(hWnd);
            break;
        case WM_DESTROY:
            PostQuitMessage(0);
            break;
        default:
            return DefWindowProc(hWnd, msg, wParam, lParam);
    }
    return 0;
}

void CreateButtons(HWND hWnd, char* buttonLabels[], int numButtons) {
    const int buttonWidth = 150;
    const int buttonHeight = 30;
    const int padding = 10;

    // Determine the number of columns and rows for grid layout
    int maxColumns = 4;  // Max columns to use, adjust as needed
    int columns = (numButtons < maxColumns) ? numButtons : maxColumns;
    int rows = (numButtons + columns - 1) / columns;  // Ceiling division

    // Calculate the total width and height needed for the buttons
    int totalWidth = columns * (buttonWidth + padding) - padding;
    int totalHeight = rows * (buttonHeight + padding) - padding;

    // Resize the window to fit all buttons if necessary
    SetWindowPos(hWnd, NULL, 0, 0, totalWidth + 40, totalHeight + 60, SWP_NOMOVE | SWP_NOZORDER);

    // Calculate the starting point to center the buttons
    RECT clientRect;
    GetClientRect(hWnd, &clientRect);
    int startX = (clientRect.right - totalWidth) / 2;
    int startY = (clientRect.bottom - totalHeight) / 2;

    for (int i = 0; i < numButtons; ++i) {
        int row = i / columns;
        int col = i % columns;

        int x = startX + col * (buttonWidth + padding);
        int y = startY + row * (buttonHeight + padding);

        HWND hButton = CreateWindow("BUTTON", buttonLabels[i], WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
                                    x, y, buttonWidth, buttonHeight, hWnd, (HMENU)(UINT_PTR)(ID_BASE_BUTTON + i), GetModuleHandle(NULL), NULL);
        if (hButton == NULL) {
            MessageBox(NULL, "Failed to create button", "Error", MB_ICONERROR);
            return;
        }
    }
}