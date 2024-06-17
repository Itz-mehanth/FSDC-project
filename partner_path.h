#ifndef PARTNER_PATH
#define PARTNER_PATH


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "map.h"
#include <math.h>
#include <stdbool.h>

int minDistance(double dist[], int sptSet[]);
void printPath(int parent[], int j, Node* graph_arr);
// double dijkstra(double graph[V][V], int src, int dest, Node* graph_arr, double dist[V]);
int partnerMap(char *sourcename,char restaurant[50], float max_dist);
int partnerMap(char *sourcename,char restaurant[50] ,float max_dist);

#endif // MAP