#pragma once
#include "Variable.h"
#include<cmath>

std::vector<double> SNU(Size equationSize, Variable **equation, Variable** detEquation, std::vector<double> param, double e);
double MyPow(double a, int degree);
double ExecuteVariable(Variable &var, std::vector<double> param);
double determenant(double** mat, int size);
void transposition(double** mat, int size);
void reverse(double** mat, int size);
void showMat(double** mat, int size);
void showVec(std::vector<double> &v);
std::vector<double> Mul(double** mat, std::vector<double> x);