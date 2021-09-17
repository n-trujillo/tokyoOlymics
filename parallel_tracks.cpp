#include "parallel_tracks.h"

//-------------------------------------------------------
// Name: is_valid_number
// PreCondition:  a string that needs to be checked as a valid competition 
// number (non-negative int)
// PostCondition: returns TRUE if string is only made up of numeric chars 0-9
//---------------------------------------------------------
bool is_valid_number(const std::string& str) {

	bool valid = false;

	for(unsigned int i = 0; i < str.size(); i ++) {
		int isDigit = isdigit(str.at(i));
		if (isDigit != 0) { // if valid digit
			valid = true;
		} else { // if at any point not a valid digit
			return false; // false
		}
	}

	return valid;
}

//-------------------------------------------------------
// Name: is_valid_time
// PreCondition:  a string that needs to be checked as a valid time 
// (non-negative float)
// PostCondition: returns TRUE if string is only made up of numeric chars 
// 0-9 or '.'
//---------------------------------------------------------
bool is_valid_time(const std::string& str) {

	bool valid = false;
	int decimalCount = 0;

	if (str == ".") { // if its just a decimal
		return false; // not a number
	}

	for(unsigned int i = 0; i < str.size(); i ++) {
		int isDigit = isdigit(str.at(i));

		if (str.at(i) == '.') {
			decimalCount ++;
		}

		if (isDigit != 0 || str.at(i) == '.') { // if valid digit or a decimal
			valid = true;

			if (decimalCount > 1) { // if decimal count is bigger than 1
				return false; // not a good number
			}

		} else { // if at any point not valid
			return false; // false
		}
	}

	return valid;
}

//-------------------------------------------------------
// Name: is_valid_country
// PreCondition:  a string that needs to be checked as a valid country (std::string)
// PostCondition: returns TRUE if string is made of exactly 3 capital chars A-Z
//---------------------------------------------------------
bool is_valid_country(const std::string& str) {

	bool valid = false;

	for(unsigned int i = 0; i < str.size(); i ++) {
		int isUpper = isupper(str.at(i));
		if (str.size() == 3 && isUpper != 0) { // if valid upper char and size is 3
			valid = true;
		} else { // if at any point not a valid digit
			return false; // false
		}
	}

	return valid;
	
}

//-------------------------------------------------------
// Name: is_valid_name
// PreCondition:  a string that needs to be checked as a valid name (std::string)
// PostCondition: returns TRUE if string is made of letters A-Z, a-z, and ' '
//---------------------------------------------------------
bool is_valid_name(const std::string& str) {
	bool valid = false;

	for (unsigned int i = 0; i < str.size(); i++) {
		bool check1 = isupper(str.at(i));
		bool check2 = isalpha(str.at(i));
			if (check1 || check2 || str.at(i) == ' ') {
				valid = true;
			} else {
				return false; // if at any point it isnt one of the valid charicaters then exit as false
			}
	}

	return valid; // after iterating through the entire 
	
}

//-------------------------------------------------------
// Name: get_runner_data
// PreCondition:  the prepped parallel arrays , and a legit filename is pass
// PostCondition: all arrays contain data from the csv file given
//---------------------------------------------------------
void get_runner_data( const std::string& file, float *timeArray, std::string* countryArray, 
		unsigned int* numberArray, std::string *lastnameArray) 
{
	if (file.size() < 4 || file.substr(file.length()-4, 4) != ".csv") throw std::invalid_argument("File not CSV file");
    // using syntax from iostreams notes (examples)
	
	std::ifstream infile;
	
	infile.open(file);
	
	if (!infile.is_open()) {
		throw std::invalid_argument("Cannot open file");
	}
	
    // all data abot to be read in from the CSV file 
    std::string line; // reading the line from the file
	float time; // float version of time
	std::string strTime; // string version of time
	std::string country;
	std::string strNumber; // string version of number
    unsigned int number;
    std::string lname;
    
	int i = 0; // index that values are bout to be placed
	
    // get whole line to be broken up later
    while(getline(infile, line))
	{
		// convert line to istringstream in order to break it up
		std::istringstream sin(line);
		
		// get data, piece by piece using the , as the delimiter
		// if data missing, throw exception
		if (!getline(sin, strTime, ',')) 
			throw std::invalid_argument("File missing data");
		// if strTime is not a valid (non-negative) float, throw exception
		if (!is_valid_time(strTime)) 
			throw std::invalid_argument("File contains invalid data (time)");	//Customize to time?
		// THEN convert to FLOAT (since not a string)
		time = std::stof (strTime);	
		
		// if data missing, throw exception
		if (!getline(sin, country, ',')) 
			throw std::invalid_argument("File missing data");
		// if country is not a valid country name (3 uppercase char), throw exception
		if (!is_valid_country(country)) 
			throw std::invalid_argument("File contains invalid data (country)");
		
		// if data missing, throw exception
		if (!getline(sin, strNumber, ',')) 
			throw std::invalid_argument("File missing data");
		// if strNumber is not a valid (non-negative) int, throw exception
		if (!is_valid_number(strNumber)) 
			throw std::invalid_argument("File contains invalid data (number)");	// Customize to number?
		// THEN convert to FLOAT (since not a string)
		number = std::stoi (strNumber); // this is NOT perfect!! there is a long int version, but...
		
		// last line does not have a ,
		// if data missing, throw exception
		if (!getline(sin, lname)) throw std::invalid_argument("File missing data");
		// if lname is not a valid name (alphabet chars and ' '), throw exception
		if (!is_valid_name(lname)) throw std::invalid_argument("File contains invalid data (name)");
		
		// assign values to arrays
		timeArray[i] = time;
		countryArray[i] = country;
		numberArray[i] = number;
		lastnameArray[i] = lname;
		i++; // increment to fill next index in the parallel arrays
		
    }
	
    infile.close();
    
}

