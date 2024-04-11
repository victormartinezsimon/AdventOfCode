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

struct day13_node
{
public:
    int cost = std::numeric_limits<int>::max();
    bool visited = false;
    string id;
    //vector<pair<int, day9_node*>> neightbours;
    map<string, int> neightbourCost;

    void reset()
    {
        cost = std::numeric_limits<int>::max();
        visited = false;
    }

    void addNeigtbourCost(string key, int cost)
    {
        if (neightbourCost.find(key) == neightbourCost.end())
        {
            neightbourCost.insert({ key, 0 });
        }
        
        neightbourCost[key] += cost;
    }
};

void day13_buildGraph(const std::vector<string>& lines, map<string, day13_node*>& nodes)
{
    nodes.clear();

    for (auto l : lines)
    {
        //Alice would gain 2 happiness units by sitting next to Bob.
        auto keys = split(l, " ");
        string k1 = trim_copy(keys[0]);
        string k2 = trim_copy(keys.back());
        k2 = k2.substr(0, k2.size() - 1);

        auto endNumber = l.find("happiness");
        auto gain = l.find("gain");

        int number = 0;

        if (gain != std::string::npos)
        {
            auto number_str = l.substr(gain + 4, endNumber - (gain + 4));
            number = atoi(number_str.c_str());
        }
        else
        {
            auto lose = l.find("lose");
            auto number_str = l.substr(lose + 4, endNumber - (lose + 4));
            number = -atoi(number_str.c_str());
        }
        
        if (nodes.find(k1) == nodes.end())
        {
            day13_node* n = new day13_node();
            n->id = k1;
            nodes.insert({ k1, n });
        }

        if (nodes.find(k2) == nodes.end())
        {
            day13_node* n = new day13_node();
            n->id = k2;
            nodes.insert({ k2, n });
        }

        nodes.at(k1)->addNeigtbourCost(k2, number);
        nodes.at(k2)->addNeigtbourCost(k1, number);
    }
}

int day13_findBest(map<string, day13_node*>& nodes, day13_node* start)
{
    for (auto kvp : nodes)
    {
        nodes[kvp.first]->reset();
    }

    int cost = 0;
    day13_node* next = start;

    while (next != nullptr)
    {
        next->visited = true;

        int bestScore = std::numeric_limits<int>::min();
        string bestNode_str = "";

        for (auto neigtbourData : next->neightbourCost)
        {
            auto node_str = neigtbourData.first;
            auto cost = neigtbourData.second;

            if (cost > bestScore && !nodes[node_str]->visited)
            {
                bestScore = cost;
                bestNode_str = node_str;
            }
        }

        if (bestNode_str.size() != 0)
        {
            next = nodes[bestNode_str];
            cost += bestScore;
        }
        else
        {
            cost += next->neightbourCost[start->id];
            next = nullptr;//Just in case
        }
    }


    return cost;
}


int day13_b(map<string, day13_node*> nodes)
{
    day13_node* n = new day13_node();
    n->id = "me";
    nodes.insert({ "me", n });

    for (auto kvp : nodes)
    {
        if (kvp.first != "me")
        {
            nodes[kvp.first]->addNeigtbourCost("me", 0);
            nodes["me"]->addNeigtbourCost(kvp.first, 0);
        }
    }

    int bestCost_b = std::numeric_limits<int>::min();

    for (auto kvp : nodes)
    {
        int cost = day13_findBest(nodes, kvp.second);

        if (cost > bestCost_b)
        {
            bestCost_b = cost;
        }
    }

    return bestCost_b;
}

void day13()
{
    auto lines = ReadFile("./input/day13.txt");

    map<string, day13_node*> nodes;
    day13_buildGraph(lines, nodes);

    int bestCost_a = std::numeric_limits<int>::min();

    for (auto kvp : nodes)
    {
        int cost = day13_findBest(nodes, kvp.second);

        if (cost > bestCost_a)
        {
            bestCost_a = cost;
        }
    }

    std::cout << "day13_a => " << bestCost_a << "\n";
    std::cout << "day13_b => " << day13_b(nodes) << "\n";

}

struct day14_reinder
{
public:
    day14_reinder(int v, int tMovement, int tRest) :velocity(v), timeMovement(tMovement), restTime(tRest) {}

public:
    const int velocity;
    const int timeMovement;
    const int restTime;

public:
    int b_currentDistance = 0;
    int b_ciclesResting = 0;
    int b_ciclesMovement = 0;

    bool b_resting = false;
    int b_score = 0;


