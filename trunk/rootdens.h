// rootdens.h -- Root Density component.
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


#ifndef ROOTDENS_H
#define ROOTDENS_H

#include "model.h"
#include <vector>
#include <memory>

class Log;
class Geometry;
class Block;
class Treelog;
class Metalib;

class Rootdens : public ModelFramed
{
  // Content.
public:
  static const char *const component;
  symbol library_id () const;
protected:
  const double SpRtLength;	// Specific root length [m/g]

  // Simulation.
public:
  virtual void set_density (const Geometry& geometry, 
			    double SoilDepth /* [cm] */,
			    double CropDepth /* [cm] */,
			    double CropWidth /* [cm] */,
			    double WRoot /* [g DM/m^2] */, double DS,
			    std::vector<double>& Density /* [cm/cm^3] */,
			    Treelog&) = 0;

  // Create and Destroy.
public:
  static std::auto_ptr<Rootdens> create_row (Metalib&, Treelog&,
                                             double row_width, 
                                             double row_position,
                                             bool debug = false);
  static std::auto_ptr<Rootdens> create_uniform (Metalib&, Treelog&);
public:
  virtual void initialize (const Geometry& geo, 
                           double row_width, double row_position, 
                           Treelog& msg) = 0;
protected:
  explicit Rootdens (Block&);
public:
  ~Rootdens ();
};

#endif // ROOTDENS_H
