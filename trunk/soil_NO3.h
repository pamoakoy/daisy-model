// soil_NO3.h

#ifndef SOIL_NO3_H
#define SOIL_NO3_H

#include "solute.h"

class SoilNO3 : public Solute
{
public:
  // Substance specific constants.
  double beta (const Soil&, const SoilWater&, int i, double C) const; // dA/dC
  double diffusion_coefficient () const; // in free solu. [m^2 / s]
  double C_to_M (const Soil&, const SoilWater&, int i, double C) const;
  double M_to_C (const Soil&, const SoilWater&, int i, double M) const;

public:
  static void load_syntax (Syntax&, AttributeList&);
  SoilNO3 (const Soil&, const SoilWater&, const AttributeList&);
};

#endif SOIL_NO3_H
