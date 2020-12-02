#include "knapsack.h"

void Knapsack::ReadData()
{
    std::cout << "------------ ZALADOWANE DANE ------------" << std::endl;
    std::cout << "Knapsack capacity : " << capacity << std::endl;
    std::cout << std::setw(10) << "WEIGHTS" << std::setw(10) << "PROFITS" << std::setw(10) << "SOLUTION" << std::endl;
    for (size_t i = 0; i < weights.size(); i++)
    {
        std::cout << std::setw(10) << weights[i] << std::setw(10) << profits[i] << std::setw(10) << solution[i] << std::endl;
    }
}

void Knapsack::SetCapacity(int _capacity)
{
    capacity = _capacity;
}

void Knapsack::SetWeights(std::vector<int> _weights)
{
    weights = _weights;
}

void Knapsack::SetProfits(std::vector<int> _profits)
{
    profits = _profits;
}

void Knapsack::SetSolution(std::vector<int> _solution)
{
    solution = _solution;
}

void Knapsack::SolveSequentially()
{
    int _n = weights.size() + 1;
    int _m = capacity + 1;

    int** _maxValues = new int* [_n];
    for (int i = 0; i < _n; i++)
    {
        _maxValues[i] = new int[_m];
        for (int j = 0; j < _m; j++)
        {
            _maxValues[i][j] = 0;
        }
    }

    for (int i = 1; i < _n; i++) {
        for (int j = 0; j < _m; j++) {
            _maxValues[i][j] = _maxValues[i - 1][j];

            if ((j >= weights[i - 1]) && (_maxValues[i][j] < _maxValues[i - 1][j - weights[i - 1]] + profits[i - 1]))
            {
                _maxValues[i][j] = _maxValues[i - 1][j - weights[i - 1]] + profits[i - 1];
            }
        }
    }

    std::cout << "BEST VALUE : " << _maxValues[_n - 1][capacity] << std::endl;
    std::cout << std::setw(10) << "WEIGHTS" << std::setw(10) << "PROFITS" << std::setw(10) << "SOLUTION" << std::endl;
    int _maxCapacity = capacity;
    for (int i = _n - 2; i > 0; i--)
    {
        std::cout << std::setw(10) << weights[i] << std::setw(10) << profits[i];
        if (_maxValues[i][_maxCapacity] != _maxValues[i - 1][_maxCapacity])
        {
            std::cout << std::setw(10) << "1";
            _maxCapacity -= weights[i - 1];
        }
        else
        {
            std::cout << std::setw(10) << "0";
        }
        std::cout << std::endl;
    }
}

void Knapsack::TestSequentially(int _times)
{
    Clock _c; _c.startCounter();
    double _duration = 0.0;

    for (int t = 0; t < _times; t++)
    {
        int _n = weights.size() + 1;
        int _m = capacity + 1;

        int** _maxValues = new int* [_n];
        for (int i = 0; i < _n; i++)
        {
            _maxValues[i] = new int[_m];
            for (int j = 0; j < _m; j++)
            {
                _maxValues[i][j] = 0;
            }
        }

        for (int i = 1; i < _n; i++) {
            for (int j = 0; j < _m; j++) {
                _maxValues[i][j] = _maxValues[i - 1][j];

                if ((j >= weights[i - 1]) && (_maxValues[i][j] < _maxValues[i - 1][j - weights[i - 1]] + profits[i - 1]))
                {
                    _maxValues[i][j] = _maxValues[i - 1][j - weights[i - 1]] + profits[i - 1];
                }
            }
        }
    }

    _duration = _c.getCounter();
    std::cout << _times << " : sequentially duration : " << _duration / 1000000.0 << "s" << std::endl;
}

void Knapsack::SolveParallelly()
{
    solveParallelly(capacity, weights, profits);
}

void Knapsack::TestParallelly(int _times)
{
    float _duration = testParallelly(capacity, weights, profits, _times);
    std::cout << _times << " : parallelly duration : " << _duration / 1000.0 << "s" << std::endl;
}