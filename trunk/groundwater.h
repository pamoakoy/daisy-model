// groundwater.h
// 
// Copyright 1996-2001 Per Abrahamsen and S�ren Hansen
// Copyright 2000-2001 KVL.
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


#ifndef GROUNDWATER_H
#define GROUNDWATER_H

#include "model_derived.h"

class Frame;
class Time;
class Treelog;
class Geometry;
class Soil;
class SoilWater;
class SoilHeat;
class BlockModel;
class Scope;

class Groundwater : public ModelDerived
{
  // Content.
public:
  static const char *const component;
  symbol library_id () const;

  // Lower boundary.
  enum bottom_t { pressure, lysimeter, forced_flux, free_drainage };
  virtual bottom_t bottom_type () const = 0;
  virtual double q_bottom (size_t edge) const = 0;
  virtual void accept_bottom (double amount, const Geometry&, size_t edge);

  // Simulation.
public:
  virtual void tick (const Geometry& geo,
                     const Soil&, SoilWater&, double h_surface /* [cm] */,
		     const SoilHeat&, const Time&, const Scope&, Treelog&) = 0;
  virtual void output (Log&) const;

  // Accessors.
public:
  virtual double table () const = 0;

    // Create and Destroy.
public:
  static void load_syntax (Frame&);
  virtual void initialize (const Geometry&, const Time&, 
			   const Scope&, Treelog&) = 0;
  virtual bool check (const Geometry&, const Scope&, Treelog&) const = 0;
protected:
  Groundwater (const BlockModel& al);
public:
  ~Groundwater ();
};

#endif // GROUNDWATER_H
