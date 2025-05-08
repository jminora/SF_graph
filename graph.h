#pragma once
#include <string>
#include <iostream>

using namespace std;

const int MAX = 100;     // Maximum number of people
const int DEG = 20;      // Maximum number of friends per person

// Function to add a connection between two people
void addConnection(const string& name1, const string& name2);

// Function to find all pairs connected through exactly 3 handshakes
void findThreeHandshakePairs();
