#pragma once
#include<iostream>
#include<vector>
#include<utility>
#include<string>

using Size = std::pair<int, int>;

class Variable {
	Size varSize;
	std::vector<double> var;
public:
	Variable() :varSize(0, 0) {};
	Variable(std::vector<double> v) :varSize(1, v.size()) {
		var.insert(var.end(), v.begin(), v.end());
	}
	double MyAbs(double a) {
		return a >= 0 ? a : -a;
	}

	void Add(std::vector<double> v, int varCount) {
		if (var.size() != 0)
			var.reserve(v.size() + var.size());
		else
			var.reserve(v.size());
		varSize.first += varCount;
		varSize.second = v.size();
		var.insert(var.end(), v.begin(), v.end());
	}
	double& operator()(int row, int col) {
		return var[row * varSize.second + col];
	}
	void show() {
		for (int i = 0; i < varSize.first; i++) {
			if (var[i * varSize.second] > 0)
				std::cout << "+" << MyAbs(var[i * varSize.second]);
			else if (var[i * varSize.second] < 0)
				std::cout << var[i * varSize.second];
			for (int j = 1; j < varSize.second; j++) {
				if (var[i * varSize.second + j] != 0)
					std::cout << "X" << j << "^" << var[i * varSize.second + j];
			}
		}

	}
	std::vector<double> Derivative(int rowNum, int* varCount) {
		std::vector<double> deriv = var;
		//deriv.insert(deriv.end(), var.begin(), var.end());
		for (int i = 0; i < varSize.first; i++) {
			(*varCount)++;
			if (deriv[i * varSize.second + rowNum] != 0) {

				deriv[i * varSize.second] *= deriv[i * varSize.second + rowNum];
				deriv[i * varSize.second + rowNum]--;
			}
			else
				for (int j = 0; j < varSize.second; j++)
					deriv[i * varSize.second + j] = 0;
		}
		return deriv;
	}
	Size getSize() {
		return varSize;
	}
};