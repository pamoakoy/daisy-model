// nitrification.h

#ifndef NITRIFICATION_H
#define NITRIFICATION_H

class AttributeList;
class Syntax;
class Soil;
class SoilWater;
class SoilHeat;
class SoilNH4;
class SoilNO3;
class CSMP;

class Nitrification
{
  // Parameters.
private: 
  const double k;
  const double k_10;

  // Simulation.
public:
  void tick (Soil&, SoilWater&, SoilHeat&, SoilNO3&, SoilNH4&);

  // Create.
public:
  static void load_syntax (Syntax&, AttributeList&);
  Nitrification (const AttributeList&);
};


#endif NITRIFICATION_H
