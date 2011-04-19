// ABAprod.h -- Production of ABA in soil.
// 
// Copyright 2007 Per Abrahamsen and KVL.
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
// GNU Lesser Public License for more details.// 
// You should have received a copy of the GNU Lesser Public License
// along with Daisy; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA


#ifndef ABAPROD_H
#define ABAPROD_H

#include "model_derived.h"
#include <vector>

class Treelog;
class BlockModel;
class Log;
class Geometry;
class SoilWater;
class Units;

class ABAProd : public ModelDerived
{
  // Content.
public:
  static const char *const component;
  symbol library_id () const;

  // Simulation.
public:
  virtual void production (const Units&, const Geometry&, const SoilWater&,
			   const std::vector<double>& S /* [cm^3/cm^3/h] */,
			   const std::vector<double>& l /* [cm/cm^3] */,
			   std::vector<double>& ABA /* [g/cm^3/h] */,
			   Treelog& msg) const = 0; 
  virtual void output (Log& log) const = 0;

  // Create and Destroy.
public:
  virtual void initialize (const Units&, Treelog&) = 0;
  virtual bool check (const Units&, Treelog&) const = 0;
protected:
  ABAProd (const BlockModel&);

public:
  ~ABAProd ();
};

#endif // ABAPROD_H
