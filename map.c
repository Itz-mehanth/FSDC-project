#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>
#include <limits.h>
#include <float.h>
#include "buttonCreator.h"
#include "textField.h"
#include "map.h"
#include <stdio.h>
#include "sounds.h"
#include "illustrations.h"
#include "settings.h"
#include "login.h"
#include "restaurants_home.h"



int num_cities=0;
Node* find_node_by_name(Node* graph, const char* name) {
    for (int i = 0; i < num_cities; i++) {
        if (strcmp(graph[i].name, name) == 0) {
            return &graph[i];  // Return pointer to the matching node
        }
    }
    // printf("%s not found\n", name);
    return NULL;  // Return NULL if no matching node is found
}

double calculate_Euclidean_distance(double lat1, double lon1, double lat2, double lon2) {
    // Convert latitude and longitude from degrees to radians
    double lat1_rad = lat1 * M_PI / 180;
    double lon1_rad = lon1 * M_PI / 180;
    double lat2_rad = lat2 * M_PI / 180;
    double lon2_rad = lon2 * M_PI / 180;

    // Earth radius in kilometers
    double R = 6371;

    // Haversine formula for distance calculation
    double dlon = lon2_rad - lon1_rad;
    double dlat = lat2_rad - lat1_rad;
    double a = pow(sin(dlat / 2), 2) + cos(lat1_rad) * cos(lat2_rad) * pow(sin(dlon / 2), 2);
    double c = 2 * atan2(sqrt(a), sqrt(1 - a));
    double distance = R * c;

    return distance;
}

void calculate_distances(Node *node) {
    // printf("%s\n", node->name);
    for (int i = 0; i < node->num_neighbors; i++) {
        // Assuming latitude and longitude are stored in node->latitude and node->longitude respectively
        // Assuming neighbor nodes' latitude and longitude are stored in their respective structs
        double distance = calculate_Euclidean_distance(node->latitude, node->longitude,
                                              node->neighbors[i]->latitude, node->neighbors[i]->longitude);
        node->distances[i] = distance;
    }
}

Node* create_graph_from_file(const char* filename) {
    FILE* fp = fopen(filename, "r");
    if (fp == NULL) {
        print_error("Error opening file");
        return NULL;
    }

    char line[256];

    // Count the number of cities in the file
    while (fgets(line, sizeof(line), fp) != NULL) {
        if (strlen(line) > 0 && line[0] != '\n') {
            num_cities++;
        }
    }
    rewind(fp);  // Reset file pointer to the beginning

    // Allocate memory for the graph
    Node* graph = (Node*)malloc(num_cities * sizeof(Node));
    if (graph == NULL) {
        print_error("Error allocating memory for graph.\n");
        fclose(fp);
        return NULL;
    }
    char neighbours_3d[num_cities+1][5][100];
    char neighbours[100];
    int neighbour_index = 0;
    int city_index = 0;
    char *token;

    /* Get the first token */

    while (fgets(line, sizeof(line), fp) != NULL) {
        if (strlen(line) > 0 && line[0] != '\n') {
            sscanf(line, "%[^,],%lf,%lf,%[^\n]", graph[city_index].name,&graph[city_index].latitude,&graph[city_index].longitude,neighbours);
            // printf("%d.%s\n%lf\n%lf\n%s\n",city_index,graph[city_index].name,graph[city_index].latitude,graph[city_index].longitude,neighbours);
            // break;
            token = strtok(neighbours, " ");
            /* Print the tokens one by one */
            while (token != NULL) {
                strcpy(neighbours_3d[city_index][neighbour_index],token);
                neighbour_index++;
                token = strtok(NULL, " ");  // Subsequent calls use NULL for str
            }
            graph[city_index].num_neighbors = neighbour_index;
            neighbour_index = 0;
            city_index++;
        }

    }

    int n=0;
    for (int i = 0; i < num_cities; i++)
    {
        // printf("%d.%s\n",n++,graph[i].name);
        for (int j = 0; j < sizeof(neighbours_3d[i])/sizeof(neighbours_3d[i][0]); j++)
        {
            graph[i].neighbors[j] = find_node_by_name(graph, neighbours_3d[i][j]);
            // printf("%s\n",graph[i].neighbors[j]->name);
        }
        graph[i].cost = INF;
        
    }
    for (int i = 0; i < num_cities; i++)
    {
        calculate_distances(&graph[i]);
        for (int j = 0; j < MAX_CITIES; j++)
        {
            graph[i].pred[j] = NULL;
        }
        
        // graph[i].pred = NULL;        
    }
    // printf("calculated distances\n");
    fclose(fp);
    return graph;
}

