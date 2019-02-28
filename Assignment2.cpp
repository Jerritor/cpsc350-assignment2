#include "Assignment2.h"
#include "GameofLife.h"
#include <iostream>
#include <fstream>
#include <string>
#include <math.h>

using namespace std;

//called on instantiation
void Assignment2::startProgram()
{
	setRandomConfig();
	cout << endl;
	setBoundaryMode();
	cout << endl;
	setAutoPlay();
	cout << endl;

	//Initializing the simulation based on the options selected
	if (outputFile.length() != 0) //if outputFile was uninitialized
	{
		if (density != -1.0) //if density was initialized
		{
			GameofLife game(boundaryMode,outputFile,rows,columns,density);
		}
		else
		{
			GameofLife game(boundaryMode,outputFile,rows,columns,newGrid);
		}
	}
	else
	{
		if (density != -1.0)
		{
			GameofLife game(boundaryMode,autoPlay,rows,columns,density);
		}
		else
		{
			GameofLife game(boundaryMode,autoPlay,rows,columns,newGrid);
		}
	}
}

//User Interface functions
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
	}
	else if (input[0] == '2') //generate random map
	{
		randomConfig = true;
		setRandomGridProperties();
	}
	else //invalid input
	{
		cout << "Please enter the number corresponding to your option." << endl;
		setRandomConfig();
	}
}

void Assignment2::setBoundaryMode()
{
	cout << "Which of the following boundary modes do you want to run?" << endl;
	cout << "1: Classic" << endl;
	cout << "2: Doughnut" << endl;
	cout << "3: Mirror" << endl;
	cout << "> ";

	string input;
	cin >> input;

	if (input[0] == '1') //Classic
		boundaryMode = 1;
	else if (input[0] == '2') //Doughnut
		boundaryMode = 2;
	else if (input[0] == '3') //Mirror
		boundaryMode = 3;
	else //invalid input
	{
		cout << "Please enter the number corresponding to your option." << endl;
		setBoundaryMode();
	}
}

void Assignment2::setAutoPlay()
{
	cout << "How do you want to run the simulation?" << endl;
	cout << "1: Automatically iterate thru generations" << endl;
	cout << "2: Iterate by pressing (or mashing) 'enter'" << endl;
	cout << "3: Output simulation to file" << endl;
	cout << "> ";

	string input;
	cin >> input;

	if (input[0] == '1') //automatically iterate
		autoPlay = true;
	else if (input[0] == '2') //iterate every 'enter'
		autoPlay = false;
	else if (input[0] == '3') //output to file
	{
		bool outputFileSet = false;
		while (!outputFileSet)
		{
			cout << "Output filename: ";
			cin >> input;

			if (input.length() != 0) //if file name is not empty
			{
				outputFileSet = true;
			}
			else
			{
				cout << "Enter a valid output file" << endl << endl;
			}
		}
		outputFile = input;
	}
}

//subfunctions
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
		cout << "Opening " << f << "..." << endl;
	string currentline;
	int linenum = 0;
	while (getline(inputfile, currentline, '\n')) //not end of file
	{
		//newline & carriage return deletion from string
		for(int i = 0; i < currentline.length(); i++)
		{
			if (currentline[i] == '\n' || currentline[i] == '\r')
				currentline.erase(i);
		}

		linenum++;
		//cout << linenum << "|currentline: " << currentline << '|' << endl;

		if (linenum == 1) //line 1: # of rows
			setRows(randomConfig,currentline);
		else if (linenum == 2) //columns
			setColumns(randomConfig,currentline);
		else //grid: lines 3 or greater
		{
			int lineLen = currentline.length();

			//cerr << "columns: " << columns << endl;
			//cerr << "lineLen: " << lineLen << endl;

			if (lineLen != columns) //making sure line length = # of grid columns
			{
				cerr << "Error with grid width - line " << linenum << endl;
				cerr << "Grid width must equal # of columns stated on row 2" << endl;
				cerr << "Use a valid map file." << endl;
				inputfile.close();
				exit(1);
			}

			//linenum >= 3
			newGrid[linenum-3].assign(currentline); //assigning strings to be passed”

			//cout << endl;
		}
		inputfile.clear();
	}

	//cout << "rows: " << rows << endl;
	//cout << "linenum-2: " << linenum-2 << endl;

	if (linenum-2 != rows) //checking if # of map lines-2 = # of grid rows
	{
		cerr << "Error with grid height" << endl;
		cerr << "Grid height must equal column length stated on row 1" << endl;
		cerr << "Use a valid map file." << endl;
		inputfile.close();
		exit(1);
	}

	cout << "Map File Succesfully Loaded: " << f << endl;
	inputfile.close();
}

void Assignment2::setRandomGridProperties()
{
	/**
	BUG/DESIGN PROBLEM: Before the use of the while-loops, the functions
	used to recall setRandomGridProperties() again, however, i had some
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
		cout << "Density: ";
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
				cout << "Please input an integer" << endl << endl;
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
			cout << "Error with your row input" << endl << endl;
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
				cout << "Please input a integer" << endl << endl;
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
			cout << "Error with your column input" << endl << endl;
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
			cout << "Please input a decimal [0,1]" << endl << endl;
			return false;
		}

		density = d;
		return true;
	}
	catch (invalid_argument& ia)
	{
		cerr << "Invalid argument: " << ia.what() << endl;
		cout << "Please input a decimal [0,1]" << endl << endl;
	}
	return false;
}

//Constructor
Assignment2::Assignment2()
{
	//uninitialized values (for error checking)
	density = -1.0;

	startProgram();
	//setRandomConfig();
}

//Destructor
Assignment2::~Assignment2()
{
	delete[] newGrid;
}
