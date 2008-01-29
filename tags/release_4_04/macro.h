// macro.h --- preferential flow.
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


#ifndef MACRO_H
#define MACRO_H

#include "librarian.h"
#include <vector>

class Geometry1D;
class Soil;
class Log;
class Surface;

class Macro
{
  // Content.
public:
  const symbol name;
  static const char *const description;
  virtual bool none () const;

  // Simulation.
public:
  virtual void tick (const Geometry1D& geo,
                     const Soil& soil, unsigned int first, unsigned int last,
		     Surface& surface,
		     const std::vector<double>& h_ice,
		     const std::vector<double>& h,
		     const std::vector<double>& Theta,
		     std::vector<double>& S,
		     std::vector<double>& S_p,
		     std::vector<double>& q_p, Treelog&) = 0;
  virtual void output (Log&) const = 0;

  // Create and Destroy.
public:
  static std::auto_ptr<Macro> create (double depth); // Defined in macro_std.C.
protected:
  Macro (Block& al);
public:
  virtual ~Macro ();
};

#ifdef FORWARD_TEMPLATES
template<>
Librarian<Macro>::Content* Librarian<Macro>::content;
#endif

static Librarian<Macro> Macro_init ("macro");

#endif // MACRO_H