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

vector<vector<char>> ParseFile_day3(const std::vector<string>& file)
{
    vector<vector<char>> result;

    for (string s : file)
    {
        vector<char> v;
        for (char c : s)
        {
            v.push_back(c);
        }
        result.push_back(v);
    }
    return result;
}

vector<pair<int, int>> ExtractNumbers_day3(const vector<char>& board)
{
    vector<pair<int, int>> result;

    int start = 0;
    bool inNumber = false;


    for (int i = 0; i <= board.size(); ++i)
    {
        if (i< board.size() && board[i] >= '0' && board[i] <= '9')
        {
            if (!inNumber)
            {
                inNumber = true;
                start = i;
            }
        }
        else
        {
            if (inNumber)
            {
                inNumber = false;
                result.push_back({ start, i - 1 });
            }
        }
    }
    return result;
}

bool anySymbol_day3(char c)
{
    return c != '.' && (c < '0' || c > '9');
}

bool anyNumber_day3(char c)
{
    return  (c >= '0' && c <= '9');
}

bool validPosition_day3(const vector<vector<char>>& board, int row, int col )
{
    //a b c
    //d X e
    //f g h

    if (row > 0 && col > 0)
    {
        char a = board[row - 1][col - 1];
        if (anySymbol_day3(a)) { return true; }
    }

    if (row > 0)
    {
        char b = board[row - 1][col];
        if (anySymbol_day3(b)) { return true; }
    }

    if (row > 0 && col < board[row].size() - 1)
    {
        char c = board[row - 1][col + 1];
        if (anySymbol_day3(c)) { return true; }
    }

    if (col > 0)
    {
        char d = board[row][col - 1];
        if (anySymbol_day3(d)) { return true; }
    }

    if (col < board[row].size() - 1)
    {
        char e = board[row][col + 1];
        if (anySymbol_day3(e)) { return true; }
    }

    if (row < board.size() - 1 && col > 0)
    {
        char f = board[row + 1][col - 1];
        if (anySymbol_day3(f)) { return true; }
    }

    if (row < board.size() - 1)
    {
        char g = board[row + 1][col];
        if (anySymbol_day3(g)) { return true; }
    }

    if (row < board.size()-1 && col < board[row].size() - 1)
    {
        char h = board[row + 1][col + 1];
        if (anySymbol_day3(h)) { return true; }
    }
    
    return false;
}

bool validNumber_day3(const vector<vector<char>>& board, int row, const pair<int, int> position)
{

    for (int i = position.first; i <= position.second; ++i)
    {
        if (validPosition_day3(board, row, i) >= 1)
        {
            return true;
        }
    }

    return false;
}

int buildNumber_day3(const vector<vector<char>>& board, int row, const pair<int, int> position)
{
    int solution = 0;

    std::string number = "";

    for (int col = position.first; col <= position.second; ++col)
    {
        number += board[row][col];
    }
    return atoi(number.c_str());
}

int getGearNumberRow_day3(const vector<vector<char>>& board, const std::vector < std::vector<pair<int, int>>>& numbers, int rowInvestigate, int colGear, int& numbersUsed)
{
    int sol = 1;
    for (auto number : numbers[rowInvestigate])
    {
       //inside
        if (colGear >= number.first && colGear <= number.second)
        {
            //premio
            sol *= buildNumber_day3(board, rowInvestigate, number);
            numbersUsed += 1;
        }
        
        //left
        if ( number.second == colGear - 1)
        {
            sol *= buildNumber_day3(board, rowInvestigate, number);
            numbersUsed += 1;
        }

        //right
        if (number.first == colGear + 1)
        {
            sol *= buildNumber_day3(board, rowInvestigate, number);
            numbersUsed += 1;
        }
    }
    
    return sol;
}

int getGearNumbers_day3(const vector<vector<char>>& board, const std::vector < std::vector<pair<int, int>>>& numbers, int row, int col)
{
   // int validNumbers = validGearPosition_day3(board, row, col);
    //if (validNumbers < 2) { return 0; }

    int result = 1;

    int numbersUsed = 0;
    if (row > 0)
    {
        result *= getGearNumberRow_day3(board, numbers, row - 1,  col, numbersUsed);
    }

    {
        result *= getGearNumberRow_day3(board, numbers, row,  col, numbersUsed);
    }

    if (row < board.size())
    {
        result *= getGearNumberRow_day3(board, numbers, row + 1,  col, numbersUsed);
    }
    if (numbersUsed < 2) { return 0; }
    return result;
}

void day3_a()
{
    std::vector<string> fileTxt = ReadFile("./input/day3.txt");

    auto board = ParseFile_day3(fileTxt);

    long long solution_a = 0;

    for (int row = 0; row < board.size(); ++row)
    {
        auto numbers = ExtractNumbers_day3(board[row]);

        for (auto number : numbers)
        {
            int n = buildNumber_day3(board, row, number);
            if (validNumber_day3(board, row, number))
            {
                solution_a += n;
            }
        }
    }

    std::cout << "Day 3 => " << solution_a << "\n";
}

void day3_b()
{
    std::vector<string> fileTxt = ReadFile("./input/day3.txt");

    auto board = ParseFile_day3(fileTxt);

    std::vector < std::vector<pair<int, int>>> numbersPerRow;
    for (int row = 0; row < board.size(); ++row)
    {
        auto numbers = ExtractNumbers_day3(board[row]);

        numbersPerRow.push_back(numbers);
    }

    long long solution_b = 0;

    for (int row = 0; row < board.size(); ++row)
    {
        for (int col = 0; col < board[row].size(); ++col)
        {
            if (board[row][col] == '*')
            {
                int number = getGearNumbers_day3(board, numbersPerRow, row, col);
                solution_b += number;
            }
        }
    }
       
    std::cout << "Day 3_b => " << solution_b << "\n";
}

void day3()
{
    day3_a();
    day3_b();
}

int getTotalWinningNumbers_day4(const string& s)
{
    std::vector<string> initialSeparation = split(s, "|");
    std::vector<string> prizeNumbers = split(split(initialSeparation[0], ":")[1], " ");
    std::vector<string> myNumbers = split(initialSeparation[1], " ");

    std::set<int> prizeSet;
    for (auto number : prizeNumbers)
    {
        if (number.size() > 0)
        {
            prizeSet.insert(atoi(number.c_str()));
        }
    }

    int count = 0;
    for (auto number : myNumbers)
    {
        if (number.size() > 0)
        {
            if (prizeSet.find(atoi(number.c_str())) != prizeSet.end())
            {
                ++count;
            }
        }
    }
    return count;
}

void day4_a()
{
    std::vector<string> fileTxt = ReadFile("./input/day4.txt");

    long long result = 0;
    for (int i = 0; i < fileTxt.size(); ++i)
    {
        int count = getTotalWinningNumbers_day4(fileTxt[i]);
        
        if (count > 0)
        {
            result += pow(2, count - 1);
        }
    }

    std::cout << "Day 4 => " << result << "\n";
}

void day4_b()
{
    std::vector<string> fileTxt = ReadFile("./input/day4.txt");

    std::vector<int> winsPerCard;
    std::vector<int> extraWins;
    std::vector<int> totalCardboards;

    for (int i = 0; i < fileTxt.size(); ++i)
    {
        winsPerCard.push_back( getTotalWinningNumbers_day4(fileTxt[i]));
        extraWins.push_back(0);
        totalCardboards.push_back(1);
    }

    for (int cardboardIdx = 0; cardboardIdx < winsPerCard.size(); ++cardboardIdx)
    {
        totalCardboards[cardboardIdx] += extraWins[cardboardIdx];

        for (int i = cardboardIdx + 1; i < cardboardIdx + 1 + winsPerCard[cardboardIdx]; ++i)
        {
            extraWins[i] += totalCardboards[cardboardIdx];
        }
    }

    long long solution = std::accumulate(totalCardboards.begin(), totalCardboards.end(), 0);
    std::cout << "Day 4_b => " << solution << "\n";
}

void day4()
{
    day4_a();
    day4_b();
}

struct day5_struct
{
public:
    unsigned long long destinationStart;
    unsigned long long sourceStart;
    unsigned long long range;

    day5_struct(unsigned long long _destinationStart, unsigned long long _sourceStart, unsigned long long _range):destinationStart(_destinationStart), sourceStart(_sourceStart),range(_range) {}

    bool inRange(unsigned long long value) const
    {
        return sourceStart <= value && value <= sourceStart + range;
    }

    unsigned long long lastSourceValue()const 
    {
        return sourceStart + range;
    }

    unsigned long long lastDestinationValue() const
    {
        return destinationStart + range;
    }

    unsigned long long getDestination(unsigned long long value) const
    {
        if (!inRange(value))
        {
            return value;
        }

        unsigned long long diff = value - sourceStart;

        return destinationStart + diff;
    }
};

