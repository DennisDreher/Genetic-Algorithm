#include "GeneticAlgorithm.h"

GeneticAlgorithm::GeneticAlgorithm()
{
}

GeneticAlgorithm::GeneticAlgorithm(std::string sequence)
	:iSeqLength(0), /*iGridSize(0), */iGeneration(0), fPopulationFitness(0), chosenCandidates(),
	bestCandidates(), pSequence(0)/*, ppGrid(0)*/
{
	//iSeqLength = sequence.length();
	iSeqLength = SEQ_LENGTH;
	//pointer points on new array with size of the passed sequence
	pSequence = new int[iSeqLength];

	std::string sPosValue = "";
	int iPosValue = 0;

//----------save the sequence in the pSequence array
	//loop through the sequence string
	for (int i = 0; i < iSeqLength; i++)
	{
		//geht element at position i and put it in string
		sPosValue = sequence.at(i);
		//convert the element into an integer
		iPosValue = atoi(sPosValue.c_str());
		//save the element in the array at position i
		pSequence[i] = iPosValue;
	}
//counts the hydrophob elements-----------------------------------------------------------------------
	//int hydrophobCounter = 0;

	//for (int i = 0; i < iSeqLength; i++)
	//{
	//	if (pSequence[i] == HYDROPHOB)
	//		hydrophobCounter++;
	//}
	//COUT << hydrophobCounter;
//----------------------------------------------------------------------------------------------------

//----------set matrix to default
	for (int generation = 0; generation < GENERATIONS; generation++)
	{
		for (int candidate = 0; candidate < POPULATION; candidate++)
		{
			for (int element = 0; element < iSeqLength; element++)
			{
				population[generation][candidate][element][ElementType] = pSequence[element];
				for (int data = 0; data < DATA_ELEMENT; data++)
				{
					population[generation][candidate][element][X_Value] = Zero;
					population[generation][candidate][element][Y_Value] = Zero;
				}
			}
		}
	}

//----------set "dataCandidates" array to default
	for (int generation = 0; generation < GENERATIONS; generation++)
	{
		for (int candidate = 0; candidate < POPULATION; candidate++)
		{
			for (int data = 0; data < DATA_CANDIDATE; data++)
			{
				dataCandidates[generation][candidate][data] = Zero;
			}
		}
	}
}

GeneticAlgorithm::~GeneticAlgorithm()
{
	if (pSequence != nullptr)
	{
		delete[] pSequence;
		pSequence = nullptr;
	}
}

void GeneticAlgorithm::StartGeneticAlgorithm()
{
	InitRadnomGenerator();
	SetDirections();
	SetCardinalDirections();
	SetCoordinates();
	FitnessCalculation();
#ifdef DIVERSITY
	CalcDiversity();
#else
#endif
#ifdef TOURNAMENT
	TournamentSelection();
#else
	Selection();
#endif
	COUT << "Generation: " << iGeneration << ENDLINE;
	iGeneration++;
	
	while (iGeneration < GENERATIONS)
	{
		Evolution();
		SetCardinalDirections();
		SetCoordinates();
		FitnessCalculation();
#ifdef DIVERSITY
		CalcDiversity();
#else
#endif
#ifdef TOURNAMENT
		TournamentSelection();
#else
		Selection();
#endif
		COUT << "Generation: " << iGeneration << ENDLINE;
		iGeneration++;
	}
	PRINT_EMPTY_LINE;
	ProtoclFitness();
	ProtocolAverageBest();
	ShowBestCandidate();
	ProtocolFolding(iSeqLength);
}

void GeneticAlgorithm::SetDirections()
{
	//loop through the population
	for (int candidate = 0; candidate < POPULATION; candidate++)
	{
		//loop through the elements
		for (int element = 0; element < iSeqLength; element++)
		{
			//get a random direction for the element
			population[iGeneration][candidate][element][Direction] = RandomDirection();
		}
	}
}

