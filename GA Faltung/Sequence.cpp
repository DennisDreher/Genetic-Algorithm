//#include "Sequence.h"
//
//Sequence::Sequence()
//	:iSeqLength(0), pSeqArray(0), iPairOnSeqCounter(0), iGridLines(0), iGridSlots(0),
//	 ppGrid(0)
//{
//}
//
//Sequence::~Sequence()
//{
//}
//
//void Sequence::SeqToArray(std::string seq)
//{
//	std::string sPosVal = "";
//	int iPosVal = 0;
//
//	iSeqLength = seq.size();			//get size of the sequence
//	pSeqArray = new int[iSeqLength];	//create array with size of sequence
//
//											//converts the string sequence into an array, each array slot contains one element
//	std::cout << "Sequenz: ";
//	for (int i = 0; i < iSeqLength; i++)
//	{
//		sPosVal = seq.at(i);					//get string position value
//		iPosVal = atoi(sPosVal.c_str());		//convert string position value to integer
//		pSeqArray[i] = iPosVal;					//save it in array
//		std::cout << pSeqArray[i];				//print the sequence element i
//	}
//	PRINT_EMPTY_LINE;
//	std::cout << "Anzahl Elemente der Sequenz: " << iSeqLength;	//print number of elements of the sequence
//	PRINT_EMPTY_LINE;
//
//	LOG_INFO("Sequenz in Array abgespeichert");
//}
//
//void Sequence::CreateGrid()
//{
//	iGridLines = iSeqLength / 2;
//	iGridSlots = iSeqLength / 2;
//	ppGrid = new int*[iGridLines];				//create the grid lines
//	for (int i = 0; i < iGridLines; i++)
//	{
//		ppGrid[i] = new int[iGridSlots];		//create the slots for each grid line
//	}
//	for (int i = 0; i < iGridLines; i++)
//	{
//		std::cout << SPACE;						//print space
//
//												//print each element
//		for (int j = 0; j < iGridSlots; j++)
//		{
//			ppGrid[i][j] = EMPTY;
//			std::cout << ppGrid[i][j] << SPACE;
//		}
//		PRINT_NEW_LINE;
//	}
//	Protocol2DArray(ppGrid, iGridLines, iGridSlots);
//
//	LOG_INFO("Grid konstruiert");
//}
//
//int* Sequence::GetSeqArray()
//{
//	return this->pSeqArray;
//}
//
//int Sequence::GetSeqLength()
//{
//	return this->iSeqLength;
//}
//
//void Sequence::SetPairOnSeqCounter(int counter)
//{
//	this->iPairOnSeqCounter = counter;
//}
//
//void Sequence::ShowSequence()
//{
//	for (int i = 0; i < iSeqLength; i++)
//	{
//		std::cout << pSeqArray[i];
//	}
//	PRINT_EMPTY_LINE;
//}
//
//void Sequence::ClearArray()
//{
//	for (int i = 0; i < iSeqLength; i++)
//	{
//		pSeqArray[i] = 0;
//	}
//}