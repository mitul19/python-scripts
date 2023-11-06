#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <map>
#include <ctime>

using namespace std;
#define RESOURCE_PATH "./resources/"


class WeatherStatistics {
public:
    WeatherStatistics();
    bool isValidDateTime(string date, string time);
    double coeff(string startDate, string startTime, string endDate, string endTime);
private:
    std::map<time_t, double> timeToPressure_;
    void load();
	time_t getFirstDateTime() { return timeToPressure_.begin()->first; };
	time_t getLastDateTime() { return timeToPressure_.rbegin()->first; };
    time_t convertDateTime(string date, string time);
};

bool WeatherStatistics::isValidDateTime(string date, string time) {
    time_t dateTime = convertDateTime(date, time);
    if(dateTime < 0) {return false;}
    if((dateTime < getFirstDateTime()) || (dateTime > getLastDateTime())) {
        cerr << "ERROR: " << date << " " << time << " is outside of available data range" << endl;
        return false;
    }
    return true;
}

WeatherStatistics::WeatherStatistics()
{
   load();
}

double WeatherStatistics::coeff(string startDate, string startTime, string endDate, string endTime) {
    time_t startDateTime = convertDateTime(startDate, startTime);
    time_t endDateTime = convertDateTime(endDate, endTime);
    
    if (endDateTime < startDateTime) {
        cerr << "ERROR: the start Date/Time must be before the end Date/time" << endl;
        exit(1);
    }
    // find iterators based on input range
    map<time_t, double>::iterator startTimePressure;
    map<time_t, double>::iterator endTimePressure;
    startTimePressure = timeToPressure_.lower_bound(startDateTime);
    endTimePressure = timeToPressure_.lower_bound(endDateTime);

    // Extract time and timeToPressure values
    double timeDiff = endTimePressure->first - startTimePressure->first;
    double pressureDiff = endTimePressure->second - startTimePressure->second;

    // calculate and return slope
    return (pressureDiff) / (timeDiff);
}

void WeatherStatistics::load()
{
    for (int year = 2012; year <=2015; year++)
    {
        ostringstream fileNameStream;
        fileNameStream << RESOURCE_PATH << "Environmental_Data_Deep_Moor_" << year << ".txt";
        string fileName = fileNameStream.str();
        cout << "Loading " << fileName << endl;

        fstream dataFilestream;
        dataFilestream.open(fileName);

        //read each line
        string line;
        getline(dataFilestream, line);  //discard top line
        // cout << line << endl;
        while (getline(dataFilestream,line))
        {
            string date, time;
            double Air_Temp, Barometric_Press, Dew_Point, Relative_Humidity, Wind_Dir, Wind_Gust, Wind_Speed;
            istringstream buffer(line);
            buffer >> date >> time >> Air_Temp >> Barometric_Press >> Dew_Point >> Relative_Humidity >> Wind_Dir >> Wind_Gust >> Wind_Speed;
            time_t dateTime = convertDateTime(date, time);
            // cout << dateTime<< endl;
            timeToPressure_[dateTime] = Barometric_Press;
        }
        // cout << timeToPressure_.size() << endl;
        dataFilestream.close();
    }
} 

time_t WeatherStatistics::convertDateTime(string date, string time)
{
    int yyyy, mon, dd = 0;
    if(sscanf(date.c_str(), "%d_%d_%d", &yyyy, &mon, &dd) !=3) {
        cerr << "ERROR: Failed to parse date string " << date << endl;
    }
    int hh, mm, ss = 0;
    if(sscanf(time.c_str(), "%d:%d:%d", &hh, &mm, &ss) != 3) {
        cerr << "ERROR: Failed to parse time string " << time << endl;
    }
    struct tm dateTime = {};
    dateTime.tm_year = yyyy - 1900;
    dateTime.tm_mon = mon - 1;
    dateTime.tm_mday = dd; 
    dateTime.tm_hour = hh;
    dateTime.tm_min = mm;
    dateTime.tm_sec = ss;

    return mktime(&dateTime);
}

int main() {

    WeatherStatistics stats;

	// request start date/time from user
    string startDate, startTime;
	cout << endl << "Enter START DATE as yyyy_mm_dd: ";
	cin >> startDate;
	cout << "Enter START TIME as hh:mm:ss (24-hour): ";
	cin >> startTime;

    if (!stats.isValidDateTime(startDate, startTime))
    {
        return 1;
    }

	// request end date/time from user
    string endDate, endTime;
	cout << "Enter END DATE as yyyy_mm_dd: ";
	cin >> endDate;
	cout << "Enter END TIME as hh:mm:ss (24-hour): ";
	cin >> endTime;

    if (!stats.isValidDateTime(endDate, endTime))
    {
        return 1;
    }
	double coeff = stats.coeff(startDate, startTime, endDate, endTime);
    cout << endl << "Coefficient: " << coeff * 24 * 60 * 60 << " inHg/day" << endl;
    return 0;
}