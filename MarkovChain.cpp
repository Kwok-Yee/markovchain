// MarkovChain.cpp : Defines the exported functions for the DLL application.
//

#include "MarkovChain.h"
#include "stdafx.h"
#include <assert.h>
#include <stdlib.h>
#include <string>

using namespace std;

extern "C" {
#define SUNNY 0
#define RAINING 1
#define WINDY 2
#define STATES 3

	bool validated = false;
	double probability = 1;
	int transition = 0;
	double random = 0;
	int currentState = SUNNY;

	int transitions[STATES][STATES] =
	{
		{00, 01, 02}, // SUNNY, RAINING, WINDY
		{11, 10, 12}, // RAINING, SUNNY, WINDY
		{22, 20, 21} // WINDY, SUNNY, RAINING
	};

	double probabilities[STATES][STATES] =
	{
		{0.5, 0.3, 0.2},  // SUNNY, RAINING, WINDY
		{0.3, 0.2, 0.5}, // RAINING, SUNNY, WINDY
		{0.4, 0.3, 0.3} // WINDY, SUNNY, RAINING
	};

	void validateProbabilities(int states)
	{
		for (size_t i = 0; i < states; i++)
		{
			assert(probabilities[i][0] + probabilities[i][1] + probabilities[i][2] == 1);
			validated = true;
		}
	};

	__declspec(dllexport) double getProbability() { return probability; };

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
		else if (random < (max - probabilities[index][1]) && random > probabilities[index][0])
		{
			c = transitions[index][1];
		}
		else if (random < max && random >(max - probabilities[index][1]))
		{
			c = transitions[index][2];
		}
		return c;
	}

	__declspec(dllexport) int calculateWeatherState()
	{
		if (!validated)
			validateProbabilities(STATES);
		if (currentState == SUNNY)
		{
			transition = calculateTransition(0);
			if (transition == 00)
			{
				probability *= 0.6;
				probabilities[0][0] = probability;
			}
			else if (transition == 01)
			{
				probability *= 0.2;
				probabilities[0][1] = probability;
				currentState = RAINING;
			}
			else if(transition == 02)
			{
				probability *= 0.2;
				probabilities[0][2] = probability;
				currentState = WINDY;
			}
		}
		else if (currentState == RAINING)
		{
			transition = calculateTransition(1);
			if (transition == 11)
			{
				probability *= 0.5;
				probabilities[1][1] = probability;
			}
			else if (transition == 10)
			{
				probability *= 0.2;
				probabilities[1][0] = probability;
				currentState = SUNNY;
			}
			else if(transition == 12)
			{
				probability *= 0.3;
				probabilities[1][2] = probability;
				currentState = WINDY;
			}
		}
		else if (currentState == WINDY)
		{
			transition = calculateTransition(2);
			if (transition == 22)
			{
				probability *= 0.4;
				probabilities[2][2] = probability;
			}
			else if (transition == 20)
			{
				probability *= 0.3;
				probabilities[2][0] = probability;
				currentState = SUNNY;
			}
			else if(transition == 21)
			{
				probability *= 0.3;
				probabilities[2][1] = probability;
				currentState = RAINING;
			}
		}
		return currentState;
	}
}

