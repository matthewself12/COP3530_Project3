#include <string>
#include <vector>
#include <unordered_map>
using namespace std;

class FlightList {
public:
    struct Flight {
    public:
        int year, month, arrivalDelay, departureDelay, carrierDelay, weatherDelay, nasDelay, securityDelay, lateAircraftDelay;
        string carrier, origin, destination;
        bool cancelled;

        // constructor
        Flight(int y, int m, string carr, int arrDel, int depDel, string orig, string dest, bool cancel, int carDel,
               int weDel, int nasDel, int secDel, int lateDel) {
            year = y;
            month = m;
            carrier = carr;
            arrivalDelay = arrDel;
            departureDelay = depDel;
            origin = orig;
            destination = dest;
            cancelled = cancel;
            carrierDelay = carDel;
            weatherDelay = weDel;
            nasDelay = nasDel;
            securityDelay = secDel;
            lateAircraftDelay = lateDel;
        }
    };

    // list of flights (uses a vector)
    vector<Flight> flightList;
    unordered_map<string, int> carrierMap;
    unordered_map<string, vector<Flight>> airportMap;

    // method to sort a vector list of flights by departure delay time and return the flight object with the least
    pair<string, double> shellSortDepartureDelay(unordered_map<string, pair<int,int>> map) {
        // make an array of the airports/airlines
        string arr[map.size()];
        // make an array of the avg delay time at each airport/airline
        double avgDelays[map.size()];

        // fill the two arrays
        int i = 0;
        for(auto it = map.begin(); it != map.end(); it++) {
            arr[i] = it->first;
            avgDelays[i] = it->second.first / (double)it->second.second;
            i++;
        }

        // sort the arrays (by sorting the avgDelays array) using SHELL SORT

        int size = map.size();
        int gap;
        for(gap = size / 2; gap >= 1; gap /= 2) {
            for(int i = 0; (i + gap) < size; i++) {
                // compare the elements at i and (i + gap)
                if(avgDelays[i] > avgDelays[i + gap]) {

                }
            }
        }

        return pair<string,double>(arr[0], avgDelays[0]);
    }

    // method to sort a vector list of flights by departure delay time and return the flight object with the least
    pair<string, double> quickSortDepartureDelay(unordered_map<string, pair<int,int>> map) {
        // make an array of the airports/airlines
        string arr[map.size()];
        // make an array of the avg delay time at each airport/airline
        double avgDelays[map.size()];

        // fill the two arrays
        int i = 0;
        for(auto it = map.begin(); it != map.end(); it++) {
            arr[i] = it->first;
            avgDelays[i] = it->second.first / (double)it->second.second;
            i++;
        }

        // sort the arrays (by sorting the avgDelays array) using QUICK SORT
        

        return pair<string,double>(arr[0], avgDelays[0]);
    }

    // method to get the avg delay time of a certain airline at each airport
    unordered_map<string, pair<int,int>> getAvgDelayAirline(string airline) {
        unordered_map<string, pair<int,int>> map;
        for(Flight f : flightList) {
            if(f.carrier == airline) { // if the flight was the desired airline
                // get the airport
                string airport = f.origin;
                // check if the airport has already been added to the map
                if(map.find(airport) != map.end()) {
                    // since airport already added, add the delay time and increment numFlights
                    map[airport].first = map[airport].first + f.departureDelay;
                    map[airport].second = map[airport].second + 1;
                } else {
                    // add the airport to the map
                    map[airport] = pair<int,int>(0,0);
                    // add the delay time and increment numFlights
                    map[airport].first = map[airport].first + f.departureDelay;
                    map[airport].second = map[airport].second + 1;
                }
            }
        }
        return map;
    }

};
