// 2023.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include "utils.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <regex>
#include <functional>
#include <set>
#include <numeric>
#include <limits.h>
#include <numeric>
#include <array>
#include <queue>
#include <iomanip>
#include <stack>
#include <bitset>
using namespace std;

int day1_b(int value, std::map<int, int>& cache)
{
    if (value <= 0) { return 0; }
    
    if (cache.find(value) != cache.end())
    {
        return cache[value];
    }
    
    int newValue = (value / 3) - 2;

    int toReturn = day1_b(newValue, cache);

    if (newValue > 0)
    {
        toReturn += newValue;
    }

    cache[value] = toReturn;
    return toReturn;
}

void day1()
{
    auto fileTxt = ReadFile("./input/day1.txt");

    long long acumA = 0;
    long long acumB = 0;
    std::map<int, int> cacheB;

    for (auto n : fileTxt)
    {
        int val = atoi(n.c_str());
        long long calcA = (val / 3) - 2;
        acumA += calcA;

       int calcB = day1_b(val, cacheB);
       acumB += calcB;

    }
    std::cout << "day 1 => " << acumA << "\n";
    std::cout << "day 1_B => " << acumB << "\n";
}

void day2_runProgram(std::vector<long long>& memory)
{
    int index = 0;

    while (memory[index] != 99)
    {
        int operation = memory[index];
        int pos1 = memory[index + 1];
        int pos2 = memory[index + 2];
        int dest = memory[index + 3];
        index += 4;

        auto val1 = memory[pos1];
        auto val2 = memory[pos2];

        long long result = 0;
        if (operation == 1)
        {
            result = val1 + val2;
        }
        else
        {
            if (operation == 2)
            {
                result = val1 * val2;
            }
            else
            {
                std::cout << "error;";
            }
        }
        
        memory[dest] = result;

    }

}

void day2()
{
    auto txt = ReadFile("./input/day2.txt")[0];
    auto split_value = split(txt, ",");
    std::vector<long long> memory;
    
    for (auto v : split_value)
    {
        memory.push_back(atoll(v.c_str()));
    }

    std::vector<long long> copyMemory = memory;

    memory[1] = 12;
    memory[2] = 2;

    day2_runProgram(memory);

    std::cout << "day2 => " << memory[0] << "\n";


    for (int noun = 0; noun <= 99; ++noun)
    {
        for (int verb = 0; verb <= 99; ++verb)
        {
            auto mem = copyMemory;
            mem[1] = noun;
            mem[2] = verb;

            day2_runProgram(mem);
            if (mem[0] == 19690720)
            {
                std::cout << "day2_b => " << (100 * noun) + verb;
                return;
            }
        }
    }

}

std::vector<std::pair<int, int>> day3_getPath(std::string& path, std::vector<int>& acumDistances)
{
    int currentX = 0;
    int currentY = 0;

    auto movements = split(path, ",");
    std::vector<std::pair<int, int>> result;
    result.push_back({ 0,0 });
    int distAcum = 0;
    acumDistances.push_back(distAcum);
    for (auto m : movements)
    {
        char dir = m[0];
        string num = m.substr(1);
        int number = atoi(num.c_str());
        distAcum += number;
        acumDistances.push_back(distAcum);

        if (dir == 'U')
        {
            currentY += number;
        }
        if (dir == 'D')
        {
            currentY -= number;
        }
        if (dir == 'L')
        {
            currentX -= number;
        }
        if (dir == 'R')
        {
            currentX += number;
        }

        result.push_back({ currentX, currentY });
    }
    return result;
}

bool day3_checkCollision(std::pair<int, int>& start1, std::pair<int, int>& end1, std::pair<int, int>& start2, std::pair<int, int>& end2, std::pair<int,int>& result )
{
    bool firstHorizontal = start1.second == end1.second;
    bool secondHorizontal = start2.second == end2.second;

    if (firstHorizontal == secondHorizontal) { return false; }//paralell lines

    if (firstHorizontal)
    {
        int minX = min(start1.first, end1.first);
        int maxX = max(start1.first, end1.first);
        int minY = min(start2.second, end2.second);
        int maxY = max(start2.second, end2.second);
        if (minX < start2.first && start2.first < maxX
            &&
            minY < start1.second && start1.second < maxY)
        {
            result = {start2.first, end1.second};
            return true;
        }
    }
    else
    {
        int minX = min(start2.first, end2.first);
        int maxX = max(start2.first, end2.first);
        int minY = min(start1.second, end1.second);
        int maxY = max(start1.second, end1.second);
        if (minX < start1.first && start1.first < maxX
            &&
            minY < start2.second && start2.second < maxY)
        {
            result = { start1.first, end2.second };
            return true;
        }
    }
    return false;
}

void day3()
{
    auto txt = ReadFile("./input/day3.txt");
    std::vector<int> acumDist1;
    std::vector<int> acumDist2;
    auto path1 = day3_getPath(txt[0], acumDist1);
    auto path2 = day3_getPath(txt[1], acumDist2);

    int bestA = -1;
    int bestB = -1;
    std::vector<pair<int, int>> collsisions;
    for (int path1I = 0; path1I < path1.size() - 1; ++path1I)
    {
        for (int path2I = 0; path2I < path2.size() - 1; ++path2I)
        {
            auto start1 = path1[path1I];
            auto end1 = path1[path1I + 1];

            auto start2 = path2[path2I];
            auto end2 = path2[path2I + 1];
           
            std::pair<int, int> collision;
            if (day3_checkCollision(start1, end1, start2, end2, collision))
            {
                int dist = abs(collision.first) + abs(collision.second);
                if (bestA == -1 || dist < bestA)
                {
                    bestA = dist;
                }

                int valueB = acumDist1[path1I] + acumDist2[path2I];
                valueB += (abs(collision.first - start1.first) + abs(collision.second - start1.second));
                valueB += (abs(collision.first - start2.first) + abs(collision.second - start2.second));


                if (bestB == -1 || valueB < bestB)
                {
                    bestB = valueB;
                }
            }
        }
    }

    std::cout << "day3 =>" << bestA << "\n";
    std::cout << "day3_b => " << bestB << "\n";

}

int main()
{
    //day1();
    //day2();
    day3();
}

// Ejecutar programa: Ctrl + F5 o menú Depurar > Iniciar sin depurar
// Depurar programa: F5 o menú Depurar > Iniciar depuración

// Sugerencias para primeros pasos: 1. Use la ventana del Explorador de soluciones para agregar y administrar archivos
//   2. Use la ventana de Team Explorer para conectar con el control de código fuente
//   3. Use la ventana de salida para ver la salida de compilación y otros mensajes
//   4. Use la ventana Lista de errores para ver los errores
//   5. Vaya a Proyecto > Agregar nuevo elemento para crear nuevos archivos de código, o a Proyecto > Agregar elemento existente para agregar archivos de código existentes al proyecto
//   6. En el futuro, para volver a abrir este proyecto, vaya a Archivo > Abrir > Proyecto y seleccione el archivo .sln
