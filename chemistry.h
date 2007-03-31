// chemistry.h --- Pesticides and other chemicals.
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
// GNU Lesser Public License for more details.
// 
// You should have received a copy of the GNU Lesser Public License
// along with Daisy; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA


#ifndef CHEMISTRY_H
#define CHEMISTRY_H

#include "model.h"
#include "reaction.h"           // Needed for initialization order.
#include "chemical.h"

class Log;
class Geometry;
class Soil;
class SoilWater;
class SoilHeat;
class OrganicMatter;
class Movement;

class Chemistry : public Model
{
  // Content.
public:
  const symbol name;
  static const char *const description;
  static const char *const component;

  // Query.
  virtual bool know (symbol chem) const = 0;
  virtual Chemical& find (symbol chem) = 0;

  // Management.
public:
  virtual void spray (symbol chem, double amount, double dt, Treelog&) = 0;
  virtual void harvest (double removed, double surface, double dt) = 0;
  virtual void mix (const Geometry&, const Soil&, const SoilWater&, 
                    double from, double to, double dt) = 0;
  virtual void swap (const Geometry&, const Soil&, const SoilWater&,
                     double from, double middle, double to, double dt) = 0;

  // Simulation.
public:
  virtual void tick_top (double snow_leak_rate /* [h^-1] */,
                         double cover /* [] */,
                         double canopy_leak_rate /* [h^-1] */,
                         double surface_runoff_rate /* [h^-1] */,
                         double dt /* [h] */) = 0;
  virtual void tick_soil (const Geometry& geo, double ponding /* [mm] */,
                          double R_mixing /* [h/mm] */,
                          const Soil&, const SoilWater&, const SoilHeat&, 
                          Movement&, const OrganicMatter&,
                          double dt, Treelog&) = 0;
  virtual void clear () = 0;
  virtual void output (Log&) const = 0;

  // Create & Destroy.
public:
  static const AttributeList& default_model ();
  virtual void initialize (Block&, const AttributeList&, const Geometry& geo,
                           const Soil&, const SoilWater&) = 0;
  virtual bool check (const Soil&, Treelog&) const = 0;
protected:
  explicit Chemistry (Block& al);
public:
  virtual ~Chemistry ();
};

#endif // CHEMISTRY_H
