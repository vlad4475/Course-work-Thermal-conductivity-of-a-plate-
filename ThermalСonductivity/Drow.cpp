#include "Drow.h"
#include <iostream>
#include "Plate.h"
#include <fstream>
#include <stdio.h>
#include <string>
#include <omp.h>

Plate *plate;
int k; //Вол-во срабатываний таймера

void Timer(int)
{
	glClear(GL_COLOR_BUFFER_BIT);

	glBegin(GL_POINTS);

	glutPostRedisplay();

	for (int i = 0; i < Drow::STEP_DROW; i++)
	{
		plate->DoIneration(plate->tempLastIteration, plate->tempNowIteration);
	}

	//Выводим на экран каждую STEP_DROW итерацию
	std::cout << "Number iteration: " << k * 100 << std::endl;

		for (int i = 0; i < plate->countStepX; i++)
		{
			for (int j = 0; j < plate->countStepY; j++)
			{
				glColor3f(plate->tempLastIteration[i][j] / 1060, 0, 1 - plate->tempLastIteration[i][j] / 1600);
				if (plate->tempLastIteration[i][j] < 100 && plate->tempLastIteration[i][j] > -100)
					glColor3f(plate->tempLastIteration[i][j] / 1060, 0.15, 1 - plate->tempLastIteration[i][j] / 1600);

				glVertex2f(i, j);
			}
		}		
	
	glEnd();
	glutSwapBuffers();
	k++;

	glutTimerFunc(0, Timer, 0);
	
}


void reshape(int w, int h)
{
	glViewport(0, 0, w, h);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, w, 0, h);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void display()
{
	
}
	

Drow::Drow(int argc, char * argv[])
{
	plate = new Plate(WIDTH_PLATE, HEIGHT_PLATE, LENGHT_STEP_OF_TIME, LENGHT_STEP_X, LENGHT_STEP_Y);

	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);

	glutInitWindowSize(WIDTH_PLATE, HEIGHT_PLATE);
	glutCreateWindow("Plate");

	glutReshapeFunc(reshape);
	
	glutDisplayFunc(display);

	glutTimerFunc(500, Timer, 0);

	glutMainLoop();
	
}

Drow::~Drow()
{
}




