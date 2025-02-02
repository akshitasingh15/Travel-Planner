#include <string>
#include <vector>
#include <iostream>
#include <queue>
#include <cstdlib>
#include <stack>
#include <cmath>  

#include "Location.h"
#include "Route.h"
#include "FileOp.h"
#include "Graph.h"

using namespace std;

Graph::Graph(string nodesFile, string edgesFile){
	routes = routeParser(edgesFile);
	cities = locationParser(nodesFile, routes);

	numExists = cities.size();
	
}

int Graph::getCityIndex(string key){
	int output = -1;
	for(int i = 0; i < cities.size(); i++){
		if(cities[i] -> city.compare(key) == 0){
			output = i;
			break;
		}
	}
	return output;
}

Location* Graph::getCity(string key){
	int i = getCityIndex(key);
	if(i != -1){
		return cities.at(i);
	}
	else{
		return NULL;
	}
}


float Graph::getWeight(string startS, string endS, bool costOrTime){
	Location* start = getCity(startS);
	Location* end = getCity(endS);

	for(int i = 0; i < routes.size(); i++){
		if(routes[i] -> doesConnect(start, end)){
			if(costOrTime){
				return routes[i] -> cost;
			}
			else{
				return routes[i] -> time;
			}
		}
	}

	return -1;
}

float Graph::getWeight(Location* start, Location* end, bool costOrTime){

	for(int i = 0; i < routes.size(); i++){
		if(routes[i] -> doesConnect(start, end)){
			if(costOrTime){
				return routes[i] -> cost;
			}
			else{
				return routes[i] -> time;
			}
		}
	}

	return -1;
}


void Graph::Dijkstra(string startCity, bool costOrTime)
{
    Location* start = getCity(startCity);
	float totalDistance = 0;

	start -> lengthFromStart = 0;

	priority_queue<Location*,vector<Location*>,compareLocation> minHeap;

	for(int i = 0; i < cities.size(); i++){
		minHeap.push(cities[i]);
	}

	while(!minHeap.empty()){
		
		while(!minHeap.empty() && minHeap.top() -> exists == false){
			minHeap.pop();
		}

		Location* smallest;

		if(!minHeap.empty()){
			smallest = minHeap.top();
		}
		else{
			return;
		}
		
		
		cout << "Smallest popped: " << smallest -> lengthFromStart << endl;	//debug
		smallest -> exists = false;

		vector<Location*>* adjacentCities = adjacentLocations(smallest);	

		for(int i = 0; i < adjacentCities -> size(); i++){

			Location* adjacent = adjacentCities -> at(i);

			float distance = getWeight(smallest, adjacent, costOrTime) + smallest -> lengthFromStart;

			cout << distance << "	vs	" << adjacent -> lengthFromStart << endl;	//debug


			if(distance < adjacent -> lengthFromStart){

				adjacent -> lengthFromStart = distance;
				adjacent -> previous = smallest;

				totalDistance = distance;

			}

			make_heap(const_cast<Location**>(&minHeap.top()), const_cast<Location**>(&minHeap.top()) + minHeap.size(), compareLocation());

		}

		delete adjacentCities;
		

	}
}

vector<Location *> *Graph::adjacentLocations(Location *city)
{

    vector<Location*>* output = new vector<Location*>();

	for(int i = 0; i < city -> routes.size(); i++){
		if(city -> routes[i] -> destination -> exists == true){
			output -> push_back(city -> routes[i] -> destination);
			//cout << i <<" Adjacent: " << city -> routes[i] -> destination -> exists << endl;	//debug
		}
	}

	return output;
}

vector<Route*>* Graph::adjacentRoutes(Location* city){
	vector<Route*>* output = new vector<Route*>();

	for(int i = 0 ; i < routes.size(); i++){
		if(routes[i]->origin->city.compare(city->city) == 0) {
			output -> push_back(routes[i]);
		}
	}
	return output;
}

Route* Graph::getRoute(Location* start, bool costOrTime, float totalDistance){
	
	vector<Route*>* routes = adjacentRoutes(start);

	float epsilon = 1e-5;

	for(int i = 0; i < routes -> size(); i++){

			if(costOrTime == true){
				if(fabs((totalDistance - routes -> at(i) -> cost) - routes -> at(i) -> origin -> lengthFromStart) > epsilon){
					return routes -> at(i);
				}
			}

			else if(costOrTime == false){
				if(fabs((totalDistance - routes -> at(i) -> time) - routes -> at(i) -> origin -> lengthFromStart) > epsilon){
					return routes -> at(i);
				}
			}
		
	}
	return NULL;
}

stack<Location*> Graph::cityStacker(string destinationS){
	
	Location* destination = getCity(destinationS);
	stack<Location*> output;

	while(destination != NULL){
		output.push(destination);
		destination = destination -> previous;
	}

	return output;

}

stack<Route*> Graph::routeStacker(string destinationS, bool costOrTime){

	stack<Route*> output;
	Location* destination = getCity(destinationS);
	float totalDistance = destination -> lengthFromStart;

	while(destination -> previous != NULL){
		output.push(getRoute(destination -> previous, costOrTime, totalDistance));
		destination = destination -> previous;

		totalDistance = destination -> lengthFromStart;
	}

	return output;
}
