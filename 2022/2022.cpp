// 2022.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <array>
#include <assert.h>     /* assert */
#include <set>
#include <map>
#include <stack>
#include <queue>
#include <functional>

using namespace std;

void day1()
{
    string line;
    std::ifstream file("./input/day1.txt");

    if (file.is_open())
    {
        long long actualValue = 0;
        std::vector<long long> values;
        while (std::getline(file, line))
        {
            if (line == "\n" || line.size() == 0)
            {
                values.push_back(actualValue);
                actualValue = 0;
            }
            else
            {
                long long v = atoll(line.c_str());
                actualValue += v;
            }

        }
        values.push_back(actualValue);
        std::sort(values.begin(), values.end());//O(nlogn)
        long long v1 = values[values.size() - 1];
        long long v2 = values[values.size() - 2];
        long long v3 = values[values.size() - 3];
        long long result = v1 + v2 + v3;
        std::cout << "Day1 =>" << v1 << "," << result << "\n";
    }
    file.close();
}

long long getScore_day2(char oponent, char mine)
{
    long long toReturn = 0;

    //points for choose
    switch (mine)
    {
    case 'X': toReturn += 1; break;//rock
    case 'Y': toReturn += 2; break;//paper
    case 'Z': toReturn += 3; break;//scissors
    }

    //points for result
    if (mine == 'X')
    {
        //rock
        switch (oponent)
        {
        case 'A': toReturn += 3; break;//rock
        case 'B': toReturn += 0; break;//paper
        case 'C': toReturn += 6; break;//scissors
        }
    }
    else
    {
        if (mine == 'Y')
        {
            //paper
            switch (oponent)
            {
            case 'A': toReturn += 6; break;//rock
            case 'B': toReturn += 3; break;//paper
            case 'C': toReturn += 0; break;//scissors
            }
        }
        else
        {
            //scissors
            switch (oponent)
            {
            case 'A': toReturn += 0; break;//rock
            case 'B': toReturn += 6; break;//paper
            case 'C': toReturn += 3; break;//scissors
            }
        }
    }

    return toReturn;
}
long long getScore_2_day2(char oponent, char mine)
{
    long long toReturn = 0;

    //case 'X';//rock
    //case 'Y';//paper
    //case 'Z';//scissors

    //points for result
    if (mine == 'X')
    {
        //lose
        switch (oponent)
        {
        case 'A': return getScore_day2(oponent, 'Z');//rock
        case 'B': return getScore_day2(oponent, 'X');//paper
        case 'C': return getScore_day2(oponent, 'Y');//scissors
        }
    }
    else
    {
        if (mine == 'Y')
        {
            //draw
            switch (oponent)
            {
            case 'A': return getScore_day2(oponent, 'X');//rock
            case 'B': return getScore_day2(oponent, 'Y');//paper
            case 'C': return getScore_day2(oponent, 'Z');//scissors
            }
        }
        else
        {
            //win
            switch (oponent)
            {
            case 'A': return getScore_day2(oponent, 'Y');//rock
            case 'B': return getScore_day2(oponent, 'Z');//paper
            case 'C': return getScore_day2(oponent, 'X');//scissors
            }
        }
    }

    return 0;
}

void day2()
{
    string line;
    std::ifstream file("./input/day2.txt");
    if (file.is_open())
    {
        long long score1 = 0;
        long long score2 = 0;
        while (std::getline(file, line))
        {
            char oponent = line[0];
            char myAction = line[2];
            score1 += getScore_day2(oponent, myAction);
            score2 += getScore_2_day2(oponent, myAction);
        }
        std::cout << "Day2 =>" << score1 << "," << score2 << "\n";
    }
    file.close();
}

void day3()
{
    string line;
    std::ifstream file("./input/day3.txt");
    if (file.is_open())
    {
        long long score = 0;
        while (std::getline(file, line))
        {
            string s1 = line.substr(0, line.size() / 2);
            string s2 = line.substr(line.size() / 2, line.size() / 2);

            assert(s1.size() == s2.size());

            std::array<bool, 256> cache;
            cache.fill(false);
            for (auto c : s1)
            {
                cache[static_cast<int>(c)] = true;
            }
            long long originalValue = score;

            for (auto c : s2)
            {
                if (cache[static_cast<int>(c)])
                {
                    if ('a' < c && c <= 'z')
                    {
                        score += (c - 'a' + 1);
                    }
                    else
                    {
                        score += (c - 'A' + 27);
                    }
                    break;
                }
            }
            assert(originalValue != score);
        }
        std::cout << "Day3 =>" << score << "\n";
    }
    file.close();
}

