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
    day3();
    day4();
    day5();
    day6();
    day7();
    day8();
}

// Ejecutar programa: Ctrl + F5 o menú Depurar > Iniciar sin depurar
// Depurar programa: F5 o menú Depurar > Iniciar depuración

// Sugerencias para primeros pasos: 1. Use la ventana del Explorador de soluciones para agregar y administrar archivos
//   2. Use la ventana de Team Explorer para conectar con el control de código fuente
//   3. Use la ventana de salida para ver la salida de compilación y otros mensajes
//   4. Use la ventana Lista de errores para ver los errores
//   5. Vaya a Proyecto > Agregar nuevo elemento para crear nuevos archivos de código, o a Proyecto > Agregar elemento existente para agregar archivos de código existentes al proyecto
//   6. En el futuro, para volver a abrir este proyecto, vaya a Archivo > Abrir > Proyecto y seleccione el archivo .sln