bool lineWithInfo_day5(const string& str)
{
    return '0' <= str[0] && str[0] <= '9';
}

std::vector<std::vector<day5_struct>> parseDay5(const std::vector<string>& input)
{
    int line = 1;//skip the seeds

    std::vector<std::vector<day5_struct>> toReturn;

    while (line < input.size())
    {
        if (lineWithInfo_day5(input[line]))
        {
            auto numbers = split(input[line], " ");
            day5_struct s5(atoll(numbers[0].c_str()), atoll(numbers[1].c_str()), atoll(numbers[2].c_str()));
            toReturn.back().push_back(s5);
        }
        else
        {
            if (input[line].size() == 0) {}//do nothing
            else
            {
                std::vector<day5_struct> newList;
                toReturn.push_back(newList);
            }
        }
        ++line;
    }

    return toReturn;

}


unsigned long long day5_finalDestination(unsigned long long seed, const std::vector<std::vector<day5_struct>>& mutation)
{
    unsigned long long value = seed;
    for (int stepidx = 0; stepidx < mutation.size(); ++stepidx)
    {
        auto stepInfo = mutation[stepidx];
        for (int rangeIdx = 0; rangeIdx < stepInfo.size(); ++rangeIdx)
        {
            if (stepInfo[rangeIdx].inRange(value))
            {
                value = stepInfo[rangeIdx].getDestination(value);
                break;
            }
        }
    }
    return value;
}


void day5_a()
{
    std::vector<string> fileTxt = ReadFile("./input/day5.txt");

    auto parsedData = parseDay5(fileTxt);

    auto seeds = split(split(fileTxt[0], ":")[1], " ");

    unsigned long long result = LLONG_MAX;

    for (auto seed : seeds)
    {
        if (seed.size() == 0) { continue; }

        unsigned long long value = day5_finalDestination(atoll(seed.c_str()), parsedData);

        if (value < result)
        {
            result = value;
        }
    }

    std::cout << "Day 5 => " << result << "\n";

}

bool day5_analyzePairSeed(const day5_struct& mutation, std::pair<unsigned long long, unsigned long long> seed, pair<unsigned long long, unsigned long long>& mutatedSeed, std::vector<pair<unsigned long long, unsigned long long>>& leftSeed)
{
    //before mutation
    if (seed.second < mutation.sourceStart)
    {
        return false;
    }

    //after mutation
    if (seed.first > mutation.lastSourceValue())
    {
        return false;
    }

    //here some collision
    //left part
    if (seed.first < mutation.sourceStart)
    {
        leftSeed.push_back({ seed.first,  mutation.sourceStart - 1 });
    }

    //right part
    if (seed.second > mutation.lastSourceValue())
    {
        leftSeed.push_back({ mutation.lastSourceValue(),  seed.second });
    }

    //mutated part
    unsigned long long start = max(seed.first, mutation.sourceStart);
    unsigned long long end = min(seed.second, mutation.lastSourceValue());

    auto valueStart = mutation.getDestination(start);
    auto valueEnd = mutation.getDestination(end);

    mutatedSeed = std::make_pair( valueStart, valueEnd);
    return true;
}

std::vector<pair<unsigned long long, unsigned long long>> day5_mutateSeeds(const std::vector<day5_struct>& mutation, const std::pair<unsigned long long, unsigned long long>& seed)
{
    std::vector<pair<unsigned long long, unsigned long long>> seedsToAnalyze = { seed };
    std::vector<pair<unsigned long long, unsigned long long>> result;

    for (auto mut : mutation)
    {
        std::vector<pair<unsigned long long, unsigned long long>> remainingSeeds;
        for (auto seed : seedsToAnalyze)
        {
            std::vector<pair<unsigned long long, unsigned long long>> leftSeed;
            pair<unsigned long long, unsigned long long> mutatedSeed;
            if (day5_analyzePairSeed(mut, seed, mutatedSeed, leftSeed))
            {
                //some part mutated, maybe the rest will be mutated next
                remainingSeeds.insert(remainingSeeds.end(), leftSeed.begin(), leftSeed.end());
                result.push_back(mutatedSeed);
            }
            else
            {
                remainingSeeds.push_back(seed);
            }
        }
        seedsToAnalyze.clear();
        seedsToAnalyze.insert(seedsToAnalyze.end(), remainingSeeds.begin(), remainingSeeds.end());
    }

    result.insert(result.end(), seedsToAnalyze.begin(), seedsToAnalyze.end());

    return result;
}

std::vector<std::pair<unsigned long long, unsigned long long>> day5_evaluateDepth(const std::vector<day5_struct>& mutation, const std::vector<std::pair<unsigned long long, unsigned long long>>& seeds)
{

    std::vector<std::pair<unsigned long long, unsigned long long>> toReturn;

    for (auto seed : seeds)
    {
        auto newSeeds = day5_mutateSeeds(mutation, seed);
        toReturn.insert(toReturn.end(), newSeeds.begin(), newSeeds.end());
    }

    return toReturn;
}

void day5_b()
{
    std::vector<string> fileTxt = ReadFile("./input/day5.txt");
    auto mutations = parseDay5(fileTxt);
    auto seeds = split(split(fileTxt[0], ":")[1], " ");
    std::vector<std::pair<unsigned long long, unsigned long long>> seedsPairs;

    for (int i = 1; i < seeds.size(); i = i + 2)
    {
        long long start = atoll(seeds[i].c_str());
        long long end = start + atoll(seeds[i + 1].c_str()) - 1;
        seedsPairs.push_back({ start, end });
    }

    std::vector<std::pair<unsigned long long, unsigned long long>> pairsAlive = seedsPairs;

    for (int mutationIdx = 0; mutationIdx < mutations.size(); ++mutationIdx)
    {
        pairsAlive = day5_evaluateDepth(mutations[mutationIdx], pairsAlive);

        std::sort(pairsAlive.begin(), pairsAlive.end(), [](auto p1, auto p2) {return p1.first < p2.first; });
    }

    std::sort(pairsAlive.begin(), pairsAlive.end(), [](auto p1, auto p2) {return p1.first < p2.first; });

    std::cout << "day 5_b => " << pairsAlive[0].first << "\n";
}

void day5()
{
    day5_a();
    day5_b();
}

pair<double, double> day6_equation(long long d, long long s)
{
    double a = s * s;
    double b = 4 * d;
    double _sqrt = sqrt(a - b);

    double solution1 = (- s + _sqrt) / -2;
    double solution2 = (-s - _sqrt) / -2;

    if (solution1 > solution2)
    {
        return { floor(solution2 + 1), ceil(solution1 - 1) };
    }
    else
    {
        return { floor(solution1 +1), ceil(solution2 - 1)};
    }
}

void day6_a()
{
    auto fileTxt = ReadFile("./input/day6.txt");

    std::vector<int> distances;
    std::vector<int> times;

    {
        string distancesTxt = fileTxt[1];
        distancesTxt.erase(0, 10);
        auto distanceSplit = split(distancesTxt, " ");
        for (int i = 0; i < distanceSplit.size(); ++i)
        {
            if (distanceSplit[i].size() > 0)
            {
                distances.push_back(atoi(distanceSplit[i].c_str()));
            }
        }
    }
    {
        string timesTxt = fileTxt[0];
        timesTxt.erase(0, 10);
        auto timesSplit = split(timesTxt, " ");
        for (int i = 0; i < timesSplit.size(); ++i)
        {
            if (timesSplit[i].size() > 0)
            {
                times.push_back(atoi(timesSplit[i].c_str()));
            }
        }
    }

    auto solution = 1;

    for (int i = 0; i < distances.size(); ++i)
    {
        auto sols = day6_equation(distances[i], times[i]);
        long long diff = abs(sols.second - sols.first) + 1;
        solution *= diff;
    }
     
    std::cout << "day6 => " << solution << "\n";
}

void day6_b()
{
    auto fileTxt = ReadFile("./input/day6.txt");
    string distances;
    string times;

    {
        string distancesTxt = fileTxt[1];
        distancesTxt.erase(0, 10);
        auto distanceSplit = split(distancesTxt, " ");
        for (int i = 0; i < distanceSplit.size(); ++i)
        {
            if (distanceSplit[i].size() > 0)
            {
                distances += distanceSplit[i];
            }
        }
    }
    {
        string timesTxt = fileTxt[0];
        timesTxt.erase(0, 10);
        auto timesSplit = split(timesTxt, " ");
        for (int i = 0; i < timesSplit.size(); ++i)
        {
            if (timesSplit[i].size() > 0)
            {
                times += timesSplit[i];
            }
        }
    }

    {
        auto sols = day6_equation(atoll(distances.c_str()), atoll(times.c_str()));
        long long diff = abs(sols.second - sols.first) + 1;
        std::cout << "day6_b => " << diff << ", Using calc: 30077773" << "\n";
    }

}

void day6()
{
    day6_a();
    day6_b();
}

