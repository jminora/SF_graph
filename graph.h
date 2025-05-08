#include <string>

#define MAX 100   // Maximum number of people
#define DEG 10    // Maximum number of friends per person

using namespace std;

class Graph {
private:
    string names[MAX];            // Names of all people
    int graph[MAX][DEG];          // Adjacency list (list of friends)
    int friendCount[MAX] = { 0 }; // Number of friends each person has
    int personCount = 0;          // Number of unique people

    // Private method to return the index of a person, adding a new one if necessary
    int getOrAddPersonIndex(const string& name);

public:
    // Public method to add a connection (friendship) between two people
    void addConnection(const string& name1, const string& name2);

    // Public method to find and print all three-handshake pairs
    void findThreeHandshakePairs();
};