void write_graph_to_file(const char* filename, Node* graph) {
    FILE* fp = fopen(filename, "w");
    if (fp == NULL) {
        print_error("Error opening file");
        return;
    }

    for (int i = 0; i < num_cities; i++) {
        fprintf(fp, "%s %.6lf %.6lf", graph[i].name, graph[i].latitude, graph[i].longitude);

        // Print neighbors (if any)
        if (graph[i].num_neighbors > 0) {
            fprintf(fp, " ");
            for (int j = 0; j < graph[i].num_neighbors; j++) {
                fprintf(fp, "%s ", graph[i].neighbors[j]->name);
            }
        }
        fprintf(fp, "\n");
    }

    fclose(fp);
}

int find_source_node_index(Node* graph,const char *source_name) {

    
  // Search for the source node by name
    // printf("checking :%s \n",source_name);
  for (int i = 0; i < num_cities; i++) {
    // printf("%s == %s \n",graph[i].name, source_name);
    if (strcmp(graph[i].name, source_name) == 0) {
        // printf("found the index: %d \n",i);
      return i; // Return index if found
    }
  }

  // If not found, return -1 to indicate an error
  print_error("Source node not found in the graph");
  return -1;
}
void create_cost_matrix(double cost_matrix[MAX_CITIES][MAX_CITIES], Node *graph, Node *source) {

    // getchar();
    // printf("graph passed to create_cost_matrix - %s\n", graph[0].neighbors[0]->name);
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            cost_matrix[i][j] = INF;
        }
    }
    // Populate the cost matrix based on the distances between neighboring nodes
    for (int i = 0; i < V; i++) {
        // printf("%s\n", graph[i].name);
        for (int j = 0; j < graph[i].num_neighbors; j++) {
            Node *neighbor = graph[i].neighbors[j];
            double distance = graph[i].distances[j];
            // Find the index of the neighbor in the graph
            // printf("printing the neighbor -%s \n", neighbor->name);
            int neighbor_index = find_source_node_index(graph, neighbor->name);
            // printf("found the node index\n");
            if (neighbor_index != -1) {
                cost_matrix[i][neighbor_index] = distance;
                // printf("%lf \n",cost_matrix[i][neighbor_index]);
            }
        }
        // printf("\n");
    }
    // getchar();

    // Set the distance from a node to itself to 0
    for (int i = 0; i < V; i++) {
        cost_matrix[i][i] = 0;
    }
    // printf("cost matrix created successfully\n");
    // getchar();

}


void print_cost_matrix(double cost_matrix[MAX_CITIES][MAX_CITIES]) {
    printf("Cost Matrix:\n");
    for (int i = 0; i < num_cities; i++) {
        for (int j = 0; j < num_cities; j++) {
            if (cost_matrix[i][j] == INF)
                printf("INF ");
            else
                printf("%.2lf ", cost_matrix[i][j]);
        }
        printf("\n");
    }
}

int minDistance(double dist[], int sptSet[]) {
    double min = DBL_MAX;
    int min_index = -1;
    for (int v = 0; v < V; v++) {
        if (sptSet[v] == 0 && dist[v] <= min) {
            min = dist[v];
            min_index = v;
        }
    }
    return min_index;
}

// Function to print the constructed distance array
void printSolution(double dist[], int n) {
    printf("Vertex\t Distance from Source\n");
    for (int i = 0; i < V; i++) {
        printf("%d \t\t %.2lf\n", i, dist[i]);
    }
}

