#define	_CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <stdio.h>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include <array>




int format(const char * filename, std::vector<std::array<float, 4>> feature, std::vector<std::string> flowertype) {

	std::string line;
	std::string substr;

	std::ifstream infile(filename);
	
	// Iterate over file line by line
	while (std::getline(infile, line)) {

		std::istringstream iss(line);

		// First 4 values in each line of csv are floats
		std::array<float, 4> tmpArray;
		for (int i = 0; i < 4; i++) {
			std::getline(iss, substr, ',');		// Get desired subportion of string
			tmpArray[i] = stof(substr);			// Convert string to float
		}
		feature.push_back(tmpArray);

		// Last (5th) value in line of csv is a string
		std::getline(iss, substr);
		flowertype.push_back(substr);
	}

	infile.close();

	return 0;
}




int main()
{
	std::vector<std::array<float, 4>> feature;
	std::vector<std::string> flowertype;

	// Move training data from csv to array.
	format("iris.data.txt", feature, flowertype);

	// Format test data here

	int correct = 0;
	int total = 0;

	// Put comparison code here


	printf("With %d samples, Results were %f%% correct\n", total, ((float)correct) / total * 100.0);
	printf("Formatting complete\n");
	std::cin.ignore();

	return 0;
}
