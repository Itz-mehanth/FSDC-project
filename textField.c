#include <windows.h>
#include <stdio.h>
#include "buttoncreator.h"  // Assuming this header contains CreateButtons function prototype

#define ID_BASE_BUTTON 1000  // Base ID for the buttons

// Declare your window procedure function
// LRESULT CALLBACK WindowProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
int InputPopup(char *customButtonLabels[],int customNumButtons) {
    static int classRegistered = 0; // Static variable to ensure the class is registered only once
    // Register the window class
    if (classRegistered == 0)
    {
        WNDCLASS wc = { 0 };
        wc.lpfnWndProc = WindowProc;  // Set the window procedure function
        wc.hInstance = GetModuleHandle(NULL);
        wc.lpszClassName = "MyWindowClass";
        
        if (!RegisterClass(&wc)) {
            MessageBox(NULL, "Failed to register window class", "Error", MB_ICONERROR);
            return 1;
        }
        classRegistered = 1;  // Set the flag to indicate the class is registered
    }


    // Create the main window
    HWND hWnd = CreateWindowEx(0, "MyWindowClass", "Dynamic Button Example",
                               WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT,
                               80, 20, NULL, NULL, GetModuleHandle(NULL), NULL);

    if (!hWnd) {
        MessageBox(NULL, "Failed to create window", "Error", MB_ICONERROR);
        return 1;
    }
    
    // Define your custom button labels and count
    
    // Array to store button IDs for later reference
    UINT_PTR buttonIds[3];  // Adjust the size based on your number of buttons
    // Create buttons dynamically based on custom array
    CreateButtons(hWnd, customButtonLabels, customNumButtons);
    
    // Show the main window
    ShowWindow(hWnd, SW_SHOWDEFAULT);
    UpdateWindow(hWnd);
    
    // Message loop
    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    
    return (int)msg.wParam;
}