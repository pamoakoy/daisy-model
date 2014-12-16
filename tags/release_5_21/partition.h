// partition.h -- Assimilate partioning for the default crop model.
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

#ifndef PARTITION_H
#define PARTITION_H

#include "plf.h"
#include <vector>

class Frame;
class FrameSubmodel;
class Log;

class Partition 
{
  // Parameters.
private:
  const PLF Root;		// Partitioning functions for root
  const PLF Leaf;		//   leaf, and stem as function of DS
  const PLF Stem;
public:
  const PLF RSR;		// Root/Shoot ratio.
private:
  const double nitrogen_stress_limit; // Allocate all ass. to SOrg above this.

  // Utilities.
public:
  void operator () (double DS, double current_RSR, double nitrogen_stress,
		    double& f_Leaf, double& f_Stem,
		    double& f_Root, double& f_SOrg) const;

  // Create and Destroy.
public:
  static void load_syntax (Frame&);
  Partition (const FrameSubmodel&);
  ~Partition ();
};

#endif // PARTITION_H
