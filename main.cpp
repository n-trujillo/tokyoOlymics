/******************************************************************************

File: ArraysHW.cpp
Author: Prof. Lupoli & Andrew Nemec
Date: 2/16/2021
Section: 
E-mail: slupoli@tamu.edu
Description:
This file contains C++  code that will simulate data collected from a track 
event with 9 lanes. The code will sort the order, then display the results

Data File Information
name: data.csv
content: The csv file will contain data in the constant form of:
<Time (float)>,<Abbreviated Country (String)>,<Uniform number (int)>,<Lastname (String)>
32.7,USA,12,Moore
36.5,RUS,35,Polsley
45.8,ENG,73,Teale
52.34,CHN,14,Nemec
76.45,ITY,23,Lupoli     

* max 2 decimals

*******************************************************************************/

#include "parallel_tracks.h"

using std::cin; using std::cout; using std::endl;
using std::string; using std::getline; using std::ifstream;
using std::invalid_argument;

int main()
{
    // create arrays needed
    // SIZE is a global var = 9
    float timeArray[SIZE]; // times vals
    unsigned int rankArray[SIZE]; // rank vals
    unsigned int numberArray[SIZE]; // jersey vals
    string countryArray[SIZE]; // country vals
    string lastnameArray[SIZE]; // name vals
    string file;
	
    // prep all arrays
    prep_float_array(timeArray);
    prep_unsigned_int_array(rankArray);
    prep_unsigned_int_array(numberArray);
    prep_string_array(countryArray);
    prep_string_array(lastnameArray);

	// prompt until both the file and the contained data are valid

    bool valid = false;

    while (valid == false) {

	    try {
			cout << "Enter file name: "; // ask for file name
			getline(cin, file);
			get_runner_data(file, timeArray, countryArray, numberArray, lastnameArray); // run function
			valid = true;

		} catch (std::invalid_argument &e) {
			cout << "Invalid File: ";
			cout << e.what() << endl;
			valid = false;
		}

	}
	
	// determine ranking, notice the rank array receives the results

	get_ranking(timeArray, rankArray);
	print_results(timeArray, countryArray, lastnameArray, rankArray);


    return 0;
}