struct day7_play
{
public:
    int _value;
    string _play;
    std::map<char, int> _countSymbols;
    bool _hasJokers;

    std::map<char, int> _cardOrderNormal = { {'A', 1},{'K', 2} ,{'Q', 3} ,{'J', 4} ,{'T', 5} ,{'9', 6} ,{'8', 7} ,{'7', 8} ,{'6', 9},{'5', 10} ,{'4', 11} ,{'3', 12} ,{'2', 13} };
    std::map<char, int> _cardOrderJoker = { {'A', 1},{'K', 2} ,{'Q', 3},{'T', 5} ,{'9', 6} ,{'8', 7} ,{'7', 8} ,{'6', 9},{'5', 10} ,{'4', 11} ,{'3', 12} ,{'2', 13}, {'J', 14} };

    day7_play(string play, int value, bool hasJokers) :_value(value), _play(play), _hasJokers(hasJokers)
    {
        GetCountSymbols();
    }

    void GetCountSymbols()
    {
        _countSymbols.insert({ 'J', 0});
        for (char c : _play)
        {
            if (_countSymbols.find(c) == _countSymbols.end())
            {
                _countSymbols.insert({ c, 0 });
            }
            ++_countSymbols[c];
        }
    }

public:
    //5, 4, 3, 2 equals
    bool HasNumber( int number, bool useJokers) const
    {
        int countJokers = _countSymbols.at('J');
        for (auto count : _countSymbols)
        {
            int myCount = count.second;

            if (useJokers && count.first != 'J')
            {
                myCount += countJokers;
            }

            if (myCount == number) { return true; }
        }
        return false;
    }

    bool HasFullHouse() const
    {
        if (!_hasJokers)
        {
            return HasNumber(3, _hasJokers) && HasNumber(2, _hasJokers);
        }
        else
        {
            int countJokers = _countSymbols.at('J');

            bool hasThree = HasNumber(3, false);
            bool hasTwo = HasNumber(2, false);
            bool hasDoublePair = HasDoublePair();

            if (countJokers >= 4) { return true; }
            if (countJokers == 0) { return hasThree && hasTwo; }
            if (countJokers == 3) { return hasTwo || hasDoublePair; }
            if (countJokers == 2) { return hasThree || hasDoublePair; }//if double pair and 2 jokers then, the 2 jokers makes the trio
            if (countJokers == 1) { return hasThree || hasDoublePair; }
            return false;
        }

    }

    bool HasDoublePair() const
    {
        int totalPairs = 0;

        for (auto count : _countSymbols)
        {
            if (count.second == 2) {++totalPairs; }
        }

        return totalPairs == 2;
    }

    bool IsBetterCard(char c1, char c2) const
    {
        if (_hasJokers)
        {
            return _cardOrderJoker.at(c1) < _cardOrderJoker.at(c2);
        }
        else
        {
            return _cardOrderNormal.at(c1) < _cardOrderNormal.at(c2);
        }
    }

    bool IsBestCardPlay(const day7_play& p2) const
    {
        for (int i = 0; i < _play.size(); ++i)
        {
            if (_play[i] == p2._play[i]) { continue; }
            return IsBetterCard(_play[i], p2._play[i]);
        }
        return true;
    }

    bool IsBetter(const day7_play& p2) const
    {
        if (HasNumber(5, _hasJokers) && p2.HasNumber(5, _hasJokers)) { return IsBestCardPlay(p2); }
        if (HasNumber(5, _hasJokers) && !p2.HasNumber(5, _hasJokers)) { return true; }
        if (!HasNumber(5, _hasJokers) && p2.HasNumber(5, _hasJokers)) { return false; }

        if (HasNumber(4, _hasJokers) && p2.HasNumber(4, _hasJokers)) { return IsBestCardPlay(p2); }
        if (HasNumber(4, _hasJokers) && !p2.HasNumber(4, _hasJokers)) { return true; }
        if (!HasNumber(4, _hasJokers) && p2.HasNumber(4, _hasJokers)) { return false; }

        if (HasFullHouse() && p2.HasFullHouse()) { return IsBestCardPlay(p2); }
        if (HasFullHouse() && !p2.HasFullHouse()) { return true; }
        if (!HasFullHouse() && p2.HasFullHouse()) { return false; }

        if (HasNumber(3, _hasJokers) && p2.HasNumber(3, _hasJokers)) { return IsBestCardPlay(p2); }
        if (HasNumber(3, _hasJokers) && !p2.HasNumber(3, _hasJokers)) { return true; }
        if (!HasNumber(3, _hasJokers) && p2.HasNumber(3, _hasJokers)) { return false; }

        if (HasDoublePair() && p2.HasDoublePair()) { return IsBestCardPlay(p2); }
        if (HasDoublePair() && !p2.HasDoublePair()) { return true; }
        if (!HasDoublePair() && p2.HasDoublePair()) { return false; }

        if (HasNumber(2, _hasJokers) && p2.HasNumber(2, _hasJokers)) { return IsBestCardPlay(p2); }
        if (HasNumber(2, _hasJokers) && !p2.HasNumber(2, _hasJokers)) { return true; }
        if (!HasNumber(2, _hasJokers) && p2.HasNumber(2, _hasJokers)) { return false; }

        return IsBestCardPlay(p2);
    }

};

struct day7_comparator
{
    bool operator()(const day7_play& p1, const day7_play& p2) const
    {
        return !p1.IsBetter(p2);
    }
};

void day7_Task(bool hasJokers)
{
    auto fileTxt = ReadFile("./input/day7.txt");

   set<day7_play, day7_comparator> plays;

    for (auto f : fileTxt)
    {
        auto info = split(f, " ");
        day7_play play(info[0], atoi(info[1].c_str()), hasJokers);
        plays.insert(play);
    }

    long long acum = 0;

    int count = 1;
    for (auto play: plays)
    {
        acum += (count) * play._value;
        ++count;
    }
    std::cout << "day7" << (hasJokers ? "_b => " : " => ") << acum << "\n";
}

void day7()
{
    day7_Task(false);
    day7_Task(true);
}

struct day8_node
{
public:
    string name;
    day8_node* left = nullptr;
    day8_node* right = nullptr;
};


day8_node* day8_getNode(map<string, day8_node*>& nodes, string name)
{
    if (nodes.find(name) == nodes.end())
    {
        day8_node* node = new day8_node();
        node->name = name;
        nodes.insert({ name, node });
    }
    return nodes[name];
}

void day8_buildStruct(const vector<string>& input, map<string, day8_node*>& nodes)
{

    for (int lineIndex = 2; lineIndex < input.size(); ++lineIndex)
    {
        auto nodeInfo = split(input[lineIndex], " ");
        string left = nodeInfo[2].substr(1, 3);
        string right = nodeInfo[3].substr(0, 3);

        auto node = day8_getNode(nodes, nodeInfo[0]);
        auto nodeLeft = day8_getNode(nodes, left);
        auto nodeRight = day8_getNode(nodes, right);

        node->left = nodeLeft;
        node->right = nodeRight;
    }
}

long long day8_countToLoop(day8_node* start, day8_node* end, const string& input)
{
    long long count = 0;
    int indexInput = 0;
    day8_node* current = start;
    while (current != nullptr && current != end)
    {
        char movement = input[indexInput];
        indexInput = (indexInput + 1) % input.size();

        if (movement == 'L')
        {
            current = current->left;
        }
        else
        {
            current = current->right;
        }
        ++count;
    }
    return count;
}

long long day8_countToLoopAnyEnd(day8_node* start, day8_node*& endNode, const string& input)
{
    long long count = 0;
    int indexInput = 0;
    day8_node* current = start;
    while (current != nullptr && current->name.back() != 'Z')
    {
        char movement = input[indexInput];
        indexInput = (indexInput + 1) % input.size();

        if (movement == 'L')
        {
            current = current->left;
        }
        else
        {
            current = current->right;
        }
        ++count;
    }
    endNode = current;
    return count;
}

void day8_a()
{
    auto fileTxt = ReadFile("./input/day8.txt");
    map<string, day8_node*> nodes;
    day8_buildStruct(fileTxt, nodes);

    day8_node* start = day8_getNode(nodes, "AAA");
    day8_node* end = day8_getNode(nodes, "ZZZ");

    std::cout << "day8 =>" << day8_countToLoop(start, end, fileTxt[0]) << "\n";
}

