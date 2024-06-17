#include <stdio.h>
#include "settings.h"
#include "theme.h"
#include <stdbool.h>
#include <conio.h>
#include "login.h"
#include "food_order_page.h"
#include "illustrations.h"
#include "map.h"
#include "restaurants_home.h"

bool veg_mode = false;

// Function to read address and distance for the current user from the file
UserDeliveryInfo readUserDeliveryInfo() {
    char filename[] = "delivery_address.txt";
    
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Failed to open file");
        exit(EXIT_FAILURE);
    }

    char line[MAX_LINE_LENGTH];
    UserDeliveryInfo userDeliveryInfo;
    int found = 0;
    char username[20];
    char address[50];
    float distance;
    while (fgets(line, sizeof(line), file) != NULL) {
        // Check if the current line contains the current user's information
        if (strstr(line, current_user_details.username) != NULL) {
            // Parse the line to extract the address and distance
            if (sscanf(line, "%[^:]: %[^,], %f km", username, address, &distance) == 3) {
            strcpy(userDeliveryInfo.address, address);
            userDeliveryInfo.distance = distance;
            found = 1;
            break;
            } else {
                // Handle sscanf failure (e.g., incorrect format in the line)
                // fprintf(stderr, "Error: Failed to parse line correctly.\n");
            }
        }
    }

    fclose(file);

    // If user's delivery information is not found, display an error message and exit
    if (!found) {
        // fprintf(stderr, "User delivery information not found for %s\n", current_user_details.username);
        userDeliveryInfo.distance = -1;
        strcpy(userDeliveryInfo.address , "none");
        return userDeliveryInfo;
    }


    return userDeliveryInfo;
}

void remove_user_delivery_details() {
    FILE *srcFile, *tempFile;
    char buffer[1000];
    readCurrentUser();
    // Open the original file for reading
    srcFile = fopen("delivery_address.txt", "r");
    if (srcFile == NULL) {
        print_error("Failed to open the file");
        return;
    }

    // Open a temporary file for writing
    tempFile = fopen("temp_delivery_address.txt", "w");
    if (tempFile == NULL) {
        print_error("Failed to open temporary file");
        fclose(srcFile);
        return;
    }

    while ((fgets(buffer, 1000, srcFile)) != NULL) {
        if (strstr(buffer, current_user_details.username) == NULL) {
            fputs(buffer, tempFile);
        }
    }

    // Close both the files
    fclose(srcFile);
    fclose(tempFile);

    remove("delivery_address.txt");

    rename("temp_delivery_address.txt", "delivery_address.txt");
}
void store_delivery_details(const char* address, float distance) {
    remove_user_delivery_details();
    FILE* file = fopen("delivery_address.txt", "a"); // Open the file in append mode
    if (file == NULL) {
        perror("Failed to open file");
        return;
    }
    readCurrentUser();

    // Write the details to the file
    fprintf(file, "%s: %s, %.2f km\n", current_user_details.username, address, distance);

    // Close the file
    fclose(file);
}
int select_delivery_address(){
    int n = 1;
    int index[MAX_CITIES];
    int choice;
    int found = 0;
    float max_dist = 0;
    double cost_matrix[MAX_CITIES][MAX_CITIES];
    double dist[V];
    Node *graph = create_graph_from_file("loc_data.txt");
    printf("%s",graph[3].name);
    char input_address[100]="";
    A:
    int x = 50,y=13;
    setCursor_inc(x,y++);
    printf("Search your address: ");
    scanf("%s",input_address);

    int address_count=0;
    for (int i = 0; i < V; i++)
    {
        if ((strstr(graph[i].name, input_address) != NULL) && strlen(input_address) > 0)
        {
            setCursor_inc(x,y++);
            set_text_color(BLACK,WHITE);
            printf("%d. %s\n", n++, graph[i].name);
            index[n - 1] = i;
            found = 1;
            address_count++;
        }
        if (address_count == 5)
        {
            break;
        }
        
    }
    if (found == 0)
    {
        print_error("No relevant nodes found.\n");
        goto A;
    }
    setCursor_inc(x,y++);
    printf("Enter your choice:");
    scanf("%d", &choice);
    if (choice > sizeof(index) / sizeof(index[0]))
    {
        printf("Invalid choice\n");
        goto A;
    }

    Node address_node = graph[index[choice]];
    setCursor_inc(x,y++);
    // printf("%s",graph[8].name);
    printf("You have selected %s\n", address_node.name);
    create_cost_matrix(cost_matrix, graph,&address_node);
    printf("testing cost matrix %lf",cost_matrix[10][20]);
    // printf("%s",graph[9].name);
    setCursor_inc(x,y++);
    printf("Enter the max distance of the restaurants:");
    scanf("%f", &max_dist);
    // dijkstra(cost_matrix, find_source_node_index(graph, address_node.name),-1, graph, dist);
    // for (int i = 0; i < V; i++)
    // {
    //     if (dist[i] < max_dist)
    //     {
    //         if (veg_mode)
    //         {
    //             if(isrestaurant(graph[i].name) && strcmp(find_restaurant(graph[i].name)->type,"veg") == 0){

    //                 // printNearbyRestaurant(i+1, graph[i].name,dist[i]);
    //                 printf("%s distance-%.2fkm\n", graph[i].name, dist[i]);
    //             }
    //         }else{
    //             if(isrestaurant(graph[i].name)){
    //                 // printNearbyRestaurant(i+1, graph[i].name,dist[i]);
    //                 printf("%s distance-%.2fkm\n", graph[i].name, dist[i]);
    //             }
    //         }
            
    //     }
    // }
    // getchar();
    // nearby_restaurants(address_node.name,max_dist);
    store_delivery_details(address_node.name,max_dist);
    return 1;
    
}

