// 2023.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

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
        return { row -1, col + 0 };
        break;
    case Directions::SOUTH:
        return { row + 1, col + 0 };
        break;
    case Directions::EAST:
        return { row + 0, col + 1 };
        break;
    case Directions::WEST:
        return { row + 0, col -1 };
        break;
    case Directions::NORTHEAST:
        return { row -1, col + 1 };
        break;
    case Directions::NORTHWEST:
        return { row -1, col -1 };
        break;
    case Directions::SOUTHEAST:
        return { row + 1, col + 1 };
        break;
    case Directions::SOUTHWEST:
        return { row + 1, col -1 };
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

void day1()
{
    std::vector<string> fileTxt = ReadFile("./input/day1.txt");

    std::vector<int> v1;
    std::vector<int> v2;

    for (auto line : fileTxt)
    {
        auto values = split(line, "   ");
        v1.push_back(atoi(values[0].c_str()));
        v2.push_back(atoi(values[1].c_str()));
    }

    std::sort(v1.begin(), v1.end());
    std::sort(v2.begin(), v2.end());

    int acumA = 0;

    for (int i = 0; i < v1.size(); ++i)
    {
        int diff = abs(v1[i] - v2[i]);
        acumA += diff;
    }

    std::cout << "Day 1 => " << acumA << "\n";

    std::map<int, int> countElementsB;

    for (auto elem : v2)
    {
        if (countElementsB.find(elem) == countElementsB.end())
        {
            countElementsB[elem] = 0;
        }

        countElementsB[elem]++;
    }

    int acumB = 0;
    for (auto elem : v1)
    {
        if (countElementsB.find(elem) != countElementsB.end())
        {
            int value = elem * countElementsB[elem];
            acumB += value;
        }
    }

    std::cout << "Day 1_B => " << acumB << "\n";

}

bool day2_checkList(std::vector<int>& list, int& indexIncorect)
{
    int v1 = list[0];
    int v2 = list[1];

    bool goingUp = v2 > v1;

    bool valid = true;
    for (int i = 1; i < list.size(); ++i)
    {
        int prev = list[i - 1];
        int curr = list[i];

        int diff = abs(curr - prev);

        if (diff <= 0 || diff > 3)
        {
            indexIncorect = i;
            return false;
        }

        bool currentSig = curr > prev;
        if (currentSig != goingUp)
        {
            indexIncorect = i;
            return false;
        }
    }
    return true;
}

void day2()
{
    std::vector<string> fileTxt = ReadFile("./input/day2.txt");

    int countA = 0;

    std::vector<std::vector<int>> unsafeList;
    std::vector<int> indexesIncorrect;

    for (auto line : fileTxt)
    {
        auto numbers = split(line, " ");

        std::vector<int> elemList;

        for (auto x : numbers)
        {
            elemList.push_back(atoi(x.c_str()));
        }

        int indexIncorrect = -1;
        bool valid = day2_checkList(elemList, indexIncorrect);
       
        if (valid)
        {
            countA++;
        }
        else
        {
            unsafeList.push_back(elemList);
            indexesIncorrect.push_back(indexIncorrect);
        }
    }

    std::cout << "Day 2 => " << countA << "\n";

    int countB = 0;
    for (int i = 0; i < indexesIncorrect.size(); ++i)
    {
        int indexIncorrect = indexesIncorrect[i];
        auto elems_0 = unsafeList[i];
        auto elems_i_1 = unsafeList[i];
        auto elems_i = unsafeList[i];

        elems_0.erase(elems_0.begin());//in case the sign is incorrect
        elems_i_1.erase(elems_i_1.begin() + indexIncorrect -1);//remove the previous one, in case is incorrect
        elems_i.erase(elems_i.begin() + indexIncorrect);//remove where we detect the error, in case is incorrect

        int notNeeded = -1;
        bool valid_0 = day2_checkList(elems_0, notNeeded);
        bool valid_i_1 = day2_checkList(elems_i_1, notNeeded);
        bool valid_i = day2_checkList(elems_i, notNeeded);
        if (valid_0 || valid_i_1 || valid_i)
        {
            countB++;
        }
    }

    std::cout << "Day 2_B => " << countA + countB << "\n";

}

std::vector<int> day3_getPositions(const std::string& txt, const std::string& reg)
{
    std::vector<int> positions;
    
    std::regex dontRegex(reg);
    auto dont_begin = std::sregex_iterator(txt.begin(), txt.end(), dontRegex);
    auto dont_end = std::sregex_iterator();

    for (std::sregex_iterator i = dont_begin; i != dont_end; ++i)
    {
        std::smatch mul = *i;

        std::string mul_str = mul.str();
        positions.push_back(mul.position());
    }
    
    return positions;
}

bool day3_getValid(int currentPosition, const std::vector<int>& valid, const std::vector<int>& invalid)
{
    int indexValid = -1;
    int indexInvalid = -1;

    for (int i = 0; i < valid.size(); ++i)
    {
        if (valid[i] > currentPosition)
        {
            break;
        }
        indexValid = i;
    }

    for (int i = 0; i < invalid.size(); ++i)
    {
        if (invalid[i] > currentPosition)
        {
            break;
        }
        indexInvalid = i;
    }

    if (indexValid == -1 && indexInvalid == -1)
    {
        return true;
    }

    if (indexValid != -1 && indexInvalid == -1)
    {
        return true;
    }

    if (indexValid == -1 && indexInvalid != -1)
    {
        return false;
    }

    if (valid[indexValid] > invalid[indexInvalid])
    {
        return true;
    }
    return false;
}

void day3()
{
    std::vector<string> fileTxt = ReadFile("./input/day3.txt");

    int valueA = 0;
    int valueB = 0;


    std::string regexA = "(mul\\(\\d{1,3}\\,\\d{1,3}\\))";

    std::string textWithotLines = "";

    for (auto line : fileTxt)
    {
        textWithotLines += line;
    }

    auto positionsDont = day3_getPositions(textWithotLines, "(don't\\(\\))");
    auto positionsDo = day3_getPositions(textWithotLines, "(do\\(\\))");

    std::regex mul_regex(regexA);
    auto mul_begin = std::sregex_iterator(textWithotLines.begin(), textWithotLines.end(), mul_regex);
    auto mul_end = std::sregex_iterator();

    for (std::sregex_iterator i = mul_begin; i != mul_end; ++i)
    {
        std::smatch mul = *i;
        std::string mul_str = mul.str();
            
        std::regex numbersRegex("(\\d{1,3})\\,(\\d{1,3})");
        std::smatch sm;

        std::regex_search(mul_str, sm, numbersRegex);
        int num1 = atoi(sm.str(1).c_str());
        int num2 = atoi(sm.str(2).c_str());
        int toAdd = num1 * num2;

        valueA += toAdd;


        int mulPosition = mul.position();

        if (day3_getValid(mulPosition, positionsDo, positionsDont))
        {
            valueB += toAdd;
        }
    }
    
    std::cout << "Day 3 => " << valueA << "\n";
    std::cout << "Day 3_B => " << valueB << "\n";

    


}

bool day4_findWord( const std::vector<string>& board, int row, int col, const std::string& word, Directions dir, int width, int height)
{
    int index = 0;

    int currentRow = row;
    int currentCol = col;

    while (index < word.size())
    {
        if (!insideField(currentRow, currentCol, width, height))
        {
            return false;
        }

        if (board[currentRow][currentCol] != word[index]) { return false; }

        auto nextPosition = getNextPosition(currentRow, currentCol, dir);
        currentRow = nextPosition.first;
        currentCol = nextPosition.second;
        ++index;
    }

    return true;
}

bool day4_findCrossMAS(const std::vector<string>& board, int row, int col, int width, int height)
{
    if (board[row][col] != 'A') { return false; }
    auto northWest = getNextPosition(row, col, Directions::NORTHWEST);
    auto northEast = getNextPosition(row, col, Directions::NORTHEAST);
    auto southWest = getNextPosition(row, col, Directions::SOUTHWEST);
    auto southEast = getNextPosition(row, col, Directions::SOUTHEAST);

    if (!insideField(northEast, width, height)) { return false; }
    if (!insideField(northWest, width, height)) { return false; }
    if (!insideField(southEast, width, height)) { return false; }
    if (!insideField(southWest, width, height)) { return false; }

    bool firstCross =   (board[northWest.first][northWest.second] == 'M' && board[southEast.first][southEast.second] == 'S') || (board[northWest.first][northWest.second] == 'S' && board[southEast.first][southEast.second] == 'M');

    bool secondCross = (board[northEast.first][northEast.second] == 'M' && board[southWest.first][southWest.second] == 'S') || (board[northEast.first][northEast.second] == 'S' && board[southWest.first][southWest.second] == 'M');

    return firstCross && secondCross;
}

void day4()
{
    std::vector<string> fileTxt = ReadFile("./input/day4.txt");

    int countA = 0;
    int countB = 0;
    int width = fileTxt[0].size();
    int height = fileTxt.size();
    const std::string word = "XMAS";

    for (int row = 0; row < height; ++row)
    {
        for (int col = 0; col < width; ++col)
        {
            countA += day4_findWord(fileTxt, row, col, word, Directions::NORTH, width, height) ? 1: 0;
            countA += day4_findWord(fileTxt, row, col, word, Directions::SOUTH, width, height) ? 1: 0;
            countA += day4_findWord(fileTxt, row, col, word, Directions::EAST, width, height) ? 1: 0;
            countA += day4_findWord(fileTxt, row, col, word, Directions::WEST, width, height) ? 1: 0;
            countA += day4_findWord(fileTxt, row, col, word, Directions::NORTHEAST, width, height) ? 1: 0;
            countA += day4_findWord(fileTxt, row, col, word, Directions::NORTHWEST, width, height) ? 1: 0;
            countA += day4_findWord(fileTxt, row, col, word, Directions::SOUTHEAST, width, height) ? 1: 0;
            countA += day4_findWord(fileTxt, row, col, word, Directions::SOUTHWEST, width, height) ? 1: 0;

            countB += day4_findCrossMAS(fileTxt, row, col, width, height) ? 1 : 0;
        }
    }
    std::cout << "day 4 => " << countA << "\n";
    std::cout << "day4 B => " << countB << "\n";

}

bool day5_valid(const std::vector<std::string>& values, std::map<std::string, std::set<std::string>>& nextValues, int& incorrectIndex)
{
    std::set<std::string> currentPrecedences;
    bool valid = true;
    for(int i = 0; i < values.size(); ++i)
    {
        std::string v = values[i];
        std::set<std::string> unionSet;
        auto forbiddenValues = nextValues[v];
        set_intersection(currentPrecedences.begin(), currentPrecedences.end(), forbiddenValues.begin(), forbiddenValues.end(), std::inserter(unionSet, unionSet.begin()));
        currentPrecedences.insert(v);

        if (unionSet.size() != 0)
        {
            incorrectIndex = i;
            return false;
        }
    }

    return true;
}


