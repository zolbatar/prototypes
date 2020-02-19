#include "../schema/schema.hpp"

class Test {

    void RunTest() {

    }

    void LoadCSV() {

        // Read in CSV file
        std::list <string> csvLines;
        string line;
        std::ifstream csv("DataSPIF.csv");
        if (csv.is_open()) {
            while (getline(csv, line)) {
                csvLines.push_back(line);
            }
            csv.close();
        }
        else {
            std::cout << "Unable to open file\n\n";
        }
    }

};