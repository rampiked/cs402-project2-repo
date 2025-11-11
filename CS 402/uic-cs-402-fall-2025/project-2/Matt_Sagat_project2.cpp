/*================================
CS 402 - Project #2:
Author : Matt Sagat
Date   : 11/11/2025
================================*/

//Included with Github Release
#include <functional>
#include <limits.h>
#include <random>
#include <iostream>

//Added by Matt
#include <vector>
#include <unordered_map>
#include <queue>
#include <cmath>
#include <algorithm>

//be sure to change Matt and Sagat with your own first and last name
#include "Matt_Sagat_project2.h"

using namespace std;

/****************
 * INSTRUCTIONS *
 ****************
 *
 * - Replace all instances of "Matt_Sagat" with your Matt and
 *   your last name. This include the .h and .cpp files, along with the
 *   header guards at the top of the .h file.
 *
 * - Implement the appropriate algorithms as described below.
 *   You must follow the specifications as written below.
 *
 * - Certain function signatures may not be modified (as it will affect auto
 *   grading). These functions will be specified.
 *
 * - You are allowed to add helper functions. Be sure to add the appropriate
 *   function prototypes in "Fistname_Sagat_project2.h."
 *
 * - The file "testing.cpp" has various functions you can utilize to test
 *   your code. You can also add your own tests!
 *
 * - If you are working in a group, please modify the comments directly below.
 *   
 * - IMPORTANT: If you are working in a group, every member is expected to submit their
 *   source code individually.
 *
 */

/*** PART 1: Hashing ***/

/* Birthday Attack 1
 *
 * 10 Points
 *
 * In this problem, you will implement a birthday attack on a simple hash function that is provided
 * in the header file. The goal will be to find a collision in the hash function using the Birthday 
 * Attack (with at least a 50% chance of success).
 *
 * Assumptions
 * - The hash function will have a 16 bit output (2 bytes). We will use the `unsigned short` type
 *   as the output type to make things simple.
 * - The hash function will take `unsigned integers` as input, again to make things simple.
 * - Your function will output:
 *     (a) two inputs a and b such that h(a) = h(b) (a collision), as a list [a, b], or 
 *     (b) {} if no collision is found.
 *   The output type of the function will be `vector<unsigned int>`.
 *
 * Algorithm Description
 * - Do the following a small constant number of times (at least 2):
 *     - Randomly generate 350 unsigned integers. Feel free to use the provided helper function
 *       `sample_int()`.
 *     - For each of the generated integers:
 *         - Hash the integer
 *         - Check if you find a collision. If yes, you can stop and output the two colliding inputs.
 * - If no collision is found, output {} (an empty list).
 *
 * Hash Function Signature
 *   unsigned short test_hash(unsigned int input);
 *
 */

unsigned int sample_int() {
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<unsigned int> dist(0);
    return dist(mt);
}

unsigned short test_hash(unsigned int input) {
    const unsigned int a = 3177205741; //3177205741
    const unsigned int b = 2371597069; //2371597069
    return static_cast<unsigned short>(a*input + b);
}

//Do not modify this function signature. 
vector<unsigned int> birthday_attack_1(function<unsigned short(unsigned int)> hash_function) {
    const int TRIALS = 3;     //small constant number of times (>= 2)
    const int SAMPLES = 350;  //samples per trial

    for (int t = 0; t < TRIALS; ++t) {
        unordered_map<unsigned short, unsigned int> seen; //map hash -> input that produced it
        seen.reserve(SAMPLES * 2);

        for (int i = 0; i < SAMPLES; ++i) {
            unsigned int x = sample_int();
            unsigned short h = hash_function(x);

            auto it = seen.find(h);
            if (it != seen.end()) {
                //collision found: h(it->second) == h(x)
                return vector<unsigned int>{ it->second, x };
            }

            seen.emplace(h, x);
        }
    }

    //no collision found after all trials
    return vector<unsigned int>{};
}