int day5_fixLine(const string& list, std::map<std::string, std::set<std::string>>& nextValues, std::map<std::string, std::set<std::string>>& prevValues)
{
    auto values = split(list, ",");

    int incorrectIndex = -1;
    while (!day5_valid(values, nextValues, incorrectIndex))
    {
        std::string v = values[incorrectIndex];
        values.erase(values.begin() + incorrectIndex);

        //bubble sort
        values.insert(values.begin() + incorrectIndex - 1, v);
    }

    int halfIndex = values.size() / 2;
    int value = atoi(values[halfIndex].c_str());
    return value;
}

void day5(bool calculateB)
{
    std::vector<string> fileTxt = ReadFile("./input/day5.txt");

    std::map<std::string, std::set<std::string>> nextValues;
    std::map<std::string, std::set<std::string>> prevValues;

    int index = 0;
    for (index = 0; index < fileTxt.size(); ++index)
    {
        std::string line = fileTxt[index];
        if (line.empty()) { break; }

        auto values = split(line, "|");
        string v0 = trim_copy(values[0]);
        string v1 = trim_copy(values[1]);

        nextValues[v0].insert(v1);

        prevValues[v1].insert(v0);
    }

    ++index;

    int valueA = 0;

    std::vector<string> incorrectValues;

    while (index < fileTxt.size())
    {
        std::string line = fileTxt[index];

        auto values = split(line, ",");

        int notUsed = -1;
        bool valid = day5_valid(values, nextValues, notUsed);

        if (valid)
        {
            int halfIndex = values.size() / 2;
            int value = atoi(values[halfIndex].c_str());
            valueA += value;
        }
        else
        {
            incorrectValues.push_back(line);
        }
        ++index;
    }

    std::cout << "day 5 => " << valueA << "\n";

    int valueB = 0;
    if (calculateB)
    {
        for (auto incorrect : incorrectValues)
        {
            auto value = day5_fixLine(incorrect, nextValues, prevValues);
            valueB += value;
        }
    }
    else
    {
        valueB = 5479;
    }

    std::cout << "day5_b => " << valueB << "\n";
}

std::pair<int, int> day6_getStart(const std::vector<string>& board)
{
    for (int row = 0; row < board.size(); ++row)
    {
        for (int col = 0; col < board[0].size(); ++col)
        {
            if (board[row][col] == '^')
            {
                return { row, col };
            }
        }
    }
    return { -1,-1 };
}


bool day6_searchPath(const std::vector<string>& board, const int width, const int height, const int startRow, const int startCol, bool stopOnLoops, std::vector<std::vector<bool>>& usedTiles)
{
    int currentRow = startRow;
    int currentCol = startCol;
    Directions currentDir = Directions::NORTH;

    usedTiles = std::vector<std::vector<bool>>(height, std::vector<bool>(width, false));

    std::vector<std::vector<std::set<Directions>>> loopDetector(height, std::vector(width, std::set<Directions>()));

    while (true)
    {
        if (!insideField(currentRow, currentCol, width, height))
        {
            break;
        }

        // detect loop
        if (loopDetector[currentRow][currentCol].contains(currentDir) && stopOnLoops)
        {
            return false;
        }

        usedTiles[currentRow][currentCol] = true;
        loopDetector[currentRow][currentCol].insert(currentDir);

        //get next position
        auto nextPosition = getNextPosition(currentRow, currentCol, currentDir);

        auto originalDir = currentDir;
        while (insideField(nextPosition, width, height) && board[nextPosition.first][nextPosition.second] == '#')
        {
            //change dir
            currentDir = turn90Degress(currentDir);
            nextPosition = getNextPosition(currentRow, currentCol, currentDir);

            if (originalDir == currentDir)
            {
                //weird case
                return false;
            }
        }

        currentRow = nextPosition.first;
        currentCol = nextPosition.second;
    }

    return true;
}

void day6A(std::vector<std::vector<bool>>& usedTiles, const int width, const int height)
{
    int countA = 0;

    for (int row = 0; row < height; ++row)
    {
        for (int col = 0; col < width; ++col)
        {
            countA += usedTiles[row][col] ? 1 : 0;
        }
    }
    std::cout << "day 6 => " << countA << "\n";
}

void day6B(const std::vector<string>& board, const int width, const int height, const int startRow, const int startCol, std::vector<std::vector<bool>>& usedTiles)
{
    std::vector<std::vector<bool>> notUsed;

    int countB = 0;

    for (int row = 0; row < height; ++row)
    {
        for (int col = 0; col < width; ++col)
        {
            if (row == startRow && col == startCol)
            {
                continue;
            }

            if (usedTiles[row][col])
            {
                //TODO: OPTIMIZATION: NOT CREATE NEW VECTORS, UPDATE OBJECTIVE AND RESTORE AT THE END
                std::vector<string> copyBoard = board;
                copyBoard[row][col] = '#';

                if (!day6_searchPath(copyBoard, width, height, startRow, startCol, true, notUsed))
                {
                    countB++;
                }
            }
        }
    }

    std::cout << "day 6_B => " << countB << "\n";
}

void day6(bool resolvePartB)
{
    std::vector<string> board = ReadFile("./input/day6.txt");

    int width = board[0].size();
    int height = board.size();

    auto startPosition = day6_getStart(board);

    std::vector<std::vector<bool>> usedTiles;
    day6_searchPath(board, width, height, startPosition.first, startPosition.second, false, usedTiles);

    day6A(usedTiles, width, height);

    if (resolvePartB)
    {
        day6B(board, width, height, startPosition.first, startPosition.second, usedTiles);
    }
    else
    {
        std::cout << "day 6_B => " << 2143 << "\n";
    }
}

bool day7_calulate(unsigned long long objective, const std::vector<unsigned long long>& values, bool calculateB)
{
    if (values.size() == 0) { return false; }

    if (values.size() == 1)
    {
        return objective == values[0];
    }

    //TODO: OPTIMIZATION: NOT CREATE NEW VECTORS, UPDATE OBJECTIVE AND RESTORE AT THE END
    auto copyValues = values;
    auto v1 = values[0];
    auto  v2 = values[1];

    copyValues.erase(copyValues.begin());
    copyValues.erase(copyValues.begin());

    auto copyValuesAdd = copyValues;
    auto add = v1 + v2;
    copyValuesAdd.insert(copyValuesAdd.begin(), add);

    bool solution = day7_calulate(objective, copyValuesAdd, calculateB);
    if (!solution)
    {
        auto copyValuesMult = copyValues;
        auto mult = v1 * v2;
        copyValuesMult.insert(copyValuesMult.begin(), mult);
        solution = day7_calulate(objective, copyValuesMult, calculateB);
    }

    if (calculateB && !solution)
    {
        auto copyValuesConcat = copyValues;
        string v1_str = std::to_string(v1);
        string v2_str = std::to_string(v2);
        auto concat = stoull((v1_str + v2_str).c_str());
        copyValuesConcat.insert(copyValuesConcat.begin(), concat);

        solution = day7_calulate(objective, copyValuesConcat, calculateB);
    }

    return solution;
}

void day7()
{
    std::vector<string> fileTxt = ReadFile("./input/day7.txt");

    long long valueA = 0;
    long long valueB = 0;
    for (auto line : fileTxt)
    {
        //string line = "3794488742: 949 7 425 5 84 8 211 2";
        std::vector<unsigned long long> params;
        auto split_1 = split(line, ":");
        unsigned long long objective = stoull(split_1[0].c_str());

        auto split_2 = split(split_1[1], " ");
        for (auto v : split_2)
        {
            if (!v.empty())
            {
                params.push_back(stoull(v.c_str()));
            }
        }

        if (day7_calulate(objective, params, false))
        {
            valueA += objective;
        }
        else
        {
            if (day7_calulate(objective, params, true))
            {
                valueB += objective;
            }
        }
    }

    std::cout << "day7 => " << valueA << "\n";
    std::cout << "day7_B => " << (valueA + valueB) << "\n";
}

std::map<char, std::vector<pair<int, int>>> day8_getLocations(const vector<string>& board, int width, int height)
{
    std::map<char, std::vector<pair<int, int>>> locations;
    for (int row = 0; row < height; ++row)
    {
        for (int col = 0; col < width; ++col)
        {
            if (board[row][col] != '.')
            {
                locations[board[row][col]].push_back({ row, col });
            }
        }
    }

    return locations;
}

std::vector<std::pair<int, int>> day8_getAllAntinodes(int startRow, int startCol, int rowIncrement, int colIncrement, int width, int height)
{
    std::vector<std::pair<int, int>> solution;

    int currentRow = startRow + rowIncrement;
    int currentCol = startCol + colIncrement;

    while (insideField(currentRow, currentCol, width, height))
    {
        solution.push_back({ currentRow, currentCol });
        currentRow += rowIncrement;
        currentCol += colIncrement;
    }

    return solution;
}

std::vector<std::pair<int, int>> day8_getAntinodes(const std::pair<int, int>& node1, const std::pair<int, int>& node2, int width, int height, bool partB)
{
    std::vector<std::pair<int, int>> solution;

    std::pair<int, int> n1 = node1;
    std::pair<int, int> n2 = node2;

    if (n1.first > n2.second)
    {
        n1 = node2;
        n2 = node1;
    }

    int diffHeight = n2.first - n1.first;

    int diffWidth = n2.second - n1.second;
    int diffWidthAbs = abs(diffWidth);

    if(diffWidth < 0)
    {
        //this means:
        //....n1
        //n2....
        if (!partB)
        {
            solution.push_back({ n1.first - diffHeight, n1.second + diffWidthAbs });//top right
            solution.push_back({ n2.first + diffHeight, n2.second - diffWidthAbs });//bottom left
        }
        else
        {
            auto allTopRight = day8_getAllAntinodes(n1.first, n2.second, -diffHeight, diffWidthAbs, width, height);

            auto allBottomLeft = day8_getAllAntinodes(n1.first, n2.second, diffHeight, -diffWidthAbs, width, height);

            for (auto pos : allTopRight)
            {
                solution.push_back(pos);
            }

            for (auto pos : allBottomLeft)
            {
                solution.push_back(pos);
            }
        }
    }
    else
    {
        //this means:
        //n1....
        //....n2
        if (!partB)
        {
            solution.push_back({ n1.first - diffHeight, n1.second - diffWidthAbs });//top left
            solution.push_back({ n2.first + diffHeight, n2.second + diffWidthAbs });//bottom right
        }
        else
        {
            auto allTopLeft = day8_getAllAntinodes(n1.first, n2.second, -diffHeight, diffWidthAbs, width, height);

            auto allBottomRight = day8_getAllAntinodes(n1.first, n2.second, diffHeight, diffWidthAbs, width, height);

            for (auto pos : allTopLeft)
            {
                solution.push_back(pos);
            }

            for (auto pos : allBottomRight)
            {
                solution.push_back(pos);
            }
        }
    }

    return solution;
}

