#include "graph.h"

static string names[MAX];        // Names of all people
static int graph[MAX][DEG];           // Adjacency list (list of friends)
static int friendCount[MAX] = { 0 };    // Number of friends each person has
static int personCount = 0;           // Number of unique people

// Returns the index of a person, adding a new one if necessary
static int getOrAddPersonIndex(const string& name) {
    for (int i = 0; i < personCount; ++i) {
        if (names[i] == name)
            return i;
    }
    if (personCount < MAX) {
        names[personCount] = name;
        return personCount++;
    }
    return -1; // Limit exceeded
}

void addConnection(const string& name1, const string& name2) {
    int a = getOrAddPersonIndex(name1);
    int b = getOrAddPersonIndex(name2);

    if (a == -1 || b == -1 || a == b)
        return; // Limit exceeded or attempt to connect a person to themselves

    // Add connection a -> b, if not already present
    bool exists = false;
    for (int i = 0; i < friendCount[a]; ++i) {
        if (graph[a][i] == b) {
            exists = true;
            break;
        }
    }
    if (!exists && friendCount[a] < DEG)
        graph[a][friendCount[a]++] = b;

    // Add connection b -> a
    exists = false;
    for (int i = 0; i < friendCount[b]; ++i) {
        if (graph[b][i] == a) {
            exists = true;
            break;
        }
    }
    if (!exists && friendCount[b] < DEG)
        graph[b][friendCount[b]++] = a;
}

void findThreeHandshakePairs() {
    bool printed[MAX][MAX] = { {false} };

    for (int start = 0; start < personCount; ++start) {
        int dist[MAX] = {};
        for (int i = 0; i < MAX; ++i) dist[i] = -1;

        int queue[MAX] = {};
        int front = 0, back = 0;

        dist[start] = 0;
        queue[back++] = start;

        // BFS search up to depth 3
        while (front < back) {
            int u = queue[front++];
            if (dist[u] >= 3) continue;

            for (int i = 0; i < friendCount[u]; ++i) {
                int v = graph[u][i];
                if (dist[v] == -1) {
                    dist[v] = dist[u] + 1;
                    queue[back++] = v;
                }
            }
        }

        // Find pairs at exactly distance 3
        for (int i = 0; i < personCount; ++i) {
            if (dist[i] == 3 && start < i && !printed[start][i]) {
                cout << names[start] << " - " << names[i] << endl;
                printed[start][i] = printed[i][start] = true;
            }
        }
    }
}
