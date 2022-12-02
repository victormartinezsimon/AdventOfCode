// 2022.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

void day1()
{
	string line;
	std::ifstream file( "./input/day1.txt" );
	
	if ( file.is_open() )
	{
		long long actualValue = 0;
		std::vector<long long> values;
		while ( std::getline ( file, line ) )
		{
			if ( line == "\n" || line.size() == 0 )
			{
				values.push_back(actualValue);
				actualValue = 0;
			}
			else
			{
				long long v = atoll( line.c_str() );
				actualValue += v;
			}

		}
		values.push_back(actualValue);
		std::sort(values.begin(), values.end());//O(nlogn)
		long long v1 = values[values.size() - 1];
		long long v2 = values[values.size() - 2];
		long long v3 = values[values.size() - 3];
		long long result = v1 + v2 + v3;
		std::cout << "Day1 =>" << v1 << "," << result << "\n";
	}
	file.close();
}

long long getScore_day2(char oponent, char mine)
{
	long long toReturn = 0;

	//points for choose
	switch (mine)
	{
	case 'X': toReturn += 1; break;//rock
	case 'Y': toReturn += 2; break;//paper
	case 'Z': toReturn += 3; break;//scissors
	}

	//points for result
	if (mine == 'X')
	{
		//rock
		switch (oponent)
		{
		case 'A': toReturn += 3; break;//rock
		case 'B': toReturn += 0; break;//paper
		case 'C': toReturn += 6; break;//scissors
		}
	}
	else
	{
		if (mine == 'Y')
		{
			//paper
			switch (oponent)
			{
			case 'A': toReturn += 6; break;//rock
			case 'B': toReturn += 3; break;//paper
			case 'C': toReturn += 0; break;//scissors
			}
		}
		else
		{
			//scissors
			switch (oponent)
			{
			case 'A': toReturn += 0; break;//rock
			case 'B': toReturn += 6; break;//paper
			case 'C': toReturn += 3; break;//scissors
			}
		}
	}

	return toReturn;
}
long long getScore_2_day2(char oponent, char mine)
{
	long long toReturn = 0;

	//case 'X';//rock
	//case 'Y';//paper
	//case 'Z';//scissors

	//points for result
	if (mine == 'X')
	{
		//lose
		switch (oponent)
		{
		case 'A': return getScore_day2(oponent, 'Z');//rock
		case 'B': return getScore_day2(oponent, 'X');//paper
		case 'C': return getScore_day2(oponent, 'Y');//scissors
		}
	}
	else
	{
		if (mine == 'Y')
		{
			//draw
			switch (oponent)
			{
			case 'A': return getScore_day2(oponent, 'X');//rock
			case 'B': return getScore_day2(oponent, 'Y');//paper
			case 'C': return getScore_day2(oponent, 'Z');//scissors
			}
		}
		else
		{
			//win
			switch (oponent)
			{
			case 'A': return getScore_day2(oponent, 'Y');//rock
			case 'B': return getScore_day2(oponent, 'Z');//paper
			case 'C': return getScore_day2(oponent, 'X');//scissors
			}
		}
	}

	return 0;
}

void day2()
{
	string line;
	std::ifstream file( "./input/day2.txt" );
	if ( file.is_open() )
	{
		long long score1 = 0;
		long long score2 = 0;
		while ( std::getline ( file, line ) )
		{
			char oponent = line[0];
			char myAction = line[2];
			score1 += getScore_day2(oponent, myAction);
			score2 += getScore_2_day2(oponent, myAction);
		}
		std::cout << "Day2 =>" << score1 << "," << score2 << "\n";
	}
	file.close();
}

int main()
{
	day1();
	day2();
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
