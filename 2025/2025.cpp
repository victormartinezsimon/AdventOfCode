// 2025.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
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
#include <thread>
#include <mutex>
#include <condition_variable>
#include <cmath>
#include <iterator>
using namespace std;

int day1_partA(int start, int size, std::vector<std::string>& movements)
{
    int value = start;
    int result = 0;

    for (auto&& movement : movements)
    {
        int multiplier = 1;
        if (movement[0] == 'L')
        {
            multiplier = -1;
        }

        int number = atoi(movement.substr(1).c_str());
        number *= multiplier;

        value = (value + number + size) % size;
        if (value == 0)
        {
            ++result;
        }
    }
    return result;
}

int day1_partB(int start, int size, std::vector<std::string>& movements)
{
    int value = start;
    int result = 0;

    for (auto&& movement : movements)
    {
        int multiplier = 1;
        if (movement[0] == 'L')
        {
            multiplier = -1;
        }
        int number = atoi(movement.substr(1).c_str());

        int totalLaps = number / size;
        number = number - (totalLaps * size);

        result += totalLaps;

        number *= multiplier;

        int oldValue = value;
        value += number;

        if ((value < 0 || value > size) && oldValue != 0)
        {
            result++;
        }

        value = ( value + size ) % size;
    }
    return result;
}

void day1()
{
    auto fileTxt = ReadFile("./input/day1.txt");

    auto partA = day1_partA(50, 100, fileTxt);
    auto partB = day1_partB(50, 100, fileTxt);
    std::cout << "day 1 => " << partA << "\n";
    std::cout << "day 1_B => " << partB + partA<< "\n";
}

long long day2_calculateA(long long start, long long end)
{
    auto decimalsStart = std::to_string(start).size();
    auto decimalEnd = std::to_string(end).size();

    if ((decimalsStart % 2) == 1)
    {
        start = pow(10, decimalsStart);
        decimalsStart++;
    }

    if ((decimalEnd % 2) == 1)
    {
        end = pow(10, decimalEnd-1) -1;
        decimalEnd--;
    }

    int divisionStart = pow(10, decimalsStart / 2);
    int divisionEnd = pow(10, decimalEnd / 2);

    int valueStart = start / divisionStart;
    int valueEnd = end /  divisionEnd;

    long long result = 0;

    for (int value = valueStart; value <= valueEnd; ++value)
    {
        std::string valueToCheck_str = std::to_string(value) + std::to_string(value);

        unsigned long long valueToCheck = atoll(valueToCheck_str.c_str());

        if (start <= valueToCheck && valueToCheck <= end)
        {
            result += valueToCheck;
        }
    }


    return result;
}

bool day2_numberValid(const std::string& value_str)
{
    int size = value_str.size();

    for (int indexStart = 1; indexStart < size; ++indexStart)
    {
        string prefix = value_str.substr(0, indexStart);

        bool finded = true;
        for (int pos = indexStart; pos < size; pos += indexStart)
        {
            string toCheck = value_str.substr(pos, indexStart);

            if (toCheck != prefix)
            {
                finded = false;
                break;
            }
        }

        if (finded)
        {
            return true;
        }
    }

    return false;
}

long long day2_calculateB(long long start, long long end)
{
    long long result = 0;

    for (long long value = start; value <= end; ++value)
    {
        std::string value_str = std::to_string(value);

        if (day2_numberValid(value_str))
        {
            result += value;
        }
    }

    return result;
}

void day2( bool calculateB)
{
    auto fileTxt = ReadFile("./input/day2.txt");

    auto list = split(fileTxt[0], ",");

    long long valueA = 0;
    long long valueB = 0;

    if (!calculateB)
    {
        valueB = 31578210022;
    }

    for (auto l : list)
    {
        auto values = split(l, "-");
        long long v1 = std::atoll(values[0].c_str());
        long long v2 = std::atoll(values[1].c_str());

        valueA += day2_calculateA(v1, v2);
        if (calculateB)
        {
            valueB += day2_calculateB(v1, v2);
        }
    }

    std::cout << "day 2 => " << valueA << "\n";
    std::cout << "day 2_B => " << valueB << "\n";

}

int day3_getBestDigit(const std::string& line, int start, int end)
{
    int best = -1;
    int index = -1;

    for (int i = start; i < end; ++i)
    {
        char v = line[i];
        int value = v - '0';

        if (value > best)
        {
            best = value;
            index = i;
        }
    }
    return index;
}