/* Birthday Attack 2
 *
 * 5 Points
 *
 * In this problem, you will implement a slightly different birthday attack on a simple 
 * hash function that is provided in the header file. The birthday attack described in 
 * part 1 above has the drawback of potentially needing too much space to implement
 * (proportional to sqrt(hash_output_domain_size)). You will address this in this
 * problem.
 *
 * The birthday-type attack you will implement in this problem is known as "Floyd's
 * tortoise and hare algorithm" (which is actually just a cycle finding algorithm).
 * We'll use it to implement a small-space birthday attack.
 *
 * Assumptions
 * - The hash function will have a 16 bit output (2 bytes). We will use the `unsigned short` type
 *   as the output type to make things simple.
 * - The hash function will take `unsigned integers` as input, again to make things simple.
 * - Your function will output two inputs a and b such that h(a) = h(b) (a collision), as a list [a, b].
 *   The output type of the function will be `vector<unsigned int>` to ensure that you can output -1 and
 *   to ensure there is no loss from converting a,b to a signed data-type.
 *
 * Algorithm Description
 * - Maintain two values, `tort` and `hare`, initialized as 
 *   tort = hash(0) and hare = hash(hash(0)).
 * - While tort != hare, take "one-step" with tort and "two-steps" with hare.
 *   This means updating tort by hashing the previous value of tort once, and hare
 *   by computing the double hash of the previous value of hare (see the initialization
 *   as an example).
 * - Once tort == hare, reset tort = 0.
 * - Now, while hash(tort) != hash(hare) take "one-step" with
 *   both tort and hare, until hash(tort) == hash(hare).
 * - Output [tort, hare]
 *
 * Additional Resources
 * - The following lecture notes explain both birthday attack algorithms:
 *      https://people.cs.uchicago.edu/~davidcash/284-autumn-21/12-hash.pdf
 *
 * Hash Function Signature
 *   unsigned short test_hash(unsigned int input);
 */

// Do not modify this function signature. 
vector<unsigned int> birthday_attack_2(function<unsigned short(unsigned int)> hash_function) {
    // Here, hash_function is an actual function. To test this function with
    // the provided `test_hash`, you can call your function in main as:
    //     vector<unsigned int> out = birthday_attack_1(test_hash);
    // Note you can implement your own test hash functions so long as their 
    // signatures match the `test_hash` function signature.
    
    // Your code here!
    //Map everything into 16-bit space
    auto f = [&](unsigned int x) -> unsigned int {
        return hash_function(x);
    };

    //Phase 1: find meeting point
    unsigned int tort = f(0);
    unsigned int hare = f(f(0));
    while (tort != hare) {
        tort = f(tort);
        hare = f(f(hare));
    }

    //Phase 2: find start of cycle
    unsigned int tort2 = 0;
    while (tort2 != hare) {
        tort2 = f(tort2);
        hare = f(hare);
    }

    //Now tort2 == hare is a *value* in the cycle.
    //Find two *different inputs* that hash to this same value.

    //Walk until we find two inputs mapping to the same hash value.
    unordered_map<unsigned short, unsigned int> seen;
    unsigned int x = 0;
    for (int i = 0; i < 100000; ++i) {
        unsigned short h = hash_function(x);
        auto it = seen.find(h);
        if (it != seen.end() && it->second != x) {
            return { it->second, x };
        }
        seen[h] = x;
        x = f(x);
    }

    //fallback
    return {};
}

/*** PART 2: Graphs ***/

/* Topological Sorting
 *
 * 5 Points
 *
 * In this problem, you are tasked with reading the description of a
 * directed graph as input, then outputting a valid topological
 * sort of the graph, if one exists.
 *
 * Input
 *  - int n: number of nodes/vertices in the graph, labeled from 0 to n-1
 *  - vector<Edge> edges: a list of directed edges in the graph
 *
 * Output
 *  - vector<int>: a valid topological sorting of the graph. If
 *    no topological sorting exists, output an empty list.
 *    If multiple topological sortings exist, you only need to
 *    output a single one.
 *
 * Note: Edge is a struct defined in Matt_Sagat_project2.h.
 *
 */


vector<int> topological_sort(int n, vector<Edge> edges) {
    //adjacency list and indegree counter
    vector<vector<int>> adj(n);
    vector<int> indegree(n, 0);

    //Build graph
    for (const auto &e : edges) {
        adj[e.from].push_back(e.to);
        indegree[e.to]++;
    }

    //Queue (or vector used as queue) for nodes with indegree 0
    vector<int> order;
    vector<int> zero_indegree;
    zero_indegree.reserve(n);

    for (int i = 0; i < n; ++i) {
        if (indegree[i] == 0) {
            zero_indegree.push_back(i);
        }
    }

    //Process all vertices with indegree 0
    while (!zero_indegree.empty()) {
        int u = zero_indegree.back();
        zero_indegree.pop_back(); //using as stack or queue both fine
        order.push_back(u);

        //Decrease indegree for neighbors
        for (int v : adj[u]) {
            indegree[v]--;
            if (indegree[v] == 0) {
                zero_indegree.push_back(v);
            }
        }
    }

    //If all nodes are processed, return order; else, there’s a cycle
    if ((int)order.size() == n) {
        return order;
    } else {
        return {}; //cycle detected
    }
}



