// intrinsics.h -- The build in models of Daisy.
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


#ifndef INTRINSICS_H
#define INTRINSICS_H

#include "symbol.h"
#include <map>
#include <vector>

class Library;
class Declare;

class Intrinsics 
{
  // Content.
  typedef std::map<symbol, std::vector<const Declare*>/**/> declare_lib_map_t;
  typedef std::map<symbol, declare_lib_map_t> declare_map_t;
  mutable declare_map_t delayed;

public:
  std::map<symbol, Library*> all;
  int count;
  mutable int closed;

  // Use.
public:
  std::map<symbol, Library*> clone () const;
  Library& add (symbol component);
  Library& library (symbol component) const;
  void declare (symbol component, symbol model, const Declare&);
  void instantiate (symbol component, symbol model) const;

  // Create and Destroy.
public:
  Intrinsics ();
  ~Intrinsics ();
};

#endif // INTRINSICS_H
