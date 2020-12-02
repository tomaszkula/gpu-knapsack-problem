#include <vector>

#include "Knapsack.h"

class Menu
{
private:
    static const std::string CAPACITY_FILE_PATH;
    static const std::string WEIGHTS_FILE_PATH;
    static const std::string PROFITS_FILE_PATH;
    static const std::string SOLUTION_FILE_PATH;

    void measure(Knapsack& _knapsack);
    void readDataFromFile(Knapsack& _knapsack);
    bool readCapacityFromFile(Knapsack& _knapsack, std::string _set);
    bool readWeightsFromFile(Knapsack& _knapsack, std::string _set);
    bool readProfitsFromFile(Knapsack& _knapsack, std::string _set);
    bool readSolutionFromFile(Knapsack& _knapsack, std::string _set);


public:
    void Display();
    bool SelectOption(Knapsack& _knapsack);
};