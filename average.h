// average.h --- Find the average of two numbers.
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


#ifndef AVERAGE_H
#define AVERAGE_H

#include "model.h"
#include "symbol.h"

#include <memory>

class Block;

class Average : public Model
{
  // Content.
public:
  static const char *const component;
  symbol library_id () const;

  // Simulation.
public:
  virtual double operator()(double a, double b) const = 0;

  // Create and Destroy.
public:
  static std::auto_ptr<const Average> build_arithmetic ();
  static std::auto_ptr<const Average> build_geometric ();
protected:
  Average ();
public:
  ~Average ();
};

#endif // AVERAGE_H