void GeneticAlgorithm::SetCardinalDirections()
{
	//loop through the population
	for (int candidate = 0; candidate < POPULATION; candidate++)
	{
		//Random Cardinal direction ("view") of the first element
		population[iGeneration][candidate][0][CardinalDirection] = RandomCardinalDirection();

		//loop through the elements
		for (int element = 0; element < iSeqLength - 1; element++)
		{
			//check cardinal direction of current element
			switch (population[iGeneration][candidate][element][CardinalDirection])
			{
			case North:
				//check direction of current element
				switch (population[iGeneration][candidate][element][Direction])
				{
				case Left:
					population[iGeneration][candidate][element + 1][CardinalDirection] = West;
					break;
				case Straight:
					population[iGeneration][candidate][element + 1][CardinalDirection] = North;
					break;
				case Right:
					population[iGeneration][candidate][element + 1][CardinalDirection] = East;
					break;
				default:
					break;
				}
				break;
			case East:
				switch (population[iGeneration][candidate][element][Direction])
				{
				case Left:
					population[iGeneration][candidate][element + 1][CardinalDirection] = North;
					break;
				case Straight:
					population[iGeneration][candidate][element + 1][CardinalDirection] = East;
					break;
				case Right:
					population[iGeneration][candidate][element + 1][CardinalDirection] = South;
					break;
				default:
					break;
				}
				break;
			case South:
				switch (population[iGeneration][candidate][element][Direction])
				{
				case Left:
					population[iGeneration][candidate][element + 1][CardinalDirection] = East;
					break;
				case Straight:
					population[iGeneration][candidate][element + 1][CardinalDirection] = South;
					break;
				case Right:
					population[iGeneration][candidate][element + 1][CardinalDirection] = West;
					break;
				default:
					break;
				}
				break;
			case West:
				switch (population[iGeneration][candidate][element][Direction])
				{
				case Left:
					population[iGeneration][candidate][element + 1][CardinalDirection] = South;
					break;
				case Straight:
					population[iGeneration][candidate][element + 1][CardinalDirection] = West;
					break;
				case Right:
					population[iGeneration][candidate][element + 1][CardinalDirection] = North;
					break;
				default:
					break;
				}
				break;
			default:
				break;
			}
		}
	}
}

void GeneticAlgorithm::SetCoordinates()
{
	for (int candidate = 0; candidate < POPULATION; candidate++)
	{
		int midPoint = 0;

		//place first element at the midpoint
		population[iGeneration][candidate][0][X_Value] = midPoint;
		population[iGeneration][candidate][0][Y_Value] = midPoint;

		for (int element = 1; element < iSeqLength; element++)
		{
			switch (population[iGeneration][candidate][element][CardinalDirection])
			{
			case North:
				//y - 1
				population[iGeneration][candidate][element][X_Value] = population[iGeneration][candidate][element - 1][X_Value];
				population[iGeneration][candidate][element][Y_Value] = population[iGeneration][candidate][element - 1][Y_Value] - COORD_OFFSET;
				break;
			case East:
				//x + 1
				population[iGeneration][candidate][element][X_Value] = population[iGeneration][candidate][element - 1][X_Value] + COORD_OFFSET;
				population[iGeneration][candidate][element][Y_Value] = population[iGeneration][candidate][element - 1][Y_Value];
				break;
			case South:
				//y + 1
				population[iGeneration][candidate][element][X_Value] = population[iGeneration][candidate][element - 1][X_Value];
				population[iGeneration][candidate][element][Y_Value] = population[iGeneration][candidate][element - 1][Y_Value] + COORD_OFFSET;
				break;
			case West:
				//x - 1
				population[iGeneration][candidate][element][X_Value] = population[iGeneration][candidate][element - 1][X_Value] - COORD_OFFSET;
				population[iGeneration][candidate][element][Y_Value] = population[iGeneration][candidate][element - 1][Y_Value];
				break;
			default:
				break;
			}
		}
	}
}


