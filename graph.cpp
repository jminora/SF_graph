#include "graph.h"
#include <iostream>

using namespace std;

// Private method to find or add a person to the graph
// It returns the index of the person, or adds a new person if the name is not found
int Graph::getOrAddPersonIndex(const string& name) {
    // Search for the person in the list of names
    for (int i = 0; i < personCount; ++i) {
        if (names[i] == name)
            return i; // Return the index if the person already exists
    }
    // If the person doesn't exist, add them to the names list
    if (personCount < MAX) {
        names[personCount] = name;
        return personCount++; // Return the new index and increment the person count
    }
    return -1; // Return -1 if the maximum number of people has been reached
}

// Public method to add a connection (friendship) between two people
void Graph::addConnection(const string& name1, const string& name2) {
    int a = getOrAddPersonIndex(name1);
    int b = getOrAddPersonIndex(name2);

    // Check for invalid cases: limit exceeded or trying to connect a person to themselves
    if (a == -1 || b == -1 || a == b)
        return;

    // Add connection a -> b if not already present
    bool exists = false;
    for (int i = 0; i < friendCount[a]; ++i) {
        if (graph[a][i] == b) {
            exists = true;
            break; // If the connection exists, no need to add it again
        }
    }
    if (!exists && friendCount[a] < DEG)
        graph[a][friendCount[a]++] = b; // Add b to a's friend list

    // Add connection b -> a if not already present
    exists = false;
    for (int i = 0; i < friendCount[b]; ++i) {
        if (graph[b][i] == a) {
            exists = true;
            break; // If the connection exists, no need to add it again
        }
    }
    if (!exists && friendCount[b] < DEG)
        graph[b][friendCount[b]++] = a; // Add a to b's friend list
}

// Public method to find and print all three-handshake pairs
void Graph::findThreeHandshakePairs() {
    bool printed[MAX][MAX] = { {false} }; // 2D array to track which pairs are already printed

    // Iterate through each person in the graph
    for (int start = 0; start < personCount; ++start) {
        int dist[MAX] = {}; // Array to store the distance of each person from 'start'
        for (int i = 0; i < MAX; ++i) dist[i] = -1; // Initialize distances to -1 (unreachable)

        int queue[MAX]{};  // Array to represent the queue for BFS
        int front = 0, back = 0;
        dist[start] = 0;  // Distance to self is 0
        queue[back++] = start; // Add the starting person to the queue

        // Perform BFS up to a depth of 3
        while (front < back) {
            int u = queue[front++];
            if (dist[u] >= 3) continue; // Stop if the distance exceeds 3

            // Explore all friends of person 'u'
            for (int i = 0; i < friendCount[u]; ++i) {
                int v = graph[u][i];
                if (dist[v] == -1) { // If person v is not yet visited
                    dist[v] = dist[u] + 1; // Set distance to v
                    queue[back++] = v; // Add v to the queue for further exploration
                }
            }
        }

        // After BFS, check for pairs exactly at distance 3
        for (int i = 0; i < personCount; ++i) {
            if (dist[i] == 3 && start < i && !printed[start][i]) {
                cout << names[start] << " - " << names[i] << endl; // Print the three-handshake pair
                printed[start][i] = printed[i][start] = true; // Mark the pair as printed
            }
        }
    }
}