void day8_b()
{
    auto fileTxt = ReadFile("./input/day8.txt");
    map<string, day8_node*> nodes;
    day8_buildStruct(fileTxt, nodes);

    std::vector<day8_node*> allStart;
    for (auto n : nodes)
    {
        if (n.first.back() == 'A')
        {
            allStart.push_back(n.second);
        }
    }

    std::cout << "day8 b info =>" << fileTxt[0].size() << "\n";

    vector<long long> gdcs;

    for (auto n : allStart)
    {
        day8_node* endNode = nullptr;
        long long times = day8_countToLoopAnyEnd(n, endNode, fileTxt[0]);
        if (endNode != nullptr)
        {
            std::cout << "[" << n->name << "," << endNode->name << "]: " << times << "\n";
            gdcs.push_back(times);
        }
    }

    long long result = gdcs[0];

    for (int i = 1; i < gdcs.size(); ++i)
    {
        result = std::lcm(result, gdcs[i]);
    }

    std::cout << "day8 b result =>" << result << "\n";
}

void day8()
{
    day8_a();
    day8_b();
}

pair<int, int> day9_calculateSum(std::vector<int> numbers)
{
    if (numbers.size() == 1) 
    { 
        return { 0,0 };
    }

    std::vector<int> newValues;

    for (int nIdx = 1; nIdx < numbers.size(); ++nIdx)
    {
        int value = numbers[nIdx] - numbers[nIdx - 1];
        newValues.push_back(value);
    }

    auto depthValue = day9_calculateSum(newValues);

    return {numbers.front() - depthValue.first, numbers.back() + depthValue.second };
}

void day9()
{
    auto fileTxt = ReadFile("./input/day9.txt");

    std::vector<std::vector<int>> inputs;

    for (auto x : fileTxt)
    {
        auto tmp = split(x, " ");

        std::vector<int> input;
        for (auto n : tmp)
        {
            input.push_back(atoi(n.c_str()));
        }
        inputs.push_back(input);
    }
    long long result_a = 0;
    long long result_b = 0;

    for (auto input : inputs)
    {
        result_a += day9_calculateSum(input).second;
        result_b += day9_calculateSum(input).first;
    }

    std::cout << "day9 =>" << result_a << "\n";
    std::cout << "day9_b =>" << result_b << "\n";
}

struct day10_node
{
public:
    int _row;
    int _col;
    int _currentDepth;

    day10_node(int row, int col, int currentDepth) :_row(row), _col(col), _currentDepth(currentDepth) {}
};

std::vector<day10_node> day10_getNeightboursChar(const day10_node& node, const std::vector<string>& fileTxt, std::vector<pair<int, int>> directions)
{
    std::vector<day10_node> toReturn;

    int width = fileTxt[0].size();
    int height = fileTxt.size();

    for (auto dir : directions)
    {
        int newRow = node._row + dir.first;
        int newCol = node._col + dir.second;

        if (newRow >= 0 && newCol >= 0 && newRow < height && newCol < width)
        {
            day10_node n(newRow, newCol, 0);
            toReturn.push_back(n);
        }
    }
    return toReturn;
}

std::vector<day10_node> day10_getNeightbours(const day10_node& node, const std::vector<string>& fileTxt)
{
    char c = fileTxt[node._row][node._col];

    const pair<int, int> top = { -1 ,0 };
    const pair<int, int> bottom = { 1 ,0 };
    const pair<int, int> left = { 0 ,-1 };
    const pair<int, int> right = { 0, 1 };


    switch (c)
    {
   
    case '|':
        return day10_getNeightboursChar(node, fileTxt, { top, bottom });//top, bottom
    case '-': 
        return day10_getNeightboursChar(node, fileTxt, { left, right });//left, right
    case 'L':
        return day10_getNeightboursChar(node, fileTxt, { top, right});//top, right
    case 'J':
        return day10_getNeightboursChar(node, fileTxt, { top, left });//top, left
    case '7':
        return day10_getNeightboursChar(node, fileTxt, { bottom, left });//bottom, left
    case 'F':
        return day10_getNeightboursChar(node, fileTxt, { bottom, right });//bottom, right
    case 'S':
        return day10_getNeightboursChar(node, fileTxt, {top, left });//top, bottom, left, right

    default:
        case '.': return {};
    }

}

std::vector<day10_node> day10_getAnyNeightbour(const day10_node& node, const std::vector<string>& fileTxt)
{
    const pair<int, int> top = { -1 ,0 };
    const pair<int, int> bottom = { 1 ,0 };
    const pair<int, int> left = { 0 ,-1 };
    const pair<int, int> right = { 0, 1 };

    return day10_getNeightboursChar(node, fileTxt, { top, left, bottom, right });//top, bottom, left, right
}

void day10_cleanOutsidePoints(std::vector<std::vector<int>>& graphDepth, const std::vector<string>& fileTxt)
{
    int count = 0;
    for (int row = 0; row < fileTxt.size(); ++row)
    {
        bool inside = false;

        for (int col = 0; col < fileTxt[0].size(); ++col)
        {
            if (graphDepth[row][col] == -1)
            {
                if (!inside)
                {
                    graphDepth[row][col] = -2;
                }
            }
            else
            {
                char c = fileTxt[row][col];
                if (c == '|' || c == 'L' || c == 'J' || c == 'S')
                {
                    inside = !inside;
                }
            }
        }
    }
}

void day10_print(const std::vector<string>& fileTxt, const std::vector<std::vector<int>>& graphDepth)
{
    for (int row = 0; row < graphDepth.size(); ++row)
    {
        for (int col = 0; col < graphDepth[0].size(); ++col)
        {
            if (graphDepth[row][col] == -1)
            {
                std::cout << ".";
            }
            else
            {
                if (graphDepth[row][col] == -2)
                {
                    std::cout << " ";
                }
                else
                {
                    char c = fileTxt[row][col];

                    switch (c)
                    {

                    case '|':
                        std::cout << char(186); break;
                    case '-':
                        std::cout << char(205); break;
                    case 'L':
                        std::cout << char(200); break;
                    case 'J':
                        std::cout << char(188); break;
                    case '7':
                        std::cout << char(187); break;
                    case 'F':
                        std::cout << char(201); break;
                    case 'S':
                        //  std::cout << char(206); break;
                        std::cout << "S"; break;
                    }
                }
            }
        }
        std::cout << "\n";
    }
}

void day10_a()
{
    auto fileTxt = ReadFile("./input/day10.txt");

    int width = fileTxt[0].size();
    int height = fileTxt.size();

    std::vector<std::vector<int>> graphDepth;

    int startCol = 0;
    int startRow = 0;

    for (int row = 0; row < height; ++row)
    {
        std::vector<int> line(width, -1);

        auto pos = fileTxt[row].find('S');
        if (pos != std::string::npos)
        {
            startCol = pos;
            startRow = row;
        }
        graphDepth.push_back(line);
    }

    std::vector< day10_node> nodesToAnalyze;

    day10_node startNode(startRow, startCol, 0);
    nodesToAnalyze.push_back(startNode);
    graphDepth[startRow][startCol] = 0;

    long long maxValue = -1;

    while (nodesToAnalyze.size() > 0)
    {
        day10_node node = nodesToAnalyze[0];

        nodesToAnalyze.erase(nodesToAnalyze.begin());

        auto neightbours = day10_getNeightbours(node, fileTxt);

        for (auto neightbour : neightbours)
        {
            if (graphDepth[neightbour._row][neightbour._col] == -1 && fileTxt[neightbour._row][neightbour._col] != '.')
            {
                graphDepth[neightbour._row][neightbour._col] = node._currentDepth + 1;
                day10_node newNode(neightbour._row, neightbour._col, node._currentDepth + 1);
                nodesToAnalyze.push_back(newNode);
                if (node._currentDepth + 1 > maxValue)
                {
                    maxValue = node._currentDepth + 1;
                }
            }
        }
    }
    std::cout << "day10 =>" << maxValue << "\n";
}

void day10_b( bool print)
{
    auto fileTxt = ReadFile("./input/day10.txt");

    int width = fileTxt[0].size();
    int height = fileTxt.size();

    std::vector<std::vector<int>> graphDepth;

    int startCol = 0;
    int startRow = 0;

    for (int row = 0; row < height; ++row)
    {
        std::vector<int> line(width, -1);

        auto pos = fileTxt[row].find('S');
        if (pos != std::string::npos)
        {
            startCol = pos;
            startRow = row;
        }
        graphDepth.push_back(line);
    }


    {
        std::vector< day10_node> nodesToAnalyze;
        day10_node startNode(startRow, startCol, 0);
        nodesToAnalyze.push_back(startNode);
        graphDepth[startRow][startCol] = 0;

        while (nodesToAnalyze.size() > 0)
        {
            day10_node node = nodesToAnalyze[0];

            nodesToAnalyze.erase(nodesToAnalyze.begin());

            auto neightbours = day10_getNeightbours(node, fileTxt);

            for (auto neightbour : neightbours)
            {
                if (graphDepth[neightbour._row][neightbour._col] == -1 && fileTxt[neightbour._row][neightbour._col] != '.')
                {
                    graphDepth[neightbour._row][neightbour._col] = node._currentDepth + 1;
                    day10_node newNode(neightbour._row, neightbour._col, node._currentDepth + 1);
                    nodesToAnalyze.push_back(newNode);
                }
            }
        }
    }
    
    day10_cleanOutsidePoints(graphDepth, fileTxt);

    int count = 0;
    for (int row = 0; row < fileTxt.size(); ++row)
    {
        bool inside = false;

        for (int col = 0; col < fileTxt[0].size(); ++col)
        {
            if (graphDepth[row][col] == -1)
            {
                ++count;
            }
        }
    }

    std::cout << "day10_b =>" << count << "\n";
    if (print)
    {
        day10_print(fileTxt, graphDepth);
    }
}