void day3_2()
{
    string line;
    std::ifstream file("./input/day3.txt");
    if (file.is_open())
    {
        long long score = 0;
        while (std::getline(file, line))
        {
            string line2;
            string line3;
            std::getline(file, line2);
            std::getline(file, line3);

            std::set<char> c1, c2, c3;
            for (auto c : line)
            {
                c1.insert(c);
            }

            for (auto c : line2)
            {
                c2.insert(c);
            }

            for (auto c : line3)
            {
                c3.insert(c);
            }

            std::set<char> c12;
            std::set<char> c123;

            std::set_intersection(c1.begin(), c1.end(),
                c2.begin(), c2.end(),
                std::inserter(c12, c12.begin()));

            std::set_intersection(c12.begin(), c12.end(),
                c3.begin(), c3.end(),
                std::inserter(c123, c123.begin()));

            for (auto c : c123)
            {
                if ('a' < c && c <= 'z')
                {
                    score += (c - 'a' + 1);
                }
                else
                {
                    score += (c - 'A' + 27);
                }
                break;
            }
        }
        std::cout << "Day3_2 =>" << score << "\n";
    }
    file.close();
}

void day4()
{
    string line;
    std::ifstream file("./input/day4.txt");
    if (file.is_open())
    {
        long long scoreFullOverlap = 0;
        long long scoreSingleOverlap = 0;
        while (std::getline(file, line))
        {
            std::string l1 = line.substr(0, line.find(","));
            std::string l2 = line.substr(line.find(",") + 1);

            int l1a = atoi(l1.substr(0, l1.find("-")).c_str());
            int l1b = atoi(l1.substr(l1.find("-") + 1).c_str());

            int l2a = atoi(l2.substr(0, l2.find("-")).c_str());
            int l2b = atoi(l2.substr(l2.find("-") + 1).c_str());

            if (l1a >= l2a && l1b <= l2b)
            {
                ++scoreFullOverlap;
            }
            else
            {
                if (l2a >= l1a && l2b <= l1b)
                {
                    ++scoreFullOverlap;
                }
            }

            if (l1a >= l2a && l1a <= l2b)
            {
                ++scoreSingleOverlap;
            }
            else
            {
                if (l2a >= l1a && l2a <= l1b)
                {
                    ++scoreSingleOverlap;
                }
            }

        }
        std::cout << "Day4 =>" << scoreFullOverlap << "," << scoreSingleOverlap << "\n";
    }
    file.close();
}

void day5_buildStacks(std::vector<string> input, std::vector<std::stack<char>>& _stacks, std::vector<std::vector<char>>& _queues)
{
    int totalStacks = std::count(input.back().begin(), input.back().end(), '[');

    for (int i = 0; i < totalStacks; ++i)
    {
        std::stack<char> _newStack;
        _stacks.push_back(_newStack);

        std::vector<char> _newQueue;
        _queues.push_back(_newQueue);
    }

    for (int i = input.size() - 1; i >= 0; --i)
    {
        int actualIndex = 0;
        int actualStack = 0;
        string msg = input[i];
        while (actualIndex < msg.size())
        {
            if (msg[actualIndex] == '[')
            {
                _stacks[actualStack].push(msg[actualIndex + 1]);
                _queues[actualStack].push_back(msg[actualIndex + 1]);
            }
            actualIndex += 4; "[<Letter>]<space>";
            ++actualStack;
        }
    }
}

void day5_parseMovements(std::string input, std::vector<std::stack<char>>& _stacks, std::vector<std::vector<char>>& _queues)
{
    //move XX from YY to ZZ
    auto posFrom = input.find("from");
    auto posTo = input.find("to");

    int totalToMove = atoi(input.substr(5, posFrom - 5).c_str());
    int from = atoi(input.substr(posFrom + 5, posTo - (posFrom + 5)).c_str()) - 1;
    int to = atoi(input.substr(posTo + 3).c_str()) - 1;

    for (int i = 0; i < totalToMove; ++i)
    {
        {
            int value = _stacks[from].top();
            _stacks[to].push(value);
            _stacks[from].pop();
        }

        {
            int value = _queues[from][_queues[from].size() - totalToMove + i];
            _queues[to].push_back(value);
        }
    }

    //remove moved elements from queue
    for (int i = 0; i < totalToMove; ++i)
    {
        _queues[from].pop_back();
    }
}

void day5()
{
    string line;
    std::ifstream file("./input/day5.txt");
    if (file.is_open())
    {
        std::vector<std::stack<char>> stacks;
        std::vector<std::vector<char>> queues;

        //read actual stack info
        std::vector<string> linesStack;
        bool findEndStacks = false;
        while (!findEndStacks)
        {
            std::getline(file, line);
            if (std::find(line.begin(), line.end(), '1') != line.end())
            {
                findEndStacks = true;
            }
            else
            {
                linesStack.push_back(line);
            }
        }
        day5_buildStacks(linesStack, stacks, queues);

        std::getline(file, line);//empty line

        //movements
        while (std::getline(file, line))
        {
            day5_parseMovements(line, stacks, queues);
        }
        std::cout << "day5 =>";
        for (auto s : stacks)
        {
            std::cout << s.top();
        }
        std::cout << ",";
        for (auto s : queues)
        {
            std::cout << s.back();
        }
        std::cout << "\n";
    }
    file.close();
}

