// reaction.h --- Tranformation between soil chemicals.
// 
// Copyright 2004 Per Abrahamsen and KVL.
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


#ifndef REACTION_H
#define REACTION_H

#include "model.h"

class Log;
class Geometry;
class Soil;
class SoilWater;
class SoilHeat;
class OrganicMatter;
class Chemistry;
class Treelog;
class Block;
class Units;

class Reaction : public ModelAListed
{
  // Content.
public:
  static const char *const component;
  symbol library_id () const;

  // Simulation.
public:
  virtual void tick (const Units& units, 
                     const Geometry&, const Soil&, const SoilWater&,
		     const SoilHeat&, const OrganicMatter&, Chemistry&,
		     const double dt, Treelog&) = 0;
  virtual void output (Log&) const = 0;

  // Create and Destroy.
  static const AttributeList& nitrification_model ();
  static const AttributeList& denitrification_model ();
  static const AttributeList& NH4_sorption_model ();
public:
  virtual void initialize (const Soil&, Treelog&) = 0;
  virtual bool check (const Units& units, 
                      const Soil&, const SoilWater&, const SoilHeat&,
		      const Chemistry&, Treelog&) const = 0;
protected:
  Reaction (Block& al);
public:
  ~Reaction ();
};

#endif // REACTION_H