std::set<pair<int, int>> day8_calculate(const vector<string>& board, const std::map<char, std::vector<pair<int, int>>>& locations, int width, int height, bool partB)
{
    std::set<pair<int, int>> solution;
    for (auto kvp : locations)
    {
        auto key = kvp.first;
        auto positions = kvp.second;

        for (int index1 = 0; index1 < positions.size(); ++index1)
        {
            for (int index2 = index1 + 1; index2 < positions.size(); ++index2)
            {
                auto antinodes = day8_getAntinodes(positions[index1], positions[index2], width, height, partB);

                for(auto antinode:antinodes)
                {
                    if (insideField(antinode, width, height) /* && board[antinode.first][antinode.second] == '.'*/)
                    {
                        solution.insert(antinode);
                    }
                }

            }
        }
    }

    return solution;
}

void day8()
{
    std::vector<string> board = ReadFile("./input/day8.txt");
    int width = board[0].size();
    int height = board.size();

    auto locations = day8_getLocations(board, width, height);

    auto day8A = day8_calculate(board, locations, width, height, false);
    auto day8B = day8_calculate(board, locations, width, height, true);

    std::cout << "day 8 => " << day8A.size() << "\n";
    std::cout << "day 8_B => " << day8B.size() << "\n";
}

struct day9_file
{
    int id;
    int start;
    int size;
    bool moved = false;
};

int day9_GetFirstWidthSize(const std::vector<day9_file>& spaces, int size)
{
    for (int i = 0; i < spaces.size(); ++i)
    {
        if (spaces[i].size >= size)
        {
            return i;
        }
    }
    return -1;
}

void day9_Calculate(std::vector<day9_file>& files, std::vector<day9_file>& spaces)
{
    for (int i = files.size() - 1; i >= 0; --i)
    {
        auto&& file = files[i];
        if (file.moved) { continue; }

        int spaceID = day9_GetFirstWidthSize(spaces, file.size);
        if (spaceID == -1) { continue; }

        auto&& space = spaces[spaceID];

        if (space.start > file.start) { continue; }

        file.moved = true;
        file.start = space.start;
        if (space.size == file.size)
        {
            spaces.erase(spaces.begin() + spaceID);
        }
        else
        {
            file.moved = true;
            file.start = space.start;
            space.start = space.start + file.size;
            space.size -= file.size;
        }
    }
}

void day9()
{
    string input = ReadFile("./input/day9.txt")[0];

    std::vector<day9_file> filesPositions;
    std::vector<day9_file> spaces;
    std::vector<day9_file> filesAsUnities;

    bool data = true;
    int id = 0;
    int currentStart = 0;
    for (auto c : input)
    {
        int value = c - '0';

        day9_file f;
        f.id = data ? id : -1;
        f.start = currentStart;
        f.size = value;

        if (data) { filesPositions.push_back(f); }
        else { spaces.push_back(f); }

        if (data)
        {
            for (int i = 0; i < value; ++i)
            {
                day9_file f;
                f.id = data ? id : -1;
                f.start = currentStart + i;
                f.size = 1;
                filesAsUnities.push_back(f);
            }
        }

        currentStart += value;
        data = !data;
        if (!data)
        {
            ++id;
        }
    }

    auto spacesCopy = spaces;
    day9_Calculate(filesAsUnities, spacesCopy);
    day9_Calculate(filesPositions, spaces);

    long long acumB = 0;
    for (auto file : filesPositions)
    {
        int start = file.start;
        int id = file.id;

        for (int i = start; i < start + file.size; ++i)
        {
            acumB += (id * i);
        }
    }

    long long acumA = 0;
    for (auto file : filesAsUnities)
    {
        int start = file.start;
        int id = file.id;

        for (int i = start; i < start + file.size; ++i)
        {
            acumA += (id * i);
        }
    }
    std::cout << "day9 => " << acumA << "\n";
    std::cout << "day9_B => " << acumB << "\n";
}

struct day10_Coord
{
    int row;
    int col;

    int startRow;
    int startCol;
};

void day10_Calculate(const std::vector<string>& board, std::vector<day10_Coord> startPoints, int width, int height)
{
    int countB = 0;

    std::set<string> paths;

    while (startPoints.size() != 0)
    {
        auto position = startPoints[0];
        startPoints.erase(startPoints.begin());

        if (!insideField(position.row, position.col, width, height)) { continue; }

        if (board[position.row][position.col] == '9')
        {
            ++countB;

            std::string path = std::to_string(position.startRow) + "," + std::to_string(position.startCol) + "=>" + std::to_string(position.row) + "," + std::to_string(position.col);

            paths.insert(path);
        }
        auto currentValue = board[position.row][position.col];

        for (auto dir : { Directions::NORTH, Directions::EAST, Directions::SOUTH, Directions::WEST })
        {
            auto nextPosition = getNextPosition(position.row, position.col, dir);
            if (!insideField(nextPosition, width, height)) { continue; }

            int nextValue = board[nextPosition.first][nextPosition.second];
            if (nextValue == '.') { continue; }

            int diff = nextValue - currentValue;
            if (diff == 1)
            {
                day10_Coord c(nextPosition.first, nextPosition.second, position.startRow, position.startCol);
                startPoints.push_back(c);
            }
        }
    }

    std::cout << "day 10 => " << paths.size() << "\n";
    std::cout << "day 10_ B => " << countB << "\n";
}

void day10()
{
    auto board = ReadFile("./input/day10.txt");

    int width = board[0].size();
    int height = board.size();

    std::vector<day10_Coord> positionsToAnalyze;

    for (int row = 0; row < height; ++row)
    {
        for (int col = 0; col < width; ++col)
        {
            if (board[row][col] == '0')
            {
                day10_Coord c(row, col, row, col);
                positionsToAnalyze.push_back(c);
            }
        }
    }
    day10_Calculate(board, positionsToAnalyze, width, height);
}

std::vector<long long> day11_calculate(long long input, map<long long, vector<long long>>& cacheIndiviual)
{
    if (cacheIndiviual.find(input) != cacheIndiviual.end())
    {
        return cacheIndiviual[input];
    }

    if (input == 0)
    {
        cacheIndiviual[input] = { 1 };
        return { 1 };
    }

    int numDigits = log10(input) + 1;
    if (numDigits % 2 == 0)
    {
        int numToUse = pow(10, numDigits / 2);
        auto left = input / numToUse;
        auto right = input % numToUse;
        cacheIndiviual[input] = { left, right };
        return cacheIndiviual[input];
    }

    cacheIndiviual[input] = { input * 2024 };
    return cacheIndiviual[input];
}

vector<long long> day11_calculateMultiple(long long input, int times, map<string, vector<long long>>& cacheMultiple, map<long long, vector<long long>>& cacheIndiviual)
{
    if(times == 0)
    {
        return {input};
    }

    string key = std::to_string(input) + "-" + std::to_string(times);

    if (cacheMultiple.find(key)!= cacheMultiple.end())
    {
        return cacheMultiple[key];
    }

    auto firstUse = day11_calculate(input, cacheIndiviual);

    std::vector<long long> result;

    for (auto elem : firstUse)
    {
        auto res = day11_calculateMultiple(elem, times - 1, cacheMultiple, cacheIndiviual);
        result.insert(result.end(), res.begin(), res.end());
    }

    cacheMultiple[key] = result;
    return result;
}

void day11_a()
{
    auto input_txt = ReadFile("./input/day11.txt")[0];
    auto input = split(input_txt, " ");

    map<string, vector<long long>> cacheMultiple;
    map<long long, vector<long long>> cacheIndiviual;

    std::vector<long long> resultA;

    for (auto elem : input)
    {
        long long value = stoll(elem.c_str());
        auto res = day11_calculateMultiple(value, 25, cacheMultiple, cacheIndiviual);
        resultA.insert(resultA.end(), res.begin(), res.end());
    }
    std::cout << "day 11 => " << resultA.size() << "\n";
}


void day11_b()
{
    auto input_txt = ReadFile("./input/day11.txt")[0];
    auto input = split(input_txt, " ");

    std::map<long long, unsigned long long> totalAppears;
    for (auto i : input)
    {
        long long key = stoll(i);
        totalAppears[key]++;
    }

    int totalTimes = 75;

    for (int i = 0; i < totalTimes; ++i)
    {
        std::map<long long, unsigned long long> currentAppears;

        for (auto kvp : totalAppears)
        {
            auto key = kvp.first;
            auto times = kvp.second;

            if (key == 0)
            {
                currentAppears[1] += times;
                continue;
            }

            int numDigits = log10(key) + 1;
            if (numDigits % 2 == 0)
            {
                int numToUse = pow(10, numDigits / 2);
                auto left = key / numToUse;
                auto right = key % numToUse;

                currentAppears[left] += times;
                currentAppears[right] += times;
                continue;
            }

            currentAppears[key * 2024] += times;
        }

        totalAppears = currentAppears;
    }

    unsigned long long resultB = 0;
    for (auto kvp : totalAppears)
    {
        resultB += kvp.second;
    }
    std::cout << "day 11_B => " << resultB << "\n";

}

void day11()
{
    day11_a();
    day11_b();
}

std::vector<std::pair<int, int>> day12_calculateShape(int row, int col, const std::vector<string>& board, std::vector<std::vector<bool>>& visited, int width, int height)
{
    if (visited[row][col])
    {
        return {};
    }

    std::vector<pair<int, int>> shape;
    std::vector<pair<int, int>> toVisit;
    toVisit.push_back({ row, col });
    char shapeChar = board[row][col];

    while (!toVisit.empty())
    {
        auto node = toVisit[0];
        int row = node.first;
        int col = node.second;


        toVisit.erase(toVisit.begin());
        if (visited[node.first][node.second]) { continue; }
        shape.push_back(node);
        visited[node.first][node.second] = true;

        for (Directions dir : {Directions::NORTH, Directions::EAST, Directions::SOUTH, Directions::WEST})
        {
            auto neightbour = getNextPosition(node.first, node.second, dir);
           
            if (insideField(neightbour, width, height) 
                && board[neightbour.first][neightbour.second] == shapeChar
                && !visited[neightbour.first][neightbour.second])
            {
                toVisit.push_back(neightbour);
            }
        }
    }

    return shape;
}

int day12_getPerimeterPartA(const std::vector<pair<int, int>>& shape, const std::vector<string>& board, const int width, const int height)
{
    int countA = 0;

    for (auto pos : shape)
    {
        for (Directions dir : {Directions::NORTH, Directions::EAST, Directions::SOUTH, Directions::WEST})
        {
            auto neightbour = getNextPosition(pos.first, pos.second, dir);
            if (!insideField(neightbour, width, height) || board[pos.first][pos.second] != board[neightbour.first][neightbour.second])
            {
                ++countA;
            }

        }
    }

    return countA;
}

pair<int, int> day12_getTopLeftNode(const std::vector<pair<int, int>>& shape)
{
    auto topLeftNode = shape[0];

    for (auto&& s : shape)
    {
        if (topLeftNode.first < s.first)
        {
            continue;
        }

        if (topLeftNode.second < s.second)
        {
            continue;
        }
        topLeftNode = s;
    }

    return topLeftNode;
}

