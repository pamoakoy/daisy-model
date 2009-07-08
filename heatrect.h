// heatrect.h -- Heat  transport in rectangular grid.
// 
// Copyright 2008 Per Abrahamsen and KVL.
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


#ifndef HEATRECT_H
#define HEATRECT_H

#include "model.h"
#include "symbol.h"
#include <vector>

class GeometryRect;
class Block;
class Treelog;

class Heatrect : public Model
{
  // Content.
public:
  const symbol name;
  static const char *const component;
  symbol library_id () const;

  // Simulation.
public:
  virtual void solve (const GeometryRect& geo,
                      const std::vector<double>& q_water,
                      const std::vector<double>& S_water,
                      const std::vector<double>& S_heat,
                      const std::vector<double>& capacity_old,
                      const std::vector<double>& capacity_new,
                      const std::vector<double>& conductivity,
                      const double T_top,
                      const double T_top_new,
                      const double T_bottom,
                      std::vector<double>& T,
                      const double dt, Treelog&) const = 0;

  // Create and Destroy.
protected:
  Heatrect (Block&);
public:
  ~Heatrect ();
};

#endif // HEATRECT_H
