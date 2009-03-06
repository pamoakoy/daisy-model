// ponddamp.h --- Dampening effect of ponding on randrop momentum.
// 
// Copyright 2009 Per Abrahamsen and KVL.
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


#ifndef PONDDAMP_H
#define PONDDAMP_H

#include "model.h"
#include <memory>

class Block;

class Ponddamp : public Model
{
  // Content.
public:
  static const char *const component;
  symbol library_id () const;

  // Simulation.
protected:
  static double dds (double P /* [mm/h] */);
public:
  virtual double value (double h /* [mm] */, double P /* [mm/h] */) const = 0;

  // Create and Destroy.
protected:
  Ponddamp ();
public:
  ~Ponddamp ();
};

#endif // PONDDAMP_H
