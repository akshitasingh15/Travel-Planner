#ifndef FILEOP_H
#define FILEOP_H

#include <vector>
#include <string>
#include <stack>
#include "Route.h"
#include "Location.h"

using namespace std;

vector<Location*> locationParser(string filename, vector<Route*> routes);
vector<Route*> routeParser(string filename);
void outputGenerator(string filename, stack<Location*> cities, stack<Route*> routes, bool costOrTime);

#endif  
