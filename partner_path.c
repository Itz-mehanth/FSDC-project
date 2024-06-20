#include "partner_path.h"
#include "delivery_boy_selection.h"
#include <stdio.h>
#include <stdlib.h>
#include "illustrations.h"
#include "food_order_page.h"
#include "theme.h"
#include "login.h"
#include "sounds.h"
#include "buttonCreator.h"
#include "textField.h"
#include <string.h>
#include <math.h>
#include "map.h"
#include <stdbool.h>
#include <limits.h>
#include <time.h>
#include <float.h>
#define TOLERANCE 0.000001

typedef struct {
    char deliveryperson[100];
    char deliveryaddress[200];
    struct tm start_time;
    struct tm end_time;
} DeliveryRecord;

char partner_path[100][100];
int partner_path_length=0;

int stringToTime(const char *datetime, struct tm *tm) {
    memset(tm, 0, sizeof(struct tm));
    if (sscanf(datetime, "%d-%d-%d %d:%d:%d",
               &tm->tm_year, &tm->tm_mon, &tm->tm_mday,
               &tm->tm_hour, &tm->tm_min, &tm->tm_sec) != 6) {
        return -1;
    }
    tm->tm_year -= 1900; // Adjust year
    tm->tm_mon -= 1; // Adjust month
    return 0;
}

// Function to find the start and end time for a specific delivery person and address
int findDeliveryTimes(DeliveryRecord records[], int record_count, const char* deliveryperson, const char* deliveryaddress, struct tm* start_time, struct tm* end_time) {
    for (int i = 0; i < record_count; i++) {
        if (strcmp(records[i].deliveryperson, deliveryperson) == 0 &&
            strcmp(records[i].deliveryaddress, deliveryaddress) == 0) {
            *start_time = records[i].start_time;
            *end_time = records[i].end_time;
            return 1; // Success
        }
    }
    return 0; // Not found
}

// Function to load delivery records from a CSV file
int loadDeliveryRecords(const char* filename, DeliveryRecord records[], int max_records) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        perror("Unable to open file");
        return -1;
    }

    char line[512];
    int record_count = 0;

    while (fgets(line, sizeof(line), file) && record_count < max_records) {
        char deliveryperson[100], deliveryaddress[200], start_time_str[20], end_time_str[20];

        // Parse the CSV line
        if (sscanf(line, "%[^,],%[^,],%[^,],%s", deliveryperson, deliveryaddress, start_time_str, end_time_str) == 4) {
            strcpy(records[record_count].deliveryperson, deliveryperson);
            strcpy(records[record_count].deliveryaddress, deliveryaddress);
            stringToTime(start_time_str,&records[record_count].start_time);
            stringToTime(end_time_str,&records[record_count].end_time);
            record_count++;
        }
    }

    fclose(file);
    return record_count;
}

int find_node_by_loc(Node* graph,double lat,double lon) {
    char partnerStatus[100];
  // Search for the source node by name
  for (int i = 0; i < num_cities; i++) {
    if (fabs(lat - graph[i].latitude) < TOLERANCE && fabs(lon - graph[i].longitude) < TOLERANCE) {
        sscanf(partnerStatus, "the partner is in %s\n",graph[i].name);
        // print_success(partnerStatus);
        return i; // Return index if found
    }
  }

  return -1;
}

double diff_tm(struct tm *a, struct tm *b) {
    return difftime(mktime(a), mktime(b));
}

struct tm get_current_time() {
    time_t t = time(NULL);
    struct tm current_time;
    localtime_s(&current_time, &t);
    return current_time;
}

double calculateTraveledPercentage(struct tm start_tm, struct tm end_tm) {
    struct tm current_time = get_current_time();
    
    double diff_start = diff_tm(&current_time, &start_tm);
    double diff_end = diff_tm(&end_tm, &start_tm);

    if (diff_start < 0) {
        return 0.0; // Travel hasn't started yet
    } else if (diff_start >= diff_end) {
        return 100.0; // Travel has finished
    } else {
        double traveled_percentage = (diff_start / diff_end) * 100.0;
        return traveled_percentage;
    }
}