int day3_partA(const std::string& line)
{
    int indexFirst = day3_getBestDigit(line, 0, line.size() - 1);
    int indexSecond = day3_getBestDigit(line, indexFirst + 1, line.size());

    std::string first = line.substr(indexFirst, 1);
    std::string second = line.substr(indexSecond, 1);
    std::string result = first + second;

    return atoi(result.c_str());
}

long long day3_partB(const std::string& line)
{
    std::vector<int> indexes;
    int totalIndex = 12;

    int lastIndex = 0;

    for (int i = 0; i < totalIndex; ++i)
    {
        auto result = day3_getBestDigit(line, lastIndex, line.size() - totalIndex + i +1);
        indexes.push_back(result);
        lastIndex = result +1;
    }

    std::string result = "";

    for (auto index : indexes)
    {
        result += line[index];
    }

    return atoll(result.c_str());

}

void day3()
{
    auto fileTxt = ReadFile("./input/day3.txt");

    long long partA = 0;
    long long partB = 0;

    for (auto&& line : fileTxt)
    {
        auto v = day3_partA(line);
        partA += v;

        auto v_b = day3_partB(line);
        partB += v_b;
    }

    std::cout << "day3 => " << partA << "\n";
    std::cout << "day3_B => " << partB << "\n";
}

int day4_getCount(const std::vector<std::string>& board, int width, int height, int row, int col, char valueCheck)
{
    int count = 0;
    for (Directions dir : all8Directions())
    {
        auto nextPosition = getNextPosition(row, col, dir);

        if (insideField(nextPosition, width, height))
        {
            if (GetValueFromBoard(board, nextPosition) == valueCheck)
            {
                ++count;
            }
        }
    }
    return count;
}

long long day4_partA(const std::vector<std::string>& board, int width, int height)
{
    long long result = 0;

    for (int row = 0; row < height; ++row)
    {
        for (int col = 0; col < width; ++col)
        {
            if (board[row][col] == '@')
            {
                auto count = day4_getCount(board, width, height, row, col, '@');
                if (count < 4)
                {
                    ++result;
                }
            }
        }
    }
    return result;
}

long long day4_partB(const std::vector<std::string>& board, int width, int height)
{
    std::vector<std::string> currentBoard = board;
    std::vector<std::string> nextBoard = board;

    long long result = 0;

    int currentCount = 0;

    do
    {
        currentCount = 0;
        for (int row = 0; row < height; ++row)
        {
            for (int col = 0; col < width; ++col)
            {
                if (currentBoard[row][col] == '@')
                {
                    auto count = day4_getCount(currentBoard, width, height, row, col, '@');
                    if (count < 4)
                    {
                        ++result;
                        nextBoard[row][col] = 'x';
                        ++currentCount;
                    }
                    else
                    {
                        nextBoard[row][col] = currentBoard[row][col];
                    }
                }
                else
                {
                    nextBoard[row][col] = currentBoard[row][col];
                }
            }
        }

        currentBoard = nextBoard;

    } while (currentCount != 0);

    return result;
}

void day4()
{
    auto board = ReadFile("./input/day4.txt");
    int width = board[0].size();
    int height = board.size();

    long long partA = day4_partA(board, width, height);
    long long partB = day4_partB(board, width, height);

    std::cout << "day4 => " << partA << "\n";
    std::cout << "day4_B => " << partB << "\n";
}

bool day5_valid(const std::vector<std::pair<long long, long long>>& groups, long long value)
{
    for (auto&& g : groups)
    {
        if (g.first > value) { return false; }

        if (g.first <= value && value <= g.second)
        {
            return true;
        }
    }

    return false;
}

void day5_buildInput(const std::vector<std::string>& fileTxt, std::vector<std::pair<long long, long long>>& groups, std::vector<long long>& values)
{
    int lineIndex = 0;
    while (!fileTxt[lineIndex].empty())
    {
        auto values = split(fileTxt[lineIndex], "-");
        long long v1 = atoll(values[0].c_str());
        long long v2 = atoll(values[1].c_str());
        groups.push_back({ v1,v2 });
        ++lineIndex;
    }

    std::sort(groups.begin(), groups.end(), [](std::pair<long long, long long> a, std::pair<long long, long long> b)
        {
            if (a.first != b.first)
            {
                return a.first < b.first;
            }

            return a.second < b.second;

        });


    ++lineIndex;

    while (lineIndex < fileTxt.size())
    {
        long long v = atoll(fileTxt[lineIndex].c_str());
        values.push_back(v);
        ++lineIndex;
    }
}

