#include "simulation.h"

Simulation::Simulation( int width, int height ){
    mWidth = width;
    mHeight = height;
    mVecSize = (mWidth * mHeight);
    mCritters.resize(mVecSize);

    size_t i;
    int random;

    for(i = 0; i < mCritters.size(); i++){
        mCritters[i] = 0;
    }
    randCritterGenerator();
    random = rand() % 101;
    for(i = 0; i < mCritters.size(); i++){
        if(random >= 40){
            createZebra(i);
        }else if(random > 40 && random <= 65){
            createLion(i);
        }
    }
}





Simulation::~Simulation( ){
    size_t i;
    for (i = 0; i < mCritters.size(); i++){
        if(mCritters[i] != 0){
            delete mCritters[i];
        }
    }
}





void Simulation::eatAll(){
    size_t i;
    for (i = 0; i < mCritters.size(); i ++){
        if (mCritters[i] != 0 && mCritters[i]->getFoodChainLevel() == 10){
            mCritters[i]->eat(mCritters);
        }
    }
}





void Simulation::reproduceAll(){
    size_t i;
    for (i = 0; i < mCritters.size(); i ++){
        if(mCritters[i] != 0){
            mCritters[i]->reproduce(mCritters);
        }
    }
}






void Simulation::moveAll(){
    size_t i;
    for(i = 0; i < mCritters.size(); i ++){
        if(mCritters[i] != 0){
            mCritters[i]->move(mCritters, mWidth, mHeight);
        }
    }
}





void Simulation::removeDead(){
    size_t i;
    for(i = 0; i < mCritters.size(); i ++){
        if(mCritters[i] != 0 && mCritters[i]->isAlive() == false){
            delete mCritters[i];
            mCritters[i] = 0;
        }
    }
}





void Simulation::step(){
    eatAll();
    reproduceAll();
    moveAll();
    removeDead();
}





void Simulation::randCritterGenerator(){
    int seed;
    seed = time(0);
    srand(seed);
}





void Simulation::createZebra(int i){
    int x = 0;
    int y = 0;

    y = i / mWidth;
    x = i % mWidth;
    mCritters[i] = new Zebra(x, y);
}





void Simulation::createLion(int i){
    int x = 0;
    int y = 0;

    y = i / mWidth;
    x = i % mWidth;
    mCritters[i] = new Lion(x, y);
}
