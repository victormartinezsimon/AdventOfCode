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
#include <array>
#include <queue>
#include <iomanip>
#include <stack>
#include <bitset>
#include <functional>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <cmath>
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

namespace day7_intcode
{
    using inputFunction = function<long long()>;
    using outputFunction = function<void(long long)>;

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
        switch (type)
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

    std::vector<long long> getInstrucionInput(std::vector<long long>& memory, int index, int operation, std::vector<int> parameterInfo, inputFunction& inputFun)
    {
        std::vector<long long> result;

        if (operation == 3)
        {
            /*
            int value = (input.front());
            input.erase(input.begin());
            result.push_back(value);
            auto value2 = memory[index + 1];
            result.push_back(value2);
            return result;
            */
            auto val = inputFun();
            result.push_back(val);

            auto value2 = memory[index + 1];
            result.push_back(value2);
            return result;
        }

        int totalParameters = getParametersForOperation(operation);
        for (int i = 0; i < totalParameters - 1; ++i)
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

    void writeResult(std::vector<long long>& memory, outputFunction& outputFun, long long result, int index, int operation, std::vector<long long>& parameterInfo)
    {
        if (operation == 5 || operation == 6)
        {
            return;
        }

        if (operation == 4)
        {
            outputFun(result);
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
        index += totalParams + 1;
    }
    //
    //1:+
    //2:*
    //3:Read
    //4:Write
    //5:Jmp !=
    //6:Jmp ==
    //7:<
    //8: ==
   
    void runProgram(std::vector<long long>& memory, inputFunction& inputFun, outputFunction& outputFun)
    {
        int index = 0;

        while (index < memory.size() && memory[index] != 99)
        {
            auto parameterInfo = parseInstruction(memory[index], 5);
            int operation = parameterInfo[0];
            int totalParameters = getParametersForOperation(operation);

            auto parameters = getInstrucionInput(memory, index, operation, parameterInfo, inputFun);

            auto result = getValueOperation(operation, parameters);

            writeResult(memory, outputFun, result, index, operation, parameters);

            updateIndex(memory, parameters, index, operation, result);
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

std::vector<std::vector<int>> day7_getCombinations(std::vector<int>& values, std::map<string, std::vector<std::vector<int>>>& cache)
{
    if (values.size() == 1)
    {
        return { {values[0]} };
    }

    std::string key = "";
    for (auto&& v : values)
    {
        key += std::to_string(v)+ ",";
    }

    if (cache.find(key) != cache.end())
    {
        return cache[key];
    }

    std::vector<std::vector<int>> result;
    for (int i = 0; i < values.size(); ++i)
    {
        int value = values[i];
        values.erase(values.begin() + i);
        auto res = day7_getCombinations(values, cache);

        for (auto& r : res)
        {
            r.push_back(value);
            result.push_back(r);
        }

        values.insert(values.begin() + i, value);

    }
    cache[key] = result;

    return result;
}

long long day7_calculateA(std::vector<int>& combination, std::vector<std::vector<long long>>& allAmplifiers, long long startValue)
{
    std::vector<long long> input = { startValue };

    for (int i = 0; i < allAmplifiers.size(); ++i)
    {
        input.insert(input.begin(), combination[i]);
        day7_intcode::inputFunction inptuFun = [&input]()
        {
            long long valueToReturn = input.front();
            input.erase(input.begin());
            return valueToReturn;
        };

        std::vector<long long> output;
        day7_intcode::outputFunction outputFun = [&output](long long val) {output.push_back(val); };
        
        auto& memory = allAmplifiers[i];
        //hay que guardar en que posicion esta la maquina para poder seguir desde ahi
        //eso sera un indice nuevo
        //pararemos cuando la ulitma se pare
        day7_intcode::runProgram(memory, inptuFun, outputFun);

        auto result = output[0];

        input.clear();
        input.push_back(result);
    }

    return input[0];
}

void day7A(std::string& txt)
{
    int totalAmplifiers = 5;

    std::vector<int> possibleValuesLow;
    for (int i = 0; i < totalAmplifiers; ++i)
    {
        possibleValuesLow.push_back(i);
    }
    std::map<string, std::vector<std::vector<int>>> cache;
    auto allCombinationsLow = day7_getCombinations(possibleValuesLow, cache);

    long long bestResultA = -1;

    for (auto&& comb : allCombinationsLow)
    {
        std::vector<std::vector<long long>> allAmplifiers;
        for (int i = 0; i < totalAmplifiers; ++i)
        {
            allAmplifiers.push_back(day5_intcode::buildMemory(txt));
        }

        auto result = day7_calculateA(comb, allAmplifiers, 0);

        if (result > bestResultA)
        {
            bestResultA = result;
        }
    }

    std::cout << "day 7=> " << bestResultA << "\n";
}

void day7B(std::string& txt)
{
    int totalAmplifiers = 5;

    std::vector<int> possibleValues;
    for (int i = 0; i < totalAmplifiers; ++i)
    {
        possibleValues.push_back(i + 5);
    }
    std::map<string, std::vector<std::vector<int>>> cache;
    auto allCombinationsLow = day7_getCombinations(possibleValues, cache);

    long long bestResult = -1;

    for (int combIdx = 0; combIdx < allCombinationsLow.size(); ++combIdx)
    {
        std::cout << combIdx << " of " << allCombinationsLow.size() << "\n";
        auto comb = allCombinationsLow[combIdx];

        //init amplifiers
        std::vector<std::vector<long long>> inputs;
        std::vector<day7_intcode::inputFunction> inputsFuns;
        std::vector<day7_intcode::outputFunction> outputsFuns;
        std::vector<std::vector<long long>> memories;
        std::array < std::condition_variable, 5> conditions;
        std::array<std::mutex, 5> mutexes;//total amplifiers

        //prepare thing
        for (int i = 0; i < totalAmplifiers; ++i)
        {
            day7_intcode::inputFunction inputFun = [i, &inputs, inputsFuns, &conditions, &mutexes]()
            {
                //wait notification
                std::unique_lock<std::mutex> lk(mutexes[i]);

                //if(inputs[i].size() == 0)
                //    std::cout << "Waiting..."+ std::to_string( i) + "\n";

                conditions[i].wait(lk, [&inputs, i] { 
                    return inputs[i].size() != 0; 
                    });
                //std::cout << "Read..." + std::to_string(i) + "\n";

                long long value = inputs[i].front();
                inputs[i].erase(inputs[i].begin());

                return value;
            };

            day7_intcode::outputFunction outputFun = [i, &inputs, totalAmplifiers, &conditions](long long val)
            {
                int next = (i + 1) % totalAmplifiers;
                inputs[next].push_back(val);
                
                //notify 
                //std::cout << "Notify..." + std::to_string(next) + "\n";
                conditions[next].notify_all();
            };

            inputsFuns.push_back(inputFun);
            outputsFuns.push_back(outputFun);

            std::vector<long long> inputThis;
            inputThis.push_back(comb[i]);
            inputs.push_back(inputThis);

            memories.push_back(day7_intcode::buildMemory(txt));

        }

        //initialization
        inputs[0].push_back(0);

        std::vector<thread> threads;
        totalAmplifiers = 5;
        for (int i = 0; i < totalAmplifiers; ++i)
        {
            threads.push_back(std::thread(day7_intcode::runProgram, std::ref(memories[i]), std::ref(inputsFuns[i]),std::ref( outputsFuns[i])));
        }

        for (auto& t : threads)
        {
            t.join();
        }

        if (inputs[0].front() > bestResult)
        {
            bestResult = inputs[0].front();
        }
    }
    std::cout << "day7 b => " << bestResult << "\n";
}

void day7()
{
    auto txt = ReadFile("./input/day7.txt")[0];
    day7A(txt);
    day7B(txt);

}

void day8()
{
    auto txt = ReadFile("./input/day8.txt")[0];
    int width = 25;
    int height = 6;
    int totalSize = width * height;
    int min0 = totalSize;
    int valueA = 0;

    std::vector<std::vector<int>> layers;
    for (int start = 0; start < txt.size(); start += totalSize)
    {
        std::array<int, 3> counts;
        counts.fill(0);
        std::vector<int> layer;
        for (int index = start; index < start + totalSize; ++index)
        {
            char v = txt[index];
            int value = v - '0';

            counts[value]++;
            layer.push_back(value);
        }

        layers.push_back(layer);

        if (counts[0] < min0)
        {
            min0 = counts[0];
            valueA = counts[1] * counts[2];
        }
    }

    std::cout << "day8 => " << valueA << "\n";
    std::cout << "day8 B => \n";


    std::vector<int> finalLayer;
    int countLine = 0;
    for (int i = 0; i < totalSize; ++i)
    {
        int currLayer = 0;
        while (layers[currLayer][i] == 2)
        {
            ++currLayer;
        }

        int value = layers[currLayer][i];
        if (value == 0)
        {
            std::cout << ".";
        }
        else
        {
            std::cout << "#";
        }
        ++countLine;
        if (countLine == width)
        {
            std::cout << "\n";
            countLine = 0;
        }
        finalLayer.push_back(layers[currLayer][i]);
    }


}

class day9_intcode
{
public:
    using memoryType = unsigned long long;
    using inputFunction = function<memoryType()>;
    using outputFunction = function<void(memoryType)>;
    
private:
    int instructionIndex = 0;
    memoryType relativeBase = 0;
    inputFunction inputFun;
    outputFunction outputFun;
    std::map<int, memoryType> memory;

    memoryType calculateInstruction(int operation, std::vector<memoryType> params)
    {
        switch (operation)
        {
        case 1: return params[0] + params[1]; break;
        case 2: return params[0] * params[1]; break;
        case 3: return -1; break;
        case 4: return -1; break;
        case 5: return params[0] != 0; break;
        case 6: return params[0] == 0; break;
        case 7: return params[0] < params[1]; break;
        case 8: return params[0] == params[1]; break;
        case 9: return -1; break;
        }

        std::cout << "error\n";
        return 0;
    }

    memoryType getValue(int value, int type)
    {
        switch (type)
        {
        case 0: return memory[value];
        case 1: return value;
        case 2: return memory[value + relativeBase];
        }
        std::cout << "error \n";
        return 0;
    }

    std::vector<int> parseParamsInfo(int value, int totalElements)
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
        case 9: return 1;
        }
        return 0;
    }

    std::vector<memoryType> readParametersFromInstruction( int operation)
    {
        int totalParams = getParametersForOperation(operation);
        std::vector<memoryType> result;
        for (int i = 0; i < totalParams; ++i)
        {
            auto value = memory[instructionIndex + i + 1];
            result.push_back(value);
        }
        return result;
    }
    std::vector<memoryType> transformParameters(int operation, const std::vector<memoryType>& params, const std::vector<int>& parameterInfo)
    {
        std::vector<memoryType> result;
        for (int i = 0; i < params.size(); ++i)
        {
            auto value = getValue(params[i], parameterInfo[i]);
            result.push_back(value);
        }

        //direct result
        std::set<int> directResult = {1, 2, 3, 7, 8};
        if (directResult.find(operation) != directResult.end())
        {
            if (parameterInfo[result.size() -1] == 2)
            {
                result[result.size() - 1] = params.back() + relativeBase;
            }
            else
            {
                result[result.size() - 1] = params.back();
            }
        }

        return result;
    }

    void writeResult(memoryType result, int operation, std::vector<memoryType>& paramsTransformed)
    {
        if (operation == 5 || operation == 6)
        {
            return;
        }

        if (operation == 4)
        {
            outputFun(paramsTransformed[0]);
            return;
        }
        if (operation == 9)
        {
            relativeBase += paramsTransformed[0];
            return;
        }

        if (operation == 3)
        {
            result = inputFun();
        }

        int indexSave = paramsTransformed.back();
        memory[indexSave] = result;
    }

    void updateIndex( std::vector<memoryType>& paramsTransformed, int operation, int result)
    {
        if (operation == 5 || operation == 6)
        {
            if (result)
            {
                instructionIndex = paramsTransformed[1];
                return;
            }
        }

        int totalParams = getParametersForOperation(operation);
        instructionIndex += totalParams + 1;
    }
    //
    //1:+
    //2:*
    //3:Read
    //4:Write
    //5:Jmp !=
    //6:Jmp ==
    //7:<
    //8: ==
    //9: +RelativeBase
    void runProgram()
    {
        while ( memory[instructionIndex] != 99)
        {

            int tmp_63 = memory[63];
            int tmp_1000 = memory[1000];


            auto instruction = memory[instructionIndex];
            auto paramsInfo = parseParamsInfo(memory[instructionIndex], 5);
            int operation = paramsInfo[0];
            paramsInfo.erase(paramsInfo.begin());
            auto paramsForInstruction = readParametersFromInstruction( operation);
            auto paramsTransformed = transformParameters(operation, paramsForInstruction, paramsInfo);

            auto result = calculateInstruction(operation, paramsTransformed);

            writeResult( result, operation, paramsTransformed);
            updateIndex( paramsTransformed, operation, result);
        }
    }

    std::map<int, memoryType> buildMemory(const std::string& txt)
    {
        auto split_value = split(txt, ",");
        std::map<int, memoryType> memory;

        int index = 0;
        for (auto v : split_value)
        {
            memory[index] = stoull(v.c_str());
            ++index;
        }

        return memory;
    }

public:

    void Init(const std::string& txt, inputFunction input, outputFunction output )
    {
        inputFun = input;
        outputFun = output;
        memory = buildMemory(txt);
        instructionIndex = 0;
        relativeBase = 0;
    }

    void Run()
    {
        runProgram();
    }
};

void day9()
{
    auto txt = ReadFile("./input/day9.txt")[0];
    day9_intcode programA;
    programA.Init(txt, 
    []() 
        {
            return 1; 
        }, 
    [](day9_intcode::memoryType v)
        {
            std::cout << v <<","; 
        });
    std::cout << "day 9 => ";
    programA.Run();
    std::cout << "\n";

    day9_intcode programB;
    programB.Init(txt,
        []()
        {
            return 2;
        },
        [](day9_intcode::memoryType v)
        {
            std::cout << v << ",";
        });
    std::cout << "day 9_B => ";
    programB.Run();
    std::cout << "\n";

}

bool day10_clearPath(const std::vector<string>& board, int width, int height, const std::pair<int,int>& origin, const std::pair<int,int>& dest)
{
    int diffRow = dest.first - origin.first;
    int diffCol = dest.second - origin.second;

    int diffRowAbs = abs(diffRow);
    int diffColAbs = abs(diffCol);

    int diffGCD = std::gcd(diffRowAbs, diffColAbs);

    int tendencyRow = diffRow / diffGCD;
    int tendencyCol = diffCol / diffGCD;

    std::pair<int, int> currentPosition = { origin.first + tendencyRow, origin.second + tendencyCol };;

    while (currentPosition != dest)
    {
        if (board[currentPosition.first][currentPosition.second] == '#')
        {
            return false;
        }

        currentPosition = { currentPosition.first + tendencyRow, currentPosition.second + tendencyCol };
    }

    return true;
}

int day10_A(const std::vector<string>& board, int width, int height, const std::vector<std::pair<int, int>>& asteroids, std::pair<int, int>& bestCoords)
{
    std::vector<std::vector<int>> counts(height, std::vector<int>(width, 0));

    for (int asteroid1 = 0; asteroid1 < asteroids.size(); ++asteroid1)
    {
        for (int asteroid2 = asteroid1 +1; asteroid2 < asteroids.size(); ++asteroid2)
        {
            auto ast1 = asteroids[asteroid1];
            auto ast2 = asteroids[asteroid2];
            bool clearPath = day10_clearPath(board, width, height, ast1, ast2);
            if (clearPath)
            {
                counts[ast1.first][ast1.second]++;
                counts[ast2.first][ast2.second]++;
            }
        }
    }


    int maxValue = 0;

    for (int row = 0; row < height; ++row)
    {
        for (int col = 0; col < width; ++col)
        {
            if (counts[row][col] > maxValue)
            {
                maxValue = counts[row][col];
                bestCoords = { row, col };
            }
        }
    }

    return maxValue;
}

std::vector<std::pair<int, int>> day10_getVisibleAsteroids(const std::vector<string>& board, int width, int height, std::pair<int, int>& laserOrigin)
{
    std::vector<std::pair<int, int>> result;

    for (int row = 0; row < height; ++row)
    {
        for (int col = 0; col < width; ++col)
        {
            if (row == laserOrigin.first && col == laserOrigin.second)
            {
                continue;
            }
            if (board[row][col] == '#')
            {
                std::pair<int, int> asteroid = { row, col };
                if (day10_clearPath(board, width, height, laserOrigin, asteroid))
                {
                    result.push_back({ row, col });
                }
            }
        }
    }

    return result;
}

struct day10_bAngles
{
    std::pair<int, int> position;
    double angles;
};

void day10_B(std::vector<string> board, int width, int height, std::pair<int,int> laserOrigin)
{
    //Y  X
    auto v0 = atan2(-5, 0);         v0 -= 3* PI / 2; while (v0 < 0) { v0 += 2*PI; }
    auto v1 = atan2(-3, 3);         v1 -= 3* PI / 2; while (v1 < 0) { v1 += 2*PI; }
    auto v2 = atan2( 0,5);          v2 -= 3* PI / 2; while (v2 < 0) { v2 += 2*PI; }
    auto v3 = atan2( 3,3);          v3 -= 3* PI / 2; while (v3 < 0) { v3 += 2*PI; }
    auto v4 = atan2( 5,0);          v4 -= 3* PI / 2; while (v4 < 0) { v4 += 2*PI; }
    auto v5 = atan2(3, -3);         v5 -= 3* PI / 2; while (v5 < 0) { v5 += 2*PI; }
    auto v6 = atan2( 0,-5);         v6 -= 3* PI / 2; while (v6 < 0) { v6 += 2*PI; }
    auto v7 = atan2( -3,-3);        v7 -= 3* PI / 2; while (v7 < 0) { v7 += 2*PI; }


    int count = 0;
    int max = 200;
    while (count < max)
    {
        auto visibles = day10_getVisibleAsteroids(board, width, height, laserOrigin);

        if (count + visibles.size() < max)
        {
            //remove them
            for (auto&& asteroid : visibles)
            {
                board[asteroid.first][asteroid.second] = 'D';
            }
        }
        else
        {
            std::vector<day10_bAngles> asteroidsToInvestigate;
            for (auto&& ast : visibles)
            {
                day10_bAngles data;
                data.position = ast;

                int diffY = ast.first - laserOrigin.first;
                int diffX = ast.second - laserOrigin.second;

                auto angles = atan2(diffY, diffX);
                angles -= 3 * PI / 2;
                while (angles < 0)
                {
                    angles += 2 * PI;
                }
                data.angles = angles;

                asteroidsToInvestigate.push_back(data);
            }

            std::sort(asteroidsToInvestigate.begin(), asteroidsToInvestigate.end(), [](const day10_bAngles& a, const day10_bAngles& b) {return a.angles < b.angles; });

            int index = max - count -1;
            auto lastOne = asteroidsToInvestigate[index];
            int valueB = lastOne.position.first + lastOne.position.second * 100;
            std::cout << "day 10_B => " << valueB << "\n";
        }

        count += visibles.size();
    }
    
}

void day10()
{
    auto board = ReadFile("./input/day10.txt");

    int width = board[0].size();
    int height = board.size();
    std::vector<std::pair<int, int>> asteroids;

    for (int row = 0; row < height; ++row)
    {
        for (int col = 0; col < width; ++col)
        {
            if (board[row][col] == '#')
            {
                asteroids.push_back({ row, col });
            }
        }
    }

    std::pair<int, int> bestCoordsA;
    int valueA = day10_A(board, width, height, asteroids, bestCoordsA);
    std::cout << "day 10 => " << valueA << "\n";


    day10_B(board, width, height, bestCoordsA);
}

class day11_intcode
{
public:
    using memoryType = long long;
    using inputFunction = function<memoryType()>;
    using outputFunction = function<void(memoryType)>;

private:
    int instructionIndex = 0;
    memoryType relativeBase = 0;
    inputFunction inputFun;
    outputFunction outputFun;
    std::map<memoryType, memoryType> memory;

    memoryType calculateInstruction(int operation, std::vector<memoryType> params)
    {
        switch (operation)
        {
        case 1: return params[0] + params[1]; break;
        case 2: return params[0] * params[1]; break;
        case 3: return -1; break;
        case 4: return -1; break;
        case 5: return params[0] != 0; break;
        case 6: return params[0] == 0; break;
        case 7: return params[0] < params[1]; break;
        case 8: return params[0] == params[1]; break;
        case 9: return -1; break;
        }

        std::cout << "error\n";
        return 0;
    }

    memoryType getValue(memoryType value, int type)
    {
        switch (type)
        {
        case 0: return memory[value];
        case 1: return value;
        case 2: 
            if (memory.find(value + relativeBase) == memory.end()) {
                memory[value + relativeBase] = 0;
            }
            return memory[value + relativeBase];
        }
        std::cout << "error \n";
        return 0;
    }

    std::vector<int> parseParamsInfo(int value, int totalElements)
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
        case 9: return 1;
        }
        return 0;
    }

    std::vector<memoryType> readParametersFromInstruction(int operation)
    {
        int totalParams = getParametersForOperation(operation);
        std::vector<memoryType> result;
        for (int i = 0; i < totalParams; ++i)
        {
            auto value = memory[instructionIndex + i + 1];
            result.push_back(value);
        }
        return result;
    }
    std::vector<memoryType> transformParameters(int operation, const std::vector<memoryType>& params, const std::vector<int>& parameterInfo)
    {
        std::vector<memoryType> result;
        for (int i = 0; i < params.size(); ++i)
        {
            auto value = getValue(params[i], parameterInfo[i]);
            result.push_back(value);
        }

        //direct result
        std::set<int> directResult = { 1, 2, 3, 7, 8 };
        if (directResult.find(operation) != directResult.end())
        {
            if (parameterInfo[result.size() - 1] == 2)
            {
                result[result.size() - 1] = params.back() + relativeBase;
            }
            else
            {
                result[result.size() - 1] = params.back();
            }
        }

        return result;
    }

    void writeResult(memoryType result, int operation, std::vector<memoryType>& paramsTransformed)
    {
        if (operation == 5 || operation == 6)
        {
            return;
        }

        if (operation == 4)
        {
            outputFun(paramsTransformed[0]);
            return;
        }
        if (operation == 9)
        {
            relativeBase += paramsTransformed[0];
            return;
        }

        if (operation == 3)
        {
            result = inputFun();
        }

        int indexSave = paramsTransformed.back();
        memory[indexSave] = result;
    }

    void updateIndex(std::vector<memoryType>& paramsTransformed, int operation, int result)
    {
        if (operation == 5 || operation == 6)
        {
            if (result)
            {
                instructionIndex = paramsTransformed[1];
                return;
            }
        }

        int totalParams = getParametersForOperation(operation);
        instructionIndex += totalParams + 1;
    }
    //
    //1:+
    //2:*
    //3:Read
    //4:Write
    //5:Jmp !=
    //6:Jmp ==
    //7:<
    //8: ==
    //9: +RelativeBase
    void runProgram()
    {
        while (memory[instructionIndex] != 99)
        {
            runOneInstruction();
        }
    }

    void runOneInstruction()
    {
        auto instruction = memory[instructionIndex];
        auto paramsInfo = parseParamsInfo(memory[instructionIndex], 5);
        int operation = paramsInfo[0];
        paramsInfo.erase(paramsInfo.begin());
        auto paramsForInstruction = readParametersFromInstruction(operation);
        auto paramsTransformed = transformParameters(operation, paramsForInstruction, paramsInfo);

        auto result = calculateInstruction(operation, paramsTransformed);

        writeResult(result, operation, paramsTransformed);
        updateIndex(paramsTransformed, operation, result);
    }

    std::map<memoryType, memoryType> buildMemory(const std::string& txt)
    {
        auto split_value = split(txt, ",");
        std::map<memoryType, memoryType> memory;

        int index = 0;
        for (auto v : split_value)
        {
            memory[index] = stoll(v.c_str());
            ++index;
        }

        return memory;
    }

public:

    void Init(const std::string& txt, inputFunction input, outputFunction output)
    {
        inputFun = input;
        outputFun = output;
        memory = buildMemory(txt);
        instructionIndex = 0;
        relativeBase = 0;
    }

    void Run()
    {
        runProgram();
    }

    void RunDebug()
    {
        runOneInstruction();
    }

    std::vector<int> GetMemoryIndexes()
    {
        std::vector<int> toReturn;
        for (auto kvp : memory)
        {
            toReturn.push_back(kvp.first);
        }
        return toReturn;
    }

    memoryType GetValueInMemoryPosition(int index)
    {
        return memory[index];
    }
};

void day11_A(std::string& code)
{
    day11_intcode programA;

    using LL = day11_intcode::memoryType;

    std::pair<LL, LL> robotPosition = { 50,50 };
    Directions currentDir = Directions::NORTH;

    std::set<std::pair<LL, LL>> positionsPainted;
    std::map<std::pair<LL, LL>, int> colorInPosition;
    bool outputIsDirection = false;

    day11_intcode::inputFunction input = [&robotPosition, &colorInPosition]()
    {
        if (colorInPosition.find(robotPosition) == colorInPosition.end())
        {
            return 0;//black;
        }

        return colorInPosition[robotPosition];

    };
    day11_intcode::outputFunction output = [&robotPosition, &currentDir, &positionsPainted, &colorInPosition, &outputIsDirection](day11_intcode::memoryType value)
    {
        if (outputIsDirection)
        {
            //0 => turn -90
            //1 => turn 90
            if (value == 0)
            {
                currentDir = turnMinus90Degress(currentDir);
            }

            if (value == 1)
            {
                currentDir = turn90Degress(currentDir);
            }

            robotPosition = getNextPosition(robotPosition, currentDir);
        }
        else
        {
            //0 => paint black
            //1 => paint white
            colorInPosition[robotPosition] = value;
            positionsPainted.insert(robotPosition);
        }

        outputIsDirection = !outputIsDirection;

    };

    programA.Init(code, input, output);
    programA.Run();

    std::cout << "day 11 =>" << positionsPainted.size() << "\n";
}

void day11_print(std::map<std::pair<day11_intcode::memoryType, day11_intcode::memoryType>, int>& colorInPosition)
{
    int minX = 1000;
    int minY = 1000;
    int maxX = -1;
    int maxY = -1;

    for (auto&& kvp : colorInPosition)
    {
        auto position = kvp.first;

        if (position.first < minY) { minY = position.first; }
        if (position.first > maxY) { maxY = position.first; }

        if (position.second < minX) { minX = position.second; }
        if (position.second > maxX) { maxX = position.second; }
    }

    for (int row = minY; row <= maxY; ++row)
    {
        for (int col = minX; col <= maxX; ++col)
        {
            std::pair<int, int> pos = { row, col };

            if (colorInPosition.find(pos) != colorInPosition.end())
            {
                if (colorInPosition[pos] == 1)
                {
                    std::cout << "#";
                }
                else
                {
                    std::cout << ".";
                }
            }
            else
            {
                std::cout << ".";
            }
        }
        std::cout << "\n";
    }

    std::cout << "\n";
}

void day11_B(std::string& code)
{
    day11_intcode programB;

    std::pair<day11_intcode::memoryType, day11_intcode::memoryType> robotPosition = { 100,100 };
    Directions currentDir = Directions::NORTH;

    std::map<std::pair<day11_intcode::memoryType, day11_intcode::memoryType>, int> colorInPosition;
    colorInPosition[robotPosition] = 1;
    bool outputIsDirection = false;

    day11_intcode::inputFunction input = [&robotPosition, &colorInPosition]()
    {
        int toReturn = 0;
        if (colorInPosition.find(robotPosition)  != colorInPosition.end())
        {
            toReturn = colorInPosition[robotPosition];
        }
        return toReturn;

    };
    day11_intcode::outputFunction output = [&robotPosition, &currentDir, &colorInPosition, &outputIsDirection](day11_intcode::memoryType value)
    {
        if (outputIsDirection)
        {
            //0 => turn -90
            //1 => turn 90
            if (value == 0)
            {
                currentDir = turnMinus90Degress(currentDir);
            }

            if (value == 1)
            {
                currentDir = turn90Degress(currentDir);
            }

            robotPosition = getNextPosition(robotPosition, currentDir);
        }
        else
        {
            //0 => paint black
            //1 => paint white
            colorInPosition[robotPosition] = value;
        }

        outputIsDirection = !outputIsDirection;

    };

    programB.Init(code, input, output);
    programB.Run();

    day11_print(colorInPosition);
}

void day11()
{
    auto code = ReadFile("./input/day11.txt")[0];

    day11_A(code);
    day11_B(code);

}

struct day12_moon
{
public:
    std::array<int, 3> position;
    std::array<int, 3> velocity;

