#pragma once
#include <iostream>
#include <string>
#include "ProtocolFile.h"
#include "Defines.h"
#include "MyLog.h"

class Sequence
{
public:
	Sequence();
	~Sequence();

	void SeqToArray(std::string seq);
	void CreateGrid();

	void SetPairOnSeqCounter(int counter);

	int* GetSeqArray();

	int GetSeqLength();


	void ShowSequence();
	void ClearArray();

private:
	int iSeqLength;
	int* pSeqArray;
	int iPairOnSeqCounter;		//number of hydrophob pair on sequence
	int iGridLines;
	int iGridSlots;
	int** ppGrid;
};