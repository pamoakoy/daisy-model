// photosynthesis.h -- Default leaf photosynthesis parameters.
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

#ifndef PHOTOSYNTHESIS_H
#define PHOTOSYNTHESIS_H

class Bioclimate;
class CanopyStandard;
class Development;
class AttributeList;
class Syntax;
class Log;
class PLF;

class Photosynthesis 
{
  // Parameters.
private:
    double Qeff;	// Quantum efficiency at low light
    double Fm;		// Max assimilation rate
    const PLF& TempEff;	// Temperature effect, photosynthesis
    const PLF& DSEff;	// Development stage effect, photosynthesis

  // Simulation.
public:
  double operator () (const Bioclimate& bioclimate, 
		      CanopyStandard& canopy,
		      Development& development) const;

  // Create and Destroy.
public:
  static void load_syntax (Syntax& syntax, AttributeList& alist);
  Photosynthesis (const AttributeList&);
  ~Photosynthesis ();
};

#endif // PHOTOSYNTHESIS_H