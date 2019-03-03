#include <iostream>
#include <fstream>
#include <string>
#include <unistd.h>
#include "GameofLife.h"

using namespace std;

void GameofLife::runSimulation()
{
	if (runMode == 1) //auto play
	{
		printGrid(); //printing grid
		nextGeneration(); //next Alive = # of alive next generation

		do
		{
			usleep(100000); //1 sec
			//cout << "alive: " << alive << "| nextAlive: " << nextAlive << endl;
			if (isSimOver()) //if # alive == # alive next gen
			{
				setGridtoNextGrid();
				printGrid();
				//program ends
			}
			else
			{
				setGridtoNextGrid();
				alive = nextAlive;
				printGrid();
				nextGeneration();
			}
		} while (!isSimOver()); //loop = new generation
		getchar();
	}
	else if (runMode == 2) //iterate w/ 'enter
	{
		getchar();
		printGrid();
		nextGeneration();

		do
		{
			getchar();
			if (isSimOver()) //if # alive == # alive next gen
			{
				setGridtoNextGrid();
				printGrid();
			}
			else
			{
				setGridtoNextGrid();
				alive = nextAlive;
				printGrid();
				nextGeneration();
			}
		} while(!isSimOver());
	}
	else //3 - output to file
	{
		cout << "Outputting simulation onto " << outfile << " - Please wait..." << endl;
		printGrid();
		nextGeneration();
		do
		{
			if (isSimOver()) //if # alive == # alive next gen
			{
				setGridtoNextGrid();
				printGrid();
			}
			else
			{
				setGridtoNextGrid();
				alive = nextAlive;
				printGrid();
				nextGeneration();
			}
		} while(!isSimOver());
		getchar();
	}

	cout << "Simulation ended. Press 'Enter' to exit program";
	getchar();
	cout << endl;
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
	//cout << "Inputted Grid:" << endl;
	for(int i = 0; i < rows; i++)
	{
		for(int j = 0; j < columns; j++)
		{
			if (g[i][j] == 'X')
			alive++;
		}
		grid[i] = g[i];
		//cout << grid[i] << endl;
	}
	//cout << "alive: " << alive << endl;
}

void GameofLife::nextGeneration()
{
	if (boundaryMode == 1) nextGenClassic(); //classic
	else if (boundaryMode == 2) nextGenDoughnut(); //doughnut
	else nextGenMirror(); //3 - mirror
}

void GameofLife::nextGenClassic()
{
	nextAlive = 0;
	for (int r = 0; r < rows; r++)
	{
		string gridLine;
		gridLine.reserve(columns);

		//cout << "r = " << r << endl;
		for (int c = 0; c < columns; c++)
		{
			int neighbors = 0;
			//cout << "c = " << c << endl;
			if (r != 0 && c != 0) //conditions where NW = null
			{
				if (grid[r-1][c-1] == 'X') neighbors++; //check NW
			}
			//else cout << "false" << endl;
			//cout << "check 1";
			if (r != 0)
			{
				if (grid[r-1][c] == 'X') neighbors++; //check N
			}
			//else cout << "false" << endl;
			//cout << '2';
			if (r != 0 && c != columns-1)
			{
				if (grid[r-1][c+1] == 'X') neighbors++; //check NE
			}
			//else cout << "false" << endl;
			//cout << '3';
			if (c != columns-1)
			{
				if (grid[r][c+1] == 'X') neighbors++; //check E
			}
			//else cout << "false" << endl;
			//cout << '4';
			if (r != rows-1 && c != columns-1)
			{
				if (grid[r+1][c+1] == 'X') neighbors++; //check SE
			}
			//else cout << "false" << endl;
			//cout << '5';
			if (r != rows-1)
			{
				if (grid[r+1][c] == 'X') neighbors++; //check S
			}
			//else cout << "false" << endl;
			//cout << '6';
			if (r != rows-1 && c != 0)
			{
				if (grid[r+1][c-1] == 'X') neighbors++; //check SW
			}
			//else cout << "false" << endl;
			//cout << '7';
			if (c != 0)
			{
				if (grid[r][c-1] == 'X') neighbors++; //check W
			}
			//else cout << "false" << endl;
			//cout << '8' << endl;
			gridLine += processNeighbor(neighbors,r,c); //number of neighbors per cell
			//cout << neighbors;
		}
		//cout << endl;
		//cout << gridLine << endl;
		nextGrid[r] = gridLine;

		//nextGrid[r] = processNeighborLine(gridLine,r);
	}
}

void GameofLife::nextGenDoughnut()
{

}

void GameofLife::nextGenMirror()
{

}

//utility functions
void GameofLife::setBoundaryMode(int b) { boundaryMode = b; }

void GameofLife::setRows(int r) { rows = r; }

void GameofLife::setColumns(int c) { columns = c; }

void GameofLife::printGrid()
{
	ofstream output;
	if (runMode == 1 || runMode == 2)
		cout << "===Generation: " << generation << "===" << endl; //increment generation here
	else //3
	{
		if (generation == 0) output = ofstream(outfile);
		else output = ofstream(outfile, ios::app);

		if (output.is_open()) output << "===Generation: " << generation << "===" << endl;
	}

	for(int r = 0; r < rows; r++)
	{
		if (runMode == 1 || runMode == 2) //print
		{
			cout << grid[r] << endl;
		}
		else //output to file,runmode == 3
		{
			if (output.is_open()) output << grid[r] << endl;
		}
	}

	if (runMode == 3) output.close();
}

char GameofLife::processNeighbor(int i,int r, int c)
{
	if (i <= 1) return '-';
	else if (i == 2)
	{
		if (grid[r][c] == 'X') nextAlive++;
		return grid[r][c];
	}
	else if (i == 3)
	{
		nextAlive++;
		return 'X';
	}
	else return '-'; //i >= 4
}

bool GameofLife::isSimOver()
{
	int genLimit = 999; //only used with runMode 3
	if (runMode == 3) if (generation >= genLimit) return true;
	if (nextAlive == alive || nextAlive == 0) //if gen stabilize or everyone's dead
	{
		bool same = true;
		for(int r = 0; r < rows; r++) //set grid[] to nextGrid[]
		{
			//cout << grid[r] << "|" << nextGrid[r] << "|" << grid[r].compare(nextGrid[r]) << endl;
			if (grid[r].compare(nextGrid[r]) != 0)
			{
				same = false;
			}
		}
		//cout << "same: " << same << endl;
		return same;
	}
	else return false;
}

void GameofLife::setGridtoNextGrid()
{
	for(int r = 0; r < rows; r++) //set grid[] to nextGrid[]
	{
		grid[r] = nextGrid[r];
	}
	generation++;
}


//Private constructor - called by overloaded constructors
GameofLife::GameofLife(int b, int row, int cols)
{
	setBoundaryMode(b);
	setRows(row);
	setColumns(cols);
	grid = new string[rows];
	nextGrid = new string[rows];

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
	runSimulation();
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
	runSimulation();
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
	runSimulation();
}

GameofLife::GameofLife(int bMode, bool autoPlay, int r, int c, string* newGrid) : GameofLife(bMode, r, c)
{
	if (autoPlay) runMode = 1;
	else runMode = 2;

	//cout << "runMode: " << runMode << endl; //ERROR CHECKING
	setGrid(newGrid);
	runSimulation();
}

//Deconstructors
GameofLife::~GameofLife()
{
	delete[] grid;
	delete[] nextGrid;
}
