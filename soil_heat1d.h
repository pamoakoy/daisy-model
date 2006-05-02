// soil_heat1d.h
// 
// Copyright 1996-2001, 2006 Per Abrahamsen and S�ren Hansen
// Copyright 2000-2001, 2006 KVL.
//
// This file is part of Daisy.
// 
// Daisy is free software; you can redistribute it and/or modify
// it under the terms of the GNU Lesser Public License as published by
// the Free Software Foundation; either version 2.1 of the License, or
// (at your option) any later version.
// 
// Daisy is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser Public License for more details.
// 
// You should have received a copy of the GNU Lesser Public License
// along with Daisy; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA


#ifndef SOIL_HEAT1D_H
#define SOIL_HEAT1D_H

#include "soil_heat.h"
#include <string>

class Geometry1D;
class Surface;
class Bioclimate;
class SoilWater;
class Weather;
class Time;

class SoilHeat1D : public SoilHeat
{
  struct Implementation;
  Implementation& impl;

  enum state_t { liquid, freezing, frozen, thawing };
  state_t state (size_t i) const;
  double capacity (const Soil&, const SoilWater&, size_t i) const;
  double capacity_apparent (const Soil&, const SoilWater&, size_t i) const;
public:
  double top_flux (const Geometry& geo,
                   const Soil&, const SoilWater&) const; // [W/m^2]
  double T_surface_snow (const Geometry&, const Soil&, const SoilWater&,
                         double T_snow, double K_snow, double dZs) const;
  void tick (const Time&, const Geometry1D& geo,
             const Soil&, SoilWater&, 
	     const Surface&, const Weather& weather);
  double energy (const Geometry1D& geo,
                 const Soil&, const SoilWater&, double from, double to) const;
  void set_energy (const Geometry1D& geo,
                   const Soil&, const SoilWater&, 
		   double from, double to, double energy);
  void swap (const Geometry& geo,
             double from, double middle, double to);
  double source (size_t i) const;
  void set_source (size_t i, double value); // [erg/cm^3/h]
  void output (Log&) const;
  static void load_syntax (Syntax&, AttributeList&);
  SoilHeat1D (const Block&);
  void initialize (const AttributeList& al, 
		   const Geometry1D& geo,
                   const Soil& soil, const Time& time, const Weather& weather,
		   Treelog&);
  ~SoilHeat1D ();
};

#endif // SOIL_HEAT1D_H
