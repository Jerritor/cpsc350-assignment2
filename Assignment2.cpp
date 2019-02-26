#include "Assignment2.h"
#include <iostream>
#include <fstream>
#include <string>
#include <math.h>

using namespace std;

bool randomConfig; //set by setRandomConfig();
int runMode, boundaryMode, rows, columns; //set by setRunMode(), setBoundaryMode(). setRandomConfig() x2
double density; //set by setRandomConfig()
string outputFile; //set by setOutputFile()
string *newGrid; //set by readGridFile()

//called on instantiation
void Assignment2::startProgram()
{
	setRandomConfig();
}

//sub functions
void Assignment2::setRandomConfig()
{
	cout << "Do you wish to provide a map file or randomly generate one?" << endl;
	cout << "1: Map File" << endl;
	cout << "2: Generate Map" << endl;
	cout << "> ";

	string input;
	cin >> input;

	if (input[0] == '1') //map file
	{
		randomConfig = false;
		cout << "Input filename (must be in directory & includes extension): ";
		cin >> input;

		readGridFile(input);

		/**
		//tests the grid map
		for(int i = 0; i < rows; i++) //rows
		{
			for(int j = 0; j < columns; j++) //columns
				cout << newGrid[i][j];
			cout << endl;
		}
		**/

	}
	else if (input[0] == '2') //generate random map
	{
		randomConfig = true;

		generateRandomGrid();
	}
	else //wrong input
	{
		cout << "Please enter the number corresponding to your option." << endl;
		setRandomConfig();
	}
}

void Assignment2::setBoundaryMode()
{

}

void Assignment2::setRunMode()
{

}

void Assignment2::setOutputFile()
{

}

//sub-sub functions
void Assignment2::readGridFile(string f)
{
	ifstream inputfile; //input stream
	inputfile.open(f); //opening the user inputted file

	if (inputfile.fail())
	{
		cerr << "Error opening file. Enter a valid map file next time." << endl;
		exit(1);
	}
	else
		cout << "Opening " << f << "...\n";
	string currentline;
	int linenum = 0;
	while (getline(inputfile, currentline,'\n')) //not end of file
	{
		linenum++;
		cout << linenum << "| ";

		if (linenum == 1) //line 1: # of rows
			setRows(randomConfig,currentline);
		else if (linenum == 2) //columns
			setColumns(randomConfig,currentline);
		else //grid: lines 3 or greater
		{
			int lineLen = currentline.length();

			if (lineLen != columns) //making sure line length = # of grid columns
			{
				cerr << "Error with grid width - line " << linenum << endl;
				cerr << "Grid width must equal # of columns stated on row 2" << endl;
				cerr << "Use a valid map file." << endl;
				exit(1);
			}

			//linenum >= 3
			newGrid[linenum-3].assign(currentline); //assigning strings to be passed”

			cout << endl;
		}
		inputfile.clear();
	}

	if (linenum-2 != rows) //checking if # of map lines-2 = # of grid rows
	{
		cerr << "Error with grid height" << endl;
		cerr << "Grid height must equal column length stated on row 1" << endl;
		cerr << "Use a valid map file." << endl;
		exit(1);
	}

	cout << "Map File Succesfully Loaded: " << f << endl;
	inputfile.close();
}

void Assignment2::generateRandomGrid()
{
	/**
	BUG/DESIGN PROBLEM: Before the use of the while-loops, the functions
	used to recall generateRandomGrid() again, however, i had some
	random recall repetition again. Not sure what the problem was.
	**/

	bool rowsSet = false, colsSet = false, densSet = false;
	string input;


	cout << "=======" << endl;
	while (!rowsSet) //setting rows
	{

		cout << "Number of rows/height of grid: ";
		cin >> input;
		rowsSet = setRows(randomConfig,input);
		//cout << "rowsSet: " << rowsSet << endl;
	}

	cout << "=======" << endl;
	while (!colsSet) //setting columns
	{
		cout << "Number of columns/width of grid: ";
		cin >> input;
		colsSet = setColumns(randomConfig,input);
		//cout << "colsSet: " << colsSet << endl;
	}

	cout << "=======" << endl;
	while (!densSet) //setting density
	{
		cout << "Density [0,1]: ";
		cin >> input;
		densSet = setDensity(input);
		//cout << "densSet: " << densSet << endl;
	}
}

//utility functions
bool Assignment2::setRows(bool isRandom, string s)
{
	try
	{
		if (fmod(stod(s),1.0) != 0.0) //if input is a decimal
		{
			if(isRandom) //random map
			{
				cout << "Please input an integer\n" << endl;
			}
			else //flat file
			{
				cout << "Error with row input - Check line 1 of " << s << endl;
			}

			return false;
		}
		rows = stoi(s);

		newGrid = new string[rows];
		return true;
	}
	catch (invalid_argument& ia)
	{
		cerr << "Invalid argument: " << ia.what() << endl;
		if (isRandom) //random map
		{
			cout << "Error with your row input\n" << endl;
		}
		else //flat-grid map
		{
			cerr << "Error converting line 2 to int" << endl;
			cerr << "Use a valid map file." << endl;
			exit(1);
		}
	}
	return false;
}

bool Assignment2::setColumns(bool isRandom, string s)
{
	try
	{
		if (fmod(stod(s),1.0) != 0.0) //if input is a decimal
		{
			if (isRandom)
			{
				cout << "Please input a integer\n" << endl;
			}
			else
			{
				cout << "Error with column input - Check line 2 of " << s << endl;
			}
			return false;
		}

		columns = stoi(s);
		return true;
	}
	catch (invalid_argument& ia)
	{
		cerr << "Invalid argument: " << ia.what() << endl;
		if (isRandom) //random map
		{
			cout << "Error with your column input\n" << endl;
		}
		else //flat-grid map
		{
			cerr << "Error converting line 1 to int" << endl;
			cerr << "Use a valid map file." << endl;
			exit(1);
		}
	}
	return false;
}

bool Assignment2::setDensity(string s)
{
	try
	{
		double d = stod(s);
		if (d > 1.0 || d < 0.0) //if out of range
		{
			cout << "Please input a decimal [0,1]\n" << endl;
			return false;
		}

		density = d;
		return true;
	}
	catch (invalid_argument& ia)
	{
		cerr << "Invalid argument: " << ia.what() << endl;
		cout << "Please input a decimal [0,1]\n" << endl;
	}
	return false;
}

//Constructor
Assignment2::Assignment2()
{
	//startProgram();
	setRandomConfig();
}

//Destructor
Assignment2::~Assignment2()
{
	delete[] newGrid;
}
