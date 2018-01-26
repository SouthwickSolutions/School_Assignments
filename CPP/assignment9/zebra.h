#ifndef _1_ZEBRA_H_
#define _1_ZEBRA_H_

#include <vector>
#include <iostream>
#include <cstdlib>

#include <time.h>
#include "critter.h"

class Zebra : public Critter{

  public:
  	Zebra(int x, int y);
  	virtual ~Zebra();

  	virtual bool eat(std::vector< Critter* >& critters);
    virtual bool reproduce(std::vector<Critter*>& critters);
    //virtual bool reproduce(std::vector<Critter*>& critters, CritterPtr&);
};

#endif /* _ZEBRA__H_ */
