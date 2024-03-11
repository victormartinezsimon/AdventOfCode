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

    //std::cout << "day7_a => " << wires["a"] << "\n";
}

int main()
{
   //day1();
   //day2();
   //day3();
   //day4();
   //day5();
   //day6();
   day7();
   //day8();
   //day9();
   //day10();
   //day11();
   //day12();
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