void day12_calculatePerimeterBTopDown(const std::vector<string>& board, std::vector<std::vector<int>>& shapeIdx,
    std::map<int, int>& acumPerimeters, const int width, const int height, Directions dirToCheck)
{
    for (int row = 0; row < height; ++row)
    {
        char lastValue = board[row][0];
        auto previousPositionFirst = getNextPosition(row, 0, dirToCheck);
        bool lastValid = !insideField(previousPositionFirst, width, height) || board[previousPositionFirst.first][previousPositionFirst.second] != lastValue;

        for (int col = 1; col < width; ++col)
        {
            char currentValue = board[row][col];
            auto previousPosition = getNextPosition(row, col, dirToCheck);
            bool currentValid = !insideField(previousPosition, width, height) || board[previousPosition.first][previousPosition.second] != currentValue;

            if (lastValue != currentValue || lastValid != currentValid)
            {
                if (lastValid)
                {
                    int id = shapeIdx[row][col - 1];
                    acumPerimeters[id]++;
                }
            }

            lastValue = currentValue;
            lastValid = currentValid;
        }

        if (lastValid)
        {
            int id = shapeIdx[row][width - 1];
            acumPerimeters[id]++;
        }
    }
}

void day12_calculatePerimeterBLeftRight(const std::vector<string>& board, std::vector<std::vector<int>>& shapeIdx,
    std::map<int, int>& acumPerimeters, const int width, const int height, Directions dirToCheck)
{
    for (int col = 0; col < width; ++col)
    {
        char lastValue = board[0][col];
        auto previousPositionFirst = getNextPosition(0, col, dirToCheck);
        bool lastValid = !insideField(previousPositionFirst, width, height) || board[previousPositionFirst.first][previousPositionFirst.second] != lastValue;

        for (int row = 1; row < height; ++row)
        {
            char currentValue = board[row][col];
            auto previousPosition = getNextPosition(row, col, dirToCheck);
            bool currentValid = !insideField(previousPosition, width, height) || board[previousPosition.first][previousPosition.second] != currentValue;

            if (lastValue != currentValue || lastValid != currentValid)
            {
                if (lastValid)
                {
                    int id = shapeIdx[row - 1][col];
                    acumPerimeters[id]++;
                }
            }

            lastValue = currentValue;
            lastValid = currentValid;
        }

        if (lastValid)
        {
            int id = shapeIdx[height -1][col];
            acumPerimeters[id]++;
        }
    }
}
int calculateExternalPerimeter (const std::vector<pair<int, int>>& shape, const std::vector<string>& board, const int width, const int height, std::map<int, int>& acumPerimeters, std::vector<std::vector<int>>& shapeIdx)
{
    auto topLeft = day12_getTopLeftNode(shape);
    Directions currentDir = Directions::EAST;
    char shapeLetter = board[topLeft.first][topLeft.second];

    auto currentPosition = topLeft;

    int currentCount = 0;
    bool firstTime = false;

    bool continueCalculating = true;

    std::set<int> differentLetter;

    while (continueCalculating)
    {
        //if -90 is same type as mine => add 1 to the perimeter, move pointer and update dir
        //else => just update the currentPosition
        auto minus90Direction = turnMinus90Degress(currentDir);
        auto minus90Position = getNextPosition(currentPosition.first, currentPosition.second, minus90Direction);

        if (insideField(minus90Position, width, height) && board[minus90Position.first][minus90Position.second] == shapeLetter)
        {
            //esquina
            ++currentCount;
            currentDir = minus90Direction;
            currentPosition = minus90Position;
            if (currentPosition == topLeft && currentDir == Directions::EAST)
            {
                continueCalculating = false;
            }
            continue;
        }

        //if here, the top is empty or other, so we need to check the turn
        auto nextPosition = getNextPosition(currentPosition.first, currentPosition.second, currentDir);

        if (!insideField(nextPosition, width, height) || board[nextPosition.first][nextPosition.second] != shapeLetter)
        {
            //normal turn
            ++currentCount;
            currentDir = turn90Degress(currentDir);

            if (insideField(nextPosition, width, height))
            {
                int borderShape = shapeIdx[nextPosition.first][nextPosition.second];
                differentLetter.insert(borderShape);
            }
            else
            {
                differentLetter.insert(-1);
            }

            if (currentPosition == topLeft && currentDir == Directions::EAST)
            {
                continueCalculating = false;
            }
            //maybe not need to update
            continue;
        }

        currentPosition = nextPosition;
        if (currentPosition == topLeft && currentDir == Directions::EAST)
        {
            continueCalculating = false;
        }
    } 

    if (differentLetter.size() == 1)
    {
        int id = *(differentLetter.begin());
        acumPerimeters[id] += currentCount;
    }

    return currentCount;
}

void day12()
{
    auto board = ReadFile("./input/day12.txt");
    int width = board[0].size();
    int height = board.size();

    std::vector<std::vector<bool>> visited(height, std::vector<bool>(width, false));

    std::vector<std::vector<pair<int, int>>> shapes;

    for (int row = 0; row < height; ++row)
    {
        for (int col = 0; col < width; ++col)
        {
            auto shapeMembers = day12_calculateShape(row, col, board, visited, width, height);
            if (!shapeMembers.empty())
            {
                shapes.push_back(shapeMembers);
            }
        }
    }

    std::vector<std::vector<int>> shapesIdx(height, std::vector<int>(width, -1));
    for (int i = 0; i < shapes.size(); ++i)
    {
        for (auto s : shapes[i])
        {
            shapesIdx[s.first][s.second] = i;
        }
    }
    std::map<int, int> acumPerimetersB;
    day12_calculatePerimeterBTopDown(board, shapesIdx, acumPerimetersB, width, height, Directions::NORTH);
    day12_calculatePerimeterBTopDown(board, shapesIdx, acumPerimetersB, width, height, Directions::SOUTH);

    day12_calculatePerimeterBLeftRight(board, shapesIdx, acumPerimetersB, width, height, Directions::EAST);
    day12_calculatePerimeterBLeftRight(board, shapesIdx, acumPerimetersB, width, height, Directions::WEST);
      

    long long valueA = 0;
    long long valueB = 0;
    for (int i = 0; i < shapes.size(); ++i)
    {
        auto&& shape = shapes[i];
        auto perimeterA = day12_getPerimeterPartA(shape, board, width, height);
        auto perimeterB = acumPerimetersB[i];
        valueA += (shape.size()) * perimeterA;
        valueB += (shape.size()) * perimeterB;

    }

    std::cout << "day 12 => " << valueA << "\n";
    std::cout << "day 12_B => " << valueB << "\n";
}

bool day13_calculate(double BAx, double BAy, double BBx, double BBy, double Px, double Py, unsigned long long& solA, unsigned long long& solB)
{
    double A1 = (Px - (Py * BBx / BBy));
    double A2 = (BAx - (BAy * BBx / BBy));

    double A = A1 / A2;
    double B = (Py - (A * BAy)) / BBy;

    solA = static_cast<unsigned long long>(A);
    solB = static_cast<unsigned long long>(B);

    bool checkX = (BAx * solA + BBx * solB) == Px;
    bool checkY = (BAy * solA + BBy * solB) == Py;

    if (!checkX || !checkY)
    {
        solA = static_cast<unsigned long long>(A + 0.1);
        solB = static_cast<unsigned long long>(B + 0.1);

        checkX = (BAx * solA + BBx * solB) == Px;
        checkY = (BAy * solA + BBy * solB) == Py;
    }

    return checkX && checkY;
}

void day13()
{
    auto fileTxt = ReadFile("./input/day13.txt");

    int line = 0;
    long long acumA = 0;
    long long acumB = 0;

    std::regex buttonsRegex("X\\+(\\d*), Y\\+(\\d*)");
    std::regex solutionRecex("X=(\\d*), Y=(\\d*)");

    while (line < fileTxt.size())
    {
        std::smatch sm;

        std::regex_search(fileTxt[line], sm, buttonsRegex);
        int BAx = atoi(sm.str(1).c_str());
        int BAy = atoi(sm.str(2).c_str());

        std::regex_search(fileTxt[line + 1], sm, buttonsRegex);
        int BBx = atoi(sm.str(1).c_str());
        int BBy = atoi(sm.str(2).c_str());

        std::regex_search(fileTxt[line + 2], sm, solutionRecex);
        unsigned long long Px = stof(sm.str(1).c_str());
        unsigned long long Py = stof(sm.str(2).c_str());

        unsigned long long solA;
        unsigned long long solB;
        if (day13_calculate(BAx, BAy, BBx, BBy, Px, Py, solA, solB))
        {
            acumA += solA * 3 + solB;
        }

        Px += 10000000000000;
        Py += 10000000000000;
        if (day13_calculate(BAx, BAy, BBx, BBy, Px, Py, solA, solB))
        {
            acumB += solA * 3 + solB;
        }

        line += 4;
    }

    std::cout << "day13 => " << acumA << "\n";
    std::cout << "day13_B => " << acumB << "\n";
}

struct day14_robot
{
    int startX;
    int startY;
    int moveX;
    int moveY;
};

int day14_getQuadrantNumber(int startX, int endX, int startY, int endY, const std::map<std::pair<int, int>, int>& positions)
{
    int totalCount = 0;
    for (auto r : positions)
    {
        auto position = r.first;
        auto count = r.second;

        if (position.first >= startX && position.first <= endX &&
            position.second >= startY && position.second <= endY)
        {
            totalCount += count;
        }
    }

    return totalCount;
}

void day14_calculateMovements(int totalMovements, int maxWidth, int maxHeight, const std::vector<day14_robot>& robots)
{
    std::map<std::pair<int, int>, int> robotsInPositions;

    for (auto&& r : robots)
    {
        long long finalX = r.startX + totalMovements * r.moveX;
        long long finalY = r.startY + totalMovements * r.moveY;

        while (finalX < maxWidth)
        {
            finalX += maxWidth;
        }

        while (finalY < maxHeight)
        {
            finalY += maxHeight;
        }

        finalX = finalX % maxWidth;
        finalY = finalY % maxHeight;

        robotsInPositions[{finalX, finalY}]++;
    }

    int halfX_1 = (maxWidth / 2) - 1;
    int halfX_2 = (maxWidth / 2) + 1;

    int halfY_1 = (maxHeight / 2) - 1;
    int halfY_2 = (maxHeight / 2) + 1;

    int q1 = day14_getQuadrantNumber(0, halfX_1, 0, halfY_1, robotsInPositions);
    int q2 = day14_getQuadrantNumber(halfX_2, maxWidth-1, 0, halfY_1, robotsInPositions);
    int q3 = day14_getQuadrantNumber(0, halfX_1, halfY_2, maxHeight-1, robotsInPositions);
    int q4 = day14_getQuadrantNumber(halfX_2, maxWidth - 1, halfY_2, maxHeight - 1, robotsInPositions);


    int valueA = q1 * q2 * q3 * q4;
    std::cout << "day14 => " << valueA << "\n";

}

