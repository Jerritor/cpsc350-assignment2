#include <iostream>
#include <string>
#include "GameofLife.h"

using namespace std;

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
	cout << "(rows): " << rows;
	cout << "(columns): " << columns;
	cout << "(density): " << density;
	cout << "numAlive: " << numAlive << endl;

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

//Private constructor - called by overloaded constructors
GameofLife::GameofLife(int b, int row, int cols)
{
	boundaryMode = b;
	rows = row;
	columns = cols;
	grid = new string[rows];

	cout << "boundaryMode: " << boundaryMode << endl;
	cout << "rows: " << rows << endl;
	cout << "columns: " << columns << endl;
}

//Public Constructors
GameofLife::GameofLife(int bMode, string outputFile, int r, int c, double d)
{
	runMode = 3;
	outfile.assign(outputFile);
	density = d;

	cout << "Instantiating Game of Life simulation..." << endl;
	GameofLife(bMode, r, c);

	cout << "outfile: " << outfile << endl;
	cout << "density: " << density << endl;
	cout << "runMode: " << runMode << endl;

	//GENERATE RANDOM GRID
	generateRandomGrid();
}

GameofLife::GameofLife(int bMode, string outputFile, int r, int c, string* newGrid)
{
	runMode = 3;
	outfile.assign(outputFile);

	cout << "Instantiating Game of Life simulation..." << endl;
	GameofLife(bMode, r, c);

	cout << "outfile: " << outfile << endl;
	cout << "runMode: " << runMode << endl;

	cout << "Inputted Grid:" << endl;
	for(int i = 0; i < rows; i++)
	{
		grid[i] = newGrid[i];
		cout << grid[i] << endl;
	}
}

GameofLife::GameofLife(int bMode, bool autoPlay, int r, int c, double d)
{
	if (autoPlay)
		runMode = 1;
	else
		runMode = 2;
	density = d;

	cout << "Instantiating Game of Life simulation..." << endl;
	GameofLife(bMode, r, c);

	cout << "density: " << density << endl;
	cout << "runMode: " << runMode << endl;

	//GENERATE RANDOM GRID
	generateRandomGrid();
}

GameofLife::GameofLife(int bMode, bool autoPlay, int r, int c, string* newGrid)
{
	if (autoPlay)
		runMode = 1;
	else
		runMode = 2;

	cout << "Instantiating Game of Life simulation..." << endl;
	GameofLife(bMode, r, c);

	cout << "runMode: " << runMode << endl;
	cout << "Inputted Grid:" << endl;
	for(int i = 0; i < rows; i++)
	{
		grid[i] = newGrid[i];
		cout << grid[i] << endl;
	}
}

//Deconstructors
GameofLife::~GameofLife()
{
	delete[] grid;
}