void day10()
{
    day10_a();
    day10_b(false);
}

void day11_parseSpace(const std::vector<string>& fileTxt, std::vector<pair<int, int>>& galaxies, std::vector<int>& emptyRow, std::vector<int>& emptyCol)
{
    std::vector<bool> colStatus(fileTxt[0].size(), false);
    std::vector<bool> rowStatus(fileTxt.size(), false);

    for (int row = 0; row < fileTxt.size(); ++row)
    {
        for (int col = 0; col < fileTxt[row].size(); ++col)
        {
            if (fileTxt[row][col] == '#')
            {
                colStatus[col] = true;
                galaxies.push_back({ row, col });
                rowStatus[row] = true;
            }
        }
    }

    for (int i = 0; i < colStatus.size(); ++i)
    {
        if (!colStatus[i])
        {
            emptyCol.push_back(i);
        }
    }

    for (int i = 0; i < rowStatus.size(); ++i)
    {
        if (!rowStatus[i])
        {
            emptyRow.push_back(i);
        }
    }
}

int day11_manhattanDistance(std::pair<int, int>a, std::pair<int, int> b)
{
    return abs(a.first - b.first) + abs(a.second - b.second);
}

int day11_getVerticalExtra(std::pair<int, int>a, std::pair<int, int> b, const std::vector<int>& emptyCol)
{
    int minValue = min(a.second, b.second);
    int maxValue = max(a.second, b.second);

    int count = 0;
    for (auto col : emptyCol)
    {
        if (minValue < col && col < maxValue)
        {
            ++count;
        }
    }
    return count;
}

int day11_getHorizontalExtra(std::pair<int, int>a, std::pair<int, int> b, const std::vector<int>& emptyRow)
{
    int minValue = min(a.first, b.first);
    int maxValue = max(a.first, b.first);

    int count = 0;
    for (auto row : emptyRow)
    {
        if (minValue < row && row < maxValue)
        {
            ++count;
        }
    }
    return count;
}



long long day11_solver(long long increase)
{
    auto fileTxt = ReadFile("./input/day11.txt");

    std::vector<pair<int, int>> galaxies;
    std::vector<int> emptyRow;
    std::vector<int> emptyCol;

    day11_parseSpace(fileTxt, galaxies, emptyRow, emptyCol);

    long long solution = 0;

    for (int galIndxA = 0; galIndxA < galaxies.size(); ++galIndxA)
    {
        for (int galIndxB = galIndxA + 1; galIndxB < galaxies.size(); ++galIndxB)
        {
            int currentDist = day11_manhattanDistance(galaxies[galIndxA], galaxies[galIndxB]);

            int extraCol = day11_getVerticalExtra(galaxies[galIndxA], galaxies[galIndxB], emptyCol);
            int extraRow = day11_getHorizontalExtra(galaxies[galIndxA], galaxies[galIndxB], emptyRow);

            currentDist += (extraCol * (increase -1)) + (extraRow * (increase-1));
            //std::cout << galIndxA << " => " << galIndxB << " =" << currentDist << "\n";
            solution += currentDist;
        }
    }

    return solution;
}

void day11()
{
    std::cout << "day 11 => " << day11_solver(2) << "\n";
    std::cout << "day 11_B => " << day11_solver(1000000) << "\n";
}

bool day12_stillValid(const string& line, const std::vector<int>& numbers, int positionIdx, int numberIdx)
{
    
    string newLine = line;
    
    for (int i = 0; i < positionIdx; ++i)
    {
        if (newLine[i] == '?')
        {
            newLine[i] = '.';
        }
    }

    for (int i = positionIdx; i < positionIdx + numbers[numberIdx]; ++i)
    {
        newLine[i] = '#';
    }

    bool findStart = false;
    int countConsecutives = 0;
    int currentNumberIndex = 0;
    for (int i = 0; i < positionIdx + numbers[numberIdx]; ++i)
    {
        ////somehow we excede the number, with a bad combination,like .#.#? 
        //if (currentNumberIndex >= numbers.size())
        //{
        //    return false;
        //}

        if (newLine[i] == '#')
        {
            ++countConsecutives;
            findStart = true;
        }
        else
        {
            //? or .
            if (findStart)
            {
                if (countConsecutives != numbers[currentNumberIndex])
                {
                    return false;
                }
                ++currentNumberIndex;
            }
            findStart = false;
            countConsecutives = 0;
        }
    }

    if (findStart)
    {
        if (countConsecutives != numbers[currentNumberIndex])
        {
            return false;
        }  
        ++currentNumberIndex;
    }


    //if we are in the end, cant be any more #
    if (currentNumberIndex == numbers.size())
    {
        for (int i = positionIdx + numbers[numberIdx]; i < newLine.size(); ++i)
        {
            if (newLine[i] == '#')
            {
                return false;
            }
        }
    }

    return true;
}

bool day12_enterNumber(const string& line, const std::vector<int>& numbers, int positionIdx, int numberIdx, const string& currentString)
{
    //do not enter
    if (positionIdx + numbers[numberIdx] > line.size())
    { 
        return false; 
    }

    //inside, there should be a space
    for (int i = positionIdx; i < positionIdx + numbers[numberIdx]; ++i)
    {
        if (line[i] == '.')
        {
            return false;
        }
    }

    if (positionIdx + numbers[numberIdx] < line.size())
    {
        if (line[positionIdx + numbers[numberIdx]] == '#')
        {
            //case like ?#? 1 => ##?
            return false;
        }
    }


    if (!day12_stillValid(currentString, numbers, positionIdx, numberIdx))
    {
        return false;
    }

    return true;
}

long long day12_optimizedSolution(const string& line, const std::vector<int>& numbers, int positionIdx, int numberIdx, map<string, long long>& cache, const string& currentString )
{
    string key = std::to_string(positionIdx) + "-" + std::to_string(numberIdx);
    
    if (cache.find(key) != cache.end())
    {
        return cache[key];
    }

    if (numbers.size() == numberIdx)
    {
        return 1;
    }

    if (positionIdx >= line.size())
    {
        return 0;
    }

    while (line[positionIdx] == '.')
    {
        ++positionIdx;
    }

    long long solution = 0;
    if (day12_enterNumber(line, numbers, positionIdx, numberIdx, currentString))
    {
        int size = numbers[numberIdx] + 1;
        string newString = currentString;

        for (int i = positionIdx; i < positionIdx + numbers[numberIdx]; ++i)
        {
            newString[i] = '#';
        }

        solution += day12_optimizedSolution(line, numbers, positionIdx + size, numberIdx +1 , cache, newString);
    }

    if (line[positionIdx] == '?')
    {
        solution += day12_optimizedSolution(line, numbers, positionIdx + 1, numberIdx, cache, currentString);
    }

    cache.insert({ key, solution });
    return solution;

}

long long da12_solve(const string& line, std::vector<int> numbers)
{
    std::map<string, long long> cache;
    long long solution = day12_optimizedSolution(line, numbers, 0, 0, cache, line);

    return solution;
}

long long day12_partA(const string& line)
{
    auto division = split(line, " ");
    string fields = division[0];

    auto numbers_split = split(division[1], ",");

    std::vector<int> numbers;
    for (auto s : numbers_split)
    {
        numbers.push_back(atoi(s.c_str()));
    }

    return da12_solve(fields, numbers);

}


long long day12_partB(const string& line)
{
    auto division = split(line, " ");
    string fields = division[0];

    auto numbers_split = split(division[1], ",");

    std::vector<int> numbers;
    for (auto s : numbers_split)
    {
        numbers.push_back(atoi(s.c_str()));
    }

    std::vector<int> newNumbers;
    for (int i = 0; i < 5; ++i)
    {
        for (auto x : numbers)
        {
            newNumbers.push_back(x);
        }
    }

    string newInput = "";
    for (int i = 0; i < 5; ++i)
    {
        newInput += fields + "?";
    }
    newInput =  newInput.substr(0, newInput.size() - 1);

    return da12_solve(newInput, newNumbers);

}

void day12()
{
    auto fileTxt = ReadFile("./input/day12.txt");

    long long solution = 0;
    for (auto line : fileTxt)
    {
        long long extra  = day12_partA(line);
        solution += extra;
    }
    std::cout << "day 12 => " << solution << "\n";

    long long solution_b = 0;
    for (auto line : fileTxt)
    {
        long long extra = day12_partB(line);
        solution_b += extra;
    }
    std::cout << "day 12_b => " << solution_b << "\n";
}

