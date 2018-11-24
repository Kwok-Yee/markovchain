// MarkovChain.cpp : Defines the exported functions for the DLL application.
//

#include "MarkovChain.h"
#include "stdafx.h"
#include <assert.h>
#include <stdlib.h>
#include <string>
#include <iostream>

using namespace std;

extern "C" {
#define SUNNY 0
#define RAINING 1
#define WINDY 2
#define STORMING 3

#define STATES 4

	bool validated = false;
	int transition = 0;
	double random = 0;
	int currentState = SUNNY;

	int transitions[STATES][STATES] =
	{
		{00, 01, 02, 03}, // SUNNY, RAINING, WINDY, STORMING
		{11, 10, 12, 13}, // RAINING, SUNNY, WINDY, STORMING
		{22, 20, 21, 23}, // WINDY, SUNNY, RAINING, STORMING
		{33, 30, 31, 32} // WINDY, SUNNY, RAINING, STORMING
	};

	double probabilities[STATES][STATES] =
	{
		{0.5, 0.2, 0.2, 0.1},  // SUNNY, RAINING, WINDY, STORMING
		{0.3, 0.2, 0.3, 0.2}, // RAINING, SUNNY, WINDY, STORMING
		{0.3, 0.2, 0.3, 0.2}, // WINDY, SUNNY, RAINING, STORMING
		{0.4, 0.1, 0.3, 0.2} // STORMING, SUNNY, RAINING, WINDY
	};

	// Validating each row for the probabilities to add up to 1 
	void validateProbabilities(int size, double ** p)
	{
		double total = 0;
		for (size_t i = 0; i < size; i++)
		{
			cout << "Row " << i << ": ";
			for (size_t j = 0; j < size; j++)
			{
				total += p[i][j];
				cout << p[i][j] << " ";
			}
			if (i == 0)
				cout << "== " << total << endl;
			else
				cout << "== " << total - i << endl;
		}
		assert(total - size < 0.000001);
		validated = true;
	};

	__declspec(dllexport) double getRandom() { return random; };

	__declspec(dllexport) double calculateRandom(double min, double max)
	{
		double r = (double)rand() / RAND_MAX;
		return min + r * (max - min);
	}

	__declspec(dllexport) int calculateTransition(int index)
	{
		int c = 0;
		double max = 1;
		random = calculateRandom(0, max);

		if (random < probabilities[index][0])
		{
			c = transitions[index][0];
		}
		else if (random > probabilities[index][0] && random < (probabilities[index][0] + probabilities[index][1]))
		{
			c = transitions[index][1];
		}
		else if (random > (probabilities[index][0] + probabilities[index][1]) && random < (probabilities[index][0] + probabilities[index][1] + probabilities[index][2]))
		{
			c = transitions[index][2];
		}
		else if (random > (probabilities[index][0] + probabilities[index][1] + probabilities[index][2]) && random < max)
		{
			c = transitions[index][3];
		}
		return c;
	}

	__declspec(dllexport) int calculateWeatherState(int size, double ** p)
	{		
		if (!validated)
			validateProbabilities(size, p);

		if (currentState == SUNNY)
		{
			transition = calculateTransition(SUNNY);
			if (transition == 00)
			{
				currentState = SUNNY;
			}
			else if (transition == 01)
			{
				currentState = RAINING;
			}
			else if (transition == 02)
			{
				currentState = WINDY;
			}
			else if (transition == 03)
			{
				currentState = STORMING;
			}
		}
		else if (currentState == RAINING)
		{
			transition = calculateTransition(RAINING);
			if (transition == 11)
			{
				currentState = RAINING;
			}
			else if (transition == 10)
			{
				currentState = SUNNY;
			}
			else if (transition == 12)
			{
				currentState = WINDY;
			}
			else if (transition == 13)
			{
				currentState = STORMING;
			}
		}
		else if (currentState == WINDY)
		{
			transition = calculateTransition(WINDY);
			if (transition == 22)
			{
				currentState = WINDY;
			}
			else if (transition == 20)
			{
				currentState = SUNNY;
			}
			else if (transition == 21)
			{
				currentState = RAINING;
			}
			else if (transition == 23)
			{
				currentState = STORMING;
			}
		}
		else if (currentState == STORMING)
		{
			transition = calculateTransition(STORMING);
			if (transition == 33)
			{
				currentState = STORMING;
			}
			else if (transition == 30)
			{
				currentState = SUNNY;
			}
			else if (transition == 31)
			{
				currentState = RAINING;
			}
			else if (transition == 32)
			{
				currentState = WINDY;
			}
		}
		return currentState;
	}
}

