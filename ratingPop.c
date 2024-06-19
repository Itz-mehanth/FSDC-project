#include <windows.h>
#include <stdio.h>
#include <stdlib.h>

INT_PTR CALLBACK RatingDialogProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam) {
    switch (message) {
        case WM_INITDIALOG:
            return (INT_PTR)TRUE;
        case WM_COMMAND:
            if (LOWORD(wParam) == IDOK) {
                char buffer[3];
                GetDlgItemText(hDlg, 1001, buffer, sizeof(buffer));
                int rating = atoi(buffer);
                EndDialog(hDlg, rating);
                return (INT_PTR)TRUE;
            } else if (LOWORD(wParam) == IDCANCEL) {
                EndDialog(hDlg, -1);
                return (INT_PTR)TRUE;
            }
            break;
    }
    return (INT_PTR)FALSE;
}

int main() {
    // Define the dialog template in memory
    DLGTEMPLATE dlgTemplate = {0};
    dlgTemplate.style = DS_MODALFRAME | WS_POPUP | WS_CAPTION | WS_SYSMENU;
    dlgTemplate.cx = 186;
    dlgTemplate.cy = 95;
    dlgTemplate.cdit = 4; // Number of controls

    // Dialog item template array
    struct {
        DLGITEMTEMPLATE tmpl;
        WORD classAtom;
        WORD id;
        WORD text;
        BYTE extraData;
    } items[4] = {
        // Static text
        {{WS_VISIBLE | WS_CHILD | SS_LEFT, 0, 7, 7, 172, 8, -1, 0, 0, 0}, 0xFFFF, -1, L"Enter your rating (1-5):", 0},
        // Edit control
        {{WS_VISIBLE | WS_CHILD | WS_BORDER | ES_AUTOHSCROLL, 0, 7, 20, 172, 14, 1001, 0, 0, 0}, 0xFFFF, 0x0081, 0, 0},
        // OK button
        {{WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, 0, 39, 45, 50, 14, IDOK, 0, 0, 0}, 0xFFFF, 0x0080, L"OK", 0},
        // Cancel button
        {{WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON, 0, 95, 45, 50, 14, IDCANCEL, 0, 0, 0}, 0xFFFF, 0x0080, L"Cancel", 0},
    };

    // Combine templates into a single buffer
    size_t dlgSize = sizeof(DLGTEMPLATE) + sizeof(items);
    DLGTEMPLATE* dlgBuffer = (DLGTEMPLATE*)malloc(dlgSize);
    memcpy(dlgBuffer, &dlgTemplate, sizeof(DLGTEMPLATE));
    memcpy((BYTE*)dlgBuffer + sizeof(DLGTEMPLATE), items, sizeof(items));

    // Create the dialog box and get the rating
    int rating = DialogBoxIndirect(GetModuleHandle(NULL), dlgBuffer, NULL, RatingDialogProc);
    if (rating != -1) {
        printf("User rating: %d\n", rating);
    } else {
        printf("User canceled the input.\n");
    }

    free(dlgBuffer);
    return 0;
}