bool day6_allDiferent(const string& s, int startEndIndex, int totalDifferent)
{
    std::set<char> cache;

    for (int i = startEndIndex - totalDifferent; i < startEndIndex; ++i)
    {
        if (cache.find(s[i]) != cache.end())
        {
            return false;
        }
        cache.insert(s[i]);
    }
    return true;
}

void day6()
{
    std::ifstream file("./input/day6.txt");
    if (file.is_open())
    {
        string line;
        if (std::getline(file, line))
        {
            int indexFirstPart = 4;

            while (indexFirstPart < line.size())
            {
                if (day6_allDiferent(line, indexFirstPart, 4))
                {
                    std::cout << "day 6 =>" << (indexFirstPart) << ",";
                    break;
                }
                ++indexFirstPart;
            }

            int indexSecondPart = 14;
            while (indexSecondPart < line.size())
            {
                if (day6_allDiferent(line, indexSecondPart, 14))
                {
                    std::cout << (indexSecondPart) << "\n";
                    break;
                }
                ++indexSecondPart;
            }

        }
    }
    file.close();
}

class FileSystem
{
public:
    string name = "";
    long long size = 0;
    vector<FileSystem*> folders;
    vector<FileSystem*> files;
    FileSystem* parent = nullptr;
    bool isFolder;
};

FileSystem* day7_commandCD(FileSystem* root, FileSystem* now, const string& line)
{
    //cd /
    if (line.substr(5, 1) == "/")
    {
        return root;
    }
    //cd ..
    if (line.substr(5, 2) == "..")
    {
        return now->parent;
    }

    //cd <name>
    string nameFolder = line.substr(5);
    for (int i = 0; i < now->folders.size(); ++i)
    {
        if (now->folders[i]->name == nameFolder)
        {
            return now->folders[i];
        }
    }
}

void day7_addFolder(FileSystem* now, string name)
{
    for (int i = 0; i < now->folders.size(); ++i)
    {
        if (now->folders[i]->name == name)
        {
            return;
        }
    }
    FileSystem* newFolder = new FileSystem();
    newFolder->name = name;
    newFolder->isFolder = true;
    newFolder->parent = now;
    now->folders.push_back(newFolder);
}

void day7_addFile(FileSystem* now, string name, long long size)
{
    for (int i = 0; i < now->files.size(); ++i)
    {
        if (now->files[i]->name == name)
        {
            return;
        }
    }
    FileSystem* newFile = new FileSystem();
    newFile->name = name;
    newFile->size = size;
    newFile->isFolder = false;
    newFile->parent = now;
    now->files.push_back(newFile);
}

void day7_calculateSize(FileSystem* position)
{
    if (position == nullptr)
    {
        return;
    }

    for (int i = 0; i < position->folders.size(); ++i)
    {
        day7_calculateSize(position->folders[i]);
        position->size += position->folders[i]->size;
    }

    for (int i = 0; i < position->files.size(); ++i)
    {
        position->size += position->files[i]->size;
    }
}

void day7_calculateSolution_1(FileSystem* now, long long& solution, long long maxValue)
{
    if (!now->isFolder)
    {
        return;
    }
    for (int i = 0; i < now->folders.size(); ++i)
    {
        if (now->folders[i]->size < maxValue)
        {
            solution += now->folders[i]->size;
        }
        day7_calculateSolution_1(now->folders[i], solution, maxValue);
    }
}

void day7_calculateSolution_2(FileSystem* now, long long minSize, long long& solution)
{
    if (!now->isFolder)
    {
        return;
    }
    for (int i = 0; i < now->folders.size(); ++i)
    {
        if (now->folders[i]->size >= minSize)
        {
            if (now->folders[i]->size < solution)
            {
                solution = now->folders[i]->size;
            }
        }
        day7_calculateSolution_2(now->folders[i], minSize, solution);
    }
}

