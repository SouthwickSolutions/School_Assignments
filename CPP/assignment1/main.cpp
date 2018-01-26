#include "stats.h"
#include "stats.cpp"//take out when using g++

int main()
{
    std::cout << "Enter a double to add to the numbers list: ";
    std::vector<double> numbers = getInput(std::cin);
    std::cout << std::endl;

    //presents the total of all numbers input
    std::cout << "The total for all of your numbers is: ";
    double numbersSum = calculateSum(numbers);
    std::cout << numbersSum;
    std::cout << std::endl;

    //presents the total number of numbers
    std::cout << "The total number of numbers is:       ";
    size_t numbersTotal = calculateCount(numbers);
    std::cout << numbersTotal;
    std::cout << std::endl;

    //presents the average of your numbers
    std::cout << "The average of your numbers is:       ";
    double numbersAverage = calculateAverage(numbers);
    std::cout << numbersAverage;
    std::cout << std::endl;

    //presents the median of your numbers
    std::cout << "The median of your numbers is:        ";
    double numbersMedian = calculateMedian(numbers);
    std::cout << numbersMedian;
    std::cout << std::endl;

    //presents the minumum of your numbers
    std::cout << "The minimum of your numbers is:       ";
    double numbersMinimum = calculateMinimum(numbers);
    std::cout << numbersMinimum;
    std::cout << std::endl;

    //presents the maximum of your numbers
    std::cout << "The maximum of your numbers is:       ";
    double numbersMaximum = calculateMaximum(numbers);
    std::cout << numbersMaximum;
    std::cout << std::endl;

    std::cout << "The collection of numbers is:        ":
    double collectionOfNumbers = calculateCollection(numbers);

    return 0;
}
