#include "simplelinearregression.h"
#include <iostream>
#include <vector>
#include <cmath>

slr::slr(std::vector<double> trainData, std::vector<double> trainTarget) {

    regressor(trainData, trainTarget);
}

double slr::mean(const std::vector<double>& v) {
    double sum = 0.0;
    for (double val : v) {
        sum += val;
    }
    return sum / v.size();
}

double slr::variance(const std::vector<double>& v, double mean_v) {
    double var = 0.0;
    for (double val : v) {
        var += std::pow(val - mean_v, 2);
    }
    return var / v.size();
}

double slr::covariance(const std::vector<double>& x, const std::vector<double>& y, double mean_x, double mean_y) {
    double cov = 0.0;
    for (size_t i = 0; i < x.size(); ++i) {
        cov += (x[i] - mean_x) * (y[i] - mean_y);
    }
    return cov / x.size();
}

void slr::regressor(const std::vector<double>& x, const std::vector<double>& y) {
    double mean_x = mean(x);
    double mean_y = mean(y);

    b1 = covariance(x, y, mean_x, mean_y) / variance(x, mean_x);
    b0 = mean_y - b1 * mean_x;
}