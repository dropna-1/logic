#include <iostream>
#include <vector>
using namespace std;

class Space {
public:
    vector<int> neighbors;
    vector<int> zone;
    bool hidden;
    Space(vector<int> neighbors, vector<int> zone, bool hidden) 
    :neighbors(neighbors), zone(zone), hidden(hidden){}
};

class Board {
    vector<Space> spaces;
public:
    Space& getSpace(int id){
        return spaces.at(id);
    }
    Board(){
        spaces.push_back({{1, 2}, {1}, true});
        spaces.push_back({{0, 4}, {1}, false});
        spaces.push_back({{0, 3, 13}, {1}, false});
        spaces.push_back({{2, 12}, {1}, false});
        spaces.push_back({{1, 12, 5}, {1, 2}, false});
        spaces.push_back({{4, 6, 7}, {2}, false});
        spaces.push_back({{5, 7, 8}, {2}, false});
        spaces.push_back({{5, 6, 8}, {2}, false});
        spaces.push_back({{6, 7, 9, 10, 17}, {2, 3, 6}, false});
        spaces.push_back({{8, 10, 11}, {3}, false});
        spaces.push_back({{8, 9, 15}, {3}, false});
        spaces.push_back({{9}, {3}, true});
        spaces.push_back({{3, 4, 14}, {1, 4}, false});
        spaces.push_back({{2, 14, 22}, {4}, false});
        spaces.push_back({{12, 13}, {4}, false});
        spaces.push_back({{10, 16, 17}, {5}, false});
        spaces.push_back({{1, 2}, {1}, false});
        spaces.push_back({{8, 15, 18, 19, 28, 29}, {5, 6}, false});
        spaces.push_back({{16, 17}, {5}, false});
        spaces.push_back({{17, 20}, {6}, true});
        spaces.push_back({{19, 21, 26}, {6}, false});
        spaces.push_back({{20, 22}, {4, 6}, false});
        spaces.push_back({{13, 21, 23}, {4, 7}, false});
        spaces.push_back({{22, 24}, {7}, true});
        spaces.push_back({{23, 25}, {7}, false});
        spaces.push_back({{24, 26, 27}, {7}, false});
        spaces.push_back({{20, 25, 27, 28}, {6, 7}, false});
        spaces.push_back({{25, 26, 28}, {7}, false});
        spaces.push_back({{17, 26, 27, 29}, {7}, false});
        spaces.push_back({{17, 28, 30, 31}, {7}, false});
        spaces.push_back({{29, 31}, {7}, false});
        spaces.push_back({{16, 29, 30}, {5, 7}, false});
    }
};