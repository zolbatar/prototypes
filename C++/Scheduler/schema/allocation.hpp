#include <chrono>

class Allocation {
public:
    std::string activity_id;
    std::chrono::system_clock start;
    std::chrono::system_clock end;
};