#ifndef TSP_H_INCLUDED
#define TSP_H_INCLUDED

#include <vector> //std::vector
#include <iostream> //std::cin

class Graph{
    public:

    //vector of verticies and edges. Populated in readGraph()
    std::vector<std::vector<double>> mVerticiesAndEdgesVec;

    //vector of a single cycle. Calculated in populateACycle()
    std::vector<int> mASingleCycleVec;

    //cost of the cycle from mASingleCycleVec
    double mCost;

    //quality of the cycle from mASingleCycleVec
    double mQuality;

    //vector used to output the cycle information. Populated in calcOutput
    std::vector<double> mOutputVec;

    //min and max weights stored here so they are only calcualted once
    double mMinPossibleWeight;
    double mMaxPossibleWeight;

    //constructor and destructor
    Graph();
    virtual ~Graph();

    void readGraph(std::istream& inputStream);
    void populateACycle();
    void calcCost();
    double calcMinWeight();
    double calcMaxWeight();
    void calcQuality();
    void calcOutput();
};

#endif // TSP_H_INCLUDED
