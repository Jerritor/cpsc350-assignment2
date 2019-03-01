#include <iostream>
#include <fstream>
#include <string>
#include "GameofLife.h"

using namespace std;

void GameofLife::runSimulation()
{
	if (boundaryMode = 1) //classic
	{

	}
	else if (boundaryMode = 2) //doughnut
	{

	}
	else //3 - mirror
	{

	}
}

void GameofLife::generateRandomGrid()	//Generate Random Grid
{
	/**
	DENSITY ALGORITHM:
	- numAlive calculates # of alive cells based on density
	- an empty grid is created of size [row*columns]
	- spots of grid are randomly filled using numAlive and 2 random ints [0,rows], [0,columns]
	**/

	//# of cells * density = # of initial alive cells (floored by int)
	int numAlive = rows*columns*density;
	alive = numAlive; //alive will be changed

	/**
	ERROR checking
	cout << "(rows): " << rows;
	cout << "(columns): " << columns;
	cout << "(density): " << density;
	cout << "numAlive: " << numAlive << endl;
	**/

	for(int r = 0; r < rows; r++) //creating empty grid
	{

		string gridLine;
		gridLine.reserve(columns); //reserve memory for length of column
		for (int c = 0; c < columns; c++)
		{
			gridLine += '-';
		}
		grid[r] = gridLine;
	}

	while (numAlive > 0) //randomly filling grid
	{
		int randX = rand() % rows;
		int randY = rand() % columns;
		if (grid[randX][randY] != 'X')
		{
			grid[randX][randY] = 'X';
			numAlive--;
		}
	}

	for(int r = 0; r < rows; r++)
	{
		cout << grid[r] << endl;
	}

	//cout << "numAlive: " << numAlive << endl;
}

void GameofLife::setGrid(string* g)
{
	cout << "Inputted Grid:" << endl;
	for(int i = 0; i < rows; i++)
	{
		for(int j = 0; j < columns; j++)
		{
			if (g[i][j] == 'X')
			alive++;
		}
		grid[i] = g[i];
		cout << grid[i] << endl;
	}
	cout << "alive: " << alive << endl;
}

string* GameofLife::nextGeneration()
{
	if (boundaryMode = 1) //classic
	{

	}
	else if (boundaryMode = 2) //doughnut
	{

	}
	else //3 - mirror
	{

	}
}

//utility functions
void GameofLife::setBoundaryMode(int b) { boundaryMode = b; }

void GameofLife::setRows(int r) { rows = r; }

void GameofLife::setColumns(int c) { columns = c; }

void GameofLife::printGrid()
{
	for(int c = 0; c < rows; c++)
	{
		if (runMode == 1 || runMode == 2) //print
		{
			cout << "===Generation: " << generation++ << "===" << endl; //increment generation here
			cout << grid[c] << endl;
		}
		else //output to file,runmode == 3
		{
			ofstream output = ofstream("jerrick.out");

			if (output.is_open())
			{
				output << "===Generation: " << generation++ << "===" << endl;
				output << grid[c] << endl;
			}

			output.close();
		}
	}
}

bool GameofLife::isSimOver()
{
	//
}

//Private constructor - called by overloaded constructors
GameofLife::GameofLife(int b, int row, int cols)
{
	setBoundaryMode(b);
	setRows(row);
	setColumns(cols);
	grid = new string[rows];

	cout << "Instantiating Game of Life simulation..." << endl;

	//ERROR CHECKING
	//cout << "boundaryMode: " << boundaryMode << endl;
	//cout << "rows: " << rows << endl;
	//cout << "columns: " << columns << endl;
}

//Public Constructors
GameofLife::GameofLife(int bMode, string outputFile, int r, int c, double d) : GameofLife(bMode, r, c) //this calls the private constructor w/o needing to code it
{
	runMode = 3;
	outfile.assign(outputFile);
	density = d;

	/**
	ERROR CHECKING
	cout << "outfile: " << outfile << endl;
	cout << "density: " << density << endl;
	cout << "runMode: " << runMode << endl;
	**/

	//GENERATE RANDOM GRID
	generateRandomGrid();
	printGrid();
}

GameofLife::GameofLife(int bMode, string outputFile, int r, int c, string* newGrid) : GameofLife(bMode, r, c)
{
	runMode = 3;
	outfile.assign(outputFile);

	/**
	ERROR CHECKING
	cout << "outfile: " << outfile << endl;
	cout << "runMode: " << runMode << endl;
	**/

	setGrid(newGrid);
}

GameofLife::GameofLife(int bMode, bool autoPlay, int r, int c, double d) : GameofLife(bMode, r, c)
{
	if (autoPlay) runMode = 1;
	else runMode = 2;

	density = d;

	/**
	ERROR CHECKING
	cout << "density: " << density << endl;
	cout << "runMode: " << runMode << endl;
	**/

	//GENERATE RANDOM GRID
	generateRandomGrid();
}

GameofLife::GameofLife(int bMode, bool autoPlay, int r, int c, string* newGrid) : GameofLife(bMode, r, c)
{
	if (autoPlay) runMode = 1;
	else runMode = 2;

	//cout << "runMode: " << runMode << endl; //ERROR CHECKING
	setGrid(newGrid);
}

//Deconstructors
GameofLife::~GameofLife()
{
	delete[] grid;
}
