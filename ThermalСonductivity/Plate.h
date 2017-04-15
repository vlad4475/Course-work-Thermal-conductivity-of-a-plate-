#pragma once
class Plate
{
public:

	const double HEAT_EXCHANGE_WITH_ENVIRONMENT = 500;
	const double AMBIENT_TEMPERATURE = -100;
	const double START_PLATE_TEMPERATURE = 500;

	double ** tempLastIteration;
	double ** tempNowIteration;
	int NumIteration;
	int sizeX, sizeY;
	double LenghtStepX, LenghtStepY, LengthSpetT;
	int countStepX, countStepY;
	double heatExchangeWithEnvironment;
	double ambientTemperature;

	void PostDecision(int countIteration);
	
	void ShapeStartCondition(double **matrixIteration);
	void ShapeBorderCondition(double **lastMatrix, double **nowMatrix);
	void DoIneration(double **lastIteartionMatrix, double **nowIterationMatrix);
	double SupplyHeat(double x, double y, double u, double t);
	void PrintIteration(double **matrixIteration);
	double ConductivityOfPlait(double x, double y, double u, double t);

	Plate(int countX, int countY, double ST, double lStepX, double lStepY);
	~Plate();
};

