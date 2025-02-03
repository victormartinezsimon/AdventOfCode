#pragma once
#include <vector>
#include <string>
#include <iostream>
#include <fstream>

using namespace std;

constexpr float PI = 3.14159265f;

std::vector<string> ReadFile(string path)
{
    std::vector<string> result;
    std::ifstream file(path.c_str());

    if (file.is_open())
    {
        string line;
        while (std::getline(file, line))
        {
            result.push_back(line);
        }
    }
    return result;
}

vector<string> split(string s, const string& delimiter)
{
    vector<string> toReturn;

    size_t pos = 0;
    std::string token;
    while ((pos = s.find(delimiter)) != std::string::npos) {
        token = s.substr(0, pos);
        toReturn.push_back(token);
        s.erase(0, pos + delimiter.length());
    }
    toReturn.push_back(s);

    return toReturn;
}

// trim from start (in place)
static inline void ltrim(std::string& s) {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](unsigned char ch) {
        return !std::isspace(ch);
        }));
}

// trim from end (in place)
static inline void rtrim(std::string& s) {
    s.erase(std::find_if(s.rbegin(), s.rend(), [](unsigned char ch) {
        return !std::isspace(ch);
        }).base(), s.end());
}

// trim from both ends (in place)
static inline void trim(std::string& s) {
    rtrim(s);
    ltrim(s);
}

// trim from start (copying)
static inline std::string ltrim_copy(std::string s) {
    ltrim(s);
    return s;
}

// trim from end (copying)
static inline std::string rtrim_copy(std::string s) {
    rtrim(s);
    return s;
}

// trim from both ends (copying)
static inline std::string trim_copy(std::string s) {
    trim(s);
    return s;
}

bool insideField(int row, int col, int width, int height)
{
    if (row < 0) { return false; }
    if (col < 0) { return false; }
    if (col >= width) { return false; }
    if (row >= height) { return false; }

    return true;
}

bool insideField(std::pair<int, int>position, int width, int height)
{
    return insideField(position.first, position.second, width, height);
}

enum class Directions {
    NORTH, SOUTH, EAST, WEST, NORTHEAST, NORTHWEST, SOUTHEAST, SOUTHWEST
};

std::pair<int, int> getNextPosition(int row, int col, Directions dir)
{
    switch (dir)
    {
    case Directions::NORTH:
        return { row - 1, col + 0 };
        break;
    case Directions::SOUTH:
        return { row + 1, col + 0 };
        break;
    case Directions::EAST:
        return { row + 0, col + 1 };
        break;
    case Directions::WEST:
        return { row + 0, col - 1 };
        break;
    case Directions::NORTHEAST:
        return { row - 1, col + 1 };
        break;
    case Directions::NORTHWEST:
        return { row - 1, col - 1 };
        break;
    case Directions::SOUTHEAST:
        return { row + 1, col + 1 };
        break;
    case Directions::SOUTHWEST:
        return { row + 1, col - 1 };
        break;
    }
    return { row, col };
}

std::pair<int, int> getNextPosition(std::pair<int, int>pos, Directions dir)
{
    return getNextPosition(pos.first, pos.second, dir);
}

Directions turn90Degress(Directions dir)
{
    switch (dir)
    {
    case Directions::NORTH:
        return Directions::EAST;
        break;
    case Directions::SOUTH:
        return Directions::WEST;
        break;
    case Directions::EAST:
        return Directions::SOUTH;
        break;
    case Directions::WEST:
        return Directions::NORTH;
        break;
    case Directions::NORTHEAST:
        return Directions::SOUTHEAST;
        break;
    case Directions::NORTHWEST:
        return Directions::NORTHEAST;
        break;
    case Directions::SOUTHEAST:
        return Directions::SOUTHWEST;
        break;
    case Directions::SOUTHWEST:
        return Directions::NORTHWEST;
        break;
    }
    return dir;
}

Directions turnMinus90Degress(Directions dir)
{
    switch (dir)
    {
    case Directions::NORTH:
        return Directions::WEST;
        break;
    case Directions::SOUTH:
        return Directions::EAST;
        break;
    case Directions::EAST:
        return Directions::NORTH;
        break;
    case Directions::WEST:
        return Directions::SOUTH;
        break;
    case Directions::NORTHEAST:
        return Directions::NORTHWEST;
        break;
    case Directions::NORTHWEST:
        return Directions::SOUTHWEST;
        break;
    case Directions::SOUTHEAST:
        return Directions::NORTHEAST;
        break;
    case Directions::SOUTHWEST:
        return Directions::SOUTHEAST;
        break;
    }
    return dir;
}