int day13_compareColumns(const std::vector<string>& puzzle, int colA, int colB)
{
    int count = 0;
    for (int i = 0; i < puzzle.size(); ++i)
    {
        if (puzzle[i][colA] == puzzle[i][colB])
        {
            ++count;
        }
    }
    return count;
}

int day13_compareRows(const std::vector<string>& puzzle, int topRow, int bottomRow)
{
    int count = 0;
    for (int i = 0; i < puzzle[topRow].size(); ++i)
    {
        if (puzzle[topRow][i] == puzzle[bottomRow][i])
        {
            ++count;
        }
    }
    return count;
}

bool day13_getSimetricColumns(const std::vector<string>& puzzle, int leftColumn, int rightColumn, bool partB)
{
    bool found = true;
    while (leftColumn >= 0 && rightColumn < puzzle[0].size())
    {
        int count = day13_compareColumns(puzzle, leftColumn, rightColumn);
        if (partB)
        {
            if (count == puzzle.size() - 1)
            {
                if (!found)
                {
                    return false;
                }
                found = !found;
            }

            if (count < puzzle.size() - 1)
            {
                return false;
            }

        }
        else
        {
            if (count != puzzle.size())
            {
                return false;
            }
        }
        --leftColumn;
        ++rightColumn;
    }
    return true;
}

bool day13_getSimetricRows(const std::vector<string>& puzzle, int topRow, int bottomRow, bool partB)
{
    bool found = true;
    while (topRow >= 0 && bottomRow < puzzle.size())
    {
        int count = day13_compareRows(puzzle, topRow, bottomRow);
        if (partB)
        {
            if (count == puzzle[0].size() - 1)
            {
                if (!found)
                {
                    return false;
                }
                found = !found;
            }

            if (count < puzzle[0].size() - 1)
            {
                return false;
            }

        }
        else
        {
            if (count != puzzle[0].size())
            {
                return false;
            }
        }
        --topRow;
        ++bottomRow;
    }
    return true;
}

long long day13_analyzeCols(const std::vector<string>& puzzle, int partB, bool usePartB)
{
    for (int i = 1; i < puzzle[0].size(); ++i)
    {
        int leftColumn = i - 1;
        int rightColumn = i;

        if (day13_getSimetricColumns(puzzle, leftColumn, rightColumn, usePartB))
        {
            if (partB != (i -1))
            {
                return i - 1;
            }
        }
    }

    return -1;
}

long long day13_analyzeRows(const std::vector<string>& puzzle, int partB, bool usePartB)
{
    for (int i = 1; i < puzzle.size(); ++i)
    {
        int topRow = i - 1;
        int bottomRow = i;

        if (day13_getSimetricRows(puzzle, topRow, bottomRow, usePartB))
        {
            if (partB != (i - 1))
            {
                return i - 1;
            }
        }
    }

    return -1;
}

long long day13_analyze(const std::vector<string>& puzzle, bool partB)
{
    int rows_a = day13_analyzeRows(puzzle, -1, false);
    int cols_a = day13_analyzeCols(puzzle, -1, false);

    if (partB)
    {
        int rows_b = day13_analyzeRows(puzzle, rows_a, true);
        int cols_b = day13_analyzeCols(puzzle, cols_a, true);

        rows_a = rows_b;
        cols_a = cols_b;
    }

    long long sol = 0;
    sol += (cols_a + 1);
    sol += (rows_a + 1) * 100;

    return sol;
}

void day13()
{
    auto fileTxt = ReadFile("./input/day13.txt");

    std::vector<std::vector<string>> input;
    std::vector<string> currentInput;
    long long sol_a = 0;
    long long sol_b = 0;
    for (int i = 0; i < fileTxt.size(); ++i)
    {
        if (fileTxt[i].size() == 0)
        {
            sol_a += day13_analyze(currentInput, false);
            sol_b += day13_analyze(currentInput, true);
            currentInput.clear();
        }
        else
        {
            currentInput.push_back(fileTxt[i]);
        }
    }
    sol_a += day13_analyze(currentInput, false);
    sol_b += day13_analyze(currentInput, true);

    std::cout << "day13 => " << sol_a << "\n";
    std::cout << "day13_b => " << sol_b << "\n";

}

void day14_moveUp(std::vector<std::string>& board)
{
    int width = board[0].size();
    int height = board.size();

    for (int col = 0; col < width; ++col)
    {
        int lastPosition = 0;

        for (int row = 0; row < height; ++row)
        {
            if (board[row][col] == '#')
            {
                lastPosition = row + 1;
            }

            if (board[row][col] == 'O')
            {
                //move to position
                board[row][col] = '.';
                board[lastPosition][col] = 'O';
                ++lastPosition;
            }
        }
    }
}

void day14_moveDown(std::vector<std::string>& board)
{
    int width = board[0].size();
    int height = board.size();

    for (int col = 0; col < width; ++col)
    {
        int lastPosition = height -1;

        for (int row = height -1; row >= 0; --row)
        {
            if (board[row][col] == '#')
            {
                lastPosition = row - 1;
            }

            if (board[row][col] == 'O')
            {
                //move to position
                board[row][col] = '.';
                board[lastPosition][col] = 'O';
                --lastPosition;
            }
        }
    }
}

void day14_moveLeft(std::vector<std::string>& board)
{
   int width = board[0].size();
   int height = board.size();

   for (int row = 0; row < height; ++row)
   {
       int lastPosition = 0;
       for (int col = 0; col < width; ++col)
       {
           if (board[row][col] == '#')
           {
               lastPosition = col + 1;
           }

           if (board[row][col] == 'O')
           {
               board[row][col] = '.';
               board[row][lastPosition] = 'O';
               ++lastPosition;
           }
       }
   }
}

void day14_moveRight(std::vector<std::string>& board)
{
    int width = board[0].size();
    int height = board.size();

    for (int row = 0; row < height; ++row)
    {
        int lastPosition = width -1;
        for (int col = width-1; col >= 0; --col)
        {
            if (board[row][col] == '#')
            {
                lastPosition = col - 1;
            }

            if (board[row][col] == 'O')
            {
                board[row][col] = '.';
                board[row][lastPosition] = 'O';
                --lastPosition;
            }
        }
    }
}

std::vector<std::string> day14_rotateHourly(const std::vector<std::string>& board)
{
    std::vector<std::string> newBoard;
    int width = board[0].size();
    int height = board.size();

    for (int col = 0; col < width; ++col)
    {
        std::string tmp(height, '.');

        for (int row = 0; row < height; ++row)
        {
            int position = height - 1 - row;
            tmp[position] = board[row][col];
        }
        newBoard.push_back(tmp);
    }


    return newBoard;
}


long long day14_calculateResult(const std::vector<std::string>& board)
{
    int height = board.size();
    long long result = 0;
    for (int row = 0; row < height; ++row)
    {
        for (auto x : board[row])
        {
            if (x == 'O')
            {
                result += (height - row);
            }
        }
    }

    return result;
}

void day14_b()
{
    auto fileTxt = ReadFile("./input/day14.txt");

    std::map<string, int> savedPositions;
    long long totalRounds = 1000000000;

    for (long long round = 0; round < totalRounds; ++round)
    {
        //for (int i = 0; i < 4; ++i)
        {
            day14_moveUp(fileTxt);
            day14_moveLeft(fileTxt);
            day14_moveDown(fileTxt);
            day14_moveRight(fileTxt);

            string key = "";
            for (auto x : fileTxt)
            {
                key += x;
            }

            if (savedPositions.find(key) != savedPositions.end())
            {
                //found loop
                long long loopSize = round - savedPositions[key];
                long long increase = (totalRounds - round) / loopSize;
                round += increase * loopSize;
                savedPositions.clear();
                //break;
            }
            else
            {
                savedPositions.insert({ key, round });
            }
        }
    }
   
    long long solutionB = day14_calculateResult(fileTxt);
    std::cout << "day14 b=> " << solutionB << "\n";
}


void day14_a()
{
    auto fileTxt = ReadFile("./input/day14.txt");
    day14_moveUp(fileTxt);
    long long solutionA = day14_calculateResult(fileTxt);
    std::cout << "day14 => " << solutionA << "\n";
}

void day14()
{
    day14_a();
    day14_b();
}



void day15_a()
{
    auto fileTxt = ReadFile("./input/day15.txt");
    
    auto separation = split(fileTxt[0], ",");

    long long result = 0;

    for (auto x : separation)
    {
        long long hash = 0;
        for (auto c : x)
        {
            hash += (int)c;
            hash = hash * 17;
            hash = hash % 256;
        }
        result += hash;
    }
    std::cout << "day15 => " << result << "\n";
}

