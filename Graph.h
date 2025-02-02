#include <iostream>
#include <vector>
#include <climits>
#include <cstring>
#include <fstream>
#include <stack>
#include "Location.h"
#include "Route.h"

using namespace std;

class Graph {
public:
    vector<Location*> cities;
    vector<Route*> routes;

    int numExists;

    Graph(string citiesFile, string routesFile);

    int getCityIndex(string key);
    Location* getCity(string key);

    float getWeight(string startS, string endS, bool costOrTime);
    float getWeight(Location* start, Location* end, bool costOrTime);

    void Dijkstra(string startCity, bool costOrTime);

    vector<Location*>* adjacentLocations(Location* city);
    Route* getRoute(Location* start, bool costOrTime, float totalDistance);

    vector<Route*>* adjacentRoutes(Location* city);
	
	stack<Location*>cityStacker(string destinationS);
	stack<Route*> routeStacker(string destinationS, bool costOrTime); 
};

