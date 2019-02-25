#include "Assignment2.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

bool randomConfig; //set by setRandomConfig();
int runMode, boundaryMode, rows, columns; //set by setRunMode(), setBoundaryMode(). setRandomConfig() x2
double density; //set by setRandomConfig()
string outputFile; //set by setOutputFile()
string *newGrid; //set by readGridFile()

void Assignment2::startProgram()
{
	setRandomConfig();
}

void Assignment2::setRandomConfig()
{
	cout << "Do you wish to provide a map file or randomly generate one?" << endl;
	cout << "1: Map File" << endl;
	cout << "2: Generate Map" << endl;

	string input;
	cin >> input;

	if (input[0] == '1') //map file
	{
		cout << "Input filename (must be in directory & includes extension): ";
		cin >> input;
		readGridFile(input);
	}
	else if (input[0] == '2')
	{
		cout << "Generate Map" << endl;
	}
	else
	{
		cout << "Please enter the number corresponding to your option." << endl;
		setRandomConfig();
	}

	for(int i = 0; i < rows; i++) //rows
	{
		for(int j = 0; j < columns; j++) //columns
			cout << newGrid[i][j];
		cout << endl;
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
		{
			try
			{
				rows = stoi(currentline);

				cout << "rows: " << rows << endl;
				newGrid = new string[rows];
			}
			catch (invalid_argument& ia)
			{
				cerr << "Invalid argument: " << ia.what() << endl;
				cerr << "Error converting line 1 to int" << endl;
				cerr << "Use a valid map file." << endl;
				exit(1);
			}
		}
		else if (linenum == 2) //columns
		{
			try
			{
				columns = stoi(currentline);

				cout << "columns: " << columns << endl;

				/**
				for(int i = 0; i < rows; i++)
				{
					newGrid[rows] = new bool[columns];
				}
				**/
			}
			catch (invalid_argument& ia)
			{
				cerr << "Invalid argument: " << ia.what() << endl;
				cerr << "Error converting line 2 to int" << endl;
				cerr << "Use a valid map file." << endl;
				exit(1);
			}
		}
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

			newGrid[linenum-3].assign(currentline);

			/**
			for (int c = 0; c < columns; c++) //char in string index
			{
				switch (currentline[c]) //setting values of grid as bools
				{
					case '-':
						cout << "hello" << endl;
						Assignment2::newGrid[linenum-3][c] = false; //FIX THIS
						cout << "-";
						break;
					case 'X':
						Assignment2::newGrid[linenum-3][c] = true;
						cout << "X";
						break;
					default:
						cout << "E";
						break;
				}
			}
			**/

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

Assignment2::Assignment2()
{
	setRandomConfig();
	//startProgram();
}

Assignment2::~Assignment2()
{
	/**
	//deleting columns
	for (int i = 0; i < rows; i++) {
		delete[] newGrid[i];
	}
	**/

	//deleting rows
	delete[] newGrid;
}
