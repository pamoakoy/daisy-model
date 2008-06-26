// condition.h -- Logic expressions
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


#ifndef CONDITION_H
#define CONDITION_H

#include "librarian.h"

class Daisy;

class Condition
{  
  // Content.
public:
  const string name;
  static const char *const description;
  virtual const string timestep ();

  // Simulation.
public:
  virtual bool match (const Daisy&) const = 0;
  virtual void output (Log&) const = 0;

  // Create & Destroy.
protected:
  Condition (const AttributeList& al);
public:
  virtual ~Condition ();
};

static Librarian<Condition> Condition_init ("condition");

#endif // CONDITION_H