    void doMovement()
    {
        if (!b_resting)
        {
            b_currentDistance += velocity;
            --b_ciclesMovement;

            if (b_ciclesMovement == 0)
            {
                b_resting = true;
                b_ciclesResting = restTime;
            }
        }
        else
        {
            --b_ciclesResting;
            if (b_ciclesResting == 0)
            {
                b_resting = false;
                b_ciclesMovement = timeMovement;
            }
        }
       
    }

    void resetMovement()
    {
        b_resting = false;
        b_ciclesMovement = timeMovement;
        b_score = 0;
        b_currentDistance = 0;
    }
};

day14_reinder day14_parseString(const string& line)
{
    auto restTime_split = split(line, " ");

    auto velocity = atoi(restTime_split[3].c_str());
    auto timeMovement = atoi(restTime_split[6].c_str());
    auto restTime = atoi(restTime_split[restTime_split.size() - 2].c_str());

    day14_reinder toReturn(velocity, timeMovement, restTime);

    return toReturn;
}

int day14_partA(const day14_reinder& reinder, int totalSeconds)
{
    
    auto velocity = reinder.velocity;
    auto timeMovement = reinder.timeMovement;
    auto restTime = reinder.restTime;

    int cicleTime = timeMovement + restTime;
    int distanceCycle = velocity * timeMovement;

    int totalCircles = totalSeconds / cicleTime;

    int solution = totalCircles * distanceCycle;

    //maybe there are some extra time
    int timeLeft = totalSeconds % cicleTime;

    if (timeLeft > timeMovement)
    {
        //we are resting
        solution += distanceCycle;
    }
    else
    {
        solution += (velocity * timeLeft);
    }
    

    return solution;
}

int day14_partB(vector<day14_reinder>& reinders, int totalSeconds)
{
    //all start rested
    for (int i = 0; i < reinders.size(); ++i)
    {
        reinders[i].resetMovement();
    }

    for (int i = 0; i < totalSeconds; ++i)
    {
        for (int reinderIdx = 0; reinderIdx < reinders.size(); ++reinderIdx)
        {
            reinders[reinderIdx].doMovement();
        }

        vector<int> bestReinders;
        int bestDistance = -1;

        for (int reinderIdx = 0; reinderIdx < reinders.size(); ++reinderIdx)
        {
            if (reinders[reinderIdx].b_currentDistance > bestDistance)
            {
                bestDistance = reinders[reinderIdx].b_currentDistance;
                bestReinders.clear();
                bestReinders.push_back(reinderIdx);
            }
            else
            {
                if (reinders[reinderIdx].b_currentDistance == bestDistance)
                {
                    bestReinders.push_back(reinderIdx);
                }
            }

        }
        for (auto idx : bestReinders)
        {
            reinders[idx].b_score++;
        }
    }

    int best = 0;

    for (int reinderIdx = 0; reinderIdx < reinders.size(); ++reinderIdx)
    {
        if (reinders[reinderIdx].b_score > best)
        {
            best = reinders[reinderIdx].b_score;
        }
    }

    return best;
}


void day14()
{
    auto lines = ReadFile("./input/day14.txt");
    int totalSeconds = 2503;

    int best_a = 0;

    vector<day14_reinder> reinders;

    for (auto l : lines)
    {
        reinders.push_back(day14_parseString(l));

        int score = day14_partA(reinders.back(), totalSeconds);

        if (score > best_a)
        {
            best_a = score;
        }
    }

    std::cout << "day14_a => " << best_a << "\n";

    int best_b = day14_partB(reinders, totalSeconds);
    std::cout << "day14_b => " << best_b << "\n";

}

struct day15_ingredient
{
public:
    string name;
    int capacity;
    int durability;
    int flavor;
    int texture;
    int calories;

public:
    day15_ingredient() {}

    day15_ingredient(const string& line)
    {
        auto double_points = line.find(":");

        name = line.substr(0, double_points);

        string other = line.substr(double_points +1);

        auto ingredients = split(other, ",");

        capacity = parse_ingredient(ingredients[0], "capacity");
        durability = parse_ingredient(ingredients[1], "durability");
        flavor = parse_ingredient(ingredients[2], "flavor");
        texture = parse_ingredient(ingredients[3], "texture");
        calories = parse_ingredient(ingredients[4], "calories");
    }

    int getValue(int index)const 
    {
        switch (index)
        {
        case 0:return capacity;
        case 1:return durability;
        case 2: return flavor;
        case 3: return texture;
        case 4: return calories;
        }
        return 0;
    }

private:
    int parse_ingredient(const string& str, const string& key)
    {
        auto capacity_str = split(str, key).back();
        return atoi(capacity_str.c_str());
    }
};

