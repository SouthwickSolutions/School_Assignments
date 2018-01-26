#ifndef LION_H_INCLUDED
#define LION_H_INCLUDED

#include "critter.h"

class Lion: public Critter{
    public:

        int mMissedMeals;

        Lion(int x, int y);
        virtual ~Lion();

        int getMissedMealCount() const;

        Critter *findNeighborPrey(std::vector<Critter*>& critters) const;
        virtual bool eat(std::vector<Critter*>& critters);
        virtual bool reproduce(std::vector<Critter*>& critters);

};

#endif // LION_H_INCLUDED