    void build(const std::string& str)
    {
        //<x=9, y=-8, z=-3>
        std::string regexTxt = "<x=(.*), y=(.*), z=(.*)";
        std::regex numbersRegex(regexTxt);
        std::smatch sm;
        std::regex_search(str, sm, numbersRegex);

        for (int i = 0; i < position.size(); ++i)
        {
            position[i] = atoi(sm.str(i + 1).c_str());
        }
        
        velocity.fill(0);
    }
};

void day12_runStep(std::vector< day12_moon>& moons, int indexPos)
{
    //update gravity
    for (int moon1 = 0; moon1 < moons.size(); ++moon1)
    {
        for (int moon2 = moon1 + 1; moon2 < moons.size(); ++moon2)
        {
            if (moons[moon1].position[indexPos] < moons[moon2].position[indexPos])
            {
                moons[moon1].velocity[indexPos]++;
                moons[moon2].velocity[indexPos]--;
            }

            if (moons[moon1].position[indexPos] > moons[moon2].position[indexPos])
            {
                moons[moon1].velocity[indexPos]--;
                moons[moon2].velocity[indexPos]++;
            }
        }
    }
    
    //update position
    for (auto& moon : moons)
    {
        moon.position[indexPos] += moon.velocity[indexPos];
    }
}

void day12_runStep(std::vector< day12_moon>& moons)
{
    day12_runStep(moons, 0);
    day12_runStep(moons, 1);
    day12_runStep(moons,2);
}

void day12_A(std::vector< day12_moon> moons)
{
    int totalSteps = 1000;
    for (int i = 0; i < totalSteps; ++i)
    {
        day12_runStep(moons);
    }

    long long resultA = 0;

    for (auto&& moon : moons)
    {
        long long vels = abs(moon.velocity[0]) + abs(moon.velocity[1]) + abs(moon.velocity[2]);
        long long pos = abs(moon.position[0]) + abs(moon.position[1]) + abs(moon.position[2]);

        resultA += vels * pos;
    }

    std::cout << "day12 => " << resultA << "\n";
}

bool day12_checkVelocityZero(const day12_moon& m, std::array<int, 3>& originalPosition, int index)
{
    bool checkVel = m.velocity[index] == 0 ;
    bool checkPos = m.position[index] == originalPosition[index];

    return checkVel && checkPos;
}

void day12_B(std::vector< day12_moon> moons)
{
    std::vector<std::array<int, 3>> originalPos;
    for (int i = 0; i < moons.size(); ++i)
    {
        originalPos.push_back(moons[i].position);
    }

    std::array<long long, 3> resultPerAxis;

    for (int axis = 0; axis < 3; ++axis)
    {
        bool stop = false;
        unsigned long long count = 0;

        while (!stop)
        {
            day12_runStep(moons, axis);
            ++count;

            stop = true;
            for (int i = 0; i < moons.size(); ++i)
            {
                auto val = day12_checkVelocityZero(moons[i], originalPos[i], axis);
                stop &= val;
            }
        }
        resultPerAxis[axis] = count;
    }

    unsigned long long res1 = std::lcm(resultPerAxis[0], resultPerAxis[1]);
    unsigned long long res2 = std::lcm(resultPerAxis[2],res1);

    std::cout << "day 12_B => " << res2 << "\n";

}

void day12()
{
    auto fileTxt = ReadFile("./input/day12.txt");

    std::vector< day12_moon> moons;

    for (auto l : fileTxt)
    {
        day12_moon moon;
        moon.build(l);
        moons.push_back(moon);
    }

    day12_A(moons);
    day12_B(moons);
}

class day13_intcode
{
public:
    using memoryType = long long;
    using inputFunction = function<memoryType()>;
    using outputFunction = function<void(memoryType)>;

private:
    int instructionIndex = 0;
    memoryType relativeBase = 0;
    inputFunction inputFun;
    outputFunction outputFun;
    std::map<memoryType, memoryType> memory;

