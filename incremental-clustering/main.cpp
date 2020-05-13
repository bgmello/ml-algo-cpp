#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "IncrementalClustering.h"

int main(int argc, char* argv[])
{
	double alpha;
	int n;

	std::string fileName;
	std::vector<std::string> sentences;
	std::ifstream inputFile;
	std::ofstream outputFile;

	if(argc==1)
	{
		std::cout << "No input file passed" << std::endl;
		return 0;
	}

	else if(argc==2)
	{

		std::cout << "No n passed, using 1" << std::endl;
		n = 1;
		std::cout << "No alpha passed, using 0.4" << std::endl;
		alpha = 0.4;

		fileName = argv[1];
	}

	else if(argc==3){
		std::cout << "No alpha passed, using 0.4" << std::endl;
		alpha = 0.4;
		n = std::atoi(argv[1]);
		fileName = argv[2];
	}

	else{
		n = std::atoi(argv[1]);
		alpha = std::atof(argv[2]);
		fileName = argv[3];
	}

	inputFile.open(fileName);
	outputFile.open(fileName+".output");

	std::string line;

	while(std::getline(inputFile, line))
	{
		sentences.push_back(line);
	}

	IncrementalClustering inc(alpha, n);

	std::vector<int> clusters = inc.fit_predict(sentences);

	for(int i=0;i<clusters.size();i++)
	{
		outputFile << sentences[i] << '\t' << clusters[i];
		outputFile << std::endl;
	}

	inputFile.close();
	outputFile.close();
	
	return 0;
}