void day7()
{
    std::ifstream file("./input/day7.txt");
    if (file.is_open())
    {
        string line;
        FileSystem* root = new FileSystem();
        root->name = "/";
        root->isFolder = true;
        FileSystem* actualPosition = root;
        bool inLS = false;
        while (std::getline(file, line))
        {
            if (line.substr(2, 2) == "cd")
            {
                actualPosition = day7_commandCD(root, actualPosition, line);
                inLS = false;
                continue;
            }
            if (line.substr(2, 2) == "ls")
            {
                inLS = true;
                continue;
            }

            if (inLS && line.substr(0, 3) == "dir")
            {
                //new directory
                string nameFolder = line.substr(4);
                day7_addFolder(actualPosition, nameFolder);
                continue;
            }
            if (inLS && line[0] >= '0' && line[1] <= '9')
            {
                //folder
                auto index = line.find(' ');
                long long size = atoll(line.substr(0, index).c_str());
                string name = line.substr(index + 1);
                day7_addFile(actualPosition, name, size);
                continue;
            }
        }
        day7_calculateSize(root);
        long long solution1 = 0;
        day7_calculateSolution_1(root, solution1, 100000);
        std::cout << "day7 => " << solution1;

        long long maxSize = 70000000;
        long long spaceNeed = 30000000;
        long long unusedSpace = maxSize - root->size;
        long long spaceToDelete = spaceNeed - unusedSpace;
        long long solution2 = root->size;
        day7_calculateSolution_2(root, spaceToDelete, solution2);
        std::cout << "," << solution2 << "\n";
    }
}

void day8_count(const vector<vector<int>>& board, int startRow, int startCol, int increaseRow, int increaseCol, set<pair<int, int>>& uniqueTrees)
{
    int actualRow = startRow;
    int actualCol = startCol;

    int maxValue = -1;

    while (actualRow >= 0 && actualCol >= 0 && actualRow < board.size() && actualCol < board[0].size())
    {
        if (board[actualRow][actualCol] > maxValue)
        {
            uniqueTrees.insert({ actualCol, actualRow });
            maxValue = board[actualRow][actualCol];
        }
        actualRow += increaseRow;
        actualCol += increaseCol;
    }
}

long long day8_getTreeScore(const vector<vector<int>>& board, int startRow, int startCol, int increaseRow, int increaseCol)
{
    int currentValue = board[startRow][startCol];

    int actualRow = startRow + increaseRow;
    int actualCol = startCol + increaseCol;
    long long toReturn = 0;

    while (actualRow >= 0 && actualCol >= 0 && actualRow < board.size() && actualCol < board[0].size())
    {
        ++toReturn;
        if (board[actualRow][actualCol] < currentValue)
        {
            actualRow += increaseRow;
            actualCol += increaseCol;
        }
        else
        {
            return toReturn;
        }

    }
    return toReturn;
}

long long day8_getTreeScore(const vector<vector<int>>& board, int startRow, int startCol)
{
    long long toReturn = day8_getTreeScore(board, startRow, startCol, 0, 1);
    toReturn *= day8_getTreeScore(board, startRow, startCol, 0, -1);
    toReturn *= day8_getTreeScore(board, startRow, startCol, 1, 0);
    toReturn *= day8_getTreeScore(board, startRow, startCol, -1, 0);

    return toReturn;
}

void day8()
{
    std::ifstream file("./input/day8.txt");
    if (file.is_open())
    {
        string line;
        vector<vector<int>> board;
        while (std::getline(file, line))
        {
            vector<int> lineToAdd;
            for (auto c : line)
            {
                lineToAdd.push_back(c - '0');
            }
            board.push_back(lineToAdd);
        }

        set<pair<int, int>> unique_trees;
        for (int i = 0; i < board[0].size(); ++i)
        {
            //top
            day8_count(board, 0, i, 1, 0, unique_trees);
            //bottom
            day8_count(board, board.size() - 1, i, -1, 0, unique_trees);
        }

        for (int i = 0; i < board.size(); ++i)
        {
            //left
            day8_count(board, i, 0, 0, 1, unique_trees);
            //right
            day8_count(board, i, board[i].size() - 1, 0, -1, unique_trees);
        }
        std::cout << "day8 => " << unique_trees.size();

        long long bestTreeScore = -1;
        for (int row = 0; row < board.size(); ++row)
        {
            for (int col = 0; col < board[row].size(); ++col)
            {
                long long value = day8_getTreeScore(board, row, col);
                if (value > bestTreeScore)
                {
                    bestTreeScore = value;
                }
            }
        }
        std::cout << "," << bestTreeScore << "\n";
    }
    file.close();
}

struct day9_position
{
public:
    int row;
    int col;
};
void day9_doMovement(char direction, day9_position& head, day9_position& tail)
{

    switch (direction)
    {
    case 'R': head.col += 1; break;//increase col
    case 'L': head.col -= 1; break;//decrease col
    case 'D': head.row += 1; break;//increase row
    case 'U': head.row -= 1; break;//decrease row
    }

}