    memoryType calculateInstruction(int operation, std::vector<memoryType> params)
    {
        switch (operation)
        {
        case 1: return params[0] + params[1]; break;
        case 2: return params[0] * params[1]; break;
        case 3: return -1; break;
        case 4: return -1; break;
        case 5: return params[0] != 0; break;
        case 6: return params[0] == 0; break;
        case 7: return params[0] < params[1]; break;
        case 8: return params[0] == params[1]; break;
        case 9: return -1; break;
        }

        std::cout << "error\n";
        return 0;
    }

    memoryType getValue(memoryType value, int type)
    {
        switch (type)
        {
        case 0: return memory[value];
        case 1: return value;
        case 2:
            if (memory.find(value + relativeBase) == memory.end()) {
                memory[value + relativeBase] = 0;
            }
            return memory[value + relativeBase];
        }
        std::cout << "error \n";
        return 0;
    }

    std::vector<int> parseParamsInfo(int value, int totalElements)
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
        case 9: return 1;
        }
        return 0;
    }

    std::vector<memoryType> readParametersFromInstruction(int operation)
    {
        int totalParams = getParametersForOperation(operation);
        std::vector<memoryType> result;
        for (int i = 0; i < totalParams; ++i)
        {
            auto value = memory[instructionIndex + i + 1];
            result.push_back(value);
        }
        return result;
    }
    std::vector<memoryType> transformParameters(int operation, const std::vector<memoryType>& params, const std::vector<int>& parameterInfo)
    {
        std::vector<memoryType> result;
        for (int i = 0; i < params.size(); ++i)
        {
            auto value = getValue(params[i], parameterInfo[i]);
            result.push_back(value);
        }

        //direct result
        std::set<int> directResult = { 1, 2, 3, 7, 8 };
        if (directResult.find(operation) != directResult.end())
        {
            if (parameterInfo[result.size() - 1] == 2)
            {
                result[result.size() - 1] = params.back() + relativeBase;
            }
            else
            {
                result[result.size() - 1] = params.back();
            }
        }

        return result;
    }

    void writeResult(memoryType result, int operation, std::vector<memoryType>& paramsTransformed)
    {
        if (operation == 5 || operation == 6)
        {
            return;
        }

        if (operation == 4)
        {
            outputFun(paramsTransformed[0]);
            return;
        }
        if (operation == 9)
        {
            relativeBase += paramsTransformed[0];
            return;
        }

        if (operation == 3)
        {
            result = inputFun();
        }

        int indexSave = paramsTransformed.back();
        memory[indexSave] = result;
    }

    void updateIndex(std::vector<memoryType>& paramsTransformed, int operation, int result)
    {
        if (operation == 5 || operation == 6)
        {
            if (result)
            {
                instructionIndex = paramsTransformed[1];
                return;
            }
        }

        int totalParams = getParametersForOperation(operation);
        instructionIndex += totalParams + 1;
    }
    //
    //1:+
    //2:*
    //3:Read
    //4:Write
    //5:Jmp !=
    //6:Jmp ==
    //7:<
    //8: ==
    //9: +RelativeBase
    void runProgram()
    {
        while (memory[instructionIndex] != 99)
        {
            runOneInstruction();
        }
    }

    void runOneInstruction()
    {
        auto instruction = memory[instructionIndex];
        auto paramsInfo = parseParamsInfo(memory[instructionIndex], 5);
        int operation = paramsInfo[0];
        paramsInfo.erase(paramsInfo.begin());
        auto paramsForInstruction = readParametersFromInstruction(operation);
        auto paramsTransformed = transformParameters(operation, paramsForInstruction, paramsInfo);

        auto result = calculateInstruction(operation, paramsTransformed);

        writeResult(result, operation, paramsTransformed);
        updateIndex(paramsTransformed, operation, result);
    }

    std::map<memoryType, memoryType> buildMemory(const std::string& txt)
    {
        auto split_value = split(txt, ",");
        std::map<memoryType, memoryType> memory;

        int index = 0;
        for (auto v : split_value)
        {
            memory[index] = stoll(v.c_str());
            ++index;
        }

        return memory;
    }

