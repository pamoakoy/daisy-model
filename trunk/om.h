// om.h --- A single organic matter pool.
// 
// Copyright 1996-2001 Per Abrahamsen and S�ren Hansen
// Copyright 2000-2002 Per Abrahamsen and KVL.
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


#ifndef OM_H
#define OM_H

#include "plf.h"
#include <vector>

class FrameSubmodel;
class AttributeList;
class Frame;
class Log;
class Geometry;
class SOM;
class SMB;
class DOM;
class Volume;

class OM
{ 
  // Parameters
public:
  static const double Unspecified;// No initial fraction specified.
  const double initial_C_per_N;	// Initial value for C/N.
  /* const */ std::vector<double> C_per_N_goal; // Prefered C/N value.
  /* const */ PLF heat_factor;
  /* const */ PLF water_factor;

  // Content.
public:
  std::vector<double> C;		// Carbon in each cell.
  std::vector<double> N;		// Nitrogen in each cell.
  const double turnover_rate;	// How fast this is it turned over?
  const std::vector<double> efficiency;	// How digestible is this?
  const std::vector<double> fractions;	// How much is turned into SMB and SOM?

  // Simulation.
public:
  void output (Log&) const;
  void mix (const Geometry&, double from, double to,
            std::vector<double>& N_change, std::vector<double>& C_change, 
            double dt);
  void mix (const Geometry&, const Volume&,
            std::vector<double>& N_change, std::vector<double>& C_change, 
            double dt);
  void swap (const Geometry&, double from, double middle, double to,
             std::vector<double>& N_change, std::vector<double>& C_change,
             double dt);
  double soil_C (const Geometry& geometry) const;
  double soil_N (const Geometry& geometry) const;
  double soil_C (const Geometry& geometry, double from, double to) const;
  double soil_N (const Geometry& geometry, double from, double to) const;
  double goal_C_per_N (size_t at) const; // Desired C/N ratio.
  static void turnover (const double from_C, const double from_N, 
			const double to_C_per_N, const double N_avail,
			double rate, const double efficiency,
			double& C_use, double& N_produce, double& N_consume);
protected:
  virtual void turnover_pool (const std::vector<bool>& active, 
                              const double* factor,
			      double fraction, double efficiency,
			      const double* N_soil, double* N_used, 
			      double* CO2, OM& om, double dt);
  virtual void turnover_dom (const std::vector<bool>& active,
                             const double* factor,
			     double fraction, DOM& dom, double dt);

public:
  void tick (const std::vector<bool>& active, const double* turnover_factor, 
	     const double* N_soil, double* N_used, double* CO2, 
	     const std::vector<SMB*>& smb, const std::vector<SOM*>&som,
	     const std::vector<DOM*>& dom,
             double dt);        // Used by SMB and SOM, but not AOM

  // Utilities.
public:
  static double get_initial_C_per_N (const AttributeList&);

  // Create & Destroy.
public:
  void initialize (size_t);
protected:
  static void load_syntax (FrameSubmodel&, const std::string& frac_desc);
  OM (const AttributeList& al);
  virtual ~OM ();
};

#endif // OM_H
