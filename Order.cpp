/********************************************************************************* 
* Diwa Ashwini Vittala, dashwini
* 2022 Spring CSE101 PA7
* Order.cpp
* Main executable file for PA7
**********************************************************************************/

#include "Dictionary.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main(int argc, char * argv[]) {
    ifstream in;
    ofstream out;
    // check command line args
    if( argc != 3 ){
        cerr << "Usage: " << argv[0] << " <input file> <output file>" << endl;
        return(EXIT_FAILURE);
    }

    in.open(argv[1]);
    if( !in.is_open() ){
        cerr << "Unable to open file " << argv[1] << " for reading" << endl;
        return(EXIT_FAILURE);
    }

    out.open(argv[2]);
    if( !out.is_open() ){
        cerr << "Unable to open file " << argv[2] << " for writing" << endl;
        return(EXIT_FAILURE);
    }

    // A dictionary to hold all our strings
    Dictionary A;

    string line;
    int line_count = 1;
    // loop through and add each one to our dictionary 
    while( getline(in, line) )  {
        A.setValue(line, line_count++);
    }

    // print out dictionary
    out << A;
    out << A.pre_string();

    // close files
    in.close();
    out.close();

    return 0;
}
