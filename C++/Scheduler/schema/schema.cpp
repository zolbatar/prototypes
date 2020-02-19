#include <map>
#include "activity.hpp"
#include "allocation.hpp"
#include "location.hpp"

class Schema {
public:
    std::map<std::string, Activity> activity;
    std::map<std::string, Allocation> allocation;
    std::map<std::string, Location> location;
};