public:

    void Init(const std::string& txt, inputFunction input, outputFunction output)
    {
        inputFun = input;
        outputFun = output;
        memory = buildMemory(txt);
        instructionIndex = 0;
        relativeBase = 0;
    }

    void Run()
    {
        runProgram();
    }

    void RunDebug()
    {
        runOneInstruction();
    }

    std::vector<int> GetMemoryIndexes()
    {
        std::vector<int> toReturn;
        for (auto kvp : memory)
        {
            toReturn.push_back(kvp.first);
        }
        return toReturn;
    }

    memoryType GetValueInMemoryPosition(int index)
    {
        return memory[index];
    }

    void SetMemoryValue(memoryType value, memoryType index)
    {
        memory[index] = value;
    }
};

void day13_printBoard(const std::vector<std::vector<int>>& board, int maxX, int maxY)
{
    for (int y = 0; y <= maxY; ++y)
    {
        for (int x = 0; x <= maxX; ++x)
        {
            auto value = board[y][x];

            switch (value)
            {
            case 0: std::cout << " "; break;//emtpy
            case 1: std::cout << "#"; break;//wall
            case 2: std::cout << "+"; break;//block
            case 3: std::cout << "~"; break;//horizontal pale
            case 4: std::cout << "0"; break;//ball
            }
        }
        std::cout << "\n";
    }
}

