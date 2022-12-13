#include <iostream>
#include <fstream>

bool check_control(char);
int main()
{
    int banknotes[5] = { 100, 500, 1000, 2000, 5000 };
    int money[1000];
    char control;
    std::cout << "Welcome to Happy Barbers Bank!" << std::endl;
    std::cout << "If you want to top up an ATM - press '+'!" << std::endl;
    std::cout << "If you want to withdraw the money - press '-'!" << std::endl;
    std::cin >> control;
    if (check_control(control))
    {
        std::ifstream bank("bank.bin", std::ios::binary);
        if (bank.is_open())
        {
            bank.read((char*)money, sizeof(money));
            bank.close();
        }
        else
        {
            for (int i = 0; i < 1000; i++)
            {
                money[i] = 0;
            }
        }

        if (control == '+')
        {
            for (int i = 0; i < 1000; i++)
            {
                if (money[i] == 0)
                {
                    money[i] = banknotes[std::rand() % 5];
                }
            }
            std::ofstream storage("bank.bin", std::ios::binary);
            storage.write((char*)money, sizeof(money));
            storage.close();
            return 0;
        }
        else if (control == '-')
        {
            int amount;
            std::cout << "Enter the amount of withdrawal:" << std::endl;
            std::cin >> amount;
            if (amount % 100 != 0)
            {
                std::cerr << "Error! Invalid amount!" << std::endl;
            }
            else
            {
                int needAmount = amount;
                for (int i = 4; i >= 0; i--)
                {
                    for (int j = 0; j < 1000; j++)
                    {
                        if (money[j] == banknotes[i] 
                            && needAmount >= banknotes[i])
                        {
                            money[j] = 0;
                            needAmount -= banknotes[i];
                            if (needAmount == 0)
                            {
                                std::cout << "Amount issued: " << amount << std::endl;
                                std::ofstream storage("bank.bin", std::ios::binary);
                                storage.write((char*)money, sizeof(money));
                                storage.close();
                                return 0;
                            }
                        }
                    }
                }
                
            }
            std::cerr << "Not enough banknotes!" << std::endl;
            return 1;
        }

    }
    else
    {
        std::cerr << "Error! Input only '-' or '+'!" << std::endl;
        return 1;
    }
}

bool check_control(char control)
{
    if (control == '-' || control == '+')
    {
        return true;
    }
    else
    {
        return false;
    }
}