long long day5_a(const std::vector<std::pair<long long, long long>>& groups, const std::vector<long long>& values)
{
    long long result= 0;
    for (auto&& v : values)
    {
        if (day5_valid(groups, v))
        {
            ++result;
        }
    }

    return result;
}

long long day5_b(std::vector<std::pair<long long, long long>> groups)
{
    bool someFusion = true;

    while (someFusion)
    {
        someFusion = false;

        int index = 0;

        while (index < groups.size() && index +1 < groups.size())
        {
            auto g1 = groups[index];
            auto g2 = groups[ index +1];

            auto g1_start = g1.first;
            auto g1_end = g1.second;

            auto g2_start = g2.first;
            auto g2_end = g2.second;

            //g1s g2s g2e g1e
            if (g1_start < g2_start && g2_end < g1_end)
            {
                groups.erase(groups.begin() + index + 1);
                someFusion = true;
                continue;
            }

            //g1s g2s g1e g2e
            if (g1_start <= g2_start && g2_start <= g1_end && g1_end <= g2_end)
            {
                groups.erase(groups.begin() + index);//delete g1
                groups.erase(groups.begin() + index);//delete g2

                std::pair<long long, long long>newGroup = { std::min(g1_start, g2_start), std::max(g1_end, g2_end) };

                groups.insert(groups.begin() + index, newGroup);
                someFusion = true;
                continue;
            }

            //g1s g1e g2e g2e
            if (g1_end < g2_start)
            {
                ++index;
            }
        }

    }

    //check extra fusion?

    long long result = 0;

    for (auto&& g : groups)
    {
        result += (g.second - g.first + 1);
    }

    return result;

}

void day5()
{
    auto fileTxt = ReadFile("./input/day5.txt");

    std::vector<std::pair<long long, long long>> groups;
    std::vector<long long> values;
    day5_buildInput(fileTxt, groups, values);

    auto resultA = day5_a(groups, values);
    auto resultB = day5_b(groups);

    std::cout << "Day 5 => " << resultA << "\n";
    std::cout << "Day 5_B => " << resultB << "\n";

}

void day6_getInput(const std::vector<std::string>& fileTxt, std::vector<std::vector<int>>& numbers, std::vector<std::string>& symbols)
{
    for (int lineIdx = 0; lineIdx < fileTxt.size() - 1; ++lineIdx)
    {
        auto&& line = fileTxt[lineIdx];

        std::regex re("\\b\\d+\\b");
        std::smatch match;

        std::string::const_iterator searchStart(line.cbegin());

        std::vector<int>number;

        while (std::regex_search(searchStart, line.cend(), match, re)) {
            number.push_back(std::stoi(match.str()));
            searchStart = match.suffix().first;
        }
        numbers.push_back(number);
    }

    auto&& lastLine = fileTxt.back();
    std::regex re("[\\+\\*]");

    std::sregex_iterator it(lastLine.begin(), lastLine.end(), re);
    std::sregex_iterator end;

    while (it != end) {
        symbols.push_back((*it).str());
        ++it;
    }

}

long long day6_partA(const std::vector<std::vector<int>>& numbers, const std::vector<std::string>& symbols)
{
    long long result = 0;
    int totalCols = symbols.size();

    for (int col = 0; col < totalCols; ++col)
    {
        long long acum = numbers[0][col];
        bool multiply = symbols[col] == "*";

        for (int row = 1; row < numbers.size(); ++row)
        {
            auto number = numbers[row][col];
            if (multiply)
            {
                acum *= number;
            }
            else
            {
                acum += number;
            }
        }

        result += acum;
    }
    return result;
}

int day6_getMaxDigits(const std::vector<int>& numbersToUse)
{
    int maxDigits = 0;
    for (auto n : numbersToUse)
    {
        int size = std::to_string(n).size();
        if (size > maxDigits)
        {
            maxDigits = size;
        }
    }

    return maxDigits;
}

