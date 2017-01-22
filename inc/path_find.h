#ifndef INC_PATH_FIND_H
#define INC_PATH_FIND_H

#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>

namespace Route_Plan {

class PathFinder {

public:
    typedef boost::adjacency_list<vecS, vecS, undirectedS> Graph;

public:
    PathFinder();
    ~PathFinder();


};

};

#endif //INC_PATH_FIND_H