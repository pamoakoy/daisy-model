// movement.h
// 
// Copyright 2006 Per Abrahamsen and KVL.
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


#ifndef MOVEMENT_H
#define MOVEMENT_H

#include "model.h"
#include <vector>
#include <memory>

class Geometry;
class Soil;
class SoilWater;
class SoilHeat;
class DOE;
class Chemical;
class Adsorption;
class Surface;
class Groundwater;
class Weather;
class Time;
class Treelog;
class Block;
class Syntax;
class AttributeList;
class Log;
class Scope;
class Tertiary;
class Units;

class Movement : public ModelLogable
{
  // Content.
public:
  static const char *const component;
  symbol library_id () const;

  virtual Geometry& geometry () const = 0;

  // Tertiary transport.
protected:
  std::auto_ptr<Tertiary> tertiary;
public:
  void tick_tertiary (const Units&,
                      const Geometry&, const Soil&, const SoilHeat&,
                      const double dt, SoilWater&, Surface&, Treelog&);

  // Simulation.
public:
  virtual void tick (const Soil&, SoilWater&, const SoilHeat&, Surface&,
                     Groundwater&, const Time&, const Weather&, 
                     double dt, Treelog&) = 0;
  virtual void solute (const Soil&, const SoilWater&, 
                       const double J_above, Chemical&,
		       double dt, const Scope&, Treelog&) = 0;
  virtual void element (const Soil&, const SoilWater&, 
                        DOE&, double diffusion_coefficient, 
			double dt, Treelog&) = 0;
  virtual void heat (const std::vector<double>& q_water,
		     const std::vector<double>& S_water,
		     const std::vector<double>& S_heat,
		     const std::vector<double>& capacity_old,
		     const std::vector<double>& capacity_new,
		     const std::vector<double>& conductivity,
		     double T_top,
		     double T_top_new,
		     std::vector<double>& T,
		     const double dt, Treelog&) const = 0;
  virtual void ridge (Surface&, const Soil&, const SoilWater&, 
                      const AttributeList&) = 0;
  void output (Log&) const;

  // Heat.
  virtual double surface_snow_T (const Soil&, const SoilWater&, const SoilHeat&,
                                 double T_snow, double K_snow,
                                 double dZs) const = 0;
  virtual std::vector<double> default_heat (const Soil&, 
                                            const Time&, const Weather&) = 0;
  virtual double bottom_T () const = 0;

  // Create and Destroy.
private:
  virtual bool check_derived (Treelog& err) const = 0;
  virtual void initialize_derived (const Soil&, const Groundwater&, 
                                   bool has_macropores, Treelog& msg) = 0;
public:
  bool check (Treelog& err) const;
  bool initialize (const Units&,
                   const Soil&, const Groundwater&, const Scope& scope,
                   Treelog& msg);
  static const AttributeList& default_model ();
  static void load_base (Syntax& syntax, AttributeList&);
  static void load_vertical (Syntax& syntax, AttributeList& alist);
  static Movement* build_vertical (Block& al);
protected:
  Movement (Block&);
public:
  ~Movement ();
};

#endif // MOVEMENT_H
