// nitrification.h
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


#ifndef NITRIFICATION_H
#define NITRIFICATION_H

#include "librarian.h"

class Soil;
class SoilWater;
class SoilHeat;
class SoilNO3;
class SoilNH4;

class Nitrification
{
  // Content.
public:
  const symbol name;
  static const char *const description;

  // Simulation.
public:
  virtual void tick (const Soil&, const SoilWater&, const SoilHeat&,
		     SoilNO3&, SoilNH4&) = 0;
  virtual void output (Log&) const = 0;

  // Create and Destroy.
protected:
  Nitrification (const AttributeList& al);
public:
  virtual ~Nitrification ();
};

#if !defined (__BORLANDC__)
EMPTY_TEMPLATE
Librarian<Nitrification>::Content* Librarian<Nitrification>::content;
#endif

static Librarian<Nitrification> Nitrification_init ("nitrification");

#endif // NITRIFICATION_H
