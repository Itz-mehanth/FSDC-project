// buttoncreator.h

#ifndef BUTTONCREATOR_H
#define BUTTONCREATOR_H

#define ID_BASE_BUTTON 1000  // Adjust as necessary
#include <windows.h>
extern int current_button;
// Declare WindowProc function
LRESULT CALLBACK WindowProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

// Other function declarations
void CreateButtons(HWND hWnd, char* buttonLabels[], int numButtons, UINT_PTR* buttonIds);

#endif // BUTTONCREATOR_H


