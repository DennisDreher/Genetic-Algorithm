#pragma once

#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
#include <iomanip>

#include "Defines.h"

//ios::in		Zum Lesen
//ios::out 		Zum Schreiben
//ios::trunc 	Datei wird beim �ffnen geleert
//ios::app 		Geschriebene Daten ans Ende anh�ngen
//ios::ate 		Positionszeiger ans Ende setzen

void ProtocolAverageBest();
void ProtocolFolding(int iSeqLength);

void ProtoclFitness();