//Subhasmita Mishra
//Roll No: 2401360011
//Course: B.Tech CSE(UX/UI)

// Name: Subhasmita Mishra
// Roll No: 2401360011
// Course: B.Tech CSE(UX/UI)

#include <iostream>
#include <string>
#include <limits>
using namespace std;

const int MAX_YEARS = 5;         // max years
const int MAX_CITIES = 15;       // max cities
const double SENTINEL = -9999.0; // represents missing data

// ================= Weather Record ADT =================
class WeatherRecord
{
public:
    string date; // Format: DD/MM/YYYY
    string city;
    double temperature;

    WeatherRecord(string d = "", string c = "", double t = SENTINEL)
        : date(d), city(c), temperature(t) {}
};

// ================= Weather Data Storage =================
class WeatherDataStorage
{
private:
    double data[MAX_YEARS][MAX_CITIES];
    string cities[MAX_CITIES];
    int years[MAX_YEARS];
    int cityCount, yearCount;

public:
    WeatherDataStorage(int y[], int yCount, string c[], int cCount)
    {
        yearCount = yCount;
        cityCount = cCount;

        for (int i = 0; i < yearCount; i++)
            years[i] = y[i];
        for (int j = 0; j < cityCount; j++)
            cities[j] = c[j];

        // initialize with sentinel
        for (int i = 0; i < yearCount; i++)
        {
            for (int j = 0; j < cityCount; j++)
            {
                data[i][j] = SENTINEL;
            }
        }
    }

    int getYearIndex(int year)
    {
        for (int i = 0; i < yearCount; i++)
        {
            if (years[i] == year)
                return i;
        }
        return -1;
    }

    int getCityIndex(string city)
    {
        for (int j = 0; j < cityCount; j++)
        {
            if (cities[j] == city)
                return j;
        }
        return -1;
    }

    // Insert new record
    void insert(const WeatherRecord &rec)
    {
        int year = stoi(rec.date.substr(6, 4)); // extract year
        int y = getYearIndex(year);
        int c = getCityIndex(rec.city);
        if (y != -1 && c != -1)
        {
            data[y][c] = rec.temperature;
            cout << "Record inserted successfully.\n";
        }
        else
        {
            cout << "Invalid year or city!\n";
        }
    }

    // Delete record (set to sentinel)
    void remove(string city, int year)
    {
        int y = getYearIndex(year);
        int c = getCityIndex(city);
        if (y != -1 && c != -1)
        {
            data[y][c] = SENTINEL;
            cout << "Record deleted successfully.\n";
        }
        else
        {
            cout << "Invalid year or city!\n";
        }
    }

    // Retrieve temperature data
    double retrieve(string city, int year)
    {
        int y = getYearIndex(year);
        int c = getCityIndex(city);
        if (y != -1 && c != -1)
        {
            return data[y][c];
        }
        return SENTINEL;
    }

    // Row-major access
    void rowMajorAccess()
    {
        cout << "\nRow-Major Order (Year-wise):\n";
        for (int i = 0; i < yearCount; i++)
        {
            for (int j = 0; j < cityCount; j++)
            {
                cout << "Year " << years[i] << ", City " << cities[j] << " -> ";
                if (data[i][j] == SENTINEL)
                    cout << "No Data\n";
                else
                    cout << data[i][j] << "°C\n";
            }
        }
    }

    // Column-major access
    void columnMajorAccess()
    {
        cout << "\nColumn-Major Order (City-wise):\n";
        for (int j = 0; j < cityCount; j++)
        {
            for (int i = 0; i < yearCount; i++)
            {
                cout << "City " << cities[j] << ", Year " << years[i] << " -> ";
                if (data[i][j] == SENTINEL)
                    cout << "No Data\n";
                else
                    cout << data[i][j] << "°C\n";
            }
        }
    }

    // Sparse data handling
    void handleSparseData()
    {
        int missing = 0, total = yearCount * cityCount;
        for (int i = 0; i < yearCount; i++)
        {
            for (int j = 0; j < cityCount; j++)
            {
                if (data[i][j] == SENTINEL)
                    missing++;
            }
        }
        cout << "\nSparse Data Handling:\nMissing entries = "
             << missing << " out of " << total << "\n";
    }

    // Complexity Analysis
    void analyzeComplexity()
    {
        cout << "\nComplexity Analysis:\n";
        cout << "Insert: O(1)\n";
        cout << "Delete: O(1)\n";
        cout << "Retrieve: O(1)\n";
        cout << "Row/Column traversal: O(n*m)\n";
        cout << "Space: O(n*m)\n";
    }
};

// ================= Main Driver =================
int main()
{
    int years[] = {2023, 2024, 2025};
    string cities[] = {"Delhi", "Mumbai", "Chennai"};

    WeatherDataStorage system(years, 3, cities, 3);
    
    int choice;
    do
    {
        cout << "\nWeather Data Storage System\n";
        cout << "1. Insert a record\n";
        cout << "2. Delete a record\n";
        cout << "3. Retrieve a record\n";
        cout << "4. Display data (Row-Major)\n";
        cout << "5. Display data (Column-Major)\n";
        cout << "6. Handle Sparse Data\n";
        cout << "7. Analyze Complexity\n";
        cout << "8. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        if (cin.fail())
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            choice = -1;
        }

        switch (choice)
        {
        case 1:
        {
            string date, city;
            double temp;
            cout << "Enter date (DD/MM/YYYY): ";
            cin >> date;
            cout << "Enter city(Delhi/Mumbai/Chennai): ";
            cin >> city;
            cout << "Enter temperature: ";
            cin >> temp;
            WeatherRecord rec(date, city, temp);
            system.insert(rec);
            break;
        }
        case 2:
        {
            string city;
            int year;
            cout << "Enter city to delete: ";
            cin >> city;
            cout << "Enter year to delete: ";
            cin >> year;
            system.remove(city, year);
            break;
        }
        case 3:
        {
            string city;
            int year;
            cout << "Enter city to retrieve: ";
            cin >> city;
            cout << "Enter year to retrieve: ";
            cin >> year;
            double result = system.retrieve(city, year);
            if (result == SENTINEL)
            {
                cout << "No record found.\n";
            }
            else
            {
                cout << "Temperature for " << city << " in " << year
                     << " is " << result << "°C\n";
            }
            break;
        }
        case 4:
            system.rowMajorAccess();
            break;
        case 5:
            system.columnMajorAccess();
            break;
        case 6:
            system.handleSparseData();
            break;
        case 7:
            system.analyzeComplexity();
            break;
        case 8:
            cout << "Exiting program.\n";
            break;
        default:
            cout << "Invalid choice. Please enter a number between 1 and 8.\n";
        }
    } while (choice != 8);

    return 0;
}
