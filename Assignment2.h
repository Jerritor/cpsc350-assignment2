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
    bool runMode;
    string outputFile;
    string* newGrid;

    void startProgram();
    void setRandomConfig();
    void setBoundaryMode();
    void setRunMode();
    void setOutputFile();

    void readGridFile(string f);
    void generateRandomGrid();

    bool setRows(bool isRandom, string s);
    bool setColumns(bool isRandom, string s);
    bool setDensity(string s);
};
