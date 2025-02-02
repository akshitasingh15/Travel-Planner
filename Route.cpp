#include <iostream>
#include <vector>
#include <string>

#include "Route.h"

using namespace std;
const float MULTI = 3;

Route::Route(){
    origin = NULL;
    destination = NULL;
    transport = "";
    time = 0;
    cost = 0;
};

Route::~Route() {}

Route::Route(Location *org, Location *dest, string trans, float tim, float cst) {
    origin = org;
    destination = dest;
    transport = trans;
    time = tim;
    cost = cst;

    if(trans.compare("plane")==0){
        cost = cst*MULTI;
    }
};

bool Route::doesConnect(Location* start, Location* end){
    if(start == origin && end == destination){
        return true;
    }
    else{
        return false;
    }
}

