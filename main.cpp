#include <vector>
#include <iostream>
#include <sstream>
#include <algorithm>

/*
vector<string> country = {
    "011",  // row 0 (city 0)
    "101",  // row 1 (city 1)
    "110"   // row 2 (city 2)
};

Row 0 → "011"
This is country[0] = "011", which means:

country[0][0] = '0' → no road between city 0 and city 0 (self, always no road)

country[0][1] = '1' → road exists between city 0 and city 1

country[0][2] = '1' → road exists between city 0 and city 2

So city 0 is connected to cities 1 and 2.
*/


// define first
std::vector<std::string> country;
std::vector<std::string> build;
std::vector<std::string> destroy;

// define Edge struct to handle build or destroy
struct Edge {
    int cost;
    int u, v;
    bool isBuild; // true = build, false = destroy

    // defines how two Edge objects are compared
    bool operator<(const Edge& other) const {
        return cost < other.cost;
    }
};

// build union find data structure
class UnionFind {
private:
    std::vector<int> parent;

    std::vector<int> rank; // for ranking

public:
    UnionFind(int n) {
        parent.resize(n);
        rank.resize(n, 0);
        // at the beginning the each node is its parent
        for (int i = 0; i < n; i++) {
            parent[i] = i;
        }

    }

    // return where the node u is at which set
    int find (int u) {
        if (u != parent[u]) {
            // assign and return the recursive call
            parent[u] = find(parent[u]); // path compression
        }
        return parent[u];
    }

    // see if can union 2 sets: Merge two sets: the smaller tree goes under the bigger one --> use rank for this
    bool unionSet(int u, int v) {
        int parent_u = find(u);
        int parent_v = find(v);

        // already connected
        if (parent_u == parent_v) {
            return false;
        }

        // if can union --> union by rank 
        if (rank[parent_u] < rank[parent_v]) {
            parent[parent_u] = parent_v;
        } else if (rank[parent_u] > rank[parent_v]) {
            parent[parent_v] = parent_u;
        } else {
            parent[parent_v] = parent_u;
            rank[parent_u]++;
        }

        return true;
    }
};

void parseCommaToVector (std::string& input, std::vector<std::string>& output) {
    std::string word = "";
    for (char c : input) {
        if (c == ',') {
            output.push_back(word);
            word = "";
        } else {
            word += c;
        }
    }

    // store the last word, after the last comma
    if (!word.empty()) {
        output.push_back(word);
    }
}

// function to get the input line
void parseInput(std::string input) {
    std::stringstream ss(input);
    std::string country_str, build_str, destroy_str;

    // Split the three sections by space
    ss >> country_str >> build_str >> destroy_str;

    // parse by comma separated into vectors
    parseCommaToVector(country_str, country);
    parseCommaToVector(build_str, build);
    parseCommaToVector(destroy_str, destroy);
}



int letterToCost(char c) {
    if (c >= 'A' && c <= 'Z') {
        return c - 'A';
    }

    if (c >= 'a' && c <= 'z') {
        return c - 'a' + 26;
    }

    return 0;
}

// function to build edges: create all possible edges between pairs of cities 
/*
If there is already a road between city i and j (i.e., country[i][j] == '1') --> consider the cost to destroy that road (since it exists and can be removed).

If there is no road yet (country[i][j] == '0')--> consider the cost to build a road there.
*/
std::vector<Edge> buildEdges (const std::vector<std::string>& country, 
                              const std::vector<std::string>& build,
                              const std::vector<std::string>& destroy) {
    int numberOfCity = country.size();

    std::vector<Edge> edges;

    for (int i = 0; i < numberOfCity; i++) {
        // for unique pairs (i,j)
        for (int j = i+1; j < numberOfCity; j++) {
            if (country[i][j] == '1') {
                edges.push_back({letterToCost(destroy[i][j]), i, j, false});
            }
            else {
                edges.push_back({letterToCost(build[i][j]), i, j, true});
            }
        }
    }
    return edges;
}

// this function is not single responsibility
// int Kruskal_Cost(std::vector<Edge>& edges, int numberOfCity) {
//     int totalCost = 0;

//     // std::sort(edges.begin(), edges.end());

//     // Sort all edges: destroy edges by cost (ascending), then build edges
//     // sort(edges.begin(), edges.end(), [](const Edge& a, const Edge& b) {
//     //     if (!a.isBuild && !b.isBuild) return a.cost < b.cost; // Destroy edges sorted
//     //     if (a.isBuild && b.isBuild) return a.cost < b.cost;   // Build edges sorted
//     //     return !a.isBuild; // Process destroy edges first
//     // });

//     // call and use union find in this algorithm
//     UnionFind uf(numberOfCity);