void day9_updatePosition(day9_position& head, day9_position& tail)
{
    //check if move horizontal
    int distanceHorizontal = head.col - tail.col;
    int distanceVertical = head.row - tail.row;

    if (abs(distanceHorizontal) == 2 || (abs(distanceHorizontal) == 1 && abs(distanceVertical) == 2))
    {
        if (distanceHorizontal > 0)
        {
            tail.col += 1;
        }
        else
        {
            tail.col -= 1;
        }
    }

    if (abs(distanceVertical) == 2 || (abs(distanceVertical) == 1 && abs(distanceHorizontal) == 2))
    {
        if (distanceVertical > 0)
        {
            tail.row += 1;
        }
        else
        {
            tail.row -= 1;
        }
    }
}

void day9_doMovement(char direction, vector<day9_position>& elements)
{
    day9_doMovement(direction, elements[0], elements[1]);//move head

    for (int i = 0; i < elements.size() - 1; ++i)
    {
        day9_updatePosition(elements[i], elements[i + 1]);
    }
}

void day9()
{
    std::ifstream file("./input/day9.txt");
    if (file.is_open())
    {
        string line;
        set<pair<int, int>> positionsVisitedSingle;
        set<pair<int, int>> positionsVisitedMultiple;
        day9_position tailPosition = { 0,0 };
        day9_position headPosition = { 0,0 };

        int totalElements = 10;
        vector<day9_position> multiplePositions(totalElements);

        while (std::getline(file, line))
        {
            char movement = line[0];
            int totalMovements = atoi(line.substr(2).c_str());

            for (int i = 0; i < totalMovements; ++i)
            {
                day9_doMovement(movement, headPosition, tailPosition);
                day9_updatePosition(headPosition, tailPosition);
                positionsVisitedSingle.insert({ tailPosition.row, tailPosition.col });

                day9_doMovement(movement, multiplePositions);
                positionsVisitedMultiple.insert({ multiplePositions.back().row, multiplePositions.back().col });
            }
        }
        std::cout << "Day9=>" << positionsVisitedSingle.size() << "," << positionsVisitedMultiple.size() << "\n";
    }
}

void day10()
{
    std::ifstream file("./input/day10.txt");
    if (file.is_open())
    {
        int currentCycle = 1;
        int valueX = 1;
        std::map<string, int> cyclesConverter({ { "noop", 1 } , { "addx", 2 } });
        string line;
        long long toReturn = 0;
        int startCycleToCount = 20;
        int increaseCycle = 40;
        while (std::getline(file, line))
        {
            string instruction = line.substr(0, 4);
            int value = 0;
            if (instruction == "addx")
            {
                value = atoi(line.substr(5).c_str());
            }

            int totalCycles = cyclesConverter[instruction];

            for (int i = 0; i < totalCycles; ++i)
            {
                if ((currentCycle - startCycleToCount) % increaseCycle == 0)
                {
                    toReturn += (valueX * currentCycle);
                }

                int currentPixelPainting = (currentCycle - 1) % 40;
                if (valueX - 1 <= currentPixelPainting && currentPixelPainting <= valueX + 1)
                {
                    std::cout << "#";
                }
                else
                {
                    std::cout << ".";
                }
                if (currentPixelPainting == 39)
                {
                    std::cout << "\n";
                }

                ++currentCycle;
            }
            valueX += value;
        }

        std::cout << "Day10=>" << toReturn << "\n";
    }
}

struct day11_monkeyNumber
{
public:
    int originalValue = 0;
    vector<string> lastOperations;
};


struct day11_monkey
{
public:
    int id = -1;
    vector<long long> objects;
    std::vector<int> monkeyToPass;
    int valueCheckToPass = 1;
    int totalInspected = 0;
    string functionUpdate_str = "";
    vector< day11_monkeyNumber> objects_2;
};


vector<string> day11_split(string s, const string& delimiter)
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

long long day11_parseFunction(string function, long long currentValue)
{
    long long toReturn = currentValue;

    long long secondOperator = 0;
    if (function.find("old") != std::string::npos)
    {
        secondOperator = currentValue;
    }
    else
    {
        secondOperator = atoll(function.substr(2).c_str());
    }

    switch (function[0])
    {
    case '+': toReturn += secondOperator; break;
    case '-': toReturn -= secondOperator; break;
    case '*': toReturn *= secondOperator; break;
    case '/': toReturn /= secondOperator; break;
    }
    return toReturn;
}

long long day11_parseFunction_2(string function, long long currentValue)
{
    long long toReturn = currentValue;

    long long secondOperator = 0;
    if (function.find("old") != std::string::npos)
    {
        return currentValue;
    }
    else
    {
        secondOperator = atoll(function.substr(2).c_str());
    }

    switch (function[0])
    {
    case '+': toReturn += secondOperator; break;
    case '-': toReturn -= secondOperator; break;
    case '*': toReturn *= secondOperator; break;
    case '/': toReturn /= secondOperator; break;
    }
    return toReturn;
}

