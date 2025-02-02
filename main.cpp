#include <iostream>
#include <string>
#include <fstream>
#include <iterator>
#include <vector>
#include <stack>

#include "FileOp.h"
#include "Route.h"
#include "Graph.h"
#include "Location.h"

using namespace std;

int main(){
    string citiesFile;
    string routesFile;
    string outputFile;
    string origin;
    string destination;
    string preference;
    bool biPreference;

    cout << "Enter filename containing cities: ";
    cin >> citiesFile;

    cout << "Enter filename contatinig routes: ";
    cin >> routesFile;

    cout << "Enter filename for output(.html): ";
    cin >> outputFile;

    cout << "Origin: ";
    cin >> origin;

    cout << "Destination:  ";
    cin >> destination;

    cout << "Enter a preference (fastest/cheapest): ";
	cin >> preference;

    if(preference.compare("cheapest") == 0){
		biPreference = true;
	}
	else if(preference.compare("fastest") == 0){
		biPreference = false;
	}

	else{
		cout << "Invalid entry";
		return 0;
	}

    Graph graph(citiesFile, routesFile);

    graph.Dijkstra(origin, biPreference);

    stack<Location*> cityStack = graph.cityStacker(destination);
	stack<Route*> routeStack = graph.routeStacker(destination, biPreference);

	outputGenerator(outputFile, cityStack, routeStack, biPreference);

	return 0;

}