#ifndef CRITTER_H_INCLUDED
#define CRITTER_H_INCLUDED

#include <vector>

class Critter{
    public:
        int  mX;
        int  mY;
        int  mFoodChainLevel;
        bool mAlive;
        int mBreedStep;

        Critter(int x, int y, int level);
        virtual ~Critter();

        int getX() const;
        int getY() const;
        int getFoodChainLevel() const;
        bool isAlive() const;

        bool kill();
        void setPosition(int x, int y);
        bool positionAvailable(int x,
                               int y,
                               std::vector<Critter*>& critters,
                               int width,
                               int height);
        virtual bool move(std::vector<Critter*>& critters,
                          int width,
                          int height);
        virtual bool eat(std::vector<Critter*>& critters) = 0;
        virtual bool reproduce(std::vector<Critter*>& critters) = 0;
        //virtual bool reproduce(std::vector< Critter* >& critters, CritterPtr&) = 0;
};
#endif // CRITTER_H_INCLUDED
