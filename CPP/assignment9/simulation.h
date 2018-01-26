#ifndef SIMULATION_H_INCLUDED
#define SIMULATION_H_INCLUDED

#include <time.h>
#include <vector>
#include <cstdlib>

#include "lion.h"
#include "zebra.h"

class Simulation{
    public:
        //member variables
        int mWidth;
        int mHeight;
        int mVecSize;
        std::vector<Critter*> mCritters;

        //constructor and destructor
        Simulation(int width, int height);
        virtual ~Simulation();

        //class methods for the assignment
        void eatAll();
        void reproduceAll();
        void moveAll();
        void removeDead();
        void step();

        //personal class methods
        void randCritterGenerator();
        void createLion(int i);
        void createZebra(int i);
};
#endif //SIMULATION_H_INCLUDED