void GeneticAlgorithm::FitnessCalculation()
//this function counts hydrophob pairs on the grid, the number of elements that are actually on the grid
//and evaluates the fitness numbers for each candidate
{
	fPopulationFitness = 0;

	int bestCandidate = 0;
	int worstCandidate = 0;

	//loop through the population
	for (int candidate = 0; candidate < POPULATION; candidate++)
	{
	//----------mark the gridstatus of each element
	//----------count the overlaps of each candidate
		//mark the first element as on the grid
		population[iGeneration][candidate][0][Gridstatus] = On_Grid;
		//init element counter to count the elements on the grid
		float elementCounter = 1;

		for (int element = 1; element < iSeqLength; element++)
		{
			//init another element to compare
			int previousElement = element - 1;
			
			//mark the current element as "On_Grid"
			population[iGeneration][candidate][element][Gridstatus] = On_Grid;
			//increment the element counter
			elementCounter++;
			//this loop compares all previous elements with the current element
			while (previousElement >= 0)
			{
				//if both elements have the same coordinates
				if (population[iGeneration][candidate][element][X_Value] == population[iGeneration][candidate][previousElement][X_Value] &&
					population[iGeneration][candidate][element][Y_Value] == population[iGeneration][candidate][previousElement][Y_Value])
				{
					//mark the previous element as "Off_Grid"
					population[iGeneration][candidate][previousElement][Gridstatus] = Off_Grid;
					//decrement the element counter
					elementCounter--;
				}
				previousElement--;
			}
			
		}
		//save the number of elements on the grid
		dataCandidates[iGeneration][candidate][Elements] = elementCounter;
		//population[iGeneration][candidate][Elements][Miscellaneous] = elementCounter;
		//save the number of overlaps
		dataCandidates[iGeneration][candidate][Overlaps] = iSeqLength - elementCounter;
		//population[iGeneration][candidate][Overlaps][Miscellaneous] = iSeqLength - elementCounter;

	//----------finde hydrophob element pairs on the grid
		int nextElement = 0;
		int horizontal = 0;
		int vertical = 0;
		float pairCounter = 0;
		//loop through the elements and stop before the second last element
		for (int element = 0; element < iSeqLength - 2; element++)
		{
			//if current element is on grid and hydrophob
			if (population[iGeneration][candidate][element][Gridstatus] == On_Grid &&
				population[iGeneration][candidate][element][ElementType] == HYDROPHOB)
			{
				nextElement = element + 2;
				while (nextElement < iSeqLength)
				{
					//if the next element is hydrophob and on the grid
					if (population[iGeneration][candidate][nextElement][Gridstatus] == On_Grid &&
						population[iGeneration][candidate][nextElement][ElementType] == HYDROPHOB)
					{
						//get the horizontal and vertical diffrence of the compared elements
						horizontal = population[iGeneration][candidate][element][X_Value] - population[iGeneration][candidate][nextElement][X_Value];
						vertical = population[iGeneration][candidate][element][Y_Value] - population[iGeneration][candidate][nextElement][Y_Value];
						//abs(zahl) gibt den betrag von zahl zurück
						//if the diffrence value of the horizontal coordinates is 1
						if (abs(horizontal) == COORD_OFFSET && abs(vertical) == 0)
						{
							pairCounter++;
						}
						//if the diffrence value of the vertical coordinates is 1
						else if (abs(vertical) == COORD_OFFSET && abs(horizontal) == 0)
						{
							pairCounter++;
						}
					}
					nextElement++;
				}
			}
		}
		//save the number of hydrophob pairs
		//population[iGeneration][candidate][HydrophobPairs][Miscellaneous] = pairCounter;
		dataCandidates[iGeneration][candidate][HydrophobPairs] = pairCounter;

	//----------fitness calculation
		float pairs = dataCandidates[iGeneration][candidate][HydrophobPairs];
		float overlaps = dataCandidates[iGeneration][candidate][Overlaps];


		//float fitness = iSeqLength * 10 + (3 * pairs) - (10 * overlaps);

		float fitness = (1 + pairs) / ((1 + overlaps) * (1 + overlaps));

		//float fitness = 10000 + (10 * pairs) - (200 * overlaps);


		//for (int i = 0; i < overlaps; i++)
		//{
		//	fitness = fitness / 100 * 90;
		//}

		//float fitness = (1 + pairs) / (1 + overlaps);

		//save the fitness data
		dataCandidates[iGeneration][candidate][Fitness] = fitness;
		//calculate the fitness of the population
		fPopulationFitness += fitness;		

		if (candidate > 0 &&
			dataCandidates[iGeneration][candidate][Fitness] > dataCandidates[iGeneration][bestCandidate][Fitness])
		{
			bestCandidate = candidate;
		}

		if (candidate > 0 &&
			dataCandidates[iGeneration][candidate][Fitness] < dataCandidates[iGeneration][worstCandidate][Fitness])
		{
			worstCandidate = candidate;
		}
	}
	//calculate the average fitness
	fAverageFitness = fPopulationFitness / POPULATION;

	dataGenerations[iGeneration][Fitness_Population] = fPopulationFitness;
	dataGenerations[iGeneration][Fitness_Average] = fAverageFitness;
	dataGenerations[iGeneration][Candidate_Best] = bestCandidate;
	dataGenerations[iGeneration][Candidate_Worst] = worstCandidate;

	bestCandidates[iGeneration][Best_Candidate] = bestCandidate;
	bestCandidates[iGeneration][BC_Generation] = iGeneration;
	bestCandidates[iGeneration][BC_Fitness] = dataCandidates[iGeneration][bestCandidate][Fitness];
	bestCandidates[iGeneration][BC_Pairs] = dataCandidates[iGeneration][bestCandidate][HydrophobPairs];
	bestCandidates[iGeneration][BC_Overlaps] = dataCandidates[iGeneration][bestCandidate][Overlaps];
}



