//
//  HeatTransferComputation.cpp
//  HeatEquation
//
//  Created by satori on 6/8/16.
//  Copyright © 2016 rinnex. All rights reserved.
//

#include "HeatTransferComputation.hpp"
#include <string>
#include <cstdio>

HeatTransferComputation::HeatTransferComputation(const Settings & settings) : settings(settings) {
    dx = settings.width / settings.N;
    dy = settings.heigh / settings.N;
    solution = MATRIX(settings.N, settings.timeIterations + 1);
    for (int i = 0; i < settings.N; i++) {
        for (int j = 0; j < settings.N; j++) {
            solution[i][j][0] = settings.initialDistribution(i * dx, j * dy);
        }
    }
}


void HeatTransferComputation::outputSolution() {
    for (int st = 0; st <= settings.timeIterations; st++) {
        std::string filename = "plot" + std::to_string(st);
        FILE * file = fopen(filename.c_str(), "w");
        for (int i = 0; i < settings.N; i++) {
            for (int j = 0; j < settings.N; j++) {
                fprintf(file, "%f %f %f\n", dx * i, dy * j, solution[i][j][st]);
            }
        }
        fclose(file);
        
    }
}

void HeatTransferComputation::eval() {
    for (int st = 1; st <= settings.timeIterations; st++) {
        for (int i = 1; i < settings.N-1; i++) {
            for (int j = 1; j < settings.N-1;j++) {
                solution[i][j][st] = solution[i][j][st-1] + settings.dt *
                (solution[i][j-1][st-1] - 2 * solution[i][j][st-1] + solution[i][j+1][st-1]) / (dy * dy)
                + settings.dt
                * (solution[i-1][j][st-1] - 2 * solution[i][j][st-1] + solution[i+1][j][st-1]) / (dx * dx)
                + settings.dt * settings.source(i * dx, j * dy, solution[i][j][st-1], (st-1) * settings.dt);
            }
        }
        for (int j = 0; j < settings.N; j++) {
            double A1 = settings.leftBorderCondition.A;
            double B1 = settings.leftBorderCondition.B;
            solution[0][j][st] = (A1 * solution[1][j][st-1] + dx * settings.leftBorderCondition.borderFunc(settings.dt * st)) / (A1 + dx  * B1);
            double A2 = settings.rightBorderCondition.A;
            double B2 = settings.rightBorderCondition.B;
            solution[settings.N-1][j][st] = (A2 * solution[settings.N-2][j][st-1] + dx * settings.rightBorderCondition.borderFunc(settings.dt * st)) / (A2 + dx * B2);
        }
        for (int i = 0; i < settings.N; i++) {
            double A1 = settings.topBorderCondition.A;
            double B1 = settings.topBorderCondition.B;
            solution[i][0][st] = (A1 * solution[i][1][st-1] + dx * settings.topBorderCondition.borderFunc(settings.dt * st)) / (A1 + dx  * B1);
            double A2 = settings.bottomBorderCondition.A;
            double B2 = settings.bottomBorderCondition.B;
            solution[i][settings.N-1][st] = (A2 * solution[i][settings.N-2][st-1] + dx * settings.bottomBorderCondition.borderFunc(settings.dt * st)) / (A2 + dx * B2);
        }
    }
}
