#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
void* background_function(void* arg) {
    while (1) {
        // Your background task goes here.
        // For demonstration, we just print a message every second.
        printf("Background function is running...\n");
        sleep(1); // Sleep for 1 second.
    }
    return NULL;
}

int main() {
    pthread_t thread_id;
    
    // Create the background thread
    if (pthread_create(&thread_id, NULL, background_function, NULL) != 0) {
        perror("Failed to create thread");
        return 1;
    }

    // Main loop of the main thread
    for (int i = 0; i < 5; i++) {
        printf("Main function is running...\n");
        sleep(2); // Sleep for 2 seconds.
    }

    // Optionally, you can join the thread if you need to wait for it to finish
    pthread_cancel(thread_id); // Cancel the thread if it's still running
    pthread_join(thread_id, NULL); // Wait for the thread to finish

    return 0;
}
