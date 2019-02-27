#include <iostream>

using namespace std;

class GameofLife
{
	public:
		GameofLife(int bMode, string outputFile, int rows, int columns, double density);
		GameofLife(int bMode, string outputFile, int rows, int columns, string* newGrid);
		GameofLife(int bMode, bool autoPlay, int rows, int columns, double density);
		GameofLife(int bMode, bool autoPlay, int rows, int columns, string* newGrid);

		~GameofLife();
	private:
		string* grid;
};