long long day6_calculateB(const std::vector<string>& stringToUse, const std::string& symbol)
{
    bool useMult = symbol == "*";
    long long result = 0;
    if (useMult) { result = 1; }

    int sizeString = stringToUse[0].size();
    for (int col = 0; col < sizeString; ++col)
    {
        int multiplier = 1;
        long long numberToUse = 0;
        for (int row = stringToUse.size() - 1; row >= 0; --row)
        {
            auto c = stringToUse[row][col];

            if (c != ' ')
            {
                int val = c - '0';
                numberToUse = numberToUse + val * multiplier;
                if (numberToUse != 0)
                {
                    multiplier *= 10;
                }
            }
        }

        if (useMult)
        {
            result *= numberToUse;
        }
        else
        {
            result += numberToUse;
        }
    }

    return result;
}

long long day6_partB(const std::vector<std::string>& fileTxt, const std::vector<std::vector<int>>& numbers, const std::vector<std::string>& symbols)
{
    int currentOffset = 0;
    
    int totalCols = symbols.size();
    long long result = 0;

    for (int col = 0; col < totalCols; ++col)
    {
        std::vector<int> numberToUse;
        for (int row = 0; row < numbers.size(); ++row)
        {
            numberToUse.push_back(numbers[row][col]);
        }

        int maxDigits = day6_getMaxDigits(numberToUse);

        std::vector<string> stringToUse;
        for (int row = 0; row < numbers.size(); ++row)
        {
            std::string str = fileTxt[row].substr(currentOffset, maxDigits);
            stringToUse.push_back(str);
        }
        currentOffset += maxDigits + 1;

        auto tmpResult = day6_calculateB(stringToUse, symbols[col]);
        result += tmpResult;

    }

    return result;
}

void day6()
{
    auto fileTxt = ReadFile("./input/day6.txt");

    std::vector<std::vector<int>> numbers;
    std::vector<std::string> symbols;

    day6_getInput(fileTxt, numbers, symbols);

    auto partA = day6_partA(numbers, symbols);
    std::cout << "day 5 => " << partA << "\n";


    auto partB = day6_partB(fileTxt, numbers, symbols);
    std::cout << "day 5_B => " << partB << "\n";
}
void day7_allCalculus(const std::vector<std::string>& board, long long& partA, long long& partB)
{
    int width = board[0].size();
    int height = board.size();

    std::vector<std::vector<long long>> particlesInPosition = std::vector<std::vector<long long>>(height, std::vector<long long>(width, 0));

    int startCol = -1;
    for (int i = 0; i < width; ++i)
    {
        if (board[0][i] == 'S')
        {
            startCol = i;
            break;
        }
    }

    particlesInPosition[0][startCol] = 1;

    std::vector<std::pair<int, int>> particlesAlive;
    particlesAlive.push_back({ 0, startCol });

    long long countSplits = 0;

    while (!particlesAlive.empty())
    {
        auto particleToAnalyze = particlesAlive.front();
        particlesAlive.erase(particlesAlive.begin());

        int nextHeight = particleToAnalyze.first + 1;
        if (nextHeight >= height)
        {
            continue;
        }

        std::vector<std::pair<int, int>> nextParticles;

        if (board[particleToAnalyze.first][particleToAnalyze.second] == '^')
        {
            //left
            int leftPos = particleToAnalyze.second - 1;
            bool createLeft = particlesInPosition[nextHeight][leftPos] == 0;
            particlesInPosition[nextHeight][leftPos] += particlesInPosition[particleToAnalyze.first][particleToAnalyze.second];
            
            int rightPos = particleToAnalyze.second + 1;
            bool createRight = particlesInPosition[nextHeight][rightPos] == 0;
            particlesInPosition[nextHeight][rightPos] += particlesInPosition[particleToAnalyze.first][particleToAnalyze.second];

            if (createLeft)
            {
                particlesAlive.push_back({ nextHeight, leftPos });
            }
            if (createRight)
            {
                particlesAlive.push_back({ nextHeight, rightPos });
            }

            ++countSplits;
        }
        else
        {
            bool createNext = particlesInPosition[nextHeight][particleToAnalyze.second] == 0;
            particlesInPosition[nextHeight][particleToAnalyze.second] += particlesInPosition[particleToAnalyze.first][particleToAnalyze.second];
            if (createNext)
            {
                particlesAlive.push_back({ nextHeight, particleToAnalyze.second });
            }
        }
    }


    long long countB = 0;
    for (int col = 0; col < width; ++col)
    {
        countB += particlesInPosition[height - 1][col];
    }

    partA = countSplits;
    partB = countB;
}

