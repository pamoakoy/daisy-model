// chemical.h --- Track a chemical.
// 
// Copyright 1996-2001 Per Abrahamsen and S�ren Hansen
// Copyright 2000-2001 KVL.
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


#ifndef CHEMICAL_H
#define CHEMICAL_H

#include "model.h"
#include "alist.h"

class Geometry;
class Soil;
class SoilWater;
class SoilHeat;
class OrganicMatter;
class VCheck;
class Treelog;
class Log;
class Block;
class Scope;

class Chemical : public Model
{
  // Content.
public:
  const symbol name;
  const AttributeList alist;
  static const char *const component;

  // Some standard chemicals.
public:
  static const symbol NO3 ();
  static const symbol NH4_solute ();
  static const symbol NH4_sorbed ();

  // And standard units.
public:
  static const symbol spray_unit (); // [g/m^2]

  // Soil.
public:
  enum phase_t { solid, solute };
  virtual phase_t phase () const = 0;
  static phase_t get_phase (symbol);
  virtual double diffusion_coefficient () const = 0; // in free solute. 

  // Soil content.
public:
  virtual double C_below () const = 0; // Concentration in groundwater [g/cm^3]
  virtual double M (size_t i) const = 0;
  virtual double C (size_t i) const = 0;
  virtual double M_left (size_t i, double dt) const = 0;
  virtual double total_surface (const Geometry&, 
				double from, double to) const = 0; // [g/cm^2]
  virtual double S (size_t i) const = 0;
  virtual double S_p (size_t i) const = 0;
  
  // Transport.
public:
  virtual void set_macro_flux (size_t e, double value) = 0;
  virtual void set_matrix_flux (size_t e, double value) = 0;
  virtual void set_content (size_t c, double M, double C) = 0;

  // Sink.
public:
  virtual void clear () = 0;
  virtual void add_to_root_sink (const std::vector<double>&, double dt) = 0;
  virtual void add_to_transform_source (const std::vector<double>&,
					double dt) = 0;
  virtual void add_to_transform_sink (const std::vector<double>&,
				      double dt) = 0;
  virtual void add_to_sorption_source (const std::vector<double>&,
				       double dt) = 0;
  virtual void add_to_sorption_sink (const std::vector<double>&,
				     double dt) = 0;

  // Management.
public:
  virtual void deposit (double amount /* [g/m^2] */, double dt /* [h] */) = 0;
  virtual void spray (double amount /* [g/m^2] */, double dt /* [h] */) = 0;
  virtual void dissipate (double amount /* [g/m^2] */, double dt /* [h] */) = 0;
  virtual void harvest (double removed, double surface, double dt) = 0;
  virtual void incorporate (const Geometry&, double amount /* [g/m^2] */, 
			    double from, double to, double dt) = 0;
  virtual void mix (const Geometry& geo, const Soil&, const SoilWater&,
		    double from, double to, double dt) = 0;
  virtual void swap (const Geometry& geo, const Soil&, const SoilWater&,
		     double from, double middle, double to, double dt) = 0;

  // Simulation.
public:
  virtual void tick_top (double snow_leak_rate /* [h^-1] */,
                         double cover /* [] */,
                         double canopy_leak_rate /* [h^-1] */,
                         double surface_runoff_rate /* [h^-1] */,
                         double dt /* [h] */,
			 Treelog&) = 0;
  virtual void tick_soil (size_t cell_size, const SoilWater&, double dt,
			  const Scope&, Treelog&) = 0;
  virtual void mixture (const Geometry& geo,
                        const double pond /* [mm] */, 
                        const double rate /* [h/mm] */,
                        const double dt /* [h]*/) = 0;
  virtual void infiltrate (const double rate, const double dt) = 0;
  virtual double down () = 0;     // [g/m^2/h]
  virtual void uptake (const Soil&, const SoilWater&, double dt) = 0;
  virtual void decompose (const Geometry& geo,
                          const Soil&, const SoilWater&, const SoilHeat&, 
                          const OrganicMatter&, double dt) = 0;
  virtual void output (Log&) const = 0;

  // Create and Destroy.
public:
  static const AttributeList& NO3_model ();
  static const AttributeList& NH4_solute_model ();
  static const AttributeList& NH4_sorbed_model ();
  static const VCheck& check_library ();
  virtual bool check (size_t n, const Scope&, Treelog&) const = 0;
  virtual void initialize (const AttributeList&,
			   const Geometry& geo,
                           const Soil&, const SoilWater&, const SoilHeat&,
			   Treelog&) = 0;
private:
  Chemical ();
  explicit Chemical (const Chemical&);
  Chemical& operator= (const Chemical&);
protected:
  explicit Chemical (Block&);
public:
  ~Chemical ();
};

#endif // CHEMICAL_H
