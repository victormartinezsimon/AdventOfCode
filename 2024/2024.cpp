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
    if (row >= width) { return false; }
    if (col >= height) { return false; }

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

int main()
{
   //day1();
   //day2();
   //day3();
   //day3();
   //day4();
  // day5(false);
   // day6(false);
   day7();
   /*
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
