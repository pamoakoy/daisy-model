// select.h --- Select a state variable.
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


#ifndef SELECT_H
#define SELECT_H

#include "destination.h"
#include "condition.h"		// Needed for proper initialization.
#include "librarian.h"
#include "symbol.h"
#include <map>
#include <vector>

class Geometry;
class Daisy;
class Time;

class Select
{
  // Content.
public:
  const symbol name;
private:
  struct Implementation;
  Implementation& impl;
protected:
  MultiDest dest;
public:
  const bool accumulate;	// Accumulate numbers over time.
  const bool flux;		// Is this a flux variable?
protected:
  const bool interesting_content; // Is this worth an initial line?
  double convert (double) const; // Convert value.
  int count;			// Number of accumulated values.
public:
  static const char *const description;
  virtual const string& dimension () const;
  virtual symbol tag () const;
  symbol log_name () const;
  virtual const Geometry* geometry () const; // For array tags.
  virtual int size () const;	// For array tags.

  // Nesting.
public:
  vector<symbol> path;		// Content of this entry.
  const unsigned int last_index;	// Index of last member in path.
  symbol current_name;
  static const symbol wildcard;
  
public:
  bool valid (const symbol name) const
  { return current_name == wildcard || name == current_name; }
  bool open (const symbol name, const int depth)	// Open one leaf level.
  { 
    // Check if next level is also in path.
    if (!valid (name))
	return false;

    // Direct acces to new head of path.
    current_name = path[depth];
    return true;
  }
  void close (const int depth)		// Close one level.
  { 
    // And restore direct access to current path.
    current_name = path[depth];
  }

  // Output routines.
  virtual void output_number (double);
  virtual void output_integer (int);
  virtual void output_name (symbol);
  virtual void output_array (const vector<double>&, const Geometry*);
  virtual void output_time (const Time&); // Obsolete

  // Reset at start of time step.
public:
  bool is_active;		// Use by log_all.C.
  bool match (bool is_printing)
  { 
    is_active = flux || is_printing;
    return is_active;
  }
  bool initial_match ()
  { 
    is_active = !flux;
    return is_active;
  }
  // Print result at end of time step.
  virtual void done () = 0;
  virtual bool prevent_printing ();

  // Create and Destroy.
protected:
  virtual const string default_dimension (const string& spec_dim) const;
public:
  static void load_syntax (Syntax&, AttributeList&);
  virtual void initialize (const map<symbol, symbol>& conv, 
			   double from, double to, const string& timestep);
  void add_dest (Destination* dest);
  virtual bool check (Treelog& err) const;
protected:
  Select (const AttributeList& al);
public:
  virtual ~Select ();
};

#ifdef FORWARD_TEMPLATES
EMPTY_TEMPLATE
Librarian<Select>::Content* Librarian<Select>::content;
#endif

static Librarian<Select> Select_init ("select");

#endif // SELECT_H