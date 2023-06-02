#include <iostream>
#include <queue>
#include <vector>
#include <map>
using namespace std;

struct State {
    int jugA;
    int jugB;
    vector<string> rules;

    State(int a, int b) : jugA(a), jugB(b) {}
};

void solveWaterJugProblem(int jugACapacity, int jugBCapacity, int target) {
    queue<State> statesQueue;
    map<pair<int, int>, bool> visited;

    State initial(0, 0);
    statesQueue.push(initial);
    visited[make_pair(0, 0)] = true;

    while (!statesQueue.empty()) {
        State currentState = statesQueue.front();
        statesQueue.pop();

        if (currentState.jugA == target || currentState.jugB == target) {
            cout << "Rules to reach the target state:" << endl;
            for (const auto& rule : currentState.rules) {
                cout << rule << endl;
            }
            return;
        }

        // Rule 1: Fill jug A
        if (!visited[make_pair(jugACapacity, currentState.jugB)]) {
            State newState(jugACapacity, currentState.jugB);
            newState.rules = currentState.rules;
            newState.rules.push_back("Fill jug A");
            statesQueue.push(newState);
            visited[make_pair(jugACapacity, currentState.jugB)] = true;
        }

        // Rule 2: Fill jug B
        if (!visited[make_pair(currentState.jugA, jugBCapacity)]) {
            State newState(currentState.jugA, jugBCapacity);
            newState.rules = currentState.rules;
            newState.rules.push_back("Fill jug B");
            statesQueue.push(newState);
            visited[make_pair(currentState.jugA, jugBCapacity)] = true;
        }

        // Rule 3: Empty jug A
        if (!visited[make_pair(0, currentState.jugB)]) {
            State newState(0, currentState.jugB);
            newState.rules = currentState.rules;
            newState.rules.push_back("Empty jug A");
            statesQueue.push(newState);
            visited[make_pair(0, currentState.jugB)] = true;
        }

        // Rule 4: Empty jug B
        if (!visited[make_pair(currentState.jugA, 0)]) {
            State newState(currentState.jugA, 0);
            newState.rules = currentState.rules;
            newState.rules.push_back("Empty jug B");
            statesQueue.push(newState);
            visited[make_pair(currentState.jugA, 0)] = true;
        }

        // Rule 5: Pour jug A into jug B
        int amountToPour = min(currentState.jugA, jugBCapacity - currentState.jugB);
        if (!visited[make_pair(currentState.jugA - amountToPour, currentState.jugB + amountToPour)]) {
            State newState(currentState.jugA - amountToPour, currentState.jugB + amountToPour);
            newState.rules = currentState.rules;
            newState.rules.push_back("Pour jug A into jug B");
            statesQueue.push(newState);
            visited[make_pair(currentState.jugA - amountToPour, currentState.jugB + amountToPour)] = true;
        }

        // Rule 6: Pour jug B into jug A
        amountToPour = min(jugACapacity - currentState.jugA, currentState.jugB);
        if (!visited[make_pair(currentState.jugA + amountToPour, currentState.jugB - amountToPour)]) {
            State newState(currentState.jugA + amountToPour, currentState.jugB - amountToPour);
            newState.rules = currentState.rules;
            newState.rules.push_back("Pour jug B into jug A");
            statesQueue.push(newState);
            visited[make_pair(currentState.jugA + amountToPour, currentState.jugB - amountToPour)] = true;
        }
    }

    cout << "No solution found!" << endl;
}

int main() {
    int jugACapacity = 4;
    int jugBCapacity = 3;
    int target = 2;

    solveWaterJugProblem(jugACapacity, jugBCapacity, target);

    return 0;
}