bool day11_passOperator(day11_monkeyNumber& monkeyNumber, long long valueCheck)
{
    long long acum = 0;
    for (int i = monkeyNumber.lastOperations.size() - 1; i >= 0; --i)
    {
        if (monkeyNumber.lastOperations[i].find("*") != std::string::npos)
        {
            return ((atoi(monkeyNumber.lastOperations[i].substr(2).c_str()) + acum) % valueCheck) == 0;
        }
        else
        {
            acum += atoi(monkeyNumber.lastOperations[i].substr(2).c_str());
        }
    }
    //here we reach the beggining
    return ((monkeyNumber.originalValue + acum) % valueCheck) == 0;
}

void day11(bool runPart2 = false)
{
    std::ifstream file("./input/day11.txt");
    if (file.is_open())
    {
        vector<day11_monkey> monkeys;
        vector<day11_monkey> monkeys_2;

        string line;
        while (std::getline(file, line))
        {
            string starting_items, operation, test1, test2, test3;
            std::getline(file, starting_items);
            std::getline(file, operation);
            std::getline(file, test1);
            std::getline(file, test2);
            std::getline(file, test3);
            std::getline(file, line);//empty line

            day11_monkey monkey;
            monkey.id = monkeys.size() + 1;
            starting_items = starting_items.substr(18);
            auto items_str = day11_split(starting_items, ",");
            for (auto str : items_str)
            {
                monkey.objects.push_back(atoll(str.c_str()));

                day11_monkeyNumber mn;
                mn.originalValue = atoll(str.c_str());
                monkey.objects_2.push_back(mn);
            }

            monkey.functionUpdate_str = operation.substr(23); // * <value>

            monkey.valueCheckToPass = atoi(test1.substr(21).c_str());
            monkey.monkeyToPass.push_back(atoi(test2.substr(29).c_str()));
            monkey.monkeyToPass.push_back(atoi(test3.substr(30).c_str()));



            monkeys.push_back(monkey);
            monkeys_2.push_back(monkey);
        }


        int totalCycles = 20;
        for (int cycle = 0; cycle < totalCycles; ++cycle)
        {
            for (auto& monkey : monkeys)
            {
                for (int obj : monkey.objects)
                {
                    int newValue = day11_parseFunction(monkey.functionUpdate_str, obj);
                    newValue = newValue / 3;
                    bool passTest = (newValue % (monkey.valueCheckToPass) == 0);
                    int newMonkey = monkey.monkeyToPass[0];
                    if (!passTest)
                    {
                        newMonkey = monkey.monkeyToPass[1];
                    }
                    monkeys[newMonkey].objects.push_back(newValue);
                    monkey.totalInspected++;
                }
                monkey.objects.clear();
            }
        }

        std::sort(monkeys.begin(), monkeys.end(), [](const day11_monkey& a, const day11_monkey& b) {
            return a.totalInspected > b.totalInspected;
            });

        if (runPart2)
        {
            int totalCycles_2 = 10000;
            const long long valueToDivide = (13 * 3 * 17 * 5 * 19 * 2 * 11 * 7);
            for (int cycle = 0; cycle < totalCycles_2; ++cycle)
            {
                for (auto& monkey : monkeys_2)
                {
                    for (int obj : monkey.objects)
                    {
                        auto newValue = day11_parseFunction(monkey.functionUpdate_str, obj);
                        newValue = (newValue % valueToDivide);
                        bool passTest = (newValue % (monkey.valueCheckToPass) == 0);
                        int newMonkey = monkey.monkeyToPass[0];
                        if (!passTest)
                        {
                            newMonkey = monkey.monkeyToPass[1];
                        }
                        monkeys_2[newMonkey].objects.push_back(newValue);
                        monkey.totalInspected++;
                    }
                    monkey.objects.clear();
                }
            }

            std::sort(monkeys_2.begin(), monkeys_2.end(), [](const day11_monkey& a, const day11_monkey& b) {
                return a.totalInspected > b.totalInspected;
                });
        }

        std::cout << "Day11=>" << (monkeys[0].totalInspected * monkeys[1].totalInspected) << ", Real => 27267163742 (Mio=>" << (monkeys_2[0].totalInspected * monkeys_2[1].totalInspected) << ")\n";
    }
    file.close();
}

struct day12_node
{
public:
    char height = 'a';
    int timesToReach = 0;
    int row = -1;
    int col = -1;
};