void GeneticAlgorithm::Selection()
{
//----------gives you a float number from 0.1 - 100.0
	//choose numbers
	float randomNumbers[POPULATION];
	for (int child = 0; child < POPULATION; child++)
	{
		float first = rand() % 100;
		float second = rand() % 100;
		second = second / 100;
		float kommazahl = first + second + 0.01;
		randomNumbers[child] = kommazahl;
	}

//----------calculate the fitness in percent for each candidate and create the fitness zones
	//array for the fitness zones
	float fitnessZones[POPULATION];
	//set array to 0
	for (int candidate = 0; candidate < POPULATION; candidate++)
	{
		fitnessZones[candidate] = 0;
	}

	//loop through the population
	for (int candidate = 0; candidate < POPULATION; candidate++)
	{
		//calculate fitness in percent 
		fitnessZones[candidate] = dataCandidates[iGeneration][candidate][Fitness] / fPopulationFitness * 100;

		float test1 = dataCandidates[iGeneration][candidate][Fitness] / fAverageFitness;

		switch (candidate)
		{
		//if it is the first candidate
		case 0:
			//-----nothing happens-----
			break;

		//after the first candidate
		default:
			//add the fitness in percent of the previous candidate to create the fitness zones
			fitnessZones[candidate] += fitnessZones[candidate - 1];
			break;
		}
	}

//----------selects the candidates for the childpopulation by comparing the random numbers with the
//----------fitness zones
	//counter to write the candidates in the cild population matrix
	int childCounter = 0;
	//loop through the population
	for (int candidate = 0; candidate < POPULATION; candidate++)
	{
		//int counter = 0;
		switch (candidate)
		{
		//if it is the first candidate
		case FIRST_CANDIDATE:
			//lopp through the random numbers
			for (int i = 0; i < POPULATION; i++)
			{
				//if the random number selects the first candidate
				if (randomNumbers[i] <= fitnessZones[candidate])
				{
					childCounter++;
					chosenCandidates[i] = candidate;
					//counter++;
				}
			}
			//COUT << "Kandidat " << candidate << ":   " << counter << ENDLINE;
			break;
		case LAST_CANDIDATE:
			//lopp through the random numbers
			for (int i = 0; i < POPULATION; i++)
			{
				//if the random number selects the first candidate
				if (randomNumbers[i] > fitnessZones[candidate - 1])
				{
					childCounter++;
					chosenCandidates[i] = candidate;
					//counter++;
				}
			}
			break;
		default:
			//loop through the random numbers
			for (int i = 0; i < POPULATION; i++)
			{
				//if a number selects the current candidate
				if (randomNumbers[i] <= fitnessZones[candidate] &&
					randomNumbers[i] > fitnessZones[candidate - 1])
				{
					childCounter++;
					chosenCandidates[i] = candidate;
					//counter++;
				}
			}
			break;
		}
	}
}

