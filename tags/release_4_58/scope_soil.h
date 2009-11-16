// scope_soil.h --- Look up values in the soil.
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


#ifndef SCOPE_SOIL_H
#define SCOPE_SOIL_H

#include "scope.h"
#include <vector>

class Soil;
class SoilWater;
class SoilHeat;

class ScopeSoil : public Scope
{
  // Utilities.
public:
  static const symbol rho_b;
  static const symbol rho_b_unit;
  static const symbol clay;
  static const symbol humus;
  static const symbol h;
  static const symbol Theta;
  static const symbol T;

  // Types.
public:
  enum domain_t { primary, secondary, matrix };

  // Content.
private:
  const Soil& soil;
  const SoilWater& soil_water;
  const SoilHeat& soil_heat;
  const std::vector<symbol> all_numbers_;

  // State.
private:
  bool old_water;
  domain_t domain;
public:                         // Abused for debugging in scope_soil.h
  int cell;			// Current cell.
public:
  void set_cell (size_t);
  void set_old_water (bool old);
  void set_domain (domain_t);

  // Scope Interface.
public:
  void entries (std::set<symbol>&) const;
  Value::type lookup (symbol tag) const;
  bool check (symbol tag) const;
  double number (symbol tag) const;
  symbol dimension (symbol tag) const;
  symbol description (symbol tag) const;

  // Create and Destroy.
private:
  ScopeSoil (const ScopeSoil&);
  ScopeSoil ();
  static std::vector<symbol> 
  /**/ find_numbers (const Soil&);
public:
  explicit ScopeSoil (const Soil&, const SoilWater&, const SoilHeat&);
  ~ScopeSoil ();
};

#endif // SCOPE_SOIL_H