struct day15_box
{
public:
    string label;
    char instruction;
    int number = -1;
    int hash;
    day15_box(string s)
    {
        if (s.back() == '-')
        {
            label = s.substr(0, s.size() - 1);
            instruction = s.back();
            
        }
        else
        {
            instruction = '=';
            label = s.substr(0, s.size() - 2);
            number = atoi(s.substr(s.size() - 1).c_str());
        }

        hash = 0;
        for (auto c : label)
        {
            hash += (int)c;
            hash = hash * 17;
            hash = hash % 256;
        }
    }
};

void day15_b()
{
    auto fileTxt = ReadFile("./input/day15.txt");

    std::array<std::vector<day15_box>, 256> boxes;

    auto instructions = split(fileTxt[0], ",");

    for (auto instruction : instructions)
    {
        day15_box ins(instruction);
        if (ins.instruction == '-')
        {
            boxes[ins.hash].erase(std::remove_if(boxes[ins.hash].begin(), boxes[ins.hash].end(), [ins](day15_box b) {return b.label == ins.label; }) ,
                        boxes[ins.hash].end());

        }
        if (ins.instruction == '=')
        {
            auto position = std::find_if(boxes[ins.hash].begin(), boxes[ins.hash].end(), [ins](day15_box b) {return b.label == ins.label; });
            if (position == boxes[ins.hash].end())
            {
                //add
                boxes[ins.hash].push_back(ins);
            }
            else
            {
                //replace
                int place = position - boxes[ins.hash].begin();
                boxes[ins.hash][place].number = ins.number;
            }
        }
    }

    long long count = 0;
    for (int box = 0; box < boxes.size(); ++box)
    {
        for (int ins = 0; ins < boxes[box].size(); ++ins)
        {
            int value = (box + 1) * (ins + 1) * boxes[box][ins].number;
            count += value;
        }
    }
    std::cout << "day 15_b => " << count << "\n";

}

void day15()
{
    day15_a();
    day15_b();
}

struct day16_particle
{
public:
    int row = 0;
    int col = 0;
    enum class ORIENTATIONS{NORTH, SOUTH, WEST, EAST};
    ORIENTATIONS orientation;

    day16_particle(int r, int c, ORIENTATIONS o) :row(r), col(c), orientation(o) {};

    void moveNext()
    {
        int increaseRow = 0;
        int increaseCol = 0;

        switch (orientation)
        {
        case ORIENTATIONS::NORTH: increaseRow = -1; break;
        case ORIENTATIONS::SOUTH: increaseRow = +1; break;
        case ORIENTATIONS::EAST: increaseCol = -1; break;
        case ORIENTATIONS::WEST: increaseCol = +1; break;
        }
        row += increaseRow;
        col += increaseCol;
    }

    void rotate90()
    {
        switch (orientation)
        {
        case ORIENTATIONS::NORTH: orientation = ORIENTATIONS::EAST; break;
        case ORIENTATIONS::SOUTH: orientation = ORIENTATIONS::WEST; break;
        case ORIENTATIONS::EAST: orientation = ORIENTATIONS::NORTH; break;
        case ORIENTATIONS::WEST: orientation = ORIENTATIONS::SOUTH; break;
        }
    }

    void rotateMinus90()
    {
        switch (orientation)
        {
        case ORIENTATIONS::NORTH: orientation = ORIENTATIONS::WEST; break;
        case ORIENTATIONS::SOUTH: orientation = ORIENTATIONS::EAST; break;
        case ORIENTATIONS::EAST: orientation = ORIENTATIONS::SOUTH; break;
        case ORIENTATIONS::WEST: orientation = ORIENTATIONS::NORTH; break;
        }
    }

};

long long day16_solver(const std::vector<string>& fileTxt, int startRow, int startCol, day16_particle::ORIENTATIONS orientation)
{

    std::vector<day16_particle> particles;
    day16_particle start(startRow, startCol, orientation);
    particles.push_back(start);

    std::set<pair<int, int>> occupedPlaces;
    std::set<pair<int, int>> divisionsTaken;

    while (particles.size() > 0)
    {
        day16_particle particle = particles.front();
        particles.erase(particles.begin());

        while (particle.row >= 0 && particle.col >= 0 && particle.row < fileTxt.size() && particle.col < fileTxt[0].size())
        {
            char c = fileTxt[particle.row][particle.col];
            occupedPlaces.insert({ particle.row, particle.col });
            if (c == '/')
            {
                particle.rotateMinus90();
            }

            if (c == '\\')
            {
                particle.rotate90();
            }

            if (c == '|')
            {
                if (divisionsTaken.find({ particle.row, particle.col }) != divisionsTaken.end())
                {
                    //loop detected
                    break;
                }
                else
                {
                    if (particle.orientation == day16_particle::ORIENTATIONS::WEST || particle.orientation == day16_particle::ORIENTATIONS::EAST)
                    {
                        day16_particle newParticle(particle.row, particle.col, day16_particle::ORIENTATIONS::SOUTH);
                        newParticle.moveNext();
                        particles.push_back(newParticle);

                        particle.orientation = day16_particle::ORIENTATIONS::NORTH;

                        divisionsTaken.insert({ particle.row, particle.col });
                    }
                }
            }

            if (c == '-')
            {
                if (divisionsTaken.find({ particle.row, particle.col }) != divisionsTaken.end())
                {
                    //loop detected
                    break;
                }
                else
                {
                    if (particle.orientation == day16_particle::ORIENTATIONS::NORTH || particle.orientation == day16_particle::ORIENTATIONS::SOUTH)
                    {
                        day16_particle newParticle(particle.row, particle.col, day16_particle::ORIENTATIONS::WEST);
                        newParticle.moveNext();
                        particles.push_back(newParticle);

                        particle.orientation = day16_particle::ORIENTATIONS::EAST;

                        divisionsTaken.insert({ particle.row, particle.col });
                    }
                }
            }

            particle.moveNext();
        }

    }

    return occupedPlaces.size();
}

long long day16_partB_bruteForce(const std::vector<string>& fileTxt)
{
    long long best = 0;

    for(int col = 0; col < fileTxt[0].size(); ++col)
    {
        long long sol1 = day16_solver(fileTxt, 0, col, day16_particle::ORIENTATIONS::SOUTH);

        if (sol1 > best)
        {
            best = sol1;
        }

        long long sol2 = day16_solver(fileTxt, fileTxt.size()-1, 0, day16_particle::ORIENTATIONS::NORTH);
        if (sol2 > best)
        {
            best = sol2;
        }
    }

    for (int row = 0; row < fileTxt.size(); ++row)
    {
        long long sol1 = day16_solver(fileTxt, row, 0, day16_particle::ORIENTATIONS::WEST);
        if (sol1 > best)
        {
            best = sol1;
        }

        long long sol2 = day16_solver(fileTxt, row, fileTxt[0].size()-1, day16_particle::ORIENTATIONS::EAST);
        if (sol2 > best)
        {
            best = sol2;
        }
    }

    return best;
}


void day16()
{
    auto fileTxt = ReadFile("./input/day16.txt");
    long long partA = day16_solver(fileTxt, 0,0, day16_particle::ORIENTATIONS::WEST);
    
    std::cout << "day16_A => " << partA << "\n";

    long long partB = day16_partB_bruteForce(fileTxt);
    //long long partB = 8225;
    std::cout << "day16_b => " << partB << "\n";
}

enum class day17_directions{NORTH, SOUTH, WEST, EAST, NONE};

string day17_directionToString(day17_directions dir)
{
    switch (dir)
    {
    case day17_directions::NORTH:
        return "north";
        break;
    case day17_directions::SOUTH:
        return "south";
        break;
    case day17_directions::WEST:
        return "east";
        break;
    case day17_directions::EAST:
        return "west";
    }
    return "**";
}

struct day17_node
{
public:
    int row = -1;
    int col =  -1;
    int cost = INT_MAX;
    int streak = 0;
    day17_directions direction = day17_directions::NONE;

    day17_node(int r, int c) :row(r), col(c) {}
    day17_node(int r, int c, int co, int s, day17_directions dir) : row(r), col(c), cost(co), streak(s), direction(dir) {}
};

string day17_cacheKey(int row, int col, int streak, day17_directions dir )
{
    return std::to_string(row) + "_" + std::to_string(col) + "_" + std::to_string(streak) + "_" + day17_directionToString(dir);
}

day17_node day17_getNeightbour(const day17_node origin, const day17_directions dir)
{
    int increaseRow = 0;
    int increaseCol = 0;

    switch (dir)
    {
    case day17_directions::NORTH:
        --increaseRow;
        break;
    case day17_directions::SOUTH:
        ++increaseRow;
        break;
    case day17_directions::WEST:
        --increaseCol;
        break;
    case day17_directions::EAST:
        ++increaseCol;
    }
    day17_node sol(origin.row + increaseRow, origin.col + increaseCol);
    return sol;
}