void day14_doMovement(std::vector<day14_robot>& robots, int maxWidth, int maxHeight)
{
    int totalMovements = 1;
    for (auto& r : robots)
    {
        long long finalX = r.startX + totalMovements * r.moveX;
        long long finalY = r.startY + totalMovements * r.moveY;

        while (finalX < maxWidth)
        {
            finalX += maxWidth;
        }

        while (finalY < maxHeight)
        {
            finalY += maxHeight;
        }

        finalX = finalX % maxWidth;
        finalY = finalY % maxHeight;

        r.startX = finalX;
        r.startY = finalY;
    }
}

void day14_print(const std::vector<day14_robot>& robots, int maxWidth, int maxHeight)
{
    std::set<pair<int, int>> positions;
    for (auto&& r : robots)
    {
        positions.insert({ r.startX, r.startY });
    }

    for (int row = 0; row < maxHeight; ++row)
    {
        for (int col = 0; col < maxWidth; ++col)
        {
            if (positions.find({ col, row }) != positions.end())
            {
                std::cout << "#";
            }
            else
            {
                std::cout << ".";
            }
        }
        std::cout << "\n";
    }
}

void day14_partB(std::vector<day14_robot> robots, int maxWidth, int maxHeight, bool print)
{
    int movementID = 0;
    while (movementID < 8149)
    {
        day14_doMovement(robots, maxWidth, maxHeight);
        ++movementID;
    }

    std::set<pair<int, int>> positions;
    for (auto&& r : robots)
    {
        positions.insert({ r.startX, r.startY });
    }
        
    std::cout << "day 14_B => " << movementID << "\n";
    if (print)
    {
        day14_print(robots, maxWidth, maxHeight);
    }
}

void day14(bool print)
{
    auto fileTxt = ReadFile("./input/day14.txt");

    std::vector<day14_robot> robots;
    std::regex buttonsRegex("p=(-*\\d*),(-*\\d*) v=(-*\\d*),(-*\\d*)");

    for (auto&& l : fileTxt)
    {
        std::smatch sm;
        std::regex_search(l, sm, buttonsRegex);

        day14_robot r(atoi(sm.str(1).c_str()), atoi(sm.str(2).c_str()), atoi(sm.str(3).c_str()), atoi(sm.str(4).c_str()));

        robots.push_back(r);
    }

    int totalMovmement = 100;
    int width = 101;
    int height = 103;

    day14_calculateMovements(totalMovmement, width, height, robots);
    day14_partB(robots, width, height, print);
}

enum class day15_types{EMPTY, WALL, BOX, START_BOX, END_BOX};

void day15_print(const std::vector<std::vector<day15_types>>& board, const std::pair<int, int>& playerPos)
{
    for (int row = 0; row < board.size(); ++row)
    {
        for (int col = 0; col < board[row].size(); ++col)
        {
            auto type = board[row][col];
            std::pair<int, int> pos = { row,col };
            if (playerPos == pos) { std::cout << "@"; continue; }
            if (type == day15_types::EMPTY) { std::cout << "."; }
            if (type == day15_types::BOX) { std::cout << "0"; }
            if (type == day15_types::WALL) { std::cout << "#"; }
            if (type == day15_types::START_BOX) { std::cout << "["; }
            if (type == day15_types::END_BOX) { std::cout << "]"; }
        }
        std::cout << "\n";
    }
    std::cout << "\n";
}

bool day15_calculateBoxChain(std::vector<std::vector<day15_types>>& board, Directions dir, int& row, int& col)
{
    std::set<day15_types> boxTypes = { day15_types::BOX, day15_types::START_BOX, day15_types::END_BOX };
    while (boxTypes.find(board[row][col]) != boxTypes.end())
    {
        auto next = getNextPosition(row, col, dir);
        row = next.first;
        col = next.second;
    }

    if (board[row][col] == day15_types::WALL) { return false; }

    return true;
}

void day15_swapTypeBox(std::vector<std::vector<day15_types>>& board, std::pair<int, int>start, std::pair<int, int> end, Directions dir)
{
    while (start != end)
    {
        if (board[start.first][start.second] == day15_types::START_BOX)
        {
            board[start.first][start.second] = day15_types::END_BOX;
        }
        else
        {
            board[start.first][start.second] = day15_types::START_BOX;
        }
        start = getNextPosition(start.first, start.second, dir);
    }
}

bool day15_canMoveBigBox(std::vector<std::vector<day15_types>>& board, Directions dir, const pair<int, int>& position, day15_types currentType)
{
    if (board[position.first][position.second] == day15_types::WALL)
    {
        return false;
    }

    if (board[position.first][position.second] == day15_types::EMPTY)
    {
        board[position.first][position.second] = currentType;
        return true;
    }

    //if movement is north or south, we need to move the other part of the box
    //if the movement is east or west, just move as allways

    if (dir == Directions::EAST || dir == Directions::WEST)
    {
        auto nextPosition = getNextPosition(position.first, position.second, dir);
        if (day15_canMoveBigBox(board, dir, nextPosition, board[position.first][position.second]))
        {
            if (board[position.first][position.second] == day15_types::START_BOX)
            {
                board[position.first][position.second] = day15_types::END_BOX;
            }
            else
            {
                board[position.first][position.second] = day15_types::START_BOX;
            }
            return true;
        }
        else
        {
            return false;
        }
    }

    //here dir is north or south
    std::pair<int, int> startBox, endBox;
    if (board[position.first][position.second] == day15_types::START_BOX)
    {
        startBox = position;
        endBox = { position.first, position.second + 1 };
    }
    else
    {
        endBox = position;
        startBox = { position.first, position.second - 1 };
    }

    //now check if we can move the both parts.
    auto nextPositionStart = getNextPosition(startBox.first, startBox.second, dir);
    auto nextPositionEnd = getNextPosition(endBox.first, endBox.second, dir);
    bool move1 = (day15_canMoveBigBox(board, dir, nextPositionStart, day15_types::EMPTY));
    bool move2 = (day15_canMoveBigBox(board, dir, nextPositionEnd, day15_types::EMPTY));

    if (move1 && move2)
    {
        //update all the big boxes
        return true;
    }
    else
    {
        return false;
    }
}

void day15_moveUpDownBigBox(std::vector<std::vector<day15_types>>& board, Directions dir, std::pair<int, int> position, day15_types type)
{
    auto nextPosition = getNextPosition(position.first, position.second, dir);
    auto typeDirection = board[nextPosition.first][nextPosition.second];

    if (typeDirection == day15_types::EMPTY)
    {
        board[position.first][position.second] = day15_types::EMPTY;
        board[nextPosition.first][nextPosition.second] = type;
        return;
    }

    if (typeDirection == type)
    {
        //only move one part, as the other part will be moved by the other part
        day15_moveUpDownBigBox(board, dir, nextPosition, typeDirection);
        board[nextPosition.first][nextPosition.second] = type;
        board[position.first][position.second] = day15_types::EMPTY;
        return;
    }

    //here there is another box
    std::pair<int, int> startBox, endBox;
    if (typeDirection == day15_types::START_BOX)
    {
        startBox = nextPosition;
        endBox = { nextPosition.first, nextPosition.second + 1 };
    }
    else
    {
        startBox = { nextPosition.first, nextPosition.second - 1 };
        endBox = nextPosition;
    }
    day15_moveUpDownBigBox(board, dir, startBox, day15_types::START_BOX);
    day15_moveUpDownBigBox(board, dir, endBox, day15_types::END_BOX);

    board[nextPosition.first][nextPosition.second] = type;
    board[position.first][position.second] = day15_types::EMPTY;
}

void day15_updateBoard(std::vector<std::vector<day15_types>>& board, Directions dir, pair<int, int>& playerPos)
{
    auto destiny = getNextPosition(playerPos.first, playerPos.second, dir);

    if (board[destiny.first][destiny.second] == day15_types::WALL) { return; }
    if (board[destiny.first][destiny.second] == day15_types::EMPTY) 
    { 
        playerPos = destiny;
        return;
    }
    if (board[destiny.first][destiny.second] == day15_types::BOX)
    {
        //try to move
        int rowEnd = destiny.first;
        int colEnd = destiny.second;
        if (day15_calculateBoxChain(board, dir, rowEnd, colEnd))
        {
            board[rowEnd][colEnd] = day15_types::BOX;
            board[destiny.first][destiny.second] = day15_types::EMPTY;
            playerPos = destiny;
        }
    }

    if (board[destiny.first][destiny.second] == day15_types::START_BOX || board[destiny.first][destiny.second] == day15_types::END_BOX)
    {
        if(day15_canMoveBigBox(board, dir, destiny, board[destiny.first][destiny.second]))
        {
            if (dir == Directions::NORTH || dir == Directions::SOUTH)
            {
                std::pair<int, int> startBox, endBox;
                if (board[destiny.first][destiny.second] == day15_types::START_BOX)
                {
                    startBox = destiny;
                    endBox = { destiny.first, destiny.second + 1 };
                }
                else
                {
                    endBox = destiny;
                    startBox = { destiny.first, destiny.second - 1 };
                }

                day15_moveUpDownBigBox(board, dir, startBox, day15_types::START_BOX);
                day15_moveUpDownBigBox(board, dir, endBox, day15_types::END_BOX);
                
                board[startBox.first][startBox.second] = day15_types::EMPTY;
                board[endBox.first][endBox.second] = day15_types::EMPTY;
            }
            else
            {
                board[destiny.first][destiny.second] = day15_types::EMPTY;
            }
            playerPos = destiny;
        }
        
    }
}


void day15_updateBoard(std::vector<std::vector<day15_types>>& board, char movement, pair<int, int>& playerPos)
{
    Directions dir = Directions::NORTH;
    switch (movement)
    {
    case '>': dir = Directions::EAST; break;
    case 'v': dir = Directions::SOUTH; break;
    case '^': dir = Directions::NORTH; break;
    case '<': dir = Directions::WEST; break;
    }

    day15_updateBoard(board, dir, playerPos);
}

void day15_doMovements(std::vector<std::vector<day15_types>>& board, const std::string& movements, pair<int, int>& playerPos)
{
    for (auto c : movements)
    {
        day15_updateBoard(board, c, playerPos);
    }
}

int day15_calculate(const std::vector<std::vector<day15_types>>& board)
{
    long long acumA = 0;
    for (int row = 0; row < board.size(); ++row)
    {
        for (int col = 0; col < board[row].size(); ++col)
        {
            if (board[row][col] == day15_types::BOX || board[row][col] == day15_types::START_BOX)
            {
                acumA += (row * 100 + col);
            }
        }
    }
    return acumA;

}

