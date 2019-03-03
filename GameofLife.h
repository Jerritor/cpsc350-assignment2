#include <iostream>

using namespace std;

class GameofLife
{
	public:
		GameofLife(int bMode, string outputFile, int r, int c, double d);
		GameofLife(int bMode, string outputFile, int r, int c, string* newGrid);
		GameofLife(int bMode, bool autoPlay, int r, int c, double d);
		GameofLife(int bMode, bool autoPlay, int r, int c, string* newGrid);

		~GameofLife();
	private:
		GameofLife(int b, int row, int cols);

		void runSimulation(); //start program

		//subfunctions
		void generateRandomGrid();
		void setGrid(string* g);
		void nextGeneration(); //uses the other nextGen__(funcs)
		void nextGenClassic();
		void nextGenDoughnut();
		void nextGenMirror();

		//utility functions
		void setBoundaryMode(int b);
		void setRows(int r);
		void setColumns(int c);
		void printGrid();
		char processNeighbor(int i, int r, int c);
		bool isSimOver();
		void setGridtoNextGrid();


		//grid
		string* grid;
		string* nextGrid;
		int generation = 0; //current generation
		int alive = 0;
		int nextAlive = 0;

		//common vars for all 4 constructors
		int boundaryMode;
		string outfile;
		int rows;
		int columns;
		int runMode;

		double density; //random grid vs. flatfile
};