void GeneticAlgorithm::TournamentSelection()
{
	// loop through the population
	for (int candidate = 0; candidate < POPULATION; candidate++)
	{
		// init candidate to compare with ts_candidate
		int compareCandidate = 0;

		// loop to choose the candidates for the tournamenet
		for (int ts_candidate = 0; ts_candidate < TS_CANDIDATES; ts_candidate++)
		{
			switch (ts_candidate)
			{
			case 0:
				// select first candidate for tournamenet selection (TS)
				ts_Candidates[ts_candidate] = rand() % POPULATION;
				break;

			default:
				// select random candidate for tournamenet selection
				ts_Candidates[ts_candidate] = rand() % POPULATION;
				// set compareCandidate to the previous candidate of current ts_candidate
				compareCandidate = ts_candidate - 1;
				// loop to compare the current ts_candidate with all previous candidates
				while (compareCandidate >= FIRST_CANDIDATE)
				{
					//if current chosen candidate is selected more than once
					if (ts_Candidates[ts_candidate] == ts_Candidates[compareCandidate])
					{
						// select new random candidate
						ts_Candidates[ts_candidate] = rand() % POPULATION;
						// reset the compare candidate
						compareCandidate = ts_candidate - 1;
					}
					else
					{
						compareCandidate--;
					}
				}
				break;
			}

		}
		// set best candidate to the first of the selected candidates
		int bestCandidate = ts_Candidates[FIRST_CANDIDATE];
		int currentCandidate = 0;

		float fitness_currentCandidate = 0;
		float fitness_bestCandidate = 0;

		// loop through the selected candidates and get the best, start with the second
		// candidate
		for (int candidate = 1; candidate < TS_CANDIDATES; candidate++)
		{
			// set current candidate to the current one of the selected candidates
			currentCandidate = ts_Candidates[candidate];
			// if the fitness of the current candidate is better than the fitness
			// of the current best candidate

			fitness_currentCandidate = dataCandidates[iGeneration][currentCandidate][Fitness];
			fitness_bestCandidate = dataCandidates[iGeneration][bestCandidate][Fitness];

			if (dataCandidates[iGeneration][currentCandidate][Fitness] >=
				dataCandidates[iGeneration][bestCandidate][Fitness])
			{
				// save the current candidate as best candidate
				bestCandidate = currentCandidate;
			}
		}
		// save the best of the selected candidates for the next generation
		chosenCandidates[candidate] = bestCandidate;
	}
	int stop = 1;
}

