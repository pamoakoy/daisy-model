// log_select.h
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


#ifndef LOG_SELECT_H
#define LOG_SELECT_H

#include "log.h"
#include "select.h"		// Need to be here to ensure proper
#include "condition.h"		// initialization in derived classes.
#include <map>
#include <vector>
#include <stack>

struct Select;
struct Condition;

struct LogSelect : public Log
{
  // Parameters.
  const string description;	// Description of log file.
  Condition& condition;	// Should we print a log now?
  std::vector<Select*> entries;
  const std::vector<symbol> conv_vector;
  const double from;
  const double to;

  // State. 
  bool is_printing;		// True iff this time step should be logged.
  bool is_active;		// True iff we need values for this time step.

  // Filter functions.
  bool check_leaf (symbol) const;
  bool check_interior (symbol) const;
  bool check_derived (symbol field, symbol name, const Library&) const;

  // Checking to see if we should log this time step.
  bool match (const Daisy& daisy, Treelog&);
  void done (const Time&);

  // Initial line.
  bool initial_match (const Daisy&, Treelog&);
  void initial_done (const Time& time);

  // Open normal items.
  void open (symbol name);
  void close ();

  // Open named items.
  void open_named (symbol name);
  void close_named ();

  // Open ordered items.
  void open_ordered (int index);
  void close_ordered ();

  // Unnamed items.
  void open_unnamed ();
  void close_unnamed ();

  // Derived items.
  void open_derived (symbol field, symbol type);
  void close_derived ();

  // Derived items in a list.
  void open_entry (symbol type, const AttributeList&);
  void close_entry ();

  // Named derived items in a list.
  void open_named_entry (symbol name, symbol type, 
			 const AttributeList&);
  void close_named_entry ();

  void output (symbol name, bool);
  void output (symbol name, double);
  void output (symbol name, int);
  void output (symbol name, symbol);
  void output (symbol name, const std::vector<double>&);
  void output (symbol name, const PLF&);
  void output (symbol name, const Time&); // Obsolete.

  // Create and Destroy.
  bool check (const Syntax&, Treelog& err) const;
  static void load_syntax (Syntax&, AttributeList&);
  LogSelect (const AttributeList& al);
  ~LogSelect ();
};

#endif // LOG_SELECT_H
