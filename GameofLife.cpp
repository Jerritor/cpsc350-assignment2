#include <iostream>
#include <string>
#include <array>
#include "GameofLife.h"

using namespace std;

void GameofLife::generateRandomGrid()	//Generate Random Grid
{

}

//Constructors
GameofLife::GameofLife(int bMode, string outputFile, int r, int c, double d)
{
	runMode = 3;

	boundaryMode = bMode;
	outfile.assign(outputFile);
	rows = r;
	columns = c;
	density = d;

	cout << "Instantiating Game of Life simulation..." << endl;
	cout << "boundaryMode: " << boundaryMode << endl;
	cout << "outfile: " << outfile << endl;
	cout << "rows: " << rows << endl;
	cout << "columns: " << columns << endl;
	cout << "density: " << density << endl;
	cout << "runMode: " << runMode << endl;

	//GENERATE RANDOM GRID
}

GameofLife::GameofLife(int bMode, string outputFile, int r, int c, string* newGrid)
{
	runMode = 3;

	boundaryMode = bMode;
	outfile.assign(outputFile);
	rows = r;
	columns = c;

	cout << "Instantiating Game of Life simulation..." << endl;
	cout << "boundaryMode: " << boundaryMode << endl;
	cout << "outfile: " << outfile << endl;
	cout << "rows: " << rows << endl;
	cout << "columns: " << columns << endl;
	cout << "runMode: " << runMode << endl;

	grid = new string[rows];
	cout << "Inputted Grid:" << endl;
	for(int i = 0; i < rows; i++)
	{
		grid[i] = newGrid[i];
		cout << grid[i] << endl;
	}

	//GENERATE RANDOM GRID
}

GameofLife::GameofLife(int bMode, bool autoPlay, int r, int c, double d)
{
	if (autoPlay)
		runMode = 1;
	else
		runMode = 2;

	boundaryMode = bMode;
	rows = r;
	columns = c;
	density = d;


	cout << "Instantiating Game of Life simulation..." << endl;
	cout << "boundaryMode: " << boundaryMode << endl;
	cout << "rows: " << rows << endl;
	cout << "columns: " << columns << endl;
	cout << "density: " << density << endl;
	cout << "runMode: " << runMode << endl;

	//GENERATE RANDOM GRID
}

GameofLife::GameofLife(int bMode, bool autoPlay, int r, int c, string* newGrid)
{
	if (autoPlay)
		runMode = 1;
	else
		runMode = 2;

	boundaryMode = bMode;
	rows = r;
	columns = c;

	cout << "Instantiating Game of Life simulation..." << endl;
	cout << "boundaryMode: " << boundaryMode << endl;
	cout << "rows: " << rows << endl;
	cout << "columns: " << columns << endl;
	cout << "runMode: " << runMode << endl;

	grid = new string[rows];
	cout << "Inputted Grid:" << endl;
	for(int i = 0; i < rows; i++)
	{
		grid[i] = newGrid[i];
		cout << grid[i] << endl;
	}

	//GENERATE RANDOM GRID
}

//Deconstructors
GameofLife::~GameofLife()
{

}
