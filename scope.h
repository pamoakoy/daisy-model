// scope.h -- A name -> value map.
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


#ifndef SCOPE_H
#define SCOPE_H

#include "symbol.h"
#include "librarian.h"
#include <vector>

class Treelog;

class Scope
{
  // Content.
private:
  const symbol title_;
public:
  static const char *const description;

  // Use.
public:
  symbol title () const;
  virtual const std::vector<symbol>& all_numbers () const = 0;
  virtual bool has_number (symbol) const = 0;
  virtual double number (symbol) const = 0;
  virtual symbol dimension (symbol) const = 0;
  virtual bool has_identifier (symbol) const;
  virtual symbol identifier (symbol) const;

  virtual symbol get_description (symbol) const = 0;

  // Create and Destroy.
private:
  Scope (const Scope&);
  Scope ();
public:
  static Scope& null ();
  explicit Scope (symbol title);
  explicit Scope (const char* title);
  explicit Scope (Block&);
  virtual ~Scope ();
};

class WScope : public Scope     // Writable scope.
{
  // Use.
public:
  virtual void set_number (symbol, double) = 0;

  // Create and Destroy.
private:
  WScope (const WScope&);
  WScope ();
public:
  explicit WScope (symbol title);
  explicit WScope (const char* title);
  explicit WScope (Block&);
  ~WScope ();
};

#ifdef FORWARD_TEMPLATES
template<>
Librarian<Scope>::Content* Librarian<Scope>::content;
#endif

static Librarian<Scope> Scope_init ("scope");

#endif // SCOPE_H
