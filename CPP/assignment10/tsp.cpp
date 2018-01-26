//The program should:
//1- read the graph description from std::cin.
//2- create an ordering of the cities that includes every city exactly once,
//      a cycle. (For example, 12345)
//3- calculate the weight of the cycle
//4- calculate the quality of the cycle
//5- display (to std::cout) the cycle (the cities in the order you selected),
//the weight and the quality.

#include "tsp.h"





//everything is handled inside the constructor
Graph::Graph(){
    readGraph(std::cin);
    populateACycle();
    calcCost();
    calcQuality();
    calcOutput();
};





Graph::~Graph(){};





//reads the file into mVerticiesAndEdgesVec
void Graph::readGraph(std::istream& inputStream){
    int n; //number of cities
    int i; //iterator
    int from, to; //cities of current line from file input
    double weight; //distance between cities

    std::vector<double> innerVector; //vector item to put inside mVerticiesAndEdgesVec

    //grabs cities (first line of input file) and stores it in innerVector
    inputStream >> n;
    innerVector.push_back(n);

    //puts innerVector inside my vector of vectors.
    mVerticiesAndEdgesVec.push_back(innerVector);

    //this for loop grabs the rest of the lines from the input file, puts them
    //in the innerVector and put that innerVector inside my vector of vectors
    for(i = 0; i <= (n*(n-1)); i++){
        //clears vector for reuse
        innerVector.clear();

        //grabs line and stores it in individual variables
        inputStream >> from >> to >> weight;

        //puts those variables in innerVector
        innerVector.push_back(from);
        innerVector.push_back(to);
        innerVector.push_back(weight);

        //stores innerVector in main vector
        mVerticiesAndEdgesVec.push_back(innerVector);

        //simple print statement that shows vector information is stored correctly
        //comment this statement out in your final code
        // std::cout << mVerticiesAndEdgesVec[i][0] << ' '
        //           << mVerticiesAndEdgesVec[i][1] << ' '
        //           << mVerticiesAndEdgesVec[i][2] << '\n';
    }
}





//populates a single cycle; 1 thru n (in order)
void Graph::populateACycle(){
    int i;

    //grabs the number of cities so this method knows how big to make the cycle
    int numOfCities = mVerticiesAndEdgesVec[0][0];

    //populates mASingleCycleVec with numbers 1 thru numOfCities (in order)
    for(i = 1; i <= numOfCities; i++){
        mASingleCycleVec.push_back(i);
    }
}





//calculates the weight/cost of a single cycle
void Graph::calcCost(){
    int i, j, k; //iterators
    mCost = 0.0; //initializes this class member

    //calculates the cost of a single cycle and stores it in mCost
    for(i = 0; i < mASingleCycleVec.size(); i++){
        for(j = 1; j < mVerticiesAndEdgesVec.size(); j++){
            if(mASingleCycleVec[i] == mVerticiesAndEdgesVec[j][0] &&
               mASingleCycleVec[i+1] == mVerticiesAndEdgesVec[j][1]){
                   mCost += mVerticiesAndEdgesVec[j][2];
            }
        }
        //don't forget to add the last edge too. Added in this if statement...
        if(i + 1 == mASingleCycleVec.size()){
            for(k = 1; k < mVerticiesAndEdgesVec.size(); k++){
                if(mASingleCycleVec.back() == mVerticiesAndEdgesVec[k][0] &&
                   mASingleCycleVec[0] == mVerticiesAndEdgesVec[k][1]){
                       mCost += mVerticiesAndEdgesVec[k][2];
                }
            }
        }
    }
}





//calculates the minimum possible weight
//minimum possible weight is the cost of the lightest edge multiplied by n.
double Graph::calcMinWeight(){
    int i;
    int numCities = mVerticiesAndEdgesVec[0][0];
    double lightestEdge = mVerticiesAndEdgesVec[1][2]; //lightestEdge starts with first value
    double comparingEdge; //current edge
    double minimumPossibleWeight;

    for(i = 1; i < mVerticiesAndEdgesVec.size(); i++){
        comparingEdge = mVerticiesAndEdgesVec[i][2];
        if(comparingEdge < lightestEdge){
            lightestEdge = comparingEdge;
        }
    }
    minimumPossibleWeight = lightestEdge * numCities;
    return minimumPossibleWeight;
}





//calculates the maximum possible weight
//maximum possible weight is the cost of the heaviest edge multiplied by n.
double Graph::calcMaxWeight(){
    int i;
    int numCities = mVerticiesAndEdgesVec[0][0];
    double heaviestEdge = mVerticiesAndEdgesVec[1][2]; //heaviestEdge starts with first value
    double comparingEdge; //current edge
    double maximumPossibleWeight;

    for(i = 1; i < mVerticiesAndEdgesVec.size(); i++){
        comparingEdge = mVerticiesAndEdgesVec[i][2];
        if(comparingEdge > heaviestEdge){
            heaviestEdge = comparingEdge;
        }
    }
    maximumPossibleWeight = heaviestEdge * numCities;
    return maximumPossibleWeight;
}





//calculates the quality of the cycle
void Graph::calcQuality(){
    int i; //iterator
    double minPossibleWeight = calcMinWeight();
    double maxPossibleWeight = calcMaxWeight();
    double costOfCycle = mCost;

    mQuality = 1 - (costOfCycle - minPossibleWeight)/
               (maxPossibleWeight - minPossibleWeight);
}





//outputs all of the calculated information
void Graph::calcOutput(){
    int i;

    //puts the cycle from mASingleCycleVec into mOutputVec
    for(i = 1; i <= mASingleCycleVec.size(); i++){
        mOutputVec.push_back(i);
    }

    //puts the cost and quality in mOutputVec
    mOutputVec.push_back(mCost);
    mOutputVec.push_back(mQuality);

    //prints information to screen
    for(i = 0; i < mOutputVec.size(); i++){
        std::cout << mOutputVec[i] << ' ';
    }
    std::cout << std::endl;
}
