// soil_NO3.h

#ifndef SOIL_NO3_H
#define SOIL_NO3_H

#include "solute.h"

class SoilNO3 : public Solute
{
public:
  // Substance specific constants.
  double diffusion_coefficient () const; // in free solu. [m� / s]
 
public:
  static void load_syntax (Syntax&, AttributeList&);
  SoilNO3 (const AttributeList&);
};

#endif SOIL_NO3_H