// Function to reconstruct and print the shortest path from source
void printPath(int parent[], int j, Node* graph_arr) {
    if (parent[j] == -1)
        return;
    printPath(parent, parent[j], graph_arr);
    // printf(" -> %s", graph_arr[j].name);
}
// Function that implements Dijkstra's single source shortest path algorithm
// for a graph represented using adjacency matrix representation
void dijkstra(double graph[V][V], int src, int dest, Node* graph_arr, double dist[V]) {
    // printf("running dijkstra\n");
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
            if (!sptSet[v] && graph[u][v] && dist[u] != DBL_MAX
                && dist[u] + graph[u][v] < dist[v]) {
                parent[v] = u;
                dist[v] = dist[u] + graph[u][v];
                // printf("%lf", dist[v]);
            }
        }
    }

    // print the constructed distance array
    // printSolution(dist, V);
    if(dest != -1){
        // printf("shortest disttance from source %s:\n", graph_arr[src].name);
        // printf("%s --> %s", graph_arr[src].name, graph_arr[dest].name);
        // printf("= %lf\n",dist[dest]);

        // // print the constructed path array
        // printf("Paths from source %s to destination is:\n", graph_arr[src].name, graph_arr[dest].name);
        // printPath(parent, dest, graph_arr);
    }
    return;
}
void graph_binary_write() {
    FILE *file = fopen("graph.bin", "wb");
    if (file == NULL) {
        print_error("Error opening file!\n");
        exit(1);
    }

    Node *graph = create_graph_from_file("new_loc_data.txt");

    for (int i = 0; i < num_cities; i++) {
        if (fwrite(&graph[i], sizeof(Node), 1, file) != 1) {
            print_error("Error writing node to file");
            fclose(file);
            getchar();
            exit(1);
        }
    }

    fclose(file);
}
Node* readNodesFromFile() {
    int count;
    FILE* file = fopen("graph.bin", "rb");
    if (file == NULL) {
        print_error("Error opening file");
        exit(EXIT_FAILURE);
    }

    // Move to the end of the file to determine the file size
    fseek(file, 0, SEEK_END);
    long fileSize = ftell(file);
    fseek(file, 0, SEEK_SET);

    // Calculate how many nodes can fit into this file size
    count = fileSize / sizeof(Node);

    // Allocate memory for nodes
    Node* nodes = malloc(count * sizeof(Node));
    if (nodes == NULL) {
        print_error("Memory allocation failed");
        fclose(file);
        exit(EXIT_FAILURE);
    }
    // printf("the count of nodes is %d\n", count);
    // getchar();
    // Read nodes from the file
    fread(nodes, sizeof(Node), count, file);
    fclose(file);

    return nodes; // Caller must free this memory
}
void cost_binary_write(){
    int count = 119;
    Node *graph = readNodesFromFile();

    // printf("graph read successfully- %s\n",graph[10].neighbors[0]->name);
    double cost_matrix[MAX_CITIES][MAX_CITIES];
    FILE *file = fopen("cost_matrix.bin", "wb");
    if (file == NULL)
    {
         print_error("Error opening file!");
         exit(1);
    }
    // printf("creating cost matrix\n");
    create_cost_matrix(cost_matrix, graph,&graph[0]);
    // printf("%lf\n",cost_matrix[0][20]);
    getchar();
    if (file == NULL)  
    {
         print_error("Error opening file!");
         exit(1);
    }
    fwrite(&count, sizeof(int), 1, file);
    fwrite(&count, sizeof(int), 1, file);
    fwrite(cost_matrix, sizeof(double), count * count, file);
}

void assignSortestDistance(Node *graph, double *dist){
    for (int i = 0; i < MAX_CITIES; i++)
    {
        graph[i].shortedDistance = dist[i];
    }
    
}
void readcostsFromFile(double cost_matrix[MAX_CITIES][MAX_CITIES]) {
    int count= 119;
    FILE* file = fopen("cost_matrix.bin", "rb");
    if (file == NULL) {
        print_error("Error opening file");
        exit(EXIT_FAILURE);
    }

    // Move to the end of the file to determine the file size
    if (cost_matrix == NULL) {
        print_error("Memory allocation failed");         
        fclose(file);
        exit(EXIT_FAILURE);
    }
    int rows, cols;

    // Read the dimensions
    fread(&rows, sizeof(int), 1, file);
    fread(&cols, sizeof(int), 1, file);

    // Ensure the dimensions match
    if (rows != 119 || cols != 119) {
        print_error("Matrix dimensions do not match!\n");
        fclose(file);
        exit(EXIT_FAILURE);
    }

    // Read nodes from the file
    fread(cost_matrix, sizeof(double), count * count, file);
    fclose(file);

}
int compareNodesByDistance(const void* a, const void* b) {
    double distanceA = ((Node*)a)->shortedDistance;
    double distanceB = ((Node*)b)->shortedDistance;
    
    if (distanceA < distanceB) return -1;
    if (distanceA > distanceB) return 1;
    return 0;
}

