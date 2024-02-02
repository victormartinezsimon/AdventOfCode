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


int day1_GetFirstNumber(const string& line, int start, int end, int increment, int& position)
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

void day1_GetStringPositions(string& line, int& leftValue, int& leftPosition, int& rightValue, int& rightPosition)
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
            int firstValue = day1_GetFirstNumber(l, 0, l.size(), +1, dummy);
            int secondValue = day1_GetFirstNumber(l,l.size()-1, -1, -1, dummy);

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
            day1_GetStringPositions(l, leftValue, leftPosition, rightValue, rightPosition);

            int positionFirst;
            int firstValue = day1_GetFirstNumber(l, 0, l.size(), +1, positionFirst);
            int positionSecond;
            int secondValue = day1_GetFirstNumber(l, l.size() - 1, -1, -1,positionSecond);

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

vector<vector<char>> day3_ParseFile(const std::vector<string>& file)
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

vector<pair<int, int>> day3_ExtractNumbers(const vector<char>& board)
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

bool day3_anySymbol(char c)
{
    return c != '.' && (c < '0' || c > '9');
}

bool day3_anyNumber(char c)
{
    return  (c >= '0' && c <= '9');
}

bool day3_validPosition(const vector<vector<char>>& board, int row, int col )
{
    //a b c
    //d X e
    //f g h

    if (row > 0 && col > 0)
    {
        char a = board[row - 1][col - 1];
        if (day3_anySymbol(a)) { return true; }
    }

    if (row > 0)
    {
        char b = board[row - 1][col];
        if (day3_anySymbol(b)) { return true; }
    }

    if (row > 0 && col < board[row].size() - 1)
    {
        char c = board[row - 1][col + 1];
        if (day3_anySymbol(c)) { return true; }
    }

    if (col > 0)
    {
        char d = board[row][col - 1];
        if (day3_anySymbol(d)) { return true; }
    }

    if (col < board[row].size() - 1)
    {
        char e = board[row][col + 1];
        if (day3_anySymbol(e)) { return true; }
    }

    if (row < board.size() - 1 && col > 0)
    {
        char f = board[row + 1][col - 1];
        if (day3_anySymbol(f)) { return true; }
    }

    if (row < board.size() - 1)
    {
        char g = board[row + 1][col];
        if (day3_anySymbol(g)) { return true; }
    }

    if (row < board.size()-1 && col < board[row].size() - 1)
    {
        char h = board[row + 1][col + 1];
        if (day3_anySymbol(h)) { return true; }
    }
    
    return false;
}

bool day3_validNumber(const vector<vector<char>>& board, int row, const pair<int, int> position)
{

    for (int i = position.first; i <= position.second; ++i)
    {
        if (day3_validPosition(board, row, i) >= 1)
        {
            return true;
        }
    }

    return false;
}

int day3_buildNumber(const vector<vector<char>>& board, int row, const pair<int, int> position)
{
    int solution = 0;

    std::string number = "";

    for (int col = position.first; col <= position.second; ++col)
    {
        number += board[row][col];
    }
    return atoi(number.c_str());
}

int day3_getGearNumberRow(const vector<vector<char>>& board, const std::vector < std::vector<pair<int, int>>>& numbers, int rowInvestigate, int colGear, int& numbersUsed)
{
    int sol = 1;
    for (auto number : numbers[rowInvestigate])
    {
       //inside
        if (colGear >= number.first && colGear <= number.second)
        {
            //premio
            sol *= day3_buildNumber(board, rowInvestigate, number);
            numbersUsed += 1;
        }
        
        //left
        if ( number.second == colGear - 1)
        {
            sol *= day3_buildNumber(board, rowInvestigate, number);
            numbersUsed += 1;
        }

        //right
        if (number.first == colGear + 1)
        {
            sol *= day3_buildNumber(board, rowInvestigate, number);
            numbersUsed += 1;
        }
    }
    
    return sol;
}

int day3_getGearNumbers(const vector<vector<char>>& board, const std::vector < std::vector<pair<int, int>>>& numbers, int row, int col)
{
   // int validNumbers = validGearPosition_day3(board, row, col);
    //if (validNumbers < 2) { return 0; }

    int result = 1;

    int numbersUsed = 0;
    if (row > 0)
    {
        result *= day3_getGearNumberRow(board, numbers, row - 1,  col, numbersUsed);
    }

    {
        result *= day3_getGearNumberRow(board, numbers, row,  col, numbersUsed);
    }

    if (row < board.size())
    {
        result *= day3_getGearNumberRow(board, numbers, row + 1,  col, numbersUsed);
    }
    if (numbersUsed < 2) { return 0; }
    return result;
}

