// 2015.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
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
#include "md5.h"

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


void day1()
{
    auto  fileTxt = ReadFile("./input/day1.txt");

    int count = 0;
    int partB = -1;

    int index = 1;
    for (auto c : fileTxt[0])
    {
        if (c == '(')
        {
            ++count;
        }
        else
        {
            --count;
        }

        if (count < 0 && partB == -1)
        {
            partB = index;
        }
        ++index;
    }

    std::cout << "day1_a => " << count << "\n";
    std::cout << "day1_b => " << partB << "\n";


}

void day2()
{
    auto fileTxt = ReadFile("./input/day2.txt");

    long long acum = 0;

    long long acumRibbon = 0;

    for (auto l : fileTxt)
    {
        auto values = split(l, "x");

        auto v1 = atoi(values[0].c_str());
        auto v2 = atoi(values[1].c_str());
        auto v3 = atoi(values[2].c_str());

        auto value = (2 * v1 * v2) + (2 * v1 * v3) + (2 * v2 * v3);

        auto mult12 = v1 * v2;
        auto mult13 = v1 * v3;
        auto mult23 = v2 * v3;

        auto ribbonBase = v1 * v2 * v3;

        if (mult12 <= mult13 && mult12 <= mult23)
        {
            acum += (value + mult12);

            acumRibbon += ribbonBase + (v1 * 2) + (v2 * 2);

            continue;
        }

        if (mult13 <= mult12 && mult13 <= mult23)
        {
            acum += (value + mult13);

            acumRibbon += ribbonBase + (v1 * 2) + (v3 * 2);

            continue;
        }

        if (mult23 <= mult12 && mult23 <= mult13)
        {
            acum += (value + mult23);

            acumRibbon += ribbonBase + (v2 * 2) + (v3 * 2);
            continue;
        }
    }
    std::cout << "day2_a => " << acum << "\n";
    std::cout << "day2_b => " << acumRibbon << "\n";
}


void day3_addVisited(map<pair<int, int>, int>& map, pair<int, int> position)
{
    if (map.find(position) == map.end())
    {
        map.insert({ position, 0 });
    }
    map[position]++;
}

void day3_updatePosition(char c, pair<int, int>& position)
{
    switch (c)
    {
        case '>': position.second++; break;
        case '<': position.second--; break;
        case '^': position.first--; break;
        case 'v': position.first++; break;
    }
}

void day3_a()
{
    auto fileTxt = ReadFile("./input/day3.txt");

    map<pair<int, int>, int> visited;

    pair<int, int> currentPosition{ 0,0 };

    day3_addVisited(visited, currentPosition);

    for (auto c : fileTxt[0])
    {
        day3_updatePosition(c, currentPosition);
        day3_addVisited(visited, currentPosition);
    }

    std::cout << "day3_a => " << visited.size() << "\n";

}


void day3_b()
{
    auto fileTxt = ReadFile("./input/day3.txt");

    map<pair<int, int>, int> visited;
    map<pair<int, int>, int> visited_robot;

    pair<int, int> currentPosition{ 0,0 };
    pair<int, int> currentPosition_robot{ 0,0 };

    day3_addVisited(visited, currentPosition);
    day3_addVisited(visited_robot, currentPosition_robot);

    bool isRobot = false;

    for (auto c : fileTxt[0])
    {
        if (isRobot)
        {
            day3_updatePosition(c, currentPosition_robot);
            day3_addVisited(visited_robot, currentPosition_robot);
        }
        else
        {
            day3_updatePosition(c, currentPosition);
            day3_addVisited(visited, currentPosition);
        }
        isRobot = !isRobot;
    }

    set<pair<int, int>> visitedAll;

    for (auto p : visited)
    {
        visitedAll.insert(p.first);
    }

    for (auto p : visited_robot)
    {
        visitedAll.insert(p.first);
    }


    std::cout << "day3_b => " << visitedAll.size() << "\n";
}

void day3()
{
    day3_a();
    day3_b();
}

void day4_a()
{
    string key = "bgvyzdsv";

    long long index = 0;
    while (true)
    {
        string k = key + std::to_string(index);

        auto hash_str = md5(k);
        
        if (hash_str[0] == '0' && hash_str[1] == '0' && hash_str[2] == '0' && hash_str[3] == '0' && hash_str[4] == '0')
        {
            std::cout << "day4_a => " << index << "\n";
            break;
        }
        
        ++index;
    }
}

