// photo.h -- Leaf photosynthesis component parameters.
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

#ifndef PHOTO_H
#define PHOTO_H

#include "librarian.h"

class CanopyStandard;
class Phenology;
class Log;
class Treelog;

#include <vector>

class Photo 
{
  // Content.
public:
  const symbol name;
  static const char *const description;

  // Simulation.
public:
  virtual double assimilate (double Ta,
                             const std::vector<double>& PAR,
                             const std::vector<double>& PAR_Height,
                             const double PAR_LAI,
                             CanopyStandard& canopy,
                             Phenology& development, Treelog&) const = 0;
  virtual void output (Log&) const = 0;

  // Create and Destroy.
public:
  static const AttributeList& default_model ();
  Photo (Block&);
  virtual ~Photo ();
};

#ifdef FORWARD_TEMPLATES
template<>
Librarian<Photo>::Content* Librarian<Photo>::content;
#endif

static Librarian<Photo> Photo_init ("photosynthesis");

#endif // PHOTO_H