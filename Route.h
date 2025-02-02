#ifndef ROUTE_H
#define ROUTE_H

#include <iostream>
#include <vector>
#include <string>

#include "Location.h"
class Location;

using namespace std;

class Route {
public:
    Location* origin;
    Location* destination;
    string originS;
    string destinationS;
    string transport;
    float time;
    float cost;

    Route();
    ~Route();
    Route(Location *org, Location *dest, string trans, float tim, float cst);

    bool doesConnect(Location* start, Location* end);
};

#endif