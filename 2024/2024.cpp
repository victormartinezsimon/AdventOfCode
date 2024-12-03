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

int main()
{
   day1();
   day2();
   day3();
   /*
   day3();
   day4();
   day5();
   day6();
   day7();
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
