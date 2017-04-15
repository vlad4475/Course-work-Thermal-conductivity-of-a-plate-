#pragma once
#include <GL/glut.h>
#include "Plate.h"
class Drow
{
public:

	const int HEIGHT_PLATE = 200;
	const int WIDTH_PLATE = 200;
	const double LENGHT_STEP_OF_TIME = 0.001;
	const double LENGHT_STEP_X = 1;
	const double LENGHT_STEP_Y = 1;
	static const int STEP_DROW = 100;
	
	Drow(int argc, char * argv[]);
	~Drow();
};

