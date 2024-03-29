// partition.C -- Assimilate partioning for the default crop model.
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

#define BUILD_DLL

#include "partition.h"
#include "plf.h"
#include "librarian.h"
#include "frame_submodel.h"
#include "check.h"
#include "mathlib.h"
#include "treelog.h"
#include <sstream>

void
Partition::operator() (double DS, double current_RSR, double nitrogen_stress,
		       double& f_Leaf, double& f_Stem,
		       double& f_Root, double& f_SOrg) const
{
  if (nitrogen_stress > nitrogen_stress_limit && DS > 1.0)
    {
      f_SOrg = 1.0;
      f_Leaf = f_Stem = f_Root = 0.0;
      return;
    }

  if (current_RSR > RSR (DS))
    f_Root = 0.0;
  else
    f_Root = Root (DS);
  f_Leaf = (1 - f_Root) * Leaf (DS);
  f_Stem = (1 - f_Root) * Stem (DS);
  f_SOrg = std::max (0.0, 1 - f_Root - f_Leaf - f_Stem);
  daisy_assert (f_SOrg > -1e-5);
  if (f_SOrg < 1e-5)
    {
      f_Root += f_SOrg;
      f_SOrg = 0.0;
    }
  daisy_assert (approximate (f_Root + f_Leaf + f_Stem + f_SOrg, 1.0));
  daisy_assert (0.0 <= f_Leaf && f_Leaf <= 1.0);
  daisy_assert (0.0 <= f_Stem && f_Stem <= 1.0);
  daisy_assert (0.0 <= f_Root && f_Root <= 1.0);
  daisy_assert (0.0 <= f_SOrg && f_SOrg <= 1.0);
}

static bool check_alist (const Metalib&, const Frame& al, Treelog& err)
{
  bool ok = true;

  const PLF& Leaf = al.plf ("Leaf");
  const PLF& Stem = al.plf ("Stem");

  PLF Shoot = Stem;
  Shoot += Leaf;

  if (Shoot.max () > 1.0001)
    {
      std::ostringstream tmp;
      tmp << "Leaf and Stem fractions must be <= 1.0 combined.\n"
	     << "They are " << Shoot.max () << " at " << Shoot.max_at ();
      err.error (tmp.str ());
      ok = false;
    }
  return ok;
}

void 
Partition::load_syntax (Frame& frame)
{
  frame.add_check (check_alist);
  frame.declare ("Root", "DS", Attribute::Fraction (), Check::fraction (),
	      Attribute::Const, "\
Fraction of assimilate for growth that goes to the roots, as a function of\n\
the crop development stage.  The remaining growth assimilate goes to the\n\
shoot.");
  frame.declare ("Leaf", "DS", Attribute::Fraction (), Check::fraction (),
	      Attribute::Const,
	      "Fraction of shoot assimilate that goes to the leafs.");
  frame.declare ("Stem", "DS", Attribute::Fraction (), Check::fraction (),
	      Attribute::Const,
	      "Fraction of shoot assimilate that goes to the stem.");
  frame.declare ("RSR", "DS", Attribute::None (), Check::positive (), Attribute::Const,
	      "Maximal root/shoot ratio as a function of development state.\n\
If the root/shoot ratio is above this, the roots will start dying.");
  frame.declare ("nitrogen_stress_limit", Attribute::None (), Check::fraction (), 
              Attribute::Const,
	      "If nitrogen stress is above this number and DS is above 1,\n\
allocate all assimilate to the storage organ.");
  frame.set ("nitrogen_stress_limit", 1.0);
}

Partition::Partition (const FrameSubmodel& al)
  : Root (al.plf ("Root")),
    Leaf (al.plf ("Leaf")),
    Stem (al.plf ("Stem")),
    RSR (al.plf ("RSR")),
    nitrogen_stress_limit (al.number ("nitrogen_stress_limit"))
{ }

Partition::~Partition ()
{ }

static DeclareSubmodel 
partition_submodel (Partition::load_syntax, "Partition", "\
Assimilate partitioning in the default crop model.\n\
The 'Root' parameter determine what fraction of the assimilate for growth\n\
goes to roots at a given development stage.  The remaining assimilate goes\n\
to the shoot.  The 'Leaf' and 'Stem' parameters determine what fraction of\n\
the shoot assimilate goes to the leaf and stem respectively.  The remaining\n\
shoot assimilate will go to the storage organ.");

// partition.C ends here.
