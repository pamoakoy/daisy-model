// domsorp.h --- Sorption and desorption of dom to som.
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


#ifndef DOMSORP_H
#define DOMSORP_H

#include "model.h"
#include <vector>

class Log;
class Soil;
class SoilWater;
class SoilHeat;
class SOM;
class DOM;
class AttributeList;
class Block;
class Treelog;
class Syntax;
class Unitc;

class Domsorp : public ModelAListed
{
  // Content.
public:
  static const char *const component;
  symbol library_id () const;

  // Simulation.
public:
  virtual void tick (const Unitc&,
                     const Soil&, const SoilWater&, const SoilHeat&,
                     const std::vector<DOM*>&, const std::vector<SOM*>&,
                     Treelog&) = 0;
  virtual void output (Log&) const = 0;

  // Create and Destroy.
public:
  virtual void initialize (const Soil&, Treelog&);
  virtual bool check (const Unitc& unitc,
                      const Soil&, const SoilWater&, const SoilHeat&,
		      size_t dom_size, size_t som_size, 
                      Treelog&) const = 0;
  static void load_syntax (Syntax&, AttributeList&);
protected:
  Domsorp (Block& al);
public:
  ~Domsorp ();
};

#endif // DOMSORP_H