bool day12_validNode(int actualRow, int actualCol, int newRow, int newCol, const vector<string>& maze)
{
    if (newRow < 0 || newCol < 0 || newRow >= maze.size() || newCol >= maze[0].size())
    {
        return false;
    }

    char origin = maze[actualRow][actualCol];
    char destiny = maze[newRow][newCol];
    if (origin == 'S') { origin = 'a'; } if (origin == 'E') { origin = 'z'; }
    if (destiny == 'S') { destiny = 'a'; } if (destiny == 'E') { destiny = 'z'; }

    return abs(origin - destiny) <= 1;
}

void day12()
{
    std::ifstream file("./input/day12.txt");
    if (file.is_open())
    {
        string line;
        int startCol = -1;
        int startRow = -1;
        int endCol = -1;
        int endRow = -1;
        vector<string> maze;
        while (std::getline(file, line))
        {
            maze.push_back(line);
            if (line.find("S") != std::string::npos)
            {
                startRow = maze.size() - 1;
                startCol = line.find("S");
            }

            if (line.find("E") != std::string::npos)
            {
                endRow = maze.size() - 1;
                endCol = line.find("E");
            }
        }

        std::vector<pair<int, int>> startIndex = { {startRow, startCol},{endRow, endCol} };
        std::vector<char> endElement = { 'E', 'a' };

        std::cout << "day12 =>";

        for (int i = 0; i < 2; ++i)
        {
            vector<day12_node> nodesToInspect;
            day12_node start{ maze[startIndex[i].first][startIndex[i].second], 0, startIndex[i].first, startIndex[i].second};
            nodesToInspect.push_back(start);

            day12_node destiny;
            set<pair<int, int>> visited;

            while (nodesToInspect.size() > 0)
            {
                day12_node node = nodesToInspect[0];
                nodesToInspect.erase(nodesToInspect.begin());

                if (visited.find({ node.row, node.col }) != visited.end())
                {
                    continue;
                }

                visited.insert({ node.row, node.col });

                if (maze[node.row][node.col] == endElement[i])
                {
                    destiny = node;
                    nodesToInspect.clear();
                    continue;
                }
                else
                {
                    const std::vector<std::pair<int, int>> movements = { {0,1},{0,-1},{1,0},{-1,0} };
                    for (std::pair<int, int> movement : movements)
                    {
                        if (day12_validNode(node.row, node.col, node.row + movement.first, node.col + movement.second, maze)
                            && visited.find({ node.row + movement.first, node.col + movement.second }) == visited.end())
                        {
                            day12_node newNode{ maze[node.row + movement.first][node.col + movement.second], node.timesToReach + 1, node.row + movement.first, node.col + movement.second };
                            nodesToInspect.push_back(newNode);
                        }
                    }
                }
            }

            std::cout << destiny.timesToReach<<",";
        }
        std::cout << "\n";

    }
    file.close();
}

struct day13_node
{
public:
    long long valueInt =-1;
    day13_node* valueList;
    day13_node* next = nullptr;
    day13_node* parent = nullptr;
    int totalElements = 0;
    bool isNumber = false;
    string txt;
};

day13_node* day13_parseLine(const std::string& line)
{
    day13_node* toReturn = new day13_node();
    toReturn->txt = line;
    day13_node* whereToAdd = toReturn;

    int actualIndex = 0;
    while(actualIndex < line.size())
    {
        char c = line[actualIndex];//can be [ ] , <number>
        if (c == '[')
        {
            //go deep
            day13_node* toAdd = new day13_node();
            toAdd->parent = whereToAdd;
            //first [
            whereToAdd->valueList = toAdd;
            whereToAdd = toAdd;
        }
        else
        {
            if (c == ']')
            {
                if (whereToAdd->parent)
                {
                    whereToAdd->parent->totalElements++;
                }
                whereToAdd = whereToAdd->parent;
            }
            else
            {
                if (c == ',')
                {
                    //create node
                    day13_node * toAdd = new day13_node();
                    toAdd->parent = whereToAdd->parent;
                    whereToAdd->next = toAdd;

                    if (whereToAdd->parent)
                    {
                        whereToAdd->parent->totalElements++;
                    }

                    whereToAdd = toAdd;
                }
                else
                {
                    //get value
                    string tmp = line.substr(actualIndex);
                    auto positionComma = tmp.find(",");
                    auto positionBracket = tmp.find("]");

                    auto realPos = min(positionBracket, positionComma);
                    long long value = atoll(tmp.substr(0, realPos).c_str());
                    actualIndex += realPos-1;//still in the comma or the ]
                    
                    whereToAdd->valueInt = value;
                    whereToAdd->isNumber = true;
                }
            }
        }
        ++actualIndex;
    }
    return toReturn;
}

