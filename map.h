#ifndef MAP
#define MAP


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>


#define MAX_CITIES 119
#define INF 100000
#define MAX_CITY_NAME_LENGTH 100
#define MAX_NEIGHBORS 10  // Adjust as needed for the maximum number of neighbors
#define V 119

typedef struct Node {
    char name[MAX_CITY_NAME_LENGTH];
    double latitude;
    double longitude;
    struct Node* neighbors[MAX_NEIGHBORS]; // Array of pointers to Node
    double distances[MAX_NEIGHBORS];
    double cost;
    struct Node* pred[MAX_CITIES]; // Single pred for simplicity, multiple parents are rare in Dijkstra
    bool visited;
    double shortedDistance;
    int num_neighbors;
} Node;

extern int num_cities;
Node* find_node_by_name(Node* graph, const char* name);
double calculate_Euclidean_distance(double lat1, double lon1, double lat2, double lon2);
void calculate_distances(Node *node);
Node* create_graph_from_file(const char* filename);
void write_graph_to_file(const char* filename, Node* graph);
void readcostsFromFile(double cost_matrix[MAX_CITIES][MAX_CITIES]);
int find_source_node_index(Node* graph,const char *source_name);
void create_cost_matrix(double cost_matrix[MAX_CITIES][MAX_CITIES], Node *graph, Node *source);
void print_cost_matrix(double cost_matrix[MAX_CITIES][MAX_CITIES]);
int minDistance(double dist[], int sptSet[]);
void printSolution(double dist[], int n);
void printPath(int parent[], int j, Node* graph_arr);
void dijkstra(double graph[V][V], int src, int dest, Node* graph_arr, double dist[V]);
int map(char *sourcename, float max_dist);

#endif // MAP