#include "Assignment2.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

bool randomConfig;
int runMode, boundaryMode, rows, columns;
double density;
string outputFile;
//bool** newGrid;


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
	ifstream inputfile;
	inputfile.open(f);

	if (inputfile.fail())
	{
		cerr << "Error opening file. Enter a valid map file next time." << endl;
		exit(1);
	}
	else
	{
		cout << "Map File Loaded: " << f << endl;
	}

	string currentline;
	int linenum = 0;
	while (getline(inputfile, currentline,'\n')) //not end of file
	{
		linenum++;
		cout << linenum << "| ";

		if (linenum == 1)
		{
			try
			{
				rows = stoi(currentline);

				cout << "rows: " << rows << endl;
				//newGrid = new bool[rows];
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
				} **/
			}
			catch (invalid_argument& ia)
			{
				cerr << "Invalid argument: " << ia.what() << endl;
				cerr << "Error converting line 2 to int" << endl;
				cerr << "Use a valid map file." << endl;
				exit(1);
			}
		}
		else //grid
		{
			int lineLen = currentline.length()-1;

			if (lineLen != columns) //making sure line length = # of grid columns
			{
				cerr << "Error with line " << linenum << endl;
				cerr << "Line length must equal column length stated on row 2" << endl;
				cerr << "Use a valid map file." << endl;
				exit(1);
			}

			for (int c = 0; c < lineLen; c++) //characters
			{
				switch (currentline[c]) //setting values of grid as bools
				{
					case '-':
						//newGrid[currentline-3][c] = false;
						cout << "-";
						break;
					case 'X':
						//newGrid[currentline-3][c] = true;
						cout << "X";
						break;
					default:
						cout << "E";
						break;
				}
			}
			cout << endl;
		}
		inputfile.clear();
	}

	if (inputfile.fail())
		cerr << "Error while reading file" << endl;
	if (inputfile.eof())
		cerr << "EOF Error" << endl;

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
		delete * newGrid[i];
	}

	//deleting rows
	delete * newGrid;
	**/
}
