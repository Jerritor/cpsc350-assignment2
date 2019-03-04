#include <iostream>

using namespace std;

class Assignment2
{
  public:
    Assignment2();
    ~Assignment2();
  private:
    bool randomConfig;
    int boundaryMode, rows, columns;
	double density;
    bool autoPlay;
    string outputFile;
    string* newGrid;

    void startProgram();
    void setRandomConfig();
    void setBoundaryMode();
    void setAutoPlay();

    bool readGridFile(string f);
    void setRandomGridProperties();

    bool setRows(bool isRandom, string s);
    bool setColumns(bool isRandom, string s);
    bool setDensity(string s);
};
