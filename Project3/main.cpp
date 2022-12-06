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
    cout << "Initializing..." << endl << endl;

    FlightList flightData;

    flightData.flightList = getDataFromCSVFile("DelayedFlights.csv");

    // create a map that holds the IATA abbreviations and full names of the carriers
    unordered_map<string, string> airlines;
    airlines.insert(pair<string, string>("WN", "Southwest"));
    airlines.insert(pair<string, string>("AA", "American Airlines"));
    airlines.insert(pair<string, string>("CO", "Continental Airlines"));
    airlines.insert(pair<string, string>("B6", "JetBlue"));
    airlines.insert(pair<string, string>("DL", "Delta"));
    airlines.insert(pair<string, string>("MQ", "Envoy Air"));
    airlines.insert(pair<string, string>("XE", "JSX Air"));
    airlines.insert(pair<string, string>("YV", "Mesa Airlines"));
    airlines.insert(pair<string, string>("OH", "PSA Airlines"));
    airlines.insert(pair<string, string>("OO", "SkyWest Airlines"));
    airlines.insert(pair<string, string>("UA", "United Airlines"));
    airlines.insert(pair<string, string>("EV", "ExpressJet Airlines"));
    airlines.insert(pair<string, string>("FL", "AirTran Airways"));
    airlines.insert(pair<string, string>("US", "US Airways"));
    airlines.insert(pair<string, string>("9E", "Endeavor Air"));
    airlines.insert(pair<string, string>("NW", "Northwest Airlines"));
    airlines.insert(pair<string, string>("AS", "Alaska Airlines"));
    airlines.insert(pair<string, string>("F9", "Frontier Airlines"));
    airlines.insert(pair<string, string>("HA", "Hawaiian Airlines"));
    airlines.insert(pair<string, string>("AQ", "Aloha Airlines"));


    string filterBy;
    string airlineSortBy;
    string airportSortBy;

    while(filterBy != "Quit" && filterBy != "quit") {

        cout << "___________________________________________________________________________" << endl;

        cout << "\nWelcome to Airport Ally" << endl;
        cout << "What would you like to filter by?: Airline or Airport (Or type \"Quit\" to exit)" << endl;
        cin >> filterBy;

        if (filterBy == "Airline") {
            cout << "\nEnter the IATA of the Airline you are flying (e.g. Southwest is WN):" << endl;
            cin >> airlineSortBy;

            auto startShell = high_resolution_clock::now();
            vector<pair<string, double>> v1 = flightData.shellSortDepartureDelay(
                    flightData.getAvgDelayAirline(airlineSortBy));
            auto stopShell = high_resolution_clock::now();
            auto durationShell = duration_cast<microseconds>(stopShell - startShell);

            auto startQuick = high_resolution_clock::now();
            vector<pair<string, double>> v2 = flightData.quickSortDepartureDelay(
                    flightData.getAvgDelayAirline(airlineSortBy));
            auto stopQuick = high_resolution_clock::now();
            auto durationQuick = duration_cast<microseconds>(stopQuick - startQuick);


            cout << "\nHere are the top three airports with their corresponding average departure delay times: "
                 << endl;
            cout << endl;
            for (int i = 0; i < v2.size(); i++) {
                cout << "Airport: " << v2.at(i).first << " Avg Delay: " << v2.at(i).second << " minutes" << endl;
            }
            cout << endl;
            cout << "Shell Sort took " << (durationShell.count() / 1000000.0) << " seconds" << endl;
            cout << "Quick Sort took " << (durationQuick.count() / 1000000.0) << " seconds" << endl;


        }
        if (filterBy == "Airport") {
            cout << "\nEnter the IATA of the Airport you are flying out of (e.g. Orlando is MCO):" << endl;
            cin >> airportSortBy;

            auto startShell = high_resolution_clock::now();
            vector<pair<string, double>> v1 = flightData.shellSortDepartureDelay(
                    flightData.getAvgDelayAirport(airportSortBy));
            auto stopShell = high_resolution_clock::now();
            auto durationShell = duration_cast<microseconds>(stopShell - startShell);

            auto startQuick = high_resolution_clock::now();
            vector<pair<string, double>> v2 = flightData.quickSortDepartureDelay(
                    flightData.getAvgDelayAirport(airportSortBy));
            auto stopQuick = high_resolution_clock::now();
            auto durationQuick = duration_cast<microseconds>(stopQuick - startQuick);

            cout << "\nHere are the top three airlines at " << airportSortBy
                 << " with their corresponding average departure delay times at " << airportSortBy << ": " << endl;
            cout << endl;
            for (int i = 0; i < v1.size(); i++) {
                cout << "Airline: " << v1.at(i).first << " (" << airlines[v1.at(i).first] << ")";
                cout << "\tAvg Delay: " << v1.at(i).second << " minutes" << endl;
            }
            cout << endl;
            cout << "Shell Sort took " << (durationShell.count() / 1000000.0) << " seconds" << endl;
            cout << "Quick Sort took " << (durationQuick.count() / 1000000.0) << " seconds" << endl << endl;
        }
    }

    cout << "\nThanks for using Aiport Ally! Have a good trip!" << endl;

    system("pause");
    return 0;
}

