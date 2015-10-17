#include <iostream>
#include <fstream>
#include "cMaze.h"

using namespace std;

/// сделать: запись в файл в utf


int main(int argc, char *argv[])
{
    cMaze m(35,25);
    m.generate(cMaze::genType_1);
    //m.printToConsole();
    //m.setSomeSpacePercent(60);
    //cout <<endl;
    //m.printToConsole();


    return 0;
}