int add_delivery_address(bool selected){
        int x = 50,y=12;
        user_delivery_info = readUserDeliveryInfo();
        
        char ch;
        setCursor_inc(x,y++);
        if (selected)
        {
            set_text_color(BLUE,WHITE);
            printf("Add your address:");
            if (user_delivery_info.distance == -1)
            {
                set_text_color(BLACK,WHITE);
                ch = _getch();
                if (ch == 13)
                {
                    if(select_delivery_address()) return 1;
                }
                return 1;
            }
            set_text_color(WHITE,GREEN);
            printf(" %s - %f Km",user_delivery_info.address,user_delivery_info.distance);
            set_text_color(BLACK,WHITE);
            ch = _getch();
            if (ch == 13)
            {
                if(select_delivery_address()) return 1;
            }
        }else{
            set_text_color(BLACK,WHITE);
            printf("Add your address:");
            if (user_delivery_info.distance == -1)
            {
                return 1;
            }
            set_text_color(WHITE,GREEN);
            printf(" %s - %f Km",user_delivery_info.address,user_delivery_info.distance);
            set_text_color(BLACK,WHITE);
        }
        
        
}
int veg_selection(bool selected,bool veg_mode){
        int x = 50,y=7;
        setCursor_inc(x,y++);
        if (selected)
        {
            set_text_color(BLUE,WHITE);
            printf("Veg mode: ");
            printf("                                                     ");
            if (veg_mode)
            {  
                set_text_color(WHITE,GREEN);
                printf("  O N  ");
            }else{
                set_text_color(WHITE,RED);
                printf(" O F F ");
            }
            

        }else{
            set_text_color(BLACK,BLACK);
            printf("Veg mode: ");
            printf("                                                     ");
            if (veg_mode)
            {  
                set_text_color(WHITE,GREEN);
                printf(" O N ");
            }else{
                set_text_color(WHITE,RED);
                printf(" O F F ");
            }
        }

}

void update_veg_mode(bool veg_mode){
    readCurrentUser();
    FILE *file = fopen("current_user.txt", "w");
    if (file == NULL) {
        print_error("Error opening file 'current_user.txt' for writing");
        return;
    }
    if (veg_mode)
    {
        current_user_details.isveg =1;
    }else{
        current_user_details.isveg =0;
    }
    
   
    // printf("Wrote current user\n");

    fprintf(file, "%s %s %s %s %d", current_user_details.username, current_user_details.password, current_user_details.email, current_user_details.phone_no, current_user_details.isveg);

    fclose(file);
    
}

int change_preference(){
    char ch;
    char options[3][20] = {
        "veg_mode",
        "add_delivery_address"
    };
    int selected_option = 0;
    while(1){
        if (selected_option == 0){
            veg_selection(true,veg_mode);
        }else{
            veg_selection(false,veg_mode);
        }
        if(selected_option == 1){
            if(add_delivery_address(true)) return 1;
        }else{
            add_delivery_address(false);
        }
        ch = _getch();
        switch(ch)
        {
            case 72:
                if (selected_option > 0) selected_option--;
                break;
            case 80:
                if (selected_option < 1) selected_option++;
                break;
            case 13:
                if(selected_option == 0) veg_mode = !veg_mode;
                update_veg_mode(veg_mode);
                break;
            case '\t':
                return -1; 
                break;
            default:
                break;
                
        }
    }
}
   

int settings()
{
    int res;
    int x = 50,y=5;
    int selected_option = 0;
    int num_options = 2;
    char options[3][20]={
        "vegmode",
        "add_delivery_address"
    };
    char ch;
    while (1)
    {
        system("cls");
        set_text_color(BLACK,BLACK);
        home();
        printUserDetails();
        side_menu(-1);
        x = 50,y=5;
        setCursor_inc(x,y++);
        set_text_color(BLACK,WHITE);
        printf("Change preference");
        setCursor_inc(x,y++);
        printf("------------------------------------------------------------------------------------------------------------------------");
        res = change_preference(selected_option);
        if (res==-1)
        {
            return -1;
        }

        ch = _getch();
        switch (ch){
            case 72:
                selected_option = (selected_option - 1 + num_options) % num_options; 
                break;
            case 80:
                selected_option = (selected_option + 1) % num_options;
                break;
            case '\t':
                return -1;
            default:
                break;

        }
    }
    
    
    return 0;
}