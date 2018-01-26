#include "stats.h"

std::vector<double> numbers;

//This function reads floating point values from
//the input stream, and returns a list that
//contains all values read. This function must
//have no output. It must read from the input
//stream until the read fails, due to the end of
//file or bad data.
std::vector<double> getInput(std::istream& input_stream){
    double currentDouble;

    while(input_stream >> currentDouble){
            std::cout << "Enter another number (hit 'q' to quit):    ";
            numbers.push_back(currentDouble);
    }

    std::sort(numbers.begin(), numbers.end(), sortUsingGreaterThan);

//    for(int i = 0; i < numbers.size(); i++){
//        std::cout << numbers[i] << " ";
//    }

    return numbers;
}

//This function will calculate the total of all
//numbers in the vector and return the result.
//If there are no numbers, it should return 0.
double calculateSum(const std::vector<double>& numbers){
    double rValue = 0.0;

    if(numbers.empty()) {
            rValue = 0.0;
    }else {
        for (int i=0; i<=numbers.size(); i++) {
            rValue += numbers[i];
        }
    }
    return rValue;
}
//This function will calculate how many numbers
//are in the vector and return the result. If
//there are no numbers, it should return 0.
size_t calculateCount( const std::vector< double >& numbers ){
    size_t rValue = 0.0;

    if(numbers.empty()) {
        rValue = 0.0;
    }else {
        rValue = numbers.size();
    }
    return rValue;
}

//This function will calculate the arithmetic
//mean of the numbers and return the result. If
//there are no numbers, it should return 0.
double calculateAverage(const std::vector<double>& numbers){
    double rValue           = 0.0;
    double totalSum         = calculateSum(numbers);
    size_t totalItemsSize_t = calculateCount(numbers);
    int totalItems          = totalItemsSize_t;

    if(numbers.empty()) {
        rValue = 0.0;
    }else {
        rValue = totalSum / totalItems;
    }
    return rValue;
}

//This function will calculate the median of the
//numbers and return the result. If there are no
//numbers, it should return 0.
double calculateMedian( const std::vector<double>& numbers ){
    size_t totalItemsSize_t = calculateCount(numbers);
    int totalItems          = totalItemsSize_t;
    double rValue           = 0.0;

    if(totalItems % 2 == 0){
        double lowMedian  = numbers[(floor(totalItems / 2)) - 1];
        double highMedian = numbers[(floor(totalItems / 2))];
        rValue = (lowMedian + highMedian) / 2;
    }else{
        rValue = numbers[floor(totalItems / 2)];
    }
    return rValue;
}

//This function will calculate the minimum of
//the numbers and return the result. If there
//are no numbers, it should return 0.
double calculateMinimum( const std::vector< double >& numbers ){
    double rValue = 0.0;

    rValue = numbers.front();

    return rValue;
}

//This function will calculate the maximum of
//the numbers and return the result. If there
//are no numbers, it should return 0.
double calculateMaximum( const std::vector< double >& numbers ){
    double rValue = 0.0;

    rValue = numbers.back();

    return rValue;
}

bool sortUsingGreaterThan(double a, double b){
    return a < b;
}
