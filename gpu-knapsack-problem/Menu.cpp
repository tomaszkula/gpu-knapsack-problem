#include "Menu.h"

const std::string Menu::CAPACITY_FILE_PATH = "./data/";
const std::string Menu::WEIGHTS_FILE_PATH = "./data/";
const std::string Menu::PROFITS_FILE_PATH = "./data/";
const std::string Menu::SOLUTION_FILE_PATH = "./data/";

void Menu::Display()
{
    std::cout << "___________________________________________________________________________________________________\n";
    std::cout << "PROBLEM PLECAKOWY (KNAPSACK PROBLEM)\n";
    std::cout << "[1] Sekwencyjnie\n";
    std::cout << "[2] Rownolegle\n";
    std::cout << "--------------------------------------------\n";
    std::cout << "[3] Przegladaj informacje o plecaku\n";
    std::cout << "[4] Wczytaj dane z plikow\n";
    std::cout << "--------------------------------------------\n";
    std::cout << "[5] Pomiar\n";
    std::cout << "--------------------------------------------\n";
    std::cout << "[0] Wyjdz\n";
    std::cout << "___________________________________________________________________________________________________\n";
}

bool Menu::SelectOption(Knapsack& _knapsack)
{
    char _option = '0';
    std::cout << "Wybierz opcje: ";
    std::cin >> _option;

    switch (_option)
    {
    case '0':
        return true;

    case '1':
        _knapsack.SolveSequentially();
        break;

    case '2':
        _knapsack.SolveParallelly();
        break;

    case '3':
        _knapsack.ReadData();
        break;

    case '4':
        readDataFromFile(_knapsack);
        break;

    case '5':
        measure(_knapsack);
        break;
    }

    return false;
}

void Menu::readDataFromFile(Knapsack& _knapsack)
{
    std::string _set = "";
    std::cout << "Podaj nazwê setu danych (np. p01): ";
    std::cin >> _set;

    bool _didReadCapacity = readCapacityFromFile(_knapsack, _set);
    bool _didReadWeights = readWeightsFromFile(_knapsack, _set);
    bool _didReadProfits = readProfitsFromFile(_knapsack, _set);
    bool _didReadSolution = readSolutionFromFile(_knapsack, _set);

    if (_didReadCapacity && _didReadWeights && _didReadProfits && _didReadSolution)
    {
        std::cout << "Dane wczytane pomyslnie!" << std::endl;
    }
    else
    {
        if (!_didReadCapacity)
        {
            std::cout << "Blad odczytu pojemnosci plecaka!" << std::endl;
        }

        if (!_didReadWeights)
        {
            std::cout << "Blad odczytu wag przedmiotow!" << std::endl;
        }

        if (!_didReadProfits)
        {
            std::cout << "Blad odczytu cen przedmiotow!" << std::endl;
        }

        if (!_didReadSolution)
        {
            std::cout << "Blad odczytu najlepszego rozwiazania!" << std::endl;
        }
    }
}

void Menu::measure(Knapsack& _knapsack)
{
    int _itemsCount = 1000;
    _knapsack.TestSequentially(_itemsCount);
    _knapsack.TestParallelly(_itemsCount);

    std::cout << std::endl;

    _itemsCount = 1000000;
    _knapsack.TestSequentially(_itemsCount);
    _knapsack.TestParallelly(_itemsCount);
}

bool Menu::readCapacityFromFile(Knapsack& _knapsack, std::string _set)
{
    std::fstream _file;
    _file.open(CAPACITY_FILE_PATH + _set + "_c.txt", std::ios::in);
    if (_file.is_open())
    {
        int _capacity = 0;
        _file >> _capacity;
        _knapsack.SetCapacity(_capacity);

        _file.close();
        return true;
    }

    return false;
}

bool Menu::readWeightsFromFile(Knapsack& _knapsack, std::string _set)
{
    std::fstream _file;
    _file.open(WEIGHTS_FILE_PATH + _set + "_w.txt", std::ios::in);
    if (_file.is_open())
    {
        std::vector<int> _weights;
        int _w = 0;
        while (_file >> _w)
        {
            _weights.push_back(_w);
        }
        _knapsack.SetWeights(_weights);

        _file.close();
        return true;
    }

    return false;
}

bool Menu::readProfitsFromFile(Knapsack& _knapsack, std::string _set)
{
    std::fstream _file;
    _file.open(WEIGHTS_FILE_PATH + _set + "_p.txt", std::ios::in);
    if (_file.is_open())
    {
        std::vector<int> _profits;
        int _p = 0;
        while (_file >> _p)
        {
            _profits.push_back(_p);
        }
        _knapsack.SetProfits(_profits);

        _file.close();
        return true;
    }

    return false;
}

bool Menu::readSolutionFromFile(Knapsack& _knapsack, std::string _set)
{
    std::fstream _file;
    _file.open(WEIGHTS_FILE_PATH + _set + "_s.txt", std::ios::in);
    if (_file.is_open())
    {
        std::vector<int> _solution;
        int _s = 0;
        while (_file >> _s)
        {
            _solution.push_back(_s);
        }
        _knapsack.SetSolution(_solution);

        _file.close();
        return true;
    }

    return false;
}