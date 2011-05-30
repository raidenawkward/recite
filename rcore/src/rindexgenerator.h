#ifndef RINDEXGENERATOR_H
#define RINDEXGENERATOR_H

#include "dictbase.h"
#include "rtime.h"

#include <stdio.h>
#include <stdlib.h>
#include <string>

using namespace std;

class IndexGeneratorBase
{
public:
	IndexGeneratorBase();
};

class RIndexGenerator : public IndexGeneratorBase
{
public:
	RIndexGenerator();
};


#endif // RINDEXGENERATOR_H