void day15_A()
{
    auto fileTxt = ReadFile("./input/day15.txt");
    std::vector<std::vector<day15_types>> boardA;
    int rowID = 0;

    std::pair<int, int> playerPos;

    while (!fileTxt[rowID].empty())
    {
        std::vector<day15_types> rowA;
        int colID = 0;

        while(colID < fileTxt[rowID].size())
        {
            char c = fileTxt[rowID][colID];
            ++colID;
            if (c == '@') { rowA.push_back(day15_types::EMPTY); playerPos = { rowID, colID -1}; continue; }
            if (c == '#') { rowA.push_back(day15_types::WALL); continue; }
            if (c == 'O') { rowA.push_back(day15_types::BOX); continue; }
            if (c == '.') { rowA.push_back(day15_types::EMPTY); continue; }
        }
        boardA.push_back(rowA);
        ++rowID;
    }

    ++rowID;

    std::string instructions = "";
    while (rowID < fileTxt.size())
    {
        instructions += fileTxt[rowID];
        ++rowID;
    }

    day15_doMovements(boardA, instructions, playerPos);
    int acumA = day15_calculate(boardA);
    std::cout << "day 15 => " << acumA << "\n";

}

void day15_B()
{
    auto fileTxt = ReadFile("./input/day15.txt");
    std::vector<std::vector<day15_types>> board;
    int rowID = 0;

    std::pair<int, int> playerPos;

    while (!fileTxt[rowID].empty())
    {
        std::vector<day15_types> row;
        int colID = 0;

        while (colID < fileTxt[rowID].size())
        {
            char c = fileTxt[rowID][colID];
            ++colID;
            if (c == '@') 
            { 
                row.push_back(day15_types::EMPTY); 
                playerPos = { rowID, row.size()-1}; 
                row.push_back(day15_types::EMPTY);
                continue; 
            }
            if (c == '#') { row.push_back(day15_types::WALL); row.push_back(day15_types::WALL); continue; }
            if (c == 'O') { row.push_back(day15_types::START_BOX); row.push_back(day15_types::END_BOX); continue; }
            if (c == '.') { row.push_back(day15_types::EMPTY); row.push_back(day15_types::EMPTY); continue; }
        }
        board.push_back(row);
        ++rowID;
    }

    ++rowID;

    std::string instructions = "";
    while (rowID < fileTxt.size())
    {
        instructions += fileTxt[rowID];
        ++rowID;
    }

    day15_doMovements(board, instructions, playerPos);
    int acumB = day15_calculate(board);
    std::cout << "day 15_B => " << acumB << "\n";

}

void day15()
{
    day15_A();
    day15_B();
}

struct day16_node
{
    int row;
    int col;
    Directions dir;
    long long currentCost;
    long long manhattan;
    long long stimatedCost;

    std::vector<std::pair<int, int>> ancestors;

    friend bool operator<(const day16_node& a, const day16_node& b)
    {
        return a.stimatedCost > b.stimatedCost;
    }
};

void day16_updateNode(day16_node& node, std::pair<int, int> endPosition)
{
    int height = abs(endPosition.first - node.row);
    int width = abs(endPosition.second - node.col);

    node.manhattan = width + height;
    node.stimatedCost = node.manhattan + node.currentCost;
}

void day16_addAncestor(day16_node& baseNode, day16_node& node, std::pair<int, int> position)
{
    node.ancestors.insert(node.ancestors.end(), baseNode.ancestors.begin(), baseNode.ancestors.end());
    node.ancestors.push_back(position);
}

void day16_print(const std::vector<string>& board, const std::set < std::pair<int, int>>& ancestors)
{
    for (int row = 0; row < board.size(); ++row)
    {
        for (int col = 0; col < board.size(); ++col)
        {
            std::pair<int, int> toSearch = { row, col };
            if (std::find(ancestors.begin(), ancestors.end(), toSearch) != ancestors.end())
            {
                std::cout << "O";
            }
            else
            {
                std::cout << board[row][col];
            }
        }
        std::cout << "\n";
    }

    std::cout << "\n";
}

int day16_calculate(const std::vector<string>& board, int width, int height, std::pair<int, int>& start, const std::pair<int, int>& endPosition, const int increaseForward, const int increaseTurn, Directions startDir, std::set<std::pair<int, int>>& knownPath, bool partA)
{
    day16_node startNode(start.first, start.second, startDir, 0);
    day16_updateNode(startNode, endPosition);

    std::priority_queue<day16_node> nodesToInvestigate;
    nodesToInvestigate.push(startNode);

    int inf = std::numeric_limits<int>::max();

    std::vector<std::vector<std::map<Directions, int>>> costToReach(height, std::vector<std::map<Directions, int>>(width, std::map<Directions, int>({ {Directions::NORTH,inf }, {Directions::SOUTH, inf},{Directions::EAST, inf}, {Directions::WEST, inf} })));

    int bestCost = -1;

    while (nodesToInvestigate.size() != 0)
    {
        auto node = nodesToInvestigate.top();
        nodesToInvestigate.pop();

        std::pair<int, int> coord = { node.row, node.col };
        if (coord == endPosition)
        {
            int cost = node.currentCost;
            node.ancestors.push_back(endPosition);

            if (bestCost == -1)
            {
                bestCost = cost;

                for (auto n : node.ancestors)
                {
                    knownPath.insert(n);
                }

                if (partA)
                {
                    return bestCost;
                }
            }
            else
            {
                if (cost != bestCost)
                {
                    return bestCost;
                }
                else
                {
                        for (auto n : node.ancestors)
                    {
                        knownPath.insert(n);
                    }
                    continue;
                }
            }
        }

        int knowCost = costToReach[node.row][node.col][node.dir];

        if (partA)
        {
            if (knowCost < node.currentCost)
            {
                continue;
            }
        }
        else
        {
            if (knowCost == node.currentCost)
            {
                std::pair<int, int> toSearch = { node.row, node.col };
                if (knownPath.find(toSearch) == knownPath.end())
                {
                    continue;
                }
            }
            else
            {
                if (knowCost < node.currentCost)
                {
                    continue;
                }
            }
        }
        
        costToReach[node.row][node.col][node.dir] = node.currentCost;

        //forward
        {
            auto forward = getNextPosition(node.row, node.col, node.dir);
            if (board[forward.first][forward.second] != '#')
            {
                auto nextCost = node.currentCost + increaseForward;

                day16_node goForward(forward.first, forward.second, node.dir, nextCost);
                day16_updateNode(goForward, endPosition);
                day16_addAncestor(node, goForward, { node.row, node.col });
                nodesToInvestigate.push(goForward);
            }
        }
        
        //90
        {
            auto newDir = turn90Degress(node.dir);
            auto nextCost = node.currentCost + increaseTurn;

            day16_node turn90(node.row, node.col, newDir, nextCost);
            day16_updateNode(turn90, endPosition);
            day16_addAncestor(node, turn90, { node.row, node.col });
            nodesToInvestigate.push(turn90);
        }

        //-90
        {
            auto newDir = turnMinus90Degress(node.dir);
            auto nextCost = node.currentCost + increaseTurn;

            day16_node turnMinus90(node.row, node.col, newDir, nextCost);
            day16_updateNode(turnMinus90, endPosition);
            day16_addAncestor(node, turnMinus90, { node.row, node.col });
            nodesToInvestigate.push(turnMinus90);
        }
    }
        
    return 0;
    
}

void day16()
{
    auto board = ReadFile("./input/day16.txt");
    int width = board[0].size();
    int height = board.size();

    std::pair<int, int> start;
    std::pair<int, int> end;

    for (int row = 0; row < height; ++row)
    {
        for (int col = 0; col < width; ++col)
        {
            if (board[row][col] == 'S')
            {
                start = { row, col };
            }
            if (board[row][col] == 'E')
            {
                end = { row, col };
            }
        }
    }
    std::set<std::pair<int, int>> pathForA;

    int valueA = day16_calculate(board, width, height, start, end, 1, 1000, Directions::EAST, pathForA, true);

    std::cout << "day 16 => " << valueA << "\n";
   // day16_print(board, pathForA);

    day16_calculate(board, width, height, start, end, 1, 1000, Directions::EAST, pathForA, false);

    std::cout << "day 16_B => " << pathForA.size() << "\n";
    //day16_print(board, pathForA);

}

unsigned long long day17_getComboValue(unsigned long long& ra, unsigned long long& rb, unsigned long long rc, int literalOperand)
{
    if (literalOperand <= 3) { return literalOperand; }
    if (literalOperand == 4) { return ra; }
    if (literalOperand == 5) { return rb; }
    if (literalOperand == 6) { return rc; }
    return -1;
}

int day17_runInstruction(unsigned long long& ra, unsigned long long& rb, unsigned long long& rc, string inst, string operand, int& instructionIdx, std::vector<int>& valuesToPrint)
{
    int inst_int = atoi(inst.c_str());
    unsigned long long literalOperand = stoull(operand.c_str());
    unsigned long long comboOperand = day17_getComboValue(ra, rb, rc, literalOperand);

    switch (inst_int)
    {
    case 0: ra = std::floor(ra / pow(2, comboOperand)); break;
    case 1: rb = rb ^ literalOperand;  break;
    case 2: rb = comboOperand % 8; break;
    case 3: if (ra != 0) { return literalOperand; }break;
    case 4: rb = rb ^ rc;  break;
    case 5://std::cout << (comboOperand % 8) << ","; 
        valuesToPrint.push_back((comboOperand % 8)); break;
    case 6: rb = std::floor(ra / pow(2, comboOperand)); break;
    case 7: rc = std::floor(ra/ pow(2, comboOperand)); break;
    }
    return instructionIdx + 2;
}

std::vector<int> day17_run(unsigned long long ra, unsigned long long rb, unsigned long long rc, const vector<string>& instructions)
{
    int instructionIdx = 0;

   std::vector<int> result;

    while (instructionIdx < instructions.size())
    {
        string instruction = instructions[instructionIdx];
        string operand = instructions[instructionIdx + 1];

        instructionIdx = day17_runInstruction(ra, rb, rc, instruction, operand, instructionIdx, result);

    }
    return result;
}

long long day17_partB(long long currentSolution, const std::vector<string>& instructions, int currentIndexInstruction)
{
    if (currentIndexInstruction < 0)
    {
        return currentSolution;
    }

    bool someValid = false;
    for (int v = 0; v <= 7; ++v)
    {
        long long solutionTmp = currentSolution;
        solutionTmp = solutionTmp << 3;
        solutionTmp = (solutionTmp | v);

        auto resTmp = day17_run(solutionTmp, 0, 0, instructions);

        bool valid = true;

        for (int indiceTmp = 0; indiceTmp < resTmp.size(); ++indiceTmp)
        {
            int tmpValue = resTmp[indiceTmp];
            int insValue = atoi(instructions[currentIndexInstruction + indiceTmp].c_str());

            if (tmpValue != insValue)
            {
                valid = false;
                break;
            }
        }

        if (valid)
        {
            auto res = day17_partB(solutionTmp, instructions, currentIndexInstruction - 1);
            if (res != -1)
            {
                return res;
            }
        }
    }
    return -1;
}

long long day17_partB(const std::vector<string>& ins)
{
    return day17_partB(0, ins, ins.size() - 1);
}