int day15_getScoreIngredient(const std::vector<day15_ingredient>& ingredients, const std::vector<int>& values, const int ingredientType)
{
    int value = 0;
    for (int ingredentIndex = 0; ingredentIndex < ingredients.size(); ++ingredentIndex)
    {
        value += ingredients[ingredentIndex].getValue(ingredientType) * values[ingredentIndex];
    }
    return value;
}

int day15_getScore_a(const int maxValue, const std::vector<day15_ingredient>& ingredients, const std::vector<int>& values)
{
    int valueAcum = std::accumulate(values.begin(), values.end(), 0);
    if (valueAcum != maxValue)
    {
        return -1;
    }

    if (ingredients.size() != values.size())
    {
        return -1;
    }

    int valueToReturn = 1;

    for (int ingredientType = 0; ingredientType < 4; ++ingredientType)
    {
        int value = day15_getScoreIngredient(ingredients, values, ingredientType);

        if (value <= 0)
        {
            return 0;
        }
        valueToReturn *= value;
    }
    
    return valueToReturn;
}

std::vector<std::vector<int>> day15_getAllPosiblities(const int valueLeft, int totalNumbers, map<string, std::vector<std::vector<int>>>& cache)
{
    string key = std::to_string(valueLeft) + "-" + std::to_string(totalNumbers);

    if (cache.find(key) != cache.end())
    {
        return cache[key];
    }

    if (valueLeft <= 0)
    {
        std::vector<std::vector<int>> result;
        return result;
    }

    if (totalNumbers == 1)
    {
        std::vector<std::vector<int>> result;
        result.push_back({ valueLeft });
        return result;
    }

    std::vector<std::vector<int>> result;
    for (int i = 1; i <= valueLeft; ++i)
    {
        auto res = day15_getAllPosiblities(valueLeft - i, totalNumbers - 1, cache);

        for (auto r : res)
        {
            r.insert(r.begin(), i);
            result.push_back(r);
        }
    }

    cache.insert({ key, result });

    return result;
}

int day15_a(const int maxValue, const std::vector<day15_ingredient>& ingredients, const std::vector<std::vector<int>>& allPosibilities)
{
    int best = -1;
    for (auto&& posibility : allPosibilities)
    {
        int score = day15_getScore_a(maxValue, ingredients, posibility);

        if (score > best)
        {
            best = score;
        }
    }

    return best;
}

int day15_b(const int maxValue, const std::vector<day15_ingredient>& ingredients, const std::vector<std::vector<int>>& allPosibilities, int exactCalories)
{
    int best = -1;

    for (auto&& posibility : allPosibilities)
    {
        int score = day15_getScore_a(maxValue, ingredients, posibility);
        int calories = day15_getScoreIngredient(ingredients, posibility, 4);

        if (score > best && calories == exactCalories)
        {
            best = score;
        }
    }


    return best;
}

void day15()
{
    auto lines = ReadFile("./input/day15.txt");

    vector<day15_ingredient> ingredients;

    for (auto line : lines)
    {
        day15_ingredient ing(line);
        ingredients.push_back(ing);
    }

    int maxSpoons = 100;

    map<string, std::vector<std::vector<int>>> cache;
    auto allPosibilities = day15_getAllPosiblities(maxSpoons, ingredients.size(), cache);
    int score_a = day15_a(maxSpoons, ingredients, allPosibilities);
    int score_b = day15_b(maxSpoons, ingredients, allPosibilities, 500);
    std::cout << "day15_a => " << score_a << "\n";
    std::cout << "day15_b => " << score_b << "\n";
}

struct day16_aunt
{
private:
    std::map<string, int> valuesAunt;

public:
    day16_aunt(const std::string & str)
    {
        auto first_doublePoints = str.find(":");

        auto values = str.substr(first_doublePoints + 1);

        for (string key : {"children", "cats", "samoyed", "pomeranians", "akitas", "vizslas", "goldfish", "trees", "cars", "perfumes"})
        {
            auto position = values.find(key);
            if (position == std::string::npos)
            {
                valuesAunt.insert({ key, -1 });
            }
            else
            {
                int startNumber = values.find(":", position) + 1;
                auto commaPosition = values.find(",", position);
                if (commaPosition == std::string::npos)
                {
                    commaPosition = values.size();
                }
                auto value_str = values.substr(startNumber, (commaPosition - startNumber));
                int value = atoi(value_str.c_str());

                valuesAunt.insert({ key, value });
            }
        }

    }
    day16_aunt(const std::map<string, int>& newValues) 
    {
        valuesAunt = newValues;
    }

    bool compareAunts(const day16_aunt& master)
    {
        for (auto kvp : master.valuesAunt)
        {
            auto key = kvp.first;
            auto value = kvp.second;

            auto myValue = valuesAunt[key];

            if (myValue != -1)
            {
                if (myValue != value)
                {
                    return false;
                }
            }

        }

        return true;
    }


