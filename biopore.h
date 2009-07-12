// biopore.h --- A single class of biopores.
// 
// Copyright 2008 Per Abrahamsen and KU.
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


#ifndef BIOPORE_H
#define BIOPORE_H

#include "model_framed.h"
#include "symbol.h"
#include "number.h"
#include "im.h"
#include <memory>
#include <vector>

class BlockModel;
class Geometry;
class Soil;
class SoilHeat;
class Log;
class Anystate;
class Chemical;
class Units;
class Groundwater;
class IM;

class Biopore : public ModelFramed
{
  // Identity.
public:
  static const char *const component;
  symbol library_id () const;

  virtual Anystate get_state () const = 0;
  virtual void set_state (const Anystate&) = 0;

  // Parameters.
protected:
  std::auto_ptr<Number> density_expr; // Biopore density [cm -> m^-2]
  const double height_start;          // Height biopores start [cm]
  const double height_end;            // Height biopores end [cm]
  const double diameter;              // [cm]

  // Log variables.
protected:
  std::vector<double> S;         // Matrix sink term [].
  double infiltration;           // Surface infiltration [cm/h]
  IM solute_infiltration;       // Solute infiltration [g/cm^2/h]

  // Utilities.
protected:
  std::vector<double> density_cell;   // Density based on cell number [m^-2]
  static symbol x_symbol ();

  static double matrix_to_biopore (double K_xx, double M_c, 
                                   double r_c, double h, double h_3);
  
  static double biopore_to_matrix (double R_wall, double M_c, 
                                   double r_c, double h, double h_3);
  double max_infiltration_rate (const Geometry&, size_t e) const; // [cm/h]

  // Interface.
public:
  virtual double total_water () const = 0;
  virtual void get_solute (IM& im) const = 0;
  double density (const size_t c) const
  { return density_cell[c]; }
  virtual double capacity (const Geometry&, size_t e, double dt) 
    /* [cm] */ const = 0;
  virtual void infiltrate (const Geometry&, size_t e,
                           double amount /* [cm] */, double dt /* [h] */);
  virtual void solute_infiltrate (const symbol chem, 
                                  const Geometry& geo, const size_t e,
                                  const double amount /* [g] */, 
                                  const double dt);
  void clear ();
  virtual void update_matrix_sink (const Geometry& geo,    
                                   const Soil& soil,  
                                   const SoilHeat& soil_heat, 
                                   const std::vector<bool>& active,
                                   const double h_barrier,
                                   const double pressure_initiate,
                                   const double pressure_limit,
                                   const std::vector<double>& h, 
                                   const double dt) = 0;
  void scale_sink (double scale);
  virtual void add_to_sink (std::vector<double>& S_matrix,
                            std::vector<double>& S_drain) const = 0;
  virtual void update_water () = 0;
private:
  virtual void add_solute (symbol chem, 
                           size_t cell, double amount /* [g] */) = 0;
public:
  virtual void matrix_solute (const Geometry& geo, double dt, 
                              const Chemical& chemical, 
                              std::vector<double>& source_chem,
                              Treelog& msg) = 0;

protected:
  void output_base (Log&) const;
public:
  virtual void output (Log&) const = 0;

  // Create and Destroy.
protected:
  bool initialize_base (const Units&, const Geometry&, const Scope&, Treelog&);
  bool check_base (const Geometry&, Treelog& msg) const;
public:
  virtual bool initialize (const Units&, 
                           const Geometry&, const Scope&, const Groundwater&,
                           Treelog&) = 0;
  virtual bool check (const Geometry&, Treelog& msg) const = 0;
protected:
  explicit Biopore (const BlockModel& al);
public:
  ~Biopore ();
};

#endif // BIOPORE_H