/* Single Source Shortest Paths on DAGs
 *
 * 10 points
 *
 * In this problem, you will be given a directed acyclic graph with 
 * arbitrary integer edge weights (i.e., they can be negative!), as
 * well as a single source node. Your goal will be to output the
 * shortest distance from the source to every other vertex in the
 * graph.
 *
 * Input
 *  - int n: number of nodes in the graph, labeled from 0 to n-1
 *  - vector<Edge> edges: list of weighted directed edges in the graph
 *  - int source: ID of the source node
 *
 * Output
 *  - vector<int>: vector of size n such that entry i is the distance
 *    from source to i in the given graph. Use the value "INT_MAX" to
 *    indicate that there is no path from source to i.
 *
 * Algorithm
 *  - Topological Sorting + BFS is enough to solve this problem.
 *
 * Assumptions
 *  - The graph given as input will always be a DAG
 *
 */
vector<int> dag_single_source(int n, vector<Edge> edges, int source) {
    //Step 1: Get topological order
    vector<int> topo_order = topological_sort(n, edges);

    //Step 2: Initialize distances
    vector<int> dist(n, INT_MAX);
    dist[source] = 0;

    //Step 3: Relax edges in topological order
    for (int u : topo_order) {
        if (dist[u] == INT_MAX) continue; //skip unreachable nodes
        for (const Edge& e : edges) {
            if (e.from == u && dist[u] != INT_MAX) {
                if (dist[u] + e.weight < dist[e.to]) {
                    dist[e.to] = dist[u] + e.weight;
                }
            }
        }
    }

    //Step 4: Return distances
    return dist;
}


/* Dijkstra's Algorithm
 *
 * 20 Points
 *
 * In this problem, you are simply tasked to implement Dijkstra's Algorithm.
 *
 * Input
 *  - int n: number of nodes in the graph, labeled from 0 to n-1
 *  - vector<Edge> edges: list of weighted directed edges in the graph
 *  - int source: ID of the source node
 *
 * Output
 *  - vector<Node>: a list of size n such that entry i contains a Node node
 *    with the following properties:
 *      - node.id = i
 *      - node.path_cost = cost of the shortest path from source to i
 *      - node.pred = id of the predecessor of i on the shortest path from
 *        source to i
 *
 * Assumptions
 *  - You are guaranteed that the graph contains only non-negative edges
 *    (i.e., weight at least 0). For simplicity, all weights will be
 *    integers.
 * 
 * Note: Node is a struct defined in Matt_Sagat_project2.h.
 */


vector<Node> dijkstras_algorithm(int n, vector<Edge> edges, int source) {
    // Your code here!
    // Note: see the LeetCode from in-class for the problem "Cheapest Flights
    // K stops" to see how you can create a priority_queue with the Node struct.
    // Initialize graph nodes
    vector<Node> graph(n);
    for (int i = 0; i < n; ++i) {
        graph[i].id = i;
        graph[i].path_cost = INT_MAX; //infinity
        graph[i].pred = -1;           //no predecessor yet
    }

    //Build adjacency list (neighbors with weights)
    vector<vector<pair<int,int>>> adj(n);
    for (Edge e : edges) {
        adj[e.from].push_back({e.to, e.weight});
    }

    //Min-priority queue for Dijkstra: sorts by path_cost automatically via operator<
    priority_queue<Node, vector<Node>, greater<Node>> pq;

    //Start at source
    graph[source].path_cost = 0;
    pq.push(graph[source]);

    while (!pq.empty()) {
        Node curr = pq.top();
        pq.pop();

        //If the current cost is already larger than the recorded cost, skip
        if (curr.path_cost > graph[curr.id].path_cost) continue;

        //Explore neighbors
        for (auto [neighbor_id, weight] : adj[curr.id]) {
            int new_cost = curr.path_cost + weight;
            if (new_cost < graph[neighbor_id].path_cost) {
                graph[neighbor_id].path_cost = new_cost;
                graph[neighbor_id].pred = curr.id;
                pq.push(graph[neighbor_id]);
            }
        }
    }

    return graph;
}


