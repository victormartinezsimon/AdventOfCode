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

bool day4_validA(std::vector<int>& digits)
{
    bool someEqual = false;
    int lastDigit = digits[0];
    for (int i = 1; i < digits.size(); ++i)
    {
        int currDigit = digits[i];
        if (currDigit == lastDigit)
        {
            someEqual = true;
        }
        if (currDigit < lastDigit)
        {
            return false;
        }
        lastDigit = currDigit;
    }

    return someEqual;
}

bool day4_validB(std::vector<int>& digits)
{
    int countEqual = 1;
    int lastDigit = digits[0];
    bool somePair = false;
    for (int i = 1; i < digits.size(); ++i)
    {
        int currDigit = digits[i];
        if (currDigit == lastDigit)
        {
            ++countEqual;
        }
        else
        {
            if (countEqual == 2)
            {
                somePair = true;
            }
            countEqual = 1;
        }
        if (currDigit < lastDigit)
        {
            return false;
        }
        lastDigit = currDigit;
    }

    return somePair || countEqual == 2;
}

std::vector<int> day4_getDigits(int value)
{
    std::vector<int> digits;
    while (value != 0)
    {
        int v = value % 10;
        value = value / 10;
        digits.insert(digits.begin(), v);
    }
    return digits;
}

void day4()
{
    int minValue = 128392;
    int maxValue = 643281;

    int acumA = 0;
    int acumB = 0;
    for (int i = minValue; i <= maxValue; ++i)
    {
        auto digits = day4_getDigits(i);
        if (day4_validA(digits))
        {
            ++acumA;
        }
        if (day4_validB(digits))
        {
            ++acumB;
        }
    }
    std::cout << "day4 =>" << acumA << "\n";
    std::cout << "day4 =>" << acumB << "\n";
    
}

namespace day5_intcode
{
    long long getValueOperation(int operation, std::vector<long long> params)
    {
        switch (operation)
        {
        case 1: return params[0] + params[1]; break;
        case 2: return params[0] * params[1]; break;
        case 3: return params[0]; break;
        case 4: return params[0]; break;
        case 5: return params[0] != 0; break;
        case 6: return params[0] == 0; break;
        case 7: return params[0] < params[1]; break;
        case 8: return params[0] == params[1]; break;
        }

        std::cout << "error\n";
        return 0;
    }

    long long getValue(int value, int type, const std::vector<long long>& memory)
    {
        switch(type)
        {
        case 0: return memory[value];
        case 1: return value;
        }
        std::cout << "error \n";
        return 0;
    }

    std::vector<int> parseInstruction(int value, int totalElements)
    {
        std::vector<int> result;

        int instruction = value % 100;
        result.push_back(instruction);
        totalElements -= 2;

        value = value / 100;
        while (totalElements >= 0)
        {
            int val = value % 10;
            result.push_back(val);
            value = value / 10;
            --totalElements;
        }

        return result;
    }

    int getParametersForOperation(int operation)
    {
        switch (operation)
        {
        case 1: 
        case 2: return 3;
        case 3:
        case 4: return 1;
        case 5:
        case 6: return 2;
        case 7:
        case 8: return 3;
        }
        return 0;
    }

    std::vector<long long> getInstrucionInput(std::vector<long long>& memory, int index, int operation, std::vector<int> parameterInfo, std::vector<long long>& input)
    {
        std::vector<long long> result;

        if (operation == 3)
        {
            int value = (input.front());
            input.erase(input.begin());
            result.push_back(value);
            auto value2 = memory[index + 1];
            result.push_back(value2);
            return result;
        }

        int totalParameters = getParametersForOperation(operation);
        for (int i = 0; i < totalParameters -1; ++i)
        {
            auto value = getValue(memory[index + i + 1], parameterInfo[i + 1], memory);
            result.push_back(value);
        }

        //exit
        if (operation == 6 || operation == 5 || operation == 4)
        {
            int i = totalParameters - 1;
            auto value = getValue(memory[index + i + 1], parameterInfo[i + 1], memory);
            result.push_back(value);
        }
        else
        {
            int i = totalParameters - 1;
            auto value2 = memory[index + 1 + i];
            result.push_back(value2);
        }

        return result;
    }

    void writeResult(std::vector<long long>& memory, std::vector<long long>& output, long long result, int index, int operation, std::vector<long long>& parameterInfo)
    {
        if (operation == 5 || operation == 6)
        {
            return;
        }

        if (operation == 4)
        {
            output.push_back(result);
            return;
        }


        int totalParams = getParametersForOperation(operation);
        int indexSave = parameterInfo.back();
        memory[indexSave] = result;
    }

    void updateIndex(std::vector<long long>& memory, std::vector<long long>& parameters, int& index, int operation, int result)
    {
        if (operation == 5 || operation == 6)
        {
            if (result)
            {
                index = parameters[1];
                return;
            }
        }

        int totalParams = getParametersForOperation(operation);
        index += totalParams +1;
    }