long long day7_partBCalculus(const std::vector<std::string>& board, std::pair<int, int> particle, int height, std::map<std::string, long long>& cache)
{
    if (particle.first >= height) { return 1; }

    std::string key = std::to_string(particle.first) + "-" + std::to_string(particle.second);

    if (cache.contains(key))
    {
        return cache[key];
    }

    long long result = 0;
    if (board[particle.first][particle.second] == '^')
    {
        result += day7_partBCalculus(board, { particle.first + 1, particle.second-1 }, height, cache);
        result += day7_partBCalculus(board, { particle.first + 1, particle.second+1 }, height, cache);
    }
    else
    {
        result = day7_partBCalculus(board, { particle.first + 1, particle.second }, height, cache);
    }


    cache[key] = result;
    return result;

}
long long day7_partBCache(const std::vector<std::string>& board)
{
    std::map<std::string, long long> cache;

    int width = board[0].size();
    int height = board.size();

    int startCol = -1;
    for (int i = 0; i < width; ++i)
    {
        if (board[0][i] == 'S')
        {
            startCol = i;
            break;
        }
    }

    long long value = day7_partBCalculus(board, { 0, startCol }, height, cache);

    return value;
}

void day7()
{
    auto board = ReadFile("./input/day7.txt");

    long long partA;
    long long partB_common;
    day7_allCalculus(board, partA, partB_common);
    auto partB = day7_partBCache(board);

    std::cout << "day 7 => " << partA << "\n";
    std::cout << "day 7_B (common) => " << partB_common << "\n";
    std::cout << "day 7_B (cache)  => " << partB << "\n";
}

struct day8_node_distance
{
    int id1;
    int id2;
    double distance;
};

struct day8_node
{
    int x;
    int y;
    int z;
};

std::vector<day8_node> day8_buildNodes(const std::vector<string>& fileTxt)
{
    std::vector<day8_node> toReturn;
    for (auto&& l : fileTxt)
    {
        auto values = split(l, ",");
        day8_node node;
        node.x = atoi(values[0].c_str());
        node.y = atoi(values[1].c_str());
        node.z = atoi(values[2].c_str());
        toReturn.push_back(node);
    }

    return toReturn;
}

double day8_getDistance(const day8_node& node1, const day8_node& node2)
{
    return std::pow(node1.x - node2.x, 2) + std::pow(node1.y - node2.y, 2) + std::pow(node1.z - node2.z, 2);
}

std::vector<day8_node_distance> day8_calculateAllDistances(const std::vector<day8_node>& nodes)
{
    std::vector<day8_node_distance> toReturn;
    for (int i = 0; i < nodes.size(); ++i)
    {
        for(int j = i+1; j < nodes.size(); ++j)
        {
            day8_node_distance node;
            node.id1 = i;
            node.id2 = j;
            node.distance = day8_getDistance(nodes[i], nodes[j]);
            toReturn.push_back(node);
        }
    }

    std::sort(toReturn.begin(), toReturn.end(), [nodes](const day8_node_distance& n1, const day8_node_distance& n2)
        {
            if (n1.distance != n2.distance)
            {
                return n1.distance < n2.distance; 
            }

            if(n1.id1 != n2.id1)
            {
                return n1.id1 < n2.id1;
            }

            return n1.id2 < n2.id2;
        });

    return toReturn;
}

std::vector<std::set<int>> day8_buildAllSets(const std::vector<day8_node>& nodes)
{
    std::vector<std::set<int>> toReturn;

    for (int i = 0; i < nodes.size(); ++i)
    {
        std::set<int> s = { i };
        toReturn.push_back(s);
    }

    return toReturn;
}

int day8_getSetIndex(int id, const std::vector<std::set<int>>& sets)
{
    for (int i = 0; i < sets.size(); ++i)
    {
        if(sets[i].contains(id))
        {
            return i;
        }
    }
    return -1;
}

void day8_mergeSets(std::vector<day8_node_distance>& distances, int iterations, std::vector<std::set<int>>& sets)
{
    for (int it = 0; it < iterations; ++it)
    {
        auto best = distances.front();
        distances.erase(distances.begin());

        int setIdx1 = day8_getSetIndex(best.id1, sets);
        int setIdx2 = day8_getSetIndex(best.id2, sets);

        if (setIdx1 != setIdx2)
        {
            std::set<int> newSet;
            
            std::set_union( sets[setIdx1].cbegin(), sets[setIdx1].cend(), 
                            sets[setIdx2].cbegin(), sets[setIdx2].cend(), 
                            std::inserter(newSet, newSet.begin()));
                            
            if (setIdx1 < setIdx2)
            {
                sets.erase(sets.begin() + setIdx2);
                sets.erase(sets.begin() + setIdx1);
            }
            else
            {
                sets.erase(sets.begin() + setIdx1);
                sets.erase(sets.begin() + setIdx2);
            }
                
            sets.insert(sets.begin(), newSet);
        }
    }
}

