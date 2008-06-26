// phenology.h -- Crop development process.
// 
// Copyright 1996-2001, 2003 Per Abrahamsen and S�ren Hansen
// Copyright 2000-2001, 2003 KVL.
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

#ifndef PHENOLOGY_H
#define PHENOLOGY_H

#include "librarian.h"

class Log;
class PLF;
class Production;
class Vernalization;

class Phenology 
{
  // Content.
public:
  const string name;
  static const char *const description;

  // State.
public:
  double DS;	        	// Development Stage
  double partial_day_length;	// Light hours this day until now [0-24 h]
  double day_length;		// Light hours previous day. [0-24 h]
  double partial_soil_temperature; // Accumaleted soil temperature. [�C]
  double soil_temperature;	// Soil temperature previous day. [�C]
  double soil_h;		// Soil potential [cm]

  // Simulation.
public:
  void light_hour ();
  virtual void tick_daily (double Ta, double WLeaf, 
			   Production&, Vernalization&, 
			   double cut_stress, Treelog&) = 0;
  virtual void emergence () = 0;
  void output (Log& log) const;

  // Create and Destroy.
public:
  static void load_syntax (Syntax& syntax, AttributeList& alist);
  Phenology (const AttributeList&);
  virtual ~Phenology ();
};

#if !defined (__BORLANDC__)
EMPTY_TEMPLATE
Librarian<Phenology>::Content* Librarian<Phenology>::content;
#endif

static Librarian<Phenology> Phenology_init ("phenology");

#endif // PHENOLOGY_H