void GeneticAlgorithm::CalcDiversity()
{
	float diversity = 0;
	int candidateCompare = 0;

	// loop through the population
	for (int candidate = 0; candidate < POPULATION; candidate++)
	{
		int element = 0;
		bool identical = false;

		switch (candidate)
		{
		// in case it is the first candidate
		case FIRST_CANDIDATE:
			// set diversity to 1
			diversity = 1;
			//and save it
			dataCandidates[iGeneration][candidate][Diversity] = diversity;
			break;

		default:
			// the compare candidate starts one before the current candidate
			candidateCompare = candidate - 1;
			// loop backwards through the population
			while (candidateCompare >= 0)
			{
				element = 0;
				// loop through the elements
				while (element < iSeqLength)
				{
					// if the directions of the compared elements are NOT the same
					if (population[iGeneration][candidate][element][Direction] != population[iGeneration][candidateCompare][element][Direction])
					{
						// diversity++;
						// dataCandidates[iGeneration][candidate][Diversity] = diversity;
						break;
					}
					// if both candidates are identical
					if (population[iGeneration][candidate][element][Direction] == population[iGeneration][candidateCompare][element][Direction] &&
						element == iSeqLength - 1)
					{
						identical = true;
						// and save it
						//dataCandidates[iGeneration][candidate][Diversity] = diversity;
						break;
					}
					element++;
				}
				if (identical == true)
				{
					dataCandidates[iGeneration][candidate][Diversity] = diversity;
					break;
				}
				candidateCompare--;
			}
			if (candidateCompare == -1)
			{
				diversity++;
				dataCandidates[iGeneration][candidate][Diversity] = diversity;
			}

			break;
		}
	}
	dataGenerations[iGeneration][Total_Diversity] = diversity;
}



void GeneticAlgorithm::Evolution()
{
	int candidateCounter = 0;
	while (candidateCounter < POPULATION)
	{
		if (POPULATION - candidateCounter < 2)
		{
			DoMutation(candidateCounter);
			candidateCounter++;
			//break;
		}
		else
		{
			Process nextProcess = GetEvolutionProcess();
			switch (nextProcess)
			{
			case Crossover:
				DoCrossover(candidateCounter);
				candidateCounter = candidateCounter + 2;
				break;
			case Mutation:
				DoMutation(candidateCounter);
				candidateCounter++;
				break;
			case NoEvolution:
				NoEvolutionProcess(candidateCounter);
				candidateCounter++;
				break;
			default:
				break;
			}
		}
	}
}

void GeneticAlgorithm::ShowBestCandidate()
{
	float bestCandidate = 0;
	int currentGeneration = 0;
	float fitness = 0;
	float pairs = 0;
	float overlaps = 0;

	for (int generation = 0; generation < GENERATIONS; generation++)
	{
		if (bestCandidates[generation][BC_Fitness] >= bestCandidates[currentGeneration][BC_Fitness])
		{
			bestCandidate = bestCandidates[generation][Best_Candidate];
			currentGeneration = generation;
			fitness = bestCandidates[generation][BC_Fitness];
			pairs = bestCandidates[generation][BC_Pairs];
			overlaps = bestCandidates[generation][BC_Overlaps];
		}
	}

	veryBestCandidate[0] = bestCandidate;
	veryBestCandidate[1] = currentGeneration + 1;

	COUT << "Generation: " << currentGeneration << ENDLINE;
	COUT << "Best Candidate: " << bestCandidate << ENDLINE;
	//COUT << "Fitness: " << fitness << ENDLINE;
	COUT << "Pairs: " << pairs << ENDLINE;
	COUT << "Overlaps: " << overlaps << ENDLINE;
}

void GeneticAlgorithm::DoCrossover(int candidateCounter)
{
	//numbers from 1 to 19
	int possibleCutPositions = iSeqLength - 1;
	int cutPosition = (rand() % possibleCutPositions) + 1;

	int candidateA = chosenCandidates[candidateCounter];
	int candidateB = chosenCandidates[candidateCounter + 1];
	int element = 0;

	//write the directions of both candidates in the child population until the cut position
	while (element < cutPosition)
	{
		population[iGeneration][candidateCounter][element][Direction] = population[iGeneration - 1][candidateA][element][Direction];
		population[iGeneration][candidateCounter + 1][element][Direction] = population[iGeneration - 1][candidateB][element][Direction];
		element++;
	}
	while (element < iSeqLength)
	{
		population[iGeneration][candidateCounter][element][Direction] = population[iGeneration - 1][candidateB][element][Direction];
		population[iGeneration][candidateCounter + 1][element][Direction] = population[iGeneration - 1][candidateA][element][Direction];
		element++;
	}
}