void addSecondsToCurrentTime(int secondsToAdd, char *timestamp) {
    struct tm current_time = get_current_time();

    // Add seconds to current time
    current_time.tm_sec += secondsToAdd;

    // Normalize the time in case it goes over bounds
    mktime(&current_time);

    // Format the modified time as a timestamp string
    if (strftime(timestamp, 50, "%Y-%m-%d %H:%M:%S", &current_time) == 0) {
        print_error("strftime failed");
    }
}

void clear_partner_path() {
    for (int i = 0; i < 100; i++) {
        partner_path[i][0] = '\0';
    }
    partner_path_length = 0;
}

// Function to reconstruct and print the shortest path from source
int printDeliveryPath(int parent[], int j, Node* graph_arr,FILE *fp) {
    static int index = 0; // Static index to keep track of the path array position
    if (parent[j] == -1) {
        // If j is the source vertex
        strcpy(partner_path[index++], graph_arr[j].name);
        fprintf(fp,"%s ", graph_arr[j].name);
        // printf("%-60s%c\n", graph_arr[j].name, 219);
        return index;
    }
    
    printDeliveryPath(parent, parent[j], graph_arr,fp);
    partner_path_length++;
    strcpy(partner_path[index++], graph_arr[j].name);
    fprintf(fp,"%s ", graph_arr[j].name);
    // printf("%-60s%c\n", graph_arr[j].name, 219);
}

// Function that implements dijkstra_for_partner's single source shortest path algorithm
// for a graph represented using adjacency matrix representation
double dijkstra_for_partner(double graph[V][V], int src, int dest, Node* graph_arr, double dist[V],int to_write) {
    // printf("running dijkstra_for_partner\n");
    int sptSet[V]; // sptSet[i] will be true if vertex i is included in shortest path tree
    int parent[V]; // Array to store constructed path
    // Initialize all distances as INFINITE and stpSet[] as false
    for (int i = 0; i < V; i++)
        dist[i] = INF, sptSet[i] = 0, parent[i] = -1;

    // Distance of source vertex from itself is always 0
    dist[src] = 0;

    // Find shortest path for all vertices
    for (int count = 0; count < V - 1; count++) {
        // Pick the minimum distance vertex from the set of vertices not
        // yet processed. u is always equal to src in the first iteration.
        int u = minDistance(dist, sptSet);

        // Mark the picked vertex as processed
        sptSet[u] = 1;
        // Update dist value of the adjacent vertices of the picked vertex.
        for (int v = 0; v < V; v++) {
            if (!sptSet[v] && graph[u][v] && dist[u] != INF
                && dist[u] + graph[u][v] < dist[v]) {
                parent[v] = u;
                dist[v] = dist[u] + graph[u][v];
                // printf("%d.%lf\n", v,dist[v]);
            }
        }
    }

    if (to_write) 
    {
        // printf("Paths from source %s to destination is:\n", graph_arr[src].name, graph_arr[dest].name);
        // getchar();
        FILE *fp = fopen("delivery_details.txt", "a");
        printDeliveryPath(parent, dest, graph_arr,fp);
        fclose(fp);
    }
    
    // print the constructed distance array
    // printSolution(dist,V,graph_arr);
    if(dest != -1){
        // printf("distances from the source:");
        // printSolution(dist, V,graph_arr);
        // printf("shortest disttance from source %s:\n", graph_arr[src].name);
        // printf("%s --> %s", graph_arr[src].name, graph_arr[dest].name);
        // printf("= %lf\n",dist[dest]);

        // // print the constructed path array
        
        // printf("%lf is the min distance ", dist[dest]);
        return dist[dest];
    }

    return -1;
}


