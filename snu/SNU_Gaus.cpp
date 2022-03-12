#include"SNU.h"

std::vector<double> SNUG(Size equationSize, Variable** equation, Variable** devEquation, std::vector<double> param, double e) {
	std::vector<double> answer = param;
	int count = 0;
	double** W = new double* [equationSize.first];
	for (int i = 0; i < equationSize.first; i++)
		W[i] = new double[equationSize.first + 1];

	double tmpVar, delta = 0;
	std::vector<double> Fx(equationSize.first);
	for (int i = 0; i < equationSize.first; i++)
		Fx[i] = 0;

	do {
		count++;
		delta = 0;
		for (int i = 0; i < answer.size(); i++)
			std::cout << "\nX" << i + 1 << " = " << answer[i];
		std::cout << "\n";
		for (int i = 0; i < equationSize.first; i++) {
			std::cout << "\nF(" << answer[i] << ") = ";
			for (int j = 0; j < equationSize.second; j++)
				equation[i][j].show();
			std::cout << " = ";
			for (int j = 0; j < equationSize.second; j++) {
				tmpVar = ExecuteVariable(equation[i][j], answer);
				Fx[i] += tmpVar;
				std::cout << tmpVar << " + ";
			}
			std::cout << " = " << Fx[i];
		}
		std::cout << "\n\n";
		for (int i = 0; i < equationSize.first; i++) {
			for (int j = 0; j < equationSize.first; j++) {
				std::cout << "W[" << i << "," << j << "] = ";
				devEquation[i][j].show();
				std::cout << " = ";
				W[i][j] = ExecuteVariable(devEquation[i][j], answer);
				std::cout << W[i][j] << ";\t\t";
			}
			std::cout << "\n";
		}
		std::cout << "\nF = ";
		showVec(Fx);
		std::cout << "\n\nW:\n";
		showMat(W, equationSize.first);

		for (int i = 0; i < equationSize.first; i++)
			W[i][equationSize.first] = Fx[i];
		std::vector<double>tmpVec(equationSize.first);
		Gaus(W, tmpVec);


		std::cout << "\nAnswer = ";
		showVec(answer);
		std::cout << " - ";
		showVec(tmpVec);
		for (int i = 0; i < answer.size(); i++)
			tmpVec[i] = answer[i] - tmpVec[i];
		std::cout << " = ";
		showVec(tmpVec);
		std::cout << "\n";

		for (int i = 0; i < answer.size(); i++) {
			double tmp;
			if (abs(tmpVec[i] - answer[i]) > delta)
				delta = abs(tmpVec[i] - answer[i]);
			tmp = answer[i];
			answer[i] = tmpVec[i];
			tmpVec[i] = tmp;
		}
		std::cout << "delta = " << delta << "\n";
		for (int i = 0; i < 50; i++)
			std::cout << "_";
		std::cout << "\n";

	} while (delta > e);
	std::cout << "N = " << count << "\n";

	for (int i = 0; i < equationSize.first; i++)
		delete[] W[i];
	return answer;
}