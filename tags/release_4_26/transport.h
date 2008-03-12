// transport.h
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


#ifndef TRANSPORT_H
#define TRANSPORT_H

#include "model.h"
#include "syntax.h"
#include <vector>

class Geometry1D;
class Soil;
class SoilWater;
class Adsorption;
class Block;
class AttributeList;
class Treelog;

class Transport : public Model
{
  // Content.
public:
  const symbol name;
  static const char *const component;

  // Simulation.
public:
  virtual void tick (Treelog&, const Geometry1D&,
                     const Soil&, const SoilWater&, 
		     const Adsorption&, 
		     double diffusion_coefficient,
		     std::vector<double>& M, 
		     std::vector<double>& C,
		     const std::vector<double>& S,
		     std::vector<double>& J,
		     const double C_below, double dt) = 0;

  // Create and Destroy.
public:
  static const AttributeList& default_model ();
  static const AttributeList& reserve_model ();
  static const AttributeList& none_model ();
protected:
  Transport (Block&);
public:
  ~Transport ();
};

#endif // TRANSPORT_H