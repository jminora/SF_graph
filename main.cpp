#include "graph.h"

int main() {
    // Example friendship network
    addConnection("Oleg", "Nikita");
    addConnection("Nikita", "Nastya");
    addConnection("Nastya", "Ivan");
    addConnection("Ivan", "Eugene");

    cout << "Pairs connected through exactly three handshakes:\n";
    findThreeHandshakePairs(); // Call the function to find pairs connected through three handshakes

    return 0;
}
