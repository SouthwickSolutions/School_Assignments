#include <cstdlib>
#include "lion.h"

Lion::Lion(int x, int y)
    : Critter(x, y, 10){

        mMissedMeals = 0;
}



Lion::~Lion(){}



int Lion::getMissedMealCount() const{
    return mMissedMeals;
}




Critter* Lion::findNeighborPrey( std::vector< Critter* >& critters ) const{
	size_t i;

 	for(i = 0; i < critters.size(); i++){
        if((critters[i]->getFoodChainLevel() == 5 && this->getFoodChainLevel() == 10) && (critters[i]->isAlive())){
            if(((critters[i]->getX() == this->getX() + 1) && (critters[i]->getY() == this->getY())) ||
               ((critters[i]->getX() == this->getX() - 1) && (critters[i]->getY() == this->getY())) ||
			   ((critters[i]->getY() == this->getY() - 1) && (critters[i]->getX() == this->getX())) ||
			   ((critters[i]->getY() == this->getY() + 1) && (critters[i]->getX() == this->getX()))){
                   return critters[i];
			}
        }
    }
 	return 0;
}





bool Lion::eat(std::vector<Critter*>& critters){
    if (isAlive() == false){
		return false;
	}
	Critter *killem = findNeighborPrey(critters);
	if (killem){
			setPosition(killem->getX(), killem->getY());
			killem->kill();
			mMissedMeals = 0;
			return false;
	}
	else{
		mMissedMeals++;
		if (mMissedMeals >= 3){
			kill();
		}
		return false;
	}
}




bool Lion::reproduce(std::vector<Critter*>& critters){
	(void)critters;
	return false;
}
