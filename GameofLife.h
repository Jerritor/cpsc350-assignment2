#include <iostream>

using namespace std;

class GameofLife
{
	public:
		void generateRandomGrid();

		GameofLife(int bMode, string outputFile, int r, int c, double d);
		GameofLife(int bMode, string outputFile, int r, int c, string* newGrid);
		GameofLife(int bMode, bool autoPlay, int r, int c, double d);
		GameofLife(int bMode, bool autoPlay, int r, int c, string* newGrid);
		~GameofLife();
	private:
		//common vars for all 4 constructors
		int boundaryMode;
		string outfile;
		int rows, columns;
		int runMode;

		//random grid vs flatfile
		double density;

		string* grid;
		int generation; //current generation
};