//     // we shouldn't do this because we should start with existing edges --> this is free
//     // for (auto& e : edges) {
//     //     // if build 
//     //     if (e.isBuild) {
//     //         // then check if it is not in the same unionset
//     //         if (uf.unionSet(e.u, e.v)) {
//     //             totalCost += e.cost;
//     //         }
//     //     } 
//     //     // case: in the same set: can't union --> destroy
//     //     else {
//     //         if (!uf.unionSet(e.u, e.v)) {
//     //             totalCost += e.cost;
//     //         }
//     //     }
//     // }

//     // First, process all existing edges (destroy edges)
//     sort(edges.begin(), edges.end());

//     for (auto& e : edges) {
//         if (!e.isBuild) {
//             if (!uf.unionSet(e.u, e.v)) {
//                 totalCost += e.cost; // Need to destroy this edge
//             }
//         }
//     }

//     // Then, process all build edges
//     // sort(edges.begin(), edges.end());
//     for (auto& e : edges) {
//         if (e.isBuild) {
//             if (uf.unionSet(e.u, e.v)) {
//                 totalCost += e.cost; // Build this edge
//             }
//         }
//     }

//     return totalCost;
// }

// int Kruskal_Cost(std::vector<Edge>& edges, int n) {
//     int totalCost = 0;
//     UnionFind uf(n);

//     // Separate destroy and build edges
//     std::vector<Edge> destroyEdges;
//     std::vector<Edge> buildEdges;

//     for (auto& e : edges) {
//         if (!e.isBuild) {
//             // std::cout << "add edge " << e.u <<e.v << " with cost " << e.cost << std::endl;
//             destroyEdges.push_back(e);
//         } else {
//             buildEdges.push_back(e);
//         }
//     }

//     // Sort destroy edges by cost (cheapest first)
//     sort(destroyEdges.begin(), destroyEdges.end());

//     for (int i = 0; i < destroyEdges.size(); i++) {
//         std::cout << "destroy edge: " << destroyEdges[i].u << destroyEdges[i].v << " ";
//     }
//     std::cout << std::endl;

//     // Process destroy edges first
//     for (auto& e : destroyEdges) {
//         if (!uf.unionSet(e.u, e.v)) {
//             std::cout << "this used edge: " << e.u <<e.v << std::endl;
//             totalCost += e.cost; // Destroy this edge
//         }
//     }

//     // Sort build edges by cost (cheapest first)
//     sort(buildEdges.begin(), buildEdges.end());

//     // Process build edges
//     for (auto& e : buildEdges) {
//         if (uf.unionSet(e.u, e.v)) {
//             totalCost += e.cost; // Build this edge
//         }
//     }

//     return totalCost;
// }


int Kruskal_Cost(std::vector<Edge>& edges, int n) {
    int totalCost = 0;
    UnionFind uf(n);

    // Initial sum of all possible destroy costs (if we destroyed everything)
    int initial_destroy_sum = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            if (country[i][j] == '1') {
                initial_destroy_sum += letterToCost(destroy[i][j]);
            }
        }
    }

    // Now, populate edges with the costs for the MST algorithm
    // Positive costs for building, negative costs for "saving" destroy costs
    std::vector<Edge> kruskal_edges;
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            if (country[i][j] == '1') {
                // Cost to *not* destroy (i.e., keep) is -destroy[i][j]
                kruskal_edges.push_back({-letterToCost(destroy[i][j]), i, j, false}); // false means existing road
            } else {
                // Cost to build is build[i][j]
                kruskal_edges.push_back({letterToCost(build[i][j]), i, j, true}); // true means new road
            }
        }
    }

    // Sort edges by their effective cost (ascending)
    sort(kruskal_edges.begin(), kruskal_edges.end());

    int mst_cost_sum = 0;
    int edges_in_mst = 0;

    for (auto& e : kruskal_edges) {
        if (uf.unionSet(e.u, e.v)) {
            mst_cost_sum += e.cost;
            edges_in_mst++;
            if (edges_in_mst == n - 1) { // Found all N-1 edges for the MST
                break;
            }
        }
    }

    // The final answer is the initial total destroy cost minus the saved destroy costs
    // plus the build costs.
    // mst_cost_sum already reflects this:
    // If it's a kept existing road: its cost is -destroy[i][j], effectively subtracting from initial_destroy_sum.
    // If it's a built road: its cost is +build[i][j], effectively adding to the cost.

    // So, the final total cost is initial_destroy_sum + mst_cost_sum
    return initial_destroy_sum + mst_cost_sum;
}

int main () {
    int numberOfCity;

    std::string input;
    std::getline(std::cin, input);

    parseInput(input);

    // get the number of city
    numberOfCity = country.size();

    // build all edges
    std::vector<Edge> edges = buildEdges(country, build, destroy);

    // run kruskal and calculate the cost
    int cost = Kruskal_Cost(edges, numberOfCity);

 
    // output printing
    std::cout << cost << "\n";

    return 0;

}
