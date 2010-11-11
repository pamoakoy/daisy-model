// source_file.h -- File source for gnuplot interface 
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

#ifndef SOURCE_FILE_H
#define SOURCE_FILE_H

#include "source.h"
#include "lexer_table.h"
#include "timestep.h"

class SourceFile : public Source
{
  // Content.
protected:
  LexerTable lex;
  symbol with_;
  const bool explicit_with;
  const int style_;
private:
  bool accumulate_;
public:
  const symbol timestep;
private:
  bool use_sum;
  int default_hour;
  const Timestep time_offset;
protected:
  void add_entry (const Time& time, std::vector<double>& vals);
private:
  std::vector<Time> times;
  std::vector<double> values;
  std::vector<double> ebars;
  
  // Interface.
public:
  symbol with () const
  { return with_; }
  int style () const 
  { return style_; }
  bool accumulate () const
  { return accumulate_; }
  const std::vector<Time>& time () const
  { return times; }
  const std::vector<double>& value () const
  { return values; }
  const std::vector<double>& ebar () const
  { return ebars; }

  // Read.
protected:
  bool read_header (Treelog&);
  bool read_entry (std::vector<std::string>&, Time&);

  // Create.
public:
  static void load_style (Frame&, const symbol default_title);
protected:
  explicit SourceFile (const BlockModel&);
public:
  ~SourceFile ();
};

#endif // SOURCE_H