void day4_b()
{
    string key = "bgvyzdsv";

    long long index = 0;
    while (true)
    {
        string k = key + std::to_string(index);

        auto hash_str = md5(k);

        if (hash_str[0] == '0' && hash_str[1] == '0' && hash_str[2] == '0' && hash_str[3] == '0' && hash_str[4] == '0' && hash_str[5] == '0')
        {
            std::cout << "day4_b => " << index << "\n";
            break;
        }

        ++index;
    }
}

void day4()
{
    //day4_a();
    //day4_b();
    std::cout << "day4_a => " << 254575 << "\n";
    std::cout << "day4_b => " << 1038736 << "\n";
}

bool day5_valid_a(const string& l)
{
    bool hasVowels = false;
    bool consecutiveLetters = false;
    bool invalidSequence = false;

    char lastLetter = 0;
    int vowelsCount = 0;
    vector<string> forbbiden = {"ab", "cd", "pq", "xy"};


    for (char c : l)
    {
        if (c == lastLetter)
        {
            consecutiveLetters = true;
        }

        if (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u')
        {
            ++vowelsCount;
        }

        for (auto f : forbbiden)
        {
            if (lastLetter == f[0] && c == f[1])
            {
                invalidSequence = true;
                break;
            }
        }

        lastLetter = c;
        if (invalidSequence)
        {
            break;
        }
    }

    hasVowels = (vowelsCount >= 3);

    return hasVowels && consecutiveLetters && !invalidSequence;

}

bool day5_valid_b(const string& l)
{
    std::map<string, int> two_lettersPositions;

    bool two_letters_check = false;
    bool three_letters_check = false;

    for (int i = 0; i < l.size(); ++i)
    {
        string sub_str = l.substr(i, 2);

        if (two_lettersPositions.find(sub_str) == two_lettersPositions.end())
        {
            two_lettersPositions.insert({ sub_str, i });
        }
        else
        {
            int index = two_lettersPositions[sub_str];
            int diff = i - index;
            if (diff > 1)
            {
                two_letters_check = true;
            }
        }

        string threeLetters = l.substr(i, 3);
        if (threeLetters.size() == 3)
        {
            if (threeLetters[0] == threeLetters[2])
            {
                three_letters_check = true;
            }
        }
    }

    return two_letters_check && three_letters_check;
}

void day5()
{
    auto fileTxt = ReadFile("./input/day5.txt");

    long long count_a = 0;
    long long count_b = 0;

    for (auto l : fileTxt)
    {
        if (day5_valid_a(l))
        {
            ++count_a;
        }

        if (day5_valid_b(l))
        {
            ++count_b;
        }
    }

    std::cout << "day5_a => " << count_a << "\n";
    std::cout << "day5_b => " << count_b << "\n";
}

void day6_toggle(const string& line, std::vector<std::vector<int>>& board, bool partA)
{
    //toggle, <x,y>, through, <x, y>
    auto sp = split(line, " ");

    auto start_str = split( sp[1],",");
    auto end_str = split(sp[3], ",");

    int startX = atoi(start_str[0].c_str());
    int endX = atoi(end_str[0].c_str());

    int startY = atoi(start_str[1].c_str());
    int endY = atoi(end_str[1].c_str());

    for (int x = startX; x <= endX; ++x)
    {
        for (int y = startY; y <= endY; ++y)
        {
            if (partA)
            {
                if (board[y][x] == 1)
                {
                    board[y][x] = 0;
                }
                else
                {
                    board[y][x] = 1;
                }
            }
            else
            {
                board[y][x] += 2;
            }
        }
    }
}

void day6_off(const string& line, std::vector<std::vector<int>>& board, bool partA)
{
    //turn,off, <x,y>, through, <x, y>
    auto sp = split(line, " ");

    auto start_str = split(sp[2], ",");
    auto end_str = split(sp[4], ",");

    int startX = atoi(start_str[0].c_str());
    int endX = atoi(end_str[0].c_str());

    int startY = atoi(start_str[1].c_str());
    int endY = atoi(end_str[1].c_str());

    for (int x = startX; x <= endX; ++x)
    {
        for (int y = startY; y <= endY; ++y)
        {
            if (partA)
            {
                board[y][x] = 0;
            }
            else
            {
                board[y][x]--;
                if (board[y][x] < 0)
                {
                    board[y][x] = 0;
                }
            }
        }
    }
}

void day6_on(const string& line, std::vector<std::vector<int>>& board, bool partA)
{
    //turn,off, <x,y>, through, <x, y>
    auto sp = split(line, " ");

    auto start_str = split(sp[2], ",");
    auto end_str = split(sp[4], ",");

    int startX = atoi(start_str[0].c_str());
    int endX = atoi(end_str[0].c_str());

    int startY = atoi(start_str[1].c_str());
    int endY = atoi(end_str[1].c_str());

    for (int x = startX; x <= endX; ++x)
    {
        for (int y = startY; y <= endY; ++y)
        {
            if (partA)
            {
                board[y][x] = 1;
            }
            else
            {
                board[y][x]++;
            }
        }
    }
}


void day6_a()
{
    auto fileTxt = ReadFile("./input/day6.txt");

    std::vector<std::vector<int>> board(1000, vector<int>(1000, 0));

    for (auto l : fileTxt)
    {
        if (l.find("toggle") != string::npos)
        {
            day6_toggle(l, board, true);
        }

        if (l.find("turn off") != string::npos)
        {
            day6_off(l, board, true);
        }

        if (l.find("turn on") != string::npos)
        {
            day6_on(l, board, true);
        }
    }

    long long count = 0;
    for (int y = 0; y < board.size(); ++y)
    {
        string s;
        for (int x = 0; x < board.size(); ++x)
        {
            if (board[y][x] == 1)
            {
                ++count;
            }
        }
    }

    std::cout << "day6_a=> " << count << "\n";

}
void day6_b()
{
    auto fileTxt = ReadFile("./input/day6.txt");

    std::vector<std::vector<int>> board(1000, vector<int>(1000, 0));

    for (auto l : fileTxt)
    {
        if (l.find("toggle") != string::npos)
        {
            day6_toggle(l, board, false);
        }

        if (l.find("turn off") != string::npos)
        {
            day6_off(l, board, false);
        }

        if (l.find("turn on") != string::npos)
        {
            day6_on(l, board, false);
        }
    }

    long long count = 0;
    for (int y = 0; y < board.size(); ++y)
    {
        string s;
        for (int x = 0; x < board.size(); ++x)
        {
            count += board[y][x];
        }
    }

    std::cout << "day6_b=> " << count << "\n";

}

void day6()
{
    day6_a();
    day6_b();
}

struct day7_node
{
public:
    string id;
    std::array<string, 2> ancestors;
    unsigned short value;
    bool hasValue = false;
    string typeFunction;

private:
 
    bool getAncestorValue(string key, const map<string, day7_node>& nodes, unsigned short& value)
    {
        if (nodes.find(key) == nodes.end())
        {
            value = atoi(key.c_str());
            return true;
        }

        if (nodes.at(key).hasValue)
        {
            value = nodes.at(key).value;
            return true;
        }
        return false;
    }

    void TryCalculateAnd(const map<string, day7_node>& nodes)
    {
        unsigned short v1;
        unsigned short v2;

        if(getAncestorValue(ancestors[0],nodes, v1) && getAncestorValue(ancestors[1],nodes,  v2))
        {
            value = v1 & v2;
            hasValue = true;
        }
    }

    void TryCalculateOR(const map<string, day7_node>& nodes)
    {
        unsigned short v1;
        unsigned short v2;

        if (getAncestorValue(ancestors[0], nodes, v1) && getAncestorValue(ancestors[1], nodes, v2))
        {
            value = v1 | v2;
            hasValue = true;
        }
    }

    void TryCalculateXOR(const map<string, day7_node>& nodes)
    {
        unsigned short v1;
        unsigned short v2;

        if (getAncestorValue(ancestors[0], nodes, v1) && getAncestorValue(ancestors[1], nodes, v2))
        {
            value = v1 ^ v2;
            hasValue = true;
        }
    }

    void TryCalculateNOT(const map<string, day7_node>& nodes)
    {
        unsigned short v1;

        if (getAncestorValue(ancestors[0], nodes, v1))
        {
            value = ~v1;
            hasValue = true;
        }
    }

    void TryCalculateLShift(const map<string, day7_node>& nodes)
    {
        unsigned short v1;
        unsigned short v2;

        if (getAncestorValue(ancestors[0], nodes, v1) && getAncestorValue(ancestors[1], nodes, v2))
        {
            value = v1 << v2;
            hasValue = true;
        }
    }

    void TryCalculateRShift(const map<string, day7_node>& nodes)
    {
        unsigned short v1;
        unsigned short v2;

        if (getAncestorValue(ancestors[0], nodes, v1) && getAncestorValue(ancestors[1], nodes, v2))
        {
            value = v1 >> v2;
            hasValue = true;
        }
    }

    void TryAssign(const map<string, day7_node>& nodes)
    {
        unsigned short v1;

        if (getAncestorValue(ancestors[0], nodes, v1))
        {
            value = v1;
            hasValue = true;
        }
    }

public:
    void TryCalculateValue(const map<string, day7_node>& nodes)
    {
        if (typeFunction == "AND")
        {
            TryCalculateAnd(nodes);
            return;
        }

        if (typeFunction == "OR")
        {
            TryCalculateOR(nodes);
            return;
        }

        if (typeFunction == "XOR")
        {
            TryCalculateXOR(nodes);
            return;
        }

        if (typeFunction == "NOT")
        {
            TryCalculateNOT(nodes);
            return;
        }

        if (typeFunction == "LSHIFT")
        {
            TryCalculateLShift(nodes);
            return;
        }

        if (typeFunction == "RSHIFT")
        {
            TryCalculateRShift(nodes);
            return;
        }

        if (typeFunction == "ASSIGN")
        {
            TryAssign(nodes);
            return;
        }
    }

    vector<string> getUnknownParent(const map<string, day7_node>& nodes)
    {
        unsigned short v1;

        vector<string> result;

        if (!getAncestorValue(ancestors[0], nodes, v1))
        {
            result.push_back(ancestors[0]);
        }

        if (typeFunction != "NOT" && typeFunction != "ASSIGN")
        {
            if (!getAncestorValue(ancestors[1], nodes, v1))
            {
                result.push_back(ancestors[1]);
            }
        }

        return result;
    }
};


void day7_getValue(const string& nodeID, map<string, day7_node>& nodes)
{
    std::stack<string> nodesToAnalyze;

    nodesToAnalyze.push(nodeID);

    while (nodesToAnalyze.size() != 0)
    {
        auto nodeId = nodesToAnalyze.top();
        nodesToAnalyze.pop();

        if (nodes[nodeId].hasValue)
        {
            continue;
        }

        nodes[nodeId].TryCalculateValue(nodes);

        if (!nodes[nodeId].hasValue)
        {

            nodesToAnalyze.push(nodeId);
            auto unknown = nodes[nodeId].getUnknownParent(nodes);

            for (auto&& node : unknown)
            {
                nodesToAnalyze.push(node);
            }
        }
    }
}

void day7_parseLine(const string& line, map<string, day7_node>& nodes)
{
    auto line_split = split(line, " -> ");

    string destNode = trim_copy(line_split.back());

    string precedent = trim_copy(line_split[0]);

    day7_node node;
    node.id = destNode;


    bool findSomeFunction = false;

    for (std::string funsWithTwoElements : {"AND", "XOR", "OR", "LSHIFT", "RSHIFT"})
    {
        if (findSomeFunction) { continue; }

        if (precedent.find(funsWithTwoElements) != string::npos)
        {
            node.typeFunction = funsWithTwoElements;

            auto ancestors = split(precedent, funsWithTwoElements);

            node.ancestors[0] = trim_copy(ancestors[0]);
            node.ancestors[1] = trim_copy(ancestors[1]);
            node.hasValue = false;
            findSomeFunction = true;
        }
    }

    if (!findSomeFunction)
    {
        if (precedent.find("NOT") != string::npos)
        {
            node.typeFunction = "NOT";

            auto ancestors = split(precedent, "NOT ");

            node.ancestors[0] = trim_copy(ancestors[1]);
            node.hasValue = false;
            findSomeFunction = true;
        }
    }

    if (!findSomeFunction)
    {
        //assing value
        node.typeFunction = "ASSIGN";
        node.ancestors[0] = trim_copy(line_split[0]);
    }
       
    nodes.insert({ destNode, node });
}

void day7_resetWires(map<string, day7_node>& nodes)
{
    for (auto p : nodes)
    {
        nodes[p.first].hasValue = false;
    }
}

void day7()
{
    auto fileTxt = ReadFile("./input/day7.txt");

    map<string, day7_node> nodes;

    for (auto&& l : fileTxt)
    {
        day7_parseLine(l, nodes);
    }

    day7_getValue("a", nodes);

    auto value_a = nodes["a"].value;

    std::cout << "day7_a => " << nodes["a"].value << "\n";

    day7_resetWires(nodes);

    nodes["b"].ancestors[0] = std::to_string(value_a);

    day7_getValue("a", nodes);
    std::cout << "day7_b => " << nodes["a"].value << "\n";

}

int day8_countValidChars(const string& str)
{
    int index = 0;

    int count = 0;

    while (index < str.size())
    {
        if (str[index] != '\\')
        {
            ++count;
            ++index;
            continue;
        }
       
        ++index;

        if (str[index] == '\"' || str[index] == '\\')
        {
            ++count;
            ++index;
            continue;
        }

        if (str[index] == 'x')
        {
            index = index + 2 + 1;//not check about not hexadecimal values
            ++count;
            continue;
        }


        //here we found a \ but nothing special after, so its a valid characer
        ++count;
        ++index;
        continue;
    }

    return count;
}

int day8_encodeChars(const string& str)
{
    int count = 0;

    for (char c : str)
    {
        if (c == '\"' || c == '\\')
        {
            count += 2;
        }
        else
        {
            ++count;
        }
    }

    return count;

}

void day8()
{
    auto fileTxt = ReadFile("./input/day8.txt");

    int total_a = 0;
    int total_b = 0;

    for (auto l : fileTxt)
    {
        int count_a = day8_countValidChars(l) - 2;
        total_a += (l.size() - count_a);

        int count_b = day8_encodeChars(l) + 2;
        total_b += (count_b - l.size());
    }

    std::cout << "day8_a => " << total_a << "\n";
    std::cout << "day8_b => " << total_b << "\n";
}

struct day9_node
{
public:
    int cost = std::numeric_limits<int>::max();
    bool visited = false;
    day9_node* parent = nullptr;
    vector<pair<int, day9_node*>> neightbours;

    void reset()
    {
        cost = std::numeric_limits<int>::max();
        visited = false;
        parent = nullptr;
    }
};

void day9_buildGraph(const std::vector<string>& lines, map<string, day9_node*>& graph )
{
    for (auto l : lines)
    {
        auto split_cost = split(l, "=");
        int cost = atoi(split_cost[1].c_str());

        auto split_keys = split(split_cost[0], "to");
        string k1 = trim_copy(split_keys[0]);
        string k2 = trim_copy(split_keys[1]);

        if (graph.find(k1) == graph.end())
        {
            day9_node* n = new day9_node();
            graph.insert({ k1, n });
        }

        if (graph.find(k2) == graph.end())
        {
            day9_node* n = new day9_node();
            graph.insert({ k2, n });
        }

        //add as neightbours
        graph[k1]->neightbours.push_back({ cost, graph[k2] });
        graph[k2]->neightbours.push_back({ cost, graph[k1] });

    }

}

int day9_findPath(map<string, day9_node*>& graph, day9_node* currentNode, bool partB)
{
    for (auto kvp : graph)
    {
        graph[kvp.first]->reset();
    }

    int current_cost = 0;

    while (currentNode != nullptr)
    {
        currentNode->cost = current_cost;
        currentNode->visited = true;

        day9_node* nextNode = nullptr;
        int index_selected = -1;

        int bestCost = 0;
        if (partB)
        {
            bestCost = std::numeric_limits<int>::min();
        }
        else
        {
            bestCost = std::numeric_limits<int>::max();
        }
        
        for (int i = 0; i < currentNode->neightbours.size(); ++i)
        {
            int cost = currentNode->neightbours[i].first;

            bool valid = false;

            if (partB)
            {
                valid = cost > bestCost;
            }
            else
            {
                valid = cost < bestCost;
            }

            if (valid && !currentNode->neightbours[i].second->visited)
            {
                nextNode = currentNode->neightbours[i].second;
                bestCost = cost;
                index_selected = i;
            }
        }

        if (nextNode != nullptr)
        {
            current_cost += currentNode->neightbours[index_selected].first;
        }

        currentNode = nextNode;
    }


    return current_cost;
}

void day9()
{
    auto fileTxt = ReadFile("./input/day9.txt");

    map<string, day9_node*> graph;

    day9_buildGraph(fileTxt, graph);

    int min_bestValue = std::numeric_limits<int>::max();
    int max_bestValue = std::numeric_limits<int>::min();

    for (auto kvp : graph)
    {
        int value_min = day9_findPath(graph, kvp.second, false);
        int value_max = day9_findPath(graph, kvp.second, true);

        if (value_min < min_bestValue)
        {
            min_bestValue = value_min;
        }

        if (value_max > max_bestValue)
        {
            max_bestValue = value_max;
        }
    }
    std::cout << "day9_a =>" << min_bestValue << "\n";
    std::cout << "day9_b =>" << max_bestValue << "\n";

}

std::string day10_parse(const string& str)
{
    std::string result = "";

    char lastChar = 0;
    int count = 0;

    for (char c : str)
    {
        if (c == lastChar)
        {
            ++count;
        }
        else
        {
            if (lastChar != 0)
            {
                result += std::to_string(count) + lastChar;
            }
            lastChar = c;
            count = 1;  
        }
    }
    result += std::to_string(count) + lastChar;
    return result;
}

void day10()
{
    auto original_str = ReadFile("./input/day10.txt")[0];

    string str_a = original_str;
    for (int i = 0; i < 40; ++i)
    {
        str_a = day10_parse(str_a);
    }

    std::cout << "day10_a => " << str_a.size() << "\n";

    string str_b = str_a;
    for (int i = 40; i < 50; ++i)
    {
        str_b = day10_parse(str_b);
    }
    std::cout << "day10_b => " << str_b.size() << "\n";
}

string day11_getNextPassword(const string& str)
{
    int index = str.size() - 1;

    string sufix = "";

    while (index >= 0 && str[index] == 'z')
    {
        sufix = sufix + 'a';
        --index;
    }

    string solution = "";
    if (index >= 0)
    {
        string prefix = str.substr(0, index);
        solution = prefix + static_cast<char>(str[index]+1) + sufix;
    }
    else
    {
        solution = 'a' + sufix;
    }

    return solution;
}

bool day11_firstCheck(const string& str)
{
    for (int i = 0; i < str.size() - 2; ++i)
    {
        char c1 = str[i];
        char c2 = str[i + 1];
        char c3 = str[i + 2];

        if (c1 + 1 == c2 && c2 + 1 == c3)
        {
            return true;
        }
    }

    return false;
}

bool day11_secondCheck(const string& str)
{
    for (int i = 0; i < str.size(); ++i)
    {
        if (str[i] == 'i' || str[i] == 'o' || str[i] == 'l')
        {
            return false;
        }
    }
    return true;
}

bool day11_thirdCheck(const string& str)
{
    int index = 0;
    char lastChar = 0;
    int countValid = 0;

    while (index < str.size())
    {
        if (str[index] == lastChar)
        {
            countValid++;
            lastChar = 0;
            ++index;//skip so aaa is not counted
        }
        else
        {
            lastChar = str[index];
        }
        ++index;
    }

    return countValid >= 2;
}

void day11()
{
    auto original_str = ReadFile("./input/day11.txt")[0];

    bool continueSearching = true;

    string newPass = original_str;

    while (continueSearching)
    {
        newPass = day11_getNextPassword(newPass);

        continueSearching = !(day11_firstCheck(newPass) && day11_secondCheck(newPass) && day11_thirdCheck(newPass));
    }

    std::cout << "day 11_a " << newPass << "\n";

    continueSearching = true;
    while (continueSearching)
    {
        newPass = day11_getNextPassword(newPass);

        continueSearching = !(day11_firstCheck(newPass) && day11_secondCheck(newPass) && day11_thirdCheck(newPass));
    }
    std::cout << "day 11_b " << newPass << "\n";
}

int day12_findNumbers(const string& str)
{
    bool isDigitExtract = false;
    string digitExtracted = "";
    int sum = 0;

    for (char c : str)
    {
        if (('0' <= c && c <= '9') || c == '-')
        {
            digitExtracted += c;
            isDigitExtract = true;
        }
        else
        {
            if (isDigitExtract)
            {
                int value = atoi(digitExtracted.c_str());
                sum += value;
                digitExtracted = "";
            }
            isDigitExtract = false;
        }
    }
    return sum;
}

int day12_findCloseSymbol(char c, int index, const string& str)
{
    int myIndex = index;

    stack<char> symbols;
    symbols.push(c);

    while (myIndex < str.size())
    {
        char c = str[myIndex];

        if (c == '{' || c == '[')
        {
            symbols.push(c);
            ++myIndex;
            continue;
        }
        
        if (c == '}' || c == ']')
        {
            char topChar = symbols.top();

            if (topChar == '{' && c == '}')
            {
                symbols.pop();
            }

            if (topChar == '[' && c == ']')
            {
                symbols.pop();
            }

            ++myIndex;

            if (symbols.size() == 0)
            {
               
                return myIndex;
            }

            continue;
        }
        ++myIndex;
    }


    return str.size();
}

void day12_addToStack(stack<int>& stack, int value)
{
    int v = stack.top();
    v += value;

    stack.pop();
    stack.push(v);
}

void day12_addNumber(stack<int>& values, const string& str)
{
    int v = atoi(str.c_str());
    day12_addToStack(values, v);
}

int day12_partB(const string& str)
{
    stack<int> values;
    values.push(0);

    stack <char> lastGroup;

    int index = 0;


    while (index < str.size())
    {
        char c = str[index];

        if (c == '{' || c == '[')
        {
            values.push(0);
            lastGroup.push(c);
            ++index;
            continue;
        }

        if (c == '}' || c == ']')
        {
            int v = values.top();
            values.pop();

            day12_addToStack(values, v);

            lastGroup.pop();

            ++index;
            continue;
        }

        if (c == 'r')
        {
            char c2 = str[index + 1];
            char c3 = str[index + 2];
            if (c2 == 'e' && c3 == 'd')
            {
                char lastTop = lastGroup.top();

                if (lastTop == '{')
                {
                    //discard
                    values.pop();
                    index = day12_findCloseSymbol(lastGroup.top(), index, str);
                    lastGroup.pop();
                }
                else
                {
                    index += 2;
                }
                continue;
            }
            else
            {
                ++index;
            }
        }

        if ((c == '-') || ('0' <= c && c <= '9'))
        {
            string numberStr = "";
            bool findNumber = true;

            while (findNumber)
            {
                char cNumber = str[index];

                if ((cNumber == '-') || ('0' <= cNumber && cNumber <= '9'))
                {
                    numberStr += cNumber;
                    ++index;
                }
                else
                {
                    findNumber = false;
                }
            }
           
            day12_addNumber(values, numberStr);

            continue;
        }
        //another not important symbol
        ++index;
       
    }

    return values.top();
}

void day12()
{
    auto original_str = ReadFile("./input/day12.txt")[0];

    int part_a = day12_findNumbers(original_str);

    std::cout << "day 12_a " << part_a << "\n";

    int part_b = day12_partB(original_str);
    std::cout << "day 12_b " << part_b << "\n";
}

int main()
{
   //day1();
   //day2();
   //day3();
   //day4();
   //day5();
   //day6();
   //day7();
   //day8();
   //day9();
   //day10();
   //day11();
   day12();
   //day13();
   //day14();
   //day15();
   //day16();
   //day17();
   //day18();
   //day19();
   //day20();
   //day21();
   //day22();
   //day23();
   //day24();
   //day25();
}

// Ejecutar programa: Ctrl + F5 o menú Depurar > Iniciar sin depurar
// Depurar programa: F5 o menú Depurar > Iniciar depuración

// Sugerencias para primeros pasos: 1. Use la ventana del Explorador de soluciones para agregar y administrar archivos
//   2. Use la ventana de Team Explorer para conectar con el control de código fuente
//   3. Use la ventana de salida para ver la salida de compilación y otros mensajes
//   4. Use la ventana Lista de errores para ver los errores
//   5. Vaya a Proyecto > Agregar nuevo elemento para crear nuevos archivos de código, o a Proyecto > Agregar elemento existente para agregar archivos de código existentes al proyecto
//   6. En el futuro, para volver a abrir este proyecto, vaya a Archivo > Abrir > Proyecto y seleccione el archivo .sln
