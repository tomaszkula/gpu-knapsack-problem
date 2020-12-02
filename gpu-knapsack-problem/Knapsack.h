#ifndef KNAPSACK_H
#define KNAPSACK_H

#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>

#include "Clock.h"

extern "C"
{
    void solveParallelly(int _capacity, std::vector<int> _weights, std::vector<int> _profits);
    float testParallelly(int _capacity, std::vector<int> _weights, std::vector<int> _profits, int _times);
}

class Knapsack
{
private:
    int capacity;
    std::vector<int> weights;
    std::vector<int> profits;
    std::vector<int> solution;

public:
    void ReadData();
    void SetCapacity(int _capacity);
    void SetWeights(std::vector<int> _weights);
    void SetProfits(std::vector<int> _profits);
    void SetSolution(std::vector<int> _solution);
    void SolveSequentially();
    void TestSequentially(int _times);
    void SolveParallelly();
    void TestParallelly(int _times);
};

#endif //KNAPSACK_H