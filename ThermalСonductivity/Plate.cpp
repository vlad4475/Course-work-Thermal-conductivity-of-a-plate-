#include "Plate.h"
#include <iostream>
#include <stdio.h>
#include <fstream>
#include <string>
#include <omp.h>


Plate::Plate(int countX, int countY, double ST, double lStepX, double lStepY)
{
	
	LenghtStepX = lStepX;
	LenghtStepY = lStepY;
	LengthSpetT = ST;
	countStepX = countX;
	countStepY = countY;
	sizeX = countStepX * LenghtStepX;
	sizeY = countStepY * LenghtStepY;

	heatExchangeWithEnvironment = HEAT_EXCHANGE_WITH_ENVIRONMENT;
	ambientTemperature = AMBIENT_TEMPERATURE;

	tempNowIteration = new double*[sizeX];
	tempLastIteration = new double*[sizeX];

	for (int i = 0; i < sizeX; i++)
	{
		tempNowIteration[i] = new double[sizeY];
		tempLastIteration[i] = new double[sizeY];
	}

	ShapeStartCondition(tempLastIteration);
	ShapeStartCondition(tempNowIteration);
	ShapeBorderCondition(tempLastIteration, tempNowIteration);
	ShapeBorderCondition(tempNowIteration, tempNowIteration);

}

void Plate::PostDecision(int countIteration)
{
	
}

void Plate::ShapeStartCondition(double **matrix)
{
	for (int i = 0; i < countStepX; i++)
	for (int j = 0; j < countStepY; j++)
	{
		matrix[i][j] = START_PLATE_TEMPERATURE; //можно так же задавать начальную температуру как функцию от координат
	}
}

void Plate::ShapeBorderCondition(double **lastMatrix, double **nowMatrix)
{
	
	for (int i = 0; i < countStepX; i++)
		nowMatrix[i][0] = heatExchangeWithEnvironment * LengthSpetT * 
		(ambientTemperature - 2 * lastMatrix[i][0] + lastMatrix[i][1]) + lastMatrix[i][0];

	for (int i = 0; i < countStepY; i++)
		nowMatrix[0][i] = heatExchangeWithEnvironment * LengthSpetT * 
		(ambientTemperature - 2 * lastMatrix[0][i] + lastMatrix[1][i]) + lastMatrix[0][i];

	for (int i = 0; i < countStepX; i++)
		nowMatrix[i][countStepY - 1] = heatExchangeWithEnvironment * 
		LengthSpetT * (ambientTemperature - 2 * lastMatrix[i][countStepY - 1] + lastMatrix[i][countStepY - 2]) + lastMatrix[i][countStepY - 1];

	for (int i = 0; i < countStepY; i++)
		nowMatrix[countStepX - 1][i] = heatExchangeWithEnvironment * 
		LengthSpetT * (ambientTemperature - 2 * lastMatrix[countStepX - 1][i] + lastMatrix[countStepX - 2][i]) + lastMatrix[countStepX - 1][i]; 
	
}

//-------------------------------------------------------------------------------------------------------------------------

double Plate::SupplyHeat(double x, double y, double u, double t)
{
	double hot;
	hot = 0;
	
	//Эти координаты нужны просто для примера.
	//Естественно можно легко модифицировать программу, что бы вводить координаты нагрева и силу нагрева через консоль или файл.
	//Под hot понимается кол-во поступления теплоты в данной точке в джоулях.
	
	if ((x < 65) && (y < 65) && (x > 55) && (y > 55)) hot = 5000;
	if ((x < 145) && (y < 65) && (x > 135) && (y > 55)) hot = 5000;
	if ((x < 55) && (y < 145) && (x > 45) && (y > 135)) hot = 5000;
	if ((x < 145) && (y < 145) && (x > 135) && (y > 135)) hot = -5000;

	return hot;
}

void Plate::DoIneration(double **lastMatrix, double **nowMatrix)
{
	
#pragma omp parallel
	{
#pragma omp for
		for (int i = 1; i < countStepX - 1; i++)
		{
			for (int j = 1; j < countStepY - 1; j++)
			{
				nowMatrix[i][j] = LengthSpetT * ConductivityOfPlait(i, j, lastMatrix[i][j], NumIteration)
					* ((nowMatrix[i - 1][j] - 2 * lastMatrix[i][j] + lastMatrix[i + 1][j]) / (LenghtStepX * LenghtStepX)
					+ (nowMatrix[i][j - 1] - 2 * lastMatrix[i][j] + lastMatrix[i][j + 1]) / (LenghtStepY * LenghtStepY))
					+ LengthSpetT * SupplyHeat(i, j, lastMatrix[i][j], NumIteration)
					+ lastMatrix[i][j];
			}
		}
	}
	
	ShapeBorderCondition(lastMatrix, nowMatrix);

	double** helperExchange;
	helperExchange = tempLastIteration;
	tempLastIteration = tempNowIteration;
	tempNowIteration = helperExchange;
	NumIteration++;
}

double Plate::ConductivityOfPlait(double x, double y, double u, double t)
{
	return 10;
}

void Plate::PrintIteration(double **matrix)
{
	std::ofstream file;
	std::string namefile = std::to_string(NumIteration);
	file.open("iterationNumer" + namefile + ".txt");

	for (int i = 0; i < countStepX; i++)
	{
		for (int j = 0; j < countStepY; j++)
		{
			file << matrix[i][j] << " ";
		}
		file << std::endl;
	}

	file.close();
	
}




Plate::~Plate()
{
}
