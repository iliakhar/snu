#include"SNU.h"

std::vector<double> SNU(Size equationSize, Variable** equation, Variable** devEquation, std::vector<double> param, double e) {
	std::vector<double> answer = param;
	int count = 0;
	double** W = new double * [equationSize.first];
	for (int i = 0; i < equationSize.first; i++)
		W[i] = new double[equationSize.first];

	double tmpVar, delta = 0;
	std::vector<double> Fx(equationSize.first);
	for (int i = 0; i < equationSize.first; i++)
		Fx[i] = 0;

	do{
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
		reverse(W, equationSize.first);
		std::cout << "\nW^-1:\n";
		showMat(W, equationSize.first);

		std::cout << "\nAnswer = X - W^-1 * F\n W^-1 * F = ";
		std::vector<double>tmpVec = Mul(W, Fx);
		showVec(tmpVec);
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

double MyPow(double a, int degree) {
	double answer = 1;
	for (int i = 0; i < abs(degree); i++)
		answer *= a;
	if (degree < 0)
		answer = (double)1 / answer;
	return answer;
}

double ExecuteVariable(Variable &var, std::vector<double> param) {
	double answer = 0, tmpAnswer = 1;
	for (int i = 0; i < var.getSize().first; i++) {
		for (int j = 0; j < param.size(); j++) {
			tmpAnswer *= pow(param[j], var(i, j + 1));
		}
		tmpAnswer *= var(i, 0);
		answer += tmpAnswer;
		tmpAnswer = 1;
	}
	return answer;
}

double determenant(double** mat, int size) {
	double k, answer = 1;
	double** newMat = new double* [size];
	for (int i = 0; i < size; i++)
		newMat[i] = new double[size];

	for (int i = 0; i < size; i++)
		for (int j = 0; j < size; j++)
			newMat[i][j] = mat[i][j];

	for (int i = 0; i < size - 1; i++) {
		for (int j = i + 1; j < size; j++) {
			k = newMat[j][i] / newMat[i][i];
			for (int l = i; l < size; l++)
				newMat[j][l] -= newMat[i][l] * k;
		}
	}

	for (int i = 0; i < size; i++)
		answer *= newMat[i][i];
	for (int i = 0; i < size; i++)
		delete[] newMat[i];
	return answer;
}

void transposition(double** mat, int size) {
	double tmp;

	for (int i = 0; i < size; i++)
		for (int j = size - 1; j > i; j--) {
			tmp = mat[i][j];
			mat[i][j] = mat[j][i];
			mat[j][i] = tmp;
		}
}

void reverse(double** mat, int size) {
	double** dopMat = new double* [size - 1];
	for (int i = 0; i < size; i++)
		dopMat[i] = new double[size - 1];

	double** detMat = new double* [size];
	for (int i = 0; i < size; i++)
		detMat[i] = new double[size];
	double det = determenant(mat, size);

	for (int i = 0; i < size; i++)
		for (int j = 0; j < size; j++) {
			for (int l = 0, ind1 = 0; l < size - 1; l++, ind1++) {
				if (l == i)
					ind1++;
				for (int k = 0, ind2 = 0; k < size - 1; k++, ind2++) {
					if (k == j)
						ind2++;
						dopMat[l][k] = mat[ind1][ind2];
				}
			}

			if ((i + j) % 2 == 0)
				detMat[i][j] = determenant(dopMat, size - 1);
			else
				detMat[i][j] = -determenant(dopMat, size - 1);
		}

	transposition(detMat, size);

	for (int i = 0; i < size; i++)
		for (int j = 0; j < size; j++)
			mat[i][j] = detMat[i][j] / det;

	for (int i = 0; i < size; i++)
		delete[] dopMat[i];
	for (int i = 0; i < size; i++)
		delete[] detMat[i];
}

void showMat(double** mat, int size) {

	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++)
			std::cout << mat[i][j] << "\t";
		std::cout << "\n";
	}
}

std::vector<double> Mul(double** mat, std::vector<double> x) {
	std::vector<double> answer(x.size());
	for (int i = 0; i < x.size(); i++)
		answer[i] = 0;

	for (int i = 0; i < x.size(); i++)
		for (int j = 0; j < x.size(); j++)
			answer[i] += mat[i][j] * x[j];
	return answer;
}

void showVec(std::vector<double> &v) {
	std::cout << "{";
	for (int i = 0; i < v.size(); i++) {
		std::cout << v[i];
		if (i != v.size() - 1)
			std::cout << ",\t";
	}
	std::cout << "}";
}