int isPartner(double latitude, double longitude) {
    FILE *file = fopen("delivery_boys_details.txt", "r");
    if (file == NULL) {
        print_error("Error opening file.\n");
        return 0;
    }
    char username[20], password[20], email[20], phone_no[20];
    double lat,lon;
    float ratings;
    int total_ratings,estimated_sec;
    num_del_boys = 0;
    while (fscanf(file, "%s %s %s %s %lf %lf %f %d %d", username, password, email, phone_no, &lat, &lon,&ratings,&total_ratings,&estimated_sec) == 9) {

        // printf("%lf == %lf = %d %lf == %lf = %d\n",lat,latitude,lat == latitude ,lon,longitude, lon == longitude);
        if (fabs(lat - latitude) < TOLERANCE && fabs(lon - longitude) < TOLERANCE)
        {
            // printf("match found\n");
            return 1;
        }
        num_del_boys++;
    }

    fclose(file);
    return 0;
}
Partner find_partner(double latitude, double longitude){
    Partner partner;
    FILE *file = fopen("delivery_boys_details.txt", "r");
    if (file == NULL) {
        print_error("Error opening file.\n");
        return partner;
    }
    num_del_boys = 0;
    while (fscanf(file, "%s %s %s %s %lf %lf %f %d %d", partner.username, partner.password, partner.email, partner.phone_no, &partner.lat, &partner.lon,&partner.ratings,&partner.total_ratings,&partner.estimated_sec) == 9) {
        // printf("%s %s %s %s %lf %lf %f %d %d\n",partner.username, partner.password, partner.email, partner.phone_no, partner.lat, partner.lon,partner.ratings,partner.total_ratings,partner.estimated_sec);
        
        if (fabs(partner.lat - latitude) < TOLERANCE && fabs(partner.lon - longitude) < TOLERANCE)
        {
            // printf("match found\n");
            return partner;
        }
    }

    fclose(file);
    return partner;
}

void convert_sec_to_time(int durationInSec, int *hours, int *minutes, int *seconds) {
    *hours = durationInSec / 3600;
    durationInSec %= 3600;
    *minutes = durationInSec / 60;
    *seconds = durationInSec % 60;
}

int calculate_travel_time(double distanceInKm, double averageSpeedKmPerHr, int *hours, int *minutes, int *seconds) {
    // Calculate total time in seconds
    double totalTimeInHours = distanceInKm / averageSpeedKmPerHr;
    int totalTimeInSec = (int)(totalTimeInHours * 3600);
    // printf("time in sec:%d", totalTimeInSec);
    // getchar();
    // Convert total time in seconds to hours, minutes, and seconds
    convert_sec_to_time(totalTimeInSec, hours, minutes, seconds);
    return totalTimeInSec;
}
double generate_random_speed(double minSpeed, double maxSpeed) {
    // Generate a random speed between minSpeed and maxSpeed
    double randomSpeed = minSpeed + (double)rand() / RAND_MAX * (maxSpeed - minSpeed);
    return randomSpeed;
}
void update_partner_rating(char *name, int new_rating) {
    FILE *fp;
    char line[256];  // Buffer for reading lines
    int found = 0;

    // Open the file in read/write mode
    fp = fopen("delivery_boys_details.txt", "r+");
    if (fp == NULL) {
        perror("Error opening file");
        return;
    }

    // Read each line from the file
    while (fgets(line, sizeof(line), fp)) {
        char currentName[100];
        int estimatedSec;
        long currentPos = ftell(fp);  // Get current position
        char password[20], email[40], phone_no[20];
        double lat, lon;
        float ratings;
        int total_ratings;

        // Parse the line into components
        sscanf(line, "%s %s %s %s %lf %lf %f %d %d\n",
               currentName, password, email, phone_no, &lat, &lon, &ratings, &total_ratings, &estimatedSec);

        // Check if the name matches
        if (strcmp(currentName, name) == 0) {
            // Calculate new average ratings
            float new_average_ratings = ((ratings * total_ratings) + new_rating) / (total_ratings + 1);

            // Move the file pointer back to the start of the line
            fseek(fp, currentPos-strlen(line)-1, SEEK_SET);

            // Update the line with new average ratings and increment total_ratings
            fprintf(fp, "%s %s %s %s %.6lf %.6lf %.6f %d %d\n",
                    currentName, password, email, phone_no, lat, lon, new_average_ratings, total_ratings + 1, estimatedSec);

            found = 1;
            break;  // No need to continue searching
        }
    }

    // Close the file
    fclose(fp);

    if (!found) {
        // printf("Name '%s' not found in the file.\n", name);
    } else {
        // printf("Updated ratings for '%s' successfully.\n", name);
    }
}

