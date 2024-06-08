#pragma once
#include <iostream>
#include <vector>
#include <cmath>




class slr {
public:
    double b0;
    double b1;

    slr(std::vector<double> trainData, std::vector<double> trainTarget);

    double mean(const std::vector<double>& v);

    double variance(const std::vector<double>& v, double mean_v);

    double covariance(const std::vector<double>& x, const std::vector<double>& y, double mean_x, double mean_y);

    void regressor(const std::vector<double>& x, const std::vector<double>& y);

};