#include<iostream>
#include<fstream>
#include<vector>
#include<utility>
#include<string>
#include"Variable.h"
#include"SNU.h"


int main() {
	Size equationSize = { 2, 3 };

	Variable** equation = new Variable * [equationSize.first];
	for (int i = 0; i < equationSize.first; i++)
		equation[i] = new Variable[equationSize.second];

	Variable** devEquation = new Variable * [equationSize.first];
	for (int i = 0; i < equationSize.first; i++)
		devEquation[i] = new Variable[equationSize.first];

	equation[0][0].Add(std::vector<double>{1, 2, 0}, 1);
	equation[0][1].Add(std::vector<double>{1, 0, 3}, 1);
	equation[0][2].Add(std::vector<double>{-4, 0, 0}, 1);
	equation[1][0].Add(std::vector<double>{1, 1, -1}, 1);
	equation[1][1].Add(std::vector<double>{-2, 0, 0}, 1);
	equation[1][2].Add(std::vector<double>{0, 0, 0}, 1);

	for (int i = 0; i < equationSize.first; i++) {
		for (int j = 0; j < equationSize.second; j++)
			equation[i][j].show();
		std::cout << "=0\n";
	}
	
	for (int i = 0; i < equationSize.first; i++)
		for (int j = 0; j < equationSize.second; j++)
			for (int k = 1; k < equationSize.first + 1; k++) {
				int varCount = 0;
				std::vector<double> deriv = equation[i][j].Derivative(k, &varCount);
				devEquation[i][k - 1].Add(deriv, varCount);
			}
			
	std::cout << "\n";
	for (int i = 0; i < equationSize.first; i++) {
		for (int j = 0; j < equationSize.first; j++) {
			devEquation[i][j].show();
			std::cout << "\t";
		}
		std::cout << "\n";
	}

	SNU(equationSize, equation, devEquation, std::vector<double>{2, 1}, 0.01, true);

	for (int i = 0; i < equationSize.first; i++) {
		delete[] equation[i];
		delete[] devEquation[i];
	}
		

}