/* A-star Algorithm
 *
 * 25 Points
 *
 * In this problem, you are asked to implement a modified version of Dijkstras,
 * known as A* (A-star). The A* algorithm is very similar to Dijkstras, with
 * two notable differences:
 *  (a) A* uses some heuristic function h to estimate the distance between any
 *      two nodes; and
 *  (b) A* only finds a path from a specified source node and a target node.
 *
 * Recall in Dijkstras, the algorithm finds the shortest path from a single
 * source to all other nodes in the graph.
 *
 * Given a source s and a target t, A* is guaranteed to output a shortest path
 * from s to t as long as the heuristic h underestimates the distance between 
 * any two nodes u,v in the graph. If d(u,v) represents the actual distance
 * between u and v, then h(u,v) <= d(u,v) for all u,v is enough to guarantee
 * that A* outputs a shortest path from s to t.
 *
 * For this specific version of A*, you will be given two points on a grid (a
 * start point and an end point). The grid will be specified by a graph, with
 * nodes being a GridNode (each with their own x and y value on the grid), and
 * edges being a GridEdge. Each GridEdge has a weight that is of a double type.
 * A GridEdge will only connect adjacent or diagonal nodes. Formally, for a
 * GridNode at point (x,y), all of the following edges are possible:
 *
 *  - (x+1, y) (cost = 1.0)
 *  - (x-1, y) (cost = 1.0)
 *  - (x, y+1) (cost = 1.0)
 *  - (x, y-1) (cost = 1.0)
 *  - (x+1, y+1) (cost = 1.5)
 *  - (x-1, y+1) (cost = 1.5)
 *  - (x+1, y-1) (cost = 1.5)
 *  - (x-1, y-1) (cost = 1.5)
 * 
 * Here, edges all have an implicit movement cost, described above. Moving along
 * a diagonal edge has a cost of 1.5, while moving along a cardinally adjacent  
 * edge (north, south, east, west) has a cost of 1.
 *
 * Note that GridEdge and GridNode are structs defined in Matt_Sagat_project2.h.
 *
 * Input:
 *  - int m: number of columns (x-axis)
 *  - int n: number of rows in the grid (y-axis)
 *  - vector<GridEdge> edges: list of edges in the graph
 *  - GridNode source: source node of the algorithm
 *  - GridNode target: target node of the algorithm
 *  - function<double(GridNode, GridNode)> h: h is a function which takes as input
 *      two GridNodes and outputs a double. This represents the heruistic_cost
 *      function for A*.
 *
 * Output:
 *  - vector<GridNode>: a list of nodes containing the path from source to target.
 *                      Note that if variable "output" is your output vector, then
 *                      it must satisfy the following properties:
 *                          - if a path from source to target exists, then
 *                              - output[0] = source
 *                              - output[output.size()-1] = target
 *                              - Moreover, output[output.size()-1].path_cost is the cost
 *                                of the path from source to target.
 *                          - if no path from source to target exists, then
 *                              - output = {} (the empty list)
 *
 * Algorithm:
 *  The algorithm is nearly identical to Dijkstra's Algorithm, with the following changes.
 *      - Suppose in Dijkstra's you are currently considering node u and expanding the 
 *        frontier along the neighbors of u.
 *      - Let v be a neighbor of u.
 *      - In Dijkstra's, you check if u.cost + weight(u,v) < v.cost, where weight(u,v) 
 *        is the weight of the edge from u to v. If this is true, you update v.cost as
 *        v.cost = u.cost + weight(u,v), update it in / add it to the priority queue,
 *        and continue.
 *      - In A*, this is modified as: v.cost = u.cost + weight(u,v) + heuristic_cost(v, target),
 *        where heuristic_cost(v, target) is a heuristic distance from node v to the target node
 *        target.
 *  
 *  As part of your implementation of A*, you are required to implement the function
 *  heuristic_cost(GridNode start, GridNode dest) defined below. Your heuristic should never
 *  over estimate the distance between any two nodes start and dest. Remember, in theory you
 *  can move north, south, east, west, or along any diagonal (so long as there is an edge).
 *  Use this information to write a heuristic function that never over estimates the distance.
 *
 *
 * Additional Resources:
 *  - Wikipedia: https://en.wikipedia.org/wiki/A*_search_algorithm
 *  - GeeksForGeeks: https://www.geeksforgeeks.org/dsa/a-search-algorithm/
 *  - Stanford: https://theory.stanford.edu/~amitp/GameProgramming/AStarComparison.html
 *
 */