void day13_A(std::string& code, int& maxX, int& maxY)
{
    day13_intcode programA;

    int boardSize = 100;
    std::vector<std::vector<int>> board(boardSize, std::vector<int>(boardSize, -1));

    std::vector<int> parameteresOutput;

    day11_intcode::inputFunction input = [] {return 0;};
    day11_intcode::outputFunction output = [&board, &parameteresOutput, &maxX, &maxY](day11_intcode::memoryType value)
    {
        parameteresOutput.push_back(value);
        if (parameteresOutput.size() == 3)
        {
            int X = parameteresOutput[0];
            int Y = parameteresOutput[1];
            int titleID = parameteresOutput[2];

            board[Y][X] = titleID;
            parameteresOutput.clear();

            if (X > maxX) { maxX = X; }
            if (Y > maxY) { maxY = Y; }
        }
    };

    programA.Init(code, input, output);
    programA.Run();

    int countBlocks = 0;

    for (int y = 0; y < boardSize; ++y)
    {
        for(int x = 0; x < boardSize; ++x)
        {
            if (board[y][x] == 2)
            {
                ++countBlocks;
            }
        }
    }
    std::cout << "day 13 =>" << countBlocks << "\n";

    day13_printBoard(board, maxX, maxY);
}

void day13_B(const std::string& code, int maxX, int maxY, bool paint)
{
    day13_intcode programB;

    std::vector<std::vector<int>> board(maxY + 1, std::vector<int>(maxX + 1, -1));
    day13_intcode::memoryType score;

    std::pair<int, int> ballPosition;
    std::pair<int, int> paddlePosition;

    day13_intcode::inputFunction input = [&board, maxX, maxY, &score, &ballPosition, &paddlePosition, paint] {
    
        if (paint)
        {
            system("cls");
            std::cout << score << "\n";
            day13_printBoard(board, maxX, maxY);
            std::this_thread::sleep_for(16ms);
        }

        int diffX = ballPosition.first - paddlePosition.first;

        if (diffX < 0) { return -1; }
        if (diffX == 0) { return 0; }
        if (diffX > 0) { return 1; }

        return 0;
    };

    std::vector<day13_intcode::memoryType> parameteresOutput;
    int bestScore = -1;
    day13_intcode::outputFunction output = [&board, &parameteresOutput, &score, &paddlePosition, &ballPosition, &bestScore](day13_intcode::memoryType value)
    {
        parameteresOutput.push_back(value);
        if (parameteresOutput.size() == 3)
        {
            auto X = parameteresOutput[0];
            auto Y = parameteresOutput[1];
            auto titleID = parameteresOutput[2];

            if (X == -1 && Y == 0)
            {
                score = titleID;
                if (score > bestScore)
                {
                    bestScore = score;
                }
            }
            else
            {
                board[Y][X] = titleID;
                if (titleID == 3)
                {
                    paddlePosition = { X,Y };
                }
                if (titleID == 4)
                {
                    ballPosition = { X,Y };
                }
            }


            parameteresOutput.clear();
        }
    };

    programB.Init(code, input, output);

    programB.SetMemoryValue(2, 0);

    programB.Run();

    std::cout << "day13_B =>" << bestScore << "\n";
}


