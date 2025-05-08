#include <iostream>
#include "graph.h"

int main() {
    Graph g; // Create a new graph object

    // Example of adding connections (friendships)
    g.addConnection("Oleg", "Nikita");
    g.addConnection("Nikita", "Nastya");
    g.addConnection("Nastya", "Ivan");
    g.addConnection("Ivan", "Eugene");

    // Find and print all three-handshake pairs
    g.findThreeHandshakePairs();

    return 0;
}
