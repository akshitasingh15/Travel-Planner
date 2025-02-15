#include <cstdlib>
#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <stack>

#include "FileOp.h"

using namespace std;

#define MULTI 3

vector<Location*> locationParser(string filename, vector<Route*> routes){
    fstream location(filename);

    string country;
    string city;
    string latitude;
    string longitude;

    vector<Location*> cities;
    Location* node;

    while(location.good()){
        getline(location, country, ',');
		getline(location, city, ',');
		getline(location, latitude, ',');
		getline(location, longitude);
		//cout << "Country:" << country << " City:" << city << " Lat:" << latitude << " Lon:" << longitude << endl << endl << endl;

		node = new Location(country, city, atof(latitude.c_str()), atof(longitude.c_str()));

        
        vector<Route*>::iterator it = routes.begin();

        while(it!=routes.end()){
            if((*it) -> originS.compare(node->city)==0){
                (*it) -> origin = node;
                node -> routes.push_back((*it));
            }
            else if((*it) -> destinationS.compare(node->city)==0){
                (*it) -> destination = node;
            }
            ++it;
        }

        cities.push_back(node);
    }

    cout << "Cities Parsed from: " << filename << endl;
	return cities;
}

vector<Route*> routeParser(string filename){

    fstream routes(filename);

    string originS;
    string destinationS;

    Location origin;
    Location destination;

    string type;
    string time;
    string cost;

    vector<Route*> allRoutes;
    Route* edge;

    while(routes.good()){
        getline(routes, originS, ',');
		getline(routes, destinationS, ',');
		getline(routes, type, ',');
		getline(routes, time, ',');
		getline(routes, cost, ',');

		cout << "Origin: " << originS << " Destination: " << destinationS << "---" << type << " " << time << " " << cost << " " << endl;

        edge = new Route(&origin, &destination, type, atof(time.c_str()), atof(cost.c_str()));

        edge -> destinationS = destinationS;
		edge -> originS = originS;

		allRoutes.push_back(edge);
    }

    cout << "Routes Parsed from: " << filename << endl;
    return allRoutes;
}

void outputGenerator(string filename, stack<Location*> cities, stack<Route*> routes, bool costOrTime) {
    ofstream output(filename.c_str());

    output << "<!DOCTYPE html>\n";
    output << "<html>\n<head>\n";
    output << "<title>Shortest path from Hyderabad to Mumbai</title>\n";
    output << "<script type='text/javascript' src='https://maps.googleapis.com/maps/api/js?key=YOUR_API_KEY&callback=initMap' async defer></script>\n";

    output << "<script>\n";
    output << "var map;\n";
    output << "var markers = [];\n";
    output << "var paths = [];\n";

    output << "function initMap() {\n";
    output << "    console.log('Initializing map...');\n"; 
    output << "    map = new google.maps.Map(document.getElementById('map'), {\n";
    output << "        zoom: 3,\n";
    output << "        center: { lat: 20.0, lng: 50.0 },\n"; 
    output << "        mapTypeId: google.maps.MapTypeId.ROADMAP\n";
    output << "    });\n";

    int markerCount = 0;
    int contentStringCount = 0;
    Location* origin;
    Location* destination;
    Route* route;
    float cost;

    while (!cities.empty() && !routes.empty()) {
        origin = cities.top();
        cities.pop();

        if (cities.empty()) {
            cout << "No more cities left, stopping." << endl;
            break;  
        }

        destination = cities.top();

        // ✅ Debugging Latitude & Longitude
        cout << "Origin: " << origin->city << " (" << origin->lat << ", " << origin->lon << ")" << endl;
        cout << "Destination: " << destination->city << " (" << destination->lat << ", " << destination->lon << ")" << endl;

        // ✅ Adding Markers
        output << "    var marker" << markerCount << " = new google.maps.Marker({\n";
        output << "        position: { lat: " << origin->lat << ", lng: " << origin->lon << " },\n";
        output << "        map: map,\n";
        output << "        title: '" << origin->city << ", " << origin->country << "'\n";
        output << "    });\n";
        output << "    markers.push(marker" << markerCount << ");\n";
        markerCount++;

        output << "    var marker" << markerCount << " = new google.maps.Marker({\n";
        output << "        position: { lat: " << destination->lat << ", lng: " << destination->lon << " },\n";
        output << "        map: map,\n";
        output << "        title: '" << destination->city << ", " << destination->country << "'\n";
        output << "    });\n";
        output << "    markers.push(marker" << markerCount << ");\n";
        markerCount++;

        // ✅ Routes Handling
        route = routes.top();
        routes.pop();

        cost = route->cost;
        if (route->transport.compare("plane") == 0) {
            cost = cost / MULTI;
        }

        // ✅ Debugging for Route
        output << "    console.log('Drawing route from " << origin->city << " to " << destination->city << "');\n";
        output << "    var path" << contentStringCount << " = new google.maps.Polyline({\n";
        output << "        path: [\n";
        output << "            { lat: " << origin->lat << ", lng: " << origin->lon << " },\n";
        output << "            { lat: " << destination->lat << ", lng: " << destination->lon << " }\n";
        output << "        ],\n";
        output << "        strokeColor: '#0000FF',\n";
        output << "        strokeOpacity: 1.0,\n";
        output << "        strokeWeight: 2\n";
        output << "    });\n";
        output << "    path" << contentStringCount << ".setMap(map);\n";
        output << "    paths.push(path" << contentStringCount << ");\n";

        output << "    var contentString" << contentStringCount << " = \"" << origin->city << ", " << origin->country << " --> " << destination->city << ", " << destination->country << " (" << route->transport << " - " << route->time << " hours - $" << cost << ")\";\n";
        output << "    google.maps.event.addListener(path" << contentStringCount << ", 'click', function(event) { alert(contentString" << contentStringCount << "); });\n";
        contentStringCount++;
    }

    output << "} // End of initMap()\n";
    output << "</script>\n";

    // ✅ Ensure map div is present
    output << "</head>\n<body>\n";
    output << "<div id='map' style='width:100%; height:500px;'></div>\n";
    output << "</body>\n</html>";

    output.close();

    cout << "Output File Generated: " << filename << endl;
}
