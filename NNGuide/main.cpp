#define	_CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <string>




int rmvWhiteSpace(char ** str) {
	int preceding = 0;

	for (int i = 0; i < (int)strlen(*str); i++) {
		if ((*str)[i] != ' ' && (*str)[i] != '\n') { break; }
		preceding++;
	}

	for (int i = strlen(*str) - 1; i > 0; i++) {
		if ((*str)[i] != ' ' && (*str)[i] != '\n') { break; }
		(*str)[i] = '\0';
	}
	*str = &(*str)[preceding];
	return 0;
}



int format(const char * filename, float feature[][4], char type[][20]) {
	//int format(const char * filename, float ** feature, char ** type) {

	FILE* file = fopen(filename, "r");

	char line[256];
	char s[2] = ",";
	char * token;
	int i = 0;

	while (fgets(line, 256, file)) //iterates through each line.
	{
		token = strtok(line, s);
		feature[i][0] = std::stof(token, 0);

		for (int j = 1; j< 5; j++)//gets 5 items from each line.
		{
			token = strtok(NULL, s);

			if (j < 4)
			{
				feature[i][j] = std::stof(token);
			}
			else {
				char ** tknptr = &token;
				rmvWhiteSpace(tknptr);
				strcpy(type[i], *tknptr);
				//printf("Type is %s\n", type[i]);
			}
		}
		i++;
	}

	fclose(file);

	return 0;
}


float dist(float * point1, float * point2) {
	float sum = 0;
	for (int i = 0; i < 4; i++) {
		sum += powf((point1[i] - point2[i]), 2);
	}

	return sqrt(sum);
}


int main()
{
	/*
	float ** feature = new float*[100];
	char ** type = new char*[100];
	float ** feature2 = new float*[50];
	char ** type2 = new char*[50];

	for (int i = 0; i < 100; i++) { feature[i] = new float[4]; }
	for (int i = 0; i < 100; i++) { type[i] = new char[20]; }
	for (int i = 0; i < 50; i++) { feature2[i] = new float[4]; }
	for (int i = 0; i < 50; i++) { type2[i] = new char[20]; }
	*/

	float feature[100][4];
	char type[100][20];
	float feature2[50][4];
	char type2[50][20];

	format("iris.data.txt", feature, type);
	format("test.txt", feature2, type2);

	int correct = 0;
	int total = 0;

	for (int i = 0; i < 50; i++) {
		float mindist[5] = { 10000, 10000, 10000, 10000, 10000 };
		int closestindex[5] = { 0,0,0,0,0 };

		for (int j = 0; j < 100; j++) {
			float distance = dist(feature[j], feature2[i]);
			for (int k = 0; k < 5; k++) {
				if (distance < mindist[k]) {

					mindist[k] = distance;
					printf("new mindist is %f\n", mindist[k]);
					closestindex[k] = j;
					break;
				}
			}
		}
		int score = 0;
		for (int k = 0; k < 5; k++) {
			if (strcmp(type2[i], type[closestindex[k]]) == 0) {
				score++;
			}
		}
		if (score > 2) {
			printf("Correct Guess! Voted %s,%s,%s,%s,%s\n", type[closestindex[0]], type[closestindex[1]], type[closestindex[2]], type[closestindex[3]], type[closestindex[4]]);
			correct++;
		}
		else {
			printf("Inorrect Guess! Actual:%s Voted %s,%s,%s,%s,%s\n", type2[i], type[closestindex[0]], type[closestindex[1]], type[closestindex[2]], type[closestindex[3]], type[closestindex[4]]);
		}

		total++;
	}

	printf("With %d samples, Results were %f%% correct\n", total, ((float)correct) / total * 100.0);


	printf("Formatting complete\n");
	std::cin.ignore();

	return 0;
}