void day13()
{
    auto code = ReadFile("./input/day13.txt")[0];
    
    int maxX = -1;
    int maxY = -1;
    day13_A(code, maxX, maxY);
    day13_B(code, maxX, maxY, false);
}

struct day14_chem
{
    string result;
    int totalResult;
    std::vector<pair<string, int>> needed;
};

long long day14_getORE(const std::map<string, day14_chem>& allChems, long long howMuch, const std::string& elemID, std::map<string, long long>& leftOvers)
{
    long long currentLeft = leftOvers[elemID];

    if (currentLeft >= howMuch)
    {
        leftOvers[elemID] -= howMuch;
        return 0;
    }

    howMuch -= currentLeft;
    leftOvers[elemID] -= currentLeft;

    if (elemID == "ORE")
    {
        return howMuch;
    }

    auto&& chem = allChems.at(elemID);

    long long currentAmount = 0;

    long long totalTimes = ceil(static_cast<float>(howMuch) / static_cast<float>(chem.totalResult));
    for (auto&& source : chem.needed)
    {
        string id = source.first;
        long long total = source.second;
        long long realTotal = total*totalTimes;
        auto res = day14_getORE(allChems, realTotal, id, leftOvers);
        currentAmount += res;
    }

    leftOvers[elemID] += (chem.totalResult*totalTimes - howMuch);

    return currentAmount;
}

bool day14_getFuel(const std::map<string, day14_chem>& allChems, long long howMuch, const std::string& elemID, std::map<string, long long>& leftOvers)
{
    long long currentLeft = leftOvers[elemID];

    if (currentLeft >= howMuch)
    {
        leftOvers[elemID] -= howMuch;
        return true;
    }

    howMuch -= currentLeft;
    leftOvers[elemID] -= currentLeft;

    if (elemID == "ORE")
    {
        return howMuch < 0;
    }

    auto&& chem = allChems.at(elemID);

    long long totalTimes = ceil(static_cast<float>(howMuch) / static_cast<float>(chem.totalResult));
    for (auto&& source : chem.needed)
    {
        string id = source.first;
        long long total = source.second;
        long long realTotal = total * totalTimes;
        bool valid = day14_getFuel(allChems, realTotal, id, leftOvers);

        if (!valid)
        {
            return false;
        }
    }

    leftOvers[elemID] += (chem.totalResult * totalTimes - howMuch);

    return true;
}

void day14_RestoreORE(std::map<string, day14_chem>& allChems, long long howMuch, const std::string& elemID, std::map<string, long long>& leftOvers)
{
    if (howMuch == 0) 
    { 
        return; 
    }

    if (elemID == "ORE")
    {
        //leftOvers["ORE"] += howMuch;
        return;
    }

    auto&& chem = allChems.at(elemID);
    long long totalToTransform = howMuch / chem.totalResult;
    leftOvers[elemID] -= (totalToTransform * chem.totalResult);

    for (auto&& source : chem.needed)
    {
        string id = source.first;
        long long total = source.second;
        leftOvers[id] += total * totalToTransform;

        day14_RestoreORE(allChems, leftOvers[id], id, leftOvers);
    }

}

void day14_restoreAllORE(std::map<string, day14_chem>& allChems, std::map<string, long long>& leftOvers)
{
    for (auto& kvp : leftOvers)
    {
        if (kvp.first == "ORE")
        {
            continue;
        }
        day14_RestoreORE(allChems, kvp.second, kvp.first, leftOvers);
    }
}


void day14_B(std::map<string, day14_chem>& allChems, int resultA, std::map<string, long long>& leftOvers)
{
    long long totalORE = 1'000'000'000'000;
    long long fuelGenerated = totalORE / resultA;
    long long leftORE = totalORE - (resultA * fuelGenerated);

    for (auto& kvp : leftOvers)
    {
        kvp.second *= fuelGenerated;
    }

    day14_restoreAllORE(allChems, leftOvers);
    
    leftOvers["ORE"] += leftORE;
    int currentTry = 100000000;

    while (currentTry > 0)
    {
        std::map < string, long long> copyLeftOvers = leftOvers;
        bool valid = day14_getFuel(allChems, currentTry, "FUEL", copyLeftOvers);
        long long copyLeftOREValue = copyLeftOvers["ORE"];
        if (valid)
        {
            fuelGenerated += currentTry;

            leftOvers = copyLeftOvers;

            day14_restoreAllORE(allChems, leftOvers);
        }
        else
        {
            day14_restoreAllORE(allChems, leftOvers);
            currentTry /= 10;
        }
    }

    std::cout << "Day 14_B => "  << fuelGenerated << "\n";
}

