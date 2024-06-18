#include "buttoncreator.h"
#include <windows.h>
#include <stdio.h>
int current_button = -1;
LRESULT CALLBACK WindowProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    switch (msg) {
        case WM_COMMAND:
            {
                int wmId = LOWORD(wParam);  // Extract the identifier of the button clicked
                switch (wmId) {
                    char string[256];
                    case ID_BASE_BUTTON + 0:
                    case ID_BASE_BUTTON + 1:
                    case ID_BASE_BUTTON + 2:
                        current_button = wmId - 1000;
                        sprintf(string, "%s.%d", "Button Clicked", wmId);
                        // Handle button click actions here
                        MessageBox(hWnd, string, "Info", MB_OK | MB_ICONINFORMATION);
                        // printf("button %d clicked", wmId);
                        break;
                    default:
                        return DefWindowProc(hWnd, msg, wParam, lParam);
                }
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

void CreateButtons(HWND hWnd, char* buttonLabels[], int numButtons, UINT_PTR* buttonIds) {
    for (int i = 0; i < numButtons; ++i) {
        // Create each button with a unique identifier
        HWND hButton = CreateWindow("BUTTON", buttonLabels[i], WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
                                    10, 10 + i * 40, 120, 30, hWnd, (HMENU)(UINT_PTR)(ID_BASE_BUTTON + i), GetModuleHandle(NULL), NULL);
        if (hButton == NULL) {
            MessageBox(NULL, "Failed to create button", "Error", MB_ICONERROR);
            return;
        }
        // Store the button ID in the array for later reference
        buttonIds[i] = ID_BASE_BUTTON + i;
    }
}
