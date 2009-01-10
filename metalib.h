// metalib.h -- A library of libraries.
// 
// Copyright 2007 Per Abrahamsen and KVL.
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


#ifndef METALIB_H
#define METALIB_H

#include "symbol.h"
#include "frame.h"
#include <memory>
#include <vector>

class Path;
class Syntax;
class AttributeList;
class Library;
class Model;
class Treelog;
class Units;
class Unit;

#ifdef __unix
#define EXPORT /* Nothing */
#elif defined (BUILD_DLL)
/* DLL export */
#define EXPORT __declspec(dllexport)
#else
/* EXE import */
#define EXPORT __declspec(dllimport)
#endif

class EXPORT Metalib : public Frame
{
  // Content.
  class Implementation;
  std::auto_ptr<Implementation> impl;

  // Interface.
public:
  const Units& units () const;
  const Unit& get_unit (symbol name) const;
  Path& path () const;
  bool exist (symbol name) const;
  Library& library (symbol name) const;
  Library& library (const char*) const;
  void all (std::vector<symbol>& libraries) const;
  int get_sequence ();
  void clear_all_parsed ();
  void refile_parsed (const std::string& from, const std::string& to);
  void added_object (symbol library, symbol object);

  // Create and Destroy.
public:
  void reset (load_frame_t);
  explicit Metalib (load_frame_t);
  ~Metalib ();
};

#endif // METALIB_H