void day17()
{
    auto fileTxt = ReadFile("./input/day17.txt");

    unsigned long long registerA = 0;
    unsigned long long registerB = 0;
    unsigned long long registerC = 0;

    std::regex registerRegex("Register A: (\\d*)");

    std::smatch sm;
    std::regex_search(fileTxt[0], sm, registerRegex);
    registerA = stoull(sm.str(1));

    string instructions_str = split(fileTxt[4], ": ")[1];
    auto instructions = split(instructions_str, ",");
    instructions_str += ",";

    auto resA = day17_run(registerA, registerB, registerC, instructions);
    std::string resA_str = "";
    for (auto a : resA)
    {
        resA_str += (std::to_string(a) + ",");
    }
    std::cout << "day 17 => " << resA_str << "\n";
    
    auto partB = day17_partB(instructions);
    std::cout << "day 17_B => " << partB << "\n";
}

struct day18_node
{
    std::pair<int, int> position;
    long long currentCost;
    long long manhattan;
    long long stimatedCost;

    std::vector<std::pair<int, int>> ancestors;

    friend bool operator<(const day18_node& a, const day18_node& b)
    {
        return a.stimatedCost > b.stimatedCost;
    }

    void updateHeuristic(std::pair<int, int> endPosition)
    {
        int height = abs(endPosition.first - position.first);
        int width = abs(endPosition.second - position.second);

        manhattan = width + height;
        stimatedCost = manhattan + currentCost;
    }

    void addAncestor(std::pair<int, int> position)
    {
        ancestors.push_back(position);
    }

    void addAllAncestors(std::vector<pair<int, int>> anc)
    {
        ancestors.insert(ancestors.end(), anc.begin(), anc.end());
    }
};


int day18_findWay(const std::vector<std::vector<bool>>& board, const std::pair<int, int>& start, const std::pair<int, int>& end, int width, int height)
{
    day18_node s(start, 0);
    std::vector<std::vector<bool>> investigated(height, std::vector<bool>(width, false));

    priority_queue<day18_node> nodesToInvestigate;

    nodesToInvestigate.push(s);

    while (!nodesToInvestigate.empty())
    {
        auto node = nodesToInvestigate.top();
        nodesToInvestigate.pop();

        if (node.position == end)
        {
            return node.currentCost;
        }

        if (investigated[node.position.first][node.position.second])
        {
            continue;
        }

        investigated[node.position.first][node.position.second] = true;

        for (Directions dir : {Directions::EAST, Directions::NORTH, Directions::SOUTH, Directions::WEST})
        {
            auto destiny = getNextPosition(node.position, dir);
            if (insideField(destiny, width, height) && board[destiny.first][destiny.second])
            {
                day18_node n(destiny, node.currentCost + 1);
                n.updateHeuristic(end);
                n.addAllAncestors(node.ancestors);
                nodesToInvestigate.push(n);
            }
        }
    }

    return -1;
}

void day18( bool calculateB)
{
    auto fileTxt = ReadFile("./input/day18.txt");

    int width =  71;
    int height =  71;

    std::vector<std::vector<bool>> board(height, std::vector<bool>(width, true));

    int totalTime = 1024;

    for(int i = 0; i < totalTime; ++i)
    {
        auto line = fileTxt[i];
        auto coord = split(line, ",");
        int col = atoi(coord[0].c_str());
        int row = atoi(coord[1].c_str());
        board[row][col] = false;
    }

    std::pair<int, int> start = { 0, 0};
    std::pair<int, int> end = { height -1, width-1 };

    auto resultA = day18_findWay(board, start, end, width, height);
    std::cout << "day 18 => " << resultA << "\n";
    if (calculateB)
    {
        int totalTry = fileTxt.size();
        for (int i = totalTime; i < fileTxt.size(); ++i)
        {
            std::cout << i << "[" << totalTry << "]" << "\n";
            auto line = fileTxt[i];
            auto coord = split(line, ",");
            int col = atoi(coord[0].c_str());
            int row = atoi(coord[1].c_str());
            board[row][col] = false;

            auto resB = day18_findWay(board, start, end, width, height);
            if (resB == -1)
            {
                std::cout << "day18_b => " << col << "," << row << "\n";
                break;
            }
        }
    }
    else
    {
        std::cout << "day18_b => 56,8 \n";
    }
}

bool day19_canUseTowel(const std::string& towel, const std::string& pattern)
{
    if (towel.size() > pattern.size())
    {
        return false;
    }

    for (int index = 0; index < towel.size(); ++index)
    {
        if (towel[index] != pattern[index])
        {
            return false;
        }
    }
    return true;
}

std::string day19_getCacheKey(const std::vector<string>& towels, const std::string& pattern)
{
    std::string result = "";
    for (auto t : towels)
    {
        result += t + "-";
    }

    result += "#" + pattern;

    return result;
}

unsigned long long day19_getTotalPatterns(std::vector<string>& towels, std::string pattern, std::map<std::string, unsigned long long>& cache)
{
    if (pattern.empty())
    {
        return 1;
    }

    std::string key = day19_getCacheKey(towels, pattern);

    if (cache.find(key) != cache.end())
    {
        return cache[key];
    }

    unsigned long long acumWays = 0;
    for (int i = 0; i < towels.size(); ++i)
    {
        std::string towel = towels[i];
        if (day19_canUseTowel(towel, pattern))
        {
            string newPattern = pattern.substr(towel.size());

            auto waysUseAndRemain = day19_getTotalPatterns(towels, newPattern, cache);

            acumWays += waysUseAndRemain;
        }
    }

    cache[key] = acumWays;
    return acumWays;
}

bool day19_canBeBuildPattern(std::vector<string>& towels, std::string pattern, std::map<std::string, bool>& cache)
{
    if (pattern.empty())
    {
        return true;
    }

    std::string key = day19_getCacheKey(towels, pattern);

    if (cache.find(key) != cache.end())
    {
        return cache[key];
    }

    bool canBeBuild = false;
    for (int i = 0; i < towels.size(); ++i)
    {
        std::string towel = towels[i];
        if (day19_canUseTowel(towel, pattern))
        {
            string newPattern = pattern.substr(towel.size());

            auto useAndRemain = day19_canBeBuildPattern(towels, newPattern, cache);

            if (useAndRemain)
            {
                canBeBuild = true;
                break;
            }
        }
    }

    cache[key] = canBeBuild;
    return canBeBuild;
}


void day19()
{
    auto fileTxt = ReadFile("./input/day19.txt");

    auto towels_tmp = split(fileTxt[0], ",");

    std::vector<string> towels;

    for (auto t : towels_tmp)
    {
        towels.push_back(trim_copy(t));
    }

    std::map<std::string, bool> cacheBuild;
    std::map<std::string, unsigned long long> cacheTimes;

    int acumA = 0;
    unsigned long long acumB = 0;

    for (int i = 2; i < fileTxt.size(); ++i)
    {
        auto pattern = fileTxt[i];

        auto canBeBuild = day19_canBeBuildPattern(towels, pattern, cacheBuild);

        if (canBeBuild)
        {
            ++acumA;
            acumB += day19_getTotalPatterns(towels, pattern, cacheTimes);
        }
    }


    std::cout << "day 19 => " << acumA << "\n";
    std::cout << "day 19_b => " << acumB << "\n";
}

std::pair<int, int> day20_findPosition(const std::vector<string>& board, char c)
{
    for (int row = 0; row < board.size(); ++row)
    {
        for (int col = 0; col < board[row].size(); ++col)
        {
            if (board[row][col] == c)
            {
                return { row, col };
            }
        }
    }
    return { -1,-1 };
}

struct day20_node
{
    std::pair<int, int> position;
    int cost;

    /*
    friend bool operator<(const day20_node& a, const day20_node& b)
    {
        return a.cost > b.cost;
    }
    */
};

std::vector<std::vector<int>> day20_calculateDistances(const std::vector<string>& board, int width, int height, const std::pair<int, int>& start, std::pair<int, int>& end)
{
    int inf = std::numeric_limits<int>::max();
    std::vector<std::vector<int>> toReturn(height, std::vector<int>(width, inf));

    day20_node startNode(start, 0);

    std::vector<day20_node> nodesToVisit;
    nodesToVisit.push_back(startNode);

    while (!nodesToVisit.empty())
    {
        auto node = nodesToVisit[0];
        nodesToVisit.erase(nodesToVisit.begin());

        if (toReturn[node.position.first][node.position.second] < node.cost) { continue; }

        toReturn[node.position.first][node.position.second] = node.cost;

        if (node.position == end) { continue; }

        for (Directions dir : {Directions::NORTH, Directions::EAST, Directions::SOUTH, Directions::WEST})
        {
            auto nextPosition = getNextPosition(node.position, dir);
            if (!insideField(nextPosition, width, height) || board[nextPosition.first][nextPosition.second] == '#') { continue; }

            day20_node newNode(nextPosition, node.cost + 1);
            nodesToVisit.push_back(newNode);
        }
    }

    return toReturn;
}

bool day20_validPosition(const std::vector<string>& board, int width, int height, const std::pair<int, int>& pos)
{
    return insideField(pos, width, height) && board[pos.first][pos.second] != '#';
}

std::map<int, std::set<pair<int, int>>> day20_calculateCheats_partA(const std::vector<string>& board, int width, int height, const std::vector<std::vector<int>>& distances)
{
    std::map<int, std::set<pair<int, int>>> toReturn;
    for (int row = 0; row < height; ++row)
    {
        for (int col = 0; col < width; ++col)
        {
            if (board[row][col] == '#')
            {
                auto north = getNextPosition(row, col, Directions::NORTH);
                auto south = getNextPosition(row, col, Directions::SOUTH);
                auto east = getNextPosition(row, col, Directions::EAST);
                auto west = getNextPosition(row, col, Directions::WEST);

                //there are few cases, so check manually
                if (day20_validPosition(board, width, height, north))
                {
                    if (day20_validPosition(board, width, height, south))
                    {
                        int diff = abs(distances[north.first][north.second] - distances[south.first][south.second]) - 2;
                        toReturn[diff].insert({row, col});
                    }

                    if (day20_validPosition(board, width, height, east))
                    {
                        int diff = abs(distances[north.first][north.second] - distances[east.first][east.second]) - 2;
                        toReturn[diff].insert({ row, col });
                    }

                    if (day20_validPosition(board, width, height, west))
                    {
                        int diff = abs(distances[north.first][north.second] - distances[west.first][west.second]) - 2;
                        toReturn[diff].insert({ row, col });
                    }
                }

                if (day20_validPosition(board, width, height, south))
                {
                    if (day20_validPosition(board, width, height, east))
                    {
                        int diff = abs(distances[south.first][south.second] - distances[east.first][east.second]) - 2;
                        toReturn[diff].insert({ row, col });
                    }

                    if (day20_validPosition(board, width, height, west))
                    {
                        int diff = abs(distances[south.first][south.second] - distances[west.first][west.second]) - 2;
                        toReturn[diff].insert({ row, col });
                    }
                }

                if (day20_validPosition(board, width, height, east))
                {
                    if (day20_validPosition(board, width, height, west))
                    {
                        int diff = abs(distances[east.first][east.second] - distances[west.first][west.second]) - 2;
                        toReturn[diff].insert({ row, col });
                    }
                }
            }
        }
    }

    return toReturn;
}