void GeneticAlgorithm::DoMutation(int candidateCounter)
{
	//possible positions that can be mutated
	int possiblePositions = iSeqLength - 2;
	//element that will be mutated
	int elementMutation = (rand() % possiblePositions) + 1;

	int currentCandidate = chosenCandidates[candidateCounter];
	int element = 0;

	while (element < elementMutation)
	{
		population[iGeneration][candidateCounter][element][Direction] = population[iGeneration - 1][currentCandidate][element][Direction];
		element++;
	}

	//get the current direction of the element that will be mutated
	int currendDirection = population[iGeneration - 1][currentCandidate][elementMutation][Direction];
	Directions eCurrentDirection = static_cast<Directions>(currendDirection);

	//geht the new direction
	Directions mutatedDirection = MutateDirection(eCurrentDirection);

	//save the new direction
	population[iGeneration][candidateCounter][elementMutation][Direction] = mutatedDirection;
	element++;

	while (element < iSeqLength)
	{
		population[iGeneration][candidateCounter][element][Direction] = population[iGeneration - 1][currentCandidate][element][Direction];
		element++;
	}
}

void GeneticAlgorithm::NoEvolutionProcess(int candidateCounter)
{
	int currentCandidate = chosenCandidates[candidateCounter];
	for (int element = 0; element < iSeqLength; element++)
	{
		population[iGeneration][candidateCounter][element][Direction] = population[iGeneration - 1][currentCandidate][element][Direction];
	}
}

Process GeneticAlgorithm::GetEvolutionProcess()
{
	//gives you a number from 1 to 100
	int process = rand() % 100 + 1;

	if (process <= RATE_MUTATION)
	{
		return Mutation;
	}
	else if (process <= RATE_CROSSOVER)
	{
		return Crossover;
	}
	else
	{
		return NoEvolution;
	}
}

Directions GeneticAlgorithm::RandomDirection()
{
	switch (rand() % 3)
	{
	case 0:
		return Left;
		break;
	case 1:
		return Right;
		break;
	case 2:
		return Straight;
		break;
	default:
		break;
	}
}

inline CardinalDirections GeneticAlgorithm::RandomCardinalDirection()
{
	switch (rand() % 4)
	{
	case 0:
		return North;
		//break;
	case 1:
		return East;
		//break;
	case 2:
		return South;
		//break;
	case 3:
		return West;
		//break;
	default:
		break;
	}
}

void GeneticAlgorithm::InitRadnomGenerator()
{
	//----------random generator for placing the elements randomly
	//get time in seconds
	__time64_t srandInit;
	_time64(&srandInit);

	//initialize the random generator
	srand((unsigned)srandInit);
}

Directions GeneticAlgorithm::MutateDirection(Directions currentDirection)
{
	int mutateDirection = rand() % 2;
	switch (currentDirection)
	{
	case Left:
		switch (mutateDirection)
		{
		case 0:
			return Straight;
			break;
		case 1:
			return Right;
			break;
		default:
			break;
		}
		break;
	case Straight:
		switch (mutateDirection)
		{
		case 0:
			return Left;
			break;
		case 1:
			return Right;
			break;
		default:
			break;
		}
		break;
	case Right:
		switch (mutateDirection)
		{
		case 0:
			return Left;
			break;
		case 1:
			return Straight;
			break;
		default:
			break;
		}
		break;
	default:
		break;
	}
}

int GeneticAlgorithm::GetSeqLength()
{
	return iSeqLength;
}