std::pair<int, int> day8_infiniteMerge(std::vector<day8_node_distance>& distances, std::vector<std::set<int>>& sets)
{
    int lastId1 = -1;
    int lastId2 = -1;
    
    while (sets.size() != 1)
    {
        auto best = distances.front();
        distances.erase(distances.begin());

        int setIdx1 = day8_getSetIndex(best.id1, sets);
        int setIdx2 = day8_getSetIndex(best.id2, sets);

        lastId1 = best.id1;
        lastId2 = best.id2;

        if (setIdx1 != setIdx2)
        {
            std::set<int> newSet;

            std::set_union(sets[setIdx1].cbegin(), sets[setIdx1].cend(),
                sets[setIdx2].cbegin(), sets[setIdx2].cend(),
                std::inserter(newSet, newSet.begin()));

            if (setIdx1 < setIdx2)
            {
                sets.erase(sets.begin() + setIdx2);
                sets.erase(sets.begin() + setIdx1);
            }
            else
            {
                sets.erase(sets.begin() + setIdx1);
                sets.erase(sets.begin() + setIdx2);
            }

            sets.insert(sets.begin(), newSet);
        }
    }

    return { lastId1, lastId2 };
}

void day8()
{
    auto fileTxt = ReadFile("./input/day8.txt");

    auto nodes = day8_buildNodes(fileTxt);

    auto distances = day8_calculateAllDistances(nodes);

    auto allSets = day8_buildAllSets(nodes);

    day8_mergeSets(distances, 1000, allSets);


    std::vector<int> allSizes;
    for (auto&& s : allSets)
    {
        allSizes.push_back(s.size());
    }
    std::sort(allSizes.begin(), allSizes.end(), [](int a, int b)
        {
            return a > b;
        });

    long long partA = allSizes[0] * allSizes[1] * allSizes[2];

    auto partBNodes = day8_infiniteMerge(distances, allSets);

    long long partB = nodes[partBNodes.first].x * nodes[partBNodes.second].x;
    

    std::cout << "day8 => " << partA << "\n";
    std::cout << "day8_B => " << partB << "\n";
}

long long day9_getArea(const std::pair<long long, long long> p1, const std::pair<long long, long long>& p2)
{
    auto width = std::abs(p1.first - p2.first ) + 1;
    auto height = std::abs(p1.second - p2.second ) +1;

    return width * height;
}


std::vector<std::pair<long long, long long>> day9_getSquarePoints(const std::pair<long long, long long>& p1, const std::pair<long long, long long>& p2)
{
    std::vector<std::pair<long long, long long>> toReturn;

    toReturn.push_back({ p1.first,p2.second });
    toReturn.push_back({ p2.first,p1.second });

    return toReturn;

}

bool puntoEnSegmento(const std::pair<long long, long long>& a, const std::pair<long long, long long>& b, const std::pair<long long, long long>& p) {
    double minX = std::min(a.first, b.first), maxX = std::max(a.first, b.first);
    double minY = std::min(a.second, b.second), maxY = std::max(a.second, b.second);

    // Comprobamos colinealidad: área = 0
    double area = (b.first - a.first) * (p.second - a.second) - (b.second - a.second) * (p.first - a.first);
    if (std::abs(area) > 1e-9) return false;

    // Comprobar si p está dentro del rango del segmento
    return (p.first >= minX && p.first <= maxX && p.second >= minY && p.second <= maxY);
}

bool IsPointInPolygon(std::pair<long long, long long> p, std::vector<std::pair<long long, long long>> poligono)
{
    bool dentro = false;
    int n = poligono.size();

    for (int i = 0, j = n - 1; i < n; j = i++) {
        const auto& a = poligono[i];
        const auto& b = poligono[j];

        // Verificar si está sobre un borde
        if (puntoEnSegmento(a, b, p)) return true;

        // Comprobar cruce de rayos
        bool intersecta = ((a.second > p.second) != (b.second > p.second)) &&
            (p.first < (b.first - a.first) * (p.second - a.second) / (b.second - a.second) + a.first);

        if (intersecta)
            dentro = !dentro;
    }

    return dentro;

}