void day20_printDistances(std::vector<std::vector<int>>& dist, std::vector<string>& board)
{
    int width = dist[0].size();
    int height = dist.size();

    for (int row = 0; row < height; ++row)
    {
        for (int col = 0; col < height; ++col)
        {
            if (board[row][col] == '#') { std::cout << "####|"; }
            else
            {
                char buff[10];
                sprintf_s(buff, "%02d|", dist[row][col]);
                std::cout << buff;
            }
        }

        std::cout << "\n";
    }
    std::cout << "\n";

}

void day20_calculateA(std::vector<std::vector<int>> distances, std::vector<string>& board, int width, int height)
{
    auto cheats = day20_calculateCheats_partA(board, width, height, distances);

    long long solA = 0;

    int limit = 100;

    for (auto kvp : cheats)
    {
        if (kvp.first >= limit)
        {
            solA += kvp.second.size();
        }
    }

    std::cout << "day 20 => " << solA << "\n";
}

void day20_printRecheables(std::set < pair<int, int>> recheables, std::pair<int, int> position, std::vector<string>& board)
{
    for (int row = 0; row < board.size(); ++row)
    {
        for (int col = 0; col < board[row].size(); ++col)
        {
            std::pair<int, int> pos = { row, col };
            if (pos == position) { std::cout << "*"; continue; }

            if (recheables.find(pos) != recheables.end())
            {
                std::cout << "O";
                continue;
            }

            std::cout << board[row][col];
        }
        std::cout << "\n";
    }
    std::cout << "\n";
}

int day20_distanceBetweenPoints(const std::pair<int, int>& p1, const std::pair<int, int>& p2)
{
    return abs(p1.first - p2.first) + abs(p1.second - p2.second);
}

void day20_calculateB(std::vector<std::vector<int>> distances, std::vector<string>& board, int width, int height, std::pair<int, int> & endPosition)
{
    std::map<int, std::set<pair<int, int>>> cheatsB;

    std::map<string, std::set<pair<int, int>>> cache;

    int limitTime = 20;

    long long solB = 0;
    int minimunCheat = 100;

    int timeToReachEnd = distances[endPosition.first][endPosition.second];

    std::map<int, int> count;

    for (int row = 0; row < height; ++row)
    {
        for (int col = 0; col < width; ++col)
        {
            if (board[row][col] == '#')
            {
                continue;
            }

            for (int row2 = row - limitTime; row2 <= row + limitTime; ++row2)
            {
                for (int col2 = col - limitTime; col2 <= col + limitTime; ++col2)
                {
                    if (!insideField(row2, col2, width, height))
                    {
                        continue;
                    }

                    if (board[row2][col2] == '#')
                    {
                        continue;
                    }

                    
                    if (row2 == row && col2 == col)
                    {
                        continue;
                    }
                    

                    int distanceBetweenPoints = day20_distanceBetweenPoints({row2, col2}, {row, col});
                    if (distanceBetweenPoints > limitTime)
                    {
                        continue;
                    }

                    if (distances[row2][col2] < distances[row][col])
                    {
                        int timeUsingThisCheat = distances[row2][col2];
                        timeUsingThisCheat += distanceBetweenPoints;
                        timeUsingThisCheat += (timeToReachEnd - distances[row][col]);

                        int realWin = timeToReachEnd - timeUsingThisCheat;


                        if (realWin >= minimunCheat)
                        {
                            ++solB;
                        }
                    }
                }
            }

        }
   }

    std::cout << "day 20_B => " << solB << "\n";
}


void day20()
{
    auto board = ReadFile("./input/day20.txt");

    auto start = day20_findPosition(board, 'S');
    auto end = day20_findPosition(board, 'E');

    int width = board[0].size();
    int height = board.size();

    auto distances = day20_calculateDistances(board, width, height, start, end);
    //day20_printDistances(distances, board);

    day20_calculateA(distances, board, width, height);
    day20_calculateB(distances, board, width, height, end);
}

namespace day21_buildPaths
{
    char day21_getCharFromDirection(Directions dir)
    {
        switch (dir)
        {
        case Directions::NORTH:return '^';
        case Directions::SOUTH:return 'v';
        case Directions::EAST:return '>';
        case Directions::WEST:return '<';
        }
        return '#';
    }

    std::vector<std::string> day21_buildAllPath(const std::pair<int, int>& curr, const std::pair<int, int>& end, std::vector<Directions>& availableMovements, const std::string& currentStr, std::vector<std::vector<char>>& board, const int width, const int height)
    {
        if (curr == end) { return { currentStr + "A"}; }

        std::vector<std::string> toReturn;

        for (auto dir : availableMovements)
        {
            auto nextPosition = getNextPosition(curr, dir);
            if (insideField(nextPosition, width, height) && board[nextPosition.first][nextPosition.second] != '#')
            {
                auto newStr = currentStr + day21_getCharFromDirection(dir);
                auto solTmp = day21_buildAllPath(nextPosition, end, availableMovements, newStr, board, width, height);
                toReturn.insert(toReturn.end(), solTmp.begin(), solTmp.end());
            }
        }

        return toReturn;
    }

    std::pair<int, int> day21_getPositionInBoard(char c, std::vector<std::vector<char>>& board)
    {
        for (int row = 0; row < board.size(); ++row)
        {
            for (int col = 0; col < board[row].size(); ++col)
            {
                if (board[row][col] == c)
                {
                    return { row, col };
                }
            }
        }
        return { -1,-1 };
    }

    std::vector<string> day21_getAllPaths(char start, char end, std::vector<std::vector<char>>& board)
    {
        auto startPos = day21_getPositionInBoard(start, board);
        auto endPos = day21_getPositionInBoard(end, board);

        std::vector<Directions> availableMovements;

        if (startPos.first < endPos.first) { availableMovements.push_back(Directions::SOUTH); }
        if (startPos.first > endPos.first) { availableMovements.push_back(Directions::NORTH); }
        if (startPos.second < endPos.second) { availableMovements.push_back(Directions::EAST); }
        if (startPos.second > endPos.second) { availableMovements.push_back(Directions::WEST); }

        auto solution = day21_buildAllPath(startPos, endPos, availableMovements, "", board, board[0].size(), board.size());

        return solution;
    }

    std::map<string, std::vector<string>> day21_getAllPaths(std::vector<std::vector<char>>& board)
    {
        int width = board[0].size();
        int height = board.size();

        std::vector<char> availableButtons;

        for (int row = 0; row < height; ++row)
        {
            for (int col = 0; col < width; ++col)
            {
                if (board[row][col] != '#')
                {
                    availableButtons.push_back(board[row][col]);
                }
            }
        }


        std::map<string, std::vector<string>> toReturn;
        for (int i = 0; i < availableButtons.size(); ++i)
        {
            for (int j = 0; j < availableButtons.size(); ++j)
            {
                std::string key = string(1, availableButtons[i]) + string(1, availableButtons[j]);
                toReturn[key] = day21_getAllPaths(availableButtons[i], availableButtons[j], board);
            }
        }
        return toReturn;
    }
}

long long day21_getMinCode(char a, char b, std::map<string, std::vector<string >> pathsNumbers, std::map<string, std::vector<string>>& pathsDirections, std::vector<std::vector<std::vector<long long>>>& cache, int currentLayer, int totalLayers)
{
    if (currentLayer == totalLayers-1) { return 1; }//in the last layer, press directly the button
    if (cache[a][b][currentLayer] != -1) { return cache[a][b][currentLayer]; }

    std::string key = string(1, a) + string(1, b);

    std::vector<string> allPaths = currentLayer == 0 ? pathsNumbers[key] : pathsDirections[key];

    long long best = -1;
    for (auto&& path : allPaths)
    {
        long long solTmp = 0;
        char currentPosition = 'A';
        for (int pos = 0; pos < path.size(); ++pos)
        {
            solTmp += day21_getMinCode(currentPosition, path[pos], pathsNumbers, pathsDirections, cache, currentLayer + 1, totalLayers);
            currentPosition = path[pos];
        }

        if (best == -1 || solTmp < best)
        {
            best = solTmp;
        }

    }
    cache[a][b][currentLayer] = best;
    return best;
}

long long day21_getMinCodeSize(const std::string& code, std::map<string, std::vector<string>> pathsNumbers, std::map<string, std::vector<string>>& pathsDirections, std::vector<std::vector<std::vector<long long>>>& cache, int totalLayers)
{
    //always we do the path from A => first letter
    //then path from N letter to N+1

    long long solution = 0;
    char currentPosition = 'A';
    for (int pos = 0; pos < code.size(); ++pos)
    {
        solution += day21_getMinCode(currentPosition, code[pos], pathsNumbers, pathsDirections, cache, 0, totalLayers);
        currentPosition = code[pos];
    }

    return solution;
}

void day21()
{
    //+---+---+---+
    //| 7 | 8 | 9 |
    //+---+---+---+
    //| 4 | 5 | 6 |
    //+---+---+---+
    //| 1 | 2 | 3 |
    //+---+---+---+
    //    | 0 | A |
    //    +---+---+
    std::vector<std::vector<char>> boardNumbers = {
       {'7','8','9'},
       {'4','5','6'},
       {'1','2','3'},
       {'#','0','A'},
    };

    auto allPathsNumbers = day21_buildPaths::day21_getAllPaths(boardNumbers);

    //    +---+---+
    //    | ^ | A |
    //+---+---+---+
    //| < | v | > |
    //+---+---+---+

    std::vector<std::vector<char>> boardDirections = {
       {'#','^','A'},
       {'<','v','>'},
    };
    auto allPathsDirections = day21_buildPaths::day21_getAllPaths(boardDirections);

    std::vector<std::vector<std::vector<long long>>> cacheA(128, std::vector<std::vector<long long>>(128, std::vector<long long>(5, -1)));

    std::vector<std::vector<std::vector<long long>>> cacheB(128, std::vector<std::vector<long long>>(128, std::vector<long long>(28, -1)));

    
    auto codes = ReadFile("./input/day21.txt");

    long long solA = 0;
    long long solB = 0;

    for (auto&& c : codes)
    {
       // c = "029A";
        long long codeSizeA = day21_getMinCodeSize(c, allPathsNumbers, allPathsDirections, cacheA, 4);
        long long  codeSizeB = day21_getMinCodeSize(c, allPathsNumbers, allPathsDirections, cacheB, 27);

        int number = atoi(c.substr(0, 3).c_str());

        solA += codeSizeA * number;
        solB += codeSizeB * number;
    }

    std::cout << "day21 => " << solA << "\n";
    std::cout << "day21_B => " << solB << "\n";
}

int main()
{
   //day1();
   //day2();
   //day3();
   //day3();
   //day4();
   //day5(false);
   //day6(false);
   //day7();
   //day8();
   //day9();
   //day10();
   //day11();
   //day12();
   //day13();
   //day14(false);
   //day15();
   //day16();
   //day17();
   //day18(false);
   //day19();
   //day20();
   day21();
   other::run();
   /*
   day22();
   day23();
   day24();
   day25();
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