void sortNodesByShortestDistance(Node nodes[], int size) {
    qsort(nodes, size, sizeof(Node), compareNodesByDistance);
}
int select_nearbyrestaurants(restaurant nearbyRestaurants[10],int count)
{
    readRestaurants();
    int selected_restaurants;
        int valid_restaurant_count = 0;

    // Count the number of non-junk restaurants
    for (int i = 0; i < 10; i++) {
        if (nearbyRestaurants[i].name != NULL && strlen(nearbyRestaurants[i].name) > 0) {
            valid_restaurant_count++;
        }
    }

    // Dynamically allocate memory for the editProfileLabels array based on the count of valid restaurants
    char *editProfileLabels[valid_restaurant_count];
    int j = 0;
    for (int i = 0; i < count; i++) {
            editProfileLabels[j++] = nearbyRestaurants[i].name;
    }

    InputPopup(editProfileLabels, count);
    
    selected_restaurants = current_button;
    select_beep();
    return selected_restaurants;
}

int map(char *sourcename, float max_dist){
    system("cls");
    home();
    printUserDetails();
    home_page_banner();
    side_menu(-1);
    restaurant* restaurants[10];
    char source[1024],destination[1024];
    double dist[V];
    double cost_matrix[MAX_CITIES][MAX_CITIES];
    Node *graph = create_graph_from_file("loc_data.txt");
    if (graph == NULL)
    {
        printf("Error reading file\n");
        return 1;
    }
    int index = 0;
    readcostsFromFile(cost_matrix);
    // create_cost_matrix(cost_matrix,graph,find_node_by_name(graph,name));
    dijkstra(cost_matrix, find_source_node_index(graph,sourcename), -1, graph,dist);
    assignSortestDistance(graph,dist);
    sortNodesByShortestDistance(graph, V);
    int near_rest_count = 0;
    restaurant nearbyrestaurants[10];
    for (int i = 0; i < V; i++)
    {
        if (dist[i] < max_dist)
        {

            if (veg_mode)
            {
                if(isrestaurant(graph[i].name) && strcmp(find_restaurant(graph[i].name)->type,"veg") == 0){
                    restaurants[index]= find_restaurant(graph[i].name);
                    if (strcmp(restaurants[index]->name,"none")==0)
                    {
                        break;
                    }
                    printNearbyRestaurant(index+1, graph[i].name,dist[index]);
                    readRestaurants();
                    restaurant *res = find_restaurant(graph[i].name);
                    nearbyrestaurants[index] = *res;
                    near_rest_count++;
                    index++;
                    // printf("%s distance-%.2fkm\n", graph[i].name, dist[i]);
                }
            }else{
                if(isrestaurant(graph[i].name)){
                    restaurants[index]= find_restaurant(graph[i].name);
                    if (strcmp(restaurants[index]->name,"none")==0)
                    {
                        break;
                    }
                    
                    printNearbyRestaurant(index+1, graph[i].name,dist[index]);
                    near_rest_count++;
                    readRestaurants();
                    restaurant *res = find_restaurant(graph[i].name);
                    nearbyrestaurants[index] = *res;
                    index++;
                    // printf("%s distance-%.2fkm\n", graph[i].name, dist[i]);
                }
            }
        }
        if (index == 10)
        {
            break;
        }
        
    }
    // sortRestaurantsByWeightedRating((restaurant*)restaurants);
    // readRestaurants();
        int response;
        int selection = INT_MAX;
        while (selection > index && printf("invalid selection\n"))
        {
            selection = select_nearbyrestaurants(nearbyrestaurants,near_rest_count);
        }
        
        // printf("your have selected %d",selection);
        system("cls");
        home();
        printUserDetails();
        home_page_banner();

        printf("****-%s:-****",nearbyrestaurants[selection-1].name);
        printRestaurant(selection,nearbyrestaurants[selection-1].name);
        response = review_restaurant(nearbyrestaurants[selection-1].name);
        if (response == 2)
        {
            return 2;
        }else if (response == 0)
        {
           return 0; 
        }
        
    return 0;
}
// void main(){
    
//     graph_binary_write();
//     printf("graph written to binary file\n");
//     double cost_matrix[MAX_CITIES][MAX_CITIES];
//     Node *graph = readNodesFromFile();
//     for (int i = 0; i < num_cities; i++)
//     {
//         printf("%d.%s\n", i+1,graph[i].name);
//     }
//     getchar();
//     printf("read modes from file %s\n",graph[90].name);
//     getchar();
//     cost_binary_write();
//     printf("cost written to binary file\n");

//     readcostsFromFile(cost_matrix); 
//     printf("cost read from binary file\n");
//     // for (int i = 0; i < V; i++)
//     // {
//     //     for (int j = 0; j < V; j++)
//     //     {
//     //         printf("%lf ",cost_matrix[i][j]);
//     //     }
//     //     printf("\n");
//     // }
    
// }

