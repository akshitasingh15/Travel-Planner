#include <iostream>
#include <string>
#include<vector>
#include <limits.h>

#include "Location.h"
#include "Route.h"
class Route;

using namespace std;

Location::Location(){
    country = "";
    city = "";
    lat = 0;
    lon = 0;

    lengthFromStart = INT_MAX;

    exists = true;

    previous = NULL;
}


Location::Location(string count, string cy, float lt, float lg){
    country = count;
    city = cy;
    lat = lt;
    lon = lg;

    lengthFromStart = INT_MAX;

    exists = true;

    previous = NULL;
}

int Location::operator==(const Location& rhs) const{
    if(this->city.compare(rhs.city) == 0){
        return 0;
    }
    else{
        return 1;
    }
}

int Location::operator<(const Location& rhs) const{
    if(this -> lengthFromStart < rhs.lengthFromStart){
        return 1;
    }
    else return 0;
}

int Location::operator> (const Location &rhs) const{
    if(this -> lengthFromStart > rhs.lengthFromStart){
        return 1;
    }
    else return 0;
}