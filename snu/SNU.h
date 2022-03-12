#pragma once
#include "Variable.h"
#include<cmath>

std::vector<double> SNU(Size equationSize, Variable **equation, Variable** detEquation, std::vector<double> param, double e, bool isGaus = false);
std::vector<double> SNUG(Size equationSize, Variable** equation, Variable** devEquation, std::vector<double> param, double e);
void dopsnu(double** W, std::vector<double> &tmpVec, std::vector<double> Fx);
void dopsnuGaus(double** W, std::vector<double>& tmpVec, std::vector<double> Fx);
double MyPow(double a, int degree);
double ExecuteVariable(Variable &var, std::vector<double> param);
double determenant(double** mat, int size);
void transposition(double** mat, int size);
void reverse(double** mat, int size);
void showMat(double** mat, int size);
void showVec(std::vector<double> &v);
std::vector<double> Mul(double** mat, std::vector<double> x);
void Gaus(double** mtrx, std::vector<double>& answer, bool isMod = false);
void swapLines(double** mtrx, int line1, int line2, double size);