//-------------------------------------------------------
// Name: prep_float_array
// PreCondition:  a float arrays is pass in
// PostCondition: data in the array is 'zeroed' out
//---------------------------------------------------------
void prep_float_array(float *ary)
// making sure all values within the array are set to 0.0;
{
	for (unsigned int i = 0; i < SIZE ; i++) { // go through each element in the array
		ary[i] = 0.0f; // set it to 0.0f
	}
   
} // done

//-------------------------------------------------------
// Name: prep_float_array
// PreCondition:  a float arrays is pass in
// PostCondition: data in the array is 'zeroed' out
//---------------------------------------------------------
void prep_unsigned_int_array(unsigned int *ary)
// making sure all values within the array are set to 0;
{
	for (unsigned int i = 0; i < SIZE; i++) { // go through each element in the array
		ary[i] = 0; // set it to 0
	}
	
}

//-------------------------------------------------------
// Name: prep_string_array
// PreCondition:  a string arrays is pass in
// PostCondition: data in the array is "N/A" out to determine if
// a value has changed
//---------------------------------------------------------
void prep_string_array(std::string *ary)
// making sure all values within the array are set to "N/A";
{
	for (unsigned int i = 0; i < SIZE; i++) { // go through each element in the array
		ary[i] = "N/A"; // set to N/A
	}
	
}

//-------------------------------------------------------
// Name: get_ranking
// PreCondition:  just the time array is passed in, and has valid data
// PostCondition: after a very ineffiect nested loop to determine the placements 
// and places the ranks in a new array. That new array is returned
//---------------------------------------------------------
void get_ranking(const float *timeArray, unsigned int *rankArray)
{
	unsigned int j  = 1; // rank number
	unsigned int i = 0;
	float prevRank = 0.0f; // used to retroactive comparision
	float hold = 1000; // some large number to start the comparison
	int holdIndex = 0;


	for (j = 1; j <= SIZE; j ++) { // for each rank

		hold = 1000; // reset the hold

		for (i = 0; i < SIZE; i ++) { // iterate though entire time array

			if (timeArray[i] < hold && timeArray[i] > prevRank) { // greater than prevRank and less than hold
				hold = timeArray[i]; // update the hold value
				holdIndex = i; // update the hold index
			}

			if (i == (SIZE - 1)) { // at the end of the timeArray
				rankArray[holdIndex] = j; // go to the index of the hold and set it to its according rank
				prevRank = hold; // update the previous rank value 
			}

		}

	}
	
}


//-------------------------------------------------------
// Name: print_results
// PreCondition:  almost all parallel arrays are passed in and have valid data
// PostCondition: after a very ineffiect nested loop to determine the ranks
// it then displays then along with a delta in time from the start
//---------------------------------------------------------
void print_results(const float *timeArray, const std::string* countryArray,
		const std::string *lastnameArray, const unsigned int* rankArray)
{

	std::cout << "Final results!!";
	std::cout << std::setprecision(2) << std::showpoint << std::fixed << std::endl;
	float best_time = 0.0f;
		
	// print the results, based of rank, but measure the time difference_type
	for(unsigned int j = 1; j <= SIZE; j++)
	{
		
		// go thru each array, find who places in "i" spot
		for(unsigned int i = 0; i < SIZE; i++)
		{
			if(rankArray[i] == 1) // has to be a better way, but need the starting time
			{
				best_time = timeArray[i];
			}
			
			
			if(rankArray[i] == j) // then display this person's data
			{
				// this needs percision display
				std::cout << "[" << j << "]  " << timeArray[i] << " " << std::setw(15) << std::left << lastnameArray[i] << "\t" << "(" << countryArray[i] << ")  +" << (timeArray[i] - best_time) << std::endl; 
			}
			
		}
	}	
}