    bool compareAunts_b(const day16_aunt& master)
    {
        for (auto kvp : master.valuesAunt)
        {
            auto key = kvp.first;
            auto value = kvp.second;

            auto myValue = valuesAunt[key];

            if (myValue != -1)
            {
                if (key == "cats" || key == "trees")
                {
                    if (myValue <= value)
                    {
                        return false;
                    }
                }
                else
                {
                    if (key == "pomeranians" || key == "goldfish")
                    {
                        if (myValue >= value)
                        {
                            return false;
                        }
                    }
                    else
                    {
                        if (myValue != value)
                        {
                            return false;
                        }
                    }
                }
            }

        }

        return true;
    }

};

void day16()
{
    auto lines = ReadFile("./input/day16.txt");

    std::vector< day16_aunt> aunts;

    for (auto l : lines)
    {
        day16_aunt aunt(l);
        aunts.push_back(aunt);
    }

    std::map<string, int> masterValues = {
        { "children",3 },
        { "cats",7 },
        { "samoyed",2 },
        { "pomeranians",3 },
        { "akitas",0,},
        { "vizslas",0 },
        { "goldfish",5 },
        { "trees",3 },
        { "cars",2 },
        { "perfumes",1 } 
    };

    day16_aunt masterAunt(masterValues);


    for (int index = 0; index < aunts.size(); ++index)
    {
        if (aunts[index].compareAunts(masterAunt))
        {
            std::cout << "day16_a => " << index + 1 << "\n";
        }

        if (aunts[index].compareAunts_b(masterAunt))
        {
            std::cout << "day16_b => " << index + 1 << "\n";
        }
    }

}

int day17_getCombinations_A(int value, std::vector<int> containers, map<string, int>& cache)
{
    if (value == 0)
    {
        return 1;
    }

    if (value < 0)
    {
        return 0;
    }

    if (containers.size() == 0)
    {
        return 0;
    }

    string key = std::to_string(value) + "-";

    for (auto x : containers)
    {
        key += std::to_string(x) + "-";
    }

    if (cache.find(key) != cache.end())
    {
        return cache[key];
    }


    int toReturn = 0;

    std::vector<int> newContainers = containers;
    newContainers.erase(newContainers.begin());

    toReturn += day17_getCombinations_A(value - containers[0], newContainers, cache);//use it
    toReturn += day17_getCombinations_A(value, newContainers, cache);//do not use

    cache.insert({ key, toReturn });

    return toReturn;
}

std::vector<std::vector<int>> day17_getCombinations_B(int value, std::vector<int> containers, map<string, std::vector<std::vector<int>>>& cache)
{
    std::vector<std::vector<int>> earlyReturn;
    if (value == 0)
    {
        earlyReturn.push_back({});
        return earlyReturn;
    }

    if (value < 0)
    {
        return earlyReturn;
    }

    if (containers.size() == 0)
    {
        return earlyReturn;
    }

    string key = std::to_string(value) + "-";

    for (auto x : containers)
    {
        key += std::to_string(x) + "-";
    }

    if (cache.find(key) != cache.end())
    {
        return cache[key];
    }

    std::vector<std::vector<int>> toReturn;
    std::vector<int> newContainers = containers;
    newContainers.erase(newContainers.begin());

    auto notUsed = day17_getCombinations_B(value, newContainers, cache);
    auto used = day17_getCombinations_B(value - containers[0], newContainers, cache);

    toReturn.insert(toReturn.end(), notUsed.begin(), notUsed.end());


    for (auto x : used)
    {
        x.insert(x.begin(), containers[0]);
        toReturn.push_back(x);
    }

    cache.insert({ key, toReturn });

    return toReturn;
}


void day17()
{
    auto lines = ReadFile("./input/day17.txt");

    std::vector<int> containers;

    for (auto l : lines)
    {
        containers.push_back(atoi(l.c_str()));
    }

    map<string, int> cache_A;
    int partA = day17_getCombinations_A(150, containers, cache_A);
    std::cout << "day17_a => " << partA << "\n";

    map<string, std::vector<std::vector<int>>> cacheBB;
    std::vector<std::vector<int>> partB_result = day17_getCombinations_B(150, containers, cacheBB);

    int minValue = lines.size();

    for (auto res : partB_result)
    {
        if (res.size() < minValue)
        {
            minValue = res.size();
        }
    }

    int countB = 0;
    for (auto res : partB_result)
    {
        if (res.size() == minValue)
        {
            ++countB;
        }
    }
   

    std::cout << "day17_b => " << countB << "\n";
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
   //day12();
   //day13();
   //day14();
   //day15();
   //day16();
   day17();
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
