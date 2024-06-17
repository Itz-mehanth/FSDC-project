#include <windows.h>
#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")  // Link against the winmm library

#include "sounds.h"

void select_beep(){
    PlaySound(TEXT("click.wav"), NULL, SND_FILENAME | SND_ASYNC);

    // Beep(4300,200);
}
void notification_beep(){
    PlaySound(TEXT("notification.wav"), NULL, SND_FILENAME | SND_ASYNC);
}

void error_beep(){
    PlaySound(TEXT("error.mp3"), NULL, SND_FILENAME | SND_ASYNC);
}

void car_horn(){
    PlaySound(TEXT("car_horn.wav"), NULL, SND_FILENAME | SND_ASYNC);
}