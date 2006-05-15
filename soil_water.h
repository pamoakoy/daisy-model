// soil_water.h
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


#ifndef SOIL_WATER_H
#define SOIL_WATER_H

#include <vector>

class AttributeList;
class Surface;
class Groundwater;
class Log;
class Soil;
class Syntax;
class Geometry;
class SoilHeat;
class Treelog;
class Block;

class SoilWater
{
  // Content.
protected:
  std::vector<double> h_;
  std::vector<double> Theta_;
  std::vector<double> Theta_old_;
  std::vector<double> S_sum_;
  std::vector<double> S_root_;
  std::vector<double> S_drain_;
  std::vector<double> X_ice_;
  
  // Sink.
public:
  virtual void clear (const Geometry&) = 0;
  virtual void root_uptake (const std::vector<double>&) = 0;
  
  // Queries
public:
  double h (size_t i) const
  { return h_[i]; }
  double Theta (size_t i) const
  { return Theta_[i]; }
  double Theta_left (size_t i) const
  { return Theta_[i] - S_sum_[i]; }
  double Theta_old (size_t i) const
  { return Theta_old_[i]; }
  double content (const Geometry&,
                  double from, double to) const; // [cm]
  double S_root (size_t i) const
  { return S_root_[i]; }
  double S_drain (size_t i) const
  { return S_drain_[i]; }
  double X_ice (size_t i) const
  { return X_ice_[i]; }

  virtual double top_flux () const = 0;

  // Ice modified lookups.
  virtual double Theta_ice (const Soil&, size_t i, double h) const = 0;
 
  // Simulation.
protected:
  void output_base (Log& log) const;
public:
  virtual void incorporate (const Geometry&, 
                            double amount, double from, double to) = 0;
  virtual void mix (const Geometry& geo,
                    const Soil&, double from, double to) = 0;
  virtual void swap (Treelog&, const Geometry& geo,
                     const Soil&, double from, double middle, double to) = 0;

  // Communication with surface.
  virtual double MaxExfiltration (const Geometry& geo,
                                  const Soil&, double T) const = 0;
  
  // Creation.
  static void load_base (Syntax&, AttributeList&);
  SoilWater (Block&);
  virtual ~SoilWater ();
};

#endif // SOIL_WATER_H
