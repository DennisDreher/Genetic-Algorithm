#pragma once

#include <iostream>
#include <string>
#include <stdlib.h>		//srand() and rand()
#include "Defines.h"
#include "MyLog.h"
#include "ProtocolFile.h"

#define TOURNAMENT
#define DIVERSITY

class GeneticAlgorithm
{
public:
	GeneticAlgorithm();
	GeneticAlgorithm(std::string sequence);
	virtual ~GeneticAlgorithm();

	void StartGeneticAlgorithm();
	void SetDirections();
	void SetCardinalDirections();
	void SetCoordinates();
	void FitnessCalculation();
	void Selection();
	void TournamentSelection();
	void CalcDiversity();
	void Evolution();
	void ShowBestCandidate();
	Process GetEvolutionProcess();
	void DoCrossover(int candidateCounter);
	void DoMutation(int candidateCounter);
	void NoEvolutionProcess(int candidateCounter);
	Directions RandomDirection();
	inline CardinalDirections RandomCardinalDirection();
	void InitRadnomGenerator();
	Directions MutateDirection(Directions currentDirection);
	int GetSeqLength();

private:
	int iSeqLength;
	int iGeneration;
	float fPopulationFitness;
	float fAverageFitness;
	int chosenCandidates[POPULATION];
	int ts_Candidates[TS_CANDIDATES];
	float bestCandidates[GENERATIONS][BEST_CANDIDATE_DATA];
	int* pSequence;
};