// depth.h --- Depth as a function of time.
// 
// Copyright 2005 Per Abrahamsen and KVL.
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


#ifndef DEPTH_H
#define DEPTH_H

#include "model.h"
#include "symbol.h"

class Time;
class Treelog;
class Block;
class Scope;
class Units;

class Depth : public Model
{
  // Content.
public:
  const symbol name;
  static const char *const component;
  symbol library_id () const;

  // Simulation.
public:
  virtual void tick (const Units&, const Time&,
                     const Scope& scope, Treelog&) = 0;
  virtual double operator()() const = 0;

  // Create and Destroy.
public:
  virtual void initialize (const Units&, const Scope&, Treelog&) = 0;
  virtual bool check (const Units&, const Scope&, Treelog&) const = 0;
  static Depth* create (double height);
protected:
  Depth (symbol name);
  Depth (const Block& al);
public:
  ~Depth ();
};

#endif // DEPTH_H
