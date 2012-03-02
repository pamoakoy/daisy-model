// wse.h -- Water Stress Effect on yield.
// 
// Copyright 2004 Per Abrahamsen, S�ren Hansen and KVL.
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


#ifndef WSE_H
#define WSE_H

#include "model.h"
#include "symbol.h"
#include <memory>

class BlockModel;

class WSE : public Model
{
  // Content.
public:
  static const char *const component;
  symbol library_id () const;

  // Simulation.
public:
  virtual double factor(const double water_stress) const = 0;

  // Create and Destroy.
public:
  static std::auto_ptr<WSE> create_none ();
  static std::auto_ptr<WSE> create_full ();
  WSE ();
  ~WSE ();
};

#endif // WSE_H