void add_delivery_boy_status(Partner partner, char timestamp[20], char *address) {
    FILE *f = fopen("delivery_boys_status.txt", "a");
    if (f == NULL) {
        print_error("Error opening file.\n");
        return;
    }

    struct tm now = get_current_time();
    char current_timestamp[20];

    // Format the time into a string
    if (strftime(current_timestamp, sizeof(current_timestamp), "%Y-%m-%d %H:%M:%S", &now) == 0) {
        print_error("strftime failed");
    }

    fprintf(f, "%s,%s,%s,%s\n", partner.username, address, current_timestamp, timestamp);
    fclose(f);
}


void convert_seconds(int total_seconds, int *hours, int *minutes, int *seconds) {
    // Calculate hours
    *hours = total_seconds / 3600;
    
    // Calculate remaining minutes
    *minutes = (total_seconds % 3600) / 60;
    
    // Calculate remaining seconds
    *seconds = total_seconds % 60;
}
void printNearbyPartner(int n, Partner partner,float distance,char *address,char *partneraddress)
{
    // printf("the input distance is %lf", distance);
    int hours, minutes,seconds;
    double minSpeed = 20,maxSpeed = 80;
    int totalTravelTime;
    totalTravelTime = calculate_travel_time(distance,generate_random_speed(minSpeed,maxSpeed),&hours, &minutes, &seconds);
    // printf("calculating travel time in sec %d\n",totalTravelTime);
    // printf("hours: %d minutes: %d seconds :   %d\n",hours,minutes,seconds);
    // printf("%d + %d",partner.estimated_sec,totalTravelTime);
    // getchar();
    char timestamp[20];
    addSecondsToCurrentTime(totalTravelTime, timestamp);
    // printf("adding status\n");
    add_delivery_boy_status(partner,timestamp,address);

    int y, x;
    if (n - 1 < 5)
    {
        y = 15;
        x = (n - 1) * 35 + 80;
    }
    else
    {
        y = 25;
        x = (n - 6) * 35 + 80;
    }

    setCursor_inc(x, y);
    y++;
    set_text_color(RED, YELLOW);
    printf("[%d] Partner Details                  ", n);
    set_text_color(CURRENT_FOREGROUND_COLOR, CURRENT_BACKGROUND_COLOR);

    setCursor_inc(x, y);
    y++;
    printf("                                      ");
    setCursor_inc(x, y);
    y++;
    set_text_color(BLUE, WHITE);
    printf("         %-21s        ", partner.username);

    setCursor_inc(x, y);
    y++;
    printf("                                      ");

    setCursor_inc(x, y);
    y++;
    set_text_color(YELLOW, WHITE);
    printf("     *");
    set_text_color(BLACK, WHITE);
    printf(" %.2f (", partner.ratings);

    set_text_color(GREEN, WHITE);
    printf("%d", partner.total_ratings);
    set_text_color(BLACK, WHITE);
    printf(")            ");
    set_text_color(BLUE, WHITE);
    printf("%-8.2f Km",distance);
    setCursor_inc(x, y);
    y++;
    printf(" Estimated time:                      ");
    setCursor_inc(x, y);
    y++;
    printf(" %2d hours:%2d minutes                 ",hours, minutes);
    setCursor_inc(x, y);
    y++;
    printf(" Partner Location: %-18s ",partneraddress);

    setCursor_inc(x, y);
    y++;
    
    if (n == 9)
    {
        setCursor_inc(0, 32);
    }

    set_text_color(CURRENT_FOREGROUND_COLOR, WHITE);
}


