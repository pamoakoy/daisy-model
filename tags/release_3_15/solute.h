// solute.h
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


#ifndef SOLUTE_H
#define SOLUTE_H

// These must be included in the header file, for 'load_syntax' to work.
#include "adsorption.h"
#include "transport.h"
#include "mactrans.h"

struct Log;
struct Syntax;
struct AttributeList;
struct Geometry;
struct Soil;
struct SoilWater;

class Solute
{
  const string submodel;	// Derived submodel.

  // State variables.
protected:
  vector<double> M_;		// Concentration in soil [g / cm�]
  vector<double> C_;		// Concentration in soil solution [g / cm�]

  // Flux variables.
protected:
  vector<double> S;		// Combined source term.
  vector<double> S_p;		// Source term for macropores only.
  vector<double> S_drain;	// Source term for soil drainage only.
  vector<double> S_external;	// External source term, e.g. incorp. fert.
  vector<double> S_permanent;	// Permanent external source term.
  vector<double> S_root;	// Root uptake source term (negative).
  vector<double> J;		// Solute transport log in matrix.
  vector<double> J_p;		// Solute transport log in macropores.
  Transport& transport;		// Solute transport model in matrix.
  Transport& reserve;		// Reserve solute transport model in matrix.
  Transport& last_resort;       // Last resort solute transport model.
  Mactrans& mactrans;		// Solute transport model in macropores.
  Adsorption& adsorption;	// Solute adsorption.
  
public:
  virtual double diffusion_coefficient () const = 0; // in free solute. 
  double C_to_M (const Soil& soil, double Theta, int i, double C) const
    { return adsorption.C_to_M (soil, Theta, i, C); }
  double M_to_C (const Soil& soil, double Theta, int i, double M) const
    { return adsorption.M_to_C (soil, Theta, i, M); }

public:
  double M (int i) const
  { return M_[i]; }
  double C (int i) const
  { return C_[i]; }
  double M_left (int i) const
  { return M_[i] + S[i] * dt; }
  double total (const Geometry&, double from, double to) const;

  // Sink.
public:
  void clear ();
  void add_to_source (const vector<double>&);
  void add_to_sink (const vector<double>&);
  void add_to_root_sink (const vector<double>&);

  // Simulation.
public:
  void tick (const Soil&, const SoilWater&, double J_in, Treelog&);
  bool check (unsigned n, Treelog& err) const;
  virtual void output (Log&) const;
  void incorporate (const Geometry&, double amount, double from, double to);
  void set_external_source (const Geometry&, 
			    double amount, double from, double to);
  void mix (const Soil&, const SoilWater&, double from, double to);
  void swap (const Soil&, const SoilWater&, double from, double middle, double to);

  // Communication with external model.
  void put_M (const Soil& soil, const SoilWater& soil_water,
	      const vector<double>& v);

  // Create and destroy.
protected:
  static void load_syntax (Syntax&, AttributeList&);
  Solute (const AttributeList& al);
private:
  virtual void default_initialize (const Soil& soil, const SoilWater&);
public:
  virtual void initialize (const AttributeList&,
			   const Soil&, const SoilWater&, Treelog&);
public:
  virtual ~Solute ();
};

#endif // SOLUTE_H