std::map<string, day14_chem> day14_buildChems( const std::vector<string>& fileTxt)
{
    std::map<string, day14_chem> allChems;

    std::string regexTxt = "(\\d+) (.*)";
    std::regex numbersRegex(regexTxt);

    for (auto&& line : fileTxt)
    {
        day14_chem chem;
        //5 BHXH, 4 VRPVC => 5 LTCX
        auto split1 = split(line, " => ");

        {
            std::smatch sm_dest;
            std::regex_search(split1[1], sm_dest, numbersRegex);
            chem.totalResult = atoi(sm_dest.str(1).c_str());
            chem.result = trim_copy(sm_dest.str(2));
        }

        auto all_sources = split(split1[0], ",");
        for (auto&& s : all_sources)
        {
            std::smatch sm_dest;
            std::regex_search(s, sm_dest, numbersRegex);
            int total = atoi(sm_dest.str(1).c_str());
            string id = trim_copy(sm_dest.str(2));

            chem.needed.push_back({ id, total });
        }

        allChems[chem.result] = chem;
    }

    return allChems;
}

void day14()
{
    auto fileTxt = ReadFile("./input/day14.txt");

    std::map<string, day14_chem> allChems = day14_buildChems(fileTxt);

    std::map<string, long long> leftOvers;
    int resultA = day14_getORE(allChems, 1, "FUEL", leftOvers);
    std::cout << "Day 14 => "  << resultA << "\n";

    day14_B(allChems, resultA, leftOvers); 
}

class day15_intcode
{
public:
    using memoryType = long long;
    using inputFunction = function<memoryType()>;
    using outputFunction = function<void(memoryType)>;

private:
    int instructionIndex = 0;
    memoryType relativeBase = 0;
    inputFunction inputFun;
    outputFunction outputFun;
    std::map<memoryType, memoryType> memory;
    bool forceStop = false;

    memoryType calculateInstruction(int operation, std::vector<memoryType> params)
    {
        switch (operation)
        {
        case 1: return params[0] + params[1]; break;
        case 2: return params[0] * params[1]; break;
        case 3: return -1; break;
        case 4: return -1; break;
        case 5: return params[0] != 0; break;
        case 6: return params[0] == 0; break;
        case 7: return params[0] < params[1]; break;
        case 8: return params[0] == params[1]; break;
        case 9: return -1; break;
        }

        std::cout << "error\n";
        return 0;
    }

    memoryType getValue(memoryType value, int type)
    {
        switch (type)
        {
        case 0: return memory[value];
        case 1: return value;
        case 2:
            if (memory.find(value + relativeBase) == memory.end()) {
                memory[value + relativeBase] = 0;
            }
            return memory[value + relativeBase];
        }
        std::cout << "error \n";
        return 0;
    }

    std::vector<int> parseParamsInfo(int value, int totalElements)
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
        case 9: return 1;
        }
        return 0;
    }

    std::vector<memoryType> readParametersFromInstruction(int operation)
    {
        int totalParams = getParametersForOperation(operation);
        std::vector<memoryType> result;
        for (int i = 0; i < totalParams; ++i)
        {
            auto value = memory[instructionIndex + i + 1];
            result.push_back(value);
        }
        return result;
    }
    std::vector<memoryType> transformParameters(int operation, const std::vector<memoryType>& params, const std::vector<int>& parameterInfo)
    {
        std::vector<memoryType> result;
        for (int i = 0; i < params.size(); ++i)
        {
            auto value = getValue(params[i], parameterInfo[i]);
            result.push_back(value);
        }

        //direct result
        std::set<int> directResult = { 1, 2, 3, 7, 8 };
        if (directResult.find(operation) != directResult.end())
        {
            if (parameterInfo[result.size() - 1] == 2)
            {
                result[result.size() - 1] = params.back() + relativeBase;
            }
            else
            {
                result[result.size() - 1] = params.back();
            }
        }

        return result;
    }

    void writeResult(memoryType result, int operation, std::vector<memoryType>& paramsTransformed)
    {
        if (operation == 5 || operation == 6)
        {
            return;
        }

        if (operation == 4)
        {
            outputFun(paramsTransformed[0]);
            return;
        }
        if (operation == 9)
        {
            relativeBase += paramsTransformed[0];
            return;
        }

        if (operation == 3)
        {
            result = inputFun();
        }

        int indexSave = paramsTransformed.back();
        memory[indexSave] = result;
    }

    void updateIndex(std::vector<memoryType>& paramsTransformed, int operation, int result)
    {
        if (operation == 5 || operation == 6)
        {
            if (result)
            {
                instructionIndex = paramsTransformed[1];
                return;
            }
        }

        int totalParams = getParametersForOperation(operation);
        instructionIndex += totalParams + 1;
    }
    //
    //1:+
    //2:*
    //3:Read
    //4:Write
    //5:Jmp !=
    //6:Jmp ==
    //7:<
    //8: ==
    //9: +RelativeBase
    void runProgram()
    {
        while (memory[instructionIndex] != 99)
        {
            if (forceStop)
            {
                return;
            }

            runOneInstruction();
        }
    }

    void runOneInstruction()
    {
        auto instruction = memory[instructionIndex];
        auto paramsInfo = parseParamsInfo(memory[instructionIndex], 5);
        int operation = paramsInfo[0];
        paramsInfo.erase(paramsInfo.begin());
        auto paramsForInstruction = readParametersFromInstruction(operation);
        auto paramsTransformed = transformParameters(operation, paramsForInstruction, paramsInfo);

        auto result = calculateInstruction(operation, paramsTransformed);

        writeResult(result, operation, paramsTransformed);
        updateIndex(paramsTransformed, operation, result);
    }

    std::map<memoryType, memoryType> buildMemory(const std::string& txt)
    {
        auto split_value = split(txt, ",");
        std::map<memoryType, memoryType> memory;

        int index = 0;
        for (auto v : split_value)
        {
            memory[index] = stoll(v.c_str());
            ++index;
        }

        return memory;
    }

public:

    void Init(const std::string& txt, inputFunction input, outputFunction output)
    {
        inputFun = input;
        outputFun = output;
        memory = buildMemory(txt);
        instructionIndex = 0;
        relativeBase = 0;
    }

    void Run()
    {
        runProgram();
    }

    void RunDebug()
    {
        runOneInstruction();
    }

    std::vector<int> GetMemoryIndexes()
    {
        std::vector<int> toReturn;
        for (auto kvp : memory)
        {
            toReturn.push_back(kvp.first);
        }
        return toReturn;
    }

    memoryType GetValueInMemoryPosition(int index)
    {
        return memory[index];
    }

    void SetMemoryValue(memoryType value, memoryType index)
    {
        memory[index] = value;
    }

    void ForceStop()
    {
        forceStop = true;
    }
};

Directions day15_intToDirection(int dir)
{
    switch (dir)
    {
    case 1: return Directions::NORTH;
    case 2: return Directions::SOUTH;
    case 4: return Directions::EAST;
    case 3: return Directions::WEST;
    }

    return Directions::NORTH;
}

int day15_DirectionToInt(Directions value)
{
    switch (value)
    {
    case Directions::NORTH:
        return 1;
        break;
    case Directions::SOUTH:
        return 2;
        break;
    case Directions::EAST:
        return 4;
        break;
    case Directions::WEST:
        return 3;
        break;
    }

    return -1;
}

void day15_printBoard(const std::vector<std::vector<int>>& board, const std::pair<int, int>& start)
{
    for (int i = 0; i < board.size(); ++i)
    {
        for (int j = 0; j < board[i].size(); ++j)
        {
            if (i == start.second && j == start.first) { std::cout << "S"; continue; }
            if (board[i][j] == 2) { std::cout << 2; }
            if (board[i][j] == 1) { std::cout << "."; }
            if (board[i][j] == 0) { std::cout << "#"; }
            if (board[i][j] == -1) { std::cout << "?"; continue; }

        }
        std::cout << "\n";
    }
}