int getNumberOfRows(char arr[100][100],int MAX_ROWS) {
    int rows = 0;
    for (int i = 0; i < MAX_ROWS; i++) {
        if (arr[i][0] != '\0') {
            rows++;
        } else {
            break;
        }
    }
    return rows;
}

// Function to normalize a value between min and max to a range of 0 to 1
void addDeliveryDetails(char *partnerName, struct tm *time, char partner_path[100][100],int path_length){
    FILE *f = fopen("delivery_details.txt", "a");
    if (f == NULL) {
        print_error("Error opening file.\n");
        return;
    }
    fprintf(f, ",%s,%d/%d/%d,%d:%d:%d\n", partnerName, time->tm_mday, time->tm_mon + 1, time->tm_year + 1900, time->tm_hour, time->tm_min, time->tm_sec);
    // printf("%s,%d/%d/%d,%d:%d:%d,", partnerName, time->tm_mday, time->tm_mon + 1, time->tm_year + 1900, time->tm_hour, time->tm_min, time->tm_sec);
    clear_partner_path();
    fclose(f);
}

void update_partner_location(Node *partnerLocation, Partner *partner) {
    FILE *f = fopen("delivery_boys_details.txt", "r");
    if (f == NULL) {
        perror("Error opening file");
        return;
    }

    FILE *tempFile = fopen("temp.txt", "w");
    if (tempFile == NULL) {
        perror("Error opening temporary file");
        fclose(f);
        return;
    }

    Partner temp;
    bool found = false;

    // Read each partner record and write to the temp file, updating the target partner's location
    while (fscanf(f, "%s %s %s %s %lf %lf %f %d %d", temp.username, temp.password, temp.email, temp.phone_no,&temp.lat, &temp.lon,&temp.ratings, &temp.total_ratings, (int *)&temp.current_del_boy,&temp.estimated_sec) == 9) {
        if (strcmp(temp.username, partner->username) == 0) {
            temp.lat = partnerLocation->latitude;
            temp.lon = partnerLocation->longitude;
            found = true;
        }
        fprintf(tempFile, "%s %s %s %s %lf %lf %f %d %d\n", temp.username, temp.password, temp.email, temp.phone_no,
                  temp.lat, temp.lon,temp.ratings, temp.total_ratings, temp.current_del_boy,temp.estimated_sec);
    }

    fclose(f);
    fclose(tempFile);

    if (found) {
        // Replace the original file with the updated temp file
        remove("delivery_boys_details.txt");
        rename("temp.txt", "delivery_boys_details.txt");
        // printf("Partner location updated successfully.\n");
    } else {
        remove("temp.txt");
    }

    FILE *fp = fopen("delivery_boys_details.txt", "r+");
    if (fp == NULL)
    {
        print_error("Error opening file");
        return;
    }
    fclose(fp);
    
}

// Function to find the best delivery person based on scores

