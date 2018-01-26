#include "zebra.h"

Zebra::Zebra(int x, int y)
	:Critter(x, y, 5){}




Zebra::~Zebra(){}





bool Zebra::eat(std::vector<Critter*>& critters){
	(void)critters;
	return false;
}





bool Zebra::reproduce(std::vector< Critter* >& critters){
    (void)critters;
	return false;
}