// You must implement this function.
double heuristic_cost(GridNode start, GridNode dest) {
    int dx = abs(dest.x - start.x);
    int dy = abs(dest.y - start.y);

    //Diagonal moves cost 1.5, straight moves cost 1
    int minD = std::min(dx, dy);
    int maxD = std::max(dx, dy);

    //Optimal path: use diagonals for min(dx, dy), then straight moves for the remainder
    return 1.5 * minD + 1.0 * (maxD - minD);
}

// To test your algorithm with the function "heruistic_cost" above,
// simply pass "heuristic_cost" as a parameter to the function.
vector<GridNode> a_star_algorithm(
    int m, 
    int n, 
    vector<GridEdge> edges, 
    GridNode source, 
    GridNode target,
    function<double(GridNode,GridNode)> h
) 
{
    // Your code here!
    // Be sure to use "h" from the inputs in your implementation; do not
    // directly use "heruistic_cost" above!
    //Map from (x,y) to neighbors
    unordered_map<int, unordered_map<int, vector<pair<GridNode,double>>>> graph;
    for(auto &e: edges) {
        graph[e.from_x][e.from_y].push_back({{e.to_x, e.to_y, 0.0, -1, -1}, 
                                            (e.to_x != e.from_x && e.to_y != e.from_y) ? 1.5 : 1.0});
    }

    auto key = [](int x, int y) { return x * 100000 + y; }; //unique key for visited
    unordered_map<int, double> g_cost; //cost from source to node
    unordered_map<int, pair<int,int>> pred; //predecessor map

    //Min-heap priority queue with cost + heuristic
    auto cmp = [&](const GridNode &a, const GridNode &b) { return a.path_cost > b.path_cost; };
    priority_queue<GridNode, vector<GridNode>, decltype(cmp)> pq(cmp);

    source.path_cost = 0.0;
    source.pred_x = -1;
    source.pred_y = -1;
    pq.push(source);
    g_cost[key(source.x, source.y)] = 0.0;

    while(!pq.empty()) {
        //Take the node with the smallest estimated total cost (f = g + h)
        GridNode curr = pq.top(); 
        pq.pop();

        //If we have reached the target, reconstruct the path from source to target
        if(curr.x == target.x && curr.y == target.y) {
            vector<GridNode> path;
            GridNode node = curr;
            //Follow the predecessor chain backwards from target to source
            while(node.pred_x != -1 && node.pred_y != -1) {
                path.push_back(node);
                int px = node.pred_x, py = node.pred_y;
                //Reconstruct the node using g_cost (actual cost from source)
                node = {px, py, g_cost[key(px,py)], -1, -1};
            }
            //Add the source node at the beginning
            path.push_back(source);
            //Reverse the path so that it goes from source to target
            reverse(path.begin(), path.end());
            return path;
        }

        //Expand all neighbors of the current node
        for(auto &nei : graph[curr.x][curr.y]) {
            GridNode neighbor = nei.first;  //Neighbor node
            double move_cost = nei.second;   //Cost to move from current to neighbor
            int k = key(neighbor.x, neighbor.y); //Unique key for this neighbor

            //Tentative g cost: actual cost from source to this neighbor via current
            double tentative_g = curr.path_cost + move_cost;

            //If this neighbor has not been visited yet, or we found a cheaper path
            if(!g_cost.count(k) || tentative_g < g_cost[k]) {
                g_cost[k] = tentative_g;  //Ipdate g cost
                neighbor.path_cost = tentative_g + h(neighbor, target); //f = g + h
                neighbor.pred_x = curr.x; //Store predecessor for path reconstruction
                neighbor.pred_y = curr.y;
                pq.push(neighbor); //Add neighbor to priority queue for future expansion
            }
        }
    }

    //No path found
    return {};
}

int main() {
    return 0;
}
