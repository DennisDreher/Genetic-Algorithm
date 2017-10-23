#pragma once

// 0 = hydrophil, "white"
// 1 = hydrophob, "black"

//----------

#define SEQ20	"10100110100101100101"
#define SEQ24	"110010010010010010010011"
#define SEQ25	"0010011000011000011000011"
#define SEQ36	"000110011000001111111001100001100100"
#define SEQ48	"001001100110000011111111110000001100110010011111"
#define SEQ50	"11010101011110100010001000010001000101111010101011"

#define SEQTEST		"110101010111101000100010000100010001011110101010111101010101111010001000100001000100010111101010101111010101011110100010001000010001000101111010101011110101010111101000100010000100010001011110101010111101010101111010001000100001000100010111101010101111010101011110100010001000010001000101111010101011"
#define SEQTESTL	319 - 19

// Testat Sequenz
// Ergebnis Turnier Selektion: 69 Paare, 0 Ueberlappungen
#define SEQ156		"000000000001001111111111100111111111110011111111111001111111111100111111111110011111111111001111111111100111111111110011111111111001111111111100100000000000"
#define SEQ156L		156

#define SEQ20L	20
#define SEQ24L	24
#define SEQ25L	25
#define SEQ36L	36
#define SEQ48L	48
#define SEQ50L	50

#define CURRENT_SEQ		SEQ156
#define SEQ_LENGTH		SEQ156L
#define POPULATION		1000
#define GENERATIONS		350
#define TS_CANDIDATES	3

#define RATE_MUTATION	2
#define RATE_CROSSOVER	75

#define HYDROPHIL 0
#define HYDROPHOB 1

#define FIRST_CANDIDATE		0
#define LAST_CANDIDATE		POPULATION - 1
#define COORD_OFFSET	2

#define DATA_ELEMENT	6
enum ElementData
{
	ElementType,	//hydrophil or hydrophob
	X_Value,		//x-coordinate of element
	Y_Value,		//y-coordinate of element
	CardinalDirection,
	Direction,
	Gridstatus,		//gridstatus of element
};

#define DATA_CANDIDATE	5
enum DataCandidate		//+++++++++geändert+++++++++++
{
	Elements,			//number of elements on the grid
	Overlaps,
	HydrophobPairs,		//number of hydrophob pairs on the grid	
	Fitness,			//total fitness
	Diversity,
};

#define DATA_GENERATION		5
enum DataGeneration
{
	Fitness_Population,
	Fitness_Average,
	Candidate_Best,
	Candidate_Worst,
	Total_Diversity,
};

#define BEST_CANDIDATE_DATA		5
enum BestCandidateData
{
	Best_Candidate,
	BC_Generation,
	BC_Fitness,
	BC_Pairs,
	BC_Overlaps,
};

extern int population[GENERATIONS][POPULATION][SEQ_LENGTH][DATA_ELEMENT];
extern float dataCandidates[GENERATIONS][POPULATION][DATA_CANDIDATE];
extern float dataGenerations[GENERATIONS][DATA_GENERATION];
extern float veryBestCandidate[2];
extern std::string grid[SEQ_LENGTH * 2][SEQ_LENGTH * 2];

//states for the slots of ELEMENT_DATA
enum States
{
	Zero,
	Off_Grid,
	On_Grid,

	//child
	//No,
	//Yes,
};

enum Process
{
	NoEvolution,
	Crossover,
	Mutation,
};

//cardinal directions
enum CardinalDirections
{
	North	= 1,
	East	= 2,
	South	= 3,
	West	= 4,
};

enum Directions
{
	Left		= 1,
	Straight	= 2,
	Right		= 3,
};

//----------------------------------------------------------------------------------------------------
#define COUT				std::cout
#define ENDLINE				std::endl
#define EMPTYLINE			std::endl << std::endl;
#define PRINT_ENDLINE		std::cout << std::endl
#define PRINT_EMPTY_LINE	std::cout << std::endl << std::endl
#define PRINT(msg)		std::cout << msg;

#define WIDTH01		std::setw(1)
#define WIDTH02		std::setw(2)
#define WIDTH04		std::setw(4)
#define WIDTH08		std::setw(8)

/*
Letzter Termin

-bekommen 3-stellige sequenz, muss verarbeitet werden können
-zeitschranke zwischen 1-2 minuten, population und generation
 frei wählbar (optimum finden)
-algorithmus muss selbständing abbrechen und den besten kandidaten finden
-1 beliebige andere selektionsstrategie implementieren und beide verwenden können

kurven
-durchscnittliche fitness
-fitness des besten kandidaten
-genetische diversität für jede jeweilige generation

genetische diversität:
	hamming distanz
*/