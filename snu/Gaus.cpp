#include "SNU.h"

void Gaus(double** mtrx, std::vector<double>& answer, bool isMod) {
    double k;
    int height = answer.size();


    for (int i = 0; i < height; i++) {
        if (isMod) {
            int maxLine = -1;
            for (int j = i + 1; j < height; j++)
                if (abs(mtrx[j - 1][i]) < abs(mtrx[j][i]))
                    maxLine = j;
            if (maxLine != -1) {
                swapLines(mtrx, i, maxLine, answer.size());
                //std::cout << "Swap lines " << i + 1 << " and " << maxLine + 1 << "\n";
                //mtrx.show();
                //std::cout << "\n";
            }

        }

        k = mtrx[i][i];
        for (int j = i; j <= height; j++) {
            mtrx[i][j] /= k;
        }
        for (int j = 0; j < height; j++) {
            k = mtrx[j][i];
            if (j != i)
                for (int l = i; l <= height; l++) {
                    mtrx[j][l] -= mtrx[i][l]* k;
                }
        }
        //mtrx.show();
        //std::cout << "\n";
    }
    //std::cout << "\n";
    //mtrx.show();
    for (int i = 0; i < height; i++)
        answer[i] = mtrx[i][height];
}

void swapLines(double** mtrx, int line1, int line2, double size) {
    double tmp;
    for (int i = 0; i < size; i++) {
        tmp = mtrx[line1][i];
        mtrx[line1][i] = mtrx[line2][i];
        mtrx[line2][i] = tmp;
    }
}