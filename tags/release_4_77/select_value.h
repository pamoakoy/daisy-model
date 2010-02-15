// select_value.h --- Select a state variable.
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

#ifndef SELECT_VALUE_H
#define SELECT_VALUE_H

#include "select.h"

class SelectValue : public Select
{
  // Content.
private:
  int type_size () const
  { return Attribute::Singleton; }

protected:
  double value;	
  void add_result (double result);

  // Output routines.
public:
  void done (double dt);

  // Create and Destroy.
public:
  SelectValue (const BlockModel& al);
};

#endif /* SELECT_VALUE_H */
