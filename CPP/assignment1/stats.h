#ifndef STATS_H_INCLUDED
#define STATS_H_INCLUDED

#include <vector>
#include <iostream>
#include <cstdlib>
#include <math.h>   //for floor()
#include<algorithm> //for std::sort
//functions
std::vector<double> getInput(std::istream& input_stream);
double calculateSum(const std::vector<double>& numbers);
size_t calculateCount(const std::vector<double>& numbers);
double calculateAverage(const std::vector<double>& numbers);
double calculateMedian(const std::vector<double>& numbers);
double calculateMinimum(const std::vector<double>& numbers);
double calculateMaximum(const std::vector<double>& numbers);


//personal functions
bool sortUsingGreaterThan(double a, double b);

#endif // STATS_H_INCLUDED
