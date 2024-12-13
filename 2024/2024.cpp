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
int calculateExternalPerimeter(const std::vector<pair<int, int>>& shape, const std::vector<string>& board, const int width, const int height, std::map<int, int>& acumPerimeters, std::vector<std::vector<int>>& shapeIdx)
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
   day12();
   /*
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