void partnerFinder(char *restaurant, char *sourcename){
    double dist[V];
    double cost_matrix[MAX_CITIES][MAX_CITIES];
    readcostsFromFile(cost_matrix);
    Partner chosen_partner;
    int partner_location_index;
    Node *graph = create_graph_from_file("new_loc_data.txt");
    // for (int i = 0; i < num_cities; i++)
    // {
    //     printf("%d.%s\n", i+1,graph[i].name);
    // }
    // getchar();
    if (graph == NULL)
    {
        printf("Error reading file\n");
        return ;
    }
    set_text_color(BLACK,WHITE);

    int total_partners;
    // printf("Restaurant: %s\nSource: %s\n",restaurant,sourcename);
    int restaurant_location_index=find_source_node_index(graph,restaurant);
    int destination_location_index=find_source_node_index(graph,sourcename);
    // printf("Partner location: %d\nRestaurant location: %d\nDestination location: %d\n",partner_location_index,restaurant_location_index,destination_location_index);
    readPartnersFromFile();
    readcostsFromFile(cost_matrix);

    double min_dist_part_rest = INF;
    double min_dist_user_rest;
    double current_dist_part_rest;
    float max_ratings = 0.0;

    // printf("The total number of delivery partners: %d\n",num_del_boys);
    for (int i = 0; i < num_del_boys; i++)
    {
        partner_location_index = find_node_by_loc(graph,partners[i].lat,partners[i].lon);
        // printf("The partner location: %d\n",partner_location_index);
        current_dist_part_rest = dijkstra_for_partner(cost_matrix, partner_location_index, restaurant_location_index ,graph,dist,0);
        // printf("%lf == %lf\n",current_dist_part_rest, min_dist_part_rest);
        if (current_dist_part_rest < min_dist_part_rest) 
        {
            min_dist_part_rest = current_dist_part_rest;
            chosen_partner = partners[i];
            partner_location_index = find_node_by_loc(graph,partners[i].lat,partners[i].lon);
        }
    }

    current_dist_part_rest = dijkstra_for_partner(cost_matrix, partner_location_index, restaurant_location_index ,graph,dist,1);
    // printf("you delivery person name is %s\n", chosen_partner.username);
    // getchar();
    struct tm time = get_current_time();
    min_dist_user_rest = dijkstra_for_partner(cost_matrix, restaurant_location_index, destination_location_index  ,graph,dist,1);
    // printf("finding rest dest path\n");
    // getchar();
    home();
    printUserDetails();
    home_page_banner();
    side_menu(-1);
    int partnerCurrentLoc_idx = find_node_by_loc(graph,chosen_partner.lat,chosen_partner.lon);
    char currentPartnerLoc[100];
    strcpy(currentPartnerLoc,graph[partnerCurrentLoc_idx].name);
    printNearbyPartner(1,chosen_partner,min_dist_part_rest+min_dist_user_rest,sourcename,currentPartnerLoc);
    Node* partnerLocation;
    partnerLocation= find_node_by_name(graph,sourcename);
    update_partner_location(partnerLocation,&chosen_partner);
    int response = MessageBox(NULL, "Wanna give rating", "Opinion", MB_ICONQUESTION | MB_YESNOCANCEL);

    if(response == IDYES){
        int user_rating;
        MessageBox(NULL, "You chose to proceed.", "Proceeding", MB_ICONINFORMATION | MB_OK);
        char *ratingsLabels[] = { "1 Star","2 Star","3 Star","4 Star","5 Star"};
        InputPopup(ratingsLabels,5);
        user_rating = current_button;
        select_beep();

        if(user_rating>0 && user_rating<6){
            update_partner_rating(chosen_partner.username,user_rating);
            print_success("Thank you for your feedback");
        }else{
            print_error("Invalid rating");
        }
    }else
    {
        MessageBox(NULL, "You chose to cancel.", "Cancelled", MB_ICONINFORMATION | MB_OK);
    }
    
    printNearbyPartner(1,chosen_partner,min_dist_part_rest+min_dist_user_rest,sourcename,currentPartnerLoc);
    getchar();
    addDeliveryDetails(chosen_partner.username,&time,partner_path,partner_path_length);
}


int partnerMap(char *sourcename,char restaurant[50] ,float max_dist){
    system("cls");
    int index = 0;
    int Partner;
    partnerFinder(restaurant,sourcename);
    return 0;
}
// void main(){
//     // graph_binary_write();
//     double cost_matrix[MAX_CITIES][MAX_CITIES];
//     // Node *graph = readNodesFromFile();
//     // printf("%s\n",graph[90].name);
//     // cost_binary_write();
//     readcostsFromFile(cost_matrix); 
//     for (int i = 0; i < V; i++)
//     {
//         for (int j = 0; j < V; j++)
//         {
//             printf("%lf ",cost_matrix[i][j]);
//         }
//         printf("\n");
//     }
    
// }

