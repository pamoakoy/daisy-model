// alist.h -- attribute list
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


#ifndef ALIST_H
#define ALIST_H

#include "symbol.h"
#include <stdexcept>
#include <string>
#include <vector>
#include <list>

class PLF;
class AttributeList;
class Syntax;

class AttributeList
{
  // Content.
  struct Implementation;
  Implementation& impl;

public:
  // Is 'key' an element of this alist?
  bool check (const std::string& key) const;
  bool check (const char* key) const;
  // Is this alist a subset of 'other'?
  bool subset (const AttributeList& other, const Syntax& syntax) const;
  // Is the element 'key' in this alist a subset of the correspi
  bool subset (const AttributeList& other, const Syntax& syntax,
	       const std::string& key) const;
  int size (const std::string& key) const;

  // Extract values.
  double number (const std::string&) const;
  double number (const char*) const;
  double number (const std::string&, double default_value) const;
  double number (const char*, double default_value) const;
  const std::string& name (const std::string&) const;
  const std::string& name (const char*) const;
  const std::string& name (const std::string&,
                           const std::string& default_value) const;
  const std::string& name (const char*,
                           const std::string& default_value) const;
  symbol identifier (const std::string&) const;
  symbol identifier (const char*) const;
  bool flag (const std::string&) const;
  bool flag (const char*) const;
  const PLF& plf (const std::string&) const;
  const PLF& plf (const char*) const;
  AttributeList& alist (const std::string&) const;
  AttributeList& alist (const char*) const;
  int integer (const std::string&) const;
  int integer (const char*) const;
  int integer (const std::string&, int default_value) const;
  int integer (const char*, int default_value) const;
  const std::vector<double>& number_sequence (const std::string&) const;
  const std::vector<double>& number_sequence (const char*) const;
  const std::vector<symbol>& 
  /**/ identifier_sequence (const std::string& key) const;
  const std::vector<symbol>& identifier_sequence (const char* key) const;
  const std::vector<bool>& flag_sequence (const std::string& key) const;
  const std::vector<bool>& flag_sequence (const char* key) const;
  const std::vector<int>& integer_sequence (const std::string& key) const;
  const std::vector<int>& integer_sequence (const char* key) const;
  const std::vector<const PLF*>& plf_sequence (const std::string& key) const;
  const std::vector<const PLF*>& plf_sequence (const char* key) const;
  const std::vector<AttributeList*>& 
  /**/ alist_sequence (const std::string& key) const;
  const std::vector<AttributeList*>& alist_sequence (const char* key) const;

  // Create and Destroy.
  void add (const std::string&, double);
  void add (const std::string&, double, const std::string&);
  void add (const std::string&, const char*);
  void add (const std::string&, const std::string&);
  void add (const std::string&, symbol);
  void add (const std::string&, bool);
  void add (const std::string&, int);
  void add (const std::string&, const AttributeList&);
  void add (const std::string&, const PLF&);
  void add (const std::string&, const std::vector<double>&);
  void add (const std::string&, const std::vector<symbol>&);
  void add (const std::string&, const std::vector<bool>&);
  void add (const std::string&, const std::vector<int>&);
  void add (const std::string&, const std::vector<AttributeList*>&);
  void add (const std::string&, const std::vector<const PLF*>&);

  void remove (const std::string&);
  bool revert (const std::string&, const AttributeList&, const Syntax&);
  void operator += (const AttributeList&);
  void operator = (const AttributeList&);
  void clear ();
  AttributeList (const AttributeList& old);
  AttributeList ();
  ~AttributeList ();
};

#endif // ALIST_H

// alist.h ends here