/*
int day13_compare_old(day13_node* a, day13_node* b)
{
    day13_node* pointerA = a;
    day13_node* pointerB = b;

    while (pointerA != nullptr && pointerB != nullptr)
    {
        if (pointerA->value == nullptr && pointerB->value == nullptr)
        {
            if (pointerA->valueInt == -1 && pointerB->valueInt != -1) { return -1; }
            if (pointerA->valueInt != -1 && pointerB->valueInt == -1) { return 1; }
            if (pointerA->valueInt < pointerB->valueInt) { return -1; }
            if (pointerA->valueInt > pointerB->valueInt) { return 1; }

            //move to next
            if (pointerA->next == nullptr && pointerB->next != nullptr)
            {
                return -1;
            }
            if (pointerA->next != nullptr && pointerB->next == nullptr)
            {
                return 1;
            }
            //here, next for both is null or a value
            if (pointerA->next == nullptr)
            {
                pointerA = pointerA->parent->next;
            }
            else
            {
                pointerA = pointerA->next;
            }

            if (pointerB->next == nullptr)
            {
                pointerB = pointerB->parent->next;
            }
            else
            {
                pointerB = pointerB->next;
            }
        }
        else
        {
            if (pointerA->value != nullptr && pointerB->value != nullptr)
            {
                pointerB = pointerB->value;
                pointerA = pointerA->value;
                continue;
            }

            //here one is list, and the other not
            if (pointerA->next == nullptr && pointerB->next != nullptr)
            {
                //a list short
                return -1;
            }
            if (pointerA->next != nullptr && pointerB->next == nullptr)
            {
                //b list short
                return 1;
            }


            ////at least one is a list, go inside
            if (pointerA->value != nullptr)
            {
                pointerA = pointerA->value;
            }
            if (pointerB->value != nullptr)
            {
                pointerB = pointerB->value;
            }
        }
    }

    if (pointerA == nullptr && pointerB != nullptr)
    {
        return 1;
    }
    if (pointerA != nullptr && pointerB == nullptr)
    {
        return -1;
    }

    return 0;
}
*/
int day13_compare(day13_node* a, day13_node* b)
{
    if (a == nullptr && b == nullptr) { return 0; }
    if (a == nullptr && b != nullptr) { return -1; }
    if (a != nullptr && b == nullptr) { return 1; }

    if (a->isNumber && b->isNumber)
    {
        if (a->valueInt < b->valueInt) { return -1; }
        if (a->valueInt > b->valueInt) { return 1; }
        return 0;
    }

    if (a->isNumber && !b->isNumber)
    {
        return day13_compare(a, b->valueList);
    }

    if (!a->isNumber && b->isNumber)
    {
        return day13_compare(a->valueList, b);
    }

    //here a is list, b is list
    if (a->totalElements == 0 && b->totalElements == 0) { return 0; }
    if (a->totalElements == 0 && b->totalElements != 0) { return -1; }
    if (a->totalElements != 0 && b->totalElements == 0) { return 1; }

    day13_node* pointerA = a->valueList;
    day13_node* pointerB = b->valueList;

    while (pointerA && pointerB)
    {
        auto result = day13_compare(pointerA, pointerB);

        if (result == 0)
        {
            pointerA = pointerA->next;
            pointerB = pointerB->next;
        }
        else
        {
            return result;
        }
    }

    if (pointerA && !pointerB) { return 1; }
    if (!pointerA && pointerB) { return -1; }
    return 0;

}

void day13()
{
    std::ifstream file("./input/day13.txt");
    if (file.is_open())
    {
        string line;
        string line2;
        long long result = 0;
        int index = 1;
        vector<day13_node*> allNodes;
        while (std::getline(file, line))
        {
            auto a = day13_parseLine(line);
            std::getline(file, line2);
            auto b = day13_parseLine(line2);

            int comparation = day13_compare(a, b);
            if (comparation < 0)
            {
                result += index;
            }

            allNodes.push_back(a);
            allNodes.push_back(b);
            std::getline(file, line);
            ++index;
        }

        allNodes.push_back(day13_parseLine("[[2]]"));
        allNodes.push_back(day13_parseLine("[[6]]"));

        std::sort(allNodes.begin(), allNodes.end(), [](day13_node* a, day13_node* b) 
            {
                int v = day13_compare(a, b); 
                return v == -1;
            });


        long long result2 = 1;

        for (int i = 0; i < allNodes.size(); ++i)
        {
            if (allNodes[i]->txt == "[[2]]") { result2 *= (i + 1); }
            if (allNodes[i]->txt == "[[6]]") { result2 *= (i + 1); }
        }

        std::cout << "day 13 => " << result << "," << result2 << "\n";
    }
    file.close();
}

int main()
{
    day1();
    day2();
    day3();
    day3_2();
    day4();
    day5();
    day6();
    day7();
    day8();
    day9();
    day10();
    day11(false);
    day12();
    day13();
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
