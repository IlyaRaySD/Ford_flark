#include <iostream>
#include <vector>
#include <limits>
#include <algorithm>
#include <set>
using namespace std;

struct Edge {
    int capacity; 
    int flow;
};

// Function for adding an edge
void add_edge(vector<vector<Edge>>& mat, int from, int to, int capacity) {
    mat[from][to].capacity = capacity;
    mat[to][from].capacity = 0; 
}

// Function for finding path
int path_find(int source, int sink, vector<vector<Edge>>& mat, vector<bool>& visited, int min_capacity) {
    if (source == sink) return min_capacity;
    visited[source] = true;
    for (int i = 0; i < mat.size(); ++i) {
        if (!visited[i] && mat[source][i].capacity - mat[source][i].flow > 0) {
            int flow_through_edge = path_find(i, sink, mat, visited, min(min_capacity, mat[source][i].capacity - mat[source][i].flow));
            if (flow_through_edge > 0) {
                mat[source][i].flow += flow_through_edge;
                mat[i][source].flow -= flow_through_edge;
                return flow_through_edge;
            }
        }
    }
    return 0;
}

// Max flow with Ford Fulrkenson algorithm
int ford_fulkerson(vector<vector<Edge>>& mat, int source, int sink) {
    int flow = 0;
    vector<bool> visited(mat.size());
    int path_flow;

    do {
        fill(visited.begin(), visited.end(), false);
        path_flow = path_find(source, sink, mat, visited, numeric_limits<int>::max());
        flow += path_flow;
    } while (path_flow > 0);

    return flow;
}

int main() {
    int n;
    cout << "Enter the number of vertex: ";
    cin >> n;

    vector<vector<Edge>> mat(n, vector<Edge>(n));

    cout << "Enter the capacity matrix(keep in your mind: the first vertex - the init, the last - the end):" << endl;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            int capacity;
            cin >> capacity;
            if (capacity > 0) {
                add_edge(mat, i, j, capacity);
            }
        }
    }

    int source = 0; 
    int sink = n - 1; 
    int max_flow = ford_fulkerson(mat, source, sink);

    cout << "\nMax flow: " << max_flow << endl;

    cout << "\nThe final matrix of capasity:\n";
    for (auto i : mat) {
        for (auto j : i) {
            cout << j.capacity << ' ';
        }
        cout << endl;
    }

    cout << "\nThe final matrix of flows:\n";
    for (auto i : mat) {
        for (auto j : i) {
            cout << j.flow << ' ';
        }
        cout << endl;
    }

    cout << "\n\n\n";

    return 0;
}