bool day9_inLine(std::pair<long long, long long> p, std::vector<std::pair<long long, long long>> polygon)
{
    for (int i = 0; i < polygon.size(); ++i)
    {
        int nextIndex = (i + 1) % polygon.size();

        auto p1 = polygon[i];
        auto p2 = polygon[nextIndex];

        if (p1.first == p2.first && p1.first == p.first)
        {
            //all in same X
            long long minY = std::min(p1.second, p2.second);
            long long maxY = std::max(p1.second, p2.second);

            return minY <= p.second && p.second <= maxY;

        }

        if (p1.second == p2.second && p1.second == p.second)
        {
            //all in same X

            long long minX = std::min(p1.first, p2.first);
            long long maxX = std::max(p1.first, p2.first);

            return minX <= p.first && p.first <= maxX;
        }
    }

    return false;
}

// Producto cruzado de (b - a) x (c - a)
double cross(const std::pair<long long, long long>& a, const std::pair<long long, long long>& b, const std::pair<long long, long long>& c) {
    return (b.first - a.first) * (c.second - a.second) -
        (b.second - a.second) * (c.first - a.first);
}

// Comprueba si c está sobre el segmento [a,b]
bool enSegmento(const std::pair<long long, long long>& a, const std::pair<long long, long long>& b, const std::pair<long long, long long>& c) {
    return min(a.first, b.first) - 1e-12 <= c.first && c.first <= max(a.first, b.first) + 1e-12 &&
        min(a.second, b.second) - 1e-12 <= c.second && c.second <= max(a.second, b.second) + 1e-12;
}

// Devuelve true si los segmentos [A,B] y [C,D] colisionan/intersectan
bool intersectan(const std::pair<long long, long long>& A, const std::pair<long long, long long>& B,
    const std::pair<long long, long long>& C, const std::pair<long long, long long>& D) {

    double d1 = cross(A, B, C);
    double d2 = cross(A, B, D);
    double d3 = cross(C, D, A);
    double d4 = cross(C, D, B);

    // Caso general: se cruzan si los signos son opuestos
    if ((d1 * d2 < 0) && (d3 * d4 < 0))
        return true;

    /*
    // Casos colineales: puntos sobre el segmento
    if (fabs(d1) < 1e-12 && enSegmento(A, B, C)) return true;
    if (fabs(d2) < 1e-12 && enSegmento(A, B, D)) return true;
    if (fabs(d3) < 1e-12 && enSegmento(C, D, A)) return true;
    if (fabs(d4) < 1e-12 && enSegmento(C, D, B)) return true;
    */
    return false;
}

long long  day9_partB(const std::vector<std::pair<long long, long long>>& points)
{
    long long best = -1;
    for (int i = 0; i < points.size(); ++i)
    {
        for (int j = i + 1; j < points.size(); ++j)
        {
            auto p1 = points[i];
            auto p2 = points[j];

            auto x0 = std::min(p1.first, p2.first);
            auto y0 = std::min(p1.second, p2.second);
            auto x1 = std::max(p1.first, p2.first);
            auto y1 = std::max(p1.second, p2.second);

            std::pair<long long, long long> pa = { x0,y0 };
            std::pair<long long, long long> pb = { x1,y0 };
            std::pair<long long, long long> pc = { x1,y1 };
            std::pair<long long, long long> pd = { x0,y1 };


            if (!IsPointInPolygon(pa, points)) continue;
            if (!IsPointInPolygon(pb, points)) continue;
            if (!IsPointInPolygon(pc, points)) continue;
            if (!IsPointInPolygon(pd, points)) continue;

            bool valid = true;
            int lastK = -1;
            for (int k = 0; k < points.size(); ++k)
            {
                lastK = k;

                auto pr1 = points[k];
                auto pr2 = points[(k + 1) % points.size()];

                if (intersectan(pa, pb, pr1, pr2)) { valid = false; break; }
                if (intersectan(pb, pc, pr1, pr2)) { valid = false; break; }
                if (intersectan(pc, pd, pr1, pr2)) { valid = false; break; }
                if (intersectan(pd, pa, pr1, pr2)) { valid = false; break; }
            }

            if (valid)
            {
                auto area = day9_getArea(p1, p2);
                auto area2 = day9_getArea(pa, pd);
                if (area > best)
                {
                    best = area;
                }
            }
           
        }
    }

    return best;
}


