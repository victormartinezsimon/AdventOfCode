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
#include <functional>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <cmath>
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
    for (Directions dir : {Directions::EAST, Directions::WEST, Directions::NORTH, Directions::SOUTH, Directions::NORTHEAST, Directions::NORTHWEST, Directions::SOUTHEAST, Directions::SOUTHWEST})
    {
        auto nextPosition = getNextPosition(row, col, dir);

        if (insideField(nextPosition, width, height))
        {
            if (board[nextPosition.first][nextPosition.second] == valueCheck)
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

int main()
{
    //day1();
    //day2(false);
    //day3();
    day4();
    /*
    day5();
    day6();
    day7();
    day8();
    day9();
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
