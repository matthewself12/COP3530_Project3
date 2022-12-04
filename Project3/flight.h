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
    vector<pair<string, double>> shellSortDepartureDelay(unordered_map<string, pair<int,int>> map) {
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
        for(int gap = size / 2; gap >= 1; gap /= 2) { // divide gap by 2 each iteration
            for(int i = 0; (i + gap) < size; i++) {
                // insertion sort part of shell sort
                for(int j = i + gap; j < size; j += gap) {
                    for(int k = j; k > gap - 1; k -= gap) {
                        // check if the elements are in order
                        if(avgDelays[k] < avgDelays[k - gap]) {
                            // swap elements
                            double temp = avgDelays[k - gap];
                            string tempStr = arr[k - gap];
                            avgDelays[k - gap] = avgDelays[k];
                            arr[k - gap] = arr[k];
                            avgDelays[k] = temp;
                            arr[k] = tempStr;
                        } else {
                            break; // since element is inserted in correct spot, break
                        }
                    }
                }
            }
        }

        vector<pair<string,double>> res;
        res.push_back(pair<string,double>(arr[0], avgDelays[0]));
        res.push_back(pair<string,double>(arr[1], avgDelays[1]));
        res.push_back(pair<string,double>(arr[2], avgDelays[2]));
        return res;
    }

    // method to sort a vector list of flights by departure delay time and return the flight object with the least
    vector<pair<string, double>> quickSortDepartureDelay(unordered_map<string, pair<int,int>> map) {
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
        quickSort(avgDelays, 0, map.size() -1);

        vector<pair<string,double>> res;
        res.push_back(pair<string,double>(arr[0], avgDelays[0]));
        res.push_back(pair<string,double>(arr[1], avgDelays[1]));
        res.push_back(pair<string,double>(arr[2], avgDelays[2]));
        return res;
    }

    void swap(double *first, double *second) {
        double temp = *first;
        *first = *second;
        *second = temp;
    }

    int partition(double array[], int front, int back) {
        int pivot = array[back];
        int i = (front - 1);
        for (int j = front; j < back; j++) {
            if (array[j] <= pivot) {
                i++;
                swap(&array[i], &array[j]);
            }
        }
        swap(&array[i + 1], &array[back]);
        return (i + 1);
    }

    void quickSort(double array[], int front, int back) {
        if (front < back) {
            int k = partition(array, front, back);
            quickSort(array, front, k - 1);
            quickSort(array, k + 1, back);
        }
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

    // method to get the avg delay time at a certain airport for each airline
    unordered_map<string, pair<int,int>> getAvgDelayAirport(string airport) {
        unordered_map<string, pair<int,int>> map;
        for(Flight f : flightList) {
            if(f.origin == airport) { // if the flight was the desired airline
                // get the airline
                string airline = f.carrier;
                // check if the airline has already been added to the map
                if(map.find(airline) != map.end()) {
                    // since airline already added, add the delay time and increment numFlights
                    map[airline].first = map[airline].first + f.departureDelay;
                    map[airline].second = map[airline].second + 1;
                } else {
                    // add the airline to the map
                    map[airline] = pair<int,int>(0,0);
                    // add the delay time and increment numFlights
                    map[airline].first = map[airline].first + f.departureDelay;
                    map[airline].second = map[airline].second + 1;
                }
            }
        }
        return map;
    }

};
