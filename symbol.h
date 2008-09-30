// symbol.h -- assign unique integers to different strings.
// 
// Copyright 2003 Per Abrahamsen and KVL.
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

#ifndef SYMBOL_H
#define SYMBOL_H

#include <string>
#include <iosfwd>

#ifdef __unix
#define EXPORT /* Nothing */
#elif defined (BUILD_DLL)
/* DLL export */
#define EXPORT __declspec(dllexport)
#else
/* EXE import */
#define EXPORT __declspec(dllimport)
#endif

class symbol 
{
public:
  class EXPORT Init 
  { 
    static int count;
  public:
    Init ();
    ~Init ();
  };
  // Database.
private:
  class DB;
  static DB* data;
  friend class Init;


  // Content.
private:
  int id;

  // Use.
public:
  bool operator== (const symbol& other) const
  { return id == other.id; }
  bool operator!= (const symbol& other) const
  { return id != other.id; }
  bool operator< (const symbol& other) const
  { return id < other.id; }
  const std::string& name () const;

  // Utilities.
public:
  static bool alphabetical (symbol, symbol) EXPORT; // Sort function.

  // Create and destroy.
public:
  explicit symbol ()
    : id (-1)
  { }
  symbol (const char*) EXPORT;
  symbol (const std::string&) EXPORT;
  explicit symbol (int) EXPORT;
  symbol (const symbol& other)
    : id (other.id)
  { }
  void operator= (const symbol& other)
  { id = other.id; }
  ~symbol ()
  { }
};

std::string operator+ (symbol, const char*) EXPORT;
std::string operator+ (const char*, symbol) EXPORT;
std::string operator+ (symbol, const std::string&) EXPORT;
std::string operator+ (const std::string&, symbol) EXPORT;
std::string operator+ (symbol, symbol) EXPORT;
std::ostream& operator<< (std::ostream&, symbol) EXPORT;

static const symbol::Init symbol_init;

#endif // SYMBOL_H
