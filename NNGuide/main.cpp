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
			}
		}
		i++;
	}

	fclose(file);

	return 0;
}



int main()
{
	float feature[100][4];
	char type[100][20];

	format("iris.data.txt", feature, type);

	// Format test data here

	int correct = 0;
	int total = 0;

	// Put comparison code here


	printf("With %d samples, Results were %f%% correct\n", total, ((float)correct) / total * 100.0);
	printf("Formatting complete\n");
	std::cin.ignore();

	return 0;
}