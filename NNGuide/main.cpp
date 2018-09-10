#define	_CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <stdio.h>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include <array>




int format(std::string filename, std::vector<std::array<float, 4>>& feature, std::vector<std::string>& flowerType) {

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
		flowerType.push_back(substr);
	}

	infile.close();
	std::cout << feature.size() << std::endl;

	return 0;
}


float dist(std::array<float, 4> point1, std::array<float, 4> point2) {
	float sum = 0;

	if (point1.size() != point2.size()) { std::cerr << "ERROR: Number of features in train and test data don't match!" << std::endl; }

	for (int i = 0; i < point1.size(); i++) {
		sum += powf((point1[i] - point2[i]), 2);
	}

	return sqrt(sum);
}




int main()
{
	const int K = 5;

	std::vector<std::array<float, 4>> trainFeature;
	std::vector<std::string> trainFlowerType;
	std::vector<std::array<float, 4>> testFeature;
	std::vector<std::string> testFlowerType;

	// Move training data from csv to array.
	format("iris.data.txt", trainFeature, trainFlowerType);
	format("test.txt", testFeature, testFlowerType);

	int correct = 0;
	int totalCases = 0;

	for (int testIndex = 0; testIndex < static_cast<int>(testFeature.size()); testIndex++) {
		// Compare all elements in test data and train data

		std::array<float, K> closestKDists;
		for (int i = 0; i < K; i++) {
			closestKDists[i] = 10'000;	// 10'000 is an arbitrarily high number
		}
		std::array<int, K> closestKTypes = { 0 };

		for (int trainIndex = 0; trainIndex < static_cast<int>(trainFeature.size()); trainIndex++) {
			
			float distance = dist(trainFeature[trainIndex], testFeature[testIndex]);
			int furthestIndex = 0;

			// Find the furthest of the K nearest cases
			for (int i = 1; i < K; i++) {
				if (closestKDists[furthestIndex] < closestKDists[i])
					furthestIndex = i;
			}

			// Check if the latest distance ranks in the top 5 closest ranks.
			if (distance < closestKDists[furthestIndex]) {
				closestKTypes[furthestIndex] = trainIndex;
				closestKDists[furthestIndex] = distance;
			}
		}

		// Count number of K votes which are correct.
		int maxVotes = 0;
		int maxVoteIndex = 0;
		std::cout << "Votes are ";
		for (int i = 0; i < K; i++) {
			std::cout << trainFlowerType[closestKTypes[i]] << ", ";

			// Count the number of votes that match vote i
			int voteCount = 0;
			for (int j = i + 1; j < K; j++) {
				if (trainFlowerType[closestKTypes[i]].compare(trainFlowerType[closestKTypes[j]]) == 0) {
					voteCount++;
				}
			}
			// Update maxVotes
			if(voteCount > maxVotes) {
				voteCount = maxVotes;
				maxVoteIndex = i;
			}
		}
		std::string prediction = trainFlowerType[closestKTypes[maxVoteIndex]];
		std::cout << " Prediction is " << prediction << " Answer is " << testFlowerType[testIndex] << std::endl;
		// If the flower type of the test case matches the most similar flower type from training data, the prediction was correct!
		if (prediction.compare(testFlowerType[testIndex]) == 0) {
			correct++;
			std::cout << "Test Case " << testIndex << " Correct!" << std::endl;
		}
		totalCases++;
	}

	// Calculate, print out, and display the results.
	if (totalCases <= 0) { std::cerr << "ERROR: total cases amounts to " << totalCases << std::endl; std::cin.ignore(); return -1; }
	std::cout << "Final Result: " << correct << " out of " << totalCases << " correct! Accuracy of " << static_cast<float>(correct) / totalCases * 100 << "%" << std::endl;
	std::cin.ignore();

	return 0;
}

