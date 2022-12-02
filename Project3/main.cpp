#include <iostream>
#include "flight.h"
using namespace std;

int main() {
    string sortBy;
    string airlineSortBy;
    string airportSortBy;


    cout << "Welcome to Airport Ally" << endl;
    cout << "What would you like to sort by?: Airline or Airport" << endl;
    cin >>  sortBy; 
    if(sortBy == "Airline"){
        cout << "Enter the IATA of the Airline you are flying (e.g. Southwest is NW):" << endl;
        cin >> airlineSortBy;
    }
    if(sortBy == "Airport"){
        cout << "Enter the IATA of the Airport you are flying out of (e.g. Orlando is MCO):" << endl;
        cin >> airportSortBy;
    }


    return 0;
}
