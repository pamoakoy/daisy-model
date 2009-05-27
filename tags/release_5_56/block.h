// block.h -- Support for block scoped variables.
// 
// Copyright 2005 Per Abrahamsen and KVL.
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


#ifndef BLOCK_H
#define BLOCK_H

#include "syntax.h"
#include "symbol.h"
#include "plf.h"
#include <string>
#include <boost/noncopyable.hpp>

class Treelog;
class Metalib;
class Path;
class Units;

#ifdef __unix
#define EXPORT /* Nothing */
#elif defined (BUILD_DLL)
/* DLL export */
#define EXPORT __declspec(dllexport)
#else
/* EXE import */
#define EXPORT __declspec(dllimport)
#endif

class EXPORT Block : private boost::noncopyable
{
  struct Implementation;
  std::auto_ptr<Implementation> impl;
public:
  Metalib& metalib ();
  const Units& units ();
  Path& path ();
  const AttributeList& alist () const;
  const Syntax& syntax () const;
  Treelog& msg () const;

  // Error handling.
  void error (const std::string&);
  bool ok () const;
  void set_error ();

  // Nested scope handling.
public:
  Syntax::type lookup (symbol) const;
  const Syntax& find_syntax (const symbol key) const;
  const AttributeList& find_alist (const symbol key) const;

  // AList emulation.
public:
  bool check (const symbol key) const;
  double number (symbol) const;
  double number (symbol, double default_value) const;
  symbol name (symbol);
  symbol name (symbol, symbol default_value);
  bool flag (symbol) const;
  bool flag (symbol, bool default_value) const;
  const PLF& plf (symbol) const;
  AttributeList& alist (symbol) const;
  int integer (symbol) const;
  int integer (symbol, int default_value) const;
  const std::vector<double>& number_sequence (symbol) const;
  const std::vector<symbol> name_sequence (symbol key);
  const std::vector<bool>& flag_sequence (symbol key) const;
  const std::vector<int>& integer_sequence (symbol key) const;
  const std::vector<const PLF*>& plf_sequence (symbol key) const;
  const std::vector<const AttributeList*>& 
  /**/ alist_sequence (symbol key) const;

  // Create and Destroy.
private:
  static symbol sequence_id (symbol key, size_t index);
  Block ();
public:
  // Toplevel.
  explicit Block (Metalib&, Treelog& msg, const Syntax&, const AttributeList&,
 		  symbol scope_id);
  // build_free
  explicit Block (Metalib&, Treelog& msg, symbol scope_id);
  // build_item
  explicit Block (Block&, const Syntax&, const AttributeList&, 
		  symbol scope_tag);
  // build_vector
  explicit Block (Block&, const Syntax&, const AttributeList&, 
		  symbol scope_tag, size_t index);
  // submodel
  explicit Block (Block&, symbol);
  ~Block ();
};

#endif // BLOCK_H