    void executeInstruction(std::vector<long long>& memory, std::vector<long long>& input, std::vector<long long>& output, int& index)
    {
        auto parameterInfo = parseInstruction(memory[index], 5);
        int operation = parameterInfo[0];
        int totalParameters = getParametersForOperation(operation);

        auto parameters = getInstrucionInput(memory, index, operation, parameterInfo, input);

        auto result = getValueOperation(operation, parameters);

        writeResult(memory, output, result, index, operation, parameters);

        updateIndex(memory, parameters, index, operation, result);

    }

    void runProgram(std::vector<long long>& memory, std::vector<long long>& input, std::vector<long long>& output)
    {
        int index = 0;

        while (index < memory.size() && memory[index] != 99)
        {
            executeInstruction(memory, input, output, index);
        }
    }

    std::vector<long long> buildMemory(const std::string& txt)
    {
        auto split_value = split(txt, ",");
        std::vector<long long> memory;

        for (auto v : split_value)
        {
            memory.push_back(atoll(v.c_str()));
        }

        return memory;
    }
}

void day5()
{
    auto txt = ReadFile("./input/day5.txt")[0];

    {
        auto memory = day5_intcode::buildMemory(txt);

        std::vector<long long> input = { 1 };
        std::vector<long long> output;
        day5_intcode::runProgram(memory, input, output);

        std::cout << "day 5 => ";
        for (auto c : output)
        {
            if (c != 0)
            {
                std::cout << c;
            }
        }
        std::cout << "\n";
    }

    {
        auto memory = day5_intcode::buildMemory(txt);

        std::vector<long long> input = { 5 };
        std::vector<long long> output;
        day5_intcode::runProgram(memory, input, output);

        std::cout << "day 5_B => ";
        for (auto c : output)
        {
            if (c != 0)
            {
                std::cout << c;
            }
        }
        std::cout << "\n";
    }
}

struct day6_planet
{
    std::string name;
    int orbits = 0;
    day6_planet* parent = nullptr;
};

int day6_calculateOrbits(day6_planet* p)
{
    if (p->orbits != 0)
    {
        return p->orbits;
    }

    if (p->parent == nullptr)
    {
        return 0;
    }

    int result = day6_calculateOrbits(p->parent) + 1;
    p->orbits = result;
    return result;
}

void day6_buildPath(day6_planet* p, std::vector<string>& path)
{
    path.insert(path.begin(), p->name);
    if (p->parent != nullptr)
    {
        day6_buildPath(p->parent, path);
    }
}

void day6()
{
    auto fileTxt = ReadFile("./input/day6.txt");

    std::map<std::string, day6_planet*> planets;

    std::string regexTxt = "(.*)\\)(.*)";
    for (auto&& line : fileTxt)
    {
        std::regex numbersRegex(regexTxt);
        std::smatch sm;

        std::regex_search(line, sm, numbersRegex);
        std::string parent = sm.str(1);
        std::string son = sm.str(2);

        if (planets.find(parent) == planets.end())
        {
            day6_planet* p = new day6_planet();
            p->name = parent;
            planets[parent] = p;
        }

        if (planets.find(son) == planets.end())
        {
            day6_planet* p = new day6_planet();
            p->name = son;
            planets[son] = p;
        }

        planets[son]->parent = planets[parent];
    }

    int valueA = 0;
    for (auto kvp : planets)
    {
        auto planet = kvp.second;

        valueA += day6_calculateOrbits(planet);
    }

    std::cout << "day 6 => " << valueA << "\n";

    std::vector<string> pathYOU;
    std::vector<string> pathSAN;

    day6_buildPath(planets["YOU"], pathYOU);
    day6_buildPath(planets["SAN"], pathSAN);
    
    int minPathSize = min(pathYOU.size(), pathSAN.size());

    int valueB = 0;
    for (int i = 0; i < minPathSize - 1; ++i)
    {
        if (pathYOU[i] != pathSAN[i])
        {
            int toReachYou = pathYOU.size() - i - 1;
            int toReachSan = pathSAN.size() - i - 1;

            valueB = toReachSan + toReachYou;
            break;
        }
    }


    std::cout << "day 6_B => " << valueB << "\n";
}

int main()
{
    //day1();
    //day2();
    //day3();
   // day4();
    //day5();
    day6();
}

// Ejecutar programa: Ctrl + F5 o menú Depurar > Iniciar sin depurar
// Depurar programa: F5 o menú Depurar > Iniciar depuración

// Sugerencias para primeros pasos: 1. Use la ventana del Explorador de soluciones para agregar y administrar archivos
//   2. Use la ventana de Team Explorer para conectar con el control de código fuente
//   3. Use la ventana de salida para ver la salida de compilación y otros mensajes
//   4. Use la ventana Lista de errores para ver los errores
//   5. Vaya a Proyecto > Agregar nuevo elemento para crear nuevos archivos de código, o a Proyecto > Agregar elemento existente para agregar archivos de código existentes al proyecto
//   6. En el futuro, para volver a abrir este proyecto, vaya a Archivo > Abrir > Proyecto y seleccione el archivo .sln
