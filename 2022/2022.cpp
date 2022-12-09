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
        std::cout << "," << solution2 <<"\n";
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
            day8_count(board, board.size()-1, i, -1, 0, unique_trees);
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
        std::cout << "," <<bestTreeScore << "\n";
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
                positionsVisitedMultiple.insert({ multiplePositions.back().row, multiplePositions.back().col});
            }
        }
        std::cout << "Day9=>" << positionsVisitedSingle.size() << "," << positionsVisitedMultiple.size() << "\n";
    }
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
