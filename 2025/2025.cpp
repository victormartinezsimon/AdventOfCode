// 2025.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include "utils.h"
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
#include <array>
#include <queue>
#include <iomanip>
#include <stack>
#include <bitset>
#include <functional>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <cmath>
using namespace std;

int day1_b(int value, std::map<int, int>& cache)
{
    if (value <= 0) { return 0; }
    
    if (cache.find(value) != cache.end())
    {
        return cache[value];
    }
    
    int newValue = (value / 3) - 2;

    int toReturn = day1_b(newValue, cache);

    if (newValue > 0)
    {
        toReturn += newValue;
    }

    cache[value] = toReturn;
    return toReturn;
}

void day1()
{
    auto fileTxt = ReadFile("./input/day1.txt");

    long long acumA = 0;
    long long acumB = 0;
    std::map<int, int> cacheB;

    for (auto n : fileTxt)
    {
        int val = atoi(n.c_str());
        long long calcA = (val / 3) - 2;
        acumA += calcA;

       int calcB = day1_b(val, cacheB);
       acumB += calcB;

    }
    std::cout << "day 1 => " << acumA << "\n";
    std::cout << "day 1_B => " << acumB << "\n";
}

int main()
{
    day1();
    /*
    day2();
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
    day23(false);
    day24();
    day25(false);
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
