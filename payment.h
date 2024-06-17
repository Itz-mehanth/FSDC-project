#ifndef PAYMENT
#define PAYMENT

#include <stdio.h>
#include <string.h>
#include <time.h>
#include <windows.h>
#include <stdlib.h>

char* generate_transaction_id() ;
int simulate_processing();
void display_confirmation(float amount);

int upi_simulation();
int simulate_payment() ;        
int payment();

#endif // !PAYMENT