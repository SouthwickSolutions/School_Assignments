#include "tsp.h"
#include "TSPGOOD.h"

int main(){

    //any cycle
    //Graph graphObject;
    //graphObject.readGraph(std::cin);
    //graphObject.populateACycle();
    //graphObject.calcCost();
    //graphObject.calcQuality();
    //graphObject.calcOutput();

    //good cycle
    TSPGOOD tspGoodObject;
    tspGoodObject.findAGoodQuality();
    
    return 0;
}