void day15_printBoard(const std::vector<std::vector<int>>& board, const std::pair<int, int>& start, const std::pair<int, int>& position)
{
    for (int i = 0; i < board.size(); ++i)
    {
        for (int j = 0; j < board[i].size(); ++j)
        {
            if (position.first == i && position.second == j) { std::cout << "D"; continue; }
            if (i == start.second && j == start.first) { std::cout << "S"; continue; }
            if (board[i][j] == 2) { std::cout << 2; continue; }
            if (board[i][j] == 1) { std::cout << "."; continue;}
            if (board[i][j] == 0) { std::cout << "#"; continue;}
            if (board[i][j] == -1) { std::cout << "?"; continue; }
        }
        std::cout << "\n";
    }
}

void day15_printBoard_B(const std::vector<std::vector<int>>& board)
{
    for (int i = 0; i < board.size(); ++i)
    {
        for (int j = 0; j < board[i].size(); ++j)
        {
            char buff[8];
            sprintf_s(buff, "|%03d|", board[i][j]);
            if (board[i][j] == -1) { std::cout << "|   |"; continue; }
            else
            {
                std::cout << buff;
            }
        }
        std::cout << "\n";
    }
}

std::vector<std::vector<int>> day15_getBoard(std::string& code, const std::pair<int, int>& start, std::pair<int, int>& end)
{
    day15_intcode program;


    std::pair<int, int> currentPosition = start;
    std::vector<std::vector<int>> board(start.first * 2, std::vector<int>(start.second * 2, -1));
    std::stack<Directions> lastDirections;

    board[currentPosition.first][currentPosition.second] = 1;

    Directions lastDecission = Directions::NONE;
    bool backTracking = false;

    day15_intcode::inputFunction input = [&program, &lastDirections, &currentPosition, &board, &lastDecission, &start, &backTracking] {

        for (Directions dir : {Directions::EAST, Directions::WEST, Directions::NORTH, Directions::SOUTH})
        {
            auto position = getNextPosition(currentPosition, dir);
            if (board[position.first][position.second] == -1)
            {
                lastDecission = dir;
                backTracking = false;
                return day15_DirectionToInt(dir);
            }
        }

        backTracking = true;

        if (lastDirections.empty())
        {
            program.ForceStop();
            return 0;
        }

        //here, we know all the sorrounding tiles, so we just undo the movememtn
        auto lastMovement = lastDirections.top();
        lastDirections.pop();

        auto turn90 = turn90Degress(lastMovement);
        auto turn180 = turn90Degress(turn90);

        lastDecission = turn180;
        int value = day15_DirectionToInt(turn180);

        return value;
    };

    day15_intcode::outputFunction output = [&program, &lastDecission, &lastDirections, &board, &currentPosition, &backTracking, &end](day15_intcode::memoryType value)
    {
        auto newTile = getNextPosition(currentPosition, lastDecission);
        board[newTile.first][newTile.second] = value;

        
        if (value == 2) {
            end = newTile;
        }
        
        if (value == 1 || value == 2)
        {
            if (!backTracking)
            {
                lastDirections.push(lastDecission);
            }

            currentPosition = newTile;
        }

    };

    program.Init(code, input, output);

    program.Run();

    return board;
}

struct day15_a_node
{
    std::pair<int, int> position;
    int count = 0;
};

void day15_a(std::pair<int, int>& start, std::vector<std::vector<int>>& board)
{
    int width = board[0].size();
    int height = board.size();
    std::vector<std::vector<bool>> visited(height, std::vector<bool>(width, false));

    std::vector<day15_a_node> nodesToInvestigate;

    day15_a_node nStart;
    nStart.count = 0;
    nStart.position = start;

    nodesToInvestigate.push_back(nStart);

    while (!nodesToInvestigate.empty())
    {
        auto node = nodesToInvestigate[0];
        nodesToInvestigate.erase(nodesToInvestigate.begin());

        if (visited[node.position.first][node.position.second]) { continue; }

        visited[node.position.first][node.position.second] = true;

        if (board[node.position.first][node.position.second] == 2)
        {
            std::cout << "day 15 => " << node.count << "\n";
            break;
        }

        for (Directions dir : {Directions::NORTH, Directions::EAST, Directions::SOUTH, Directions::WEST})
        {
            auto next = getNextPosition(node.position, dir);

            if(!insideField(next, width, height)){continue;}

            if (visited[next.first][next.second]) { continue; }
            if (board[next.first][next.second] == 0) { continue; }

            day15_a_node nextNode;
            nextNode.count = node.count +1;
            nextNode.position = next;

            nodesToInvestigate.push_back(nextNode);
        }
    }
}

void day15_b(std::pair<int, int>& start, std::vector<std::vector<int>>& board, bool paint)
{
    int width = board[0].size();
    int height = board.size();
    std::vector<std::vector<int>> timeToReach(height, std::vector<int>(width, -1));

    std::vector<day15_a_node> nodesToInvestigate;

    day15_a_node nStart;
    nStart.count = 0;
    nStart.position = start;

    nodesToInvestigate.push_back(nStart);

    int biggest = -1;

    while (!nodesToInvestigate.empty())
    {
        auto node = nodesToInvestigate[0];
        nodesToInvestigate.erase(nodesToInvestigate.begin());

        if (timeToReach[node.position.first][node.position.second] != -1) { continue; }

        timeToReach[node.position.first][node.position.second] = node.count;

        if (node.count > biggest) { biggest = node.count; }

        for (Directions dir : {Directions::NORTH, Directions::EAST, Directions::SOUTH, Directions::WEST})
        {
            auto next = getNextPosition(node.position, dir);

            //if (!insideField(next, width, height)) { continue; }

            //if (timeToReach[next.first][next.second] != -1) { continue; }
            if (board[next.first][next.second] == 0) { continue; }

            day15_a_node nextNode;
            nextNode.count = node.count + 1;
            nextNode.position = next;

            nodesToInvestigate.push_back(nextNode);
        }
    }

    if (paint)
    {
        day15_printBoard_B(timeToReach);
    }

    std::cout << "day 15_B => " << biggest << "\n";
}


void day15()
{
    auto code = ReadFile("./input/day15.txt")[0];
    std::pair<int, int> start = { 25,25 };
    std::pair<int, int> end;

    auto board = day15_getBoard(code, start, end);

    //day15_printBoard(board, start);

    day15_a(start, board);

    day15_b(end, board, false);
}

int main()
{
    //day1();
    //day2();
    //day3();
    //day4();
    //day5();
    //day6();
    //day7 ();
    //day8();
    //day9();
    //day10();
    //day11();
    //day12();
    //day13();
    //day14();
    day15();
}

// Ejecutar programa: Ctrl + F5 o menú Depurar > Iniciar sin depurar
// Depurar programa: F5 o menú Depurar > Iniciar depuración

// Sugerencias para primeros pasos: 1. Use la ventana del Explorador de soluciones para agregar y administrar archivos
//   2. Use la ventana de Team Explorer para conectar con el control de código fuente
//   3. Use la ventana de salida para ver la salida de compilación y otros mensajes
//   4. Use la ventana Lista de errores para ver los errores
//   5. Vaya a Proyecto > Agregar nuevo elemento para crear nuevos archivos de código, o a Proyecto > Agregar elemento existente para agregar archivos de código existentes al proyecto
//   6. En el futuro, para volver a abrir este proyecto, vaya a Archivo > Abrir > Proyecto y seleccione el archivo .sln
