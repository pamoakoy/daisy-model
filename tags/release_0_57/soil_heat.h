// soil_heat.h

#ifndef SOIL_HEAT_H
#define SOIL_HEAT_H

#include <string>
#include <vector>

class AttributeList;
class Log;
class Surface;
class Bioclimate;
class Syntax;
class Soil;
class SoilWater;
class Groundwater;
class Weather;
class Time;
class Filter;

class SoilHeat
{
  struct Implementation;
  Implementation& impl;

public:
  double top_flux (const Soil&, const SoilWater&) const; // [W/m^2]
  void tick (const Time&, const Soil&, const SoilWater&, 
	     const Surface&, const Groundwater&, const Weather& weather);
  double energy (const Soil&, const SoilWater&, double from, double to) const;
  void set_energy (const Soil&, const SoilWater&, 
		   double from, double to, double energy);
  void swap (const Soil&, double from, double middle, double to);
  double T (unsigned int i) const; // [dg C]
  void output (Log&, Filter&) const;
  bool check (unsigned n) const;
  static void load_syntax (Syntax&, AttributeList&);
  SoilHeat (const AttributeList&);
  void initialize (const AttributeList& al, 
		   const Soil& soil, const Time& time, const Weather& weather);
  ~SoilHeat ();
};

#endif SOIL_HEAT_H
