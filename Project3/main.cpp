#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <chrono>
using namespace std::chrono;
using namespace std;
#include "flight.h"

vector<FlightList::Flight> getDataFromCSVFile(string filePath){
    vector<FlightList::Flight> temp;
    fstream inFile(filePath);

    if (inFile.is_open()){
        string head;
        getline(inFile, head);

        while (getline(inFile, head)){
            istringstream stream(head);
            int year, month, arrivalDelay, departureDelay, carrierDelay, weatherDelay, nasDelay, securityDelay, lateAircraftDelay;
            string carrier, origin, destination;
            bool cancelled;

            //temps
            string unused;
            string tempCancelled;
            string tempYear, tempMonth, tempArrivalDelay, tempDepartureDelay, tempCarrierDelay, tempWeatherDelay, tempNasDelay, tempSecurityDelay, tempLateAircraftDelay;

            getline(stream, unused, ',');
            getline(stream, tempYear, ',');
            if (tempYear != ""){
                year = stoi(tempYear);
            } else {
                year = 0;
            }

            getline(stream, tempMonth, ',');
            if (tempMonth != ""){
                month = stoi(tempMonth);
            } else {
                month = 0;
            }
            getline(stream, unused, ',');
            getline(stream, unused, ',');
            getline(stream, unused, ',');
            getline(stream, unused, ',');
            getline(stream, unused, ',');
            getline(stream, unused, ',');
            getline(stream, carrier, ',');
            getline(stream, unused, ',');
            getline(stream, unused, ',');
            getline(stream, unused, ',');
            getline(stream, unused, ',');
            getline(stream, unused, ',');
            getline(stream, tempArrivalDelay, ',');
            if (tempArrivalDelay != ""){
                arrivalDelay = stoi(tempArrivalDelay);
            } else {
                arrivalDelay = 0;
            }
            getline(stream, tempDepartureDelay, ',');
            if (tempDepartureDelay != ""){
                departureDelay = stoi(tempMonth);
            } else {
                departureDelay = 0;
            }
            getline(stream, origin, ',');
            getline(stream, destination, ',');
            getline(stream, unused, ',');
            getline(stream, unused, ',');
            getline(stream, unused, ',');
            getline(stream, tempCancelled, ',');
            if (tempCancelled == "0"){
                cancelled = false;
            } else {
                cancelled = true;
            }
            getline(stream, unused, ',');
            getline(stream, unused, ',');

            getline(stream, tempCarrierDelay, ',');
            if (tempCarrierDelay != ""){
                carrierDelay = stoi(tempCarrierDelay);
            } else {
                carrierDelay = 0;
            }

            getline(stream, tempWeatherDelay, ',');
            if (tempWeatherDelay != ""){
                weatherDelay = stoi(tempWeatherDelay);
            } else {
                weatherDelay = 0;
            }

            getline(stream, tempNasDelay, ',');
            if (tempNasDelay != ""){
                nasDelay = stoi(tempNasDelay);
            } else {
                nasDelay = 0;
            }

            getline(stream, tempSecurityDelay, ',');
            if (tempSecurityDelay != ""){
                securityDelay = stoi(tempSecurityDelay);
            } else {
                securityDelay = 0;
            }

            getline(stream, tempLateAircraftDelay, ',');
            if (tempLateAircraftDelay != ""){
                lateAircraftDelay = stoi(tempLateAircraftDelay);
            } else {
                lateAircraftDelay = 0;
            }

            FlightList::Flight p(year, month, carrier, arrivalDelay, departureDelay, origin, destination, cancelled, carrierDelay, weatherDelay, nasDelay, securityDelay, lateAircraftDelay);
            temp.push_back(p);
        }
    }

    return temp;

}


int main() {
    cout << "Initializing..." << endl;

    FlightList flightData;

    flightData.flightList = getDataFromCSVFile("DelayedFlights.csv");

    string sortBy;
    string airlineSortBy;
    string airportSortBy;



    cout << "Welcome to Airport Ally" << endl;
    cout << "What would you like to sort by?: Airline or Airport" << endl;
    cin >>  sortBy;

    if(sortBy == "Airline"){
        cout << "Enter the IATA of the Airline you are flying (e.g. Southwest is WN):" << endl;
        cin >> airlineSortBy;

        auto startShell = high_resolution_clock::now();
        vector<pair<string,double>> v1 = flightData.shellSortDepartureDelay(flightData.getAvgDelayAirline(airlineSortBy));
        auto stopShell = high_resolution_clock::now();
        auto durationShell = duration_cast<microseconds>(stopShell - startShell);

        auto startQuick = high_resolution_clock::now();
        vector<pair<string,double>> v2 = flightData.quickSortDepartureDelay(flightData.getAvgDelayAirline(airlineSortBy));
        auto stopQuick = high_resolution_clock::now();
        auto durationQuick = duration_cast<microseconds>(stopQuick - startQuick);


        cout << "Here are the top three airports with their corresponding average departure delay times: " << endl;
        for(int i = 0; i < v1.size(); i++) {
            cout << "Airport: " << v1.at(i).first << " Avg Delay: " << v1.at(i).second << " minutes" << endl;
        }
        cout << "Shell Sort took " << durationShell.count() << " microseconds"<< endl;
        cout << "Quick Sort took " << durationQuick.count() << " microseconds"<< endl;


    }
    if(sortBy == "Airport"){
        cout << "Enter the IATA of the Airport you are flying out of (e.g. Orlando is MCO):" << endl;
        cin >> airportSortBy;

        auto startShell = high_resolution_clock::now();
        vector<pair<string,double>> v1 = flightData.shellSortDepartureDelay(flightData.getAvgDelayAirport(airportSortBy));
        auto stopShell = high_resolution_clock::now();
        auto durationShell = duration_cast<microseconds>(stopShell - startShell);

        auto startQuick = high_resolution_clock::now();
        vector<pair<string,double>> v2 = flightData.quickSortDepartureDelay(flightData.getAvgDelayAirport(airportSortBy));
        auto stopQuick = high_resolution_clock::now();
        auto durationQuick = duration_cast<microseconds>(stopQuick - startQuick);

        cout << "Here are the top three airlines at " << airportSortBy << " with their corresponding average departure delay times: " << endl;
        for(int i = 0; i < v1.size(); i++) {
            cout << "Airline: " << v1.at(i).first << " Avg Delay: " << v1.at(i).second << " minutes" << endl;
        }
        cout << "Shell Sort took " << durationShell.count() << " microseconds"<< endl;
        cout << "Quick Sort took " << durationQuick.count() << " microseconds"<< endl;
    }


    return 0;
}

