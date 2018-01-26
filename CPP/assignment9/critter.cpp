#include "critter.h"

#include <cstdlib>
#include <ctime>
#include <algorithm>

Critter::Critter(int x, int y, int level){
    if(x < 0){mX = 0;}
    else{mX = x;}

    if(y < 0){mY = 0;}
    else{mY = y;}

    if(mFoodChainLevel < 0){mFoodChainLevel = 0;}
    else{mFoodChainLevel = level;}

    mAlive = true;
    mBreedStep = true;
}



Critter::~Critter(){}



int Critter::getX() const{
    return mX;
}



int Critter::getY() const{
    return mY;
}



int Critter::getFoodChainLevel() const{
    return mFoodChainLevel;
}



bool Critter::isAlive() const{
    return mAlive;
}





bool Critter::kill(){
    bool r;

    if(mAlive){
        mAlive = false;
        r = true;
    }else{r = false;}

    return r;
}




void Critter::setPosition(int x, int y){
    mX = x;
    mY = y;
}





bool Critter::positionAvailable(int x, int y, std::vector<Critter*>& critters, int width, int height){
    size_t i;
	if((x < width) && (y < height) &&  (x >= 0) && (y >= 0)){
        for(i = 0; i < critters.size(); i++){
            if((x == critters[i]->getX()) && (y == critters[i]->getY())){
                return false;
            }
        }
        return true;
    }
    else{
        return false;
    }
}





bool Critter::move(std::vector<Critter*>& critters, int width, int height){
    size_t i;
    bool determine = true;
    int random = 0;
    int count = 0;
    int numberEQRand = 0;
    std::vector<bool> mDirection;

    if (!isAlive()){
        return false;
    }

     //north
      determine = positionAvailable(mX, mY - 1, critters, width, height);
      if (determine){
          mDirection.push_back(true);
      }else{
          mDirection.push_back(false);
      }

      //south
      determine = positionAvailable(mX, mY + 1, critters, width, height);
      if (determine){
          mDirection.push_back(true);
      }else{
          mDirection.push_back(false);
      }

      //east
      determine = positionAvailable(mX + 1, mY, critters, width, height);
      if (determine){
          mDirection.push_back(true);
      }else{
          mDirection.push_back(false);
      }

      //west
      determine = positionAvailable(mX - 1, mY, critters, width, height);
      if (determine){
        mDirection.push_back(true);
      }else{
        mDirection.push_back(false);
      }

    //getting directions (up = 0, down = 1, left = 2, right = 3)
    for(i = 0; i < 4; i++){
        if(mDirection[i] == true){
            count++;
        }
    }
    if (count > 0 && count  <= 4){
        while (true){
            random = rand() % 4;

            //north
            if (mDirection[0] == true && random == 0){
                setPosition(mX, mY - 1);
                numberEQRand ++;

                return true;
            }
            //south
            else if(mDirection[1] == true && random == 1){
                setPosition(mX, mY + 1);

                return true;
            }
            //east
            else if(mDirection[2] == true && random == 2){
                setPosition(mX + 1, mY);

                return true;
            }
            //west
            else if (mDirection[3] == true && random == 3){
                setPosition(mX - 1, mY);

                return true;
            }
        }
    }
    return false;
}
