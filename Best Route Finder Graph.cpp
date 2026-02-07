#include <iostream>
#include <climits>
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
        cout << "\n===CONGESTION ANALYSIS===" << endl;
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
    float getRoadLength() {
        return roadLength;
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
    
    // Dijkstra's Algorithm Helper Functions
    int minDistance(float dist[], bool visited[], int n) {
        float min = INT_MAX;
        int minIndex = -1;
        for (int i = 0; i < n; i++) {
            if (!visited[i] && dist[i] <= min) {
                min = dist[i];
                minIndex = i;
            }
        }
        return minIndex;
    }
    
    void printPath(int parent[], int j, string nodes[]) {
        if (parent[j] == -1) {
            cout << nodes[j];
            return;
        }
        printPath(parent, parent[j], nodes);
        cout << " -> " << nodes[j];
    }

public:
    TrafficSystem() {
        road1.initialize(80, 15.5);
        road2.initialize(60, 12.0);
        road3.initialize(100, 18.0);
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
    
    // Edge structure for adjacency list
    struct Edge {
        int destination;
        float weight;
        Edge* next;
        
        Edge(int dest, float w) {
            destination = dest;
            weight = w;
            next = NULL;
        }
    };
    
    // Add edge to adjacency list
    void addEdge(Edge* adjList[], int src, int dest, float weight) {
        Edge* newEdge = new Edge(dest, weight);
        newEdge->next = adjList[src];
        adjList[src] = newEdge;
    }
    
    // Dijkstra's Algorithm Implementation using Adjacency List
    void dijkstraShortestPath() {
        cout << "\n============================================" << endl;
        cout << "  DIJKSTRA'S SHORTEST PATH TO AIR UNIVERSITY" << endl;
        cout << "============================================" << endl;
        
        // Show current traffic status
        cout << "\n===CURRENT TRAFFIC CONDITIONS===" << endl;
        cout << "Route 1 (9th Avenue):" << endl;
        cout << "  - Vehicles: " << road1.getVehicleCount() 
             << " | Avg Speed: " << road1.calculateAverageSpeed() << " km/h"
             << " | Congestion: " << road1.getCongestionScore() << "/100" << endl;
        
        cout << "Route 2 (Margalla Road):" << endl;
        cout << "  - Vehicles: " << road2.getVehicleCount() 
             << " | Avg Speed: " << road2.calculateAverageSpeed() << " km/h"
             << " | Congestion: " << road2.getCongestionScore() << "/100" << endl;
        
        cout << "Route 3 (Margalla Avenue):" << endl;
        cout << "  - Vehicles: " << road3.getVehicleCount() 
             << " | Avg Speed: " << road3.calculateAverageSpeed() << " km/h"
             << " | Congestion: " << road3.getCongestionScore() << "/100" << endl;
        
        // graph structure
        const int V = 5;
        string nodes[V] = {"Home", "Junction A", "Junction B", "Junction C", "Air University"};
        
        // Create adjacency list
        Edge* adjList[V];
        for (int i = 0; i < V; i++)
            adjList[i] = NULL;
        float time1 = road1.calculateTravelTime();
        addEdge(adjList, 0, 1, time1 * 0.6); 
        addEdge(adjList, 1, 4, time1 * 0.4); 
     
        float time2 = road2.calculateTravelTime();
        addEdge(adjList, 0, 2, time2 * 0.5); 
        addEdge(adjList, 2, 4, time2 * 0.5);  
        
        float time3 = road3.calculateTravelTime();
        addEdge(adjList, 0, 3, time3 * 0.7); 
        addEdge(adjList, 3, 4, time3 * 0.3);
        
        addEdge(adjList, 1, 2, 5.0);  // Junction A to B
        addEdge(adjList, 2, 3, 4.0);  // Junction B to C
        addEdge(adjList, 1, 3, 7.0);  // Junction A to C
        float dist[V];
        bool visited[V];
        int parent[V];
        
        for (int i = 0; i < V; i++) {
            dist[i] = INT_MAX;
            visited[i] = false;
            parent[i] = -1;
        }
        
        dist[0] = 0;  // Distance from Home to Home is 0
        
        for (int count = 0; count < V - 1; count++) {
            int u = minDistance(dist, visited, V);
            if (u == -1) break;
            visited[u] = true;
            Edge* edge = adjList[u];
            while (edge != NULL) {
                int v = edge->destination;
                float weight = edge->weight;
                
                if (!visited[v] && dist[u] != INT_MAX && 
                    dist[u] + weight < dist[v]) {
                    dist[v] = dist[u] + weight;
                    parent[v] = u;
                }
                edge = edge->next;
            }
        }
        
        // Clean up adjacency list
        for (int i = 0; i < V; i++) {
            Edge* current = adjList[i];
            while (current != NULL) {
                Edge* temp = current;
                current = current->next;
                delete temp;
            }
        }
        
        // Display results
        cout << "\n===DIJKSTRA'S SHORTEST PATH RESULT===" << endl;
        cout << "Starting Point: " << nodes[0] << endl;
        cout << "Destination: " << nodes[4] << endl;
        cout << "\nOptimal Route: ";
        printPath(parent, 4, nodes);
        cout << "\n\nEstimated Travel Time: " << dist[4] << " minutes" << endl;
        
        // Determine which road corresponds to the path
        cout << "\nRECOMMENDED ROUTE:";
        if (parent[4] == 1) {
            cout << "Via 9th Avenue" << endl;
            cout << "   Expected Time: " << road1.calculateTravelTime() << " minutes" << endl;
            cout << "   Road Length: " << road1.getRoadLength() << " km" << endl;
            cout << "   Traffic Status: ";
            if (road1.getCongestionScore() >= 80) cout << "Heavy Congestion";
            else if (road1.getCongestionScore() >= 50) cout << "Moderate Traffic";
            else cout << "Clear Road";
            cout << endl;
        } else if (parent[4] == 2) {
            cout << "Via Margalla Road" << endl;
            cout << "   Expected Time: " << road2.calculateTravelTime() << " minutes" << endl;
            cout << "   Road Length: " << road2.getRoadLength() << " km" << endl;
            cout << "   Traffic Status: ";
            if (road2.getCongestionScore() >= 80) cout << "Heavy Congestion";
            else if (road2.getCongestionScore() >= 50) cout << "Moderate Traffic";
            else cout << "Clear Road";
            cout << endl;
        } else if (parent[4] == 3) {
            cout << "Via Margalla Avenue" << endl;
            cout << "   Expected Time: " << road3.calculateTravelTime() << " minutes" << endl;
            cout << "   Road Length: " << road3.getRoadLength() << " km" << endl;
            cout << "   Traffic Status: ";
            if (road3.getCongestionScore() >= 80) cout << "Heavy Congestion";
            else if (road3.getCongestionScore() >= 50) cout << "Moderate Traffic";
            else cout << "Clear Road";
            cout << endl;
        }
        
        // Compare all direct routes
        cout << "\n===COMPARISON OF ALL ROUTES===" << endl;
        cout << "1. Via 9th Avenue: " << time1 << " min" 
             << (parent[4] == 1 ? " -FASTEST" : "") << endl;
        cout << "2. Via Margalla Road: " << time2 << " min" 
             << (parent[4] == 2 ? " -FASTEST" : "") << endl;
        cout << "3. Via Margalla Avenue: " << time3 << " min" 
             << (parent[4] == 3 ? " -FASTEST" : "") << endl;
        
        cout << "\n===ALL PATHS FROM HOME===" << endl;
        for (int i = 1; i < V; i++) {
            cout << "\nTo " << nodes[i] << ": ";
            if (dist[i] == INT_MAX)
                cout << "No path available";
            else {
                printPath(parent, i, nodes);
                cout << " (Distance: " << dist[i] << " km)";
            }
        }
        cout << "\n============================================" << endl;
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
        cout<<"5. Dijkstra's Shortest Path to Air University" << endl;
        cout<<"6. Exit" << endl;
        cout << "===============================" << endl;
        cout <<"Enter choice (1-6): ";
        cin >> choice;
        if (choice == 1) {
            int roadNum, numVehicles, avgSpeed;
            cout<<"\n--- Select Road ---" << endl;
            cout<<"1. Via 9th Avenue (Speed Limit: 50 km/h)" << endl;
            cout<<"2. Via Margalla Road (Speed Limit: 50 km/h)" << endl;
            cout<<"3. Via Margalla Avenue  (Speed Limit: 80 km/h)" << endl;
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
            trafficSys.dijkstraShortestPath();
        else if (choice == 6)
            cout << "\nExiting Traffic System. Drive Safely!"<<endl;
        else
            cout << "Invalid choice!"<<endl;
    } while (choice != 6);
    return 0;
}