// scope_id.h -- A name -> value map.
// 
// Copyright 2004 Per Abrahamsen and KVL.
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


#ifndef SCOPE_ID_H
#define SCOPE_ID_H

#include "scope.h"
#include <string>

class ScopeID : public WScope
{
  // Content.
  const symbol tag;
  std::vector<symbol> all_numbers_;
  double value;
  symbol dim;

  // Scope interface.
public:
  const std::vector<symbol>& all_numbers () const;
  bool has_number (symbol name) const;
  double number (symbol) const;
  symbol dimension (symbol) const;
  symbol get_description (symbol) const;

  // WScope interface.
public:
  void add (symbol, double);

  // ScopeID interface.
public:
  void set_dimension (symbol name, symbol dim);

  // Create.
private:
  ScopeID (const ScopeID&);
public:
  explicit ScopeID (const symbol tag, const symbol dim);
  explicit ScopeID (Block&);
  ~ScopeID ();
};

#endif // SCOPE_ID_H
