#include <iostream>
using namespace std;
//Vehicle Node (Linked List)
class VehicleNode {
public:
    int speed;
    VehicleNode* next;
VehicleNode(int spd) {
        speed = spd;
        next = NULL;
    }
};
//Road Class
class Road {
private:
    VehicleNode* head;
    int vehicleCount;
    int speedLimit;
    float roadLength;
public:
    Road() {
        head = NULL;
        vehicleCount = 0;
        speedLimit = 0;
    roadLength = 0;
    }
void initialize(int limit, float length) {
        speedLimit = limit;
        roadLength = length;
    }
void addVehicle(int speed) {
        VehicleNode* newVehicle = new VehicleNode(speed);
if (head == NULL) {
            head = newVehicle;
        } else {
            VehicleNode* temp = head;
            while (temp->next != NULL)
                temp = temp->next;
            temp->next = newVehicle;
        }
    vehicleCount++;
    }
float calculateAverageSpeed() {
        if (vehicleCount == 0) return 0;
int totalSpeed = 0;
        VehicleNode* temp = head;
        while (temp != NULL) {
            totalSpeed += temp->speed;
            temp = temp->next;
        }
        return (float)totalSpeed / vehicleCount;
    }
void detectCongestion() {
        float avgSpeed = calculateAverageSpeed();
cout << "\n*** CONGESTION ANALYSIS ***" << endl;
        cout << "Average Speed: " << avgSpeed << " km/h" << endl;
        cout << "Vehicle Count: " << vehicleCount << endl;
if (vehicleCount >= 15)
            cout << "Status: HEAVY CONGESTION - Too many vehicles!" << endl;
        else if (vehicleCount >= 10)
            cout << "Status: MODERATE CONGESTION - Traffic building up" << endl;
        else if (vehicleCount >= 5)
            cout << "Status: LIGHT TRAFFIC - Normal flow" << endl;
        else
            cout << "Status: FREE FLOW - Road is clear" << endl;
    }
int getVehicleCount() {
        return vehicleCount;
    }
int getSpeedLimit() {
        return speedLimit;
    }
float calculateTravelTime() {
        float avgSpeed = calculateAverageSpeed();
        if (avgSpeed == 0) avgSpeed = speedLimit;
        return (roadLength / avgSpeed) * 60;
    }
int getCongestionScore() {
        int score = 0;
if (vehicleCount >= 15) score += 50;
        else if (vehicleCount >= 10) score += 40;
        else if (vehicleCount >= 5) score += 25;
        else score += 10;
float avgSpeed = calculateAverageSpeed();
        if (avgSpeed == 0) avgSpeed = speedLimit;
float ratio = avgSpeed / speedLimit;
        if (ratio < 0.3) score += 50;
        else if (ratio < 0.5) score += 40;
        else if (ratio < 0.7) score += 25;
        else score += 10;
return score;
    }
~Road() {
while (head != NULL) {
            VehicleNode* temp = head;
            head = head->next;
            delete temp;
        }
    }
};
//Traffic System Class
class TrafficSystem {
private:
    Road road1, road2, road3;
public:
    TrafficSystem() {
        road1.initialize(50, 15.5);
        road2.initialize(50, 12.0);
        road3.initialize(80, 18.0);
    }
void printRoadName(int roadNum) {
        if (roadNum == 1) cout << "Via 9th Avenue";
        else if (roadNum == 2) cout << "Via Margalla Road";
        else if (roadNum == 3) cout << "Via Margalla Avenue";
    }
void addVehiclesToRoad(int roadNum, int numVehicles, int avgSpeed) {
        Road* selectedRoad;
if (roadNum == 1) selectedRoad = &road1;
        else if (roadNum == 2) selectedRoad = &road2;
        else if (roadNum == 3) selectedRoad = &road3;
        else {
            cout << "Invalid road number!" << endl;
            return;
        }
cout << "\nAdding " << numVehicles << " vehicles to ";
        printRoadName(roadNum);
        cout << "..." << endl;
        cout << "Average Speed: " << avgSpeed << " km/h" << endl;
for (int i = 0; i < numVehicles; i++)
    selectedRoad->addVehicle(avgSpeed);
cout << numVehicles << " vehicles added successfully!" << endl;
    }
void analyzeRoadCongestion(int roadNum) {
if (roadNum == 1) road1.detectCongestion();
        else if (roadNum == 2) road2.detectCongestion();
        else if (roadNum == 3) road3.detectCongestion();
        else cout << "Invalid road number!" << endl;
    }
void displayAllRoadsSummary() {
        cout << "\n============================================" << endl;
        cout << "        ALL ROADS TRAFFIC SUMMARY" << endl;
        cout << "============================================" << endl;
cout << "\n--- Via 9th Avenue ---" << endl;
        cout << "Speed Limit: " << road1.getSpeedLimit() << " km/h" << endl;
        cout << "Total Vehicles: " << road1.getVehicleCount() << endl;
        cout << "Congestion Score: " << road1.getCongestionScore() << "/100" << endl;
        cout << "Average Speed: " << road1.calculateAverageSpeed() << " km/h" << endl;
cout << "\n--- Via Margalla Road ---" << endl;
        cout << "Speed Limit: " << road2.getSpeedLimit() << " km/h" << endl;
        cout << "Total Vehicles: " << road2.getVehicleCount() << endl;
        cout << "Congestion Score: " << road2.getCongestionScore() << "/100" << endl;
        cout << "Average Speed: " << road2.calculateAverageSpeed() << " km/h" << endl;
cout << "\n--- Via Margalla Avenue ---" << endl;
        cout << "Speed Limit: " << road3.getSpeedLimit() << " km/h" << endl;
        cout << "Total Vehicles: " << road3.getVehicleCount() << endl;
        cout << "Congestion Score: " << road3.getCongestionScore() << "/100" << endl;
        cout << "Average Speed: " << road3.calculateAverageSpeed() << " km/h" << endl;
cout << "\n============================================" << endl;
    }
void findBestRoute() {
        cout << "\n========================================" << endl;
        cout << "   BEST ROUTE FINDER - ROUTE COMPARISON" << endl;
        cout << "========================================" << endl;
float t1 = road1.calculateTravelTime();
        float t2 = road2.calculateTravelTime();
        float t3 = road3.calculateTravelTime();
if (t1 <= t2 && t1 <= t3)
            cout << "BEST ROUTE: 9th Avenue" << endl;
        else if (t2 <= t1 && t2 <= t3)
            cout << "BEST ROUTE: Margalla Road" << endl;
        else
            cout << "BEST ROUTE: Margalla Avenue" << endl;
    }
};
// MAIN FUNCTION
int main() {
TrafficSystem trafficSys;
    int choice;
cout<<"============================================" << endl;
cout<<"   ROAD TRAFFIC ANALYSIS SYSTEM " << endl;
cout<<"     WITH CONGESTION DETECTOR" << endl;
cout<<"============================================" << endl;
 do {
cout<<"\n========== MAIN MENU ==========" << endl;
cout<<"1. Add Vehicles to Road" << endl;
cout<<"2. Analyze Congestion on Road" << endl;
cout<<"3. Display All Roads Summary" << endl;
cout<<"4. Find Best Route" << endl;
cout<<"5. Exit" << endl;
cout << "===============================" << endl;
cout <<"Enter choice (1-5): ";
cin >> choice;
if (choice == 1) {
    int roadNum, numVehicles, avgSpeed;
cout<<"\n--- Select Road ---" << endl;
    cout<<"1. Via 9th Avenue (Speed Limit: 50 km/h)" << endl;
cout<<"2. Via Margalla Road (Speed Limit: 50 km/h)" << endl;
cout<<"3. Via Margalla Avenue (Speed Limit: 80 km/h)" << endl;
cout<<"Enter road number: ";
cin>>roadNum;
cout<<"Enter number of vehicles to add: ";
cin>>numVehicles;
cout << "Enter average speed of vehicles (km/h): ";
cin>>avgSpeed;
if (numVehicles > 0 && avgSpeed > 0)
    trafficSys.addVehiclesToRoad(roadNum, numVehicles, avgSpeed);
else
    cout << "Invalid input!" << endl;
    }
else if (choice == 2) {
    int roadNum;
    cout<<"\n--- Select Road ---"<<endl;
    cout<<"1. Via 9th Avenue"<<endl;
    cout<<"2. Via Margalla Road"<<endl;
    cout<<"3. Via Margalla Avenue"<<endl;
    cout<<"Enter road (1-3): ";
    cin>>roadNum;
trafficSys.analyzeRoadCongestion(roadNum);
    }
else if (choice == 3)
    trafficSys.displayAllRoadsSummary();
else if (choice == 4)
    trafficSys.findBestRoute();
else if (choice == 5)
    cout << "\nExiting Traffic System. Drive Safely!"<<endl;
else
cout << "Invalid choice!"<<endl;
} while (choice != 5);
return 0;
}


