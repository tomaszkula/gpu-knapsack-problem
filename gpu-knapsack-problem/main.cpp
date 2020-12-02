#include <iostream>
#include <vector>
#include <string>
#include "Menu.h"
#include "Knapsack.h"

int main()
{
    srand(time(0));

    Knapsack* _knapsack = new Knapsack();
    Menu* _menu = new Menu();

    while (true)
    {
        std::system("cls");
        _menu->Display();
        if (_menu->SelectOption(*_knapsack))
        {
            return 0;
        }

        std::cout << "Wcisnij klawisz, aby kontynuowac...";
        std::cin.ignore();
        std::cin.get();
    }

    return 0;
}