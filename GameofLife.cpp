#include <iostream>
#include <string>
#include <array>
#include "GameofLife.h"

using namespace std;

GameofLife::GameofLife(int bMode, string outputFile, int rows, int columns, double density)
{
	cout << "Instantiating Game of Life simulation..." << endl;
	cout << "bMode: " << bMode << endl;
	cout << "outputFile: " << outputFile << endl;
	cout << "rows: " << rows << endl;
	cout << "columns: " << columns << endl;
	cout << "density: " << density << endl;
}

GameofLife::GameofLife(int bMode, string outputFile, int rows, int columns, string* newGrid)
{
	cout << "Instantiating Game of Life simulation..." << endl;
	cout << "bMode: " << bMode << endl;
	cout << "outputFile: " << outputFile << endl;
	cout << "rows: " << rows << endl;
	cout << "columns: " << columns << endl;

	grid = new string[rows];
	cout << "Inputted Grid:" << endl;
	for(int i = 0; i < rows; i++)
	{
		grid[i] = newGrid[i];
		cout << grid[i] << endl;
	}
}

GameofLife::GameofLife(int bMode, bool autoPlay, int rows, int columns, double density)
{
	cout << "Instantiating Game of Life simulation..." << endl;
	cout << "bMode: " << bMode << endl;
	cout << "autoPlay: " << autoPlay << endl;
	cout << "rows: " << rows << endl;
	cout << "columns: " << columns << endl;
	cout << "density: " << density << endl;
}

GameofLife::GameofLife(int bMode, bool autoPlay, int rows, int columns, string* newGrid)
{
	cout << "Instantiating Game of Life simulation..." << endl;
	cout << "bMode: " << bMode << endl;
	cout << "autoPlay: " << autoPlay << endl;
	cout << "rows: " << rows << endl;
	cout << "columns: " << columns << endl;
	cout << "Inputted Grid:" << endl;
	for(int i = 0; i < rows; i++)
	{
		cout << newGrid[i] << endl;
	}
}

GameofLife::~GameofLife()
{

}
