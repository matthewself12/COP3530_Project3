#include <string>
#include <vector>
#include <unordered_map>
using namespace std;

class FlightList {
public:
    struct Flight {
    public:
        // flight attributes
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
    unordered_map<string, vector<Flight>> carrierMap;
    unordered_map<string, vector<Flight>> airportMap;
};
