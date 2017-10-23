#include "ProtocolFile.h"

void ProtocolAverageBest()
{
	std::fstream fs;
	std::stringstream ss;

	for (int generation = 0; generation < GENERATIONS; generation++)
	{
		int bestCandidate = dataGenerations[generation][Candidate_Best];
		int worstCandidate = dataGenerations[generation][Candidate_Worst];

		//float populationFitness = dataGenerations[generation][0];
		float averageFitness = dataGenerations[generation][Fitness_Average];
		float bestFitness = dataCandidates[generation][bestCandidate][Fitness];
		//float worstFitness = dataCandidates[generation][worstCandidate][Fitness];
		float diversity = dataGenerations[generation][Total_Diversity];

		//ss << populationFitness << ";" << averageFitness << ";" << bestFitness << ";" << worstFitness << ";" << diversity << ENDLINE;
		ss << averageFitness << ";" << bestFitness << ";" << diversity << ENDLINE;
		//ss << averageFitness << ";" << bestFitness << ENDLINE;
	}

	fs.open("Tabelle.ods", std::ios::out);
	fs << ss.str();
	fs.close();
}

void ProtocolFolding(int iSeqLength)
{
	std::fstream fs;
	std::stringstream ss;

	int lessX = 0;
	int lessY = 0;

	int currentX = 0;
	int currentY = 0;

	int candidate = veryBestCandidate[0];
	int generation = veryBestCandidate[1] - 1;

	for (int element = 0; element < iSeqLength; element++)
	{
		if (population[generation][candidate][element][X_Value] < lessX)
		{
			lessX = population[generation][candidate][element][X_Value];
		}
		if (population[generation][candidate][element][Y_Value] < lessY)
		{
			lessY = population[generation][candidate][element][Y_Value];
		}
	}

	lessX = lessX * -1 + 2;
	lessY = lessY * -1 + 2;
	
	int currentI;
	std::string currentS;

	// place the elements in the string array
	for (int element = 0; element < iSeqLength; element++)
	{
		currentX = population[generation][candidate][element][X_Value] + lessX;
		currentY = population[generation][candidate][element][Y_Value] + lessY;
		currentI = population[generation][candidate][element][ElementType];
		ss << currentI;
		currentS = ss.str();
		ss.str("");
		grid[currentX][currentY] = currentS;
	}

	//place the lines in the string array
	for (int element = 0; element < iSeqLength - 1; element++)
	{
		currentX = population[generation][candidate][element][X_Value] + lessX;
		currentY = population[generation][candidate][element][Y_Value] + lessY;

		switch (population[generation][candidate][element + 1][CardinalDirection])
		{
		case North:
			currentY--;
			grid[currentX][currentY] = "|";
			break;

		case East:
			currentX++;
			grid[currentX][currentY] = "-";
			break;

		case South:
			currentY++;
			grid[currentX][currentY] = "|";
			break;

		case West:
			currentX--;
			grid[currentX][currentY] = "-";
			break;

		default:
			break;
		}
	}

	ss.str("");
	for (int x = 0; x < SEQ_LENGTH * 2; x++)
	{
		for (int y = 0; y < SEQ_LENGTH * 2; y++)
		{
			ss << WIDTH02 << grid[y][x];
		}
		ss << ENDLINE;
	}

	fs.open("Faltung.txt", std::ios::out);
	fs << ss.str();
	fs.close();
}

void ProtoclFitness()
{
	std::fstream fs;
	std::stringstream ss;
	std::string tmpString;
	const char* generation;

	ss << "Ftiness.ods";
	tmpString = ss.str();
	generation = tmpString.c_str();

	ss.str("");

	for (int candidate = 0; candidate < POPULATION; candidate++)
	{
		//100 generationen
		ss << dataCandidates[0][candidate][Fitness] << ";" << dataCandidates[49][candidate][Fitness] << ";" << dataCandidates[99][candidate][Fitness] << ENDLINE;

		//ss << data[0][candidate][Fitness] << ";" << data[9][candidate][Fitness] << ";" << data[19][candidate][Fitness] << ENDLINE;
		//ss << data[0][candidate][Fitness] << ENDLINE;
		//ss << data[0][candidate][Fitness] << ";";
	}

	fs.open(generation, std::ios::out);
	fs << ss.str();
	fs.close();
}