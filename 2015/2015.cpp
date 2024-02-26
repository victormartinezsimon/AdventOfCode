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

int main()
{
   day1();
   day2();
   day3();
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