bool day17_isValidNeightbour(const day17_node origin, const day17_directions dir, int width, int height)
{
    auto neightbour = day17_getNeightbour(origin, dir);

    if (neightbour.row < 0 || neightbour.row >= height) { return false; }
    if (neightbour.col < 0 || neightbour.col >= width) { return false; }

    return true;
}

bool day17_isAntiDirection(const day17_directions dir1, const day17_directions dir2)
{
    switch (dir1)
    {
    case day17_directions::NORTH: return dir2 == day17_directions::SOUTH; break;
    case day17_directions::SOUTH: return dir2 == day17_directions::NORTH; break;
    case day17_directions::EAST: return dir2 == day17_directions::WEST; break;
    case day17_directions::WEST: return dir2 == day17_directions::EAST; break;

    }
    return false;
}

bool day17_onCache(day17_node node, const map<string, int>& cache)
{
    string key = day17_cacheKey(node.row, node.col, node.streak, node.direction);

    return cache.find(key) != cache.end();
}


bool day17_onCache(int row, int col, int streak, day17_directions dir, int currentCost, const map<string, int>& cache)
{
    //if I found something with lower streak and cost <= currentCost then return false
    //this include same streak and direction

    for (int s = 1; s <= streak; ++s)
    {
        string key = day17_cacheKey(row, col, s, dir);

        if (cache.find(key) != cache.end())
        {
            if (cache.at(key) < currentCost)
            {
                return false;
            }
        }
    }


    return false;
}


bool day17_onFinalNode(int width, int height, day17_node node, int minConsecutive, int maxConsecutive)
{
    return node.col == width - 1 && node.row == height - 1 && node.streak >= minConsecutive && node.streak <= maxConsecutive;
}

long long day17_solve(const std::vector<string> board, int minConsecutive, int maxConsecutive)
{
    int width = board[0].size();
    int height = board.size();

    map<string, int> nodesIKnow;

    auto my_comp = [width, height](const day17_node& l, const day17_node& r)
    {
        int manhattanLeft = (width - l.col) + (height - l.row);
        int manhattanRight = (width - r.col) + (height - l.row);

        //if there is some direction that is lower, take this
        int bestLeft = l.cost + manhattanLeft;
        int bestRight = r.cost + manhattanRight;

        if (bestLeft != bestRight)
        {
            return bestLeft > bestRight;
        }

        //if same best approach, take the one with fewer manhattan
        if (manhattanLeft != manhattanRight)
        {
            return manhattanRight > manhattanRight;
        }

        //if same manhattan, decide base on rows
        if (l.row != r.row)
        {
            return l.row < r.row;
        }
        return l.col < r.col;

    };
    std::priority_queue< day17_node,
        std::vector< day17_node >,
        decltype(my_comp)> priority_list{ my_comp };

    {
        day17_node start(0, 0, 0, 0, day17_directions::NONE);
        priority_list.push(start);
    }

    while (!priority_list.empty())
    {
        day17_node node = priority_list.top();
        priority_list.pop();

        if (day17_onCache(node, nodesIKnow))
        {
            continue;
        }

        {
            string key = day17_cacheKey(node.row, node.col, node.streak, node.direction);
            nodesIKnow.insert({ key, node.cost });
        }


        if (day17_onFinalNode(width, height, node, minConsecutive, maxConsecutive))
        {
            return node.cost;
        }

        for (auto direction : { day17_directions::NORTH, day17_directions::SOUTH, day17_directions::EAST, day17_directions::WEST })
        {
            if (day17_isAntiDirection(direction, node.direction))
            {
                continue;
            }
            if (!day17_isValidNeightbour(node, direction, width, height))
            {
                continue;
            }

            if (direction != node.direction && node.direction != day17_directions::NONE)
            {
                if (node.streak < minConsecutive)
                {
                    continue;
                }
            }

            int currentStreak = 1;
            if (direction == node.direction)
            {
                currentStreak = node.streak + 1;
            }

            if (currentStreak > maxConsecutive)
            {
                continue;
            }


            auto neightbour = day17_getNeightbour(node, direction);
            int costNeightbour = board[neightbour.row][neightbour.col] - '0';
            int currentCost = node.cost + costNeightbour;

            if (!day17_onCache(neightbour.row, neightbour.col, currentStreak, direction, currentCost, nodesIKnow))
            {
                day17_node newNode(neightbour.row, neightbour.col, currentCost, currentStreak, direction);
                priority_list.push(newNode);
            }
        }
    }

    return 0;
}

void day17()
{
    auto fileTxt = ReadFile("./input/day17.txt");
    auto part_a = day17_solve(fileTxt, 1, 3);//886
    auto part_b = day17_solve(fileTxt, 4, 10);//1055
    std::cout << "day 17 => " << part_a << "\n";
    std::cout << "day 17_b => " << part_b << "\n";
}

enum class day18_directions { NORTH, SOUTH, EAST, WEST, NONE };
struct day18_wall
{
public:
    long long x;
    long long y;
    long long size;
    day18_directions direction;

    day18_wall(int X, int Y, const string& line, bool partB)
    {
        x = X;
        y = Y;

        char dir = line[0];
        size = atoi(split(line, " ")[1].c_str());

        if (partB)
        {
            string color = line.substr(line.size()-7, 5);
            size = std::stoul(color, nullptr, 16);

            auto direction = line[line.size() - 2];
            switch (direction)
            {
            case '0': dir = 'R'; break;
            case '1': dir = 'D'; break;
            case '2': dir = 'L'; break;
            case '3': dir = 'U'; break;
            }

        }

        switch (dir)
        {
        case 'R': direction = day18_directions::EAST; break;
        case 'D': direction = day18_directions::SOUTH; break;
        case 'L': direction = day18_directions::WEST; break;
        case 'U': direction = day18_directions::NORTH; break;
        }
    }

    void nextPosition(long long& nextX, long long& nextY)
    {
        nextX = x;
        nextY = y;

        switch (direction)
        {
        case day18_directions::NORTH:
            nextY = y - size;
            break;
        case day18_directions::SOUTH:
            nextY = y + size;
            break;
        case day18_directions::EAST:
            nextX = x + size;
            break;
        case day18_directions::WEST:
            nextX = x - size;
            break;
        }
    }
};
void day18_buildWallsInformation(const std::vector<string> lines, vector<day18_wall>& wallsIds, bool partB)
{
    long long X = 0;
    long long Y = 0;

    for (auto l : lines)
    {
        day18_wall node(X, Y, l, partB);
        wallsIds.push_back(node);

        node.nextPosition(X, Y);
    }
}

long long day18_calculate(const vector<day18_wall>& wallsIds)
{
    long long toAdd = 0;
    long long perimeter = 0;

    for (int i = 0; i < wallsIds.size(); ++i)
    {
        int index0 = i;
        int index1 = (i + 1) % wallsIds.size();
        int prevIndex = (i - 1 + wallsIds.size()) % wallsIds.size();

        toAdd += (wallsIds[index0].x * (wallsIds[index1].y - wallsIds[prevIndex].y));

        perimeter +=  wallsIds[index0].size;
    }

    long long area = toAdd / 2;//gauss area: https://es.wikipedia.org/wiki/F%C3%B3rmula_del_%C3%A1rea_de_Gauss

    //pick: https://es.wikipedia.org/wiki/Teorema_de_Pick
    //A = I + B/2 - 1 where:
    //A is area
    //I is points inside
    //B is perimeter
    //and we want to know I + B

    long long result = area + perimeter / 2 + 1;

    return result;
}

void day18()
{
    auto fileTxt = ReadFile("./input/day18.txt");

    //if(false)
    {
        vector<day18_wall> wallsIds;
        day18_buildWallsInformation(fileTxt, wallsIds, false);
        auto b = day18_calculate( wallsIds);
        std::cout << "day18_a => " << b << "\n";
    }

    {
        vector<day18_wall> wallsIds;
        day18_buildWallsInformation(fileTxt, wallsIds, true);
        auto b = day18_calculate(wallsIds);
        std::cout << "day18_b => " << b << "\n";
    }
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
   //day17();
    day18();
}

// Ejecutar programa: Ctrl + F5 o menú Depurar > Iniciar sin depurar
// Depurar programa: F5 o menú Depurar > Iniciar depuración

// Sugerencias para primeros pasos: 1. Use la ventana del Explorador de soluciones para agregar y administrar archivos
//   2. Use la ventana de Team Explorer para conectar con el control de código fuente
//   3. Use la ventana de salida para ver la salida de compilación y otros mensajes
//   4. Use la ventana Lista de errores para ver los errores
//   5. Vaya a Proyecto > Agregar nuevo elemento para crear nuevos archivos de código, o a Proyecto > Agregar elemento existente para agregar archivos de código existentes al proyecto
//   6. En el futuro, para volver a abrir este proyecto, vaya a Archivo > Abrir > Proyecto y seleccione el archivo .sln
