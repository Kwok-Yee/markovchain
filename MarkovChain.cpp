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

	__declspec(dllexport) int calculateTransition(int size, int ** t, double ** p, int index)
	{
		int c = 0;
		double max = 1;
		random = calculateRandom(0, max);
		
		for (size_t i = 0; i < size; i++)
		{
			random -= p[index][i];
			if (random <= 0)
				return t[index][i];
		}
	}

	__declspec(dllexport) int calculateWeatherState(int size, int ** t, double ** p)
	{		
		if (!validated)
			validateProbabilities(size, p);

		if (currentState == SUNNY)
		{
			transition = calculateTransition(size, t, p, SUNNY);
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
			transition = calculateTransition(size, t, p, RAINING);
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
			transition = calculateTransition(size, t, p, WINDY);
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
			transition = calculateTransition(size, t, p, STORMING);
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