void day3_a()
{
    std::vector<string> fileTxt = ReadFile("./input/day3.txt");

    auto board = day3_ParseFile(fileTxt);

    long long solution_a = 0;

    for (int row = 0; row < board.size(); ++row)
    {
        auto numbers = day3_ExtractNumbers(board[row]);

        for (auto number : numbers)
        {
            int n = day3_buildNumber(board, row, number);
            if (day3_validNumber(board, row, number))
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

    auto board = day3_ParseFile(fileTxt);

    std::vector < std::vector<pair<int, int>>> numbersPerRow;
    for (int row = 0; row < board.size(); ++row)
    {
        auto numbers = day3_ExtractNumbers(board[row]);

        numbersPerRow.push_back(numbers);
    }

    long long solution_b = 0;

    for (int row = 0; row < board.size(); ++row)
    {
        for (int col = 0; col < board[row].size(); ++col)
        {
            if (board[row][col] == '*')
            {
                int number = day3_getGearNumbers(board, numbersPerRow, row, col);
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

int day4_getTotalWinningNumbers(const string& s)
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
        int count = day4_getTotalWinningNumbers(fileTxt[i]);
        
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
        winsPerCard.push_back(day4_getTotalWinningNumbers(fileTxt[i]));
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

bool day5_lineWithInfo(const string& str)
{
    return '0' <= str[0] && str[0] <= '9';
}

std::vector<std::vector<day5_struct>> day5_parseDay(const std::vector<string>& input)
{
    int line = 1;//skip the seeds

    std::vector<std::vector<day5_struct>> toReturn;

    while (line < input.size())
    {
        if (day5_lineWithInfo(input[line]))
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

    auto parsedData = day5_parseDay(fileTxt);

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
    auto mutations = day5_parseDay(fileTxt);
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

    vector<long long> gdcs;

    for (auto n : allStart)
    {
        day8_node* endNode = nullptr;
        long long times = day8_countToLoopAnyEnd(n, endNode, fileTxt[0]);
        if (endNode != nullptr)
        {
            //std::cout << "[" << n->name << "," << endNode->name << "]: " << times << "\n";
            gdcs.push_back(times);
        }
    }

    long long result = gdcs[0];

    for (int i = 1; i < gdcs.size(); ++i)
    {
        result = std::lcm(result, gdcs[i]);
    }

    std::cout << "day8 b =>" << result << "\n";
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
    
    std::cout << "day16_a => " << partA << "\n";

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

/*
struct day19_part
{
    int x = 0;
    int m = 0;
    int a = 0;
    int s = 0;

    day19_part(const string& input)
    {
        string removeSymbols = input.substr(1, input.size() - 2);

        auto allSymbols = split(removeSymbols, ",");

        for (auto symbol : allSymbols)
        {
            char key = symbol[0];
            int value = atoi(symbol.substr(2).c_str());

            switch (key)
            {
            case 'x': x = value; break;
            case 'm': m = value; break;
            case 'a': a = value; break;
            case 's': s = value; break;
            }
        }
    }

    int getValue(char c)
    {
        switch (c)
        {
        case 'x': return x; break;
        case 'm': return m; break;
        case 'a': return a; break;
        case 's': return s; break;
        }
    }
};

struct day19_condition
{
public:
    char letter = 0;
    char action = 0;
    long long number = 0;
    string result = "";
    bool onlyResult = false;

    day19_condition(const string& s)//s>2770:qs
    {
        auto posSymbol = s.find(':');
        if (posSymbol != string::npos)
        {
            //condition with condition
            letter = s[0];
            action = s[1];
            
            string number_s = split(s.substr(2), ":")[0];
            number = atoll(number_s.c_str());
            result = s.substr(posSymbol + 1);
            onlyResult = false;
        }
        else
        {
            result = s;
            onlyResult = true;
        }
    }

};

struct day19_instruction
{
public:
    string key;
    vector<day19_condition> conditions;

    day19_instruction(const string& s) // qqz{s>2770:qs,m<1801:hdj,R}
    {
        auto positionSymbol = s.find('{');
        key = s.substr(0, positionSymbol);

        auto allConditions_str = s.substr(positionSymbol + 1, s.size() - positionSymbol - 2);

        auto conditions_str = split(allConditions_str, ",");

        for (auto c : conditions_str)
        {
            day19_condition cond(c);
            conditions.push_back(cond);
        }
    }


    string evaluate(day19_part part)
    {
        for (int condIdx = 0; condIdx< conditions.size(); ++condIdx)
        {
            day19_condition cond = conditions[condIdx];
            if (cond.onlyResult)
            {
                return cond.result;
            }

            auto value = part.getValue(cond.letter);
            auto comparation = cond.number;

            if (cond.action == '<')
            {
                if (value < comparation)
                {
                    return cond.result;
                }
            }

            if (cond.action == '>')
            {
                if (value > comparation)
                {
                    return cond.result;
                }
            }
        }
        return "";
    }


};

void day19_buildData(const std::vector<string>& lines, map<string, day19_instruction>& instructions, vector<day19_part>& parts)
{
    int index = 0;
    while (lines[index].size() > 0)
    {
        day19_instruction ins(lines[index]);
        instructions.insert({ ins.key, ins });
        ++index;
    }
    ++index;

    while (index < lines.size())
    {
        day19_part p(lines[index]);
        parts.push_back(p);
        ++index;
    }

}

string day19_analyzePart(const map<string, day19_instruction>& instructions, const day19_part& part)
{
    string currentInstruction = "in";

    while (instructions.find(currentInstruction) != instructions.end())
    {
        auto instruction = instructions.at(currentInstruction);

        currentInstruction = instruction.evaluate(part);
    }

    return currentInstruction;
}

void day19_analyze(const map<string, day19_instruction>& instructions, const vector<day19_part>& parts, vector<day19_part>& accepted, vector<day19_part>& rejected)
{
    for (auto part : parts)
    {
        string result = day19_analyzePart(instructions, part);

        if (result == "A")
        {
            accepted.push_back(part);
        }

        if (result == "R")
        {
            rejected.push_back(part);
        }
    }
}


void day19_partA(const vector<day19_part>& accepted)
{
    long long result = 0;

    for (auto a : accepted)
    {
        result += (a.a + a.m + a.s + a.x);
    }
    std::cout << "day 19_a => " << result << "\n";
}

*/

struct day19_part
{
    pair<int, int> a;
    pair<int, int> m;
    pair<int, int> s;
    pair<int, int> x;

    day19_part( int max)
    {
        x = { 1, max };
        m = { 1, max };
        a = { 1, max };
        s = { 1, max };
    }

    day19_part(const string& input)
    {
        string removeSymbols = input.substr(1, input.size() - 2);

        auto allSymbols = split(removeSymbols, ",");

        for (auto symbol : allSymbols)
        {
            char key = symbol[0];
            int value = atoi(symbol.substr(2).c_str());

            switch (key)
            {
            case 'x': x = { value,value }; break;
            case 'm': m = { value,value }; break;
            case 'a': a = { value,value }; break;
            case 's': s = { value,value }; break;
            }
        }
    }

    day19_part(const day19_part& other)
    {
        x = other.x;
        m = other.m;
        a = other.a;
        s = other.s;
    }

    day19_part(int _a, int _m, int _s, int _x)
    {
        x = { _x,_x };
        m = { _m,_m };
        a = { _a,_a };
        s = { _s,_s };
    }

    pair<int, int> getValues(char c)
    {
        switch (c)
        {
        case 'x': return x; break;
        case 'm': return m; break;
        case 'a': return a; break;
        case 's': return s; break;
        }
    }

    void setValue(char c, pair<int, int> value)
    {
        switch (c)
        {
        case 'x': x = value; break;
        case 'm': m = value; break;
        case 'a': a = value; break;
        case 's': s = value; break;
        }
    }
};

struct day19_condition
{
public:
    char letter = 0;
    char action = 0;
    long long number = 0;
    string result = "";
    bool onlyResult = false;

    day19_condition(const string& s)//s>2770:qs
    {
        auto posSymbol = s.find(':');
        if (posSymbol != string::npos)
        {
            //condition with condition
            letter = s[0];
            action = s[1];

            string number_s = split(s.substr(2), ":")[0];
            number = atoll(number_s.c_str());
            result = s.substr(posSymbol + 1);
            onlyResult = false;
        }
        else
        {
            result = s;
            onlyResult = true;
        }
    }

};

using day19_nodeElement = pair<string, day19_part>;

struct day19_instruction
{
public:
    string key;
    vector<day19_condition> conditions;
    string param_str;

    day19_instruction(const string& s) // qqz{s>2770:qs,m<1801:hdj,R}
    {
        param_str = s;
        auto positionSymbol = s.find('{');
        key = s.substr(0, positionSymbol);

        auto allConditions_str = s.substr(positionSymbol + 1, s.size() - positionSymbol - 2);

        auto conditions_str = split(allConditions_str, ",");

        for (auto c : conditions_str)
        {
            day19_condition cond(c);
            conditions.push_back(cond);
        }
    }

    vector<day19_nodeElement> evaluate(const day19_part& node)
    {
        vector<day19_nodeElement> toReturn;

        day19_part currentNode = node;

        for (int i = 0; i < conditions.size(); ++i)
        {
            auto condition = conditions[i];

            if (condition.onlyResult)
            {
                toReturn.push_back({ condition.result, currentNode });
            }
            else
            {
                char letter = condition.letter;
                char action = condition.action;
                int number = condition.number;

                auto values = currentNode.getValues(letter);

                if (action == '<')
                {
                   //CurrentNode: [3000, 4000]; < 3500 => add[3000, 3500], currentNode: [3500, 4000] 
                   //CurrentNode: [2000, 3000]; < 1000 => currentNode[2000, 3000]
                   //CurrentNode: [2000, 3000]; < 3500 => add[2000, 3000], currentNode: => stop execution

                    if (values.first < number && number < values.second)
                    {
                        day19_part n = currentNode;
                        n.setValue(letter, {values.first, number - 1});
                        toReturn.push_back({ condition.result, n });
                        currentNode.setValue(letter, { number, values.second });
                        continue;
                    }

                    if (number < values.first)
                    {
                        //do nothig
                        continue;
                    }

                    if (values.second < number)
                    {
                        toReturn.push_back({ condition.result, currentNode });
                        break;
                    }

                }
                if (action == '>')
                {
                    //CurrentNode: [3000, 4000]; > 3500 => add[3500, 4000], currentNode: [3000, 3500] 
                    //CurrentNode: [2000, 3000]; > 3500 => currentNode[2000, 3000]
                    //CurrentNode: [3800, 4000]; > 3500 => add[3800, 4000], currentNode: => stop execution

                    if (values.first < number && number < values.second)
                    {
                        day19_part n = currentNode;
                        n.setValue(letter, { number +1, values.second });
                        toReturn.push_back({ condition.result, n });
                        currentNode.setValue(letter, { values.first, number });
                        continue;
                    }

                    if (number > values.second)
                    {
                        //do nothing;
                        continue;
                    }

                    if (values.first > number)
                    {
                        toReturn.push_back({ condition.result, currentNode });
                        break;
                    }
                }
            }
        }
        return toReturn;
    }
};

void day19_buildData(const std::vector<string>& lines, map<string, day19_instruction>& instructions, vector<day19_part>& parts)
{
    int index = 0;
    while (lines[index].size() > 0)
    {
        day19_instruction ins(lines[index]);
        instructions.insert({ ins.key, ins });
        ++index;
    }
    ++index;

    while (index < lines.size())
    {
        day19_part p(lines[index]);
        parts.push_back(p);
        ++index;
    }
}

void day19_analyzePart(const map<string, day19_instruction>& instructions, const day19_part& part, vector<day19_part>& accepted, vector<day19_part>& rejected)
{
    vector<day19_nodeElement> listToAnalyze;
    listToAnalyze.push_back({ "in", part });

    while (listToAnalyze.size() != 0)
    {
        auto node = listToAnalyze[0];
        listToAnalyze.erase(listToAnalyze.begin());

        auto instructionId = node.first;
        auto p = node.second;

        if (instructionId == "R")
        {
            rejected.push_back(p);
            continue;
        }

        if (instructionId == "A")
        {
            accepted.push_back(p);
            continue;
        }

        auto instruction = instructions.at(instructionId);

        auto newNodes = instruction.evaluate(p);

        listToAnalyze.insert(listToAnalyze.end(), newNodes.begin(), newNodes.end());
    }
}


void day19_analyze(const map<string, day19_instruction>& instructions, const vector<day19_part>& parts, vector<day19_part>& accepted, vector<day19_part>& rejected)
{
    for (int i = 0; i < parts.size(); ++i)
    {
        day19_analyzePart(instructions, parts[i], accepted, rejected);
    }
}

void day19_partA(vector<day19_part>& accepted)
{
    long long result = 0;

    for (auto ac : accepted)
    {
        long long value = (ac.a.first + ac.m.first + ac.s.first + ac.x.first);
        result += value;
    }

    std::cout << "day 19_a => " << result << "\n";
}

void day19_partB(vector<day19_part>& accepted)
{
    double result = 0;

    for (auto ac : accepted)
    {
        double a = (ac.a.second - ac.a.first + 1);
        double m = (ac.m.second - ac.m.first + 1);
        double s = (ac.s.second - ac.s.first + 1);
        double x = (ac.x.second - ac.x.first + 1);

        double value = a * m * s * x;
        result += value;
    }
    std::cout << "day 19_b => " << std::setprecision(16) << result << "\n";
}

void day19()
{
    auto fileTxt = ReadFile("./input/day19.txt");
    map<string, day19_instruction> instructions;
    vector<day19_part> parts_a;

    day19_buildData(fileTxt, instructions, parts_a);

    
    vector<day19_part> accepted_a;
    vector<day19_part> rejected_a;

    day19_analyze(instructions, parts_a, accepted_a, rejected_a);
    day19_partA(accepted_a);

    vector<day19_part> accepted_b;
    vector<day19_part> rejected_b;
    vector<day19_part> parts_b;

    day19_part b(4000);
    parts_b.push_back(b);

    day19_analyze(instructions, parts_b, accepted_b, rejected_b);
    day19_partB(accepted_b);
}

enum class day20_type {FLIP, CONJUNCTION, NONE, BROADCASTER};
enum class day20_pulse {HIGH, LOW};

struct day20_signal
{
public:
    string origin;
    string destiny;
    day20_pulse pulse;

    day20_signal(string o, string d, day20_pulse p) : origin(o), destiny(d), pulse(p) {}
};

struct day20_node
{
public:
    string label;
    vector<string> sons;
    vector<string> parents;

    day20_pulse currentPulse = day20_pulse::LOW;
    map<string, day20_pulse> lastParentReceivedPulses;
    day20_type type;

    void addSon(string s)
    {
        sons.push_back(s);
    }

    void addParent(string s)
    {
        parents.push_back(s);
        lastParentReceivedPulses.insert({ s, day20_pulse::LOW });
    }

    bool execute(day20_signal currentInput, day20_pulse& output)
    {
        if (type == day20_type::FLIP)
        {
            if (currentInput.pulse == day20_pulse::LOW)
            {
                flipPulse();
                output = currentPulse;
                return true;
            }
        }

        if (type == day20_type::CONJUNCTION)
        {
            lastParentReceivedPulses[currentInput.origin] = currentInput.pulse;
            bool allHigh = true;
            for (auto p : lastParentReceivedPulses)
            {
                if (p.second == day20_pulse::LOW)
                {
                    allHigh = false;
                    break;
                }
            }
            if (allHigh)
            {
                output = day20_pulse::LOW;
            }
            else
            {
                output = day20_pulse::HIGH;
            }

            return true;
        }

        if (type == day20_type::BROADCASTER)
        {
            output = day20_pulse::LOW;
            return true;
        }

        return false;
    }

    day20_pulse GetActualValue()
    {
        if (type == day20_type::FLIP)
        {
            return currentPulse;
        }
        if (type == day20_type::CONJUNCTION)
        {
            bool allHigh = true;
            for (auto p : lastParentReceivedPulses)
            {
                if (p.second == day20_pulse::LOW)
                {
                    allHigh = false;
                    break;
                }
            }
            if (allHigh)
            {
                return day20_pulse::LOW;
            }
            else
            {
                return day20_pulse::HIGH;
            }
        }
        return day20_pulse::LOW;
    }

    void setType(char c)
    {
        switch (c)
        {
        case 'b': type = day20_type::BROADCASTER; break;
        case '%': type = day20_type::FLIP; break;
        case '&': type = day20_type::CONJUNCTION; break;
        }
    }


private:
    void flipPulse()
    {
        if (currentPulse == day20_pulse::HIGH)
        {
            currentPulse = day20_pulse::LOW;
        }
        else
        {
            if (currentPulse == day20_pulse::LOW)
            {
                currentPulse = day20_pulse::HIGH;
            }
        }
    }
};

day20_node* day20_getOrBuildNode(map<string, day20_node*>& nodes, string key)
{
    if (nodes.find(key) == nodes.end())
    {
        day20_node* n = new day20_node();
        nodes.insert({ key, n });
    }
    return nodes[key];
}

void day20_parseInput(const std::vector<string> file, map<string, day20_node*>& nodes)
{
    for (auto l : file)
    {
        auto split_str = split(l, "->");

        string key = split_str[0];
        
        trim(key);

        char type = key[0];
        if (key != "broadcaster")
        {
            key = key.substr(1);
        }
        
        auto node = day20_getOrBuildNode(nodes, key);

        node->setType(type);//this builds the node if not exists
        node->label = key;

        auto sons_str = split(split_str[1], ",");

        for (auto son_str : sons_str)
        {
            trim(son_str);
            day20_getOrBuildNode(nodes, son_str)->addParent(key);
            node->addSon(son_str);
        }
    }
}

void day20_analyzePress(map<string, day20_node*>& nodes, long long& lowPulses, long long& highPulses )
{
    vector<day20_signal> signalsToAnalyze;

    day20_signal initialSignal("Button", "broadcaster", day20_pulse::LOW);
    signalsToAnalyze.push_back(initialSignal);

    while (signalsToAnalyze.size() != 0)
    {
        day20_signal signal = signalsToAnalyze[0];
        signalsToAnalyze.erase(signalsToAnalyze.begin());

        if (signal.pulse == day20_pulse::LOW )
        {
            ++lowPulses;
        }
        if (signal.pulse == day20_pulse::HIGH)
        {
            ++highPulses;
        }

        day20_pulse output;
        auto node = nodes[signal.destiny];
        if (node->execute(signal, output))
        {
            //add the new value to all sons
            for (auto son_str : node->sons)
            {
                day20_signal newSignal(signal.destiny, son_str, output);
                signalsToAnalyze.push_back(newSignal);
            }
        }
    }
}

void day20_analyzePress_b(map<string, day20_node*>& nodes, map<string, long long>& result, const vector<string>& nodesToAnalyze, long long pulsation)
{
    vector<day20_signal> signalsToAnalyze;

    day20_signal initialSignal("Button", "broadcaster", day20_pulse::LOW);
    signalsToAnalyze.push_back(initialSignal);

    while (signalsToAnalyze.size() != 0)
    {
        day20_signal signal = signalsToAnalyze[0];
        signalsToAnalyze.erase(signalsToAnalyze.begin());

        day20_pulse output;
        auto node = nodes[signal.destiny];
        if (node->execute(signal, output))
        {
            //add the new value to all sons
            for (auto son_str : node->sons)
            {
                day20_signal newSignal(signal.destiny, son_str, output);
                signalsToAnalyze.push_back(newSignal);


                if (std::find(nodesToAnalyze.begin(), nodesToAnalyze.end(), son_str) != nodesToAnalyze.end())
                {
                    if (output == day20_pulse::LOW)
                    {
                        if (result.find(son_str) == result.end())
                        {
                            result.insert({son_str, pulsation });
                        }
                    }
                }

            }
        }
    }
}

long long day20_analyzePulses(map<string, day20_node*>& nodes, int totalPulsations)
{
    long long lowPulses = 0;
    long long highPulses = 0;
    for (int i = 0; i < totalPulsations; ++i)
    {
        day20_analyzePress(nodes, lowPulses, highPulses);
    }

    return lowPulses * highPulses;
}

void day20_partB()
{
    auto fileTxt = ReadFile("./input/day20.txt");

    map<string, day20_node*> nodes;
    day20_parseInput(fileTxt, nodes);

    string finalNode = "rx";

    auto caller = nodes[finalNode]->parents[0];

    auto caller_parents = nodes[caller]->parents;

    long long maxTries = 10000;

    map<string, long long> results;

    for (auto t = 0; t < maxTries; ++t)
    {
        day20_analyzePress_b(nodes, results, caller_parents, t + 1);

        if (results.size() == caller_parents.size())
        {
            break;
        }
    }

    long long result = 1;
    for (auto x : results)
    {
        result *= x.second;
    }

    std::cout << "day20_b => " << result << "\n";
}

void day20_partA()
{
    auto fileTxt = ReadFile("./input/day20.txt");

    map<string, day20_node*> nodes;
    day20_parseInput(fileTxt, nodes);
    auto resultA = day20_analyzePulses(nodes, 1000);

    std::cout << "day20_a => " << resultA <<"\n";
}

void day20()
{
    day20_partA();
    day20_partB();
}

pair<int, int> day21_getStart(const std::vector<std::string> &input)
{
    for (int i = 0; i < input.size(); ++i)
    {
        auto position = input[i].find('S');
        if (position != string::npos)
        {
            return { i, position };
        }
    }
    return { -1,-1 };
}

bool day21_validPosition(const std::vector<std::string>& input, const vector<vector<int>>& distances, int Y, int X)
{
    int width = input[0].size();
    int height = input.size();

    if (Y < 0 || X < 0 || Y >= height || X >= width)
    {
        return false;
    }

    if (distances[Y][X] != -1)
    {
        return false;
    }

    return input[Y][X] == '.';
}

void day21_partA(const std::vector<std::string>& input, pair<int, int> startPosition, int maxDistance)
{
    int width = input[0].size();
    int height = input.size();

    vector<vector<int>> distances(height, vector<int>(width, -1));//not setted

    vector <pair<int,pair<int, int>>> nodesToAnalyze;//{distance, {Y, X}};

    nodesToAnalyze.push_back({ 0,startPosition });

    long long count = 0;

    while (nodesToAnalyze.size() != 0)
    {
        auto node = nodesToAnalyze.front();
        nodesToAnalyze.erase(nodesToAnalyze.begin());

        int distance = node.first;
        auto position = node.second;

        if (distance > maxDistance)
        {
            nodesToAnalyze.clear();
            continue;
        }

        if (distances[position.first][position.second] != -1)
        {
            continue;//we reach the same spot throug 2 ways, but by definition, the other was better
        }

        if (distance % 2 == 0)
        {
            ++count;
        }

        distances[position.first][position.second] = distance;
        //create 4 sons

        //top
        {
            int nextY = position.first - 1;
            int nextX = position.second;
            if (day21_validPosition(input, distances, nextY, nextX))
            {
                nodesToAnalyze.push_back({ distance + 1, {nextY, nextX} });
            }
           
        }

        //bottom
        {
            int nextY = position.first + 1;
            int nextX = position.second;
            if (day21_validPosition(input, distances, nextY, nextX))
            {
                nodesToAnalyze.push_back({ distance + 1, {nextY, nextX} });
            }

        }

        //left
        {
            int nextY = position.first;
            int nextX = position.second -1;
            if (day21_validPosition(input, distances, nextY, nextX))
            {
                nodesToAnalyze.push_back({ distance + 1, {nextY, nextX} });
            }

        }

        //right
        {
            int nextY = position.first;
            int nextX = position.second + 1;
            if (day21_validPosition(input, distances, nextY, nextX))
            {
                nodesToAnalyze.push_back({ distance + 1, {nextY, nextX} });
            }

        }

    }

    std::cout << "day 21_a =>" << count << "\n";
}

void day21_partB(const std::vector<std::string>& input, pair<int, int> startPosition, int maxDistance)
{
    int width = input[0].size();
    int height = input.size();

    vector<vector<int>> distances(height, vector<int>(width, -1));//not setted

    vector <pair<int, pair<int, int>>> nodesToAnalyze;//{distance, {Y, X}};

    nodesToAnalyze.push_back({ 0,startPosition });

    long long countImpar = 0;
    long long countPar = 0;
    long long countOutside = 0;

    while (nodesToAnalyze.size() != 0)
    {
        auto node = nodesToAnalyze.front();
        nodesToAnalyze.erase(nodesToAnalyze.begin());

        int distance = node.first;
        auto position = node.second;

        if (distances[position.first][position.second] != -1)
        {
            continue;//we reach the same spot throug 2 ways, but by definition, the other was better
        }

        if (distance <= width / 2)
        {
            if ((distance % 2) == 1)
            {
                ++countImpar;
            }
            else
            {
                ++countPar;
            }
        }
        else
        {
            ++countOutside;
        }

        distances[position.first][position.second] = distance;
        //create 4 sons

        //top
        {
            int nextY = position.first - 1;
            int nextX = position.second;
            if (day21_validPosition(input, distances, nextY, nextX))
            {
                nodesToAnalyze.push_back({ distance + 1, {nextY, nextX} });
            }

        }

        //bottom
        {
            int nextY = position.first + 1;
            int nextX = position.second;
            if (day21_validPosition(input, distances, nextY, nextX))
            {
                nodesToAnalyze.push_back({ distance + 1, {nextY, nextX} });
            }

        }

        //left
        {
            int nextY = position.first;
            int nextX = position.second - 1;
            if (day21_validPosition(input, distances, nextY, nextX))
            {
                nodesToAnalyze.push_back({ distance + 1, {nextY, nextX} });
            }

        }

        //right
        {
            int nextY = position.first;
            int nextX = position.second + 1;
            if (day21_validPosition(input, distances, nextY, nextX))
            {
                nodesToAnalyze.push_back({ distance + 1, {nextY, nextX} });
            }
        }
    }

    //complete rombos with par elements are: 1 1 9 9 25 25 49 49
    //complete rombos with impar elements are: 0 4 4 16 16 36 36 64 64

    long long n = maxDistance / width;
    
    long long totalPares = 0;
    long long totalImpares = 0;
    
    if (n % 2 == 0)
    {
        totalPares = pow(n, 2);
        totalImpares = pow(n + 1, 2);
    }
    else
    {
        totalImpares = pow(n, 2);
        totalPares = pow(n + 1, 2);
    }
    
    long long totalOutside = (totalPares + totalImpares) / 2;
    
    long long solution = countImpar * totalImpares + countPar * totalPares + countOutside * totalOutside;

    std::cout << "Day 21_b => "<< solution << "\n";

}

void day21()
{
    auto fileTxt = ReadFile("./input/day21.txt");
    auto start = day21_getStart(fileTxt);
    day21_partA(fileTxt, start, 64);
    //explain: https://github.com/DeadlyRedCube/AdventOfCode/blob/main/2023/AOC2023/D21.h
    day21_partB(fileTxt, start, 26501365);
}

struct day22_block
{
public:

    array<int, 3> start;
    array<int, 3> end;
    int id;

    set<int> overBlock;
    set<int> underBlock;

    int minZ;
    int maxZ;

    day22_block(string s, int _id)
    {
        id = _id;

        auto coords = split(s, "~");

        {
            auto start_coords = split(coords[0], ",");
            for (int i = 0; i < start_coords.size(); ++i)
            {
                start[i] = atoi(start_coords[i].c_str());
            }
        }

        {
            auto end_coords = split(coords[1], ",");
            for (int i = 0; i < end_coords.size(); ++i)
            {
                end[i] = atoi(end_coords[i].c_str());
            }
        }

        minZ = min(start[2], end[2]);
        maxZ = max(start[2], end[2]);
    }


    day22_block(const day22_block& other)
    {
        this->id = other.id;
        for (int i = 0; i < start.size(); ++i)
        {
            this->start[i] = other.start[i];
            this->end[i] = other.end[i];
        }
        minZ = min(start[2], end[2]);
        maxZ = max(start[2], end[2]);

        this->overBlock = other.overBlock;
        this->underBlock = other.underBlock;

        // this->overBlock.insert(this->overBlock.begin(), other.overBlock.begin(), other.overBlock.end());
        //this->underBlock.insert(this->underBlock.begin(), other.underBlock.begin(), other.underBlock.end());
    }

    void setMinZ(int value)
    {
        int diff = end[2] - start[2];
        start[2] = value;
        end[2] = start[2] + diff;

        minZ = min(start[2], end[2]);
        maxZ = max(start[2], end[2]);
    }

    bool collides(const day22_block& other)
    {
        //returns collision on XY

        int myMinX = min(start[0], end[0]);
        int myMaxX = max(start[0], end[0]);

        int myMinY = min(start[1], end[1]);
        int myMaxY = max(start[1], end[1]);

        int otherMinX = min(other.start[0], other.end[0]);
        int otherMaxX = max(other.start[0], other.end[0]);

        int otherMinY = min(other.start[1], other.end[1]);
        int otherMaxY = max(other.start[1], other.end[1]);


        if (myMaxX < otherMinX) { return false; }
        if (myMinX > otherMaxX) { return false; }
        if (myMaxY < otherMinY) { return false; }
        if (myMinY > otherMaxY) { return false; }

        return true;
    }

    string getString()
    {
        string toReturn = std::to_string(id) + ",";
        toReturn += std::to_string(start[0]) + ",";
        toReturn += std::to_string(start[1]) + ",";
        toReturn += std::to_string(start[2]) + ",";
        toReturn += std::to_string(end[0]) + ",";
        toReturn += std::to_string(end[1]) + ",";
        toReturn += std::to_string(end[2]);

        return toReturn;
    }

};

void day22_calculateUnderBlock(vector<day22_block>& allBlocks, int index)
{
    auto last = allBlocks.back();
    int elementMinZ = allBlocks[index].minZ;
    for (int i = index - 1; i >= 0; --i)
    {
        int searchZ = allBlocks[i].maxZ;
        if (searchZ + 1 == elementMinZ)
        {
            if (allBlocks[index].collides(allBlocks[i]))
            {
                allBlocks[index].underBlock.insert(i);
                allBlocks[i].overBlock.insert(index);
            }
        }
    }
}

void day22_calculateUnder(vector<day22_block>& allBlocks)
{
    for (int i = 0; i < allBlocks.size(); ++i)
    {
        auto id = allBlocks[i].id;

        day22_calculateUnderBlock(allBlocks, i);
    }
}

void day22_sortBlocks(vector<day22_block>& blocks)
{
    std::sort(blocks.begin(), blocks.end(), [](const day22_block& a, const day22_block& b) {

        if (a.minZ != b.minZ) 
        { 
            return a.minZ < b.minZ; 
        }

        if (a.start[0] != b.start[0]) { return a.start[0] < b.start[0]; }

        return a.start[1] < b.start[1];
        });
}

vector<day22_block> day22_moveDown(const vector<day22_block>& originalBlocks)
{
    vector<day22_block> movedBlocks;

    for (int i = 0; i < originalBlocks.size(); ++i)
    {
        if (originalBlocks[i].minZ == 1)
        {
            movedBlocks.push_back(originalBlocks[i]);//ground blocks
            continue;
        }

        int id = originalBlocks[i].id;

        int maxZ = -1;
        int maxIndex = -1;

        for (int j = movedBlocks.size()-1; j >= 0; --j)
        {
            if (movedBlocks[j].collides(originalBlocks[i]))
            {
                if (maxZ < movedBlocks[j].maxZ + 1)
                {
                    maxZ = movedBlocks[j].maxZ + 1;
                    maxIndex = j;
                }
            }
        }

        if (maxIndex ==-1)
        {
            day22_block newBlock = originalBlocks[i];
            newBlock.setMinZ(1);
            movedBlocks.push_back(newBlock);
        }
        else
        {
            day22_block newBlock = originalBlocks[i];
            newBlock.setMinZ(movedBlocks[maxIndex].maxZ + 1);
            movedBlocks.push_back(newBlock);
        }

        day22_sortBlocks(movedBlocks);

    }
    return movedBlocks;
}

int day22_partB(const vector<day22_block>& blocks, int start)
{
    std::vector<int> supports(blocks.size(), 0);

    for (int i = 0; i < blocks.size(); ++i)
    {
        supports[i] = blocks[i].underBlock.size();
    }

    vector<int> toVisit;
    toVisit.push_back(start);

    int count = 0;

    while (toVisit.size() != 0)
    {
        int current = toVisit.front();
        toVisit.erase(toVisit.begin());

        if (supports[current] == 0 && current != start)
        {
            ++count;
        }

        auto&& b = blocks[current];

        for (auto over : b.overBlock)
        {
            supports[over]--;

            if (supports[over] == 0)
            {
                toVisit.push_back(over);
            }
        }
    }

    return count;
}

void day22()
{
    auto fileTxt = ReadFile("./input/day22.txt");

    vector<day22_block> allBlocks;

    for (int i = 0; i < fileTxt.size(); ++i)
    {
        day22_block b(fileTxt[i], i);
        allBlocks.push_back(b);
    }

    day22_sortBlocks(allBlocks);

    auto moved = day22_moveDown(allBlocks);

    day22_calculateUnder(moved);


    vector<int> validIndexOnMoved;
    vector<int> NotvalidIndexOnMoved;

    for (int index = 0; index < moved.size(); ++index)
    {
        day22_block block = moved[index];

        auto overBlock = block.overBlock;

        bool allOk = true;
        for (auto oB : overBlock)
        {
            if (moved[oB].underBlock.size() <= 1)
            {
                allOk = false;
                break;
            }
        }
        if (allOk)
        {
            validIndexOnMoved.push_back(index);
        }
        else
        {
            NotvalidIndexOnMoved.push_back(index);
        }
    }
    std::cout << "day22_a =>" << validIndexOnMoved.size() << "\n";

    long long partB = 0;

    for (auto&& notValidIndex : NotvalidIndexOnMoved)
    {
        partB += day22_partB(moved, notValidIndex);
    }

    std::cout << "day 22_b =>" << partB << "\n";
}


struct day23_node
{
public:
    int x = -1;
    int y = -1;

    int prevX = -1;
    int prevY = -1;

    int cost = 0;

    day23_node(int _x, int _y) :x(_x), y(_y) {}
    day23_node(int _x, int _y, int _prevX, int _prevY, int _cost) :x(_x), y(_y), prevX(_prevX), prevY(_prevY), cost(_cost) {}
};

bool day23_validNode(pair<int, int> position, int width, int height)
{
    if (position.second < 0) { return false; }
    if (position.second >= width) { return false; }
    if (position.first < 0) { return false; }
    if (position.first >= height) { return false; }
    return true;
}

bool day23_validNode(const day23_node& originalNode, const day23_node& newNode, int width, int height, const std::vector<std::string>& fileTxt)
{
    if (!day23_validNode({newNode.y, newNode.x}, width, height)) { return false; }

    if (originalNode.prevX == newNode.x && originalNode.prevY == newNode.y) { return false; }//turn back

    if (fileTxt[newNode.y][newNode.x] == '#') { return false; }
    return true;
}

const std::vector<pair<int, int>> day23_getMovements(char position)
{
    if (position == '.') { return { {1,0}, {-1,0}, {0,1}, {0,-1} }; }
    if (position == '>') { return { {1,0} }; }
    if (position == '<') { return { {-1,0} }; }
    if (position == 'v') { return { {0,1} }; }
    if (position == '^') { return { {0,-1} }; }
}

void day23_a()
{
    auto fileTxt = ReadFile("./input/day23.txt");

    int width = fileTxt[0].size();
    int height = fileTxt.size();

    int finalPositionX = width - 2;
    int finalPositionY = height - 1;

    long long worst = -1;

    std::vector<day23_node> nodesToInvestigate;

    day23_node start(1, 0);
    nodesToInvestigate.push_back(start);

    while (nodesToInvestigate.size() != 0)
    {
        auto node = nodesToInvestigate.front();
        nodesToInvestigate.erase(nodesToInvestigate.begin());

        //check if we reached end position
        if (node.x == finalPositionX && node.y == finalPositionY)
        {
            if (worst < node.cost)
            {
                worst = node.cost;
            }

            continue;
        }

        //get neightbours
        auto&& movements = day23_getMovements(fileTxt[node.y][node.x]);

        for (auto&& m : movements)
        {
            day23_node newNode(node.x + m.first, node.y + m.second, node.x, node.y, node.cost + 1);

            if (day23_validNode(node, newNode, width, height, fileTxt))
            {
                nodesToInvestigate.push_back(newNode);
            }
        }
    }

    std::cout << "day23_a => " << worst << "\n";
}

bool day23_validPosition(const pair<int, int> newPosition, const vector<string>& fileTxt)
{
    int width = fileTxt[0].size();
    int height = fileTxt.size();

    if (newPosition.first < 0) { return false; }
    if (newPosition.first >= height) { return false; }
    if (newPosition.second < 0) { return false; }
    if (newPosition.second >= width) { return false; }


    if (fileTxt[newPosition.first][newPosition.second] == '#') { return false; }
    return true;
}

struct day23_node_graph
{
public:
    int id;
    pair<int, int> intersection;
    vector<pair<int, day23_node_graph*>> adjacents;

    day23_node_graph(int _id) :id(_id) {  };

    void addAdjacent(int cost, day23_node_graph* n)
    {
        for (int i = 0; i < adjacents.size(); ++i)
        {
            if (adjacents[i].second == n)
            {
                return;
            }
        }

        adjacents.push_back({ cost, n });
    }
};

struct day23_graph
{
public:

    vector<day23_node_graph*> nodes;

    day23_node_graph* nodeByIndex(int index)
    {
        for (int i = 0; i < nodes.size(); ++i)
        {
            if (nodes[i]->id == index)
            {
                return nodes[i];
            }
        }
        return nullptr;
    }

    day23_node_graph* getNode(pair<int, int> instersection)
    {
        for (int i = 0; i < nodes.size(); ++i)
        {
            if (nodes[i]->intersection == instersection)
            {
                return nodes[i];
            }
        }
        auto node = addNode();
        node->intersection = instersection;
        return node;
    }

    bool hasNode(pair<int, int> instersection)
    {
        for (int i = 0; i < nodes.size(); ++i)
        {
            if (nodes[i]->intersection == instersection)
            {
                return true;
            }
        }
        return false;
    }

private:
    day23_node_graph* addNode()
    {
        day23_node_graph* n = new day23_node_graph(nodes.size());
        nodes.push_back(n);
        return n;
    }
};

void day23_b_getNodeFromPosition(const pair<int, int>& start, pair<int,int> lastPosition, const std::vector<string>& fileTxt, day23_graph& currentGraph, int width, int height, day23_node_graph* currentNode)
{
    int count = 1;
    pair<int, int> currentPosition = start;

    while (true)
    {
        auto&& movements = day23_getMovements('.');

        std::vector<pair<int, int>> nextValues;

        for (auto m : movements)
        {
            pair<int, int> newNode = { currentPosition.first + m.first, currentPosition.second + m.second };
            if (day23_validNode(newNode, width, height))
            {
                if (fileTxt[newNode.first][newNode.second] == '#')
                {
                    continue;
                }

                if (newNode == lastPosition)
                {
                    continue;
                }

                nextValues.push_back(newNode);
            }
        }

        if (nextValues.size() == 0)
        {
            auto intersectionNode = currentGraph.getNode(currentPosition);
            currentNode->addAdjacent(count, intersectionNode);
            intersectionNode->addAdjacent(count, currentNode);
            return;
        }

        if (nextValues.size() == 1)
        {
            ++count;
            lastPosition = currentPosition;
            currentPosition = nextValues[0];
            continue;
        }
        if (nextValues.size() > 1)
        {
            bool hasNode = currentGraph.hasNode(currentPosition);

            auto intersectionNode = currentGraph.getNode(currentPosition);

            currentNode->addAdjacent(count, intersectionNode);
            intersectionNode->addAdjacent(count, currentNode);

            if (hasNode)
            {
                return;
            }

            for (int i = 0; i < nextValues.size(); ++i)
            {
                day23_b_getNodeFromPosition(nextValues[i], currentPosition, fileTxt, currentGraph, width, height, intersectionNode);
                
            }
        }
    }
}

void day23_getWorstRoute(day23_graph& graph, day23_node_graph* currentPosition, const day23_node_graph* endPosition, std::vector<bool> visited, int currentCost, int& worstCost)
{
    if (currentPosition == endPosition)
    {
        if (currentCost > worstCost)
        {
            worstCost = currentCost;
        }
        return;
    }

    visited[currentPosition->id] = true;

    for (int i = 0; i < currentPosition->adjacents.size(); ++i)
    {
        int newCost = currentPosition->adjacents[i].first;
        auto neightbour = currentPosition->adjacents[i].second;

        if (visited[neightbour->id])
        {
            continue;
        }
        day23_getWorstRoute(graph, neightbour, endPosition, visited, currentCost + newCost, worstCost);
    }
}

void day23_b()
{
    auto fileTxt = ReadFile("./input/day23.txt");
    int width = fileTxt[0].size();
    int height = fileTxt.size();

    day23_graph graph;

    auto startNode = graph.getNode({ 0,1 });

    day23_b_getNodeFromPosition({ 0, 1 }, { -1,-1 }, fileTxt, graph, width, height, startNode);

    
    auto endNode = graph.getNode({ height - 1, width - 2 });

    std::vector<bool> visited(graph.nodes.size(), false);
    int worst = -1;

    day23_getWorstRoute(graph, startNode, endNode, visited, 0, worst);

    std::cout << "day23_b => " << worst-1 << "\n";
}

void day23()
{
    day23_a();
    day23_b();
}

struct day24_point
{
    array<double, 3> start;
    array<double, 3> direction;

    day24_point(const std::string& s)
    {
        auto division = split(s, "@");

        auto start_str = split(division[0], ",");

        for (int i = 0; i < 3; ++i)
        {
            start[i] = stod(start_str[i].c_str());
        }

        auto direction_str = split(division[1], ",");
        for (int i = 0; i < 3; ++i)
        {
            direction[i] = stod(direction_str[i].c_str());
        }
    }

    bool validPoint(pair<double, double> point) const
    {
        if (direction[0] > 0 && point.first < start[0]) { return false; }
        if (direction[0] < 0 && point.first > start[0]) { return false; }

        if (direction[1] > 0 && point.second < start[1]) { return false; }
        if (direction[1] < 0 && point.second > start[1]) { return false; }

        return true;
    }

    array<double, 3> moveParticle(double x, double y, double Z)
    {
        array<double, 3> toReturn;
        toReturn[0] = start[0] + direction[0] + x;
        toReturn[1] = start[1] + direction[1] + x;
        toReturn[2] = start[2] + direction[2] + x;

        return toReturn;
    }
};

bool day24_getCollision(day24_point& P1, day24_point& P2, pair<double, double>& solution)
{
    double C = P1.direction[1] / P1.direction[0];
    double D = P2.direction[1] / P2.direction[0];

    double minus = C - D;
    if (minus == 0) { return false; }//paralel

    double SolX = (P2.start[1] - D*P2.start[0] - P1.start[1] + C * P1.start[0]) / minus;
    double SolY = P1.start[1] + C * (SolX - P1.start[0]);

    solution = { SolX, SolY };
    return true;
}

bool day24_inArea(const std::pair<double, double>& solution, const std::pair<double, double>& maxArea)
{
    if (solution.first < maxArea.first) { return false; }
    if (solution.first > maxArea.second) { return false; } 
    if (solution.second < maxArea.first) { return false; }
    if (solution.second > maxArea.second) { return false; }
    return true;
}

void day24_a(vector<day24_point>& points, pair<double, double> maxArea)
{
    long long count = 0;

    for (int i = 0; i < points.size(); ++i)
    {
        for (int j = i + 1; j < points.size(); ++j)
        {
            pair<double, double> solution;
            if (day24_getCollision(points[i], points[j], solution))
            {
                if (points[i].validPoint(solution) && points[j].validPoint(solution))
                {
                    if (!day24_inArea(solution, maxArea))
                    { 
                        continue; 
                    }

                    ++count;
                }
            }
        }
    }

    std::cout << "day24_a =>" << count << "\n";

}

#define ALL(x) (x).begin(),(x).end()
#define ALLc(x) (x).cbegin(),(x).cend()

using i64 = long long;
template<typename T>
struct Coord3D
{
    constexpr Coord3D(T X = 0, T Y = 0, T Z = 0) : x(X), y(Y), z(Z) {}
    constexpr Coord3D operator + (const Coord3D& p) const { return Coord3D(x + p.x, y + p.y, z + p.z); }
    constexpr Coord3D operator - (const Coord3D& p) { return Coord3D(x - p.x, y - p.y, z - p.z); };
    constexpr Coord3D operator * (T scalar) const { return Coord3D(x * scalar, y * scalar, z * scalar); }
    T x, y, z;
};

using Point3D = Coord3D<i64>;
using PosVel = std::array<i64, 6>;

struct VelSort {
    bool operator()(const PosVel& a, const PosVel& b) const {
        if (a[SortIndex] < b[SortIndex]) return true;
        if (b[SortIndex] < a[SortIndex]) return false;
        return a < b;
    }
    static int SortIndex;
};
int VelSort::SortIndex = 0;

//https://github.com/FCayouette/Advent-of-Code-2023/blob/main/AoC23Day24.cpp
void day24_online(std::vector <string> lines)
{
    i64 part1 = 0;
    std::string line;
    std::vector<Point3D> positions, velocities;
    std::vector<PosVel> dataPoints;
   for (auto line : lines)
    {
        Point3D p, v;
        sscanf_s(line.c_str(), "%lld, %lld, %lld @ %lld, %lld, %lld", &p.x, &p.y, &p.z, &v.x, &v.y, &v.z);

        positions.push_back(p);
        velocities.push_back(v);
        dataPoints.push_back({ p.x, p.y, p.z, v.x, v.y, v.z });
    }

    std::array<i64, 3> hailStoneSpeed = { -3,1,2 };
    if (positions.size() > 10)
    {
        for (int axis = 0; axis < 3; ++axis)
        {
            VelSort::SortIndex = 3 + axis;
            std::sort(ALL(dataPoints), VelSort());

            std::vector<std::pair<i64, i64>> constraints;
            for (int i = 1; i < dataPoints.size(); ++i)
                if (dataPoints[i - 1][VelSort::SortIndex] == dataPoints[i][VelSort::SortIndex])
                    constraints.push_back({ dataPoints[i][VelSort::SortIndex], dataPoints[i][VelSort::SortIndex - 3] - dataPoints[i - 1][VelSort::SortIndex - 3] });

            int i = 0;
            while (true)
            {
                int x = (i + 1) / 2 * (i % 2 == 0 ? 1 : -1);

                if(std::all_of(ALLc(constraints), [x](const std::pair<i64, i64>& p) { return (x - p.first) != 0 && p.second % (x - p.first) == 0; }))
                {
                    hailStoneSpeed[axis] = x;
                    break;
                }
                ++i;
            }
        }
    }

    // intersect first 2 in hailstone frame of reference
    i64 a = hailStoneSpeed[0] - velocities[0].x;
    i64    b = hailStoneSpeed[0] - velocities[1].x;
    i64 c = hailStoneSpeed[1] - velocities[0].y;
    i64   d = hailStoneSpeed[1] - velocities[1].y;
    i64 x = (b * (positions[1].y - positions[0].y) - (positions[1].x - positions[0].x) * d) / (a * d - b * c);

    Point3D origin = positions[0] + (velocities[0] - Point3D(hailStoneSpeed[0], hailStoneSpeed[1], hailStoneSpeed[2])) * x;

    std::cout << "day24_2 =>" << origin.x + origin.y + origin.z << "\n";
}

void day24()
{
    auto fileTxt = ReadFile("./input/day24.txt");

    vector<day24_point> points;

    for (auto s : fileTxt)
    {
        day24_point p(s);
        points.push_back(p);
    }

    day24_a(points, { 200000000000000, 400000000000000 });
    day24_online(fileTxt);
}

void day25_buildGraph(const std::vector<string>& fileInput, vector<vector<int>>& adjacent)
{
    map<string, int> keys_ids;

    for (auto x : fileInput)
    {
        auto split_key = split(x, ":");

        string key_str = trim_copy(split_key[0]);

        if (keys_ids.find(key_str) == keys_ids.end())
        {
            if (key_str.size() != 0)
            {
                keys_ids.insert({ key_str, keys_ids.size() });
            }
        }

        string all_values_str = trim_copy(split_key[1]);

        auto all_values = split(all_values_str, " ");
        for (auto x : all_values)
        {
            string x_str = trim_copy(x);
            if (keys_ids.find(x_str) == keys_ids.end())
            {
                if (x_str.size() != 0)
                {
                    keys_ids.insert({ x_str, keys_ids.size() });
                }
            }
        }
    }

    for (int i = 0; i < keys_ids.size(); ++i)
    {
        vector<int> newValue(keys_ids.size(), 0);
        adjacent.push_back(newValue);
    }

    for (auto x : fileInput)
    {
        auto split_key = split(x, ":");

        string all_values_str = trim_copy(split_key[1]);
        auto all_values = split(all_values_str, " ");

        string key_str = trim_copy(split_key[0]);
        int key_id = keys_ids[key_str];

        for (auto x : all_values)
        {
            string x_str = trim_copy(x);
            if (x_str.size() != 0)
            {
                int x_id = keys_ids.at(x_str);

                adjacent[key_id][x_id] = 1;
                adjacent[x_id][key_id] = 1;
            }
        }
    }
}

// From https://en.wikipedia.org/wiki/Stoer-Wagner_algorithm
pair<int, vector<int>> day25_globalMinCut(vector<vector<int>> mat) {
    pair<int, vector<int>> best = { INT_MAX, {} };
    int n = mat.size();
    vector<vector<int>> co(n);

    for (int i = 0; i < n; i++)
        co[i] = { i };

    for (int ph = 1; ph < n; ph++) {
        vector<int> w = mat[0];
        size_t s = 0, t = 0;
        for (int it = 0; it < n - ph; it++) { // O(V^2) -> O(E log V) with prio. queue
            w[t] = INT_MIN;
            s = t, t = max_element(w.begin(), w.end()) - w.begin();
            for (int i = 0; i < n; i++) w[i] += mat[t][i];
        }
        best = min(best, { w[t] - mat[t][t], co[t] });
        co[s].insert(co[s].end(), co[t].begin(), co[t].end());
        for (int i = 0; i < n; i++) mat[s][i] += mat[t][i];
        for (int i = 0; i < n; i++) mat[i][s] = mat[s][i];
        mat[0][t] = INT_MIN;
    }

    return best;
}



void day25()
{
    auto fileTxt = ReadFile("./input/day25.txt");

    std::vector<std::vector<int>> adjacent;

    day25_buildGraph(fileTxt, adjacent);

    auto sol = day25_globalMinCut(adjacent);
    std::cout << "day25_a =>"  << (sol.second.size()* (adjacent.size()- sol.second.size()));

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
}

// Ejecutar programa: Ctrl + F5 o menú Depurar > Iniciar sin depurar
// Depurar programa: F5 o menú Depurar > Iniciar depuración

// Sugerencias para primeros pasos: 1. Use la ventana del Explorador de soluciones para agregar y administrar archivos
//   2. Use la ventana de Team Explorer para conectar con el control de código fuente
//   3. Use la ventana de salida para ver la salida de compilación y otros mensajes
//   4. Use la ventana Lista de errores para ver los errores
//   5. Vaya a Proyecto > Agregar nuevo elemento para crear nuevos archivos de código, o a Proyecto > Agregar elemento existente para agregar archivos de código existentes al proyecto
//   6. En el futuro, para volver a abrir este proyecto, vaya a Archivo > Abrir > Proyecto y seleccione el archivo .sln
