#ifndef LOCATION_H
#define LOCATION_H

#include <vector>
#include <string>
#include <iostream>
#include <limits.h>

#include "Route.h"
class Route;

using namespace std;

class Location {
public:
    string country;
    string city;
    float lat;
    float lon;

    vector<Route*> routes;  // Routes originating from this location
    bool exists;            // Whether this location exists
    Location* previous;     // For pathfinding (e.g., Dijkstra's algorithm)
    float lengthFromStart;  // Distance from the start location

    Location();
    Location(string count, string cap, float lt, float lg);

    // Method to calculate weight for pathfinding algorithms
    float getWeight(Location* start, Location* end);
    
    // Overloaded comparison operators for pathfinding algorithms
    int operator==(const Location& rhs) const;
    int operator<(const Location& rhs) const;
    int operator>(const Location& rhs) const;
};

class compareLocation{
public:
	bool operator()(const Location* l1, const Location* l2) const{
		bool output = false;
		if(l1->lengthFromStart > l2->lengthFromStart){
			output = true;
		}
		return output;
	}
};

#endif