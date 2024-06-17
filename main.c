#include <stdio.h>
#include <stdlib.h>
#include "delivery_boy_selection.h"
#include "illustrations.h"
#include "login.h"
#include "theme.h"
#include "food_order_page.h"
#include "restaurants_home.h"
#include "animations.h"
#include "notification.h"


int main(){
    printf("\n\n\n\n\n\n\n\n\n\n");
    welcome_pop();
    carAnime();
    int loginRes;
    system("cls");
    // home();
    HOME:
    set_text_color(BLACK,BLACK);
    // print_error("Sorry you are not logged in");
    if (UserType() == 2)
    {
        delivery_boy_login();
        goto HOME;
    }
    A:
    loginRes = loginFunction();
    if(loginRes == 2){
        B:
        if(restaurantsHomeFunction()==2){
            goto A;
        }
        else {
            C:
            if(foodOrder()==2){
                goto A;
            }
        }
    }else if (loginRes == 0)
    {
        goto HOME;
    }
    else{
        goto C;
    }
    return 1;
}