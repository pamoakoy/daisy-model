// scope_block.h -- Treat a block as a scope.
// 
// Copyright 2006 Per Abrahamsen and KVL.
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


#ifndef SCOPE_BLOCK_H
#define SCOPE_BLOCK_H

#include "scope.h"
#include "block.h"

class ScopeBlock : public Scope
{
  // Content.
private:
  const Block& block;

  // Scope interface.
public:
  void entries (std::set<symbol>&) const;
  Attribute::type lookup (symbol) const;
  symbol dimension (symbol tag) const;
  symbol description (symbol) const;
  int type_size (symbol tag) const;

  bool check (symbol tag) const;
  int value_size (symbol tag) const;
  double number (symbol tag) const;
  symbol name (symbol) const;

public:
  // Use.
  const std::vector<symbol>& all_numbers () const;
  bool has_number (symbol tag) const;
  bool has_name (symbol) const;

  // Create and Destroy.
private:
  ScopeBlock (const ScopeBlock&);
  ScopeBlock ();
public:
  explicit ScopeBlock (const Block&);
  ~ScopeBlock ();
};

#endif // SCOPE_BLOCK_H