long long day9_calculateA(const std::vector<std::pair<long long, long long>>& points)
{
    long long best = -1;

    for (int i = 0; i < points.size(); ++i)
    {
        for (int j = i + 1; j < points.size(); ++j)
        {
            auto area = day9_getArea(points[i], points[j]);
            if (area > best)
            {
                best = area;
            }
        }
    }
    return best;
}

void day9()
{
    auto fileTxt = ReadFile("./input/day9.txt");
    std::vector<std::pair<long long, long long>> points;

    for (auto&& l : fileTxt)
    {
        auto values = split(l, ",");
        auto x = atoll(values[0].c_str());
        auto y = atoll(values[1].c_str());
        points.push_back({ x,y });
    }

    auto valueA = day9_calculateA(points);
    std::cout << "day 9 => " << valueA << "\n";

    auto valueB = day9_partB(points);
    std::cout << "day 9_B => " << valueB << "\n";
}


long long day11_solver(const std::map<std::string,std::vector<std::string>>& nodes,const std::string& currentNode,
	const std::string& end,const std::set<std::string>& invalidNodes, std::map<std::string,long long>& cache)
{
	if(currentNode == end)
	{
		return 1;
	}

	if(cache.contains(currentNode))
	{
		return cache[currentNode];
	}

	if(nodes.contains(currentNode) == false)
	{
		return 0;
	}

	long long count = 0;

	auto sons = nodes.at(currentNode);
	for(auto d: sons)
	{
		if(invalidNodes.contains(d))
		{
			continue;
		}

		count += day11_solver(nodes,d,end,invalidNodes, cache);
	}

	cache[currentNode] = count;

	return count;
}


void day11()
{
	 auto fileTxt = ReadFile("./input/day11.txt");

	 auto nodes = day11_getNodes(fileTxt);

	 std::map<std::string,long long> cache_partA;
	 auto partA = day11_solver(nodes, "you", "out", {}, cache_partA);

	 std::cout << "day 11 => " << partA << "\n";

	 std::map<std::string,long long> cache_svr_dac;
	 auto from_svr_dac = day11_solver(nodes, "svr", "dac", {"fft"}, cache_svr_dac);

	 std::map<std::string,long long> cache_dac_fft;
	 auto from_dac_fft = day11_solver(nodes, "dac", "fft", {}, cache_dac_fft);

	 std::map<std::string,long long> cache_fft_out;
	 auto from_fft_out = day11_solver(nodes, "svr", "fft", {"dac"}, cache_fft_out);
	 
	 std::map<std::string,long long> cache_svr_fft;
	 auto from_svr_fft = day11_solver(nodes, "svr", "fft", {"dac"}, cache_svr_fft);

	 std::map<std::string,long long> cache_fft_dac;
	 auto from_fft_dac = day11_solver(nodes, "fft", "dac", {"svr"},cache_fft_dac);

	 std::map<std::string,long long> cache_dac_out;
	 auto from_dac_out = day11_solver(nodes, "dac", "out", {"fft"}, cache_dac_out);
	 
	 long long partB = from_svr_dac * from_dac_fft * from_fft_out + from_svr_fft * from_fft_dac * from_dac_out;

	 std::cout << "day 11_B => " << partB << "\n";
}

int main()
{
    //day1();
    //day2(false);
    //day3();
    //day4();
    //day5();
    //day6();
    //day7();
    //day8();
    day9();
    other_9();
    //day9_gpt();
    //std::cout << "mine\n";
    //day9();
    /*
    day10();
    day11();
    day12();
    day13();
    day14();
    day15();
    day16();
    day17();
    day18();
    day19();
    day20();
    day21();
    day22();
    day23(false);
    day24();
    day25(false);
    */
}

// Ejecutar programa: Ctrl + F5 o menú Depurar > Iniciar sin depurar
// Depurar programa: F5 o menú Depurar > Iniciar depuración

// Sugerencias para primeros pasos: 1. Use la ventana del Explorador de soluciones para agregar y administrar archivos
//   2. Use la ventana de Team Explorer para conectar con el control de código fuente
//   3. Use la ventana de salida para ver la salida de compilación y otros mensajes
//   4. Use la ventana Lista de errores para ver los errores
//   5. Vaya a Proyecto > Agregar nuevo elemento para crear nuevos archivos de código, o a Proyecto > Agregar elemento existente para agregar archivos de código existentes al proyecto
//   6. En el futuro, para volver a abrir este proyecto, vaya a Archivo > Abrir > Proyecto y seleccione el archivo .sln
