
// be sure to change FIRSTNAME and LASTNAME with your own first and last name
#ifndef Matt_Sagat_PROJECT2
#define Matt_Sagat_PROJECT2

#include <functional>

// Struct Declarations

// Struct to capture (weighted) edges in a graph; used in Dijkstra's algorithm
// as well.
struct Edge {
    int from;
    int to;
    int weight; // default = 1 if unweighted graph
};


// struct to capture nodes in the graph such that you can recover the path
// length from source to node id, as well as the actual path from the
// source to each node.
struct Node {
    int id;
    int path_cost;
    int pred;
    bool operator> (const Node&) const;
    bool operator>=(const Node&) const;
    bool operator==(const Node&) const;
    bool operator< (const Node&) const;
    bool operator<=(const Node&) const;
    bool operator!=(const Node&) const;
};

inline bool Node::operator>=(const Node& node) const {return path_cost >= node.path_cost; }
inline bool Node::operator> (const Node& node) const {return path_cost > node.path_cost; }
inline bool Node::operator==(const Node& node) const {return path_cost == node.path_cost; }
inline bool Node::operator< (const Node& node) const {return path_cost < node.path_cost; }
inline bool Node::operator<=(const Node& node) const {return path_cost <= node.path_cost; }
inline bool Node::operator!=(const Node& node) const {return path_cost != node.path_cost; }


struct GridNode {
    int x;
    int y;
    double path_cost;
    int pred_x;
    int pred_y;
    bool operator> (const GridNode&) const;
    bool operator>=(const GridNode&) const;
    bool operator==(const GridNode&) const;
    bool operator< (const GridNode&) const;
    bool operator<=(const GridNode&) const;
    bool operator!=(const GridNode&) const;
};

inline bool GridNode::operator> (const GridNode& node) const { return path_cost > node.path_cost; }
inline bool GridNode::operator>=(const GridNode& node) const { return path_cost >= node.path_cost; }
inline bool GridNode::operator==(const GridNode& node) const { return path_cost == node.path_cost; }
inline bool GridNode::operator< (const GridNode& node) const { return path_cost < node.path_cost; }
inline bool GridNode::operator<=(const GridNode& node) const { return path_cost <= node.path_cost; }
inline bool GridNode::operator!=(const GridNode& node) const { return path_cost != node.path_cost; }

struct GridEdge {
    int from_x;
    int from_y;
    int to_x;
    int to_y;
};

// function declarations
std::vector<unsigned int> birthday_attack_1(std::function<unsigned short(unsigned int)> hash_function);
std::vector<unsigned int> birthday_attack_2(std::function<unsigned short(unsigned int)> hash_function);
std::vector<int> topological_sort(int n, std::vector<Edge> edges);
std::vector<int> dag_single_source(int n, std::vector<Edge> edges, int source);
std::vector<Node> dijkstras_algorithm(int n, std::vector<Edge> edges, int source);
double heuristic_cost(GridNode start, GridNode dest);

std::vector<GridNode> a_star_algorithm(
    int m, 
    int n, 
    std::vector<GridEdge> edges, 
    GridNode source, 
    GridNode target,
    std::function<double(GridNode,GridNode)> h
);

#endif
