//Algorithm 1 - Hill-Climbing-TSP

#ifndef TSP_GOOD_H_INCLUDED
#define TSP_GOOD_H_INCLUDED

#include "tsp.h"

class TSPGOOD: public Graph{
    public:
        //class members
        int mFirstIndex;
        int mSecondIndex;

        //constructors and deconstructors
        TSPGOOD();
        virtual ~TSPGOOD();

        //class methods
        void populateARandomCycle();
        void populateANewCycle();
        void switchBackCycles();
        void findAGoodQuality();
};

#endif //TSP_GOOD_H_INCLUDED
