#include <algorithm> //std::random_shuffle
#include <iostream> //for debugging
#include <cstdlib> // for srand and rand
#include <ctime>  // std::time

#include "TSPGOOD.h"

TSPGOOD::TSPGOOD()
    : Graph(){

    //reads file into mVerticiesAndEdgesVec
    readGraph(std::cin);

    //sets seed to be random every time the program is run
    srand(time(0));

    //populates a cycle for use in finding neighbor cycles
    populateARandomCycle();

    //calculates the min and max weight so we only have to do it once
    mMinPossibleWeight = calcMinWeight();
    mMaxPossibleWeight = calcMaxWeight();
}





TSPGOOD::~TSPGOOD(){};





//populates a random cycle and stores it in mASingleCycleVec
void TSPGOOD::populateARandomCycle(){

    //populates a cycle; 1 thru n
    populateACycle();

    //uses random_shuffle to mix mASingleCycleVec
    std::random_shuffle(mASingleCycleVec.begin()+1, mASingleCycleVec.end());

    //debugging********************
    //prints cycle
    //for(int i = 0; i < mASingleCycleVec.size(); i++){
    //    std::cout << mASingleCycleVec[i] << ' ';
    //}
    //std::cout << std::endl;
}





//generates a neighbor cycle by switching indexes of mASingleCycleVec
void TSPGOOD::populateANewCycle(){

    //generate the random indexes to be switched
    int range = mASingleCycleVec.size() - 1;
    int mFirstIndex = rand() % range + 1;
    int mSecondIndex = mFirstIndex;

    //makes sure second number is not the same as the first number
    while(mSecondIndex == mFirstIndex){
        mSecondIndex = rand() % range + mASingleCycleVec[0];
    }
    //debugging**********************
    //prints what is to be switched
    //std::cout << "Indexes to be switched: " << mFirstIndex << ' ' << mSecondIndex << std::endl;
    //std::cout << "Index values to be switched: " << mASingleCycleVec[mFirstIndex] << ' ' << mASingleCycleVec[mSecondIndex] << std::endl;

    //switches the vertices, uses local variables so as not to change the indexes in case you need to switch the vectors back
    int localFirstIndex = mFirstIndex;
    int localSecondIndex = mSecondIndex;
    int firstNumber = mASingleCycleVec[localFirstIndex];
    mASingleCycleVec[localFirstIndex] = mASingleCycleVec[localSecondIndex];
    mASingleCycleVec[localSecondIndex] = firstNumber;

    //debugging********************
    //prints cycle
    //for(int i = 0; i < mASingleCycleVec.size(); i++){
    //    std::cout << mASingleCycleVec[i] << ' ';
    //}
    //std::cout << std::endl;
}





//switches back the cycles if they are not better quality
void TSPGOOD::switchBackCycles(){
    int firstNumber = mASingleCycleVec[mSecondIndex];
    mASingleCycleVec[mSecondIndex] = mASingleCycleVec[mFirstIndex];
    mASingleCycleVec[mFirstIndex] = firstNumber;
}




//finds a cycle with a quality of over 0.80
void TSPGOOD::findAGoodQuality(){
    //called to initialize mFirstIndex and mSecondIndex
    populateANewCycle();
    bool firstTime = true;
    double goodQuality = 0.80;
    mQuality = 0.0;

    //pseudocode for while loop algorithm-
    //while quality < .8
    //  calc quality of current cycle
    //  if quality < .8:
    //      generate a neighbor cycle
    //      repeat
    //  if quality > .8:
    //      calc cost
    //output to screen
    while(mQuality < goodQuality){
        std::cout << mQuality << std::endl;
        calcQuality();
        if(mQuality < goodQuality){
            //if(firstTime == false){
            //    switchBackCycles();
            //}
            populateANewCycle();
            //firstTime = false;
            continue;
        }else if(mQuality > goodQuality){
            break;
        }
    }
    //debugging********************
    //prints cycle
    //for(int i = 0; i < mASingleCycleVec.size(); i++){
    //    std::cout << mASingleCycleVec[i] << ' ';
    //}
    //std::cout << std::endl;

    calcOutput();
}
