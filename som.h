// som.h --- A single soil organic matter pool.
// 
// Copyright 2002 Per Abrahamsen and KVL.
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


#ifndef SOM_H
#define SOM_H

#include "model.h"
#include "om.h"

class Frame;

class SOM : public ModelAListed, public OM
{ 
public:
  static const char *const component;
  symbol library_id () const;

  void output(Log& log) const
  { OM::output (log); }

  // Create & Destroy.
public:
  SOM (Block&);
};

#endif // SOM_H
