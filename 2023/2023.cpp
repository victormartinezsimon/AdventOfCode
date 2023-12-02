// 2023.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <regex>

using namespace std;



template <class T>
class MyTree
{
public:
    T _value;
    MyTree<T>* _left = nullptr;
    MyTree<T>* _right = nullptr;

    MyTree<T>(T value) { _value = value; }
    void AddLeft(MyTree<T>* l) { _left = l; }
    void AddRight(MyTree<T>* r) { _right = r; }
};

template <class T>
class NodeGraph
{
public:
    int _id;
    T _value;
    std::vector<NodeGraph*> _neightbours;
    std::vector<float> _cost;

    NodeGraph<T>(T value, int id) { _value = value; _id = id; }

    void AddNeightbour(NodeGraph<T>* n, float cost)
    {
        _neightbours.push_back(n);
        _cost.push_back(n);
    }

    float GetCost(NodeGraph<T>* n)
    {
        for (int i = 0; i < _neightbours.size(); ++i)
        {
            if (n->_id == _neightbours[i]->_id)
            {
                return _cost[i];
            }
        }
        return -1;
    }
};

template <class T>
class MyGraph
{
public:
    vector< NodeGraph<T>> _allNodes;

    NodeGraph<T>* AddNode(T value)
    { 
        NodeGraph<T>* node = new NodeGraph<T>(value, _allNodes.size());
        _allNodes.push_back(node);
        return node;
    }

    void AddDirectionalRoute(NodeGraph<T>* n1, NodeGraph<T>* n2, float cost)
    {
        n1->AddNeightbour(n2, cost);
    }

    void AddRoute(NodeGraph<T>* n1, NodeGraph<T>* n2, float cost)
    {
        n1->AddNeightbour(n2, cost);
        n2->AddNeightbour(n1, cost);
    }
};


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


int GetFirstNumber_day1(const string& line, int start, int end, int increment, int& position)
{
    int index = start;

    while (index != end)
    {
        if (line[index] >= '0' && line[index] <= '9')
        {
            position = index;
            return line[index] - '0';
        }

        index = index + increment;
    }

    return -1;
}

void GetStringPositions(string& line, int& leftValue, int& leftPosition, int& rightValue, int& rightPosition)
{
    std::vector<string> numbers = {"zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};

    leftValue = -1;
    leftPosition = line.size();
    rightValue = -1;
    rightPosition = -1;


    for (int i = 0; i < numbers.size(); ++i)
    {
        auto foundLeftPosition = line.find(numbers[i].c_str());

        if (foundLeftPosition != std::string::npos)
        {
            if (foundLeftPosition < leftPosition)
            {
                leftPosition = foundLeftPosition;
                leftValue = i;
            }
        }

        std::size_t foundRightPosition = line.rfind(numbers[i].c_str());

        if (foundRightPosition != std::string::npos)
        {
            if ((int)foundRightPosition > rightPosition)
            {
                rightPosition = foundRightPosition;
                rightValue = i;
            }
        }
    }
}


void day1()
{
    std::vector<string> fileTxt = ReadFile("./input/day1.txt");

    //part 1
    {
        long long acum = 0;

        for (auto l : fileTxt)
        {
            int dummy;
            int firstValue = GetFirstNumber_day1(l, 0, l.size(), +1, dummy);
            int secondValue = GetFirstNumber_day1(l,l.size()-1, -1, -1, dummy);

            acum += firstValue * 10 + secondValue;
        }

        std::cout << "Day 1 => " << acum << "\n";
    }
    //part 2
    {
        long long acum = 0;

        for (auto l : fileTxt)
        {
            int leftValue;
            int leftPosition;
            int rightValue;
            int rightPosition;
            GetStringPositions(l, leftValue, leftPosition, rightValue, rightPosition);

            int positionFirst;
            int firstValue = GetFirstNumber_day1(l, 0, l.size(), +1, positionFirst);
            int positionSecond;
            int secondValue = GetFirstNumber_day1(l, l.size() - 1, -1, -1,positionSecond);

            if (positionFirst > leftPosition)
            {
                firstValue = leftValue;
            }

            if (positionSecond < rightPosition)
            {
                secondValue = rightValue;
            }

            acum += firstValue * 10 + secondValue;
        }

        std::cout << "Day 1_2 => " << acum << "\n";
    }
}


void day2()
{
    std::vector<string> fileTxt = ReadFile("./input/day2.txt");

    std::map<string, int> maxPerColor = { {"red", 12},{"green", 13},{"blue", 14}};

    int count_a = 0;
    long long count_b = 0;

    for (int i = 0; i < fileTxt.size(); ++i)
    {
        auto match = split(fileTxt[i], ":")[1];
      
        auto plays = split(match, ";");

        std::map<string, int> currentMax = { {"red", 0},{"green", 0},{"blue", 0} };

        for (auto play : plays)
        {
            auto cubes = split(play, ",");

            for (auto cube : cubes)
            {
                for (auto max : maxPerColor)
                {
                    auto color = split(cube, max.first);
                    if (color.size() >= 2)
                    {
                        int value = atoi(color[0].c_str());
                        
                        if (currentMax[max.first] < value)
                        {
                            currentMax[max.first] = value;
                        }

                        break;
                    }
                }
            }
        }
       
        {
            bool valid_a = true;
            for (auto max : maxPerColor)
            {
                if (max.second < currentMax[max.first])
                {
                    valid_a = false;
                    break;
                }
            }

            if (valid_a)
            {
                count_a += (i + 1);
            }
        }
        {
            long long pow = 1;
            for (auto max : currentMax)
            {
                pow = pow * max.second;
            }
            count_b += pow;
        }
    }

    std::cout << "Day 2 => " << count_a << "\n";
    std::cout << "Day 2_2 => " << count_b << "\n";
}
void day3()
{

}
void day4()
{

}
void day5()
{

}
void day6()
{

}
void day7()
{

}
void day8()
{

}
void day9()
{

}
void day10()
{

}
void day11()
{

}
void day12()
{

}
void day13()
{

}
void day14()
{

}
void day15()
{

}
void day16()
{

}
void day17()
{

}
void day18()
{

}
void day19()
{

}
void day20()
{

}
void day21()
{

}
void day22()
{

}
void day23()
{

}
void day24()
{

}
void day25()
{

}

int main()
{
    day1();
    day2();
}

// Ejecutar programa: Ctrl + F5 o menú Depurar > Iniciar sin depurar
// Depurar programa: F5 o menú Depurar > Iniciar depuración

// Sugerencias para primeros pasos: 1. Use la ventana del Explorador de soluciones para agregar y administrar archivos
//   2. Use la ventana de Team Explorer para conectar con el control de código fuente
//   3. Use la ventana de salida para ver la salida de compilación y otros mensajes
//   4. Use la ventana Lista de errores para ver los errores
//   5. Vaya a Proyecto > Agregar nuevo elemento para crear nuevos archivos de código, o a Proyecto > Agregar elemento existente para agregar archivos de código existentes al proyecto
//   6. En el futuro, para volver a abrir este proyecto, vaya a Archivo > Abrir > Proyecto y seleccione el archivo .sln
