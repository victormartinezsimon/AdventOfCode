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
            std::string l2 = line.substr( line.find(",") +1);

            int l1a = atoi(l1.substr(0, l1.find("-")).c_str());
            int l1b = atoi(l1.substr( l1.find("-") + 1).c_str());

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
        std::cout << "Day4 =>" << scoreFullOverlap << "," << scoreSingleOverlap<<"\n";
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

    for(int i = startEndIndex - totalDifferent; i < startEndIndex; ++i)
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
                    std::cout << "day 6 =>" << (indexFirstPart)<<",";
                    break;
                }
                ++indexFirstPart;
            }

            int indexSecondPart = 14;
            while (indexSecondPart < line.size())
            {
                if (day6_allDiferent(line, indexSecondPart, 14))
                {
                    std::cout << (indexSecondPart)<< "\n";
                    break;
                }
                ++indexSecondPart;
            }

        }
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
