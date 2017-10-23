#include <string>
#include <iostream>

#include "Defines.h"
#include "GeneticAlgorithm.h"
#include "ProtocolFile.h"
#include "Output.h"

int population[GENERATIONS][POPULATION][SEQ_LENGTH][DATA_ELEMENT];
float dataCandidates[GENERATIONS][POPULATION][DATA_CANDIDATE];
float dataGenerations[GENERATIONS][DATA_GENERATION];
float veryBestCandidate[2];
std::string grid[SEQ_LENGTH * 2][SEQ_LENGTH * 2];

int main()
{
	std::string sequence = CURRENT_SEQ;
	GeneticAlgorithm ga(sequence);
	ga.StartGeneticAlgorithm();

	COUT << ENDLINE << ENDLINE;
	system("pause");

	Output output;
	output.Initialize(ga.GetSeqLength());
	output.CalculateStart();
	output.Draw();

	COUT << ENDLINE << ENDLINE;
	system("pause");

	return 0;
}